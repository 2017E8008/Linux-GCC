//tcp Э��ʵ�� server client�˵Ĵ������Ϣͨ��
//server = socket������  bind��ip+�˿ں�  listen�򿪶˿�   accpet�����ȴ�client����
//client = socket������  connect����serverip+�˿ں�
//server client ʹ��send recv ͨ��

//server��
#include "func.h"
int main(int argc,char** argv){
		int sfd=socket(AF_INET,SOCK_STREAM,0);
		struct sockaddr_in server;
		memset(&server,0,sizeof(server));
		server.sin_family=AF_INET;
		server.sin_addr.s_addr=inet_addr(argv[1]);
		server.sin_port=htons(atoi(argv[2]));
		bind(sfd,(struct sockaddr*)&server,sizeof(server));

		listen(sfd,10);
		struct sockaddr_in client;
		memset(&client,0,sizeof(client));
		int len=sizeof(client);
		while(1){
				int cfd=accept(sfd,(struct sockaddr*)&client,&len);
				printf("client add=%s,client port=%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
				char buf[128]={0};
                send(cfd,"hello",10,0);
				recv(cfd,buf,sizeof(buf),0);
				printf("from client=%s\n",buf);
			//	printf("server send success\n");
		}
		return 0;
}


//client��
#include "func.h"
int main(int argc,char** argv){
		int cfd;
		cfd=socket(AF_INET,SOCK_STREAM,0);
		struct sockaddr_in client;
		memset(&client,0,sizeof(client));
		client.sin_family=AF_INET;
		client.sin_addr.s_addr=inet_addr(argv[1]);
		client.sin_port=htons(atoi(argv[2]));
		connect(cfd,(struct sockaddr*)&client,sizeof(client));
		char buf[128]={0};
        recv(cfd,buf,sizeof(buf),0);
		send(cfd," world\n",10,0);
		printf("from server=%s\n",buf);
		return 0;
}

