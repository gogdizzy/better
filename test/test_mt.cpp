//
// Created by 关鑫 on 2018/6/4.
//

#include <stdio.h>
#include <deque>
#include <map>
#include <list>
#include <thread>
#include <atomic>
#include <memory>
#include <unordered_map>
#include <vector>
#include <bitset>
#include <boost/thread/detail/singleton.hpp>
#include <boost/container/detail/singleton.hpp>
#include <boost/serialization/singleton.hpp>
#include <boost/pool/singleton_pool.hpp>
#include <boost/lockfree/stack.hpp>


//int main() {
//    uint32_t x = std::thread::hardware_concurrency();
//    printf( "hardware_concurrency = %u\n", x );
//    return 0;
//}

#include <iostream>


using namespace std;
//建一个Test类
class Test
{
public:
    Test()
    {
        a = 0;
        b = 0;
        cout << "无参构造函数被调用了" << endl;
    }
    Test(int aa, int bb)
    {
        a = aa;
        b = bb;
        cout << "有参构造函数被调用了" << endl;
    }
    Test(const Test& t)
    {
        a = t.a;
        b = t.b;
        cout << "复制构造函数被调用了" << endl;
    }
    void print()
    {
        cout << "a:" << a << endl << "b:" << b << endl;
    }
    ~Test()
    {
        cout << "析构函数被调用了" << endl;
    }
private:
    int a;
    int b;
};

//以下为几个方便说明的操作函数
Test g()
{
    Test tt(11, 22);
    return tt;
}
void play1()
{
    g();
}
void play2()
{
    Test t1 = g();
    t1.print();
}
void play3()
{
    Test t2(3,4);
    t2.print();
    t2 = g();
    t2.print();
}

//主函数
int main() {
    // play3();
    std::vector< int > vi;
    cout << vi.max_size();
    return 0;
}