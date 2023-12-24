#include <iostream>

using namespace std;

class Widget
{
public:
    Widget()  { cout << "Widget::생성자" << endl; }
    ~Widget() { cout << "Widget::소멸자" << endl; }
};

/*
 * 인자가 복사 생성 되었으므로 1 증가
 */
void Func(shared_ptr<Widget> shptr)
{
    cout << "[Func] 참조 카운트: " << shptr.use_count() << endl;

    shared_ptr<Widget> shptr2(shptr);
    cout << "[Func] 참조 카운트: " << shptr.use_count() << endl;
}

/*
 * 복사가 일어나지 않았으므로
 * 참조 카운트가 증가하지 않는다.
 */
void FuncRef(shared_ptr<Widget>& shptr)
{
    cout << "[FuncRef] 참조 카운트: " << shptr.use_count() << endl;
}

int main(int argc, char* argv[])
{
    /*
     * 소유권 개념 없이, 여러 곳에서 공유되는 개념이다.
     *
     * 실제 객체를 가리키는 첫 shared_ptr 이 생성될 때
     * 참조 카운트를 관리하는 Control Block 을 함께 동적 할당한 후,
     *
     * 복사(복사 생성, 복사 대입)된 shared_ptr 들이
     * 이 Control Block 을 공유하는 방식으로 구현된다.
     */

    /* shared_ptr 간에 복사가 일어날 때 참조 카운트가 1씩 증가한다.
     *
     * shared_ptr 이 소멸할 때마다 참조 카운트가 1씩 감소하고
     * 
     * 마지막에 0이 되는 녀석이 Raw 포인터 실제 객체를 해제한다.
     */
    shared_ptr<Widget> shptr(new Widget);
    cout << "[main] 참조 카운트: " << shptr.use_count() << endl;

    shared_ptr<Widget> shptr2(shptr);
    cout << "[main] 참조 카운트: " << shptr2.use_count() << endl;

    /*
     * shared_ptr 이 아닌 Raw 포인터를 복사 대입하는 건
     *
     * 참조 카운트를 증가시키지 않는다.
     */
    Widget* ptr = shptr2.get();
    cout << "[main] 참조 카운트: " << shptr.use_count() << endl;

    Func(shptr);
    cout << "[main] 참조 카운트: " << shptr2.use_count() << endl;

    FuncRef(shptr2);
    cout << "[main] 참조 카운트: " << shptr.use_count() << endl;

    return 0;
}
