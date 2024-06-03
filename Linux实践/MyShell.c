#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include <stdlib.h>
#include <string.h>

char gpath[80] = "/home/s2021013064/shixi/";

int getml(char* command_list[],char* input)
{
    int command_count = 0;

    char* token = strtok(input, "|");
    while (token != NULL)
    {
        while (*token == ' ') {
            token++;
        }
        char* end = token + strlen(token) - 1;
        while (*end == ' ' || *end == '\n') {
            *end = '\0';
            end--;
        }

        strcpy(command_list[command_count],token);
        command_count++;

        token = strtok(NULL, "|");
    }

        return command_count;
}


void chuli(char* command_list[],char* ml)
{
    int command_count = 0;

  
    char* token = strtok(ml, " ");
    while (token != NULL) {

        while (*token == ' ') {
            token++;
        }
        char* end = token + strlen(token) - 1;
        while (*end == ' ' || *end == '\n') {
            *end = '\0';
            end--;
        }

        strcpy(command_list[command_count],token);
        command_count++;

        token = strtok(NULL, " ");
    }
  
    command_list[command_count] = NULL;
}

void chulicdx(char* tar,int ge)
{
	char t[80];
	char filepath[80];
	strcpy(t,tar);
	int count = 0;
	char* command[10];
	char* ml[10];
	int k=0;
	for(;k<10;++k)
	{
		command[k] = (char*)malloc(80 * sizeof(char));
		ml[k] = (char*)malloc(80 * sizeof(char));
	}
	char* com;
	if(ge == 2)
	{
		com = strtok(t,">");
		strcpy(command[count++],com);
		com = strtok(NULL,">");
		strcpy(filepath,com);
	}
	else
	{
		com = strtok(t,"<");
		strcpy(command[count++],com);
		com = strtok(NULL,"<");
		strcpy(filepath,com);
	}
	char* to = filepath;
	
        while (*to == ' ') 
	{
           	to++;
       	}
        char* end = to + strlen(to) - 1;
        while (*end == ' ' || *end == '\n') 
	{
            	*end = '\0';
            	end--;
        }


	int fd;
	chuli(ml,command[0]);
	if(access(to,F_OK) == 0)
	{
		fd = open(to,O_RDWR);
	}
	else
	{
		perror("文件不存在\n");
		return;
	}
	int sfd0 = dup(0);
	int sfd1 = dup(1);

	pid_t pid = fork();
	if(pid < 0)
	{
		perror("进程创建错误2\n");
	}
	if(pid == 0)
	{

		if(ge == 2)
		{	
			dup2(fd,1);
		}
		else
		{
			dup2(fd,0);
		}

		execvp(ml[0],ml);
		
		if(ge == 2)
			dup2(sfd1,1);
		else 
			dup2(sfd0,0);
	}
	else
	{
		wait(NULL);
	}
}

void channal(char str[])
{
	int fd[2];
	int sfd0 = dup(0);
	int sfd1 = dup(1);

	if(pipe(fd))
	{
		perror("创建管道失败\n");
		exit(1);
	}

	fcntl(fd[0],F_SETFL,O_NONBLOCK);

	char* com[10];
        int k=0;
        for(;k<10;++k)
        {
                com[k] = (char*)malloc(80 * sizeof(char));
        }
        int num = getml(com,str);
        char ch1[80],ch2[80];

	char* ml1[10];
	char* ml2[10];
      	for(k=0;k<10;++k)
	{
         	ml1[k] = (char*)malloc(80 * sizeof(char));
         	ml2[k] = (char*)malloc(80 * sizeof(char));
	}
        strcpy(ch1,com[0]);
	strcpy(ch2,com[1]);
        chuli(ml1,ch1);
	chuli(ml2,ch2);
	

/*	pid_t p = fork();
	if(p < 0)
	{
		perror("创建进程失败2\n");
		return;
	}else if(p==0){

*/	pid_t pid = fork();
	if(pid <  0)
	{
		perror("创建进程失败\n");
		exit(1);
	}
	
	if(pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		execvp(ml1[0],ml1);
		close(fd[1]);
		dup2(sfd1,1);
	}
	else
	{
		dup2(fd[0], 0);
		close(fd[1]);
		wait(NULL);
		//execvp(ml2[0],ml2);
		system(com[1]);
		close(fd[0]);
		dup2(sfd0,0);
	}
	for(k=0;k<10;++k)
	{
		free(ml1[k]);
		free(ml2[k]);
	}
	dup2(sfd1,1);
/*	}
	else{
		wait(NULL);
		close(fd[0]);
		close(fd[1]);
	}*/
}

