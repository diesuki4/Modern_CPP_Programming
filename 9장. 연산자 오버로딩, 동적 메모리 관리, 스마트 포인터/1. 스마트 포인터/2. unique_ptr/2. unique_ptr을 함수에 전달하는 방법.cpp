#include <iostream>

using namespace std;

// 복사가 안 되니 레퍼런스로 전달하면?
void FuncWrong(unique_ptr<int>& uptr)
{
    // 유일한 소유권이라는 원칙이 깨져버렸다.
    cout << *uptr << endl;
}

// 그냥 Raw Pointer 를 전달하는 게 옳다.
void FuncRight(int *p)
{
    cout << *p << endl;
}

int main(int argc, char* argv[])
{
    unique_ptr<int> uptr(new int(5));

    // 나쁜 방법
    FuncWrong(uptr);

    // 좋은 방법
    FuncRight(uptr.get());

    return 0;
}
