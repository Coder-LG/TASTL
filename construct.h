#pragma once
#include<new.h>

namespace TA {
	template<class T1,class T2>
	inline void construct(T1* p, const T2& value) {
		new (p) T1(value);
	}

	/*��������Ԫ�غϲ�Ϊһ�����*/
	template<class T>
	inline void destroy(T* pointer) {
		pointer->~T();
	}
	
	/*���л�������������õ��������������򲻵��ã�ͨ������ʵ�ֵ��������ж�*/

	inline void destroy(char*, char*) {}//û���β���,����ռλ�����������ػ���
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