void houtai(char str[])
{
	char str2[80];
	strcpy(str2,str);

	char* com[10];
        int k=0;
        for(;k<10;++k)
        {
                com[k] = (char*)malloc(80 * sizeof(char));
        }
	chuli(com,str);
	
	pid_t pid = fork();
        if(pid <  0)
        {
                perror("创建进程失败\n");
                exit(1);
        }
        else if(pid == 0)
        {
                
                execvp(com[0],com);
        }
        else
        {
		printf("程序已经挂入后台\n");
	}		
}

int jiance(const char str[],char* ta)
{
	if(strchr(str,'|') != NULL)
	{
		return 1;
	}
	else if(strchr(str,'>') != NULL)
	{
		return 2;
	}
	else if(strchr(str,'<') != NULL)
	{
		return 3;
	}
	else
	{
	       	char* pos = strchr(str,'&');
		if(pos != NULL)
		{
			*pos = '\0';
			return 4;
		}
	}

	char* ml1 = strtok(str," ");
	char* ml2 = strtok(NULL," ");
/*
	char cmd[strlen(gpath)+strlen(ml1)+3];
	sprintf(cmd,"%s%s",gpath,ml1);
	
	if(access(cmd,F_OK) == 0)
	{
		if(ml2 != NULL)
		{
			strcat(cmd," ");
			strcat(cmd,ml2);
		}
		system()
		pid_t pid = fork();
		if(pid < 0)
		{
			perror("创建进程失败\n");
			return;
		}
		else if(pid == 0)
		{
			system(cmd);
		}
		else
		{
			wait(NULL);
		}

		return 6;
	}

*/
	if(ml1 != NULL && ml2 == NULL)
	{
		if(strcmp(ml1,"exit") == 0)
		{
			strcpy(ta,ml1);
			return 8;
		}
		else
		{
			strcpy(ta,ml1);
			return 5;
		}
	}
	
	char* ml3 = strtok(NULL," ");
	if(ml1 != NULL && ml2 != NULL && ml3 == NULL)
	{
		if(strcmp(ml1,"cd") == 0)
		{
			strcpy(ta,ml2);
			return 6;
		}
		else if(strcmp(ml1,"path")==0)
		{
			strcpy(gpath,"");
			strcpy(ta,ml2);
			return 7;
		}
		else
		{
			return 9;
		}
	}

	return 0;
}

void name()
{
	char n[80];
	char* n1 = getlogin();
	char n2[80];
	char n3[80];
	if(gethostname(n2,80) != 0)
	{
		perror("获取主机名失败\n");
		return;
	}
	if(getcwd(n3,80) == NULL)
	{
		perror("获取目录名失败\n");
		return;
	}
	strcat(n,"[");
	strcat(n,n1);
	strcat(n,"@");
	strcat(n,n2);
	strcat(n,":");
	strcat(n,n3);
	strcat(n,"]#");
	printf("%s",n);
}

int main()
{
	int tui = 1;
	while(tui)
	{
		char input[80];
		char target[80];
		char beif[80];
		int a;
		name();
		fgets(input,80,stdin);
		strcpy(beif,input);
		input[strlen(input)-1] = '\0';
		switch(jiance(input,target))
		{
		case 1: channal(input);break;
		case 2: chulicdx(input,2);break;
		case 3: chulicdx(input,3);break;
		case 4:	houtai(input);break;
		case 5: system(target);break;
		case 6: chdir(target);break;
		case 7: strcpy(gpath,target);printf("path:%s\n",gpath);break;
		case 8: tui = 0;break;
		case 9: system(beif);break;
		case 0: printf("无效命令\n");break;
		}
	}

	exit(0);
}
