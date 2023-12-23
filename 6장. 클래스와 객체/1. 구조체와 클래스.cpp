#include <iostream>

using namespace std;

struct Struct
{
    int age;
    string name;
    float score;
};

class Class
{
    int age;
    string name;
    float score;
};

int main(int argc, char* argv[])
{
    Struct s{15, "김철수", 94.4F};

    /*
     * C++ 에서 구조체와 클래스의 유일한 차이는
     * 
     * 기본 접근 지정자가
     * 구조체는 public, 클래스는 private 이라는 것이다.
     * 
     * 은닉화를 통해 구조체보다는 클래스가
     * 객체지향적 관점에서 캡슐화를 유도하고 있다고 볼 수 있다.
     */
    
    // private 이므로 불가
    // Class c{15, "김철수", 94.4F};

    return 0;
}
