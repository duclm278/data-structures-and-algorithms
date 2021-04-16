#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_L 256

typedef struct Profile
{
	char name[MAX_L];
	char email[MAX_L];
	struct Profile *next;
} Profile;

Profile *first, *last;

void initList(void);
int listEmpty(void);
Profile *makeProfile(char *name, char *email);
void insertLast(char *name, char *email);
void loadData(char *filename);
void printList(void);
void removeProfile(char *name);
Profile *findProfile(char *name);
void saveData(char *filename);
void clearList(void);

int main(void)
{
	int choice;
	char filename[MAX_L];
	char name[MAX_L];
	char email[MAX_L];
	Profile *p;

	while (1)
	{
		printf("1. Load data\n");
		printf("2. Display list\n");
		printf("3. Create new profile\n");
		printf("4. Remove a profile\n");
		printf("5. Find a profile\n");
		printf("6. Save data\n");
		printf("7. Quit\n");
		printf("Enter command: ");

		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			printf("Enter filename: ");
			scanf("%s", filename);
			loadData(filename);
			break;
		case 2:
			printList();
			break;
		case 3:
			printf("Enter name: ");
			scanf("%s", name);
			printf("Enter email: ");
			scanf("%s", email);
			insertLast(name, email);
			break;
		case 4:
			printf("Enter name: ");
			scanf("%s", name);
			removeProfile(name);
			break;
		case 5:
			printf("Enter name: ");
			scanf("%s", name);
			p = findProfile(name);
			if (p != NULL)
				printf("FOUND profile %s, %s\n", p->name, p->email);
			else
				printf("NOT FOUND profile %s\n", name);
			break;
		case 6:
			printf("Enter name: ");
			scanf("%s", filename);
			saveData(filename);
			break;
		case 7:
			clearList();
			return 0;
			break;
		}
		printf("\n");
	}
}

void initList(void)
{
	first = NULL;
	last = NULL;
}

int listEmpty(void)
{
	return (first == NULL && last == NULL);
}

Profile *makeProfile(char *name, char *email)
{
	Profile *p = malloc(sizeof(Profile));
	strcpy(p->name, name);
	strcpy(p->email, email);
	p->next = NULL;
	return p;
}

void insertLast(char *name, char *email)
{
	Profile *p = makeProfile(name, email);
	if (listEmpty())
	{
		first = p;
		last = p;
	}
	else
	{
		last->next = p;
		last = p;
	}
}

void loadData(char *filename)
{
	FILE *f = fopen(filename, "r");
	if (f == NULL)
	{
		printf("Can't load data\n");
		return;
	}

	char name[MAX_L], email[MAX_L];
	while (!feof(f))
	{
		fscanf(f, "%s%s", name, email);
		insertLast(name, email);
	}

	fclose(f);
}

void printList(void)
{
	for (Profile *p = first; p != NULL; p = p->next)
	{
		printf("%s, %s\n", p->name, p->email);
	}
}

void removeProfile(char *name)
{
	Profile *p = NULL;
	Profile *tmp = NULL;
	Profile *prev = NULL;

	if (strcmp(first->name, name) == 0)
	{
		while (strcmp(first->name, name) == 0)
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
		if (strcmp(p->name, name) == 0)
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
}

Profile *findProfile(char *name)
{
	Profile *p = first;
	while (p != NULL)
	{
		if (strcmp(p->name, name) == 0)
			return p;
		p = p->next;
	}
	return NULL;
}

void saveData(char *filename)
{
	FILE *f = fopen(filename, "w+");
	if (f == NULL)
	{
		printf("Can't load data\n");
		return;
	}

	for (Profile *p = first; p != NULL; p = p->next)
	{
		fprintf(f, "%s %s", p->name, p->email);
		if (p->next != NULL)
			fprintf(f, "\n");
	}

	fclose(f);
}

void clearList(void)
{
	Profile *p = first;
	Profile *tmp = NULL;
	while (p != NULL)
	{
		tmp = p;
		p = p->next;
		free(tmp);
	}
	first = last = NULL;
}
