#include <iostream>

using namespace std;

/*
 * l-value 와 r-value 는 left, right 가 아니다.
 * 
 * l-value (locator value)
 * 이름이 부여된 변수다.
 * & 연산자로 주소를 구할 수 있다.
 * 수식이 끝나도 소멸하지 않는다.
 * 
 * r-value
 * 이름이 존재하지 않는 임시 값이다.
 * & 연산자로 주소를 구할 수 없다.
 * 수식이 끝나면 소멸한다.
 * (C++11 부터는 r-value 레퍼런스에 저장해 수명을 늘릴 수 있다.)
 */

class MyInt
{
    int num;

public:
    MyInt(int num) : num(num) { cout << "MyInt::생성자 " << num << endl; }
    MyInt(const MyInt& rhs) : num(rhs.num) { cout << "MyInt::복사 생성자 " << num << endl; }

    // 이미 이름이 있는 객체가 레퍼런스로 반환된다.
    MyInt& operator++ ()
    {
        ++num;

        return *this;
    }

    // 이름이 없는 복사된 임시 객체(사본)가 반환된다.
    MyInt operator++ (int)
    {
        const MyInt pivot(*this);

        ++num;

        return pivot;
    }

    ~MyInt() { cout << "MyInt::소멸자 " << num << endl; }
};

int main(int argc, char* argv[])
{
    MyInt mi1(10);

    /*
     * ++mi 는 l-value 이므로
     * 
     * 복사가 아닌, mi1 의 레퍼런스로 저장된다.
     */
    MyInt& mi2 = ++mi1;

    /*
     * mi++ 은 임시 값이므로 레퍼런스에 저장할 수 없다.
     * 
     * MyInt& mi3 = mi1++;
     */

    /*
     * 임시 값, 임시 객체는
     * 상수 레퍼런스에 저장이 가능하다.
     */
    const MyInt& mi3 = mi1++;

    /*
     * C++11 부터는 r-value 레퍼런스를 통해
     * 
     * 상수 레퍼런스에 저장하지 않고도, 수명 연장이 가능하다.
     */
    MyInt&& mi4 = mi1++;

    return 0;
}
