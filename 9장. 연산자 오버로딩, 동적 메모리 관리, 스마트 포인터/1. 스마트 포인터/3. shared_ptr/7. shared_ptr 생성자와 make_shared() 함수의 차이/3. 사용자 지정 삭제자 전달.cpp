/*
 * https://pknam.tistory.com/14
 * https://stackoverflow.com/questions/20895648/difference-in-make-shared-and-normal-shared-ptr-in-c
 */
#include <iostream>
#include <mutex>

using namespace std;

void unlock(mutex* pm)
{
    pm->unlock();

    cout << "자원이 해제되었습니다." << endl;
}

int main(int argc, char* argv[])
{
    mutex mtx;

    mtx.lock();
    shared_ptr<mutex> shptr1(&mtx, unlock);

    /*
     * make_shared() 함수는
     * 사용자 지정 삭제자(deleter) 를 전달할 수 없다.
     */
    shared_ptr<mutex> shptr2 = make_shared<mutex>();

    return 0;
}
