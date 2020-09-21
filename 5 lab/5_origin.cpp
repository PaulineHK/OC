#include<iostream>
#include<unistd.h>
#include<pthread.h>

using namespace std;
/*
Критическим ресурсом будет являться глобальный массив, 
к которому обращаются 2 потока, а критическими секциями - 
где как-то с эти ресурсом взаимодействуем.
Без синхронизации потоков числа будут выводится в беспорядке, 
но у меня только если убрать циклы с паузой, а если с ними, 
то только первые элементы неровно выводятся: "  0 0 1 1 ..."
*/
#define N 25
int a[N];//критический ресурс
pthread_mutex_t Mutex;

void* ThreadFunc(void*){
	int pause;

	for(int i=0;i<N;i++){
		//критическая секция
		cout<<" "<<a[i]<<" ";
		//критическая секция
		for(long j=0;j<1000000;j++) pause++;
	}
	cout<<endl;

	return 0;
}

int main(){
	pthread_t Thread;
	int pause;
	int res;

	for(int i=0;i<N;i++)
		a[i]=i;
	res=pthread_create(&Thread,NULL, ThreadFunc,NULL);
	if(res!=0){
		cerr<<"Ошибка при создании потока"<<endl;
		cin.get();
		return 0;
	}
	for(int i=0; i<N; i++){
		//критическая секция
		cout<<" "<<a[i]<<" ";
		//критическая секция
		for(long j=0;j<1000000;j++) pause++;
	}
	cout<<endl;

	pthread_join(Thread,NULL);

return 0;
}

