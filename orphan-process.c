#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

const int MSG_LENGTH=80;
int main(int argc, char** argv) 
{
    pid_t child_pid, my_pid,parent_pid;
    char message[MSG_LENGTH];
    int count;

    child_pid = fork();
    parent_pid = getppid();
    my_pid = getpid();

    char buf[BUFSIZ];

    printf("Till now worked one proccess.\n");
switch (child_pid) {
    case -1:
        perror("Forking didnt worked.\n");
        exit(1);
    case 0:
        snprintf(message,MSG_LENGTH,"I am child, child PID = %d, my PID=%d, parent PID =%d",\
        child_pid,my_pid,parent_pid);
        count = 5;
    break;
    default:
        snprintf(message,MSG_LENGTH,"I am parent, child PID =%d, my PID=%d, parent PID =%d",\
        child_pid,my_pid,parent_pid);
        count = 5;
    break;
}
   

for (; count > 0; count--) {
    puts(message);
        if(count==3 && child_pid!=0 && child_pid>0){//parent process is killed
            sprintf(buf,"ps -ef | grep orphan-process | grep %d | grep -v grep",child_pid);
            system(buf);
            printf("Parent dies.\n");
            exit(0);
        }
    sleep(1);
}

if(child_pid==0){//child is killed before program ends
        sprintf(buf,"ps -ef | grep orphan-process | grep %d | grep -v grep",child_pid);
        system(buf);
    printf("Child dies.\n");
    exit(0);
}
}