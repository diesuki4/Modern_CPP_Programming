#include <iostream>

using namespace std;

int getNum()
{
    return 5;
}

int main(int argc, char* argv[])
{
    double d;

    // int
    decltype(getNum()) iNum;
    
    /*
     * 타입을 정해주는 것이지
     * 값까지 할당해주지는 않는다.
     * 
     * cout << iNum << endl;
     */

    // double
    decltype(d) d2;

    /*
     * double&
     * 
     * (()) 는 레퍼런스로만 정의할 수 있다.
     * 따라서 초기화가 필요하다.
     */
    decltype((d)) rd = d2;

    return 0;
}
