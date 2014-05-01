#ifndef _PFSP_COMMONS_TYPES_HPP
#define _PFSP_COMMONS_TYPES_HPP

#include <tuple>
#include <vector>
#include "g++-4.8.2/random"
#include <chrono>

#include "lib/array/proxy.hpp"

#include "pfsp/neighborhood/exchange.hpp"
#include "pfsp/neighborhood/insert.hpp"
#include "pfsp/neighborhood/transpose.hpp"
#include "pfsp/neighborhood/functor.hpp"

#include "pfsp/apply/exchange.hpp"
#include "pfsp/apply/insert.hpp"
#include "pfsp/apply/transpose.hpp"

#include "pfsp/pivoting/functor.hpp"

#include "pfsp/init/functor.hpp"

#include "pfsp/eval/init.hpp"
#include "pfsp/eval/exchange.hpp"
#include "pfsp/eval/insert.hpp"
#include "pfsp/eval/transpose.hpp"
#include "pfsp/eval/functor.hpp"

#include "pfsp/instance.hpp"

//
// MEANING OF THOSES TYPES ARE SELF-EVIDENT
// IF NOT: CHECK PFSP AND LIB DOCUMENTATION
// 


typedef size_t addr_t;
typedef int_least32_t val_t;
typedef int_least32_t priority_t;

typedef std::vector<val_t> DD;
typedef std::vector<priority_t> PR;
typedef std::vector<val_t> PM;
typedef lib::array::proxy<val_t> PMP;

typedef std::vector<addr_t> S;
typedef std::tuple<addr_t, addr_t> M;
typedef void (*X)(S&, const M&);

typedef std::default_random_engine random_engine;
typedef std::uniform_int_distribution<size_t> uniform_distribution;

typedef std::chrono::system_clock sysclock;
typedef std::chrono::high_resolution_clock hrclock;

typedef pfsp::pivoting::functor<M>* H;
typedef void (*W)(const S&, H);
typedef pfsp::neighborhood::functor<S, H>* _W;

typedef pfsp::instance<addr_t, val_t, priority_t, DD, PR, PM, PMP> I;

typedef pfsp::eval::init<addr_t, val_t, priority_t, DD, PR, PMP, PM, DD, PMP> E;

typedef pfsp::eval::functor<val_t, S, M, PMP, DD>* ME;
typedef pfsp::eval::transpose<addr_t, val_t, priority_t, S, M, DD, PR, PMP, PM, DD, PMP> TE;
typedef pfsp::eval::insert<addr_t, val_t, priority_t, S, M, DD, PR, PMP, PM, DD, PMP> IE;
typedef pfsp::eval::exchange<addr_t, val_t, priority_t, S, M, DD, PR, PMP, PM, DD, PMP> EE;

typedef std::pair<val_t, M> R;
typedef R (*P)(const S&, W, ME);


typedef struct{
	W walk;
	X apply;
	ME eval;
} N;

typedef pfsp::init::functor<S>* IN;

typedef std::chrono::milliseconds delta_t;


#endif // _PFSP_COMMONS_TYPES_HPP