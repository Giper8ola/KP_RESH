


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>


typedef struct Date
{
    int day;
    int month;
    int year;
} date;

typedef struct Inventory
{
    char name[100];
    char category[100];
    int  number;
    char description[100];
    date Date;
    char state[100];
} inventory;

int save(char* filename, inventory Invent[1]);
int loadMany(char* filename);
int loadOne(char* filename, char category[50]);
int sort(char* fileName);
int updateOne(char* fileName, int number, inventory newParams);

int compare(const void* x1, const void* x2);
inventory* fillArrayOfInv(char* filename);
int countOfInvInFile(char* fileName);

int main()
{
    int state;
    srand(time(NULL));
    system("chcp 1251");
    setlocale(LC_ALL, "RUS");
    char* filename = "data.txt";
    do
    {
        printf("\n1 - ��������� ����� � ��\n2 - �������� ������ �� ��\n3 - ����� ����� � ��\n4 - �������������� ��\n5 - �������� �����\n");
        scanf("%d", &state);

        switch (state)
        {
        case 1: {
            inventory invent[1];

            invent[0].number = rand() % 100;

            printf("������� �������� ������������: ");
            fgets(invent[0].name, 100, stdin);
            scanf("%[^\n]", &invent[0].name);

            printf("������� ��������� ������������: ");
            fgets(invent[0].category, 100, stdin);
            scanf("%[^\n]", &invent[0].category);

            printf("������� �������� ������������: ");
            fgets(invent[0].description, 100, stdin);
            scanf("%[^\n]", &invent[0].description);

            printf("���� ��������������: \n");
            printf("������� ����: ");
            scanf("%d", &invent[0].Date.day);
            printf("������� �����: ");
            scanf("%d", &invent[0].Date.month);
            printf("������� ���: ");
            scanf("%d", &invent[0].Date.year);

            printf("������� ��������� ������������: ");
            fgets(invent[0].state, 100, stdin);
            scanf("%[^\n]", &invent[0].state);

            save(filename, invent);
            break;
        }
        case 2: {
            loadMany(filename);
            break;
        }

        case 3: {
            char category[100];
            printf("������� ��������� ������: ");
            fgets(category, 100, stdin);
            scanf("%[^\n]", &category);
            loadOne(filename, category);
            break;
        }

        case 4: {
            puts("�� ���� ��������������: ");
            sort(filename);
            break;
        }

        case 5:
        {
            int state2 = 1, number, state3;
            inventory newParams = { "", "", 100, "", {0, 0, 0}, "" };
            printf("������� ����� ������: ");
            scanf("%d", &number);

            do {
                printf("\n1 - �������� ��������\n2 - �������� ���������\n3 - �������� ��������\n4 - �������� ����\n5 - �������� ���������\n6 - ��������� ���������\n");
                scanf("%d", &state3);

                switch (state3) {
                case 1:
                {
                    printf("������� ����� �������� ������������: ");
                    fgets(newParams.name, 100, stdin);
                    scanf("%[^\n]", &newParams.name);
                    break;
                }
                case 2:
                {
                    printf("������� ����� ��������� ������������: ");
                    fgets(newParams.category, 100, stdin);
                    scanf("%[^\n]", &newParams.category);
                    break;
                }
                case 3:
                {
                    printf("������� ����� �������� ������������: ");
                    fgets(newParams.description, 100, stdin);
                    scanf("%[^\n]", &newParams.description);
                    break;
                }
                case 4:
                {
                    printf("����� ���� ��������������: \n");
                    printf("������� ����: ");
                    scanf("%d", &newParams.Date.day);
                    printf("������� �����: ");
                    scanf("%d", &newParams.Date.month);
                    printf("������� ���: ");
                    scanf("%d", &newParams.Date.year);
                    break;
                }
                case 5:
                {
                    printf("������� ����� ��������� ������������: ");
                    fgets(newParams.state, 100, stdin);
                    scanf("%[^\n]", &newParams.state);
                    break;
                }
                case 6:
                {
                    updateOne(filename, number, newParams);
                    state2 = 2;
                    break;
                }
                }
            } while (state2 == 1);
        }
        default:
            break;
        }

    } while (1);
}

int save(char* filename, inventory Invent[1])
{
    size_t size = sizeof Invent[0];
    FILE* fp = fopen(filename, "a+");
    fwrite(Invent, size, 1, fp);
    printf("����� ������ ��������");
    fclose(fp);
}

