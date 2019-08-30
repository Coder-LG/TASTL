#pragma once
#include"type_traits.h"
#include"iterator.h"
#include<iostream>
using  std::endl;
namespace TA {
	template<class T1,class T2>
	inline void construct(T1* p, const T2& value) {
		new (p) T1(value);
#ifdef DEBUG
		std::cout << "one constructed" << endl;
#endif // DEBUG
	}

	/*析构单个元素合并为一种情况*/
	template<class T>
	inline void destroy(T* pointer) {
		pointer->~T();
#ifdef DEBUG
		std::cout << "one destroyed" << endl;
#endif // DEBUG
	}
	
	/*序列化析构，如果不用调用析构函数，则不调用，通过重载实现调用与否的判断*/

	inline void destroy(char*, char*) {
#ifdef DEBUG
		std::cout << "multi no need to destroy" << endl;
#endif // DEBUG
	}//没有形参名,参数占位符，调起重载机制
	inline void destroy(wchar_t*, wchar_t*) {
#ifdef DEBUG
		std::cout << "multi no need to destroy" << endl;
#endif // DEBUG
	}
	/*具体类型批量析构入口*/
	template<class iterator, class T>
	inline void __destroy(iterator first, iterator last, T*) {
		typedef typename __type_traits<T>::has_trivial_destructor trivial_destructor;
		__destroy_aux(first, last, trivial_destructor());
	}

	/*不将类型判断暴露出来的批量析构入口*/
	template<class iterator>
	inline void destroy(iterator first, iterator last) {
		__destroy(first, last, value_type(first));
	}


	/*需要批量调用析构函数的情况*/
	template<class iterator>
	inline void __destroy_aux(iterator first,iterator last,__false_type) {
		for (; first < last; first++) {
			destroy(&*first);
		}
	}
	/*不需要批量调用析构函数的情况*/
	template<class iterator>
	inline void __destroy_aux(iterator first, iterator last, __true_type) {
		#ifdef DEBUG
		std::cout << "multi no need to destroy" << endl;
		#endif // DEBUG

	}



}