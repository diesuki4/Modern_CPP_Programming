/*
 * https://stackoverflow.com/questions/49796242/c-move-assignment-prevents-copy-swap-idiom#answer-49796595
 */
#include <iostream>
#include <vector>

using namespace std;

/*
 * Copy & Swap 관용구
 */

class Widget
{
    int i;
    double d;

    void swap(Widget& w)
    {
        using std::swap;

        swap(i, w.i);
        swap(d, w.d);
    }

public:
    Widget(int i, double d) : i(i), d(d)
    {
    }

    Widget(const Widget& rhs) : i(rhs.i), d(rhs.d)
    {
    }
    
    /* 포인터가 아닌 멤버에 대해서는
     * 꼭 이동이 복사보다 빠른 건 아니다. */
    Widget(Widget&& rhs) : i(move(rhs.i)), d(move(rhs.d))
    {
    }

    Widget& operator= (Widget rhs)
    {
        swap(rhs);

        return *this;
    }
};

class WidgetP
{
    int n;
    int* arr;

    /* Copy & Swap 을 위한 private swap() 함수 */
    void swap(WidgetP& wp)
    {
        using std::swap;

        swap(n, wp.n);
        swap(arr, wp.arr);
    }

public:
    WidgetP() : n(0), arr(nullptr)
    {
    }

    WidgetP(vector<int>&& v) : n(v.size()), arr(new int[n])
    {
        for (int i = 0; i < n; ++i)
            arr[i] = v[i];
    }

    WidgetP(const WidgetP& rhs) : n(rhs.n), arr(new int[n])
    {
        for (int i = 0; i < n; ++i)
            arr[i] = rhs.arr[i];
    }

    /* 포인터 멤버에 대해서는
     * 이동이 복사보다 빠르다. */
    WidgetP(WidgetP&& rhs) : n(move(n)), arr(move(rhs.arr))
    {
    }

    /* Copy & Swap 관용구
     *
     * 1. 대입 연산자를 작성할 때 주로 사용된다.
     * 2. 인자로 값 타입을 받으면 lvalue, rvalue 모두에서 동작하게 할 수 있다.
     * 3. 기존 메모리 해제와 new 의 순서에 대한 고려 없이 예외 안전성을 보장한다. */
    WidgetP& operator= (WidgetP rhs)
    {
        swap(rhs);

        return *this;
    }

    /* 값 타입을 인자로 받는 Copy & Swap 으로 구현된 대입 연산자는
     * rvalue 버전을 별도로 작성해 줄 필요가 없다.
     * 
     * rvalue 로 전달되면 알아서 이동 생성자가 호출되므로.
     * 
     * WidgetP& operator= (WidgetP&& rhs); */
    
    ~WidgetP()
    {
        if (0 < n)
        {
            delete[] arr;
            arr = nullptr;
            n = 0;
        }
    }
};

int main(int argc, char* argv[])
{
    

    return 0;
}
