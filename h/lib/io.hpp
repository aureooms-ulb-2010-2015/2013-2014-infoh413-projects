#ifndef _LIB_IO_HPP
#define _LIB_IO_HPP

#include <vector>
#include <map>
#include <queue>
#include <list>
#include <set>

namespace lib{
namespace io{

const char* list_p[] = {"[", "]", ", "};
const char* map_p[]  = {"{", "}", ", ", " : "};

template<typename S, typename T>
S& format(S& out, const std::vector<T>& vector, const char* p[] = list_p){
	out << p[0];
	if(!vector.empty()){
		for (size_t index = 0; index < vector.size()-1; ++index){
			out << vector[index];
			out << p[2];
		}
		out << vector[vector.size()-1];
	}
	out << p[1];
	return out;
}

template<typename S, typename T>
S& format(S& out, const std::list<T>& list, const char* p[] = list_p){
	out << p[0];
	if(!list.empty()){
		typename std::list<T>::const_iterator it = list.cbegin();
		out << *it;
		for (++it; it != list.cend(); ++it){
			out << p[2];
			out << *it;
		}
	}
	out << p[1];
	return out;
}

template<typename S, typename T>
S& format(S& out, std::queue<T> queue, const char* p[] = list_p){
	out << p[0];
	if(!queue.empty()){
		while(queue.size() > 1){
			out << queue.front();
			queue.pop();
			out << p[2];
		}
		out << queue.front();
		queue.pop();
	}
	out << p[1];
	return out;
}

template<typename S, typename Key, typename T>
S& format(S& out, const std::map<Key,T>& map, const char* p[] = map_p){
	out << p[0];
	if (map.size() > 0){
		typename std::map<Key,T>::const_iterator it, pen = --map.end();
		for(it = map.begin(); it != pen; ++it){
			out << it->first;
			out << p[3];
			out << it->second;
			out << p[2];
		}
		out << it->first;
		out << p[3];
		out << it->second;
	}
	out << p[1];
	return out;
}

template<typename S, typename Key, typename T>
S& format(S& out, const std::multimap<Key,T>& map, const char* p[] = map_p){
	out << p[0];
	if (map.size() > 0){
		typename std::multimap<Key,T>::const_iterator it, pen = --map.end();
		for(it = map.begin(); it != pen; ++it){
			out << it->first;
			out << p[3];
			out << it->second;
			out << p[2];
		}
		out << it->first;
		out << p[3];
		out << it->second;
	}
	out << p[1];
	return out;
}

template<typename S, typename T>
S& format(S& out, const std::set<T>& set, const char* p[] = map_p){
	out << p[0];
	if(set.size() > 0){
		bool first = true;
		for(const T& val : set){
			if(!first) out << p[2];
			out << val;
			first = false;
		}
	}
	out << p[1];
	return out;
}

}
}



template<typename S, typename T>
S& operator<<(S& out, const std::vector<T>& vector){
	return lib::io::format(out, vector);
}

template<typename S, typename T>
S& operator<<(S& out, const std::list<T>& list){
	return lib::io::format(out, list);
}

template<typename S, typename T>
S& operator<<(S& out, std::queue<T> queue){
	return lib::io::format(out, queue);
}

template<typename S, typename Key, typename T>
S& operator<<(S& out, const std::map<Key,T>& map){
	return lib::io::format(out, map);
}

template<typename S, typename Key, typename T>
S& operator<<(S& out, const std::multimap<Key,T>& map){
	return lib::io::format(out, map);
}

template<typename S, typename T>
S& operator<<(S& out, const std::set<T>& set){
	return lib::io::format(out, set);
}


#endif //_LIB_IO_HPP
