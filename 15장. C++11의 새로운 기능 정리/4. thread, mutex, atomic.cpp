#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex mtx;

int num;
int cs_num;
// 동기화 없이, Thead-safe 한 변수
atomic<int> atomic_num;

void lock(mutex* p)   { p->lock(); }
void unlock(mutex* p) { p->unlock(); }

/*
 * 자원 관리 객체의 모든 부분이 구현된 것이 아니다.
 * 
 * 대표적으로 복사 등에 대한 고려가 빠져있다.
 */
class ResourceManager
{
    shared_ptr<mutex> shptr;

public:
    explicit ResourceManager(mutex* pm)
    // 자원 관리 객체가 소멸할 때, 락을 해제한다.
    : shptr(pm, unlock)
    {
        // 자원 관리 객체가 생성될 때 락을 건다.
        lock(shptr.get());
    }
};

void thread_func(int tid)
{
    // Thread-unsafe
    for (int i = 0; i < 10000; ++i) ++num;

    // Thread-safe
    // 대신, 비용이 높다.
    for (int i = 0; i < 10000; ++i) ++atomic_num;

    // Critical Section
    {
        ResourceManager rm(&mtx);
        cout << "스레드 번호: " << tid << " 실행" << endl;

        for (int i = 0; i < 10000; ++i) ++cs_num;

        // Scope 가 끝날 때 자원 관리 객체를 통해
        // 락을 해제
    }
}

int main(int argc, char* argv[])
{
    thread t[50];

    for (int i = 0; i < 50; ++i)
        // thread_func(i) 를 실행하는 스레드 생성
        t[i] = thread(thread_func, i);

    for (int i = 0; i < 50; ++i)
        // i번째 스레드가 종료될 때까지 대기
        t[i].join();

    cout << "num: " << num << endl;
    cout << "cs_num: " << cs_num << endl;
    cout << "atomic_num: " << atomic_num << endl;

    return 0;
}
