#include <iostream>
#include <vector>

using namespace std;

/*
 * C 의 typedef 는 템플릿을 지원하지 않는다.
 *
 * template <typename T>
 * typedef vector<T> vectorT;
 */

/*
 * C++ 의 using 은 템플릿을 지원한다.
 */
template <typename T>
using vectorT = vector<T>;

int main(int argc, char* argv[])
{
    vectorT<int> v;

    return 0;
}
