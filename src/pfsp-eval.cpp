
#include "pfsp_commons/framework.hpp"

#include "pfsp_eval/global.hpp"


using namespace pfsp_eval;

int main(int argc, char *argv[]){

	try{

		if(argc < 2){
			throw lib::error::exception("<filename> missing");
		}

		pfsp::framework::parse(argv[1], global::i);

		std::cout << "jobs " << global::i.nbJob << std::endl;
		std::cout << "mach " << global::i.nbMac << std::endl;

		if(size_t(argc - 2) != global::i.nbJob + 1){
			throw lib::error::exception("wrong #jobs");
		}

		pfsp::framework::init_eval(global::i, global::e);
		size_t n = global::i.nbJob + 1;
		S s(n);
		while(n--){
			s[n] = std::stoi(argv[2 + n]);
		}

		std::cout << "val  " << (*global::e)(s) << std::endl;

		pfsp::framework::clean_eval(global::e);

	}
	catch(const std::exception& e){
		std::cout << "error " << e.what() << std::endl;
		return 1;
	}

	return 0;
}
