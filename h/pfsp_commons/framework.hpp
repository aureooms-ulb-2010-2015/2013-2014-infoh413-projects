#ifndef _PFSP_COMMONS_FRAMEWORK_HPP
#define _PFSP_COMMONS_FRAMEWORK_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <chrono>

#include "lib/io.hpp"
#include "lib/error/exception.hpp"

#include "pfsp/io/parse/body.hpp"
#include "pfsp/io/parse/header.hpp"
#include "pfsp/mem/allocate.hpp"

namespace pfsp{
namespace framework{


template<typename I>
inline void parse(const std::string& file, I& i){

	std::ifstream in;
	in.open(file);

	if(!in.is_open()) throw lib::error::exception("Could not open input file");

	pfsp::io::parse::header(in, i.nbJob, i.nbMac);
	pfsp::mem::allocate(i.processing, i.dueDates, i.priority, i.proxy, i.nbJob, i.nbMac);
	pfsp::io::parse::body(in, i.nbJob, i.nbMac, i.proxy, i.dueDates, i.priority);

	in.close();


}

template<typename I, typename E, typename TE, typename IE, typename EE, typename F>
inline void init_eval(const I& i, E*& e, F*& te, F*& ie, F*& ee){

	e = new E(i.nbJob, i.nbMac, i.dueDates, i.priority, i.proxy);
	te = new TE(i.nbJob, i.nbMac, i.dueDates, i.priority, i.proxy, e->wt, e->detail);
	ie = new IE(i.nbJob, i.nbMac, i.dueDates, i.priority, i.proxy, e->wt, e->detail);
	ee = new EE(i.nbJob, i.nbMac, i.dueDates, i.priority, i.proxy, e->wt, e->detail);

}

template<typename I, typename E, typename PE, typename F>
inline void init_eval(const I& i, E* e, F*& fn){
	fn = new PE(i.nbJob, i.nbMac, i.dueDates, i.priority, i.proxy, e->wt, e->detail);
}

template<typename I, typename E>
inline void init_eval(const I& i, E*& e){
	e = new E(i.nbJob, i.nbMac, i.dueDates, i.priority, i.proxy);
}


template<typename E, typename F>
inline void clean_eval(E*& e, F*& te, F*& ie, F*& ee){
	delete e;
	delete te;
	delete ie;
	delete ee;
}

template<typename F>
inline void clean_eval(F*& e){
	delete e;
}

template<typename S, typename A, typename B, typename C>
inline void print_step(S& out, const A& steps, const B& duration, const C& opt){
	out << "best "  << opt ;
	out << " step " << steps;
	out << " time " << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
	out << " ms" << std::endl;
}

template<typename S, typename B, typename C, typename D, typename E, typename F>
inline void output(S& out, bool v, const B& s, C& list_p, const D& opt, const E& duration, const F& seed_v){


	if(v){
		out << "done ";
		lib::io::format(out, s, list_p) << std::endl;
	}

	if(v) out << "best ";
	out << opt << std::endl;


	if(v) out << "time ";
	out << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
	if(v) out << " ms";
	out << std::endl;
	

	if(v) out << "seed ";
	lib::io::format(out, seed_v, list_p) << std::endl;
}



template<typename S, typename A, typename B, typename C, typename D, typename E, typename F>
inline int main(S& out, const A& argc, const B& argv, const bool& help_flag, C fill, D help, E check, F run){
	
	try{
		fill(argc, argv);

		if(help_flag){
			help();
			return 0;
		}

		check();
		run();
	}
	catch(const std::exception& e){
		out << "error " << e.what() << std::endl;
		return 1;
	}

	return 0;
}

}
}


#endif // _PFSP_COMMONS_FRAMEWORK_HPP