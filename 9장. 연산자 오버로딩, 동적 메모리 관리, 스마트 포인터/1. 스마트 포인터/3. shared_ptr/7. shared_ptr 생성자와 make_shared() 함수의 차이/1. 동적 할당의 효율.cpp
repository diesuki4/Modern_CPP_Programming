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
    /*
     * 생성할 때 동적 할당된 포인터를 전달한다.
     *
     * Widget 객체를 생성할 때 1번, Control Block 을 생성할 때 1번
     *
     * 총 2번의 Heap allocation, 2번의 deallocation 이 발생한다.
     */
    shared_ptr<Widget> shptr1(new Widget(5));

    /*
     * 완벽한 전달(Perfect forwarding) 로 인자만 바로 전달한다.
     *
     * Widget 객체, Control Block 을 하나의 메모리 블록으로 할당해
     *
     * Heap allocation, deallocation 을 1번씩으로 줄일 수 있는
     * 성능상 이점이 있다.
     *
     * Reference count, Weak count 가 모두 1이 되어야 해제되는
     * Control Block 의 특성 때문에
     *
     * Weak count 로 인해, Reference count 는 0이 되었음에도
     * 하나로 묶인 Widget 객체까지 함께 소멸하지 못하는 문제가 발생할 수 있다.
     */
    shared_ptr<Widget> shptr2 = make_shared<Widget>(10);

    return 0;
}
