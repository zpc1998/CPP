# include<iostream>
# include<thread>
# include<vector>
# include<mutex>
# include<condition_variable>
# include<queue>
#include <ctime>
#include <windows.h>
using namespace std;

# define PRODUCT_SIZE 5//生产者数量
# define CUSTOMER_SIZE 20//消费者数量
#define MAX_SIZE 10//最大产品数量
mutex mut;//互斥锁
condition_variable con;//条件变量
queue<int> que;//队列，模拟缓冲区
void Producter()
{

	while (true)
	{
		srand(int(time(NULL))); // 用于计算机产生伪随机数
		std::unique_lock <std::mutex> lck(mut); // 添加锁，防止生产者与消费者同时访问共享缓存区
		while (que.size() > MAX_SIZE)//当队列已满时等待，不再生产
		{
			con.wait(lck);//P操作，阻塞当前生产者进程，停止生产
		}
		int data = rand()%1000 + 1;//随机产生数字代表商品的生产
		que.push(data);//将数据推入队列代表商品加入缓冲区
		cout << this_thread::get_id() << "生产了产品：" << data << endl;
		Sleep(500);
		con.notify_all();//唤醒所有等待的进程，即V操作

	}
}
void Customer()
{
	while (true)
	{
		std::unique_lock <std::mutex> lck(mut);
		while (que.empty())//当队列为空时等待，不再消费
		{
			//用condition_variable对象实现对缓冲区的互斥操作
			con.wait(lck);//P操作,唤醒生产者线程，生产产品
		}
		cout << this_thread::get_id() << "消费了产品：" << que.front() << endl;
		Sleep(500);
		que.pop(); // 消费产品后，产品池不满，唤醒所有wait的进程
		con.notify_all();//唤醒所有等待的进程，即V操作
	}
}
int main()
{
	vector<thread> threadPoll;
	//创建生产者和消费者
	cout << "开始创建生产者和消费者" << endl;
	for (int i = 0; i < PRODUCT_SIZE; ++i)
	{
		threadPoll.push_back(thread(Producter)); // 创建一个后，该线程即开始执行
	}
	for (int i = 0; i < PRODUCT_SIZE + CUSTOMER_SIZE; ++i)
	{
		threadPoll.push_back(thread(Customer));
	}
	Sleep(1000);

	for (int i = 0; i < PRODUCT_SIZE + CUSTOMER_SIZE; ++i)
	{
		threadPoll[i].join();//原始线程等到新线程执行完毕后再销毁
	}
	return 0;
}
