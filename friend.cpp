#include <iostream>
using namespace std;

class Car;

// 包含友元成员函数的类
class bus
{
public:
    int friend_visit(Car& car); // 友元成员函数
};

// 基础类
class Car
{
    friend int get_num(Car& car); // 全局函数做友元函数
    friend class taxi; // 友元类
    friend int bus::friend_visit(Car& car); // 友元成员函数
public:
    int c_price;
    Car(int price = 0, int num = 0) :c_price(price), c_num(num)
    {
        cout << "调用构造函数" << endl;
    }

private:
    int c_num;

};

// 友元类的定义
class taxi
{
public:
    void visit(Car &car);

};


// 友元成员函数
int bus::friend_visit(Car& car)
{
    int num = car.c_num;
    return num;
}

// 友元类中的函数
void taxi::visit(Car &car)
{
    int num = car.c_num;
    cout << "车数量：" << num << endl;
} 

// 全局函数做友元函数
int get_num(Car& car)
{
    int res = car.c_num;
    return res;
}

// 成员函数做友元函数
// 基类中声明另一个类中的成员函数为友元函数

int main()
{
    taxi t;
    Car car(10, 30);
    bus b;
    int num_b = b.friend_visit(car);
    cout << "bus num：" << num_b << endl;
    t.visit(car);
}