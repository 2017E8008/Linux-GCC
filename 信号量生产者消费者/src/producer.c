#include "func.h"
//������

int sem_id;
struct sembuf sop[2];
void init();
void delete();
int main(){
	init();
	while(1){
		//printf("producer number:%d\n",semctl(sem_id,1,GETVAL));
		//printf("space number%d\n",semctl(sem_id,0,GETVAL));
		semop(sem_id,&sop[0],1);    //p -1 �ֿ�ʣ��ռ��1 
		printf("produceing....\n");
		semop(sem_id,&sop[1],1);    // V +1   ��Ʒ������1
		printf("producer number:%d\n",semctl(sem_id,1,GETVAL));
		printf("space number%d\n",semctl(sem_id,0,GETVAL));
		printf("\n");
	    sleep(2);
		signal(SIGINT,delete);    //����ctrl+c ��Ǵ�ɾ���ź������˳���ǰ����
	}
}
void init(){
	sem_id = semget(1234,2,IPC_CREAT|0600);
	unsigned short sem_array[2]={10,0};   //��Ʒ����=0  �ֿ�ռ�=10
	int ret = semctl(sem_id,0,SETALL,sem_array);
	printf("producer init %d\n",semctl(sem_id,1,GETVAL));
	printf("space number init %d\n",semctl(sem_id,0,GETVAL));
	
	memset(&sop[0],0,sizeof(struct sembuf));
	memset(&sop[1],0,sizeof(struct sembuf));
	sop[0].sem_num=0;    //0���ź���,�ֿ�ʣ������,p����
	sop[0].sem_op=-1;
	sop[0].sem_flg=SEM_UNDO;
	sop[1].sem_num=1;    //1���ź���,��Ʒ����,v����
	sop[1].sem_op=1;
	sop[1].sem_flg=SEM_UNDO;
}
void delete(){
	semctl(sem_id,IPC_RMID,0);
	kill(getpid(),SIGQUIT);
}