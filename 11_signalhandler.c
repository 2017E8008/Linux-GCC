#include "func.h"


void sig(int signum)
{
// ͬһ���ź������ִ������
	printf("before sleep,I am signal %d\n",signum);
	sleep(3);
	printf("after sleep,I am signal %d\n",signum);
}
int main()
{
	//����2��3���źţ���Ӧͬһ��handle����
	signal(SIGINT,sig);
	signal(SIGQUIT,sig);
	while(1);
}

