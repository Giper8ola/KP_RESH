


#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

typedef struct Zakaz
{
    int number;
    char date[20];
    char client[100];
    int summ;
    int status;
} z;

int save(char* filename, struct Zakaz zakaz[1]);
int loadMany(char* filename);
int loadOne(char* filename, int number);
int sort(char* fileName, char date[20]);

void main()
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
                struct Zakaz zakaz[1];
                char firstName[48], lastName[48], name[100] = "";
                zakaz[0].number = rand() % 100;
				printf("������� ���� ������: ");
                scanf("%s", &zakaz[0].date);
                printf("������� ��� � ������� �������: ");
                scanf("%s %s", &firstName, &lastName);
                strcat(name, firstName);
                strcat(name, " ");
                strcat(name, lastName);
                strncpy(zakaz[0].client, name, 100);
                printf("�������� ����� ������: ");
                scanf("%d", &zakaz[0].summ);
                printf("������� ������ ������: ");
                scanf("%d", &zakaz[0].status);
                save(filename, zakaz);
                break;
			}
            case 2: {
                loadMany(filename);
                break;
            }
            case 3: {
                int number;
                printf("������ ����� ������: ");
                scanf("%d", &number);
                loadOne(filename, number);
                break;
            }
            case 4: {
                char arr[20] = "fddss";
                sort(filename, arr);
            }
            
		}
		
	} while (1);
}

int save(char* filename, struct Zakaz zakaz[1])
{
    int size = sizeof(zakaz[0]);              // ������ ����� �������
    int count = sizeof(zakaz) / size;         // ���������� �������� 

    FILE* fp = fopen(filename, "a+");
    size_t written = fwrite(zakaz, size, 1, fp);
    printf("����� ������ ��������");
    fclose(fp);
}

int loadMany(char* filename)
{
    struct Zakaz p; 
    FILE* fp = fopen(filename, "r");
    printf("\n������ � ���� ������: \n");
    while (fread(&p, sizeof(p), 1, fp) == 1)
    {
        printf("\nId: %d\nDate: %s\nClient: %s\n����� ������: %d\n������ ������: %d", p.number, p.date, p.client, p.summ, p.status);
    }
    printf("\n");
    fclose(fp);
}

int loadOne(char* filename, int number)
{
    struct Zakaz p;
    FILE* fp = fopen(filename, "r");
    printf("\n����� �� �������: %d\n", number);
    while (fread(&p, sizeof(p), 1, fp) == 1)
    {
        if (p.number == number)
            printf("\nId: %d\nDate: %s\nClient: %s\n����� ������: %d\n������ ������: %d", p.number, p.date, p.client, p.summ, p.status);
    }
    printf("\n");
    fclose(fp);
}

int sort(char* fileName, char date[20])
{
    struct Zakaz p;
    FILE* fp = fopen(fileName, "r");
    fseek(fp, 0, SEEK_END);
    int file_size = ftell(fp);
    int n = file_size / sizeof(p);
    struct Zakaz* zakaz;
    zakaz = malloc(n * sizeof(struct Zakaz));

    int i = 0;
    while (fread(&p, sizeof(p), 1, fp) == 1 && i < n)
    {
        *(zakaz + n + i) = p;
        i++;
    }
    for (int i = 0; i < n; i++)
        printf("\nId: %d", (*(zakaz + n + i)).number);

    printf("\n");
    fclose(fp);
}

