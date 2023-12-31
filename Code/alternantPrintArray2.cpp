/*
// 有数组array = {0,1,2,3,4,5,6,7,8,9,10}, 请用2个线程依次读取该数组内容并打印出来。
// 期望结果是：
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

std::mutex mtx2;
int i = 0;  // 全局变量

void printArray2(vector<int> v, int id) {
	int n = v.size();
	for (; i < n;) {
		//std::unique_lock<std::mutex> lock(mtx);  // 获取互斥锁
		mtx2.lock();
		if (i % 2 == id) {
			cout << "thread" << id + 1 << ": " << i << endl;
			i++;
		}
		//std::this_thread::sleep_for(std::chrono::milliseconds(100));  // 休眠 100 毫秒
		mtx2.unlock();
	}
}

#if 1
int main() {
	vector<int> vec = { 0,1,2,3,4,5,6,7,8,9,10 };
	int id1 = 0;
	int id2 = 1;
	thread t1(printArray2, vec, id1);
	thread t2(printArray2, vec, id2);
	t1.join();
	t2.join();
	return 0;
}
#endif