#include<Windows.h>
#include<thread>
namespace TA {
	class thread {
	private:
		DWORD WINAPI func(LPVOID);
		int id;
		HANDLE thread_t;
	public:
		thread(void(WINAPI*ifunc)(int id) , int iid) {
			func = ifunc;
			id = iid;
		}
		void start() {
			thread_t = _(NULL, 0,func, &id, 0, NULL);
		}

	};
}