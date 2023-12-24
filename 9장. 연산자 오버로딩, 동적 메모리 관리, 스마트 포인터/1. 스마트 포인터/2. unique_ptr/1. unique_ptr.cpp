#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    /*
     * unique_ptr 도 auto_ptr 과 마찬가지로 소유권을 중요시 하지만,
     * 소유권 이전 방식에 차이점이 있다.
     *
     * 소유권이 있기 때문에
     * shared_ptr 에서의 참조 카운트 같은 건 존재하지 않는다.
     */
    unique_ptr<int> uptr1(new int(5));

    cout << *uptr1 << endl;

    /*
     * 완벽한 전달(Perfect forwarding) 로 인자를 바로 전달해
     *
     * 내부에서 객체를 생성할 수도 있다.
     */
    unique_ptr<int> uptr2 = make_unique<int>(5);

    /*
     * 복사 생성자와 복사 대입 연산자가
     * 삭제(delete 처리) 되어 있기 때문에
     *
     * 컴파일러 선에서 복사는 허용하지 않는다.
     *
     * unique_ptr<int> uptr2(uptr1);
     * uptr2 = uptr1;
     */

     /*
      * 복사는 안 되지만, 소유권 이전은 가능하다.
      * (이동 시맨틱을 이용한다.)
      */
    unique_ptr<int> uptr3(move(uptr2));

    /*
     * 소유권 이전 후에 기존 포인터는
     * 댕글링(nullptr 을 가리키는) 포인터가 되므로
     *
     * 주의해야 한다.
     */
    if (uptr2 == nullptr)
        cout << "이 포인터는 더 이상 소유권이 없습니다." << endl;

    /*
     * 이동 대입 연산자를 통해
     * 다시 소유권을 가져온다.
     */
    uptr2 = move(uptr3);

    if (uptr2)
        cout << *uptr2 << " 다시 소유권을 가져왔습니다." << endl;

    return 0;
}