int loadMany(char* filename)
{
    inventory Invent;
    FILE* fp = fopen(filename, "r");
    printf("������ � ���� ������: \n");
    while (fread(&Invent, sizeof(Invent), 1, fp) == 1)
    {
        printf("\n�������� ������������: %s\n��������� ������������: %s\n����� ������������: %d\n�������� ������������: %s\n���� ��������������: %d.%d.%d\n��������� ������������: %s\n", Invent.name, Invent.category, Invent.number, Invent.description, Invent.Date.day, Invent.Date.month, Invent.Date.year, Invent.state);
    }
    printf("\n");
    fclose(fp);
}


int loadOne(char* filename, char category[50])
{
    inventory Invent;
    FILE* fp = fopen(filename, "r");
    printf("\n������ ���������: %s\n", category);
    while (fread(&Invent, sizeof(Invent), 1, fp) == 1)
    {
        if (strcmp(Invent.category, category) == 0)
            printf("\n\t�������� ������������: %s\n\t��������� ������������: %s\n\t����� ������������: %d\n\t�������� ������������: %s\n\t���� ��������������: %d.%d.%d\n\t��������� ������������: %s\n", Invent.name, Invent.category, Invent.number, Invent.description, Invent.Date.day, Invent.Date.month, Invent.Date.year, Invent.state);
    }
    fclose(fp);
}

int sort(char* fileName)
{
    inventory* Invent;
    Invent = fillArrayOfInv(fileName);

    int j2 = countOfInvInFile(fileName);

    qsort(Invent, j2, sizeof(inventory), compare);

    for (int i = 0; i < j2; i++)
        printf("\n\t�������� ������������: %s\n\t��������� ������������: %s\n\t����� ������������: %d\n\t�������� ������������: %s\n\t���� ��������������: %d.%d.%d\n\t��������� ������������: %s\n", Invent[i].name, Invent[i].category, Invent[i].number, Invent[i].description, Invent[i].Date.day, Invent[i].Date.month, Invent[i].Date.year, Invent[i].state);

    printf("\n");
}

int updateOne(char* fileName, int number, inventory newParams)
{
    int pos;
    inventory* Invent;
    inventory inv;
    inventory* newInvent;

    Invent = fillArrayOfInv(fileName);

    int j2 = countOfInvInFile(fileName);

    newInvent = (inventory*)malloc(j2 * sizeof(inventory));

    for (int i = 0; i < j2; i++)
    {
        if (Invent[i].number == number)
        {
            pos = i;
            continue;
        }
        newInvent[i] = Invent[i];
    }

    FILE* fp = fopen(fileName, "r");
    while (fread(&inv, sizeof(inv), 1, fp) == 1)
    {
        if (inv.number == number)
        {
            strcpy(inv.name, strcmp(newParams.name, "") != 0 ? newParams.name : inv.name);
            strcpy(inv.description, strcmp(newParams.description, "") != 0 ? newParams.description : inv.description);
            strcpy(inv.category, strcmp(newParams.category, "") != 0 ? newParams.category : inv.category);
            strcpy(inv.state, strcmp(newParams.state, "") != 0 ? newParams.state : inv.state);
            if (newParams.Date.day + newParams.Date.month + newParams.Date.year != 0)
            {
                inv.Date.day = newParams.Date.day;
                inv.Date.month = newParams.Date.month;
                inv.Date.year = newParams.Date.year;
            }
            break;
        }
    }

    fclose(fp);
    newInvent[pos] = inv;

    size_t size = sizeof(newInvent[0]);
    FILE* fp2 = fopen(fileName, "w+");
    fwrite(newInvent, size, j2, fp2);
    printf("���� ������� ��������");
    fclose(fp2);
}

int compare(const void* x1, const void* x2)
{
    inventory* A = (inventory*)x1;
    inventory* B = (inventory*)x2;
    if (A->Date.year == B->Date.year) {
        if (A->Date.month == B->Date.month)
            return A->Date.day - B->Date.day;
        else
            return A->Date.month - B->Date.month;
    }
    else
        return A->Date.year - B->Date.year;
}

int countOfInvInFile(char* fileName)
{
    int count = 0;
    FILE* fp = fopen(fileName, "r");
    inventory inv;
    while (fread(&inv, sizeof(inv), 1, fp) == 1)
    {
        count++;
    }
    fclose(fp);
    return count;
}

inventory* fillArrayOfInv(char* fileName)
{
    int j, j2 = 0;
    inventory inv;
    inventory* Invent;
    j = countOfInvInFile(fileName);

    FILE* fp2 = fopen(fileName, "r");
    Invent = (inventory*)malloc(j * sizeof(inventory));

    while (fread(&inv, sizeof(inv), 1, fp2) == 1)
    {
        Invent[j2] = inv;
        j2++;
    }
    fclose(fp2);

    return Invent;
}