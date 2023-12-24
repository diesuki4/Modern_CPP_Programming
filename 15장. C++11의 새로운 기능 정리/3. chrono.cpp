#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

int main(int argc, char* argv[])
{
    // 시각을 나타내는 구조체
    system_clock::time_point start;
    system_clock::time_point end;
    
    // 현재 시각 저장
    start = system_clock::now();

    for (int i = 0; i < 100000; ++i)
    {
        int *p = new int;
        delete p;
    }

    // 종료 시각 저장
    end = system_clock::now();

    nanoseconds nanosec = end - start;

    // 실행 시간 출력
    cout << nanosec.count() << endl;

    return 0;
}
