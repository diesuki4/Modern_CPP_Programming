#include <iostream>

using namespace std;

/*
 * lvalue 참조와 rvalue 참조의 어셈블리 분석
 * 
 * 함수 호출에서 const T& 나 T&& 나
 * 스택에 생성된 임시 개체의 참조를 받아오는 것이지,
 * 함수의 스택 프레임 안에 다이렉트로 생성돼 사용되는 것이 아니다.
 * 
 * 호출 규약에 따라 다를 수 있지만,
 * 임시 개체는 해당 구문이 끝나면 소멸한다는 결과는 같다.
 * 
 * const T& 나 T&& 변수에 담은 임시 개체는
 * 변수를 통해 생명 주기가 연장된다.
 *
 * Widget 변수와 Widget&& 변수는 lvalue 로 쓰이는 것은 같지만,
 * 직접 값을 가진다는 점과 참조를 가진다는 점은 다르다.
 */

class Widget
{
    int data;

public:
    Widget(int data) : data(data) { cout << "생성 " << data << endl; }
    Widget(const Widget& rhs) : data(rhs.data) { cout << "복사 " << data << endl; }
    Widget(Widget&& rhs) : data(move(rhs.data)) { cout << "이동 " << data << endl; }
    ~Widget() { cout << "소멸 " << data << endl; }
};

void Func1(Widget num)
{

}

void Func2(const Widget& crnum)
{

}

void Func3(Widget&& rrnum)
{

}

int main(int argc, char* argv[])
{
    // mov       esi, 3
    // lea       edi, [$num]
    // call      Widget::Widget(this, int)
    Widget num(3);

    // lea       eax, [$num]
    // mov       [$rnum], eax
    Widget& rnum = num;

    // mov       esi, 4
    // lea       edi, [$__temp]
    // call      Widget::Widget(this, int)
    // lea       eax, [$__temp]
    // mov       [$crnum], eax
    const Widget& crnum(4);
    Widget&& rrnum(5);

    cout << "ㅡㅡㅡㅡㅡㅡㅡㅡ" << endl;

    // lea       esi, [$num]
    // lea       edi, [$__arg]
    // call      Widget::Widget(this, Widget const&)
    // lea       edi, [$__arg]
    // call      Func1(Widget)
    Func1(num);
    Func1(crnum);
    Func1(rrnum);
    Func1(move(rrnum));
    Func1(6);
    // lea       edi, [$__arg]
    // call      Widget::~Widget(this)

    cout << "ㅡㅡㅡㅡㅡㅡㅡㅡ" << endl;

    // lea       edi, dword ptr [$num]
    // call      Func2(const Widget&)
    Func2(num);
    Func2(crnum);
    Func2(rrnum);
    Func2(move(rrnum));

    // mov       esi, 7
    // lea       edi, [$__temp]
    // call      Widget::Widget(this, int)
    // lea       edi, dword ptr [$__temp]
    // call      Func2(const Widget&)
    Func2(7);
    // lea       edi, [$__temp]
    // call      Widget::~Widget(this)

    cout << "ㅡㅡㅡㅡㅡㅡㅡㅡ" << endl;

    // mov       edi, dword ptr [$rrnum]
    // call      move<Widget&>(Widget&)
    // mov       edi, eax;
    // call      Func3(Widget&&)
    Func3(move(rrnum));

    // mov       esi, 8
    // lea       edi, [$__temp]
    // call      Widget::Widget(this, int)
    // lea       edi, dword ptr [$__temp]
    // call      Func3(Widget&&)
    Func3(8);
    // lea       edi, [$__temp]
    // call      Widget::~Widget(this)

    return 0;
}
