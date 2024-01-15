#include <iostream>

using namespace std;

/*
 * lvalue, rvalue 를 모두 받는 3가지 방법
 */

// 1. 값으로 받는다.
void CallByValue(int val)
{
    cout << val << endl;
}

// 2. const 참조로 받는다.
void ConstRef(const int& cRef)
{
    cout << cRef << endl;
}

// 3. 전달 참조로 받는다.
template <typename T>
void UniversalRef(T&& t)
{
    cout << t << endl;
}

int main(int argc, char* argv[])
{
    int num = 10;

    CallByValue(num);
    CallByValue(20);

    ConstRef(num);
    ConstRef(20);

    UniversalRef(num);
    UniversalRef(20);

    return 0;
}
