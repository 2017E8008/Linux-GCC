//udpͨ��   selectģ��
//server��
#include "func.h"
int main(int argc,char **argv){
	int sfd;
	sfd=socket(AF_INET,SOCK_DGRAM,0);
	struct sockaddr_in ser;
	memset(&ser,0,sizeof(ser));
	ser.sin_family=AF_INET;
	ser.sin_port=htons(atoi(argv[2]));
	ser.sin_addr.s_addr=inet_addr(argv[1]);
	int ret;
	ret=bind(sfd,(struct sockaddr*)&ser,sizeof(ser));  //�󶨶˿�  sfd+sockaddr_in

	char buf[128]={0};
	struct sockaddr_in cli;
	memset(&cli,0,sizeof(cli));
	int len=sizeof(cli);
    //serverֻ����recvfrom �õ����ݰ�;����client socket
	ret=recvfrom(sfd,buf,sizeof(buf),0,(struct sockaddr*)&cli,&len);
	printf("client addr=%s,client port=%d\n",inet_ntoa(cli.sin_addr),ntohs(cli.sin_port));
    fd_set rdset;

	while(1){
	    FD_ZERO(&rdset);
	    FD_SET(0,&rdset);
	    FD_SET(sfd,&rdset);
		ret=select(10,&rdset,NULL,NULL,NULL);
		if(FD_ISSET(sfd,&rdset)){
            memset(buf,0,sizeof(buf));
            ret=recvfrom(sfd,buf,sizeof(buf),0,(struct sockaddr*)&cli,&len);
	        if(ret>0){
				printf("client: %s\n",buf);
			   // printf("client addr=%s,client port=%d\n",inet_ntoa(cli.sin_addr),ntohs(cli.sin_port));
	        }else if(ret==0){
                printf("bye bye\n");
            }				
		}
		if(FD_ISSET(0,&rdset)){
			memset(buf,0,sizeof(buf));
			read(0,buf,sizeof(buf));   //���͵�client
	        sendto(sfd,buf,strlen(buf)-1,0,(struct sockaddr*)&cli,len);
	    }
	//close(sfd);  //Ӧ�����˲���ı�
	}
	return 0;
}
	
//client��
#include "func.h"
int main(int argc,char* argv[])
{
	int sfd;
	sfd=socket(AF_INET,SOCK_DGRAM,0);
	
	struct sockaddr_in ser;
	memset(&ser,0,sizeof(ser));
	ser.sin_family=AF_INET;
	ser.sin_port=htons(atoi(argv[2]));
	ser.sin_addr.s_addr=inet_addr(argv[1]);
	int ret;
	int len=sizeof(ser);
	//�ͻ����ȷ���
	ret=sendto(sfd,"connect",10,0,(struct sockaddr*)&ser,len);
	
	char buf[128]={0};
	struct sockaddr_in cli;    //��������recvfrom��������
	memset(&cli,0,sizeof(cli));
	fd_set rdset;

	while(1){
		FD_ZERO(&rdset);
        FD_SET(0,&rdset);
	    FD_SET(sfd,&rdset);
		ret=select(sfd+1,&rdset,NULL,NULL,NULL);
		if(FD_ISSET(sfd,&rdset)){
	        memset(buf,0,sizeof(buf));
	        recvfrom(sfd,buf,sizeof(buf),0,(struct sockaddr*)&cli,&len);
	        printf("server: %s\n",buf);
		}
		if(FD_ISSET(0,&rdset)){
			memset(buf,0,sizeof(buf));
			read(0,buf,sizeof(buf));  //������server
	        sendto(sfd,buf,strlen(buf)-1,0,(struct sockaddr*)&ser,len);
	    }
	}
	close(sfd);
	return 0;
}
