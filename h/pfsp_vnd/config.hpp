#ifndef _PFSP_VND_CONFIG_HPP
#define _PFSP_VND_CONFIG_HPP

#include "lib/pinput.hpp"
#include "lib/error/exception.hpp"

#include "pfsp_vnd/global.hpp"

using namespace pfsp_vnd;

namespace pfsp_vnd{
	namespace config{

		lib::pinput::helper optparse;

		typedef std::vector<std::string> V;
		typedef std::vector<std::vector<std::string>> D;

		inline void fill(int argc, char *argv[]){
			optparse.usage("pfsp-ii <filename> [options] [flags]")

			.flag("--help", "display help")
			.flag("--verbose", "verbose output")

			.alias("--help", "-h")
			.alias("--verbose", "-v")

			.option("--seed", "seed array for the random engine")
			.option("--init", "initial solution generator")
			.option("--ordering", "ordering type")
			.option("--pivoting", "pivoting type")

			.alias("--seed", "-s")
			.alias("--init", "-i")
			.alias("--ordering", "-o")
			.alias("--pivoting", "-p")

			.mandatory("--init")
			.mandatory("--ordering")
			.mandatory("--pivoting")

			.odefault("--seed", {std::to_string(hrclock::now().time_since_epoch().count())})

			.condition("--init",
				[&]{return global::init.count(global::INIT) > 0;},
				"in {slack, random}")
			.condition("--ordering",
				[&]{return global::ordering.count(global::ORDERING) > 0;},
				"in {(s)tie, (s)tei}")
			.condition("--pivoting",
				[&]{return global::pivoting.count(global::PIVOTING) > 0;},
				"in {best, first}")

			.oassign("--init", [&](const V& v){global::INIT = v[0];})
			.oassign("--ordering", [&](const V& v){global::ORDERING = v[0];})
			.oassign("--pivoting", [&](const V& v){global::PIVOTING = v[0];})
			.oassign("--seed", [&](const V& v){
				for(const auto& e : v) global::seed_v.push_back(std::stoll(e));
			})

			.fassign("--help", [&](const bool v){global::help = v;})
			.fassign("--verbose", [&](const bool v){global::verbose = v;})


			.parse(argc, argv, global::params, global::options, global::flags);

		
			std::seed_seq seed(global::seed_v.begin(), global::seed_v.end());
			global::g.seed(seed);
		}

		inline void check(){
			if(global::params.size() < 1) throw lib::error::exception("<filename> missing");
			
			optparse.validate(global::params, global::options, global::flags);

		}


		inline void help(){
			optparse.signature();
		}

	}
}




#endif // _PFSP_VND_CONFIG_HPP