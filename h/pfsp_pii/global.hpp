#ifndef _PFSP_PII_GLOBAL_HPP
#define _PFSP_PII_GLOBAL_HPP


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

#include "pfsp/accept/metropolis.hpp"

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

		E* e = NULL;


		EN transpose = {
			NULL,
			&pfsp::apply::transpose<S, M>,
			NULL,
			&pfsp::random::transpose<random_engine, uniform_distribution, S, M>
		};

		EN insert = {
			NULL,
			&pfsp::apply::insert<S, M>,
			NULL,
			&pfsp::random::insert<random_engine, uniform_distribution, S, M>
		};

		EN exchange = {
			NULL,
			&pfsp::apply::exchange<S, M>,
			NULL,
			&pfsp::random::exchange<random_engine, uniform_distribution, S, M>
		};

		std::unordered_map<std::string, EN*> neighborhood{
			{"exchange" , &exchange},
			{"insert" , &insert},
			{"transpose" , &transpose}
		};


	// INPUT
		std::vector<std::string> params;
		std::map<std::string, std::vector<std::string>> options;
		std::set<std::string> flags;

	// PII
		uniform_real_distribution r(0.0, 1.0);
		real Tp = 0;
		real Td = 0;
		real T = 0;
		size_t steps = 0;
		size_t max_steps = 0;
		delta_t time(0);
		delta_t max_time(0);
		val_t val;
		
		real sample_size_f = 0;

		std::string NEIGHBORHOOD, INIT;

		auto accept = pfsp::accept::metropolis<random_engine, uniform_real_distribution, real, val_t, M>(g, r, T, val);

	}
}



#endif // _PFSP_PII_GLOBAL_HPP