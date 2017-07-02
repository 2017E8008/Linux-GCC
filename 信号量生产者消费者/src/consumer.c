#include "func.h"
//������
//���������ĸ���
int sem_id;
struct sembuf sop[2];
void init();
void delete();
int main(){
	init();
	while(1){
		//printf("producer number:%d\n",semctl(sem_id,1,GETVAL));
		//printf("space number%d\n",semctl(sem_id,0,GETVAL));
		semop(sem_id,&sop[1],1);    //p -1 ��Ʒ������1 
		printf("consume....\n");
		semop(sem_id,&sop[0],1);    // V +1   �ֿ�ʣ��ռ��1
		printf("producer number:%d\n",semctl(sem_id,1,GETVAL));
		printf("space number%d\n",semctl(sem_id,0,GETVAL));
		printf("\n");
	    sleep(1);
		signal(SIGINT,delete);    //����ctrl+c ��Ǵ�ɾ���ź������˳���ǰ����
	}
}
void init(){
    //�ź�����ʼ����producer�н���
	sem_id = semget(1234,2,IPC_CREAT|0600);   //ʹ�ù����ź���,��ʹ��setval;
	printf("producer init %d\n",semctl(sem_id,1,GETVAL));
	printf("space number init %d\n",semctl(sem_id,0,GETVAL));
	
	memset(&sop[0],0,sizeof(struct sembuf));
	memset(&sop[1],0,sizeof(struct sembuf));
	sop[0].sem_num=0;    //0���ź���,�ֿ�ʣ��ռ�,v����
	sop[0].sem_op=1;
	sop[0].sem_flg=SEM_UNDO;
	sop[1].sem_num=1;    //1���ź���,��Ʒ����,p����
	sop[1].sem_op=-1;
	sop[1].sem_flg=SEM_UNDO;
}
void delete(){
	semctl(sem_id,IPC_RMID,0);
	kill(getpid(),SIGQUIT);
}