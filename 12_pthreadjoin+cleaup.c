//create �������̲߳��� ����join�������̻߳�ȡ����ֵ
#include "func.h"
void* func(void *p){
		long *p1;
		p1=(long*)p;
        printf("i=%ld\n",*p1);
		(*p1)++;
		pthread_exit((void*)*p1);
       // pthread_exit(p1);
}
int main(){
		pthread_t pthid;
		long i=1;
		pthread_create(&pthid,NULL,func,&i);
		pthread_join(pthid,(void**)&i);
		printf("final=%ld\n",i);
}



//���߳�read ��cancelnation point �ǻᱻpthread_cancel����ͬʱ�ᱻpthread_cleanup ������Դ������
#include "func.h"
void cleanup1(void* p)
{
	printf("start cleanup\n");
	free(p);
	printf("cleanup over\n");
}

void* threadfunc(void *p)
{
	char *p1;
	printf("child thread,please input something\n");
	p1=(char*)malloc(20);
	pthread_cleanup_push(cleanup1,p1);
	read(0,p1,sizeof(p1));    //���ﱻcancel���������޷���ִ��
    //ҵ���߼�
	pthread_exit((void*)5);
	pthread_cleanup_pop(1);
	printf("see me?\n");
}
//���̱߳�cancel,���̻߳������߳���Դ
int main()
{
	pthread_t pthid;
	int ret;
	ret=pthread_create(&pthid,NULL,threadfunc,NULL);
    sleep(1);   //��֤���߳��Ѿ�����
	ret=pthread_cancel(pthid);	
	long l=0;
	pthread_join(pthid,(void**)&l);
	printf("I am main thread,chid exit=%ld\n",l);
	return 0;
}
