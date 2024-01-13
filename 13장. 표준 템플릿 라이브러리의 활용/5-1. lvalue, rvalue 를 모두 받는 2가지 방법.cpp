#include <iostream>

using namespace std;

/*
 * lvalue, rvalue 를 모두 받는 2가지 방법
 */

// 1. const 참조로 받는다.
void ConstRef(const int& val)
{
    cout << val << endl;
}

// 2. 전달 참조로 받는다.
template <typename T>
void UniversalRef(T&& t)
{
    cout << t << endl;
}

int main(int argc, char* argv[])
{
    int num = 10;

    ConstRef(num);
    ConstRef(20);

    UniversalRef(num);
    UniversalRef(20);

    return 0;
}
