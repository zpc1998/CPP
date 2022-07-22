#include <iostream>
using namespace std;
#pragma warning(suppress : 4996) // 防止strcpy()警告

class Car
{
    int c_price; // 价格
    char* c_name;
public:
    // 普通构造函数
    Car(int price=0, char *name=NULL) :c_price(price)
    {
        // 调用构造函数
        cout << "调用构造函数" << endl;
        // 申请新的堆空间，用于存放拷贝的栈空间内容
        c_name = new char[sizeof(name)]();	//加个括号，将内存空间全部初始化为0
        // 拷贝字符串的数据到新的内存空间,专门的API
        strcpy(c_name, name);	//将name地址指向的内存空间拷贝给m_name地址指向的内存空间

        cout << "Car():c_price(price), c_length(length)" << endl;
    }
    // 拷贝构造函数
    // 自定义拷贝构造函数，需要自己完成成员的赋值
    // 默认构造函数时浅拷贝构造函数，对于指针变量的拷贝，浅拷贝只会传递指针变量的地址值，不会传递所指向的内容
    Car(const Car& car)
    {
        cout << "调用拷贝构造函数" << endl;
        this->c_price = car.c_price;
        // 申请新的堆空间，存放拷贝的栈空间内容
        this->c_name = new char(sizeof(car.c_name));
        strcpy(this->c_name, car.c_name);
        cout << "Car():(const Car &car)" << endl;
    }
    // 展示
    void display()
    {
        cout << "car price：" << c_price << endl << "car name：" << c_name << endl;
    }
    // 修改指针变量的值
    void reset_name( )
    {
        c_name[0] = 'a';
    }
};
int main()
{
    char name[] = { 'b','e','n','z','\0' };

    Car* car = new Car(100, name);
    Car* car1 = new Car(*car);
    
    car->reset_name();
    
    car1->display();
    car->display();
    return 0;
}
