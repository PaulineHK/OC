#include<iostream>
#include<unistd.h>
#include<pthread.h>

using namespace std;

#define N 25
int a[N];
pthread_mutex_t Mutex;

void* ThreadFunc(void*){
	int pause;
	
	for(int i=0;i<N;i++){
		pthread_mutex_lock(&Mutex);
		cout<<" "<<a[i]<<" ";
		pthread_mutex_unlock(&Mutex);
		for(long j=0;j<1000000;j++) pause++;		
	}
	cout<<endl;
	
	
	return 0;
}

int main(){
	Mutex=PTHREAD_MUTEX_INITIALIZER;
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
		pthread_mutex_lock(&Mutex);
		cout<<" "<<a[i]<<" ";
		pthread_mutex_unlock(&Mutex);
		for(long j=0;j<1000000;j++) pause++;
		
	}
	cout<<endl;
		
	pthread_join(Thread,NULL);

	pthread_mutex_destroy(&Mutex);
return 0;
}
