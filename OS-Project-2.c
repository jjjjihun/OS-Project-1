#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Max_Line 5

int Week[32];
char Schedule[32][Max_Line][1024];
int Check_Schedule[32] = { 0, };
int week, lastday, YEAR, MONTH;

void Draw_Calendar();
void Input_Schedule();

int main(void)
{
    int op, i;
    int year, month, th;
    int num[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    printf("해당년을 입력하시오 : ");
    scanf("%d", &year);
    YEAR = year;

    printf("해당 월을 입력하시오 : ");
    scanf("%d", &month);
    MONTH = month;

    lastday = num[month - 1];

    if (month == 2 && (!(year % 4) && (year % 100) || !(year % 400)))
        lastday = 29;

    if (month == 2 || month == 1)
    {
        year--;
        month += 12;
    }

    th = year / 100;
    year = year % 100;

    week = ((21 * th / 4) + (5 * year / 4) + (26 * (month + 1)) / 10) % 7;

    for (i = 1; i <= lastday; i++)
    {
        Week[i] = (week + i - 1) % 7;
    }

    while (1)
    {
        Draw_Calendar();

        printf("\n** M E N U **\n");
        printf("1. 스케쥴 입력\n");
        printf("In : ");
        fflush(stdin);
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            Input_Schedule();
            break;
        }
    }
    return 0;
}

void Print_Month()
{
    printf("\n\t\t\t             ");
    switch (MONTH)
    {
    case 1:
        printf("January\n");
        break;
    case 2:
        printf("Feburay\n");
        break;
    case 3:
        printf("March\n");
        break;
    case 4:
        printf("Aprill\n");
        break;
    case 5:
        printf("May\n");
        break;
    case 6:
        printf("June\n");
        break;
    case 7:
        printf("July\n");
        break;
    case 8:
        printf("August\n");
        break;
    case 9:
        printf("September\n");
        break;
    case 10:
        printf("October\n");
        break;
    case 11:
        printf("November\n");
        break;
    case 12:
        printf("December\n");
        break;
    }
}

void Draw_Calendar()
{
    int i, j, count = 1;

    system("CLS");

    Print_Month();
    printf("\n\t\t\t sun mon tue wed thr fri sat \n");

    for (i = 0; i <= 5; i++)
    {
        printf("\t\t\t");
        for (j = 0; j < 7; j++)
        {
            if (i == 0 && j < week)
            {
                printf("    ");
            }
            else
            {
                if (Check_Schedule[count] == 0)
                    printf("%4d", count);
                else
                    printf("   *");

                count++;

                if (count > lastday)
                {
                    printf("\n");
                    break;
                }
            }
        }
        if (count > lastday)
            break;
        printf("\n");
    }
}

void Input_Schedule()
{
    int day, i, check = 'y';
    char line[1024];

    Draw_Calendar();

    printf("\n날짜 입력 : ");
    scanf("%d", &day);

    if (Check_Schedule[day] != 0)
    {
        printf("스케쥴이 쓰여있습니다.\n");
        printf("계속하시겠습니까?[Y/N] : [ ]\b\b");
        fflush(stdin);
        scanf("%c", &check);
    }

    if (check == 'Y' || check == 'y')
    {
        printf("\n스케쥴 항목 입력\n");
        printf("(5줄 이하 입력 가능 끝내려면 END를 입력하세요 \"END\")\n\n");

        Check_Schedule[day] = 1;

        for (i = 0; i < Max_Line; i++)
        {
            strcpy(Schedule[day][i], "\0");
            fflush(stdin);
            gets(line);

            if (!strcmp(line, "END"))
                break;
            else
            {
                strcpy(Schedule[day][i], line);
            }
        }
    }
}
