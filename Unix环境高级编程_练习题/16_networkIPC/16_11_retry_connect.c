//��������������ڸ��غ��ص�ϵͳ֮��,client���ܷ���˲ʱconnect ����
//ָ�������㷨 exponential backoff
#include "apue.h"
#include <sys/socket.h>
#define MAXSLEEP 128
int connect_retry(int domain,int type,int protocol,const struct sockaddr *addr,socklent_t len){
	int numsec,fd;
	//��������
	for(numsec=1;numsec<=MAXSLEEP;numsec <<=1){
		if((fd=socket(domain,type,protocol))<0) return -1;   
	
    	if(connect(fd,addr,alen)==0){
			//connection accepted
			return fd;         //success ���������ӵ�socket������
		}
		//connect false �ȹرձ���fd,����������(BSD,MACϵͳ����ظ�����ʱ��Ȼ����ԭ���׽��ֻ�ʧ��)
		close(fd);
		
		//delay before trying again
		if(numsec<=MAXSLEEP/2)
			sleep(numsec);
	}
	return -1;        //������Ȼδ���ӳɹ�
}