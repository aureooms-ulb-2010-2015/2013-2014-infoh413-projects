
#include "pfsp_commons/framework.hpp"

#include "pfsp_sa/global.hpp"
#include "pfsp_sa/config.hpp"


using namespace pfsp_sa;


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

	auto init = global::init[global::options["--init"][0]];
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

	auto neighborhood = global::neighborhood[global::options["--neighborhood"][0]];
	auto accept = global::accept;

// INIT RESTART

	size_t last_improvement = 0;
	const real t = global::T;


// FIND LOCAL OPTIMUM

	hrclock::time_point beg = hrclock::now();

	// SA ALGORITHM
	while(
		(!global::max_steps || global::steps < global::max_steps) &&
		(!global::max_time.count() || global::time < global::max_time)
	){
		M m = (*neighborhood->random)(global::g, s);

		val_t delta = (*neighborhood->eval)(s, m);
		if(delta <= 0 || accept(delta)){
			global::val += delta;
			(*neighborhood->eval)(s, m, global::e->detail, global::e->wt);
			(*neighborhood->apply)(s, m);
		}

		++global::steps;
		global::duration = hrclock::now() - beg;
		global::time = std::chrono::duration_cast<delta_t>(global::duration);

		if(global::val < opt){
			last_improvement = global::steps;
			opt = global::val;
			argopt = s;
			if(global::verbose){
				pfsp::framework::print_step(std::cout, global::steps, global::duration, opt);
			}
		}
		else if(global::steps - last_improvement > global::restart_wait){
			global::T = t;
			s = argopt;
			global::val = (*global::e)(s);
			continue;
		}

		if(global::steps % global::cooling_step == 0){
			global::T *= global::alpha;
			if(global::T == 0) break;
		}


	}
	// <end>

	hrclock::time_point end = hrclock::now();


// CLEAN

	pfsp::framework::clean_eval(global::e, global::transpose.eval, global::insert.eval, global::exchange.eval);


// OUTPUT

	pfsp::framework::output(std::cout, global::verbose, s, global::list_p, opt, end - beg, global::seed_v);
}


int main(int argc, char *argv[]){
	return pfsp::framework::main(std::cout, argc, argv, global::help, &config::fill, &config::help, &config::check, &run);
}
