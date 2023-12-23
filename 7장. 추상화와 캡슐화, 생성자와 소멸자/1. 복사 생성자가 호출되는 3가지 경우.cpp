#include <iostream>

using namespace std;

class Widget
{
    int data;

public:
    Widget(int data) : data(data)
    {

    }

    Widget(const Widget& rhs) : data(rhs.data)
    {
        cout << "Widget::복사 생성자" << endl;
    }
};

// 1. 객체가 함수에 값 타입으로 전달될 때
// w(전달 객체)
Widget Func(Widget w)
{
    // 2. 객체가 값 타입으로 반환될 때
    // 임시 객체 t(w)
    //
    // RVO 가 수행되면, 임시 객체가 생략될 수 있다.
    return w;
}

int main(int argc, char* argv[])
{
    Widget w1(5);

    // 3. 기존 객체로 새로운 객체를 만들 때
    Widget w2(w1);

    Func(w1);

    return 0;
}
