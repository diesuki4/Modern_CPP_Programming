#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main(int argc, char* argv[])
{
    vector<int> v{0, 1, 2, 3, 4, 5};

    // 범위 기반 for문
    for (auto& e : v)
        cout << e << " ";
    cout << endl;

    set<int> st{4, 1, 3, 0, 5, 2};

    // 범위 기반 for문
    for (int e : st)
        cout << e << " ";
    cout << endl;

    return 0;
}
