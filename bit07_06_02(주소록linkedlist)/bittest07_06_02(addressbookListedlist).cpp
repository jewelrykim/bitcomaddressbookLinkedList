#pragma warning(disable:4996)
#include <stdio.h>
#include <iostream>
#include <malloc.h>
#include <windows.h>
struct user
{
	char * name;		//�̸�
	char * address;	//�ּ�
	char * phonenum;	//��ȭ��ȣ
	struct user * pNext;
};
typedef struct Search
{
	user* data;
	user* pPre;
	struct Search * pNext;
};
void Nodememory(char* *data, char * title){
	char temp[1024];
	printf("%s", title);
	gets(temp);
	fflush(stdin);
	*data = (char *)malloc(strlen(temp) + 1);
	strcpy(*data, temp);
}
void Enter(user* *node){	//�Է¹޴��Լ�

	Nodememory(&(*node)->name, "�̸� : ");
	Nodememory(&(*node)->address, "�ּ� : ");
	Nodememory(&(*node)->phonenum, "��ȭ��ȣ : ");
}
void Print( user* node){							//����ϴ��Լ�
	printf("\n�̸� : %s\n", node->name);
	printf("�ּ� : %s\n", node->address);
	printf("��ȭ��ȣ : %s\n\n", node->phonenum);
}
void MultiPrint(Search* pSearch){
	while (pSearch != NULL)
	{
		Print(pSearch->data);
		pSearch = pSearch->pNext;
	}
}
void Insert(user* pNode, user* *pTop){
	pNode->pNext = NULL;
	if (*pTop == NULL)
	{
		*pTop = pNode;
	}
	else{
		user * pStart = *pTop;
		while (pStart->pNext != NULL)//����
		{
			pStart = pStart->pNext;
		}
		pStart->pNext = pNode;
	}
}
void MultiSearchInsert(Search* pNode, Search* *pTop){
	pNode->pNext = *pTop;
	*pTop = pNode;
}
void Input(user* *pTop){		//�Է��ϴ� �Լ�
		user *pNode = (user*)malloc(sizeof(user));
		Enter(&pNode);
		Insert(pNode, pTop);
}
void Output(user* pTop){				//����Լ�
	user *Node = (user*)malloc(sizeof(user));
	user *pStart = pTop;
	int count = 0;
	while(pStart != NULL)
	{
		Print(pStart);
		pStart = pStart->pNext;
		count++;
	}
	if (count == 0){
		printf("����ִ�.\n");
	}
}
user* SSearch(user* *pStart, user* *pPre, char* sear){
	while (*pStart != NULL){
		if (strcmp((*pStart)->name, sear) == 0){
			return *pStart;
		}
		*pPre = *pStart;
		(*pStart) = (*pStart)->pNext;
	}
	return NULL;
}
Search* MSearch(user* *pStart,Search* *pCtop, user* *pPre, char* sear){
	int count = 0;
	while (*pStart != NULL){
		if (strstr((*pStart)->name, sear) != NULL){
			Search* copy = (Search*)malloc(sizeof(Search));
			copy->pNext = NULL;
			copy->data = *pStart;
			copy->pPre = *pPre;
			MultiSearchInsert(copy, pCtop);
			count++;
		}
		*pPre = *pStart;
		(*pStart) = (*pStart)->pNext;
	}
	if (count == 0){
		return NULL;
	}
	else{
		return *pCtop;
	}
}
void SingleSearch( user* pTop,char* *errmsg){		//���ϰ˻��Լ�
	user* pPre = NULL;
	printf("�˻��ϰ� ���� ����� ��Ȯ�� �̸� : ");
	char sear[128] = { ' ' };//�˻��� �̸� ���庯��
	gets(sear);
	fflush(stdin);
	user* pSearch = SSearch(&pTop, &pPre, sear);
	if (pSearch == NULL)
	{
		printf("��ã�� \n");
	}
	else{
		Print(pSearch);
	}
}
void MultiSearch( user* pTop, char* *errmsg){			//���߰˻��Լ�
	printf("�˻��ϰ� ���� ����� �̸� : ");
	user* pPre = NULL;
	Search* pCopy;
	char sear[128] = { ' ' };//�˻��� �̸� ���庯��
	gets(sear);
	fflush(stdin);
	user* pStart = pTop;
	Search* pSearch = MSearch(&pStart, &pCopy, &pPre, sear);
	if (pSearch == NULL)
	{
		printf("��ã�� \n");
	}
	else{
		MultiPrint(pSearch);
	}
//	printf("%s", errmsg[]);
}
void Change(user* pNode ,char* *errmsg){		//�����Լ�( ��Ȯ�� ��ġ�ϴ� �̸��� ��������
	user* pPre = NULL;
	printf("�˻��� �� : ");
	char sear[128] = { ' ' };//�˻��� �̸� ���庯��
	gets(sear);
	fflush(stdin);
	user* pSearch = SSearch(&pNode, &pPre, sear);
	if (pSearch == NULL)
	{
		printf("��ã�� \n");
	}
	else{
		Enter(&pSearch);
		Print(pSearch);
	}
//	printf("%s", errmsg[]);
}
void DeleteAt(user* pStart, user* *pTop, user* *pPre){
	if (pStart == *pTop){
		*pTop = pStart->pNext;
	}
	else{
		(*pPre)->pNext = pStart->pNext;
	}
	free(pStart);
	printf("��������");
}
void SingleDelete(user* *pNode, char* *errmsg){		//���ϻ����Լ�
	user* pPre = NULL;

	printf("�����ϰ� ���� ����� ��Ȯ�� �̸� : ");
	char sear[128] = { ' ' };//�˻��� �̸� ���庯��
	gets(sear);
	fflush(stdin);

	user* pStart = *pNode;
	user* pSearch = SSearch(&pStart, &pPre, sear);

	if (pSearch == NULL)
	{
		printf("��ã�� \n");
	}
	else{
		DeleteAt(pStart, pNode, &pPre);
	}
	//printf("%s", errmsg[re]);
}
void MultiDelete(user* *pNode, char* *errmsg){		//���߻���
	user* pPre = NULL;

	printf("�����ϰ� ���� ����� ��Ȯ�� �̸� : ");
	char sear[128] = { ' ' };//�˻��� �̸� ���庯��
	gets(sear);
	fflush(stdin);

	user* pStart = *pNode;
	Search * pCopy = NULL;
	MSearch(&pStart, &pCopy, &pPre, sear);

	if (pCopy == NULL)
	{
		printf("��ã�� \n");
	}
	else{
		while (pCopy != NULL){
			DeleteAt(pCopy->data, pNode, &pCopy->pPre);
			pCopy = pCopy->pNext;
		}
	}
}
/*
void FilePrint(const user* arr, int count){
	FILE *fp;
	printf("�ּҷ��� �����մϴ�.\n");
	fp = fopen("addressbook.txt", "w");
	fprintf(fp, "%d\n");
	for (int index = 0; index < count; index++)
	{
		fprintf(fp, "%s\n%s\n%s\n", arr[index].name, arr[index].address, arr[index].phonenum);
	}
	fclose(fp);
}
char* FileDataScan(FILE * fp, char **pData){
	char temp[1024] = { " " };
	char* tester;
	tester = fgets(temp, 1024, fp);
	*pData = (char *)malloc(strlen(temp));
	strcpy(*pData, temp);
	(*pData)[strlen(temp) - 1] = NULL;
	return tester;
}
void FileScan(user* arr,  int *count){
	FILE *fp;
	fp = fopen("addressbook.txt", "r");
	if (fp == NULL)
		printf("�ּҷ��� �����ϴ�.");
	else{
		printf("�ּҷ��� �о�ɴϴ�.\n");
		fscanf(fp, "%d\n", usermax);
		int index = 0;
		free(arr);
		arr = (user *)malloc(sizeof(user)* (*usermax));
		while (!feof(fp))
		{
			if (FileDataScan(fp, &arr[index].name) == NULL)break;
			FileDataScan(fp, &arr[index].address);
			FileDataScan(fp, &arr[index].phonenum);
			index++;

		}
		*count = index;
	}
	fclose(fp);
}*/
void main()
{
	char mode = '1';// mode�� ��弳�� ����
	user* pTop=NULL;
	int count = 0; //������ �˷��ִ� ����
	char * SearchErrMsg[] = { "ã�⼺��", "���� ��ϵ� �����Ͱ� �����ϴ�.", "ã������ �����Ͱ� �������� �ʽ��ϴ�." };
	char * ChangeErrMsg[] = { "ã�⼺��", "��ϵ� �����Ͱ� �����ϴ�.", "ã������ �����Ͱ� �������� �ʽ��ϴ�." };
	char * DeleteErrMsg[] = { "��������", "���� ��ϵ� �����Ͱ� �����ϴ�.", "ã������ �����Ͱ� �������� �ʽ��ϴ�." };
	while (mode != '0'){
		printf("\nmode ���� ( 1 = �Է� , 2 = ��� , 3 = ���ϰ˻�(��Ȯ�� �̸�), 4 = ���߰˻�(���Ե� ����), 5= ����(��Ȯ�� �̸�), 6 = ���ϻ���(��Ȯ�� �̸�), 7 = ���߻���(���Ե� ����), 8 = ��������, 9 = ���Ϸε� 0 = ����) \n");
		mode = getchar();
		fflush(stdin);

		switch (mode)
		{
		case '1':	//�Է�
			Input(&pTop);
			break;
		case '2':	//���
			Output(pTop);
			break;
		case '3':	//���ϰ˻�
			SingleSearch(pTop, SearchErrMsg);
			break;
		case '4':	//���߰˻�
			MultiSearch(pTop,SearchErrMsg);
			break;
		case '5':	// ����
			Change(pTop, ChangeErrMsg);
			break;
			
		case '6':	// ���ϻ���
			SingleDelete(&pTop,  DeleteErrMsg);
			break;
		case '7':	//���߻���
			MultiDelete(&pTop, DeleteErrMsg);
			break;
		case '8':/*
			FilePrint(pTop, count);
			break;
		case '9':
			FileScan(pTop,  &count);
			break;*/
		default:
			mode = '0';
			break;
		}
	}
}