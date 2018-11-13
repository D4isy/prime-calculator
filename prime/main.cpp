
#include "normal.h"

#include <stdio.h>
#include <windows.h>

#include <iostream>
#include <vector>
#include <thread>

using namespace std;

LARGE_INTEGER start, endd, freq;

void primeThreading(int num, int count, vector<int>& v) {
	thread** th;

	th = new thread*[count];

	for (int i = 0; i < count; i++) {
		th[i] = new thread(procThread, i + 1, num, &v);
	}

	QueryPerformanceCounter(&start);
	for (int i = 0; i < count; i++) {
		th[i]->join();
	}
	QueryPerformanceCounter(&endd);

	for (int i = 0; i < count; i++) {
		delete th[i];
	}

	delete[] th;
}

int main() {
	int n;

	cout << "Prime Calculator (1~n)" << endl;
	cout << "n > ";
	cin >> n;

	int type;
	cout << "[1] general calculate" << endl;
	cout << "[2] upgrade calculate" << endl;
	cout << "[3] multithreading calculate" << endl;
	cout << "type > ";
	cin >> type;

	bool isPrime = false;
	vector<int> v;

	QueryPerformanceFrequency(&freq);

	switch (type) {
	case 1:
		QueryPerformanceCounter(&start);
		for (int i = 2; i < n; i++) {
			isPrime = prime(i);
			if (isPrime) {
				v.push_back(i);
			}
		}
		QueryPerformanceCounter(&endd);
		break;
	case 2:
		QueryPerformanceCounter(&start);
		for (int i = 2; i < n; i++) {
			isPrime = primeUpgrade(i);
			if (isPrime) {
				v.push_back(i);
			}
		}
		QueryPerformanceCounter(&endd);
		break;
	case 3:
		int thread;
		cout << "thread count > ";
		cin >> thread;
		primeThreading(n, thread, v);
		break;
	}

	double ellapse = double((double(endd.QuadPart) - double(start.QuadPart)) / double(freq.QuadPart));
	printf("elapsed time : %.7lf sec\n", ellapse);

	char ch;
	cout << "Do you want print? (y, n)" << endl;
	cout << " > ";
	cin >> ch;

	if (ch == 'y' || ch == 'Y') {
		for (size_t i = 0; i < v.size(); i++) {
			cout << v[i] << " ";
		}
	}

	v.clear();
}