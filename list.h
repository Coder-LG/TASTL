#pragma once
#include"construct.h"
#include"iterator.h"
#include"mempool.h"
#include"type_traits.h"
namespace TA {
	template<class T>
	struct iterator {

	};
	template<class T>
	class list {
	public:
		typedef T value_type;
		typedef value_type* iterator;
		typedef value_type& reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;

		typedef struct node{
			node * next;
			T data;
		}node;

		node* head;

		list() {
			head = nullptr;
		}
		list(const list& in) {

		}
		~list() {
			node* temp = head;
			while (temp != nullptr) {
				destroy();
				temp = temp->next;
			}
		}

		/*ÈÝÁ¿Ïà¹Ø*/
		size_type size() {}
		bool empty() { return head==nullptr; }
	private:
		typedef mempool data_allocator;
	};
}