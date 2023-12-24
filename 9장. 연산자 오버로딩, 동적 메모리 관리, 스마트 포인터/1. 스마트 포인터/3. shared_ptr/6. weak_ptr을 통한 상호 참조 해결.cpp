#include <iostream>

using namespace std;

class Widget
{
    int data;
    int otherData;
    // shared_ptr 대신 weak_ptr 로 선언
    weak_ptr<Widget> other;

public:
    Widget(int data) : data(data) { cout << "Widget::생성자 " << data << endl; }

    void setOther(shared_ptr<Widget>& other)
    {
        // 참조 카운트가 증가하지 않는다.
        // shared_ptr => weak_ptr 암시적 형 변환
        this->other = other;
        this->otherData = other->data;
    }

    void useOther()
    {
        /*
         * weak_ptr 은 사용하기 전에 꼭 유효성을 확인해야 하며,
         * 
         * lock() 함수를 통해 shared_ptr 로 변환해야만 사용 가능하다.
         */
        shared_ptr<Widget> shptr = other.lock();

        // shared_ptr => bool 암시적 형 변환
        if (shptr)
            cout << otherData << " 가 아직 살아 있습니다." << endl;
        else
            cout << otherData << " 는 이미 소멸했습니다." << endl;
    }

    ~Widget() { cout << "Widget::소멸자 " << data << endl; }
};

int main(int argc, char* argv[])
{
    shared_ptr<Widget> shptr1 = make_shared<Widget>(1);
    shared_ptr<Widget> shptr2 = make_shared<Widget>(2);

    shptr1->setOther(shptr2);
    shptr2->setOther(shptr1);

    cout << shptr1.use_count() << endl;
    cout << shptr2.use_count() << endl;

    shared_ptr<Widget> shptr3 = make_shared<Widget>(3);

    {
        shared_ptr<Widget> shptr4 = make_shared<Widget>(4);

        shptr3->setOther(shptr4);
        shptr3->useOther();
    }

    shptr3->useOther();

    /*
     * weak_ptr 은 이미 존재하는 제어 블록을 통해 관리되므로,
     * Raw Pointer 로는 생성할 수 없다.
     * 
     * weak_ptr<Widget> wkptr(new Widget(0));
     */
    weak_ptr<Widget> wkptr;

    {
        // shptr5 를 통해 제어 블록이 생성
        shared_ptr<Widget> shptr5 = make_shared<Widget>(5);

        // wkptr 이 shptr5 의 제어 블록을 활용
        wkptr = shptr5;
        cout << "wkptr.use_count(): " << wkptr.use_count() << endl;
    }

    /*
     * 현재 shptr5 와 Widget(5) 객체는 소멸했지만,
     * 힙에 할당된 제어 블록은 아직 소멸하지 않았다.
     * 
     * 제어 블록은 Reference count 와 함께 Weak count 도 관리한다.
     * 
     * 실제 객체는 Reference count 가 0이 될 때 소멸하지만,
     * 제어 블록은 Reference count 와 Weak count 모두 0이 될 때 소멸한다.
     */
    cout << "shptr5 의 제어 블록은 소멸되지 않았습니다." << endl;
    cout << "wkptr.use_count(): " << wkptr.use_count() << endl;

    /*
     * 그 이유는 실제 객체가 소멸할 때 제어 블록까지 해제해 버리면
     * 
     * weak_ptr 에서는 실제 객체가 살아있는지 아닌지
     * 알 방법이 없기 때문이다.
     */
    if (wkptr.lock())
        cout << "Widget(5) 가 아직 살아 있습니다." << endl;
    else
        cout << "Widget(5) 는 이미 소멸했습니다." << endl;

    return 0;
}
