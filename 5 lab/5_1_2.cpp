#include<iostream>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
using namespace std;

#define N 25
int a[N];
sem_t Sem;

void* ThreadFunc(void*){
	int pause;	
	for(int i=0;i<N;i++){
		sem_wait(&Sem);
		cout<<" "<<a[i]<<" ";	
		sem_post(&Sem);
		for(long j=0;j<1000000;j++) pause++;
		
	}
	cout<<endl;
	
	return 0;
}

int main(){
	sem_init(&Sem,0,1);
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
		sem_wait(&Sem);
		cout<<" "<<a[i]<<" ";
		sem_post(&Sem);
		for(long j=0;j<1000000;j++) pause++;
	}
	cout<<endl;
		
	pthread_join(Thread,NULL);

	sem_destroy(&Sem);
return 0;
}
