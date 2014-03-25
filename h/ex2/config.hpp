#ifndef _EX2_CONFIG_HPP
#define _EX2_CONFIG_HPP

#include "lib/pinput.hpp"
#include "lib/error/exception.hpp"
#include "ex2/global.hpp"

namespace ex2{
	namespace config{

		inline void fill(int argc, char *argv[]){
			lib::pinput::parse(argc, argv, ex2::global::params, ex2::global::options, ex2::global::flags, ex2::global::option_set, ex2::global::flag_set);	
			ex2::global::help = ex2::global::flags.count("-h") || ex2::global::flags.count("--help");

			// SEED

			if(ex2::global::options.count("--seed") && ex2::global::options["--seed"].size() > 0){
				for(const auto& e : ex2::global::options["--seed"]){
					ex2::global::seed_v.push_back(std::stoll(e));
				}
			}
			else{
				ex2::global::seed_v.push_back(hrclock::now().time_since_epoch().count());
			}

			std::seed_seq seed(ex2::global::seed_v.begin(), ex2::global::seed_v.end());
			ex2::global::g.seed(seed);
		}

		inline void check(){
			if(ex2::global::params.size() < 1) throw lib::error::exception("<filename> missing");
			
			if(ex2::global::options.count("--ordering") == 0 || ex2::global::options["--ordering"].size() == 0)
				throw lib::error::exception("--ordering missing");
			if(ex2::global::ordering.count(ex2::global::options["--ordering"][0]) == 0)
				throw lib::error::exception("wrong --ordering");

			if(ex2::global::options.count("--init") == 0 || ex2::global::options["--init"].size() == 0)
				throw lib::error::exception("--init missing");
			if(ex2::global::init.count(ex2::global::options["--init"][0]) == 0)
				throw lib::error::exception("wrong --init");

			if(ex2::global::options.count("--pivoting") == 0 || ex2::global::options["--pivoting"].size() == 0)
				ex2::global::options["--pivoting"] = decltype(ex2::global::options)::mapped_type({"first"});
			if(ex2::global::pivoting.count(ex2::global::options["--pivoting"][0]) == 0)
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
			std::cout << std::endl;
		}


	}
}




#endif // _EX2_CONFIG_HPP