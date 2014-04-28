#ifndef _PFSP_IG_CONFIG_HPP
#define _PFSP_IG_CONFIG_HPP

#include <string>

#include "lib/pinput.hpp"
#include "lib/error/exception.hpp"
#include "pfsp_ig/global.hpp"

using namespace pfsp_ig;

namespace pfsp_ig{
	namespace config{

		inline void fill(int argc, char *argv[]){
			lib::pinput::parse(argc, argv, global::params, global::options, global::flags, global::option_set, global::flag_set);	
			global::help = global::flags.count("-h") || global::flags.count("--help");
			global::verbose = global::flags.count("-v") || global::flags.count("--verbose");

			// SEED

			if(global::options.count("--seed") && global::options["--seed"].size() > 0){
				for(const auto& e : global::options["--seed"]){
					global::seed_v.push_back(std::stoll(e));
				}
			}
			else{
				global::seed_v.push_back(hrclock::now().time_since_epoch().count());
			}

			std::seed_seq seed(global::seed_v.begin(), global::seed_v.end());
			global::g.seed(seed);

			if(global::options.count("--temperature") && global::options["--temperature"].size() > 0){
				global::T = std::stod(global::options["--temperature"][0]);
			}

			if(global::options.count("--alpha") && global::options["--alpha"].size() > 0){
				global::alpha = std::stod(global::options["--alpha"][0]);
			}

			if(global::options.count("--cooling-step") && global::options["--cooling-step"].size() > 0){
				global::cooling_step = std::stoul(global::options["--cooling-step"][0]);
			}
			
			if(global::options.count("--max-time") && global::options["--max-time"].size() > 0){
				global::max_time = delta_t(std::stoul(global::options["--max-time"][0]));
			}

			if(global::options.count("--max-steps") && global::options["--max-steps"].size() > 0){
				global::max_steps = std::stoul(global::options["--max-steps"][0]);
			}

		}

		inline void check(){
			if(global::params.size() < 1) throw lib::error::exception("<filename> missing");
			
			if(global::options.count("--neighborhood") == 0 || global::options["--neighborhood"].size() == 0)
				throw lib::error::exception("--neighborhood missing");
			if(global::neighborhood.count(global::options["--neighborhood"][0]) == 0)
				throw lib::error::exception("wrong --neighborhood");

			if(global::options.count("--init") == 0 || global::options["--init"].size() == 0)
				throw lib::error::exception("--init missing");
			if(global::init.count(global::options["--init"][0]) == 0)
				throw lib::error::exception("wrong --init");

			if(global::options.count("--temperature") == 0 || global::options["--temperature"].size() == 0)
				throw lib::error::exception("--temperature missing");
			if(global::T <= 0.0)
				throw lib::error::exception("wrong --temperature");

			if(global::options.count("--alpha") == 0 || global::options["--alpha"].size() == 0)
				throw lib::error::exception("--alpha missing");
			if(global::alpha <= 0.0 || global::alpha > 1.0)
				throw lib::error::exception("wrong --alpha");

			if(global::options.count("--cooling-step") == 0 || global::options["--cooling-step"].size() == 0)
				throw lib::error::exception("--cooling-step missing");
			if(global::cooling_step == 0)
				throw lib::error::exception("wrong --cooling-step");

			if(
				(global::options.count("--max-time") == 0 || global::options["--max-time"].size() == 0) &&
				(global::options.count("--max-steps") == 0 || global::options["--max-steps"].size() == 0)
			) throw lib::error::exception("please specify at least one termination criterion (--max-time or --max-steps)");

			if(global::max_time.count() < 0)
				throw lib::error::exception("--max-time must be a non negative value");



		}


		inline void help(){
			std::cout << "> OPTION" << std::endl;
			std::cout << std::endl;
			std::cout << "  --seed" << " " << "long long[]" << std::endl;
			std::cout << std::endl;
			std::cout << "> FLAG" << std::endl;
			std::cout << std::endl;
			std::cout << "  -h | --help" << std::endl;
			std::cout << "  -v | --verbose" << std::endl;
			std::cout << std::endl;
		}


	}
}




#endif // _PFSP_IG_CONFIG_HPP