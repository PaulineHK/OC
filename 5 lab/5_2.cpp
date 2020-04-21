#include<iostream>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<signal.h>

using namespace std;

sem_t Semaphore;
sem_t empty;
sem_t wait;
int m;
pthread_t cook;                                                         
        
void* Cannibal(void* arg){
	int name=*(int*)arg;
	while(1){
		sem_wait(&Semaphore);
		if(m==0){
			sem_post(&empty);
            cout<<"Жду повара "<<name<<endl;
			sem_wait(&wait);
			cout<<name<<" ест"<<endl;
			m--;
		}else{
			cout<<name<<" ест"<<endl;
			m--;	
		}
		sem_post(&Semaphore);
        sleep(0);
	}
	return NULL;
}

void* Cook(void* arg){
    int meat=*(int*)arg;
	int i;
	while(1){
		sem_wait(&empty);
		cout<<"Готовлю еду"<<endl;
		for(i=0; i<100000000; i++);
		m=meat;	
		sem_post(&wait);
	}	
	return NULL;
}

int main(){
	setlocale(LC_ALL,"RUS");
	
	int n, p;
	cout<<getpid()<<endl;
	cout<<"Количество дикарей: ";
	cin>>n;
	cout<<"Количество мяса: ";
	cin>>m;
	
	int name[n];
	sem_init(&Semaphore,0,1);
	sem_init(&empty,0,0);
	sem_init(&wait,0,0);
	pthread_create(&cook, NULL, Cook, &m);
	
	cout<<"Время работы: ";
	cin>>p;
	
	pthread_t* cannibals=new pthread_t[n];
	int i;
	for(i=0;i<n;i++){
		name[i]=i;
		int create = pthread_create(&cannibals[i], NULL, Cannibal, &name[i]);
		if(create!=0){
			cout<<"ERROR: "<<i<<endl;
		}
	}
	sleep(p);
    
	for(i=0;i<n;i++){
		pthread_kill(cannibals[i],SIGTERM);
	}
	pthread_kill(cook, SIGTERM);
	delete[] cannibals;	
    sem_destroy(&Semaphore);
	sem_destroy(&empty);
	sem_destroy(&wait);
	return 0;
}
