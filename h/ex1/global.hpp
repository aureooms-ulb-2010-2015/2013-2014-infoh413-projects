#ifndef _EX1_GLOBAL_HPP
#define _EX1_GLOBAL_HPP


#include <vector>
#include <map>
#include <unordered_map>
#include <set>

#include "pfsp/neighborhood/exchange.hpp"
#include "pfsp/neighborhood/insert.hpp"
#include "pfsp/neighborhood/transpose.hpp"

#include "pfsp/apply/exchange.hpp"
#include "pfsp/apply/insert.hpp"
#include "pfsp/apply/transpose.hpp"

#include "pfsp/pivoting/best.hpp"
#include "pfsp/pivoting/first.hpp"

#include "pfsp/init/random.hpp"
#include "pfsp/init/slack.hpp"

#include "pfsp/instance.hpp"

#include "commons/types.hpp"

namespace ex1{
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
		auto init_r = pfsp::init::random<random_engine, uniform_distribution, S>(g);
		auto init_s = pfsp::init::slack<S, addr_t, val_t, priority_t, DD, PR, PM>(i.nbJob, i.nbMac, i.dueDates, i.priority, i.processingTimesMatrix);

		std::unordered_map<std::string, IN> init{
			{"random", &init_r.f},
			{"slack", &init_s.f}
		};

		N transpose = {
			&pfsp::neighborhood::transpose<S, H, M>,
			&pfsp::apply::transpose<S, M>,
			nullptr
		};

		N insert = {
			&pfsp::neighborhood::insert<S, H, M>,
			&pfsp::apply::insert<S, M>,
			nullptr
		};

		N exchange = {
			&pfsp::neighborhood::exchange<S, H, M>,
			&pfsp::apply::exchange<S, M>,
			nullptr
		};

		std::unordered_map<std::string, N*> neighborhood{
			{"exchange" , &exchange},
			{"insert" , &insert},
			{"transpose" , &transpose}
		};

		std::unordered_map<std::string, P> pivoting{
			{"best", &pfsp::pivoting::best<R, val_t, S, M, W, ME>},
			{"first", &pfsp::pivoting::first<R, val_t, S, M, W, ME>}
		};


	// INPUT
		std::vector<std::string> params;
		std::map<std::string, std::vector<std::string>> options;
		std::set<std::string> flags;
		
		std::set<std::string> option_set = {
			"--seed",
			"--init",
			"--pivoting",
			"--neighborhood",
		};

		std::set<std::string> flag_set = {
			"-h", "--help"
		};

	}
}



#endif // _EX1_GLOBAL_HPP