#define DEBUG
#include<iostream>
#include"timer.h"
#include "mempool.h"
#include"construct.h"
using namespace std;
using namespace TA;
void mempooltest() {
	mempool pool;
	int** x;
	int t = 0;
	x = new int* [10000];
	timer timer;
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

void constructtest() {
	int* a=new int[10];
	for (int i = 0; i < 10; i++) {
		construct(&a[i],i);
		cout << a[i]<<endl;
	}
	destroy(&a[0], &a[9]);
	for (int i = 0; i < 10; i++) {
		cout << a[i] << endl;
	}

}
int main() {
	//mempooltest();
	constructtest();
	return 0;
}