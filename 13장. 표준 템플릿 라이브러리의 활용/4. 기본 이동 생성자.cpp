/*
 * https://stackoverflow.com/questions/18290523/is-a-default-move-constructor-equivalent-to-a-member-wise-move-constructor
 * https://stackoverflow.com/questions/4819936/why-is-there-no-default-move-assignment-move-constructor-in-early-drafts-of-the
 */
#include <iostream>

using namespace std;

/*
 * 기본 이동 생성자
 */

class NonMovable
{
    NonMovable(NonMovable&& rhs) = delete;

public:
    NonMovable() { }
    NonMovable(const NonMovable& rhs) = default;
};

class Widget
{
    string name = "Widget";

public:
    /*
     * 기본 이동 생성자
     *
     * Widget(Widget&& rhs) : name(move(rhs.name))
     * {
     * }
     */
    const string& getName() const { return name; }
};

class Button
{
    NonMovable nm;      // 이동 불가능 멤버
    string name = "Button";

public:
    /*
     * 기본 이동 생성자의 추가 조건은
     * 복사 생성자보다 훨씬 까다롭다.
     * 
     * 아래를 모두 만족해야 추가된다.
     * 
     * 1. 이동 생성자를 명시하지 않았다.
     * 2. 이동 대입 연산자를 명시하지 않았다.
     * 3. 복사 생성자를 명시하지 않았다.
     * 4. 복사 대입 연산자를 명시하지 않았다.
     * 5. 소멸자를 명시하지 않았다.
     * 6. 모든 멤버가 이동이 가능해야 한다.
     */
    const string& getName() const { return name; }
};

int main(int argc, char* argv[])
{
    Widget w1;
    Widget w2(move(w1));

    cout << "w1: " << w1.getName() << endl;
    cout << "w2: " << w2.getName() << endl;

    Button b1;
    // 이동 불가 멤버 nm 으로 인해, 기본 이동 생성자가 추가되지 않는다.
    // Button b2(move(b1));
    Button b2(b1);

    return 0;
}
