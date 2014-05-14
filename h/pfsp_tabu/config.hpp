#ifndef _PFSP_TABU_CONFIG_HPP
#define _PFSP_TABU_CONFIG_HPP

#include <string>

#include "lib/pinput.hpp"
#include "lib/error/exception.hpp"
#include "pfsp_tabu/global.hpp"

using namespace pfsp_tabu;

namespace pfsp_tabu{
	namespace config{

		lib::pinput::helper optparse;

		typedef std::vector<std::string> V;
		typedef std::vector<std::vector<std::string>> D;

		inline void fill(int argc, char *argv[]){
			optparse.usage("pfsp-tabu <filename> [options] [flags]")

			.flag("--help", "display help")
			.flag("--verbose", "verbose output")

			.alias("--help", "-h")
			.alias("--verbose", "-v")

			.option("--seed", "seed array for the random engine")
			.option("--init", "initial solution generator")
			.option("--neighborhood", "neighborhood type")
			.option("--max-steps", "step based termination criterion")
			.option("--max-time", "time (ms) based termination criterion")
			.option("--restart-wait-f", "number of unsuccessful neighborhood walk steps before restart (neighborhood size %)")
			.option("--sample-size-f-min", "min sample size (neighborhood size %)")
			.option("--sample-size-f-max", "max sample size (neighborhood size %)")
			.option("--tabu-tenure-f-min", "min tenure for the 1st phase (neighborhood size %)")
			.option("--tabu-tenure-f-max", "max tenure for the 1st phase (neighborhood size %)")
			.option("--tabu-tenure-f-2nd", "fixed tenure for the 2nd phase (neighborhood size %)")
			.option("--phase-repartition", "repartition of the computation time between the two phases ([0, p[, [p, 1])")

			.alias("--seed", "-s")
			.alias("--init", "-i")
			.alias("--neighborhood", "-n")
			.alias("--max-steps", "-#")
			.alias("--max-time", "-t")
			.alias("--restart-wait-f", "-r")
			.alias("--sample-size-f-min", "--ssmin")
			.alias("--sample-size-f-max", "--ssmax")
			.alias("--tabu-tenure-f-min", "--ttmin")
			.alias("--tabu-tenure-f-max", "--ttmax")
			.alias("--tabu-tenure-f-2nd", "--tt2nd")
			.alias("--phase-repartition", "--ph")

			.mandatory("--init")
			.mandatory("--neighborhood")
			.mandatory(D({{"--max-steps"}, {"--max-time"}}))
			.mandatory("--restart-wait-f")
			.mandatory("--sample-size-f-min")
			.mandatory("--sample-size-f-max")
			.mandatory("--tabu-tenure-f-min")
			.mandatory("--tabu-tenure-f-max")
			.mandatory("--tabu-tenure-f-2nd")
			.mandatory("--phase-repartition")

			.odefault("--seed", {std::to_string(hrclock::now().time_since_epoch().count())})

			.condition("--init",
				[&]{return global::init.count(global::INIT) > 0;},
				"in {slack, random}")
			.condition("--neighborhood",
				[&]{return global::neighborhood.count(global::NEIGHBORHOOD) > 0;},
				"in {(s)transpose, (s)insert, (s)exchange}")
			.condition("--max-time", [&]{return global::max_time.count() >= 0;}, ">= 0")
			.condition("--sample-size-f-min", [&]{return global::sample_size_f_min > 0.0;}, "> 0")
			.condition("--sample-size-f-min", [&]{return global::sample_size_f_min <= 1.0;}, "<= 1")
			.condition("--sample-size-f-max", [&]{return global::sample_size_f_max > 0.0;}, "> 0")
			.condition("--sample-size-f-max", [&]{return global::sample_size_f_max <= 1.0;}, "<= 1")
			.condition("--restart-wait-f", [&]{return global::restart_wait_f >= 0.0;}, ">= 0")
			.condition("--tabu-tenure-f-min", [&]{return global::ttfmin >= 0.0;}, ">= 0")
			.condition("--tabu-tenure-f-max", [&]{return global::ttfmax >= 0.0;}, ">= 0")
			.condition("--tabu-tenure-f-2nd", [&]{return global::ttf2nd >= 0.0;}, ">= 0")
			.condition("--phase-repartition", [&]{return global::phase_repartition >= 0.0;}, ">= 0")
			.condition("--phase-repartition", [&]{return global::phase_repartition <= 1.0;}, "<= 1")

			.oassign("--init", [&](const V& v){global::INIT = v[0];})
			.oassign("--neighborhood", [&](const V& v){global::NEIGHBORHOOD = v[0];})
			.oassign("--max-time", [&](const V& v){global::max_time = delta_t(std::stoul(v[0]));})
			.oassign("--max-steps", [&](const V& v){global::max_steps = std::stoul(v[0]);})
			.oassign("--sample-size-f-min", [&](const V& v){global::sample_size_f_min = std::stod(v[0]);})
			.oassign("--sample-size-f-max", [&](const V& v){global::sample_size_f_max = std::stod(v[0]);})
			.oassign("--restart-wait-f", [&](const V& v){global::restart_wait_f = std::stod(v[0]);})
			.oassign("--tabu-tenure-f-min", [&](const V& v){global::ttfmin = std::stod(v[0]);})
			.oassign("--tabu-tenure-f-max", [&](const V& v){global::ttfmax = std::stod(v[0]);})
			.oassign("--tabu-tenure-f-2nd", [&](const V& v){global::ttf2nd = std::stod(v[0]);})
			.oassign("--phase-repartition", [&](const V& v){global::phase_repartition = std::stod(v[0]);})
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




#endif // _PFSP_TABU_CONFIG_HPP