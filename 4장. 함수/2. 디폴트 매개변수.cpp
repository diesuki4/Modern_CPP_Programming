#include <iostream>

using namespace std;

/*
 * 디폴트 파라미터는
 * 선언부에 작성한다.
 * 
 * 오른쪽부터 채워야 한다.
 */
void Func(int num1, int num2 = 20, int num3 = 30);

void Func(int num1, int num2, int num3)
{
    cout << num1 << " " << num2 << " " << num3 << endl;
}

int main(int argc, char* argv[])
{
    Func(10);

    return 0;
}
