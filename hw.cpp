#include <stdio.h> // for printf, scanf
#include <cstdio> 
#include <stdlib.h> //
#include <string.h>
#include <iostream>
#include <istream>
#include <string>
#include <string.h>
#include <typeinfo.h>


using namespace std;


int mat(){
	int n;

	scanf_s("%d", &n, sizeof(int));
	int** mat = (int**)malloc(n*sizeof(int));
	for (int i = 0; i < n; i++){
		mat[i] = (int*)malloc(n*sizeof(int));

	}

	//cin >> n;
	//vector< vector<int> > a(n, vector<int>(n));
	for (int a_i = 0; a_i < n; a_i++){
		for (int a_j = 0; a_j < n; a_j++){
			scanf_s("%d", &mat[a_i][a_j], sizeof(int));
		}
		
	}
	printf("the mat is: \n");
	int md = 0, sd = 0;
	for (int a_i = 0; a_i < n; a_i++){
		for (int a_j = 0; a_j < n; a_j++){
			printf("%d \t", mat[a_i][a_j]);
			if (a_i == a_j){
				md += mat[a_i][a_j];
			}
			if (a_i == n - 1 - a_j){
				sd += mat[a_i][a_j];
			}
		}
		printf("\n");
	}
	printf("abs diff is: %d", (md<=sd ? sd-md : md-sd));
	//printf("sd is: %d", sd);
	return 0;
}

void q1(){
	char abc[27];
	char *ptr = abc;
	strcpy_s(abc, sizeof(abc), "abcdefxyz");
	printf("%s", ptr);


	// 1. abc
	// 2. ptr
	// 3. &abc[4]
	// 4. abc + 4
	// 5. *abc[4] + 2
	// 6. &ptr
	// 7. *(abc + 4)
	// 8. abc + 4
	// 9. abc[27]
	cout << abc << typeid(abc).name() << endl;
	cout << ptr << typeid(ptr).name() << endl;
	cout << &abc[4] << typeid(&abc[4]).name() << endl;
	cout << abc + 4 << typeid(abc + 4).name() << endl;

}

string getH(string &t){
	char c0 = t[0], c1 = t[1];

	int tNum = atoi(&c0) * 10 + atoi(&t[1]);
	if (t[8] == 'P'){
		if (tNum != 12){
			tNum += 12;
		}
	}
	else{
		if (tNum == 12){
			tNum = 0;
		}
	}
	

	t[0] = '0' + tNum / 10;
	t[1] = '0' + tNum % 10;
	return t;

}

int timefix(){

		int hh, mm, ss;
		char t12[3];
		scanf_s("%d:%d:%d%s", &hh, &mm, &ss, t12, sizeof(t12));

		if (strcmp(t12, "PM") == 0 && hh != 12) hh += 12;
		if (strcmp(t12, "AM") == 0 && hh == 12) hh = 0;

		printf("%02d:%02d:%02d", hh, mm, ss);
		return 0;
	

}

int ** anothe2d(int r_n, int c_n){
	int ** rows = (int**)malloc(sizeof(int**) * (r_n)+1);
	rows[0] = (int *)r_n;
	if (rows == NULL) return NULL;
	for (int i = 1; i <= r_n; i++){
		rows[i] = (int*)malloc(sizeof(int*)*c_n);
		if (rows[i] == NULL){
			for (int j = 0; j < i; j++){
				free(rows[j]);
			}
			free(rows);
			return NULL;
		}
	}
	return rows+1;
}

void remfree(int** arrrrrr){
	int nrows = (int)(arrrrrr[-1]);
	for (int i = 0; i < nrows; i++){
		free(arrrrrr[i]);
		printf("frreeeeing rows");
	}
	int ** frp = arrrrrr;
		free(frp);
	printf("freed alll");
}

int** arr2D(int r_num, int c_num){
	int rows = r_num*sizeof(int*);
	int data = r_num * c_num*sizeof(int*);
	int** arr = (int**)malloc( data + rows);
	if (arr == NULL){
		return NULL;
	}
	int* head = (int*)(arr + r_num);
	for (int i = 0; i < r_num; i++){
		arr[i] = head + (i*c_num);
	}
	return arr;
	//in this case we can just use free to delete the srray
}


int mainw(void){
	/*char buff[80];
	scanf_s("%[^\n]s", buff, sizeof(char) * 79);
	printf("%s \n", buff);
	
	printf("hello world \n");*/

	//mat();
	/*string tt = "07:17:53PM";
	getH(tt);
	for (int i = 0; i < 8; i++){
		printf("%c", tt[i]);
	}
	printf("\n");*/
	//timefix();
	int rw = 7;
	int cl = 5;
	//int** ar2d2 = arr2D(rw, cl);
	int** ar2d2 = anothe2d(rw, cl);
	for (int i = 0; i < rw; i++){
		for (int j = 0; j < cl; j++){
			ar2d2[i][j] = i + j;
		}

	}
	for (int i = 0; i < rw; i++){
		for (int j = 0; j < cl; j++){
			printf("%d \t", ar2d2[i][j]);
		}
		printf("\n");
	}
	//free(ar2d2);
	remfree(ar2d2);
	system("pause");
	return 0;
}