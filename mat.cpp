#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>

using namespace std;



int o(){
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
			scanf_s ("%d", &mat[a_i][a_j], sizeof(int));
		}
		for (int a_j = 0; a_j < n; a_j++){
			printf("%d \t", mat[a_i][a_j]);
			printf("\n");
		}
	}
	return 0;
}