#ifndef _PFSP_II_GLOBAL_HPP
#define _PFSP_II_GLOBAL_HPP


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

#include "pfsp/pivoting/metropolis.hpp"

#include "pfsp/init/random.hpp"
#include "pfsp/init/slack.hpp"

#include "pfsp/random/exchange.hpp"
#include "pfsp/random/insert.hpp"
#include "pfsp/random/transpose.hpp"

#include "pfsp/instance.hpp"

#include "pfsp_pii/types.hpp"

namespace pfsp_pii{
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

		E* e = nullptr;

		EN transpose = {
			&pfsp::neighborhood::transpose<S, H, M>,
			&pfsp::apply::transpose<S, M>,
			nullptr,
			&pfsp::random::transpose<random_engine, uniform_distribution, S, M>
		};

		EN insert = {
			&pfsp::neighborhood::insert2<S, H, M>,
			&pfsp::apply::insert<S, M>,
			nullptr,
			&pfsp::random::insert<random_engine, uniform_distribution, S, M>
		};

		EN exchange = {
			&pfsp::neighborhood::exchange<S, H, M>,
			&pfsp::apply::exchange<S, M>,
			nullptr,
			&pfsp::random::exchange<random_engine, uniform_distribution, S, M>
		};

		std::unordered_map<std::string, EN*> neighborhood{
			{"exchange" , &exchange},
			{"insert" , &insert},
			{"transpose" , &transpose}
		};

		auto walk = &pfsp::neighborhood::random<random_engine, RS, S, H, M>;
		auto pivoting = &pfsp::pivoting::metropolis<random_engine, uniform_real_distribution, RS, real, R, val_t, S, M, RW, ME>;


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
			"--temperature"
		};

		std::set<std::string> flag_set = {
			"-h", "--help",
			"-v", "--verbose"
		};

	// PII
		uniform_real_distribution r(0.0, 1.0);
		real T = 0;
		size_t steps = 0;
		size_t max_steps = 0;
		delta_t time(0);
		delta_t max_time(0);

	}
}



#endif // _PFSP_II_GLOBAL_HPP