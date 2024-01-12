#include <iostream>

using namespace std;

/*
 * 속성 지정자 (Attribute specifier)
 *
 * 함수, 변수, typedef 선언에 속성을 추가할 수 있다.
 */

// 반환 값을 반드시 받아야 한다. (Warning)
[[nodiscard]]
int getNum() { return 5; }

// 쓰이지 않는 함수다. (Error)
[[deprecated]]
void doNotUse() { return; }

// Error
[[deprecated]]
typedef string OldType;

int main(int argc, char* argv[])
{
    // Warning
    getNum();

    // 불가
    // doNotUse();

    // 불가
    // OldType ot;

    return 0;
}
