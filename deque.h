#pragma once
#include"iterator.h"
#include"mempool.h"
namespace TA {
	struct __deque_iterator/*: public iterator<T> */{

	};
	template<class T>
	class deque {
	public:
		typedef T value_type;
		typedef __deque_iterator* iterator;
		typedef value_type* pointer;
		typedef value_type& reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
	private:
		typedef mempool data_allocator;
		typedef struct node {
			node* next;
			node* pre;
			T data;
		}node;
		node* head;
		node* end;
		size_type num;

	public:

		deque() {
			num = 0;
			//end = new node;
			end = (node*)data_allocator::allocate(sizeof(node));
			end->next = nullptr;
			end->pre = nullptr;
			head = end;
		}
		~deque() {
			node* temp = head;
			while (temp->next != nullptr) {
				temp = temp->next;
				destroy(temp->pre);
				data_allocator::deallocate(temp->pre, sizeof(node));
				temp->pre = nullptr;
			}
			destroy(temp);

		}
		void push_front(const T& x) {
			num++;
			head->pre = (node*)data_allocator::allocate(sizeof(node));
			head->pre->data = x;
			head->pre->next = head;
			head->pre->pre = nullptr;
			head = head->pre;
		}
		void push_back(const T& x) {
			num++;
			end->data = x;
			end->next = (node*)data_allocator::allocate(sizeof(node));
			end->next->pre = end;
			end->next->next = nullptr;
			end = end->next;
		}
		T& pop_front() {
			num--;
			T temp = head->data;
			head = head->next;
			data_allocator::deallocate(head->pre, sizeof(node));
			head->pre = nullptr;
			return temp;
		}
		T& pop_back() {
			num--;
			T temp = end->pre->data;
			end = end->pre;
			data_allocator::deallocate(end->next, sizeof(node));
			end->next = nullptr;
			return temp;
		}
		iterator insert_before(iterator it, const T& x) {

		}
		void erase(iterator it) {

		}
		bool empty() const { return num == 0; }
		size_type size() { return num; }
	};


}
