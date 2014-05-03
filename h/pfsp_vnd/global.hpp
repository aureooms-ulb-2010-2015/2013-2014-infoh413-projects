#ifndef _PFSP_VND_GLOBAL_HPP
#define _PFSP_VND_GLOBAL_HPP


#include <vector>
#include <map>
#include <unordered_map>
#include <set>

#include "pfsp/neighborhood/exchange.hpp"
#include "pfsp/neighborhood/insert2.hpp"
#include "pfsp/neighborhood/transpose.hpp"

#include "pfsp/neighborhood/sexchange.hpp"
#include "pfsp/neighborhood/sinsert.hpp"
#include "pfsp/neighborhood/stranspose.hpp"

#include "pfsp/apply/exchange.hpp"
#include "pfsp/apply/insert.hpp"
#include "pfsp/apply/transpose.hpp"

#include "pfsp/pivoting/best.hpp"
#include "pfsp/pivoting/first.hpp"

#include "pfsp/init/random.hpp"
#include "pfsp/init/slack.hpp"

#include "pfsp/instance.hpp"

#include "pfsp_commons/types.hpp"

namespace pfsp_vnd{
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

		N transpose = {
			&__t,
			&pfsp::apply::transpose<S, M>,
			NULL
		};

		N insert = {
			&__i,
			&pfsp::apply::insert<S, M>,
			NULL
		};

		N exchange = {
			&__e,
			&pfsp::apply::exchange<S, M>,
			NULL
		};

		auto __st = pfsp::neighborhood::stranspose<random_engine, uniform_distribution, S, H, M>(g);
		auto __si = pfsp::neighborhood::sinsert<random_engine, uniform_distribution, S, H, M>(g);
		auto __se = pfsp::neighborhood::sexchange<random_engine, uniform_distribution, S, H, M>(g);

		N stranspose = {
			&__st,
			&pfsp::apply::transpose<S, M>,
			NULL
		};

		N sinsert = {
			&__si,
			&pfsp::apply::insert<S, M>,
			NULL
		};

		N sexchange = {
			&__se,
			&pfsp::apply::exchange<S, M>,
			NULL
		};

		std::vector<N*>
		tei({&transpose, &exchange, &insert}),
		tie({&transpose, &insert, &exchange}),
		stei({&stranspose, &sexchange, &sinsert}),
		stie({&stranspose, &sinsert, &sexchange});

		std::unordered_map<std::string, std::vector<N*>> ordering{
			{"tei" , tei},
			{"tie" , tie},
			{"stie" , stie},
			{"stei" , stei}
		};

		std::unordered_map<std::string, P> pivoting{
			{"best", &pfsp::pivoting::best<R, val_t, S, M, W, ME>},
			{"first", &pfsp::pivoting::first<R, val_t, S, M, W, ME>}
		};


	// INPUT
		std::vector<std::string> params;
		std::map<std::string, std::vector<std::string>> options;
		std::set<std::string> flags;
		
	// VND
		size_t steps = 0;
		delta_t time(0);

		std::string ORDERING, INIT, PIVOTING;

	}
}



#endif // _PFSP_VND_GLOBAL_HPP