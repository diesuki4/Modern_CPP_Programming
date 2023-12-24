#include <iostream>

using namespace std;

/*
 * 입력으로
 *
 * 이름이 부여된 l-value 가 오든
 * 이름이 없는 임시 r-value 가 오든
 *
 * 모두 T&& 타입의 r-value 레퍼런스로 반환한다.
 *
 * 형 변환만 진행할 뿐,
 * 어떤 동작이나 별도 메모리를 할당하지 않는다.
 *
 * 이동 생성자, 이동 대입 연산자를 통해
 * 복사 오버헤드를 감소시킬 때 사용된다.
 *
 * l-value t 혹은 임시 r-value t 에 대해,
 * move(t) 호출 이후에는 t 의 값은 보장받지 못한다.
 */

class Widget
{
    string s;
    int data;

public:
    Widget(const char* s, int data) : s(s), data(data) { }

    void show() { cout << "s = " << s << ", data = " << data << endl; }
};

int main(int argc, char* argv[])
{
    string s1("String1");
    string s2("String2");

    /*
     * 이동 대입 연산자에 의해
     * s2 의 멤버들이 s1 으로 이동(얕은 복사) 된다.
     */
    s1 = move(s2);

    /*
     * 이동 이후 원본 객체 s2 의 값은
     * 보장받지 못 한다.
     */
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl << endl;

    Widget w1("String1", 1);
    Widget w2("String2", 2);

    /*
     * 컴파일러는 기본 이동 생성자, 기본 이동 대입 연산자를 만든다.
     *
     * 따라서, Widget 의 기본 이동 대입 연산자에 의해
     * 각 멤버 또한 이동 대입된다.
     */
    w1 = move(w2);

    /*
     * string 멤버는 이동되었지만, int 멤버는 복사되었다.
     *
     * 이건 move() 함수나 자료형 때문이 아니다.
     *
     * move() 함수는 r-value 래퍼런스로 형 변환만 할 뿐
     * 이외 어떤 동작도 하지 않는다.
     *
     * 복사 대입 연산자와 마찬가지로, 각 멤버마다 이동 대입이 일어난 결과일 뿐이다.
     */
    w1.show();
    w2.show();

    return 0;
}
