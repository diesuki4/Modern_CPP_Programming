#include <iostream>

using namespace std;

/*
 * inline 키워드는 선언부에 작성한다.
 * 
 * 컴파일러에게 알릴 뿐, 무조건 inline 처리해 주는 것은 아니다.
 */
inline int inlineSquare(int num);
int square(int num);

/*
 * $num    = dword ptr [ebp + 8]
 * $result = dword ptr [ebp - 4]
 * 
 * 함수 프롤로그
 * push    ebp
 * mov     ebp, esp
 * 
 * int result = num * num;
 * mov     eax, $num
 * imul    eax, eax
 * mov     $result, eax
 * 
 * 반환 값 저장
 * mov     eax, $result
 * 
 * 함수 에필로그 (return;)
 * leave  (mov esp, ebp;   pop ebp;)
 * ret    (pop eip;        jmp eip;)
 */
int inlineSquare(int num)
{
    int result = num * num;

    return result;
}

int square(int num)
{
    int result = num * num;

    return result;
}

int main(int argc, char* argv[])
{
    // $num = dword ptr [ebp - 4]

    /*
     * 값 준비
     * mov     eax, 5
     * 
     * 계산
     * imul    eax, eax
     * 
     * 결과 저장
     * mov     $num, eax
     */
    int num = inlineSquare(5);

    /*
     * 인자 전달
     * push    5
     * 
     * 함수 호출
     * call    int square(int)
     * 
     * 인자 정리
     * add     esp, 4
     * 
     * 반환 값 가져오기
     * mov     $num, eax
     */
    num = square(5);

    return 0;
}
