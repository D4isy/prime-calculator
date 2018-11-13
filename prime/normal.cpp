
#include <math.h>

#include <iostream>
#include <mutex>
#include <vector>

using namespace std;

int src = 2;
mutex mtx, mtx2;
vector<int> vv;

bool prime(int num) {
	for (int i = 2; i < num; i++) {
		if (num % i == 0) {
			return false;
		}
	}

	return true;
}

bool primeUpgrade(int num) {
	for (int i = 2; i < sqrt(num); i++) {
		if (num % i == 0) {
			return false;
		}
	}

	return true;
}

void procThread(int id, int max, void* v) {

	int num;
	bool check;
	while (src < max) {
		check = true;
		mtx.lock();
		num = src;
		src++;
		mtx.unlock();
		for (int i = 2; i < sqrt(num); i++) {
			if (num % i == 0) {
				check = false;
				break;
			}
		}

		if (check) {
			// 소수 추가
			mtx2.lock();
			((vector<int>*)v)->push_back(num);
			mtx2.unlock();
		}
	}
}