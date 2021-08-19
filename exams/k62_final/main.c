#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_L 256

typedef struct Profile
{
	char class[MAX_L];
	char course[MAX_L];
	char schedule[MAX_L];
	struct Profile *next;
} Profile;

Profile *first, *last;

void initList(void);
int listEmpty(void);
Profile *makeProfile(char *class, char *course, char *schedule);
void insertLast(char *class, char *course, char *schedule);
void loadData(char *filename);
void printList(void);
void removeProfile(char *name);
Profile *findProfile(char *course);
void saveData(char *filename);
void clearList(void);

int main(void)
{
	int choice;
	char filename[MAX_L];
	char class[MAX_L];
	char course[MAX_L];
	char schedule[MAX_L];
	Profile *p;

	while (1)
	{
		printf("1. Load data\n");
		printf("2. Display list\n");
		printf("3. Create new class\n");
		printf("4. Remove a class\n");
		printf("5. Find a class\n");
		printf("6. Sort classes\n");
		printf("7. Count classes\n");
		printf("8. Save data\n");
		printf("9. Quit\n");
		printf("Enter command: ");

		scanf("%d", &choice);
		getchar();
		switch (choice)
		{
		case 1:
			printf("Enter filename: ");
			scanf("%s", filename);
			getchar();
			loadData(filename);
			break;
		case 2:
			printList();
			break;
		case 3:
			printf("Enter class code: ");
			fgets(class, MAX_L, stdin);
			if (class[strlen(class) - 1] == '\n')
				class[strlen(class) - 1] = '\0';

			printf("Enter course code: ");
			fgets(course, MAX_L, stdin);
			if (course[strlen(course) - 1] == '\n')
				course[strlen(course) - 1] = '\0';

			printf("Enter class schedule: ");
			fgets(schedule, MAX_L, stdin);
			if (schedule[strlen(schedule) - 1] == '\n')
				schedule[strlen(schedule) - 1] = '\0';

			insertLast(class, course, schedule);
			break;
		case 4:
			printf("Enter class code: ");
			fgets(class, MAX_L, stdin);
			if (class[strlen(class) - 1] == '\n')
				class[strlen(class) - 1] = '\0';

			removeProfile(class);
			break;
		case 5:
			printf("Enter course code: ");
			fgets(course, MAX_L, stdin);
			if (course[strlen(course) - 1] == '\n')
				course[strlen(course) - 1] = '\0';

			p = findProfile(course);
			if (p != NULL)
				printf("FOUND class:\n%s\n%s\n%s\n", p->class, p->course, p->schedule);
			else
				printf("NOT FOUND course %s\n", course);
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			printf("Enter filename: ");
			scanf("%s", filename);
			getchar();
			saveData(filename);
			break;
		case 9:
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

Profile *makeProfile(char *class, char *course, char *schedule)
{
	Profile *p = malloc(sizeof(Profile));
	strcpy(p->class, class);
	strcpy(p->course, course);
	strcpy(p->schedule, schedule);
	p->next = NULL;
	return p;
}

void insertLast(char *class, char *course, char *schedule)
{
	Profile *p = makeProfile(class, course, schedule);
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

	char class[MAX_L], course[MAX_L], schedule[MAX_L];
	while (!feof(f))
	{
		fgets(class, MAX_L, f);
		if (class[strlen(class) - 1] == '\n')
			class[strlen(class) - 1] = '\0';

		fgets(course, MAX_L, f);
		if (course[strlen(course) - 1] == '\n')
			course[strlen(course) - 1] = '\0';

		fgets(schedule, MAX_L, f);
		if (schedule[strlen(schedule) - 1] == '\n')
			schedule[strlen(schedule) - 1] = '\0';

		insertLast(class, course, schedule);
	}

	fclose(f);
}

void printList(void)
{
	for (Profile *p = first; p != NULL; p = p->next)
	{
		printf("%s\n%s\n%s\n", p->class, p->course, p->schedule);
	}
}

void removeProfile(char *class)
{
	Profile *p = NULL;
	Profile *tmp = NULL;
	Profile *prev = NULL;

	if (strcmp(first->class, class) == 0)
	{
		while (strcmp(first->class, class) == 0)
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
		if (strcmp(p->class, class) == 0)
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

Profile *findProfile(char *course)
{
	Profile *p = first;
	while (p != NULL)
	{
		if (strcmp(p->course, course) == 0)
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
		fprintf(f, "%s\n%s\n%s", p->class, p->course, p->schedule);
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