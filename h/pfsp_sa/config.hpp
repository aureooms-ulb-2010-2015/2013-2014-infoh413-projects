#ifndef _PFSP_SA_CONFIG_HPP
#define _PFSP_SA_CONFIG_HPP

#include <string>

#include "lib/pinput.hpp"
#include "lib/error/exception.hpp"
#include "pfsp_sa/global.hpp"

using namespace pfsp_sa;

namespace pfsp_sa{
	namespace config{

		lib::pinput::helper optparse;

		typedef std::vector<std::string> V;
		typedef std::vector<std::vector<std::string>> D;

		inline void fill(int argc, char *argv[]){
			optparse.usage("pfsp-sa <filename> [options] [flags]")

			.flag("--help", "display help")
			.flag("--verbose", "verbose output")

			.alias("--help", "-h")
			.alias("--verbose", "-v")

			.option("--seed", "seed array for the random engine")
			.option("--init", "initial solution generator")
			.option("--neighborhood", "neighborhood type")
			.option("--max-steps", "step based termination criterion")
			.option("--max-time", "time (ms) based termination criterion")
			.option("--temperature-d", "delta used for the temperature")
			.option("--temperature-p", "probability used for the temperature")
			.option("--restart-wait-f", "number of unsuccessful neighborhood walk steps before restart (neighborhood size %)")
			.option("--alpha", "cooling factor")
			.option("--cooling-step-f", "cooling step (neighborhood size %)")
			.option("--sample-size-f", "sample size (neighborhood size %)")

			.alias("--seed", "-s")
			.alias("--init", "-i")
			.alias("--neighborhood", "-n")
			.alias("--max-steps", "-#")
			.alias("--max-time", "-t")
			.alias("--temperature-d", "--td")
			.alias("--temperature-p", "--tp")
			.alias("--restart-wait-f", "-r")
			.alias("--alpha", "-a")
			.alias("--cooling-step-f", "-c")
			.alias("--sample-size-f", "--ss")

			.mandatory("--init")
			.mandatory("--neighborhood")
			.mandatory(D({{"--max-steps"}, {"--max-time"}}))
			.mandatory("--temperature-d")
			.mandatory("--temperature-p")
			.mandatory("--restart-wait-f")
			.mandatory("--alpha")
			.mandatory("--cooling-step-f")
			.mandatory("--sample-size-f")

			.odefault("--seed", {std::to_string(hrclock::now().time_since_epoch().count())})

			.condition("--init",
				[&]{return global::init.count(global::INIT) > 0;},
				"in {slack, random}")
			.condition("--neighborhood",
				[&]{return global::neighborhood.count(global::NEIGHBORHOOD) > 0;},
				"in {transpose, insert, exchange}")
			.condition("--temperature-p", [&]{return global::Tp > 0.0;}, "> 0")
			.condition("--temperature-p", [&]{return global::Tp < 1.0;}, "< 1")
			.condition("--temperature-d", [&]{return global::Td > 0.0;}, "> 0")
			.condition("--alpha", [&]{return global::alpha > 0.0;}, "> 0")
			.condition("--alpha", [&]{return global::alpha <= 1.0;}, "<= 1")
			.condition("--cooling-step-f", [&]{return global::cooling_step_f > 0.0;}, ">= 0")
			.condition("--max-time", [&]{return global::max_time.count() >= 0;}, ">= 0")
			.condition("--sample-size-f", [&]{return global::sample_size_f > 0.0;}, "> 0")
			.condition("--sample-size-f", [&]{return global::sample_size_f <= 1.0;}, "<= 1")
			.condition("--restart-wait-f", [&]{return global::restart_wait_f >= 0.0;}, ">= 0")

			.oassign("--init", [&](const V& v){global::INIT = v[0];})
			.oassign("--neighborhood", [&](const V& v){global::NEIGHBORHOOD = v[0];})
			.oassign("--temperature-p", [&](const V& v){global::Tp = std::stod(v[0]);})
			.oassign("--temperature-d", [&](const V& v){global::Td = std::stod(v[0]);})
			.oassign("--alpha", [&](const V& v){global::alpha  = std::stod(v[0]);})
			.oassign("--cooling-step-f", [&](const V& v){global::cooling_step_f = std::stod(v[0]);})
			.oassign("--max-time", [&](const V& v){global::max_time = delta_t(std::stoul(v[0]));})
			.oassign("--max-steps", [&](const V& v){global::max_steps = std::stoul(v[0]);})
			.oassign("--sample-size-f", [&](const V& v){global::sample_size_f = std::stod(v[0]);})
			.oassign("--restart-wait-f", [&](const V& v){global::restart_wait_f = std::stod(v[0]);})
			.oassign("--seed", [&](const V& v){
				for(const auto& e : v) global::seed_v.push_back(std::stoll(e));
			})

			.fassign("--help", [&](const bool v){global::help = v;})
			.fassign("--verbose", [&](const bool v){global::verbose = v;})


			.parse(argc, argv, global::params, global::options, global::flags);

		
			std::seed_seq seed(global::seed_v.begin(), global::seed_v.end());
			global::g.seed(seed);

			global::T = - global::Td / std::log(global::Tp);
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




#endif // _PFSP_SA_CONFIG_HPP