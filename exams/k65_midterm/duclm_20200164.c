#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_L 256

struct StudentNode
{
	char id[10];
	char name[50];
	double toan, ly, hoa;
	struct StudentNode *next;
};
typedef struct StudentNode *StudentDB;

/* Read from file */
StudentDB read_db(char *filename);

/* Make a new node */
struct StudentNode *make_node(char *id, char *name, double toan, double ly, double hoa);

/* Append a new node to the end of the list */
StudentDB append_std(StudentDB db, struct StudentNode *st);

/* Find a node by ID */
struct StudentNode *find_by_id(StudentDB db, char *id);

/* Remove a node */
StudentDB remove_std(StudentDB db, char *id);

/* Swap two nodes */
StudentDB swap_std(StudentDB db, struct StudentNode *b1, struct StudentNode *b2);

/* Print a student profile */
void print_std(struct StudentNode *s);

/* Print all profiles */
void print_db(StudentDB db);

int main(void)
{
	int n;
	int flag;
	int flag1;
	int flag2;
	int choice;
	char filename[MAX_L];
	char id[10];
	char id1[10];
	char id2[10];
	char name[50];
	double toan, ly, hoa;
	StudentDB db = NULL;
	struct StudentNode tmp;

	while (1)
	{
		printf("1. Load data\n");
		printf("2. Add a new profile\n");
		printf("3. Delete a profile\n");
		printf("4. Swap two students\n");
		printf("5. Find students\n");
		printf("6. Quit\n");
		printf("Enter command: ");

		scanf("%d", &choice);
		getchar();
		switch (choice)
		{
		case 1:
			printf("Enter filename: ");
			scanf("%s", filename);
			getchar();
			db = read_db(filename);
			print_db(db);
			break;
		case 2:
			printf("Add a new profile\n");

			flag = 0;
			do
			{
				if (flag == 1)
					printf("=> Error! Try again!\n");
				printf("Enter id: ");
				scanf("%s", id);
				getchar();
				printf("Enter name: ");
				fgets(name, 50, stdin);
				if (name[strlen(name) - 1] == '\n')
					name[strlen(name) - 1] = '\0';
				printf("Enter toan: ");
				scanf("%lf", &toan);
				getchar();
				printf("Enter ly: ");
				scanf("%lf", &ly);
				getchar();
				printf("Enter hoa: ");
				scanf("%lf", &hoa);
				getchar();

				if (find_by_id(db, id) == NULL)
					flag = 0;
				else
					flag = 1;
			} while (flag == 1);

			strcpy(tmp.id, id);
			strcpy(tmp.name, name);
			tmp.toan = toan;
			tmp.ly = ly;
			tmp.hoa = hoa;
			db = append_std(db, &tmp);
			print_db(db);
			break;
		case 3:
			printf("Delete a profile\n");

			flag = 0;
			do
			{
				if (flag == 1)
					printf("=> Error! Try again!\n");
				printf("Enter id: ");
				scanf("%s", id);
				getchar();

				if (find_by_id(db, id) != NULL)
					flag = 0;
				else
					flag = 1;
			} while (flag == 1);

			db = remove_std(db, id);
			print_db(db);
			break;
		case 4:
			printf("Swap two students\n");

			flag1 = 0;
			flag2 = 0;
			do
			{
				if (flag1 == 1 || flag2 == 1)
					printf("=> Error! Try again!\n");
				printf("Enter id1: ");
				scanf("%s", id1);
				getchar();
				printf("Enter id2: ");
				scanf("%s", id2);
				getchar();

				if (find_by_id(db, id1) != NULL)
					flag1 = 0;
				else
					flag1 = 1;
				if (find_by_id(db, id2) != NULL)
					flag2 = 0;
				else
					flag2 = 1;
			} while (flag1 == 1 || flag2 == 1);

			db = swap_std(db, find_by_id(db, id1), find_by_id(db, id2));
			print_db(db);
			break;
		case 5:
			printf("Enter n: ");
			scanf("%d", &n);
			printf("ID          Name                                                Math   Physics  Chemistry\n");
			printf("-----------------------------------------------------------------------------------------\n");
			for (struct StudentNode *p = db; p != NULL; p = p->next)
			{
				if (p->toan + p->ly + p-> hoa >= n)
					print_std(p);
			}
			break;
		case 6:
			return 0;
			break;
		}
		printf("\n");
	}
}

