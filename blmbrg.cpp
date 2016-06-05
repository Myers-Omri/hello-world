#include "stdio.h"
#include "string.h"
#include "conio.h"
#include <iostream>
#include <time.h>
using namespace std;









typedef enum { SUCCESS,MEM_FAIL, NULL_PTR, ALREADY_EXIST} ListResult;
typedef enum { F, D } DfType;

struct df_t {
	char* name;
	DfType type; // D:dir F:file
	struct df_t* childListHead;
	struct df_t* parent;
	struct df_t* left;
	struct df_t* right;

};


typedef df_t DF;


ListResult putName(char* newName, DF* df);

DF* GetNewDF(char* name, DfType t);

char rootName[] = "root";
DF* Root = GetNewDF(rootName, D);

DF* currentFolder = Root;



int compareStrings(char* s1, char* s2) {
	int si = 0, flag = 0;
	while (s1[si] != '\0' && s2[si]!='\0' )
	{
		if (s1[si] > s2[si]) {
			flag = 1;
			break;
		}
		if (s1[si] < s2[si]) {
			flag = -1;
			break;
		}
		si++;
	}
	if (s1[si] == '\0' && s2[si] != '\0') flag = -1;
	if (s1[si] != '\0' && s2[si] == '\0') flag = 1; // checks if the end of s1 and not s2 

	return flag;
}


DF* find(char* name, DfType t) {
	DF* cNode = currentFolder->childListHead;
	if (cNode == NULL) return NULL;
	while (cNode != NULL) {
		if (compareStrings(name, cNode->name) == 0 && t==cNode->type) {
			return cNode;
		}
		cNode = cNode->right;
	}
	return NULL;

}

ListResult isertTochildList(DF* newDF) { //TODO:need to sort !!
	
	if (currentFolder->childListHead == NULL) {
		currentFolder->childListHead = newDF;
		return SUCCESS;
	}
	if (compareStrings(newDF->name, currentFolder->childListHead->name) < 0){
		currentFolder->childListHead->left = newDF;
		newDF->right = currentFolder->childListHead;
		currentFolder->childListHead = newDF;
		return SUCCESS;
	}
	DF* cNode = currentFolder->childListHead;
	while (cNode != NULL) {
		int c = compareStrings(newDF->name, cNode->name);
		int c2 = 0;
		if (c >= 0){   // || (c == 0  && newDF->type > cNode->type)) {
			if (cNode->right != NULL) {
				c2 = compareStrings(newDF->name, cNode->right->name);
			}
			if (c2 < 0 || cNode->right == NULL) {
				newDF->right = cNode->right;
				newDF->left = cNode;
				if (cNode->right != NULL) {
					cNode->right->left = newDF;
				}

				cNode->right = newDF;
				return SUCCESS;
			}

			
		}
		
		cNode = cNode->right;
	}
	 
	return SUCCESS;
}


ListResult creatAtCurrent(char* name, DfType t) {
	if (find(name, t) != NULL) {
		return ALREADY_EXIST;
	}
	DF* newDF = GetNewDF(name, t);
	newDF->parent = currentFolder;
	isertTochildList(newDF);
	return SUCCESS;
}


void recPrint(DF* r, DF* Parent, int d) {
	if (r == NULL) {
		if (Parent == Root) {
			return;
		}
		recPrint(Parent->right, Parent->parent, d - 1);	
		if (r==NULL) return;
	}
	for (int i = 0; i < d; i++) {
		printf("\t");
	}
	printf("%s \n", r->name);
	
	recPrint(r->childListHead, r, d + 1);
	
}


void recDelete(DF* r, DF* Parent) {
	if (r == NULL) {
		if (Parent == Root) {
			return;
		}
		recDelete(Parent->right, Parent->parent);
		if (r == NULL) return;
	}
		
	recDelete(r->childListHead, r);
	printf("\n deleted %s", r->name);
	free(r);

}

void printTree() {
	DF* head = Root;
	printf("\n");
	recPrint(Root,Root->parent, 0);

}



