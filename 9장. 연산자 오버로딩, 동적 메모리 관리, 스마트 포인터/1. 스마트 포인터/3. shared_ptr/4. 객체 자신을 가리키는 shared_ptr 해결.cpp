#include <iostream>

using namespace std;

// enable_shared_from_this<T> 클래스를 상속한다.
class Widget : public enable_shared_from_this<Widget>
{
public:
    Widget() { cout << "Widget::생성자" << endl; }

    shared_ptr<Widget> get_shared_ptr()
    {
        /*
         * 이미 생성된 제어 블록을 활용해
         * share_ptr 을 생성해 반환한다.
         * 
         * 단, 제어 블록이
         * 이미 생성된(한 번이라도 Raw Pointer 를 통해 share_ptr 이 생성된)
         * 상태여야 정상 작동한다.
         */
        return shared_from_this();
    }

    ~Widget() { cout << "Widget::소멸자" << endl; }
};

int main(int argc, char* argv[])
{
    Widget* p = new Widget;

    /*
     * 현재는 제어 블록이 없기 때문에
     * 정상 동작하지 않는다.
     * 
     * shared_ptr<Widget> shptr1 = p->get_shared_ptr();
     */
    
    shared_ptr<Widget> shptr1(p);
    /*
     * 이제 제어 블록이 존재하므로
     * 정상 동작한다.
     */
    shared_ptr<Widget> shptr2 = shptr1->get_shared_ptr();

    return 0;
}
