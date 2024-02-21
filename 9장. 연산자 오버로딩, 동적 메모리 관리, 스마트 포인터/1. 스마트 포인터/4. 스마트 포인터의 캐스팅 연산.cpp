/*
 * https://en.cppreference.com/w/cpp/memory/shared_ptr/pointer_cast
 */
#include <iostream>

using namespace std;

/*
 * 스마트 포인터의 캐스팅 연산
 */

class Base { public: virtual void f() {} };
class Derived : public Base { public: virtual void f() override {} };

int main(int argc, char* argv[])
{
    shared_ptr<Derived> shDerived;

    shared_ptr<Base> shBase = static_pointer_cast<Base>(shDerived);
    shDerived = dynamic_pointer_cast<Derived>(shBase);
    shBase = const_pointer_cast<Base>(make_shared<const Base>());
    shBase = reinterpret_pointer_cast<Base>(make_shared<int>());

    return 0;
}
