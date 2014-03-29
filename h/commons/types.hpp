#ifndef _COMMONS_TYPES_HPP
#define _COMMONS_TYPES_HPP

#include <tuple>
#include <vector>
#include <random>
#include <chrono>

#include "pfsp/neighborhood/exchange.hpp"
#include "pfsp/neighborhood/insert.hpp"
#include "pfsp/neighborhood/transpose.hpp"

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


typedef int addr_t;
typedef long int val_t;
typedef long int priority_t;

typedef std::vector<val_t> DD;
typedef std::vector<priority_t> PR;
typedef std::vector<std::vector<val_t>> PM;

typedef std::vector<addr_t> S;
typedef std::tuple<addr_t, addr_t> M;
typedef void (*X)(S&, const M&);

typedef std::default_random_engine random_engine;
typedef std::uniform_int_distribution<size_t> uniform_distribution;

typedef std::chrono::system_clock sysclock;
typedef std::chrono::high_resolution_clock hrclock;

typedef pfsp::pivoting::functor<M>* H;
typedef void (*W)(const S&, H);

typedef pfsp::instance<addr_t, val_t, priority_t> I;

typedef pfsp::eval::init<addr_t, val_t, priority_t, DD, PR, PM, PM, DD> E;

typedef pfsp::eval::functor<val_t, S, M, PM, DD>* ME;
typedef pfsp::eval::transpose<addr_t, val_t, priority_t, S, M, DD, PR, PM, PM, DD> TE;
typedef pfsp::eval::insert<addr_t, val_t, priority_t, S, M, DD, PR, PM, PM, DD> IE;
typedef pfsp::eval::exchange<addr_t, val_t, priority_t, S, M, DD, PR, PM, PM, DD> EE;

typedef std::pair<val_t, M> R;
typedef R (*P)(S&, W, ME);


typedef struct{
	W walk;
	X apply;
	ME eval;
} N;

typedef pfsp::init::functor<S>* IN;


#endif // _COMMONS_TYPES_HPP