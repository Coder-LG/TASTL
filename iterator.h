#pragma once
#include<iostream>
#include<cstddef>//ptrdiff_t��Ӧ��ͷ�ļ�
/*iterator����*/
namespace TA {
	struct input_iterator_tag {};//���������
	struct output_iterator_tag {};//���������
	struct forward_iterator_tag :public input_iterator_tag {};//ǰ�������
	struct bidirectional_iterator_tag :public forward_iterator_tag {};//˫�������
	struct random_access_iterator_tag :public bidirectional_iterator_tag {};//����L�ʵ�����
	//std::iterator,��׼����������ģ��
	template<class Category, class T, class Distance = ptrdiff_t, class Pointer = T *, class Reference = T &>
	struct iterator {
		typedef Category iterator_category;//�����������ͣ�����֮�е�һ��
		typedef T		 value_type;//��������ָ���Ԫ�ص�����
		typedef Distance difference_type;//�����������Ĳ�ֵ
		typedef Pointer  pointer;//��������ԭʼָ��
		typedef Reference reference;//��������ָ��Ԫ�ص�����
	};

	//ģ��������ȡ�ӿ�
	template<class Iterator>
	struct iterator_traits {
		//���µĲ����൱��һ���ݹ�Ĳ��������ڵݹ���ȡԭʼָ������ֵ
		typedef typename Iterator::iterator_category iterator_category;
		typedef typename Iterator::value_type		 value_type;
		typedef typename Iterator::difference_type   difference_type;
		typedef typename Iterator::pointer		     pointer;
		typedef typename Iterator::reference         reference;
	};
	template<class T>
	struct iterator_traits<T*> {
		//�൱�ڵݹ���ֹ����
		typedef random_access_iterator_tag iterator_category;
		typedef T         value_type;
		typedef ptrdiff_t diffrence_type;
		typedef T* pointer;
		typedef T& reference;
	};
	template<class T>
	struct iterator_traits<const T*> {
		typedef random_access_iterator_tag iterator_category;
		typedef	T		   value_type;
		typedef ptrdiff_t  diffrence_type;
		typedef const T* pointer;//�ص�������
		typedef const T& reference;//��������
	};

	//���������������Ĳ�ֵ���͵ĺ���distance_type
	template<class Iterator>
	inline typename iterator_traits<Iterator>::difference_type* distance_type(const Iterator&) {
		return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
	}

	//��ȡ��������value_type����
	template<class Iterator>
	inline typename iterator_traits<Iterator>::value_type* value_type(const Iterator&) {
		return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
	}

	//������һ�������֮��ľ���ĺ���_distance,��distance�����������
	template<class InputIterator>
	inline typename iterator_traits<InputIterator>::difference_type _distance(InputIterator first, InputIterator last, input_iterator_tag) {
		typename iterator_traits<InputIterator>::difference_type n = 0;
		while (first != last) {
			++first;
			++n;
		}
		return n;
	}
	//����������L�ʵ�����֮��ľ���ĺ���_distance����distance�����������
	template<class RandomAccessIterator>
	inline typename iterator_traits<RandomAccessIterator>::difference_type _distance(RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag) {
		return last - first;
	}

	//����Ӧ�ص���distance����
	template<class InputIterator>
	inline typename iterator_traits<InputIterator>::difference_type
		distance(InputIterator first, InputIterator last) {
		typedef typename iterator_traits<InputIterator>::iterator_category category;
		//��typename�ܹ�������category��һ������
		return _distance(first, last, category());//��ʾ����category��Ĺ��캯�������ظ����һ������
	}

	/*****���µĺ������ڽ�ָ���ƶ�nλ�ķ���*/
	//һ�����������ǰ�ƶ��ķ�������˫���������������ʵ�������ͬ
	template<class InputIterator, class Distance>
	inline void _advance(InputIterator& i, Distance n, input_iterator_tag) {
		while (n--) {
			++i;
		}
	}

	//���˫��������ƶ��ķ���
	template<class BidirectionalIterator, class Distance>
	inline void _advance(BidirectionalIterator& iter, Distance n,
		bidirectional_iterator_tag) {
		if (n >= 0)//��n����0ʱ������ƶ�
		{
			while (n--) {
				++iter;
			}
		} else//��nС��0ʱ����ǰ��
		{
			while (n++) {
				--iter;
			}
		}
	}

	//��������L�ʵ������ƶ��ķ���
	template<class RandomAccessIterator, class Distance>
	inline void _advance(RandomAccessIterator& iter, Distance n,
		random_access_iterator_tag) {
		iter += n;
	}

	//����Ӧ�ĵ���advance����
	template<class InputIterator, class Distance>
	inline void advance(InputIterator& iter, Distance n)
	{
		_advance(i, n, iterator_catetory(iter));
	}
	/*������Ĵ����в��ѷ��֣�ʵ��һ������������Ҫ��һ�¹�����
	1.����5��������ı�־�࣬�ñ�־������ʵ�ֺ����Ĳ����ã������أ��������������������뺯��distance(iter1, iter2, tag)���ƶ�����advance(iter, n, tag)��
	�������־��ֱ�Ϊ��input_iterator_tag��output_iterator_tag��forward_iterator_tag��bidirectional_iterator_tag��random_access_iterator_tag��

	2.����ÿ��iterator�࣬���������5�����ԣ��ֱ�Ϊ��iterator_category��value_type��difference_type��pointer��reference��

	3.����һ���������ġ�����ե֭����iterator_traits�����ڻ�ȡiterator��5������ֵ��

	4.����������Ĳ������ֱ�Ϊ��

	1�� ��ȡiterator�ı�־----->iterator_category(iter)��

	2����ȡ����������ֵ������----->distance_type(iter)��

	3����ȡ��������ԭʼ����--------->value_type(iter)��

	4�������������ľ���---------------- > distance(iter1, iter2, tag)��

	5�����������ƶ�nλ------------------ > advance(iter, n, tag)��*/
}