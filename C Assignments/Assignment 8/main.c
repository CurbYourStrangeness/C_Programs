#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define COMMAND_LEN 255

int main(int args, char* argv[]) {
    long size;
    char *buf;
    char *ptr = NULL;
    char str[100];

    char *cmd1;  
    char *cmd2;  
    do{
        pid_t pid;
        if (pid == 0 || pid == -1) {
            break;
        }


        size = pathconf(".", _PC_PATH_MAX);
        if ((buf = (char *)malloc((size_t)size)) != NULL)
            ptr = getcwd(buf, (size_t)size);
        printf("%s ?",ptr);
        fgets(str, COMMAND_LEN, stdin);
        printf(" %s ", str);



        if (strcmp(str,"exit\n")==0){
            printf("Exiting...\n");
            exit(1);
        }
        else {

            cmd1 = strtok(str, " "); 
            cmd2 = strtok(NULL, " ");

            cmd1 = strtok(cmd1, "\n");
            cmd2 = strtok(cmd2, "\n");

            printf("cmd1: %s  cmd2: %s \n\n ", cmd1, cmd2);



            if(strcmp(cmd1,"multi")==0){
                printf("Goes to multi \n");
                parse_file(cmd2);

            }
            else{
                process(cmd1, cmd2);
            }
        }
    }while (1);

}

int parse_file(char* cmd2){
    char* cmd1;

    printf("%s", cmd2);

    int x;
    x=strcmp(cmd2, "names.txt");
    printf("%d", x);

    FILE* fin;
    fin = fopen("names.txt", "r");
    if (fin == NULL)
    {
        printf("\n fileopen failed\n");
        exit(1);
    }else {
        const int BUFSIZE = 1024;
        char str2[BUFSIZE];
        printf("file index: \n");

        while (!feof(fin)) {

            printf("%s", str2);
            fgets(str2, BUFSIZE, fin);

            cmd1 = strtok(str2, " "); 
            cmd2 = strtok(NULL, " ");

            cmd1 = strtok(cmd1, "\n");
            cmd2 = strtok(cmd2, "\n");

            printf("cmd1: %s  cmd2: %s \n\n ", cmd1, cmd2);

            process(cmd1, cmd2);

        }

        fclose(fin);
    }
}

pid_t process(char *cmd1, char *cmd2) {
    int totes;

    pid_t pid = fork();

    if (pid == 0) // child
    {
        execlp(cmd1, cmd1, cmd2, (char*) 0);
    } else if (pid > 0) // parent
    {
        wait(&totes);
    } else 
    {
        printf("Unfortunate fork() error");
        exit(1);
    }
    return pid;
}
