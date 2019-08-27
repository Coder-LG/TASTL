#include<iostream>
#include"TAspeedometer.h"
#include "TAmempool.h"
using namespace std;

void mempooltest() {
	TAmempool pool;
	int** x;
	int t = 0;
	x = new int* [10000];
	TAtimer timer;
	for (int m = 0; m < 10; m++) {
		timer.start();
		for (int j = 1; j < 200; j++) {
			for (int i = 0; i < 10000; i++) {
				//cout << i<<" ";
				x[i] = (int*)pool.allocate(sizeof(int));
			}
			for (int i = 0; i < 10000; i++) {
				pool.deallocate(x[i], sizeof(int));
			}
		}

		timer.stop();
		cout << timer.get() << endl;
		t += timer.get();
	}
	cout << endl << t / 10;
}




int main() {
	mempooltest();

	return 0;
}