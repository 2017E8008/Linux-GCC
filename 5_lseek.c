#include "func.h"
int main(int argc,char** argv){
		int fd;
        //��֤�ļ�����,��ʱmode_t ����umaskӰ��
		fd=open(argv[1],O_RDWR|O_CREAT|O_TRUNC,0664);
		int ret=lseek(fd,10240000,SEEK_SET);
		printf("ret=%d\n",ret);
		char *buf=malloc(sizeof(char)*100);	
		write(fd,"h",1);
		close(fd);
		return 0;
}
