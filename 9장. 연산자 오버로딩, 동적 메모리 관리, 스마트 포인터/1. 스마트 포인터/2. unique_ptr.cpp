#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    /*
     * unique_ptr 도 auto_ptr 과 마찬가지로 소유권을 중요시 하지만,
     * 
     * 소유권 이전을 금지한다는 차이점이 있다.
     */
    unique_ptr<int> uptr(new int(5));

    cout << *uptr << endl;

    /*
     * 컴파일러 선에서 소유권 이전을 허용하지 않는다.
     * 
     * unique_ptr<int> uptr2(uptr);
     */

    return 0;
}
