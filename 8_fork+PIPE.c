//  �ӽ���д  �����̶�
#include "func.h"

int main()
{
		int fds[2];
		int i;
		pid_t pid;
		pipe(fds);
		pid=fork();
		if(pid==0)
		{
				close(fds[0]);//�رն���
				char buf[50]="hello,cuixuange";
				write(fds[1],buf,sizeof(buf));
                printf("child is writing...\n");
				sleep(3);
                printf("child wtite done\n");
				exit(0);
		}else{
				close(fds[1]);//�ر�д��
				wait(NULL);   //���𸸽��̣��ȴ��ӽ���д��� 
				char buf[50]={0};
				read(fds[0],buf,sizeof(buf));
				printf("child=%d\n",pid);
				puts(buf);
				return 0;
		}
}

//   �ӽ��̶�  ������д
#include "func.h"
//  ������д    �ӽ��̶�
int main()
{
		int fds[2];
		int i;
		pipe(fds);
		if(!fork())
		{
				close(fds[1]);//�ر�д��,�ñ�֤�ñ�֤�ñ�֤�ر�˳��
				char buf[20]={0};
				read(fds[0],buf,sizeof(buf));
				puts(buf);
				exit(0);
		}else{
				close(fds[0]);//�رն���
				write(fds[1],"I am parent",11);
				wait(NULL);   //���𸸽��̵ȴ��ӽ��̵����
				return 0;
		}
}

