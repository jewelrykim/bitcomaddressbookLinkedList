#pragma warning(disable:4996)
#include <stdio.h>
#include <iostream>
#include <malloc.h>
#include <windows.h>
struct user
{
	char * name;		//이름
	char * address;	//주소
	char * phonenum;	//전화번호
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
void Enter(user* *node){	//입력받는함수

	Nodememory(&(*node)->name, "이름 : ");
	Nodememory(&(*node)->address, "주소 : ");
	Nodememory(&(*node)->phonenum, "전화번호 : ");
}
void Print( user* node){							//출력하는함수
	printf("\n이름 : %s\n", node->name);
	printf("주소 : %s\n", node->address);
	printf("전화번호 : %s\n\n", node->phonenum);
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
		while (pStart->pNext != NULL)//연결
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
void Input(user* *pTop){		//입력하는 함수
		user *pNode = (user*)malloc(sizeof(user));
		Enter(&pNode);
		Insert(pNode, pTop);
}
void Output(user* pTop){				//출력함수
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
		printf("비어있다.\n");
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
void SingleSearch( user* pTop,char* *errmsg){		//단일검색함수
	user* pPre = NULL;
	printf("검색하고 싶은 사람의 정확한 이름 : ");
	char sear[128] = { ' ' };//검색할 이름 저장변수
	gets(sear);
	fflush(stdin);
	user* pSearch = SSearch(&pTop, &pPre, sear);
	if (pSearch == NULL)
	{
		printf("못찾음 \n");
	}
	else{
		Print(pSearch);
	}
}
void MultiSearch( user* pTop, char* *errmsg){			//다중검색함수
	printf("검색하고 싶은 사람의 이름 : ");
	user* pPre = NULL;
	Search* pCopy;
	char sear[128] = { ' ' };//검색할 이름 저장변수
	gets(sear);
	fflush(stdin);
	user* pStart = pTop;
	Search* pSearch = MSearch(&pStart, &pCopy, &pPre, sear);
	if (pSearch == NULL)
	{
		printf("못찾음 \n");
	}
	else{
		MultiPrint(pSearch);
	}
//	printf("%s", errmsg[]);
}
void Change(user* pNode ,char* *errmsg){		//수정함수( 정확히 일치하는 이름만 수정가능
	user* pPre = NULL;
	printf("검색할 값 : ");
	char sear[128] = { ' ' };//검색할 이름 저장변수
	gets(sear);
	fflush(stdin);
	user* pSearch = SSearch(&pNode, &pPre, sear);
	if (pSearch == NULL)
	{
		printf("못찾음 \n");
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
	printf("삭제성공");
}
void SingleDelete(user* *pNode, char* *errmsg){		//단일삭제함수
	user* pPre = NULL;

	printf("삭제하고 싶은 사람의 정확한 이름 : ");
	char sear[128] = { ' ' };//검색할 이름 저장변수
	gets(sear);
	fflush(stdin);

	user* pStart = *pNode;
	user* pSearch = SSearch(&pStart, &pPre, sear);

	if (pSearch == NULL)
	{
		printf("못찾음 \n");
	}
	else{
		DeleteAt(pStart, pNode, &pPre);
	}
	//printf("%s", errmsg[re]);
}
void MultiDelete(user* *pNode, char* *errmsg){		//다중삭제
	user* pPre = NULL;

	printf("삭제하고 싶은 사람의 정확한 이름 : ");
	char sear[128] = { ' ' };//검색할 이름 저장변수
	gets(sear);
	fflush(stdin);

	user* pStart = *pNode;
	Search * pCopy = NULL;
	MSearch(&pStart, &pCopy, &pPre, sear);

	if (pCopy == NULL)
	{
		printf("못찾음 \n");
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
	printf("주소록을 저장합니다.\n");
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
		printf("주소록이 없습니다.");
	else{
		printf("주소록을 읽어옵니다.\n");
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
	char mode = '1';// mode는 모드설정 변수
	user* pTop=NULL;
	int count = 0; //개수를 알려주는 변수
	char * SearchErrMsg[] = { "찾기성공", "삭제 등록된 데이터가 없습니다.", "찾으려는 데이터가 존재하지 않습니다." };
	char * ChangeErrMsg[] = { "찾기성공", "등록된 데이터가 없습니다.", "찾으려는 데이터가 존재하지 않습니다." };
	char * DeleteErrMsg[] = { "삭제성공", "삭제 등록된 데이터가 없습니다.", "찾으려는 데이터가 존재하지 않습니다." };
	while (mode != '0'){
		printf("\nmode 선택 ( 1 = 입력 , 2 = 출력 , 3 = 단일검색(정확한 이름), 4 = 다중검색(포함된 글자), 5= 수정(정확한 이름), 6 = 단일삭제(정확한 이름), 7 = 다중삭제(포함된 글자), 8 = 파일저장, 9 = 파일로드 0 = 종료) \n");
		mode = getchar();
		fflush(stdin);

		switch (mode)
		{
		case '1':	//입력
			Input(&pTop);
			break;
		case '2':	//출력
			Output(pTop);
			break;
		case '3':	//단일검색
			SingleSearch(pTop, SearchErrMsg);
			break;
		case '4':	//다중검색
			MultiSearch(pTop,SearchErrMsg);
			break;
		case '5':	// 수정
			Change(pTop, ChangeErrMsg);
			break;
			
		case '6':	// 단일삭제
			SingleDelete(&pTop,  DeleteErrMsg);
			break;
		case '7':	//다중삭제
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