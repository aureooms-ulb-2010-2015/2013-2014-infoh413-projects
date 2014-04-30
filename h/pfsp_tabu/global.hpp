#ifndef _PFSP_TABU_GLOBAL_HPP
#define _PFSP_TABU_GLOBAL_HPP


#include <vector>
#include <map>
#include <unordered_map>
#include <set>

#include "pfsp/neighborhood/exchange.hpp"
#include "pfsp/neighborhood/insert2.hpp"
#include "pfsp/neighborhood/transpose.hpp"
#include "pfsp/neighborhood/random.hpp"

#include "pfsp/apply/exchange.hpp"
#include "pfsp/apply/insert.hpp"
#include "pfsp/apply/transpose.hpp"

#include "pfsp/tabu/exchange.hpp"
#include "pfsp/tabu/insert.hpp"
#include "pfsp/tabu/transpose.hpp"

#include "pfsp/accept/metropolis.hpp"

#include "pfsp/init/random.hpp"
#include "pfsp/init/slack.hpp"

#include "pfsp/random/exchange.hpp"
#include "pfsp/random/insert.hpp"
#include "pfsp/random/transpose.hpp"

#include "pfsp/instance.hpp"

#include "pfsp_tabu/types.hpp"

namespace pfsp_tabu{
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
		bool help, verbose;

	// DATA
		I i;

	// OPTIONS
		auto init_r = pfsp::init::random<random_engine, uniform_distribution, S>(g);
		auto init_s = pfsp::init::slack<S, addr_t, val_t, priority_t, DD, PR, PMP>(i.nbJob, i.nbMac, i.dueDates, i.priority, i.proxy);

		std::unordered_map<std::string, IN> init{
			{"random", &init_r.f},
			{"slack", &init_s.f}
		};

		E* e = NULL;

		EN transpose = {
			&pfsp::neighborhood::transpose<S, H, M>,
			&pfsp::apply::transpose<S, M>,
			NULL,
			&pfsp::random::transpose<random_engine, uniform_distribution, S, M>,
			&pfsp::tabu::transpose<M, A7, K>
		};

		EN insert = {
			&pfsp::neighborhood::insert2<S, H, M>,
			&pfsp::apply::insert<S, M>,
			NULL,
			&pfsp::random::insert<random_engine, uniform_distribution, S, M>,
			&pfsp::tabu::insert<M, A7, K>
		};

		EN exchange = {
			&pfsp::neighborhood::exchange<S, H, M>,
			&pfsp::apply::exchange<S, M>,
			NULL,
			&pfsp::random::exchange<random_engine, uniform_distribution, S, M>,
			&pfsp::tabu::exchange<M, A7, K>
		};

		std::unordered_map<std::string, EN*> neighborhood{
			{"exchange" , &exchange},
			{"insert" , &insert},
			{"transpose" , &transpose}
		};

		auto walk = &pfsp::neighborhood::random<random_engine, RS, S, H, M>;


	// INPUT
		std::vector<std::string> params;
		std::map<std::string, std::vector<std::string>> options;
		std::set<std::string> flags;
		
		std::set<std::string> option_set = {
			"--seed",
			"--init",
			"--neighborhood",
			"--max-steps",
			"--max-time",
			"--temperature-d",
			"--temperature-p",
			"--alpha",
			"--cooling-step",
			"--tabu-tenure"
		};

		std::set<std::string> flag_set = {
			"-h", "--help",
			"-v", "--verbose"
		};

	// TABU
		uniform_real_distribution r(0.0, 1.0);
		real Tp = 0;
		real Td = 0;
		real T = 0;
		real alpha = -1;
		size_t cooling_step = 0;
		size_t steps = 0;
		size_t max_steps = 0;
		size_t tt = 0;
		delta_t time(0);
		delta_t max_time(0);
		val_t val;
		A7 tabu;

		auto accept = pfsp::accept::metropolis<random_engine, uniform_real_distribution, real, val_t, M>(g, r, T, val);
	}
}



#endif // _PFSP_TABU_GLOBAL_HPP