/*
 * https://pknam.tistory.com/14
 * https://stackoverflow.com/questions/20895648/difference-in-make-shared-and-normal-shared-ptr-in-c
 */
#include <iostream>

using namespace std;

class Widget { };

// 예외 발생 가능성이 있는 함수
int priority(int num) throw(int)
{
    if (num == 0)
        throw 0;

    return num;
}

void processWidget(shared_ptr<Widget> shptr, int priority)
{
    return;
}

int main(int argc, char* argv[])
{
    /*
     * 다음 순으로 실행되면 메모리 누수 가능성이 존재
     * 
     * 1. new Widget
     * 2. priority(3)
     * 3. shared_ptr 생성자
     * 
     * 2. 에서 예외가 발생하면 Widget 객체가 누수
     */
    processWidget(shared_ptr<Widget>(new Widget), priority(3));

    /*
     * 아래와 같이 해결 가능
     * (C++17 부터는 이렇게 하지 않아도 문제가 없다.)
     */
    Widget* p = new Widget;
    processWidget(shared_ptr<Widget>(p), priority(3));

    /*
     * make_shared() 함수는 내부에서 객체를 생성하므로,
     * 인자의 평가 순서에 따라 발생할 수 있는
     * 
     * 예외 안전성 문제에서 안전하다.
     */
    processWidget(make_shared<Widget>(), priority(3));

    return 0;
}
