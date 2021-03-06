#pragma once
#include <vector>
#include <deque>
#include <stack>
#include <list>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <utility>
#include <string>
#include <type_traits>
#include <fstream>
#include <array>
#include <forward_list>
#include <ppl.h>
#include <ppltasks.h>
#include <optional>
#include <experimental\coroutine>
#include <experimental/generator>
//that might be usefull and not in the std already

template<typename T>
decltype(auto) derefCompletely(T& thing) {
	if constexpr(std::is_pointer_v<T>)
		return derefCompletely(*thing);
	else
		return thing;
}

template<typename fn>
struct Not{
	Not(fn t_f) : m_function(std::move(t_f)) {}
	template<typename ... Args>
	decltype(auto) operator()(Args... args) {
		return !m_function(std::forward<Args>(args)...);
	}
private:
	fn m_function;
};//callable that is returns !fn(args...) :D

template<typename fn>
inline auto not(fn func) {
	return Not<fn>(std::forward<fn>(func));
}

inline std::vector<uint64_t> Range(const uint64_t n) {
	std::vector<uint64_t> retVal(n);
	std::generate(retVal.begin(), retVal.end(), [awesome = 0]()mutable {return awesome++; });
	return retVal;
}

inline std::vector<uint64_t> Range(const uint64_t n1,const uint64_t n2) {
	std::vector<uint64_t> retVal(n2 - n1);
	std::generate(retVal.begin(), retVal.end(), [awesome = n1]()mutable {return awesome++; });
	return retVal;
}

template<int size>
inline constexpr std::array<uint64_t, size> RangeArray(const uint64_t start) {
	std::array<uint64_t, size> retVal = {};
	std::generate(retVal.begin(), retVal.end(), [abc = start]()mutable {return abc++; });
	return retVal;
}

//I found this online
inline std::string getFileContents(const std::string& filePath) {
	std::string fileContents;
	std::ifstream file(filePath, std::ios::in);
	file.seekg(0, std::ios::end);
	int filesize = (int)file.tellg();
	file.seekg(0, std::ios::beg);
	filesize -= (int)file.tellg();
	fileContents.resize(filesize);
	file.read(&fileContents[0], filesize);
	file.close();
	return fileContents;
}

template<typename T>
struct removePtrt {
	using val = T;
};

template<typename T>
struct removePtrt<T*> {
	using val = T;
};

inline constexpr int roundToNearest(const int num, const int multiply) {
	return (num / multiply)*multiply + multiply * !!(num%multiply);
}

template<int multiply>
inline constexpr int roundToNearestT(const int num) {
	return (num / multiply)*multiply + multiply * !!(num%multiply);
}

template<typename T>
struct getDimensions {
	static constexpr size_t value = 0;
};
template<typename T,size_t n>
struct getDimensions<std::array<T, n>> {
	static constexpr size_t value = getDimensions<T>::value + 1;
};
template<typename T>
struct getDimensions<std::vector<T>> {
	static constexpr size_t value = getDimensions<T>::value + 1;
};
template<typename T>
struct getDimensions<std::stack<T>> {
	static constexpr size_t value = getDimensions<T>::value + 1;
};
template<typename T,typename U>
struct getDimensions<std::unordered_map<T,U>> {
	static constexpr size_t value = getDimensions<U>::value + 1;
};
template<typename T,typename U>
struct getDimensions<std::map<T,U>> {
	static constexpr size_t value = getDimensions<U>::value + 1;
};
template<typename T>
struct getDimensions<std::list<T>> {
	static constexpr size_t value = getDimensions<T>::value + 1;
};
template<typename T>
struct getDimensions<std::forward_list<T>> {
	static constexpr size_t value = getDimensions<T>::value + 1;
};
template<typename T>
struct getDimensions<std::deque<T>> {
	static constexpr size_t value = getDimensions<T>::value + 1;
};

