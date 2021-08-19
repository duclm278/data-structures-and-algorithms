#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_L 256

struct DiemDoNode {
	char id[10];
	int x;
	int y;
	struct DiemDoNode *next;
};
typedef struct DiemDoNode *DiemDoDB;
typedef struct DiemDoNode DiemDo;
 
struct TuyenXeNode {
	char id[10];
	int soDiemDo;
	DiemDo dsDiemDo[10];
	struct TuyenXeNode *next;
};
typedef struct TuyenXeNode *TuyenXeDB;
typedef struct TuyenXeNode TuyenXe;

DiemDo *first_dd, *last_dd;
TuyenXe *first_tx, *last_tx;

// Diem do
void initList_dd(void);
int listEmpty_dd(void);
DiemDo *makeProfile_dd(char *id, int x, int y);
void insertLast_dd(char *id, int x, int y);
void loadData_dd(char *filename_dd);
void printList_dd(void);
// void removeProfile_dd(char *id);
DiemDo *findProfile_dd(char *id);
// void saveData_dd(char *filename_dd);
// void clearList_dd(void);

// Tuyen xe
void initList_tx(void);
int listEmpty_tx(void);
TuyenXe *makeProfile_tx(char *id, int soDiemDo, DiemDo dsDiemDo[]);
void insertLast_tx(char *id, int soDiemDo, DiemDo dsDiemDo[]);
void loadData_tx(char *filename_tx);
void printList_tx(void);
// void removeProfile_tx(char *id);
TuyenXe *findProfile_tx(char *id);
// void saveData_tx(char *filename_tx);
// void clearList_tx(void);

int main(void)
{
	int choice;
	// char filename[MAX_L];
	char id_dd[MAX_L];
	int x_dd;
	int y_dd;
	char id_tx[MAX_L];
	int soDiemDo_tx;
	DiemDo dsDiemDo_tx[10];

	while (1)
	{
		printf("1. Load and display data\n");
		printf("2. Nhap diem do moi\n");
		printf("3. Nhap tuyen xe moi\n");
		printf("4. Tim tat ca tuyen xe qua diem do\n");
		printf("5. Tim diem do gan (x, y) nhat\n");
		printf("6. Save data");
		printf("7. Display data\n");
		printf("Enter command: ");

		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			loadData_dd("DIEMDO.txt");
			printList_dd();
			printf("\n");
			loadData_tx("TUYENXE.txt");
			printList_tx();
			break;
		case 2:
			printf("Nhap diem do moi\n");

			int flag_dd = 0;
			do
			{
				if (flag_dd == 1)
					printf("Error! Try again!\n");
				printf("Nhap id: ");
				scanf("%s", id_dd);
				printf("Nhap x: ");
				scanf("%d", &x_dd);
				printf("Nhap y: ");
				scanf("%d", &y_dd);

				if (findProfile_dd(id_dd) == NULL)
					flag_dd = 0;
				else
					flag_dd = 1;
			} while (flag_dd == 1);

			insertLast_dd(id_dd, x_dd, y_dd);
			printList_dd();
			break;
		case 3:
			printf("Nhap tuyen xe moi\n");

			int flag_tx = 0;
			do
			{
				if (flag_tx == 1)
					printf("Error! Try again!\n");
				printf("Nhap id: ");
				scanf("%s", id_tx);
				printf("Nhap soDiemDo: ");
				scanf("%d", &soDiemDo_tx);
				for (int i = 0; i < soDiemDo_tx; i++)
				{
					printf("Nhap diem do %d\n", i + 1);
					printf("Nhap id: ");
					scanf("%s", id_dd);
					strcpy(dsDiemDo_tx[i].id, id_dd);
				}

				if (findProfile_tx(id_tx) == NULL)
				{
					for (int i = 0; i < soDiemDo_tx; i++)
					{
						if (findProfile_dd(dsDiemDo_tx[i].id) != NULL)
							flag_tx = 0;
						else
						{
							flag_tx = 1;
							break;
						}
					}
				}
				else
					flag_tx = 1;
			} while (flag_tx == 1);

			insertLast_tx(id_tx, soDiemDo_tx, dsDiemDo_tx);
			printList_tx();
			break;
		case 4:
			printf("Nhap id: ");
			scanf("%s", id_dd);
			
			int count_tx = 0;
			for (TuyenXe *p = first_tx; p != NULL; p = p->next)
			{
				for (int i = 0; i < p->soDiemDo; i++)
				{
					if (strcmp((p->dsDiemDo)[i].id, id_dd) == 0)
					{
						printf("%s\n", p->id);
						count_tx++;
					}
				}
			}
			
			if (count_tx == 0)
				printf("Not found!\n");
			break;
		case 5:
			printf("Nhap vi tri\n");
			int x_0, y_0;
			printf("Nhap x: ");
			scanf("%d", &x_0);
			printf("Nhap y: ");
			scanf("%d", &y_0);

			char result[10];
			double min_distance = -1;
			double current_distance;
			for (DiemDo *p = first_dd; p != NULL; p = p->next)
			{
				current_distance = sqrt( pow((p->x - x_0), 2) + pow((p->y - y_0), 2) );
				if (min_distance == -1 || min_distance > current_distance)
				{
					min_distance = current_distance;
					strcpy(id_dd, p->id);
				}
			}
			printf("%s\n", id_dd);
			break;
		case 6:
			break;
		case 7:
			printList_dd();
			printf("\n");
			printList_tx();
			break;
		}
		printf("\n");
	}
}

