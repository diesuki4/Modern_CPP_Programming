/*
 * https://modoocode.com/228
 */
#include <iostream>

using namespace std;

class Widget
{
    int data;

public:
    explicit Widget(int data) : data(data)           { cout <<   "생성자 "    << data << endl; }
    Widget(const Widget& rhs) : data(rhs.data)       { cout << "이동 생성자 " << data << endl; }
    Widget(Widget&& rhs)      : data(move(rhs.data)) { cout << "복사 생성자 " << data << endl; }
    ~Widget()                                        { cout <<   "소멸자 "    << data << endl; }
};

void Func(Widget& w)       { cout << "lvalue 레퍼런스" << endl; }
void Func(const Widget& w) { cout << "lvalue 상수 레퍼런스" << endl; }
void Func(Widget&& w)      { cout << "rvalue 레퍼런스" << endl; }

template <typename T>
void Wrapper1(T u)
{
    Func(u);
}

template <typename T>
void Wrapper2(T& u)
{
    Func(u);
}

template <typename T>
void Wrapper3(T&& u)
{
    // rvalue 로 전달되어도, 여기서는 이름을 가지므로 lvalue 다.
    Func(u);
}

/*
 * forward() 가 있으면, move() 는 사실상 필요가 없다.
 *
 * 하지만, 의미상 명확하게 하기 위해
 * 이동 시맨틱을 요청하는 상황에서는 move() 를 쓴다.
 */
template <typename T>
void Wrapper4(T&& u)
{
    // 모두 rvalue 로 전달한다.
    // const 객체의 이동 요청은 복사로 처리된다.
    Func(move(u));
}

/*
 * forwad() 는 전달 참조(보편 참조) 에서 사용한다.
 *
 * 전달 참조를 이용한 가변 인자 템플릿에서의
 * Perfect forwarding 등에 사용된다.
 */
template <typename T>
void Wrapper5(T&& u)
{
    // lvalue 는 lvalue 로, rvalue 는 rvalue 로 완벽 전달한다.
    Func(forward<T>(u));
}

int main(int argc, char* argv[])
{
    Widget w(1);
    const Widget cw(2);

    Func(w);
    Func(cw);
    Func(Widget(3));   // 임시 객체는 이 구문이 끝나면 소멸한다.
    cout << endl;

    Wrapper1(w);
    Wrapper1(cw);
    Wrapper1(Widget(4));
    cout << endl;

    Wrapper2(w);
    Wrapper2(cw);
    // Wrapper2(Widget(5));
    cout << endl;

    Wrapper3(w);
    Wrapper3(cw);
    Wrapper3(Widget(6));
    cout << endl;

    Wrapper4(w);
    Wrapper4(cw);
    Wrapper4(Widget(7));
    cout << endl;

    Wrapper5(w);
    Wrapper5(cw);
    Wrapper5(Widget(8));
    cout << endl;

    return 0;
}
