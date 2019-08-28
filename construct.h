#pragma once
#include<new.h>

namespace TA {
	template<class T1,class T2>
	inline void construct(T1* p, const T2& value) {
		new (p) T1(value);
	}

	/*析构单个元素合并为一种情况*/
	template<class T>
	inline void destroy(T* pointer) {
		pointer->~T();
	}
	
	/*序列化析构，如果不用调用析构函数，则不调用，通过重载实现调用与否的判断*/

	inline void destroy(char*, char*) {}//没有形参名,参数占位符，调起重载机制
	inline void destroy(wchar_t*, wchar_t*) {}
	template<class iterator>
	inline void destroy(iterator first, iterator last) {
		__destroy(first, last, value_type(first));
	}

	template<class iterator , class T>
	inline void __destroy(iterator first, iterator last, T*) {
		typedef typename __type_traits<T>::has_trivial_destructor trivial_destructor;
		__destroy_aux(first, last, trivial_destructor());
	}



}