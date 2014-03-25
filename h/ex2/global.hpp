#ifndef _EX2_GLOBAL_HPP
#define _EX2_GLOBAL_HPP


#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <chrono>
#include <random>

#include "pfsp/neighborhood/exchange.hpp"
#include "pfsp/neighborhood/insert.hpp"
#include "pfsp/neighborhood/transpose.hpp"

#include "pfsp/pivoting/functor.hpp"
#include "pfsp/pivoting/best.hpp"
#include "pfsp/pivoting/first.hpp"

#include "pfsp/init/functor.hpp"
#include "pfsp/init/random.hpp"
#include "pfsp/init/slack.hpp"

#include "pfsp/eval.hpp"
#include "pfsp/instance.hpp"


typedef int addr_t;
typedef long int val_t;
typedef long int priority_t;

typedef std::vector<val_t> DD;
typedef std::vector<priority_t> PR;
typedef std::vector<std::vector<val_t>> PM;

typedef std::vector<addr_t> solution;

typedef std::default_random_engine random_engine;
typedef std::uniform_int_distribution<size_t> uniform_distribution;

typedef std::chrono::system_clock sysclock;
typedef std::chrono::high_resolution_clock hrclock;

typedef pfsp::pivoting::functor<solution>* handler;
typedef void (*walk)(const solution&, handler);

typedef pfsp::instance<addr_t, val_t, priority_t> I;
typedef pfsp::eval<addr_t, val_t, priority_t, DD, PR, PM> eval;

typedef solution (*P)(const solution&, walk, eval);

namespace ex2{
	namespace global{


	// IO
		const char* list_p[] = {"", "", " "};

	// CHRONO
		double start, stop, start_c, stop_c;
		hrclock::time_point checkpoint, tmp;
		hrclock::duration duration(0);

	// SEED
		std::vector<long long> seed_v;
		random_engine g;

	// FLAGS
		bool help;

	// DATA
		I i;

	// OPTIONS
		auto init_r = pfsp::init::random<random_engine, uniform_distribution, solution>(g);
		auto init_s = pfsp::init::slack<solution, addr_t, val_t, priority_t, DD, PR, PM>(i.nbJob, i.nbMac, i.dueDates, i.priority, i.processingTimesMatrix);

		std::unordered_map<std::string, pfsp::init::functor<solution>*> init{
			{"random", &init_r.f},
			{"slack", &init_s.f}
		};

		auto transpose = &pfsp::neighborhood::transpose<solution, handler>;
		auto insert = &pfsp::neighborhood::insert<solution, handler>;
		auto exchange = &pfsp::neighborhood::exchange<solution, handler>;

		std::vector<walk> tei({transpose, exchange, insert}), tie({transpose, insert, exchange});

		std::unordered_map<std::string, std::vector<walk>> ordering{
			{"tei" , tei},
			{"tie" , tie}
		};

		std::unordered_map<std::string, P> pivoting{
			{"best", &pfsp::pivoting::best<solution, walk, eval>},
			{"first", &pfsp::pivoting::first<solution, walk, eval>}
		};


	// INPUT
		std::vector<std::string> params;
		std::map<std::string, std::vector<std::string>> options;
		std::set<std::string> flags;
		
		std::set<std::string> option_set = {
			"--seed",
			"--init",
			"--pivoting",
			"--ordering",
		};

		std::set<std::string> flag_set = {
			"-h", "--help"
		};

	}
}



#endif // _EX2_GLOBAL_HPP