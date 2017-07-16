#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <shadow.h>
#include <errno.h>
#include <crypt.h>

void help(void)
{
	printf("�û�������֤����\n ��һ������Ϊ�û���!\n");
	exit(-1);
}
void error_quit(char *msg)
{
	perror(msg);
	exit(-2);
}
void get_salt(char *salt,char *passwd)
{
	int i,j;
//ȡ��salt,i ��¼�����ַ��±�,j ��¼$���ִ���
	for(i=0,j=0;passwd[i] && j != 3;++i)
	{
		if(passwd[i] == '$')
			++j;
	}
	strncpy(salt,passwd,i-1);
	printf("salt %s\n",salt);
}
int main(int argc,char **argv)
{
    struct spwd *sp;
    char *passwd;
	char salt[512]={0};
	if(argc != 2)
	help();
	//�����û�������
	passwd=getpass("����������:");
	//�õ��û����Լ�����,�����в����ĵ�һ������Ϊ�û���
	if((sp=getspnam(argv[1])) == NULL)                    //�����û�����ȡ spwd�ṹ��(ͨ����ȡ/etc/shadow�ļ�)
	error_quit("��ȡ�û���������");
	get_salt(salt,sp->sp_pwdp);                           //��spwd�ṹ���ж�ȡ��ֵ
	//����������֤
	if(!strcmp(sp->sp_pwdp,crypt(passwd,salt)))       //salt+�������� SHA-512���� �ж��Ƿ�ʹ洢������
		printf("��֤ͨ��!\n");
	else
		printf("��֤ʧ��!\n");
	return 0;
}