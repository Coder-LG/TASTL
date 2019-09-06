#pragma once
#include"vector.h"

namespace TA {
	template<class T>
	class stack {

	private:
		vector<T > arr;

	public:
		stack() {

		}
		~stack() {

		}
		void push(T data) {
			arr.push(data);
		}
		T pop() {
			return arr.last();
		}
	};
}