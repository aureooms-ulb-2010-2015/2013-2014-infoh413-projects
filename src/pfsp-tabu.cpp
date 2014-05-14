
#include "pfsp_commons/framework.hpp"

#include "pfsp_tabu/global.hpp"
#include "pfsp_tabu/config.hpp"

#include <algorithm>


using namespace pfsp_tabu;


void run(){

// PARSE INPUT

	pfsp::framework::parse(global::params[0], global::i);

	if(global::verbose){
		std::cout << "jobs " << global::i.nbJob << std::endl;
		std::cout << "mach " << global::i.nbMac << std::endl;
	}


// INIT EVAL

	pfsp::framework::init_eval<I,E,TE,IE,EE>(global::i, global::e, global::transpose.eval, global::insert.eval, global::exchange.eval);


// SOLUTION

	S s(global::i.nbJob + 1);


// GEN INITIAL SOLUTION

	auto init = global::init[global::INIT];
	(*init)(s);
	global::val = (*global::e)(s);
	val_t opt = global::val;
	S argopt(s);

	// PRINT IT
	if(global::verbose){
		std::cout << "init ";
		lib::io::format(std::cout, s, global::list_p) << std::endl;
		std::cout << "best " << global::val << std::endl;
	}


// ALIAS

	auto neighborhood = global::neighborhood[global::NEIGHBORHOOD];

// COMPUTING CONSTANTS
	const addr_t ssmin = std::max(1.0, real((*neighborhood->size)(s)) * global::sample_size_f_min);
	const addr_t ssmax = std::max(ssmin + 1, addr_t(real((*neighborhood->size)(s)) * global::sample_size_f_max));
	const addr_t restart_wait = global::restart_wait_f * real((*neighborhood->size)(s));

	uniform_distribution ssd(ssmin, ssmax);

	const addr_t ttmin = 1 + global::ttfmin * real(global::i.nbJob);
	const addr_t ttmax = std::max(ttmin + 1, addr_t(1) + addr_t(global::ttfmax * real(global::i.nbJob)));
	const addr_t tt2nd = 1 + global::ttf2nd * real(global::i.nbJob);

	uniform_distribution ttd(ttmin, ttmax);

	const delta_t phase1dt((unsigned long)(real(global::max_time.count()) * global::phase_repartition));
	const delta_t phase2dt(global::max_time);

	const addr_t phase1steps(addr_t(real(global::max_steps) * global::phase_repartition));
	const addr_t phase2steps(global::max_steps);

// INIT RESTART

	size_t last_improvement = 0;

// INIT TABU

	global::tabu.resize(global::i.nbJob + 1, 0);


// FIND LOCAL OPTIMUM

	hrclock::time_point beg = hrclock::now();

	auto fn = [&](const addr_t tt){
	// SAMPLE NEIGHBORHOOD
		R r(
			std::piecewise_construct,
			std::forward_as_tuple(std::numeric_limits<val_t>::max()),
			std::forward_as_tuple()
		);

		const addr_t i = ssd(global::g);
		addr_t j = i;

		HFN fn = [&](const M& m) -> bool{
			if((*neighborhood->tabu)(s, m, global::tabu, global::steps)) return true;

			val_t v = (*neighborhood->eval)(s, m);
			if(v <= r.first){
				r.first = v;
				r.second = m;
			}

			return --j;
		};

		(*neighborhood->sample)(s, &fn);

		if(j < i){
			global::tabu[s[std::get<0>(r.second)]] = global::steps + tt; // UPDATE TABU COUNTER
			global::val += r.first;
			(*neighborhood->eval)(s, r.second, global::e->detail, global::e->wt);
			(*neighborhood->apply)(s, r.second);
		}

		++global::steps;
		global::duration = hrclock::now() - beg;
		global::time = std::chrono::duration_cast<delta_t>(global::duration);

	// CHECK BETTER
		if(global::val < opt){
			std::fill_n(&global::tabu[1], global::i.nbJob, 0); // RESET TABU VECTOR
			last_improvement = global::steps;
			opt = global::val;
			argopt = s;
			if(global::verbose){
				pfsp::framework::print_step(std::cout, global::steps, global::duration, opt);
			}
		}
	// IF STAGNATION : RESTART FROM BEST KNOW
		else if(restart_wait && global::steps - last_improvement > restart_wait){
			std::fill_n(&global::tabu[1], global::i.nbJob, 0); // RESET TABU VECTOR
			s = argopt;
			global::val = (*global::e)(s);
		}
	};

	// TABU ALGORITHM

	while(
		(!phase2steps || global::steps < phase1steps) &&
		(!phase2dt.count() || global::time < phase1dt)
	) fn(ttd(global::g));

	while(
		(!phase2steps || global::steps < phase2steps) &&
		(!phase2dt.count() || global::time < phase2dt)
	) fn(tt2nd);
	// <end>

	hrclock::time_point end = hrclock::now();


// CLEAN

	pfsp::framework::clean_eval(global::e, global::transpose.eval, global::insert.eval, global::exchange.eval);


// OUTPUT

	pfsp::framework::output(std::cout, global::verbose, argopt, global::list_p, opt, end - beg, global::seed_v);
}


int main(int argc, char *argv[]){
	return pfsp::framework::main(std::cout, argc, argv, global::help, &config::fill, &config::help, &config::check, &run);
}
