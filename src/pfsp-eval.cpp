
#include "pfsp_commons/framework.hpp"

#include "pfsp_eval/global.hpp"


using namespace pfsp_eval;

int main(int argc, char *argv[]){

	pfsp::framework::parse(argv[1], global::i);

	std::cout << "jobs " << global::i.nbJob << std::endl;
	std::cout << "mach " << global::i.nbMac << std::endl;

	if(size_t(argc - 2) != global::i.nbJob + 1){
		std::cout << "error wrong #jobs" << std::endl;
	}

	pfsp::framework::init_eval(global::i, global::e);
	size_t n = global::i.nbJob + 1;
	S s(n);
	while(n--){
		s[n] = std::stoi(argv[2 + n]);
	}

	std::cout << "val  " << (*global::e)(s) << std::endl;

	pfsp::framework::clean_eval(global::e);

	return 0;
}
