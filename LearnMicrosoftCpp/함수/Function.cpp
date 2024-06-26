/*
함수는 일부 작업을 수행하는 코드 블록입니다. 함수는 호출자가 함수에 인수를 전달할 수 있도록 하는
입력 매개 변수를 필요에 따라 정의할 수 있습니다. 함수는 필요에 따라 출력으로 값을 반환할 수 있습니다.
함수는 이상적으로 함수의 기능을 명확하게 설명하는 이름을 사용하여 재사용 가능한 단일 블록에서 일반 작업을
캡슐화하는 데 유용합니다. 다음 함수는 호출자에서 두 개의 정수를 허용하고 해당 합계를
반환합니다. a 및 b는 형식 int의 매개 변수입니다.
*/

int Sum(int a, int b)
{
    return a + b;
}

/*
함수는 프로그램의 여러 위치에서 호출하거나 호출할 수 있습니다.
함수에 전달되는 값은 함수 정의의 매개 변수 형식과 호환되어야 하는 인수입니다.
*/
#include <iostream>
int main()
{
    int j = Sum(10, 32);
    int i = Sum(j, 66);
    std::cout << "The value of j is" << i << std::endl;
}

/*
함수 길이에 대한 실질적인 제한은 없지만 잘 정의된 단일 작업을 수행하는 함수를 위한 좋은 디자인이 목표입니다.
복잡한 알고리즘은 가능하면 이해하기 쉬운 더 간단한 함수로 세분화해야 합니다.

클래스 범위에서 정의되는 함수는 맴버 함수라고 합니다. 다른 언어와 달리 C++에서는
네임스페이스 범위에서 함수를 정의할 수도 있습니다. 이러한 함수는 자유 함수 또는 비 맴버 함수
라고 하며 표준 라이브러리에서 광범위하게 사용됩니다.
*/