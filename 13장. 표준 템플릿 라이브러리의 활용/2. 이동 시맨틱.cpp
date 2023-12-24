#include <iostream>

using namespace std;

/*
 * 이동 생성자, 이동 대입 연산자 호출을 <이동 시맨틱> 이라고 한다.
 *
 * 이동 시맨틱은 임시 객체, move() 로 감싸진 r-value 레퍼런스가 전달되어
 *
 * 전달된 원본 객체(rhs) 의 값이 더 이상 유지될 필요가 없을 때
 *
 * 얕은 복사로 복사 오버헤드를 줄이기 위해 사용된다.
 */

class Widget
{
    int data;

public:
    Widget(int data) : data(data) { cout << "Widget::생성자 " << data << endl; }

    Widget(const Widget& rhs) : data(rhs.data) { cout << "Widget::복사 생성자 " << data << endl; }

    /*
     * 이동 생성자
     *
     * r-value 레퍼런스가 전달되면 호출된다.
     */
    Widget(Widget&& rhs) : data(rhs.data)
    {
        cout << "Widget::이동 생성자 " << data << endl;

        rhs.data = 0;
    }

    Widget& operator= (const Widget& rhs)
    {
        cout << "Widget::복사 대입 연산자 " << data << " = " << rhs.data << endl;

        data = rhs.data;

        return *this;
    }

    /*
     * 이동 대입 연산자
     *
     * 이동 생성자와 마찬가지로 r-value 레퍼런스가 전달되면 호출된다.
     */
    Widget& operator= (Widget&& rhs)
    {
        cout << "Widget::이동 대입 연산자 " << data << " << " << rhs.data << endl;

        swap(data, rhs.data);

        return *this;
    }

    void show() const { cout << data << endl; }

    ~Widget() { cout << "Widget::소멸자 " << data << endl; }
};

Widget GetWidgetRVO()
{
    // 임시 객체 t(0) 이 반환된다.
    return Widget(0);
}

Widget GetWidgetNRVO()
{
    Widget w(0);

    // 임시 객체 t(w) 가 반환된다.
    return w;
}

int main(int argc, char* argv[])
{
    Widget w1(10);

    // RVO 가 일어난다.
    Widget w2(GetWidgetRVO());

    // 이동 생성자 w3(t) 호출
    Widget w3(GetWidgetNRVO());

    // 복사 생성자 w4(w1) 호출
    Widget w4(w1);

    // 이동 생성자 w5(w1) 호출
    Widget w5(move(w1));

    // 복사 대입 연산자 w4 = w3 호출
    w4 = w3;

    // 이동 대입 연산자 w5 = t 호출
    w5 = GetWidgetRVO();

    return 0;
}
