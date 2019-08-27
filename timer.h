#include<ctime>
namespace TA {
	class timer {
		clock_t startTime;
		clock_t endTime;
	public:
		void start() {
			startTime = clock();
		}
		void stop() {
			endTime = clock();
		}
		float getS() {
			return float(endTime - startTime) / CLOCKS_PER_SEC;
		}
		clock_t get() {
			return (endTime - startTime);
		}
	};
}