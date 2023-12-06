#include <stdio.h>

#define Max_Line 5

int Week[32];
char Schedule[32][Max_Line][1024];      //�������� ������ �Է¹ޱ� ���� �迭 
int Check_Schedule[32] = { 0, };         //������ �Է� üũ �迭�� ���� 0���� �ʱ�ȭ 
int week, lastday, YEAR, MONTH;

void Draw_Calendar();
void Input_Schedule();
void View_Schedule();

int main(void)
{
    int op, i;
    int year, month, th;
    int num[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };   //1�� �� ���� �ϼ��� ���� 

    printf("�ش���� �Է��Ͻÿ� : ");      //������ �Է¹޴´�. 
    scanf("%d", &year);
    YEAR = year;

    printf("�ش� ���� �Է��Ͻÿ� : ");
    scanf("%d", &month);         //���� �Է¹޴´�. 
    MONTH = month;

    // �Էµ� ���� ������ ��¥�� ���Ѵ�
    lastday = num[month - 1];

    // ���� �����̸� ������ ���ڸ� 29�Ϸ� �����Ѵ�
    if (month == 2 && (!(year % 4) && (year % 100) || !(year % 400))) lastday = 29;

    // 1�� �̳� 2���̸� ������ 13�� �̳� 14���� ����
    if (month == 2 || month == 1)
    {
        year--;
        month += 12;
    }

    // �⵵�� ���� ���ڸ��� ���� ���ڸ��� ������
    th = year / 100;
    year = year % 100;

    // �ش� �� 1���� ���� ���ϴ� ����
    week = ((21 * th / 4) + (5 * year / 4) + (26 * (month + 1)) / 10) % 7;

    for (i = 1; i <= lastday; i++)
    {
        Week[i] = (week + i - 1) % 7;
    }

    while (1)
    {
        Draw_Calendar();         //�޷� �׸��� �Լ��� ȣ���Ѵ�. (�޷� ���) 

        printf("\n** M E N U **\n");
        printf("1. ������ �Է�\n");
        printf("2. ������ ����\n");
        printf("3. ������\n");
        printf("In : ");
        fflush(stdin);         //�� �ܰ迡�� �Է� ��Ʈ���� ���� �����͸� ����. 
        scanf("%d", &op);         //�޴� �̵� 

        switch (op)
        {
        case 1: Input_Schedule(); break;   //���� �Է� �Լ� 
        case 2: View_Schedule(); break;   //���� ��� �Լ� 
        case 3: exit(1);
        }
    }
    return 0;
}

void Print_Month()                  //���� ����ϴ� �Լ� 
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

void Draw_Calendar()            //�޷��� �׸� 
{
    int i, j, count = 1;

    system("CLS");            //ȭ����� ������ cls��ɾ�� �����ش�. 

    Print_Month();               //���� ��� 
    printf("\n\t\t\t sun mon tue wed thr fri sat \n");   //�ָ� ��� 

    // 5�ֿ� ���ļ�
    for (i = 0; i <= 5; i++)
    {
        printf("\t\t\t");
        // �Ͽ��Ϻ��� ����ϱ��� ��¥�� ����Ѵ�
        for (j = 0; j < 7; j++)
        {
            // ���� ��¥�� ���� ������ �������� ����Ѵ�
            if (i == 0 && j < week)
            {
                printf("    ");
            }
            else
            {
                if (Check_Schedule[count] == 0) printf("%4d", count);
                else printf("   *");

                count++;

                // ���� �Էµ� ���� ������ ��¥�� �Ѵ´ٸ� �����Ѵ�
                if (count > lastday)
                {
                    printf("\n");
                    break;
                }
            }
        }
        // �ְ� �������Ƿ� ���� �ٲ۴�
        if (count > lastday) break;
        printf("\n");
    }
}

void Input_Schedule()
{
    int day, i, check = 'y';      //check�� y�� �ʱ�ȭ, �������� ������ �ٷ� ������ ����� �Ѿ�� ���ؼ� 
    char line[1024];            //�ӽ÷� �����ٳ����� �Է¹��� ��. buffer 

    Draw_Calendar();

    printf("\n��¥ �Է� : ");
    scanf("%d", &day);

    if (Check_Schedule[day] != 0)      //���� �ش��Ͽ� �������� ���������� 
    {
        printf("�������� �����ֽ��ϴ�.\n");
        printf("����Ͻðڽ��ϱ�?[Y/N] : [ ]\b\b");
        fflush(stdin);               //�Է� ���� ���� 
        scanf("%c", &check);         //Y or N. Y�� �ϱ� ����� ���� 
    }

    if (check == 'Y' || check == 'y')
    {
        printf("\n������ �Է�\n");
        printf("(5�� ���� �Է� ���� �������� END�� �Է��ϼ��� \"END\")\n\n");

        Check_Schedule[day] = 1;         //�ش��Ͽ� �����ٸ� ���� üũ 

        for (i = 0; i < Max_Line; i++)            //�� ���� Max_line���� ���� 
        {
            strcpy(Schedule[day][i], "\0");      //������ �� ������ NULL�� �ʱ�ȭ �Ѵ�. 
            fflush(stdin);
            gets(line);                  //������ �Է¹޴´�. 

            if (!strcmp(line, "END")) break;   //���� ���� ������ END��� for���� �������´� 
            else
            {
                strcpy(Schedule[day][i], line);   //������ ������ Schedule[day][i]�� ���� 
            }
        }
    }
}

void WEEK(int _day)                  //�� �̸��� ����ϴ� �Լ� 
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


void View_Schedule()         //������ ��� 
{
    int day, i;

    Draw_Calendar();      //�޷��� �׸��� 
    printf("\n��¥ �Է� : ");   //Day(��)�� �Է¹޴´�. 
    scanf("%d", &day);

    printf("%d/%d/%d : ", YEAR, MONTH, day);   //�⵵, ��, ���� �Է¹޴´�. 
    WEEK(day);                        //�ش� �ָ� ����ؼ� ��� 

    if (Schedule[day] == NULL) printf("There is no Schedule\n");   //�ش� �Ͽ� �������� ������ 
    else
    {
        for (i = 0; i < Max_Line; i++)
        {
            if (Schedule[day][i] != NULL) printf("%s\n", Schedule[day][i]);      //�������� ������ ��� 
        }
    }

    getch();
}