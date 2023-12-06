#include <stdio.h>

#define Max_Line 5

int Week[32];
char Schedule[32][Max_Line][1024];      //스케줄의 내용을 입력받기 위한 배열 
int Check_Schedule[32] = { 0, };         //스케줄 입력 체크 배열을 전부 0으로 초기화 
int week, lastday, YEAR, MONTH;

void Draw_Calendar();
void Input_Schedule();
void View_Schedule();

int main(void)
{
    int op, i;
    int year, month, th;
    int num[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };   //1년 각 월의 일수를 저장 

    printf("해당년을 입력하시오 : ");      //연도를 입력받는다. 
    scanf("%d", &year);
    YEAR = year;

    printf("해당 월을 입력하시오 : ");
    scanf("%d", &month);         //달을 입력받는다. 
    MONTH = month;

    // 입력된 달의 마지막 날짜를 구한다
    lastday = num[month - 1];

    // 만약 윤년이면 마지막 날자를 29일로 설정한다
    if (month == 2 && (!(year % 4) && (year % 100) || !(year % 400))) lastday = 29;

    // 1월 이나 2월이면 전년의 13월 이나 14월로 본다
    if (month == 2 || month == 1)
    {
        year--;
        month += 12;
    }

    // 년도를 앞의 두자리와 뒤의 두자리로 나눈다
    th = year / 100;
    year = year % 100;

    // 해당 월 1일의 요일 구하는 공식
    week = ((21 * th / 4) + (5 * year / 4) + (26 * (month + 1)) / 10) % 7;

    for (i = 1; i <= lastday; i++)
    {
        Week[i] = (week + i - 1) % 7;
    }

    while (1)
    {
        Draw_Calendar();         //달력 그리는 함수를 호출한다. (달력 출력) 

        printf("\n** M E N U **\n");
        printf("1. 스케쥴 입력\n");
        printf("2. 스케쥴 보기\n");
        printf("3. 끝내기\n");
        printf("In : ");
        fflush(stdin);         //전 단계에서 입력 스트림에 남은 데이터를 비운다. 
        scanf("%d", &op);         //메뉴 이동 

        switch (op)
        {
        case 1: Input_Schedule(); break;   //내용 입력 함수 
        case 2: View_Schedule(); break;   //내용 출력 함수 
        case 3: exit(1);
        }
    }
    return 0;
}

void Print_Month()                  //달을 출력하는 함수 
{
    printf("\n\t\t\t             ");
    switch (MONTH)
    {
    case  1: printf("January\n"); break;
    case  2: printf("Feburay\n"); break;
    case  3: printf("March\n"); break;
    case  4: printf("Aprill\n"); break;
    case  5: printf("May\n"); break;
    case  6: printf("June\n"); break;
    case  7: printf("July\n"); break;
    case  8: printf("August\n"); break;
    case  9: printf("September\n"); break;
    case 10: printf("October\n"); break;
    case 11: printf("November\n"); break;
    case 12: printf("December\n"); break;
    }
}

void Draw_Calendar()            //달력을 그림 
{
    int i, j, count = 1;

    system("CLS");            //화면상의 내용을 cls명령어로 지워준다. 

    Print_Month();               //달을 출력 
    printf("\n\t\t\t sun mon tue wed thr fri sat \n");   //주를 출력 

    // 5주에 걸쳐서
    for (i = 0; i <= 5; i++)
    {
        printf("\t\t\t");
        // 일요일부터 토요일까지 날짜를 출력한다
        for (j = 0; j < 7; j++)
        {
            // 만약 날짜가 없는 요일은 공백으로 출력한다
            if (i == 0 && j < week)
            {
                printf("    ");
            }
            else
            {
                if (Check_Schedule[count] == 0) printf("%4d", count);
                else printf("   *");

                count++;

                // 만약 입력된 달의 마지막 날짜를 넘는다면 종료한다
                if (count > lastday)
                {
                    printf("\n");
                    break;
                }
            }
        }
        // 주가 끝났으므로 줄을 바꾼다
        if (count > lastday) break;
        printf("\n");
    }
}

void Input_Schedule()
{
    int day, i, check = 'y';      //check를 y로 초기화, 스케줄이 없으면 바로 스케줄 쓰기로 넘어가기 위해서 
    char line[1024];            //임시로 스케줄내용을 입력받을 곳. buffer 

    Draw_Calendar();

    printf("\n날짜 입력 : ");
    scanf("%d", &day);

    if (Check_Schedule[day] != 0)      //만약 해당일에 스케줄이 쓰여있으면 
    {
        printf("스케쥴이 쓰여있습니다.\n");
        printf("계속하시겠습니까?[Y/N] : [ ]\b\b");
        fflush(stdin);               //입력 버퍼 비우기 
        scanf("%c", &check);         //Y or N. Y시 일기 덮어쓰기 시작 
    }

    if (check == 'Y' || check == 'y')
    {
        printf("\n스케쥴 입력\n");
        printf("(5줄 이하 입력 가능 끝내려면 END를 입력하세요 \"END\")\n\n");

        Check_Schedule[day] = 1;         //해당일에 스케줄를 씀을 체크 

        for (i = 0; i < Max_Line; i++)            //줄 수는 Max_line으로 제한 
        {
            strcpy(Schedule[day][i], "\0");      //스케줄 쓸 공간을 NULL로 초기화 한다. 
            fflush(stdin);
            gets(line);                  //내용을 입력받는다. 

            if (!strcmp(line, "END")) break;   //만약 받은 라인이 END라면 for문을 빠져나온다 
            else
            {
                strcpy(Schedule[day][i], line);   //스케줄 내용을 Schedule[day][i]에 저장 
            }
        }
    }
}

void WEEK(int _day)                  //주 이름을 출력하는 함수 
{
    switch (_day)
    {
    case 0: printf("Sun\n\n"); break;
    case 1: printf("Mon\n\n"); break;
    case 2: printf("Tue\n\n"); break;
    case 3: printf("Wed\n\n"); break;
    case 4: printf("Thr\n\n"); break;
    case 5: printf("Fri\n\n"); break;
    case 6: printf("Sat\n\n"); break;
    }
}


void View_Schedule()         //스케줄 출력 
{
    int day, i;

    Draw_Calendar();      //달력을 그린다 
    printf("\n날짜 입력 : ");   //Day(일)을 입력받는다. 
    scanf("%d", &day);

    printf("%d/%d/%d : ", YEAR, MONTH, day);   //년도, 월, 일을 입력받는다. 
    WEEK(day);                        //해당 주를 계산해서 출력 

    if (Schedule[day] == NULL) printf("There is no Schedule\n");   //해당 일에 스케줄이 없으면 
    else
    {
        for (i = 0; i < Max_Line; i++)
        {
            if (Schedule[day][i] != NULL) printf("%s\n", Schedule[day][i]);      //스케줄의 내용을 출력 
        }
    }

    getch();
}