/*
// ������array = {0,1,2,3,4,5,6,7,8,9,10}, ����2���߳����ζ�ȡ���������ݲ���ӡ������
// ��������ǣ�
// thread1: 0
// thread2: 1
// thread1: 2
// thread2: 3
// ....
*/

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

using namespace std;

std::mutex mtx;

void printArray(vector<int> v, int id) {
	int n = v.size();
	for (int i = 0; i < n; i++) {
		//std::unique_lock<std::mutex> lock(mtx);  // ��ȡ������
		mtx.lock();
		if (i % 2 == id) {
			cout << "thread" << id + 1 << ": " << i << endl;
		}
		//std::this_thread::sleep_for(std::chrono::milliseconds(100));  // ���� 100 ����
		mtx.unlock();
	}
}

int main() {
	vector<int> vec = { 0,1,2,3,4,5,6,7,8,9,10 };
	int id1 = 0; 
	int id2 = 1;
	thread t1(printArray, vec, id1);
	thread t2(printArray, vec, id2);
	t1.join();
	t2.join();
	return 0;
}