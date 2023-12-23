#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Section
{
    int start;
    int end;
};

int main(int argc, char* argv[])
{
    int num1 = 3;
    int num2 = 30;

    /*
     * 람다(Lambda) 함수
     * 
     * 이름이 없는 익명 함수다.
     * 
     * 값에 의한 캡처는 모두 const 로 처리된다.
     */
    auto func = [/*const*/ num1, &num2]()
    {
        // 불가
        // ++num1;

        ++num2;
    };

    func();

    cout << "num1 = " << num1 << ", num2 = " << num2 << endl;

    /*
     * mutable 키워드를 이용하면
     * 값 타입도 수정이 가능하다.
     */
    [num1, &num2]() mutable
    {
        /*
         * 단, 값 타입이기 때문에
         * 외부 값은 수정되지 않는다.
         */
        ++num1;

        ++num2;
    } /*호출*/();

    cout << "num1 = " << num1 << ", num2 = " << num2 << endl;

    [] { cout << "인자 목록은 필요 없다면, 생략이 가능하다." << endl; }();

    /*
     * 람다 함수의 모든 구성요소를
     * 생략하지 않고 사용하면 다음과 같다.
     */
    auto func2 = [num1](int& num2) mutable throw(int) -> int
    {
        if (num2 == 0)
            throw(num2);

        return ++num1;
    };

    vector<Section> v{
        {3, 5},
        {9, 12},
        {5, 7},
        {1, 8},
        {4, 13},
        {12, 14},
        {2, 8}
    };

    /*
     * 람다 함수는 STL 함수들과 함께 사용할 때
     * 빛을 발한다.
     * 
     * 함수를 정의한 후 함수 포인터를 전달하는 대신
     * 
     * 바로 익명 함수를 만들어 전달할 수 있다.
     */
    sort(v.begin(), v.end(), [](const auto& lhs, const auto& rhs) { return lhs.start < rhs.start; });

    for (Section& sec : v)
        cout << sec.start << " " << sec.end << endl;

    return 0;
}
