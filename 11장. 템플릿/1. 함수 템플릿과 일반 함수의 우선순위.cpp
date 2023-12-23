#include <iostream>

using namespace std;

// 3순위. 함수 템플릿
template <typename T>
int add(T& a, T& b)
{
    cout << "add(T&, T&)" << endl;

    return a + b;
}

// 2순위. 템플릿 특수화
template <>
int add<int>(int& a, int& b)
{
    cout << "add<int>(int&, int&)" << endl;

    return a + b;
}

// 1순위. 일반 함수
int add(int& a, int& b)
{
    cout << "add(int&, int&)" << endl;

    return a + b;
}

int main(int argc, char* argv[])
{
    int num1 = 1, num2 = 2;

    cout << add(num1, num2) << endl;

    return 0;
}
