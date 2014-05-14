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

#include "pfsp/neighborhood/sexchange.hpp"
#include "pfsp/neighborhood/sinsert.hpp"
#include "pfsp/neighborhood/stranspose.hpp"

#include "pfsp/apply/exchange.hpp"
#include "pfsp/apply/insert.hpp"
#include "pfsp/apply/transpose.hpp"

#include "pfsp/tabu/exchange.hpp"
#include "pfsp/tabu/insert.hpp"
#include "pfsp/tabu/transpose.hpp"

#include "pfsp/init/random.hpp"
#include "pfsp/init/slack.hpp"

#include "pfsp/random/exchange.hpp"
#include "pfsp/random/insert.hpp"
#include "pfsp/random/transpose.hpp"

#include "pfsp/size/exchange.hpp"
#include "pfsp/size/insert.hpp"
#include "pfsp/size/transpose.hpp"

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

		auto __t = pfsp::neighborhood::transpose<S, H, M>();
		auto __i = pfsp::neighborhood::insert2<S, H, M>();
		auto __e = pfsp::neighborhood::exchange<S, H, M>();

		auto __st = pfsp::neighborhood::stranspose<random_engine, uniform_distribution, S, H, M>(g);
		auto __si = pfsp::neighborhood::sinsert<random_engine, uniform_distribution, S, H, M>(g);
		auto __se = pfsp::neighborhood::sexchange<random_engine, uniform_distribution, S, H, M>(g);

		auto __sst = pfsp::neighborhood::stranspose<random_engine, uniform_distribution, S, HPT, M>(g);
		auto __ssi = pfsp::neighborhood::sinsert<random_engine, uniform_distribution, S, HPT, M>(g);
		auto __sse = pfsp::neighborhood::sexchange<random_engine, uniform_distribution, S, HPT, M>(g);

		EN transpose = {
			&__t,
			&pfsp::apply::transpose<S, M>,
			NULL,
			&pfsp::random::transpose<random_engine, uniform_distribution, S, M>,
			&pfsp::size::transpose<addr_t, S>,
			&pfsp::tabu::transpose<S, M, A7, K>,
			&__sst
		};

		EN insert = {
			&__i,
			&pfsp::apply::insert<S, M>,
			NULL,
			&pfsp::random::insert<random_engine, uniform_distribution, S, M>,
			&pfsp::size::insert<addr_t, S>,
			&pfsp::tabu::insert<S, M, A7, K>,
			&__ssi
		};

		EN exchange = {
			&__e,
			&pfsp::apply::exchange<S, M>,
			NULL,
			&pfsp::random::exchange<random_engine, uniform_distribution, S, M>,
			&pfsp::size::exchange<addr_t, S>,
			&pfsp::tabu::exchange<S, M, A7, K>,
			&__sse
		};

		EN stranspose = {
			&__st,
			&pfsp::apply::transpose<S, M>,
			NULL,
			&pfsp::random::transpose<random_engine, uniform_distribution, S, M>,
			&pfsp::size::transpose<addr_t, S>,
			&pfsp::tabu::exchange<S, M, A7, K>,
			&__sst
		};

		EN sinsert = {
			&__si,
			&pfsp::apply::insert<S, M>,
			NULL,
			&pfsp::random::insert<random_engine, uniform_distribution, S, M>,
			&pfsp::size::insert<addr_t, S>,
			&pfsp::tabu::exchange<S, M, A7, K>,
			&__ssi
		};

		EN sexchange = {
			&__se,
			&pfsp::apply::exchange<S, M>,
			NULL,
			&pfsp::random::exchange<random_engine, uniform_distribution, S, M>,
			&pfsp::size::exchange<addr_t, S>,
			&pfsp::tabu::exchange<S, M, A7, K>,
			&__sse
		};

		std::unordered_map<std::string, EN*> neighborhood{
			{"exchange" , &exchange},
			{"insert" , &insert},
			{"transpose" , &transpose},
			{"sexchange" , &sexchange},
			{"sinsert" , &sinsert},
			{"stranspose" , &stranspose}
		};



	// INPUT
		std::vector<std::string> params;
		std::map<std::string, std::vector<std::string>> options;
		std::set<std::string> flags;

	// TABU
		uniform_real_distribution r(0.0, 1.0);
		size_t steps = 0;
		size_t max_steps = 0;
		real restart_wait_f = -1.0;
		real ttfmin = 0;
		real ttfmax = 0;
		real ttf2nd = 0;
		delta_t time(0);
		delta_t max_time(0);
		val_t val;
		real sample_size_f_min = 0;
		real sample_size_f_max = 0;
		real phase_repartition = 0;
		A7 tabu;
		
		std::string NEIGHBORHOOD, INIT;
	}
}



#endif // _PFSP_TABU_GLOBAL_HPP