template<typename T1, typename T2, size_t size>
inline std::array<T1,size> array_cast(std::array<T2,size> oldArray){
	std::array<T1, size> retVal = {};
	for(size_t i = 0;i<size;++i){
		retVal[i] = static_cast<T1>(oldArray[i]);
	}return retVal;
}

template<typename T1, typename T2, size_t size>
constexpr inline std::array<T1, size> array_cast2(std::array<T2, size> oldArray) {
	return array_cast_impl<T1>(oldArray, std::make_index_sequence<size>);
}
template<typename T1, typename T2, size_t size, size_t... i>
constexpr inline std::array<T1, size> array_cast_impl(std::array<T2, size> oldArray, std::index_sequence<i...>) {
	return { static_cast<T1>(oldArray[i])... };
}

inline bool isLetter(char let) {
	return let >= 'a' && let <= 'z' || let >= 'A' && let <= 'Z'; 
}

inline std::vector<std::string> split(const std::string& string,char letter = ' ') {
	std::vector<std::string> retVal;
	//retVal.reserve(3);
	size_t currentA = 0;
	do {
		size_t spot = string.find(letter, currentA);
		if(spot!=currentA)
			retVal.push_back(string.substr(currentA, spot - currentA));
		currentA = spot + 1;
	}while(currentA);//std::string::npos + 1 = 0
	return retVal;
}



inline bool isNumber(char let){
	return let >= '0'&&let <= '9';
}

constexpr size_t out_of_range = -1;
template<typename string_t, typename... pred>
inline size_t find_first_if_not(const string_t& str, size_t off, pred... fn) {
	for (; off < str.size(); ++off){
		bool t = false;
		(void)(std::initializer_list<int>{(t |= fn(str[off]),0)...});
		//if (!(fn(str[off])||...)){}
		if(!t)
			return off;
	}return -1;
}

template<typename string_t, typename... pred>
inline size_t find_first_if(const string_t& str, size_t off, pred... fn) {
	for (; off < str.size(); ++off) {
		bool t = false;
		(void)(std::initializer_list<int>{(t |= fn(str[off]), 0)...});
		//if ((fn(str[off])||...))
		if (t)
			return off;
	}return -1;
}


template<typename... fns>
struct fnOr {
	constexpr fnOr(fns... functions) :m_fns(std::make_tuple(std::forward<fns>(functions)...)) {}
	template<typename... Args>
	decltype(auto) operator()(Args... args){
		return operator_impl(std::forward_as_tuple(std::forward<Args>(args)...), std::index_sequence_for<fns...>()); 
	}
private:
	std::tuple<fns...> m_fns;
	template<typename tuple,size_t... i>
	decltype(auto) operator_impl(tuple args,std::index_sequence<i...>){
		bool t = false;
		(void)(std::initializer_list<int>{(t = t || std::apply(std::get<i>(m_fns), args), 0)...});
		return t;
	}
};

template<typename... fns>
inline constexpr auto make_fnOr(fns... fn){
	return fnOr<fns...>(std::forward<fns>(fn)...);
}

template<typename T,typename adjFn, typename predFn>
inline T breadthFirstSearch(T start,adjFn adj, predFn pred){
	std::vector<T> queue(1, start);
	while (queue.size()){
		std::vector<T> next;
		for(T& node:queue){
			if(pred(node))
				return node;
			for(T&& newNode:adj(node))
				next.push_back(newNode);			
		}queue = std::move(next);
	}return {};
}

template<typename T, typename adjFn, typename predFn>
inline T breadthFirstSearchMultiple(T start, adjFn adj, predFn pred) {
	std::vector<T> queue(1, start);
	std::vector<T> retVal;
	while (queue.size()) {
		std::vector<T> next;
		for (T& node : queue) {
			for (T& newNode : adj(node))
				next.push_back(std::move(newNode));
			if (pred(node))
				retVal.push_back(std::move(node));
		}queue = std::move(next);
	}return retVal;
}

