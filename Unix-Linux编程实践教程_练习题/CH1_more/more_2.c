
// ʹ�� c�⺯��ʵ�� more����******�汾1
// /dev/tty�ļ� ��ȡ��������,���Ǵ�stdin��ȡ�û�����=�������ض��� ��stdin����Ĵ���ҳ���ݡ��û��������� ֮������

#include <stdio.h>
#include <stdlib.h>
#define PAGELEN 24
#define LINELEN 512
void do_more(FILE *);
int see_more();

int main(int argc,char** argv){
	FILE * fp;
	if(argc == 1){
		//fputs(k,STDOUT_FILENO);   //fputs (const char *__restrict __s, FILE *__restrict __stream)  c�⺯���Ľӿ�
		do_more( stdin );  //stdin ��stdout ���ļ�ָ�롣STDOUT_FILENO���ļ�������
	}
	else{ 
		fp = fopen(argv[1],"r");
		do_more(fp);
		fclose(fp);
	}
	return 0;
}

void do_more(FILE * fp){
	char line[LINELEN];
	int num_of_lines = 0;
	int reply;
	FILE	*fp_tty;
	fp_tty = fopen( "/dev/tty", "r" );	  
	if ( fp_tty == NULL )	exit(1);  
	
	while(fgets(line,LINELEN,fp)){
		if(fputs(line , stdout) == EOF)     
			exit(0);
		if(num_of_lines == PAGELEN){        //һҳչʾ��,�ȴ��û�����
			reply = see_more(fp_tty);           //see_more ��ȡ�û�����,������Ҫչʾ������
			//printf("reply = %d\n",reply);
			if(reply == 0)
				break;    //exit(0)
			num_of_lines -= reply;
		}

		num_of_lines ++;
	}
}

int see_more(FILE *tty){
	int c;
	//printf(" [more?] ");
	printf("\033[7m more? \033[m");
	while(( c = getc(tty)) != EOF){            //while �������ÿһ���ַ��������ж�
		if(c == 'q') {printf("q\n"); return 0;}    //do_more exit
		if(c == ' ')  {printf("space \n"); return PAGELEN;}
		if(c == '\n') {printf("n \n"); return 1;}
	}
	return 0;
}

/* ע�ͣ�
	1.ÿ����Ȼ��Ҫ enter����Ϊ���������־
	2.�����ַ�ʱ��ÿһ���ַ��������ж�,��Ȼÿ���� \n ����
	3.�����argc==1ʱ����stdin��ȡ����  =>  �Ӷ��ܹ�֧�ֹܵ����ض���
	���磺 who | more  ����ִ��
	
	4./dev/tty�ļ� ��ֹ�ض��� more���޷����� ����ҳ���ݡ��û��������� ֮������
	=�� ����/dev/ttyд,��ζ����Ļ��ʾ  ��/dev/tty��,��ȡ��������
*/

/*
       #include <stdio.h>

       int fgetc(FILE *stream);

       char *fgets(char *s, int size, FILE *stream);

       int getc(FILE *stream);

       int getchar(void);

       int ungetc(int c, FILE *stream);

*/