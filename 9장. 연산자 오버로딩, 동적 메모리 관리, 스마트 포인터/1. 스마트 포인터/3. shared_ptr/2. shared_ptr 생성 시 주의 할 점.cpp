#include <iostream>

using namespace std;

class Widget
{
public:
    Widget()  { cout << "Widget::생성자" << endl; }
    ~Widget() { cout << "Widget::소멸자" << endl; }
};

int main(int argc, char* argv[])
{
    Widget* p1 = new Widget;

    // 올바른 사용법
    shared_ptr<Widget> shptr1(p1);
    shared_ptr<Widget> shptr2(shptr1);

    Widget* p2 = new Widget;
    /*
     * 이렇게 생성하면 제어 블록이 따로 생성되고
     * 각각 0이 될 때, Widget 객체를 해제할 것이므로
     * 
     * Widget 객체가 2번 delete 되게 된다.
     */
    shared_ptr<Widget> shptr3(p2);
    shared_ptr<Widget> shptr4(p2);

    return 0;
}
