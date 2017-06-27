//waitpid ������������
#include "func.h"
int main()
{
	pid_t pid;
	pid=fork();
	if(!pid)
	{
		printf("child pid=%d,ppid=%d\n",getpid(),getppid());
		return 5;			
	}else{
		printf("parent pid=%d\n",getpid());
		int status;
		pid_t cpid;
		while(1)
	   {//һֱ�ȴ��ӽ��̵��˳�
        //waitpid �����������ߵ�ִ�У��൱�ڼ�������
			cpid=waitpid(pid,&status,WNOHANG);
			printf("wait child...%d\n",cpid);
			if(cpid!=0)
			{
				break;
			}
		}
		if(WIFEXITED(status))   //����  ���ӽ��������˳�
		{
			printf("the child exit value=%d\n",WEXITSTATUS(status));   //��ӡ�ӽ���returnֵ
		}else{
			printf("child crash\n");
		}
		return 0;
	}
}

