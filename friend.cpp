#include <iostream>
using namespace std;

class Car;

// ������Ԫ��Ա��������
class bus
{
public:
    int friend_visit(Car& car); // ��Ԫ��Ա����
};

// ������
class Car
{
    friend int get_num(Car& car); // ȫ�ֺ�������Ԫ����
    friend class taxi; // ��Ԫ��
    friend int bus::friend_visit(Car& car); // ��Ԫ��Ա����
public:
    int c_price;
    Car(int price = 0, int num = 0) :c_price(price), c_num(num)
    {
        cout << "���ù��캯��" << endl;
    }

private:
    int c_num;

};

// ��Ԫ��Ķ���
class taxi
{
public:
    void visit(Car &car);

};


// ��Ԫ��Ա����
int bus::friend_visit(Car& car)
{
    int num = car.c_num;
    return num;
}

// ��Ԫ���еĺ���
void taxi::visit(Car &car)
{
    int num = car.c_num;
    cout << "��������" << num << endl;
} 

// ȫ�ֺ�������Ԫ����
int get_num(Car& car)
{
    int res = car.c_num;
    return res;
}

// ��Ա��������Ԫ����
// ������������һ�����еĳ�Ա����Ϊ��Ԫ����

int main()
{
    taxi t;
    Car car(10, 30);
    bus b;
    int num_b = b.friend_visit(car);
    cout << "bus num��" << num_b << endl;
    t.visit(car);
}