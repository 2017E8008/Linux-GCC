//�¶�����   �ӽ��̱�init�й�
#include "func.h"
int main(){
		pid_t pid;
		pid=fork();
		if(pid==0){
			//	printf("child pid=%d ppid=%d\n",getpid(),getppid());
				sleep(5);
				printf("alone pid=%d initpid=%d\n",getpid(),getppid());
				return 0;
		}else{ //�Ƚ��븸����
				printf("parent pid=%d ",getpid());
				return 0;
		}
}


//��ʬ���� Z  �ӽ����˳�PCBȴ�����ͷ�
#include"func.h"
int main(){
		pid_t pid ;
		pid=fork();
		if(pid==0){
				printf("zombie pid=%d ppid=%d\n",getpid(),getppid());
				return 0;
		}else{
				while(1);
				return 0;
		}
}
