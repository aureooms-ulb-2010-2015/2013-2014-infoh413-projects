#ifndef _PFSP_II_CONFIG_HPP
#define _PFSP_II_CONFIG_HPP

#include <string>

#include "lib/pinput.hpp"
#include "lib/error/exception.hpp"
#include "pfsp_ii/global.hpp"

using namespace pfsp_rii;

namespace pfsp_rii{
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

			if(global::options.count("--wp") && global::options["--wp"].size() > 0){
				global::wp = std::stod(global::options["--wp"][0]);
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

			if(global::options.count("--wp") == 0 || global::options["--wp"].size() == 0)
				throw lib::error::exception("--wp missing");
			if(global::wp < 0.0 || global::wp > 1.0)
				throw lib::error::exception("wrong --wp");

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




#endif // _PFSP_II_CONFIG_HPP