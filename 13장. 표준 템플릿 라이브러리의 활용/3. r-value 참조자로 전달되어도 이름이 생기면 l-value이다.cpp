/*
 * https://modoocode.com/228
 */
#include <iostream>

using namespace std;

class Widget
{
    int data;

public:
    explicit Widget(int data) : data(data)     { cout << "생성자 " << data << endl; }
    Widget(const Widget& rhs) : data(rhs.data) { cout << "복사 생성자 " << data << endl; }
    Widget(Widget&& rhs)      : data(rhs.data) { cout << "이동 생성자 " << data << endl; }
};

class Window1
{
    Widget w;

public:
    // 복사 생성자가 호출되는 게 당연하다.
    Window1(const Widget& rhs) : w(rhs) { }
};

class Window2
{
    Widget w;

public:
    /*
     * 복사 생성자가 호출된다.
     *
     * rhs 가 const Widget& 타입이므로,
     * move(rhs) 의 결과는 const Widget&& 가 된다.
     *
     * 이때 컴파일러는 Widget&& 와 const Widget& 생성자 중에
     * const Widget& 에 더 우선순위를 둔다.
     */
    Window2(const Widget& rhs) : w(move(rhs)) { }
};

class Window3
{
    Widget w;

public:
    /*
     * 복사 생성자가 호출된다.
     *
     * rhs 는 Widget&& 타입이긴 하지만, 현재 Window3 생성자에서
     * rhs 라는 이름을 가지므로,
     *
     * w(rhs) 에는 l-value 로 전달된다.
     *
     */
    Window3(Widget&& rhs) : w(rhs) { }
};

class Window4
{
    Widget w;

public:
    /*
     * 드디어 이동 생성자가 호출된다.
     *
     * 이름이 있는 l-value 인 rhs 를
     * move(rhs) 를 통해 다시 한 번 r-value 로 만들어 줘야 한다.
     */
    Window4(Widget&& rhs) : w(move(rhs)) { }
};

int main(int argc, char* argv[])
{
    Widget w1(1);
    Window1 win1(w1);
    Window1 win11(move(w1));
    Window1 win111(Widget(111));
    cout << endl;

    Widget w2(2);
    Window2 win2(w2);
    Window2 win22(move(w2));
    Window2 win222(Widget(222));
    cout << endl;

    Widget w3(3);
    // Window3 win3(w3);
    Window3 win33(move(w3));
    Window3 win333(Widget(333));
    cout << endl;

    Widget w4(4);
    // Window4 win4(w4);
    Window4 win44(move(w4));
    Window4 win444(Widget(444));
    cout << endl;

    return 0;
}