template<typename T,typename adjFn,typename predFn>
inline std::pair<T,bool> depthFirstSearch(T start,adjFn adj,predFn pred){
	if (pred(start))
		return { start,true };
	for(T&& next:adj(start)){
		const auto temp = depthFirstSearch(next, adj, pred);
		if(temp.second)
			return temp;		
	}return { start,false };
}

inline constexpr int ceilDiv(int top, int bot) {
	return (top / bot) + !!(top%bot);
}

inline std::vector<int> splitNumber(const int total,const int n){//splits a number into n ints, as equal as possible
	std::vector<int> retVal(n,total/n);
	for (int i = 0; i < total%n; ++i)
		++retVal[i];	
	return retVal;
}

inline std::experimental::generator<int> splitNumber_g(const int total, const int n) {//splits a number into "equal" ints
	for (int i = 0; i < total%n; ++i)
		co_yield (total / n) + 1;
	for (int i = total%n; i < n; ++i)
		co_yield total / n;
}

template<typename T, typename adjFn, typename predFn>
inline T breadthFirstSearch_p(T start, adjFn adj, predFn pred) {
	std::vector<T> queue(1, start);
	std::optional<T> retVal;
	std::mutex mutex;
	while (queue.size()&&!retVal.has_value()) {
		std::vector<T> next;
		concurrency::parallel_for_each(queue.begin(),queue.end(),[&](T& item){
			if (item)
				retVal = std::move(item);
			else{
				std::unique_lock<std::mutex> lock{ mutex };
				for(auto&& nextItem:adj(item))
					next.emplace_back(std::move(nextItem));				
			}
		});
		queue = std::move(next);
	}return retVal.value();
}

template<typename T>
class circleInt {
public:
	circleInt(T t_per):m_per(t_per){};
	circleInt& operator=(T thingy){
		m_stuff = std::move(thingy);
		m_stuff = m_stuff % m_per;
		return *this;
	}
	operator T(){
		return m_stuff;
	}
	circleInt& operator++(int){
		m_stuff = (m_stuff + 1)%m_per;
		return *this;
	}circleInt& operator++() {
		m_stuff = (m_stuff + 1) % m_per;
		return *this;
	}
	circleInt& operator+(T other){
		m_stuff += other;
		m_stuff = m_stuff%m_per;
		return *this;
	}
	circleInt& operator+=(T other){
		m_stuff += other;
		m_stuff = m_stuff % m_per;
		return *this;
	}
private:
	T m_stuff;
	const T m_per;
};

template<typename Container_t,typename pred>
inline Container_t& remove_if_quick_all(Container_t& vec,pred fn){
	//removes things faster!, loses order	
	vec.erase(std::partition(vec.begin(), vec.end(), not(fn)), vec.end());	
	return vec;
}

template<typename T>
class view {//like std::string_view but with everything!
public:
	view() = default;
	view(T* t_data,size_t t_size):m_data(t_data),m_size(t_size){}
	view(const std::vector<T>& vec):m_data(vec.data()),m_size(vec.size()){};
	const T& operator[](size_t index)const {
		return m_data[index];
	}
	void cut_right(size_t len){
		m_size -= len;
	}
	void cut_left(size_t len){
		m_data += len;
		m_size -= len;
	}
private:
	T* m_data;
	size_t m_size = 0;
};

template<typename container_t,typename T>
inline bool is_in(const container_t& abc, const T item){
	return std::find(abc.begin(), abc.end(), item) != abc.end();
}
/*
template<typename container,typename T>
std::vector<std::vector<container::iterator::value_type>> splity(const container& cont,const T item){
	std::vector<std::vector<typename container::iterator::value_type>> retVal;
	retVal.reserve(10);
	std::vector<typename container::iterator::value_type> vec;
	vec.reserve(20);
	for(const auto& i:cont){
		if (i == item){
			retVal.push_back(vec);
			vec.clear();
		}else if(vec.size()){
			vec.push_back(i);
		}
	}return retVal;
}

*/