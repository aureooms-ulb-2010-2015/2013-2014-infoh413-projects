#ifndef _PFSP_VND_CONFIG_HPP
#define _PFSP_VND_CONFIG_HPP

#include "lib/pinput.hpp"
#include "lib/error/exception.hpp"

#include "pfsp_vnd/global.hpp"

using namespace pfsp_vnd;

namespace pfsp_vnd{
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
		}

		inline void check(){
			if(global::params.size() < 1) throw lib::error::exception("<filename> missing");
			
			if(global::options.count("--ordering") == 0 || global::options["--ordering"].size() == 0)
				throw lib::error::exception("--ordering missing");
			if(global::ordering.count(global::options["--ordering"][0]) == 0)
				throw lib::error::exception("wrong --ordering");

			if(global::options.count("--init") == 0 || global::options["--init"].size() == 0)
				throw lib::error::exception("--init missing");
			if(global::init.count(global::options["--init"][0]) == 0)
				throw lib::error::exception("wrong --init");

			if(global::options.count("--pivoting") == 0 || global::options["--pivoting"].size() == 0)
				global::options["--pivoting"] = decltype(global::options)::mapped_type({"first"});
			if(global::pivoting.count(global::options["--pivoting"][0]) == 0)
				throw lib::error::exception("wrong --pivoting");
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




#endif // _PFSP_VND_CONFIG_HPP