/* Read from file */
StudentDB read_db(char *filename)
{
	StudentDB db = NULL;
	FILE *f = fopen(filename, "r");
	if (f == NULL)
	{
		printf("Can't load data\n");
		return db;
	}

	int size;
	if (fscanf(f, "%d", &size) != 1)
		return db;

	char id[10];
	char name[50];
	double toan, ly, hoa;
	struct StudentNode st;
	for (int i = 0; i < size; i++)
	{
		fscanf(f, "%s\n", st.id);
		fgets(st.name, 50, f);
		if ((st.name)[strlen(st.name) - 1] == '\n')
			(st.name)[strlen(st.name) - 1] = '\0';
		fscanf(f, "%lf%lf%lf", &st.toan, &st.ly, &st.hoa);
		db = append_std(db, &st);
	}

	fclose(f);
	return db;
}

/* Make a new node */
struct StudentNode *make_node(char *id, char *name, double toan, double ly, double hoa)
{
	struct StudentNode *n = (struct StudentNode *)malloc(sizeof(struct StudentNode));
	strcpy(n->id, id);
	strcpy(n->name, name);
	n->toan = toan;
	n->ly = ly;
	n->hoa = hoa;
	n->next = NULL;
	return n;
}

/* Append a new node to the end of the list */
StudentDB append_std(StudentDB db, struct StudentNode *st)
{
	if (db == NULL)
	{
		db = make_node(st->id, st->name, st->toan, st->ly, st->hoa);
		return db;
	}

	struct StudentNode *last = db;
	while (last->next != NULL)
		last = last->next;

	last->next = make_node(st->id, st->name, st->toan, st->ly, st->hoa);
	return db;
}

/* Find a node by ID */
struct StudentNode *find_by_id(StudentDB db, char *id)
{
	struct StudentNode *p = db;
	while (p != NULL)
	{
		if (strcmp(p->id, id) == 0)
			return p;
		p = p->next;
	}
	return NULL;
}

/* Remove a node */
StudentDB remove_std(StudentDB db, char *id)
{
	struct StudentNode *p = NULL;
	struct StudentNode *tmp = NULL;
	struct StudentNode *prev = NULL;

	struct StudentNode *first = db;
	struct StudentNode *last = db;
	while (last->next != NULL)
		last = last->next;

	if (strcmp(first->id, id) == 0)
	{
		while (strcmp(first->id, id) == 0)
		{
			tmp = first;
			first = first->next;
			free(tmp);
		}
		if (first == NULL)
			last = NULL;
	}

	prev = first;
	p = first->next;
	while (p != NULL)
	{
		if (strcmp(p->id, id) == 0)
		{
			tmp = p;
			p = p->next;
			prev->next = p;
			free(tmp);
		}
		else
		{
			prev = p;
			p = prev->next;
		}
	}
	last = prev;

	return first;
}

/* Swap two nodes */
StudentDB swap_std(StudentDB db, struct StudentNode *b1, struct StudentNode *b2)
{
	struct StudentNode tmp;

	strcpy(tmp.id, b1->id);
	strcpy(b1->id, b2->id);
	strcpy(b2->id, tmp.id);

	strcpy(tmp.name, b1->name);
	strcpy(b1->name, b2->name);
	strcpy(b2->name, tmp.name);
	
	tmp.toan = b1->toan;
	b1->toan = b2->toan;
	b2->toan = tmp.toan;

	tmp.ly = b1->ly;
	b1->ly = b2->ly;
	b2->ly = tmp.ly;

	tmp.hoa = b1->hoa;
	b1->hoa = b2->hoa;
	b2->hoa = tmp.hoa;

	return db;
}

/* Print a student profile */
void print_std(struct StudentNode *s)
{
	printf("%-10s  %-50s  %-5.2lf  %-5.2lf    %-5.2lf\n", s->id, s->name, s->toan, s->ly, s->hoa);
}

/* Print all profiles */
void print_db(StudentDB db)
{
	printf("ID          Name                                                Math   Physics  Chemistry\n");
	printf("-----------------------------------------------------------------------------------------\n");
	for (struct StudentNode *p = db; p != NULL; p = p->next)
	{
		print_std(p);
	}
}