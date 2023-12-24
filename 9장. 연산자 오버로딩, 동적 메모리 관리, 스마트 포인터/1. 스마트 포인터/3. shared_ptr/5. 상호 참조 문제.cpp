#include <iostream>

using namespace std;

class Widget
{
    shared_ptr<Widget> other;

public:
    Widget() { cout << "Widget::생성자" << endl; }

    void setOther(shared_ptr<Widget>& other)
    {
        // 참조 카운트가 증가한다.
        this->other = other;
    }

    ~Widget() { cout << "Widget::소멸자" << endl; }
};

int main(int argc, char* argv[])
{
    shared_ptr<Widget> shptr1 = make_shared<Widget>();
    shared_ptr<Widget> shptr2 = make_shared<Widget>();

    /*
     * 상호 참조 문제 (Cross-referencing problem)
     *
     * shared_ptr 에서 서로를 참조하게 되면
     * 둘 다 참조 카운트가 1이 되지 못 해
     * 
     * 객체가 소멸되지 않는 문제
     */
    shptr1->setOther(shptr2);
    shptr2->setOther(shptr1);

    cout << shptr1.use_count() << endl;
    cout << shptr2.use_count() << endl;

    return 0;
}
