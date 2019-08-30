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

	/*��������Ԫ�غϲ�Ϊһ�����*/
	template<class T>
	inline void destroy(T* pointer) {
		pointer->~T();
#ifdef DEBUG
		std::cout << "one destroyed" << endl;
#endif // DEBUG
	}
	
	/*���л�������������õ��������������򲻵��ã�ͨ������ʵ�ֵ��������ж�*/

	inline void destroy(char*, char*) {
#ifdef DEBUG
		std::cout << "multi no need to destroy" << endl;
#endif // DEBUG
	}//û���β���,����ռλ�����������ػ���
	inline void destroy(wchar_t*, wchar_t*) {
#ifdef DEBUG
		std::cout << "multi no need to destroy" << endl;
#endif // DEBUG
	}
	/*�������������������*/
	template<class iterator, class T>
	inline void __destroy(iterator first, iterator last, T*) {
		typedef typename __type_traits<T>::has_trivial_destructor trivial_destructor;
		__destroy_aux(first, last, trivial_destructor());
	}

	/*���������жϱ�¶�����������������*/
	template<class iterator>
	inline void destroy(iterator first, iterator last) {
		__destroy(first, last, value_type(first));
	}


	/*��Ҫ���������������������*/
	template<class iterator>
	inline void __destroy_aux(iterator first,iterator last,__false_type) {
		for (; first < last; first++) {
			destroy(&*first);
		}
	}
	/*����Ҫ���������������������*/
	template<class iterator>
	inline void __destroy_aux(iterator first, iterator last, __true_type) {
		#ifdef DEBUG
		std::cout << "multi no need to destroy" << endl;
		#endif // DEBUG

	}



}