#pragma once
#include<intrin.h>//ʹ��Ӣ�ض�ԭ�Ӳ������
namespace TA {
	class mutex {
		long long flag;
	public:
		mutex() {
			flag = 0;
		}
		void lock() {
			while (_interlockedbittestandset64_HLEAcquire(&this->flag, 1)) {

			}
		}
		void unlock() {
			flag = 0;
		}
	};
}