#ifndef _PFSP_RII_CONFIG_HPP
#define _PFSP_RII_CONFIG_HPP

#include <string>

#include "lib/pinput.hpp"
#include "lib/error/exception.hpp"
#include "pfsp_rii/global.hpp"

using namespace pfsp_rii;

namespace pfsp_rii{
	namespace config{

		lib::pinput::helper optparse;

		typedef std::vector<std::string> V;
		typedef std::vector<std::vector<std::string>> D;

		inline void fill(int argc, char *argv[]){
			optparse.usage("pfsp-rii <filename> [options] [flags]")

			.flag("--help", "display help")
			.flag("--verbose", "verbose output")

			.alias("--help", "-h")
			.alias("--verbose", "-v")

			.option("--seed", "seed array for the random engine")
			.option("--init", "initial solution generator")
			.option("--neighborhood", "neighborhood type")
			.option("--max-steps", "step based termination criterion")
			.option("--max-time", "time (ms) based termination criterion")
			.option("--wp", "random solution pivoting probability")

			.alias("--seed", "-s")
			.alias("--init", "-i")
			.alias("--neighborhood", "-n")
			.alias("--max-steps", "-#")
			.alias("--max-time", "-t")
			.alias("--wp", "-w")

			.mandatory("--init")
			.mandatory("--neighborhood")
			.mandatory(D({{"--max-steps"}, {"--max-time"}}))
			.mandatory("--wp")

			.odefault("--seed", {std::to_string(hrclock::now().time_since_epoch().count())})

			.condition("--init",
				[&]{return global::init.count(global::INIT) > 0;},
				"in {slack, random}")
			.condition("--neighborhood",
				[&]{return global::neighborhood.count(global::NEIGHBORHOOD) > 0;},
				"in {transpose, insert, exchange}")
			.condition("--wp", [&]{return global::wp >= 0.0;}, ">= 0")
			.condition("--wp", [&]{return global::wp <= 1.0;}, "<= 1")
			.condition("--max-time", [&]{return global::max_time.count() >= 0;}, ">= 0")

			.oassign("--init", [&](const V& v){global::INIT = v[0];})
			.oassign("--neighborhood", [&](const V& v){global::NEIGHBORHOOD = v[0];})
			.oassign("--wp", [&](const V& v){global::wp = std::stod(v[0]);})
			.oassign("--max-time", [&](const V& v){global::max_time = delta_t(std::stoul(v[0]));})
			.oassign("--max-steps", [&](const V& v){global::max_steps = std::stoul(v[0]);})
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




#endif // _PFSP_RII_CONFIG_HPP