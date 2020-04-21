#include<pthread.h>
#include<iostream>
#include<unistd.h>
#include<stdio.h>
#include<vector>
using namespace std;

int n;

vector<vector<int>> matrix1, matrix2, matrix3;

void* fun(void* arg){
	int m=*(int*)arg;
for(int i=0;i<n;i++){
	matrix3[m][i]=matrix1[m][i]+matrix2[m][i];
}
return NULL;
}

vector<vector<int>> add(int m, int n, int p){
vector<vector<int>> a(m);
for(int i=0; i<m;i++){
	a[i].resize(n);
	for(int j=0;j<n;j++){
		a[i][j]=p;
		cout<<a[i][j]<<" ";
		if(p!=0)
		p++;
	}
	cout<<endl;
}
return a;
}


int main(){
int m,i,j;
cout<<"Размер матрицы:\nm: ";
cin>>m;
cout<<"n: ";
cin>>n;
	cout<<"m1"<<endl;
matrix1=add(m,n,1);
	cout<<"m2"<<endl;
matrix2=add(m,n,2);
	cout<<"m3"<<endl;
matrix3=add(m,n,0);
cout<<endl;
pthread_t* thread=new pthread_t[m];
int number[m];
for(i=0;i<m;i++){
	number[i]=i;
	pthread_create(&thread[i], NULL, &fun, &number[i]);
}
for(i=0;i<m;i++){
pthread_join(thread[i],NULL);
}

for(i=0;i<m;i++){
	for(j=0;j<n;j++){
		cout<<matrix3[i][j]<<" ";
	}
	cout<<endl;
}

cout<<endl;
int ok=1;
for(i=0;i<m;i++){
	for(j=0;j<n;j++){
		if(matrix3[i][j]!=(matrix1[i][j]+matrix2[i][j])){
			cout<<matrix3[i][j]<< " and "<<matrix1[i][j]+matrix2[i][j]<<endl;
			cout<<"1) "<<matrix1[i][j]<<"     2) "<<matrix2[i][j]<<endl;
			sleep(1);
			ok=0;
			break;
		}
	}
}
if(ok!=1)
	cout<<"Неверно"<<endl;
else cout<<"Верно"<<endl;
return 0;
}
