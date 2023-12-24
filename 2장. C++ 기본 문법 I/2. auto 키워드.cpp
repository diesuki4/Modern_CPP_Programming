#include <iostream>
#include <vector>

using namespace std;

/*
 * auto 키워드는 컴파일러가 자동으로 자료형을 지정하는 대신,
 *
 * 초깃값이 꼭 필요하다.
 */

void print(vector<int>& v)
{
    // 반복자 때문에 보기가 지저분하다.
    for (vector<int>::iterator it = v.begin(); it != v.end(); ++it)
        cout << *it << " ";
    cout << endl;
}

// 함수의 반환 형에도 auto 를 쓸 수 있다.
auto getNum()
{
    return 5;
}

int main(int argc, char* argv[])
{
    vector<int> v{0, 1, 2, 3, 4, 5};

    // 함수도 담을 수 있다.
    auto func = print;

    print(v);

    // 람다 함수를 담을 때 엄청 유용하게 쓰인다.
    auto func2 = [](vector<int>& v) /*-> void*/
    {
        // 반복자 사용 시에도 유용하게 쓰인다.
        for (auto it = v.begin(); it != v.end(); ++it)
            cout << *it << " ";
        cout << endl;
    };

    func2(v);

    /*
     * 범위 기반 for 문에서 & 를 붙여주지 않으면
     * 값으로 가져와진다.
     */
    for (auto e : v)
        e = 0;

    print(v);

    /*
     * & 를 붙여주어야
     * 레퍼런스로 가져와진다.
     */
    for (auto& e : v)
        e = 0;

    print(v);

    auto str = "Hello World !!";
    auto d = 1.0;
    auto f = 3.F;
    auto c = 'c';
    auto i1 = 3, i2 = 30;

    // 다음과 같이 타입을 알 수 있다.
    cout << typeid(str).name() << endl;
    cout << typeid(d).name() << endl;
    cout << typeid(f).name() << endl;
    cout << typeid(c).name() << endl << endl;
    cout << typeid(i1).name() << endl;
    cout << typeid(i2).name() << endl;
    cout << boolalpha << (typeid(i1) == typeid(i2)) << endl;
    cout << boolalpha << (typeid(d) == typeid(f)) << endl;

    return 0;
}
