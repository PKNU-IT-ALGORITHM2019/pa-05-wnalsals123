#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define WORD_LENGTH 100
#define BUFFER_LENGTH 200

typedef struct Dict {
	char word[WORD_LENGTH];
	char cls[WORD_LENGTH];
	char mean[BUFFER_LENGTH];
	
}Dict;

typedef struct tree {		// 영어 사전 이진 트리의 노드 구조를 정의
	Dict key;
	tree *left;		// 왼쪽 트리에 대한 링크
	tree *right;		// 오른쪽 트리에 대한 링크
} tree;

FILE *fp;
Dict w;
tree *root = NULL;

void load()
{
	char buffer[BUFFER_LENGTH];

	while (1) {
		printf("$ read ");
		scanf("%s", buffer);
		getchar();
		fp = fopen(buffer, "r");
		if (fp == NULL)
			printf("\t파일을 찾을 수 없습니다.\n");
		else {
			printf("\t파일을 불러왔습니다.\n");
			return;
		}
	}
}

void load(char *p)
{
	fp = fopen(p, "r");
	if (fp == NULL) {
		printf("\t파일을 찾을 수 없습니다.\n");
		return;
	}
	else {
		printf("\t파일을 불러왔습니다.\n");
		return;
	}
}

void insert(tree **root, Dict x) {
	tree *nNode;
	tree *qNode = NULL;
	tree *pNode = *root;

	while (pNode != NULL) {
		qNode = pNode;
		if (strcmp(x.word, pNode->key.word) < 0)
			pNode = pNode->left;
		else if (strcmp(x.word, pNode->key.word) >= 0)
			pNode = pNode->right;
	}

	nNode = (tree*)malloc(sizeof(tree));
	nNode->key = x;
	nNode->left = NULL;
	nNode->right = NULL;

	if (qNode != NULL) {
		if (strcmp(x.word, qNode->key.word) < 0) 
			qNode->left = nNode;
		else if (strcmp(x.word, qNode->key.word) >= 0)
			qNode->right = nNode;
	}
	else 
		*root = nNode;
}

void find(tree *root, char *p)
{
	while (root != NULL) {
		if (strcmp(p, root->key.word) == 0) {
			printf("\tmeaning: %s\n", root->key.mean);
			return;
		}
		else if (strcmp(p, root->key.word) < 0)
			root = root->left;
		else if (strcmp(p, root->key.word) > 0)
			root = root->right;
	}
	printf("\tNot found!\n");
	return;
}

int save()
{
	char line[2000];
	int Nword = 0, cls_s, cls_e, n = 0;

	while (fgets(line, 2000, fp)) {
		strtok(line, " ");
		strcpy(w.word, line);
		for (int i = 0; i < 2000; i++) {
			if (line[i] == '(')
				cls_s = i;
			if (line[i] == ')') {
				cls_e = i;
				break;
			}
		}
		for (int i = cls_s; i < cls_e + 1; i++)
			w.cls[n++] = line[i];
		w.cls[n] = '\0';
		n = 0;
		for(int i = cls_e + 2; line[i] != '\0'; i++)
			w.mean[n++] = line[i];
		w.mean[n] = '\0';
		n = 0;
		insert(&root, w);
		Nword++;
	}
	return Nword;
}

int add()
{
	printf("\tword: ");
	gets_s(w.word);
	printf("\tclass: ");
	gets_s(w.cls);
	printf("\tmeaning: ");
	gets_s(w.mean);
	insert(&root, w);
	return 1;
}

int del(tree **root, char *p)
{
	tree *parent = NULL;
	tree *pNode = *root;
	tree *child;
	tree *succ, *succ_parent;

	while ((pNode != NULL) && (strcmp(p, pNode->key.word) != 0)) {
		parent = pNode;
		if (strcmp(p, pNode->key.word) < 0)
			pNode = pNode->left;
		else 
			pNode = pNode->right;
	}

	if (pNode == NULL) {
		printf("\tNot found!\n");
		return 0;
	}

	if ((pNode->left == NULL) && (pNode->right == NULL)) {
		if (parent != NULL) {
			if (parent->left == pNode) parent->left = NULL;
			else parent->right = NULL;
		}
		else root = NULL;
	}
	else if ((pNode->left == NULL) || (pNode->right == NULL)) {
		if (pNode->left != NULL)
			child = pNode->left;
		else 
			child = pNode->right;
		if (parent != NULL) {
			if (parent->left == pNode) parent->left = child;
			else parent->right = child;
		}
		else 
			*root = child;
	}
	else {
		succ_parent = pNode;
		succ = pNode->left;
		while (succ->right != NULL) {
			succ_parent = succ;
			succ = succ->right;
		}
		if (succ_parent->left == succ)
			succ_parent->left;
		else 
			succ_parent->right = succ->left;
		pNode->key = succ->key;
		pNode = succ;
	}
	printf("\tDeleted successfully!\n");
	return 1;
}

int del_A(char *p)
{
	char buffer[WORD_LENGTH];
	int n = 0 ;
	load(p);

	while (fscanf(fp, "%s", buffer) != EOF)
		n = n + del(&root, buffer);
	printf("\t%d words were deleted successfully!\n", n);
	return n;
}

int main()
{
	int size;
	char command[BUFFER_LENGTH], *moon;

	load();
	size = save();

	while (1) {
		printf("$ ");
		gets_s(command, sizeof(command));

		if (strcmp(command, "size") == 0)
			printf("\t%d개\n", size);
		else if (strcmp(command, "add") == 0)
			size = size + add();
		else if (strcmp(command, "exit") == 0)
			break;
		else {
			strtok(command, " ");
			moon = strtok(NULL, "\0");
			if (strcmp(command, "find") == 0 && moon != NULL)
				find(root, moon);
			else if (strcmp(command, "delete") == 0 && moon != NULL)
				size = size - del(&root, moon);
			else if (strcmp(command, "deleteall") == 0 && moon != NULL)
				size = size - del_A(moon);
			else
				printf("\t잘못된 입력입니다.\n");
		}
	}
	return 0;
}