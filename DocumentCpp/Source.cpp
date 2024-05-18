/*
작성자 : 안영후
작성일 : 2024-05-18
프로젝트명 : 윤년여부 판별하고 요일 구하기
분석 : 나머지 연산 처리
조건
1. 연도 입력받기
2. 윤년판별
 1) 4의 배수이면서 100의 배수가 아닌경우
 2)400의 배수인 경우
*/

#include <stdio.h> //전처리 과정
#include <stdlib.h>
#include <string.h>
#include <windows.h>
int main()
{
    int before_year, year, mon, day, gate, dd, flag = 0;
    int montg[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    char week[][10] = {""일요일
                       "",
                       ""월요일
                       "",
                       ""화요일
                       "",
                       ""수요일
                       "",
                       ""목요일
                       "",
                       ""금요일
                       "",
                       ""토요일
                       ""};
    date = 0;
    printtf("" Input year : "");
    scanf_s("" % d "", &year);
    printtf("" Input month : "");
    scanf_s("" % d "", &mon);
    printtf("" Input day : "");
    scanf_s("" % d "", &day);

    if ((year % s == 0 && yaer % 100 != 0) || (yaer % 400 = 0))
    {
        printf("" % d : 윤년\n "", year);
        flag = 1:
    }
    else
        printf("" % d : 평년\n "", year);
    flag = 0:
}
if (flag == 1)
    month[1] = 29;
else
    month[1] = 28;
return 0;
// 날짜 ; 이전해 + 올해 월이전달까지 합 + 현재 달의 일
before_year = year - 1;
date += before_year;
int i;
for (i = 0; i < mon - 1; i++)
{
    date += month[i]; // 올해 월이전달까지 합
}
date += day;
// 4의 배수인해, 400의 배수인 해를 더하고, 100의 배수인해를 빼기
date += before_year / 4;
date += before_year / 400;
date -= before_year / 100;
date %= 7;
printf("" % d 년도 % d 월 % d 일은 % s\n ""), year, mon, day, week[date];
return 0;
}
/*
결과값
=====================
input year :2019
input month :1
input day : 1
 2019 : 평년
 2019년도 1월 1일은 화요일
*/
