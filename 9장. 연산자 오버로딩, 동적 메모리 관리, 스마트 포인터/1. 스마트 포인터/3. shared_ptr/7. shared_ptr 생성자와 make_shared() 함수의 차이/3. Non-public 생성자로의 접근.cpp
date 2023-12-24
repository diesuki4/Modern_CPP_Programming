/*
 * https://pknam.tistory.com/14
 * https://stackoverflow.com/questions/20895648/difference-in-make-shared-and-normal-shared-ptr-in-c
 */
#include <iostream>

using namespace std;

class Widget
{
    int data;

    Widget(int data) : data(data) { } 

public:
    static shared_ptr<Widget> createNew(int data)
    {
        // make_shared() 함수에서는 Widget 의 private 생성자에 접근 불가
        // return make_shared<Widget>(10);
        return shared_ptr<Widget>(new Widget(10));
    }
};

int main(int argc, char* argv[])
{


    return 0;
}
