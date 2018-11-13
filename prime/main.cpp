
#include "normal.h"

#include <stdio.h>
#include <windows.h>

#include <iostream>
#include <vector>
#include <thread>

using namespace std;

void primeThreading(int num, int count, vector<int>& v) {
	thread** th;

	th = new thread*[count];

	for (int i = 0; i < count; i++) {
		th[i] = new thread(procThread, i + 1, num, &v);
	}

	for (int i = 0; i < count; i++) {
		th[i]->join();
	}

	for (int i = 0; i < count; i++) {
		delete th[i];
	}

	delete[] th;
}

int main() {
	int n;

	cout << "�Ҽ� ���ϱ� (1~n)" << endl;
	cout << "n ���� > ";
	cin >> n;

	int type;
	cout << "[1] �Ϲ� �Ҽ� ���ϱ�" << endl;
	cout << "[2] ���׷��̵�� �Ҽ� ���ϱ�" << endl;
	cout << "[3] ��Ƽ������ �Ҽ� ���ϱ�" << endl;
	cout << "���� > ";
	cin >> type;

	bool isPrime = false;
	vector<int> v;

	LARGE_INTEGER start, end, freq;

	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);

	switch (type) {
	case 1:
		for (int i = 2; i < n; i++) {
			isPrime = prime(i);
			if (isPrime) {
				v.push_back(i);
			}
		}
		break;
	case 2:
		for (int i = 2; i < n; i++) {
			isPrime = primeUpgrade(i);
			if (isPrime) {
				v.push_back(i);
			}
		}
		break;
	case 3:
		int thread;
		cout << "������ ���� > ";
		cin >> thread;
		primeThreading(n, thread, v);
		break;
	}

	QueryPerformanceCounter(&end);

	double ellapse = double((double(end.QuadPart) - double(start.QuadPart)) / double(freq.QuadPart));
	printf("����ð� : %.7lf �ʰ� �ɷȽ��ϴ�.\n", ellapse);

	char ch;
	cout << "����Ͻðڽ��ϱ�? ";
	cin >> ch;

	if (ch == 'y' || ch == 'Y') {
		for (size_t i = 0; i < v.size(); i++) {
			cout << v[i] << " ";
		}
	}

	v.clear();
}