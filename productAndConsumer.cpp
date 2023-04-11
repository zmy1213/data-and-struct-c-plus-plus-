#include<iostream>
#include<thread>
#include<queue>
#include<string>
#include<type_traits>
#include<mutex>
#include<memory>
#include<random>
#include<chrono>
#include<format>
using namespace std;



template<typename T>
concept always_true = true;

template<always_true T1, always_true T2>
struct MyPro
{
	T1 val;
	T2 name;
};

template<typename T,typename T1,typename T2>
concept Is_Pro = is_same_v<T,MyPro<T1,T2>>;


template<typename T1,typename T2,Is_Pro<T1,T2> T>
class Queue 
{
private:
	mutex m;
	condition_variable c;
	queue<shared_ptr<T>> q;
public:
	void push(T& data)
	{
		lock_guard<mutex> lc(m);
		q.push(make_shared<T>(data));
		c.notify_all();
	}
	shared_ptr<T> pop()
	{
		unique_lock<mutex> lc(m);
		c.wait(lc, [&] {return !q.empty(); });
		auto res = q.front();
		q.pop();
		return res;
	}
	void pro()
	{
		for (int i = 0; i < 100; ++i)
		{
			MyPro<int, string> mp{ i, format("proId:{}", i) };
			cout << "I am a productor ,product a production" << endl;
			cout << mp.name << " " << mp.val << endl;
			push(mp);
		}
	}
	void con()
	{
		int i = 0;
		while (1)
		{
	/*		int ran = rand() % 20;
			auto t = chrono::microseconds(ran);
			this_thread::sleep_for(t);*/
			cout << "I am a consumer ,consume a production" << i++ <<endl;
			auto res = this->pop();
			cout << res->name << " "<<res->val << endl;
		}
	}
};
using Q = Queue<int,string,MyPro<int,string>>;
int main()
{
	srand(time(NULL));
	
	Q q;
	thread t1(&Q::pro,&q);
	thread t2(&Q::con,&q);

	t1.join();
	t2.join();
}
