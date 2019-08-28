#pragma once
#include<iostream>
#include<cstddef>//ptrdiff_t相应的头文件
/*iterator父类*/
namespace TA {
	struct input_iterator_tag {};//输入迭代器
	struct output_iterator_tag {};//输出迭代器
	struct forward_iterator_tag :public input_iterator_tag {};//前向迭代器
	struct bidirectional_iterator_tag :public forward_iterator_tag {};//双向迭代器
	struct random_access_iterator_tag :public bidirectional_iterator_tag {};//随机訪问迭代器
	//std::iterator,标准迭代器的类模板
	template<class Category, class T, class Distance = ptrdiff_t, class Pointer = T *, class Reference = T &>
	struct iterator {
		typedef Category iterator_category;//迭代器的类型，五种之中的一个
		typedef T		 value_type;//迭代器所指向的元素的类型
		typedef Distance difference_type;//两个迭代器的差值
		typedef Pointer  pointer;//迭代器的原始指针
		typedef Reference reference;//迭代器所指向元素的引用
	};

	//模板类型提取接口
	template<class Iterator>
	struct iterator_traits {
		//以下的操作相当于一个递归的操作。用于递归提取原始指针的相关值
		typedef typename Iterator::iterator_category iterator_category;
		typedef typename Iterator::value_type		 value_type;
		typedef typename Iterator::difference_type   difference_type;
		typedef typename Iterator::pointer		     pointer;
		typedef typename Iterator::reference         reference;
	};
	template<class T>
	struct iterator_traits<T*> {
		//相当于递归终止条件
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
		typedef const T* pointer;//重点在这里
		typedef const T& reference;//还有这里
	};

	//定义两个迭代器的差值类型的函数distance_type
	template<class Iterator>
	inline typename iterator_traits<Iterator>::difference_type* distance_type(const Iterator&) {
		return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
	}

	//获取迭代器的value_type函数
	template<class Iterator>
	inline typename iterator_traits<Iterator>::value_type* value_type(const Iterator&) {
		return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
	}

	//求两个一般迭代器之间的距离的函数_distance,供distance函数分类调用
	template<class InputIterator>
	inline typename iterator_traits<InputIterator>::difference_type _distance(InputIterator first, InputIterator last, input_iterator_tag) {
		typename iterator_traits<InputIterator>::difference_type n = 0;
		while (first != last) {
			++first;
			++n;
		}
		return n;
	}
	//求两个随机訪问迭代器之间的距离的函数_distance，供distance函数分类调用
	template<class RandomAccessIterator>
	inline typename iterator_traits<RandomAccessIterator>::difference_type _distance(RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag) {
		return last - first;
	}

	//自适应地调用distance函数
	template<class InputIterator>
	inline typename iterator_traits<InputIterator>::difference_type
		distance(InputIterator first, InputIterator last) {
		typedef typename iterator_traits<InputIterator>::iterator_category category;
		//从typename能够看出。category是一个类型
		return _distance(first, last, category());//显示调用category类的构造函数，返回该类的一个对象
	}

	/*****以下的函数用于将指针移动n位的方法*/
	//一般迭代器求向前移动的方法，与双向迭代器和随机反问迭代器不同
	template<class InputIterator, class Distance>
	inline void _advance(InputIterator& i, Distance n, input_iterator_tag) {
		while (n--) {
			++i;
		}
	}

	//针对双向迭代器移动的方法
	template<class BidirectionalIterator, class Distance>
	inline void _advance(BidirectionalIterator& iter, Distance n,
		bidirectional_iterator_tag) {
		if (n >= 0)//当n大于0时。向后移动
		{
			while (n--) {
				++iter;
			}
		} else//当n小于0时，向前移
		{
			while (n++) {
				--iter;
			}
		}
	}

	//定义随机訪问迭代器移动的方法
	template<class RandomAccessIterator, class Distance>
	inline void _advance(RandomAccessIterator& iter, Distance n,
		random_access_iterator_tag) {
		iter += n;
	}

	//自适应的调用advance函数
	template<class InputIterator, class Distance>
	inline void advance(InputIterator& iter, Distance n)
	{
		_advance(i, n, iterator_catetory(iter));
	}
	/*从上面的代码中不难发现，实现一个迭代器。须要做一下工作：
	1.定义5类迭代器的标志类，该标志类用于实现函数的差别调用（即重载），比如求两迭代器距离函数distance(iter1, iter2, tag)。移动函数advance(iter, n, tag)。
	这五个标志类分别为：input_iterator_tag，output_iterator_tag。forward_iterator_tag，bidirectional_iterator_tag，random_access_iterator_tag。

	2.对于每个iterator类，都必须包括5个属性，分别为：iterator_category、value_type、difference_type、pointer、reference。

	3.定义一个迭代器的“属性榨汁机”iterator_traits，用于获取iterator的5中属性值。

	4.定义迭代器的操作。分别为：

	1） 获取iterator的标志----->iterator_category(iter)。

	2）获取两迭代器差值的类型----->distance_type(iter)。

	3）获取迭代器的原始类型--------->value_type(iter)；

	4）求两迭代器的距离---------------- > distance(iter1, iter2, tag)；

	5）将迭代器移动n位------------------ > advance(iter, n, tag)。*/
}