#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;

    pid = fork();
    if (pid == 0){
        execl("./register", "register", NULL);
        perror("register");
        exit(1);
    }
    pid = fork();
    if (pid == 0){
        execl("./login", "login", NULL);
        perror("login");
        exit(1);
    }
    pid = fork();
    if (pid == 0){
        execl("./add_friend", "add_friend", NULL);
        perror("add_friend");
        exit(1);
    }
    pid = fork();
    if (pid == 0){
        execl("./talk", "talk", NULL);
        perror("talk");
        exit(1);
    }
    pid = fork();
    if (pid == 0){
        execl("./record", "record", NULL);
        perror("record");
        exit(1);
    }

    int ret;

    while (1) {
        ret = wait(NULL);
        if (ret < 0) {
            break;
        }
    }

    return 0;    
}





