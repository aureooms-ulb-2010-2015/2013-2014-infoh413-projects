
#include "pfsp_commons/framework.hpp"

#include "pfsp_ig/global.hpp"
#include "pfsp_ig/config.hpp"

#include <algorithm>


using namespace pfsp_ig;


void run(){

// PARSE INPUT

	pfsp::framework::parse(global::params[0], global::i);

	if(global::verbose){
		std::cout << "jobs " << global::i.nbJob << std::endl;
		std::cout << "mach " << global::i.nbMac << std::endl;
	}


// INIT EVAL

	pfsp::framework::init_eval<I, E>(global::i, global::e);
	pfsp::framework::init_eval<I, E, IE>(global::i, global::e, global::sinsert.eval);
	pfsp::framework::init_eval<I, E, PIE>(global::i, global::e, global::peval);


// ALIAS

	auto pivoting = global::pivoting[global::PIVOTING];
	auto neighborhood = &global::sinsert;
	auto accept = global::accept;



// SOLUTION

	S s(global::i.nbJob + 1);

// GEN INITIAL SOLUTION

	auto init = global::init[global::INIT];
	(*init)(s);
	global::val = (*global::e)(s);

// COMPUTE CONSTANTS

	const addr_t sample_size = std::max(1.0, real(s.size() - 1) * global::sample_size_f);

	
	hrclock::time_point beg = hrclock::now();

// LS ON INITIAL SOLUTION
	R candidate = pivoting(s, neighborhood->walk, neighborhood->eval);

	while(candidate.first){
		global::val += candidate.first;
		(*neighborhood->eval)(s, candidate.second, global::e->detail, global::e->wt);
		(*neighborhood->apply)(s, candidate.second);

		candidate = pivoting(s, neighborhood->walk, neighborhood->eval);
	}

// BEST BACKUP
	val_t opt = global::val;
	S argopt(s);

// PRINT INITIAL SOL
	if(global::verbose){
		std::cout << "init ";
		lib::io::format(std::cout, s, global::list_p) << std::endl;
		std::cout << "best " << global::val << std::endl;
	}


// FIND LOCAL OPTIMUM


	// IG ALGORITHM
	while(
		(!global::max_steps || global::steps < global::max_steps) &&
		(!global::max_time.count() || global::time < global::max_time)
	){

		S _s = s;
		val_t _val;
		size_t i = 0;

	// DESTRUCTION
		for(; i < sample_size; ++i){
			uniform_distribution u(1, global::i.nbJob - i);
			M m(u(global::g), global::i.nbJob - i);
			(*neighborhood->apply)(_s, m);
		}

		_val = (*global::e)(_s);

	// CONSTRUCTION
		while(i--){
			val_t v = 0;
			M m;
		// FIND BEST MOVE (default none)
			for(size_t j = 1; j < global::i.nbJob - i; ++j){
				M x(global::i.nbJob - i, j);
				val_t t = (*global::peval)(_s, x);
				if(t < v){
					v = t;
					m = x;
				}
			}
			if(v < 0){
				// MAKE MOVE m
				_val += (*neighborhood->eval)(_s, m, global::e->detail, global::e->wt);
				(*neighborhood->apply)(_s, m);
			}
		}

	// LS ON RECONSTRUCTED SOLUTION
		candidate = pivoting(_s, neighborhood->walk, neighborhood->eval);

		while(candidate.first){
			_val += candidate.first;
			(*neighborhood->eval)(_s, candidate.second, global::e->detail, global::e->wt);
			(*neighborhood->apply)(_s, candidate.second);

			candidate = pivoting(_s, neighborhood->walk, neighborhood->eval);
		}

	// TEST ACCEPTANCE CRITERION
		if(_val <= global::val || (global::T > 0.0 && accept(_val - global::val))){
			// ACCEPT
			global::val = _val;
			std::swap(s, _s);
		}
		else{
			// REJECT
			(*global::e)(s);
		}

	// STEP
		++global::steps;
		global::duration = hrclock::now() - beg;
		global::time = std::chrono::duration_cast<delta_t>(global::duration);

	// CHECK BETTER
		if(global::val < opt){
			opt = global::val;
			argopt = s;
			if(global::verbose){
				pfsp::framework::print_step(std::cout, global::steps, global::duration, opt);
			}
		}


	}
	// <end>

	hrclock::time_point end = hrclock::now();


// CLEAN

	pfsp::framework::clean_eval(global::e);
	pfsp::framework::clean_eval(global::sinsert.eval);
	pfsp::framework::clean_eval(global::peval);


// OUTPUT

	pfsp::framework::output(std::cout, global::verbose, argopt, global::list_p, opt, end - beg, global::seed_v);
}


int main(int argc, char *argv[]){
	return pfsp::framework::main(std::cout, argc, argv, global::help, &config::fill, &config::help, &config::check, &run);
}
