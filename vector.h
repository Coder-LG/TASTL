#pragma once
#include"mempool.h"
#include"iterator.h"
namespace TA {
	template<class T >
	class vector {
	public:
		typedef T value_type;
		typedef value_type* iterator;
		typedef value_type& reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;

		iterator begin() const { return start; }
		iterator end() const{ return finish; }
		size_type size()const { return (size_type)(end() - start()) }
		size_type capacity()const {return (size_type)(end_of_storage-start()) }
		bool empty() const{ return end() == begin(); }
		reference operator[](size_type n)const{return *(begin()+n) }

		vector():start(0),finish(0),end_of_storage(0){}
		~vector() { deallocate(); }


		reference front() { return *begin(); }
		reference back() { return *(begin()-1); }
		void push_back() {
			if (finish != end_of_storage) {
				//TODO:
				


			}
		}
		void pop_back() {
			destroy(--finish);//????///
		}
	protected:
		typedef mempool data_allocator;
		iterator start;
		iterator finish;
		iterator end_of_storage;
		

		void insert_aux(iterator position,const T& x) {
		}
		void deallocate() {
			if (start) {
				data_allocator::deallocate(start, end_of_storage - start);
			}
		}
	private:

	};
}