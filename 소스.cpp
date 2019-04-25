#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define NWORD 200000
#define BUFFER_LENGTH 100

typedef struct Dict {
	char word[BUFFER_LENGTH];
	char *mean;
}Dict;

FILE *fp;
Dict book[NWORD];
int size = 0;

void load()
{
	char buffer[BUFFER_LENGTH];

	while (1) {
		printf("$ read ");
		scanf("%s", buffer);
		getchar();
		fp = fopen(buffer, "r");
		if (fp == NULL)
			printf("������ ã�� �� �����ϴ�.\n");
		else {
			printf("������ �ҷ��Խ��ϴ�.\n\n");
			return;
		}

	}
}

void save()
{
	char moon[2000];
	int ok = 0;

	while (!feof(fp)) {
		fgets(moon, 2000, fp);
		if (moon[0] == '\n')
			continue;

		while (moon[ok] != '(')
			ok++;
		ok--;

		book[size].mean = strdup(moon);
		moon[ok] = '\0';
		strcpy(book[size].word, moon);
		size++;
		ok = 0;
	}
}

void find(int first, int last, char *sword)
{
	// �����˻�Ž��
}

void add(int first, int last, char *sword)
{
	// �߰�
}

void del(int first, int last, char *sword)
{
	// ����
}

void del_A(int first, int last, char *sword)
{
	// ��ü����
}

int main()
{
	char command[BUFFER_LENGTH];
	char *moon;

	load();
	save();

	while (1) {
		printf("$ ");
		gets_s(command, sizeof(command));

		if (strcmp(command, "size") == 0)
			printf("%d\n", size);
		else if (strcmp(command, "exit") == 0)
			break;
		else {
			strtok(command, " ");
			if (strcmp(command, "find") == 0) {
				moon = strtok(NULL, "\0");
				find(0, size, moon);
			}
			else
				printf("�߸��� �Է��Դϴ�.\n\n");
		}
	}

	return 0;
}