void cd(char *inp)
{
	if (compareStrings(inp, "cd..") == 0) {
		if (currentFolder == Root) return;
		currentFolder = currentFolder->parent;
		return;
	}
	DF* temp_curr = find(inp, D);
	if (temp_curr == NULL) {
		printf("\n not exist\n");
		return;
	}
	currentFolder = temp_curr;
	printf("\n change dir\n");
}


void recPwd(DF* c) {
	if (c == NULL) {
		return;
	}
	recPwd(c->parent);
	printf("%s\\", c->name);

}

void pwd()
{
	recPwd(currentFolder);
	
	
	printf("\n print current dir\n");
}

void mkdir(char *inp)
{
	printf("\n add dir");
	if (find(inp, D) != NULL) {
		printf("\n already exist \n");
		return;
	}

	creatAtCurrent(inp, D);
	printf("\n dir was added under %s\n", currentFolder->name);
}
	


void mkfile(char *inp)
{
	
	if (find(inp, F) != NULL) {
		printf("\n ****already exist *****\n");
		return;
	}

	creatAtCurrent(inp, F);
	printf("\n file was added under %s\n", currentFolder->name);
}

void print()
{
	printf("\n printing  dir tree");


	printTree();
	printf("\n print dir tree");
}



void test_cmpStr() {
	char s1[] = "aabbc";
	char s2[] = "bbbbb";
		if (compareStrings(s1, s2) != -1) {
			printf("fail -1");
		}
		char s3[] = "aabbc";
		char s4[] = "aabbcbb";
		if (compareStrings(s3, s4) != -1) {
			printf("fail -1");
		}
		char s5[] = "aabbb";
		char s6[] = "aabbb";
		if (compareStrings(s5, s6) != 0) {
			printf("fail 0");
		}
		char s7[] = "aacb";
		char s8[] = "aabbb";
		if (compareStrings(s7, s8) !=1) {
			printf("fail 1");
		}
		char s9[] = "aabbbb";
		char s10[] = "aabbb";
		if (compareStrings(s9, s10) != 1) {
			printf("fail 1");
		}

}

int menu()
{
	printf("\n\n 1. change dir"); //done
	printf("\n 2. print current dir"); //done
	printf("\n 3. add dir"); //done
	printf("\n 4. add file"); //done
	printf("\n 5. print dir tree"); 
	printf("\n 6. exit");
	printf("\n What would you like to do: ");
	int i = _getch() - '0';
	return i;
}


int main(int argc, char* argv[])
{
	
	
	char inp[100];
	int i = 0;
	while (true)
	{
		i = menu();
		switch (i)
		{
		case 1:
			printf("\nEnter subdir: ");
			scanf("%s", inp);
			cd(inp);
			break;
		case 2:
			pwd();
			break;
		case 3:
			printf("\nEnter new subdir: ");
			scanf("%s", inp);
			mkdir(inp);
			break;
		case 4:
			printf("\nEnter new filename: ");
			scanf("%s", inp);
			mkfile(inp);
			break;
		case 5:
			print();
			break;
		case 6:
			recDelete(Root, NULL);


			return 0;
		}
	}
	
	return 0;
}



ListResult putName(char* newName, DF* df) { //TODO:
	int len = 0;
	int i = 0;
	if (newName == NULL) return NULL_PTR; //error
	while (newName[len] != '\0') { //check len of string
		len += 1;
	}
	len += 1;
	char* name = (char*)malloc(sizeof(name)*len);
	if (name == NULL) return MEM_FAIL;
	for (int j = 0;j < len; j++) {
		name[j] = newName[j];
	}
	df->name = name;
	return SUCCESS;
}

DF* GetNewDF(char* name, DfType t) {
	DF* newDF
		= (DF*)malloc(sizeof(DF));
	if (newDF == NULL) {
		return NULL;
	}

	putName(name, newDF);
	newDF->type = t;
	newDF->childListHead = NULL;
	newDF->parent = NULL;
	newDF->left = NULL;
	newDF->right = NULL;

	return newDF;
}
