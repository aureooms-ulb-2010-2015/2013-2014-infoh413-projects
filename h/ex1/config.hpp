#ifndef OS_CONFIG_HPP
#define OS_CONFIG_HPP

#include "lib/pinput.hpp"
#include "lib/error/exception.hpp"
#include "ex1/global.hpp"

namespace ex1{
	namespace config{

		inline void fill(int argc, char *argv[]){
			lib::pinput::parse(argc, argv, ex1::global::params, ex1::global::options, ex1::global::flags, ex1::global::option_set, ex1::global::flag_set);	
			ex1::global::help = ex1::global::flags.count("-h") || ex1::global::flags.count("--help");

			// SEED

			if(ex1::global::options.count("--seed") && ex1::global::options["--seed"].size() > 0){
				for(const auto& e : ex1::global::options["--seed"]){
					ex1::global::seed_v.push_back(std::stoll(e));
				}
			}
			else{
				ex1::global::seed_v.push_back(hrclock::now().time_since_epoch().count());
			}

			std::seed_seq seed(ex1::global::seed_v.begin(), ex1::global::seed_v.end());
			ex1::global::g.seed(seed);
		}

		inline void check(){
			if(ex1::global::params.size() < 1) throw lib::error::exception("<filename> missing");
			
			if(ex1::global::options.count("--neighborhood") == 0 || ex1::global::options["--neighborhood"].size() == 0)
				throw lib::error::exception("--neighborhood missing");
			if(ex1::global::neighborhood.count(ex1::global::options["--neighborhood"][0]) == 0)
				throw lib::error::exception("wrong --neighborhood");

			if(ex1::global::options.count("--init") == 0 || ex1::global::options["--init"].size() == 0)
				throw lib::error::exception("--init missing");
			if(ex1::global::init.count(ex1::global::options["--init"][0]) == 0)
				throw lib::error::exception("wrong --init");

			if(ex1::global::options.count("--pivoting") == 0 || ex1::global::options["--pivoting"].size() == 0)
				throw lib::error::exception("--pivoting missing");
			if(ex1::global::pivoting.count(ex1::global::options["--pivoting"][0]) == 0)
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




#endif // OS_CONFIG_HPP