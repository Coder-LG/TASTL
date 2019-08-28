#pragma once
namespace TA {
	template <typename T>
	class SmartPointer {
	private:
		T* m_pointer;
	public:
		explicit SmartPointer(T* p = NULL) {
			m_pointer = p;
		}
		explicit SmartPointer(const SmartPointer<T>& obj) {
			m_pointer = obj.m_pointer;
			const_cast<SmartPointer<T>&>(obj).m_pointer = NULL; /* 同一个对象只允许有一个智能指针指向 */
		}
		SmartPointer<T>& operator = (const SmartPointer<T>& obj) {
			if (this != &obj) {
				delete m_pointer;
				m_pointer = obj.m_pointer;
				const_cast<SmartPointer<T>&>(obj).m_pointer = NULL; /* 同一个对象只允许有一个智能指针指向 */
			}
			return *this;
		}
		T* operator -> () { return m_pointer; }
		T& operator * () { return *m_pointer; }
		bool isNull() { return (m_pointer == NULL); }
		~SmartPointer() { delete m_pointer; }
	};

}