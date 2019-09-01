#pragma once
#include"mempool.h"
#include"iterator.h"
#include"construct.h"

namespace TA {

	enum err { index_out_of_range }err;

	template<typename T>
	class vector {
	public:
		typedef T value_type;
		typedef value_type* iterator;
		typedef value_type& reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
	private:
		typedef mempool data_allocator;

		value_type* head;		//the array head pointer
		size_type maxindex;		//the length-1 of array
		size_type frontindex;
		void exlength() {
			value_type* newhead = (value_type*)data_allocator::allocate((size_type)((maxindex + 1) * 2*sizeof(value_type)));
			data_allocator::memcpy((char*)newhead, (char*)head, sizeof(T) * (maxindex + 1));

			data_allocator::deallocate(head, (maxindex + 1) * sizeof(value_type));

			maxindex = maxindex * 2 + 1;

			head = newhead;
		}
	public:

		vector(size_type n = 5) {
			maxindex = n - 1;
			frontindex = 0;

			head = (value_type*)data_allocator::allocate(n*sizeof(value_type));
			//memset(head, 0, sizeof(T) * n);
		}

		~vector() {
			destroy(head, head + frontindex);
			data_allocator::deallocate(head, (maxindex + 1) * sizeof(value_type));
		}

		value_type& operator [] (int i) {
			if (i >= frontindex) {
				throw index_out_of_range;
			}

			return head[i];
		}
		void push(value_type in) {
			if (frontindex == maxindex) {
				exlength();
			}

			head[frontindex++] = in;
		}
		void del(int i) {
			if (i >= frontindex) {
				//err= index_out_of_range
				//throw index_out_of_range;
			}

			for (int j = i; j < frontindex; j++) {
				head[j] = head[j + 1];
			}

			frontindex--;

		}
		void insert(int i, value_type in) {
			if (i >= frontindex) {
				//throw index_out_of_range;
			}

			//判断后移是否越界
			if (frontindex + 1 > maxindex) {
				exlength();
			}
			//向后复制时需要总尾开始，否则第一个元素将会覆盖全部
			for (int j = frontindex; j >= i; j--) {
				head[j + 1] = head[j];
			}

			head[i] = in;

			frontindex++;
		}
		int find(value_type target) {
			for (int i = 0; i <= frontindex; i++) {
				if (head[i] == target) {
					return i;
				}
			}
			return -1;
		}
		int getlength() { return frontindex + 1; }
		int getmaxlength() { return maxindex + 1; }
	};
};