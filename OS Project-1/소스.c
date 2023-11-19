#include <stdio.h>

int Week[32];
int lastday, YEAR, MONTH;

void Draw_Calendar();
int GetLastDay(int year, int month);
void Print_Month();

int main(void)
{
    int year, month, th;

    printf("해당 년을 입력하시오: ");
    scanf("%d", &year);
    YEAR = year;

    printf("해당 월을 입력하시오: ");
    scanf("%d", &month);
    MONTH = month;

    lastday = GetLastDay(year, month);

    th = year / 100;
    year = year % 100;
    int week = ((21 * th / 4) + (5 * year / 4) + (26 * (month + 1)) / 10) % 7;

    for (int i = 1; i <= lastday; i++)
    {
        Week[i] = (week + i - 1) % 7;
    }

    Draw_Calendar();

    return 0;
}

void Draw_Calendar()
{
    printf("\n\t\t\t\t\t");
    Print_Month();
    printf("\n\t\t\t sun mon tue wed thr fri sat \n");

    for (int i = 0; i <= 5; i++)
    {
        printf("\t\t\t");
        for (int j = 0; j < 7; j++)
        {
            if (i == 0 && j < Week[1])
            {
                printf("    ");
            }
            else
            {
                printf("%4d", i * 7 + j - Week[1] + 1);
                if (i * 7 + j - Week[1] + 1 > lastday)
                {
                    printf("\n");
                    break;
                }
            }
        }
        if (i * 7 + Week[1] > lastday)
            break;
        printf("\n");
    }
}

void Print_Month()
{
    switch (MONTH)
    {
    case 1: printf("January\n"); break;
    case 2: printf("Feburay\n"); break;
    case 3: printf("March\n"); break;
    case 4: printf("April\n"); break;
    case 5: printf("May\n"); break;
    case 6: printf("June\n"); break;
    case 7: printf("July\n"); break;
    case 8: printf("August\n"); break;
    case 9: printf("September\n"); break;
    case 10: printf("October\n"); break;
    case 11: printf("November\n"); break;
    case 12: printf("December\n"); break;
    }
}

int GetLastDay(int year, int month)
{
    int num[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    int lastday = num[month - 1];

    if (month == 2 && (!(year % 4) && (year % 100) || !(year % 400)))
        lastday = 29;

    if (month == 2 || month == 1)
    {
        year--;
        month += 12;
    }

    return lastday;
}