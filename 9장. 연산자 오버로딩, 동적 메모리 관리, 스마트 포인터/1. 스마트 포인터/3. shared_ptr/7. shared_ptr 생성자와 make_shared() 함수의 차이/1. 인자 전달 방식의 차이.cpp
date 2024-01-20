/*
 * https://pknam.tistory.com/14
 * https://stackoverflow.com/questions/20895648/difference-in-make-shared-and-normal-shared-ptr-in-c
 */
#include <iostream>

using namespace std;

class Widget
{
    int data;

public:
    Widget(int data) : data(data) { }
};

int main(int argc, char* argv[])
{
    // shared_ptr 생성자는 이미 생성된 메모리 주소를 받는 반면,
    shared_ptr<Widget> shptr1(new Widget(5));
    
    // make_shared() 함수는 Perfect Forwarding 을 통해 내부에서 자원을 생성한다.
    shared_ptr<Widget> shptr2 = make_shared<Widget>(10);

    return 0;
}
