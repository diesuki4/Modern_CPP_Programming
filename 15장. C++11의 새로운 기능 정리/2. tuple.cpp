#include <iostream>
#include <tuple>

using namespace std;

/*
 * 기존에는 함수에서 2개 이상의
 * 타입을 가진 값을 반환하려면
 * 
 * 별도 구조체를 정의해야 했다.
 */
struct Struct
{
    int i;
    string s;
    float f;
};

Struct GetValues()
{
    Struct st;

    st = {10, "Hello World !!", 5.3F};

    return st;
}

/*
 * 튜플은 이를 쉽게 대체할 수 있다.
 */
auto GetValuesTuple()
{
    tuple<int, string, float> tp;

    tp = {10, "Hello World !!", 5.3F};

    return tp;
}

int main(int argc, char* argv[])
{
    tuple<int, string, float> tp1 = GetValuesTuple();

    // 인덱스로 i번째 원소에 접근
    cout << get<0>(tp1) << endl;
    cout << get<1>(tp1) << endl;
    cout << get<2>(tp1) << endl;

    int i = 1;
    string s = "I'm String !!";
    float f = 0.2F;

    // make_tuple() 함수로도 튜플을 만들 수 있다.
    auto tp2 = make_tuple(i, s, f);

    // 튜플끼리 값 교환도 가능하다.
    swap(tp1, tp2);

    // tp2 의 값이 순서대로 i, s, f 에 저장된다.
    tie(i, s, f) = tp1;

    cout << i << endl;
    cout << s << endl;
    cout << f << endl;

    return 0;
}
