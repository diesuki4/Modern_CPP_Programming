#include <iostream>

using namespace std;

/*
 * auto_ptr 은 C++TR1 부터 존재했지만
 * C++11 부터 사용 중지가 권고되었고, C++17 에서는 제거됐다.
 *
 * unique_ptr 을 사용할 것을 권장한다.
 */

int main(int argc, char* argv[])
{
    // auto_ptr 은 소유권을 중요시 하는 스마트 포인터다.
    auto_ptr<int> aptr1(new int(5));

    /*
     * 소유권이 aptr2 로 이전되었고,
     * aptr1 의 Raw 포인터는 nullptr 을 가리키게 된다.
     */
    auto_ptr<int> aptr2(aptr1);

    cout << *aptr2 << endl;

    // 런타임 에러
    // cout << *aptr1 << endl;

    return 0;
}