// Diem do
void initList_dd(void)
{
	first_dd = NULL;
	last_dd = NULL;
}

int listEmpty_dd(void)
{
	return (first_dd == NULL && last_dd == NULL);
}

DiemDo *makeProfile_dd(char *id, int x, int y)
{
	DiemDo *p = malloc(sizeof(DiemDo));
	strcpy(p->id, id);
	p->x = x;
	p->y = y;
	p->next = NULL;
	return p;
}

void insertLast_dd(char *id, int x, int y)
{
	DiemDo *p = makeProfile_dd(id, x, y);
	if (listEmpty_dd())
	{
		first_dd = p;
		last_dd = p;
	}
	else
	{
		last_dd->next = p;
		last_dd = p;
	}
}

void loadData_dd(char *filename_dd)
{
	FILE *f = fopen(filename_dd, "r");
	if (f == NULL)
	{
		printf("Can't load data\n");
		return;
	}

	int size_dd;
	if (fscanf(f, "%d", &size_dd) != 1)
		return;
	
	char id[10];
	int x;
	int y;
	for (int i = 0; i < size_dd; i++)
	{
		fscanf(f, "%s%d%d", id, &x, &y);
		insertLast_dd(id, x, y);
	}

	fclose(f);
}

void printList_dd(void)
{
	printf("Diem Do        Toa do\n");
	printf("-----------------------------------------------------\n");
	for (DiemDo *p = first_dd; p != NULL; p = p->next)
	{
		printf("%s           (%d, %d)\n", p->id, p->x, p->y);
	}
}

void removeProfile_dd(char *id)
{
	
}

DiemDo *findProfile_dd(char *id)
{
	DiemDo *p = first_dd;
	while (p != NULL)
	{
		if (strcmp(p->id, id) == 0)
			return p;
		p = p->next;
	}
	return NULL;
}

void saveData_dd(char *filename_dd)
{
	
}

void clearList_dd(void)
{
	
}

// Tuyen xe
void initList_tx(void)
{
	first_tx = NULL;
	last_tx = NULL;
}

int listEmpty_tx(void)
{
	return (first_tx == NULL && last_tx == NULL);
}

TuyenXe *makeProfile_tx(char *id, int soDiemDo, DiemDo dsDiemDo[])
{
	TuyenXe *p = malloc(sizeof(TuyenXe));
	strcpy(p->id, id);
	p->soDiemDo = soDiemDo;
	for (int i = 0; i < soDiemDo; i++)
		(p->dsDiemDo)[i] = dsDiemDo[i];
	p->next = NULL;
	return p;
}

void insertLast_tx(char *id, int soDiemDo, DiemDo dsDiemDo[])
{
	TuyenXe *p = makeProfile_tx(id, soDiemDo, dsDiemDo);
	if (listEmpty_tx())
	{
		first_tx = p;
		last_tx = p;
	}
	else
	{
		last_tx->next = p;
		last_tx = p;
	}
}

void loadData_tx(char *filename_tx)
{
	FILE *f = fopen(filename_tx, "r");
	if (f == NULL)
	{
		printf("Can't load data\n");
		return;
	}

	int size_tx;
	if (fscanf(f, "%d", &size_tx) != 1)
		return;
	
	char id[10];
	int soDiemDo;
	DiemDo dsDiemDo[10];
	for (int i = 0; i < size_tx; i++)
	{
		fscanf(f, "%s%d", id, &soDiemDo);
		for (int j = 0; j < soDiemDo; j++)
		{
			fscanf(f, "%s", (dsDiemDo[j]).id);
		}
		insertLast_tx(id, soDiemDo, dsDiemDo);
	}

	fclose(f);
}

void printList_tx(void)
{
	printf("Tuyen xe       Lo trinh\n");
	printf("-----------------------------------------------------\n");
	for (TuyenXe *p = first_tx; p != NULL; p = p->next)
	{
		printf("%s            [", p->id);
		for (int i = 0; i < p->soDiemDo; i++)
		{
			printf("%s", ((p->dsDiemDo)[i]).id);
			if (i != p->soDiemDo - 1)
				printf(", ");
		}
		printf("]\n");
	}
}

void removeProfile_tx(char *id)
{
	
}

TuyenXe *findProfile_tx(char *id)
{
	TuyenXe *p = first_tx;
	while (p != NULL)
	{
		if (strcmp(p->id, id) == 0)
			return p;
		p = p->next;
	}
	return NULL;
}

void saveData_tx(char *filename_tx)
{
	
}

void clearList_tx(void)
{
	
}