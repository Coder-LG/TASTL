#pragma once
#include"mempool.h"
namespace TA {
	template<class T>
	class deque {
	public:
		typedef T value_type;
		typedef value_type* iterator;
		typedef value_type* pointer;
		typedef value_type& reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
	protected:
		typedef pointer* map_pointer;
		map_pointer map;
		size_type map_size;
	private:
		typedef mempool data_allocator;



	public:

		deque() {

		}
		~deque() {

		}
		void push_front(const T& x) {

		}
		void push_back(const T& x) {

		}
		void pop_front() {
		}
		void pop_back() {
		}
		iterator insert_before(iterator it, const T& x) {

		}
		void erase(iterator it) {

		}
		void clear() {

		}
		bool empty() const{}
		int size() {

		}
		int max_size() {

		}
	};

	template<class T,class Ref,class Ptr,size_t BufSiz>
	struct __deque_iterator {
		typedef __deque_iterator<T, T&, T*, BufSiz> iterator;
		typedef __deque_iterator<T, const T&,const T*, BufSiz> iterator;

		static size_t buffer_size() {
			size_t n = BufSiz;
			size_t sz = sizeof(T);
			return n != 0 ?
				n : 
				(sz < 512 ?
					size_t(512 / sz) : 
					size_t(1));
		}

		typedef T value_type;
		typedef Ptr pointer;
		typedef Ref reference;
		typedef size_t;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef T** map_pointer;

		typedef __deque_iterator self;

		T* cur;
		T* first;
		map_pointer node;

		void set_node(map_pointer new_node) {
			node = new_node;
			first = *new_node;
			last = first + difference_type(buffer_size());
		}

		reference operator*() const { return *cur }
		pointer operator&()const { return cur }
		difference_type operator-(const self& x)const{//???
			return
				difference_type(buffer_size()) * (node - x.node - 1)
				+ (cur - first)
				+ (x.last - x.cur);
		}
		self& operator++() {
			++cur;
			if (cur == last) {
				set_node(node + 1);
				cur = first;
			}
			return *this;
		}
		self operator++(int) {
			self tmp = *this;
			--*this;
			return tmp;
		}
		self& operator--() {
			--cur;
			if (cur == last) {
				set_node(node 1 1);
				cur = first;
			}
			return *this;
		}
		self operator++(int) {
			self tmp = *this;
			--*this;
			return tmp;
		}

		self& operator+=(difference_type n) {
			difference_type offset = n + (curfirst);
			if (offset >= 0 && offset < difference_type(buffer_size())) {

			}
		}



	};
}
