#include <iostream>

using namespace std;

class Widget
{
public:
    Widget() { cout << "Widget::생성자" << endl; }

    shared_ptr<Widget> get_shared_ptr()
    {
        /*
         * 매 호출마다 Raw Pointer 를 통해
         * 새로운 제어 블록이 생성되므로
         * 
         * 해제 시에 문제가 발생한다.
         */
        return shared_ptr<Widget>(this);
    }

    ~Widget() { cout << "Widget::소멸자" << endl; }
};

int main(int argc, char* argv[])
{
    shared_ptr<Widget> shptr1(new Widget);
    shared_ptr<Widget> shptr2 = shptr1->get_shared_ptr();

    return 0;
}
