#include <unistd.h>
#include <sys/types.h>
#include <semaphore.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SEM_NAME_1 "/semaphore1"
#define SEM_NAME_2 "/semaphore2"
int main(){
    int fd;
    char str[20];
    int size = sizeof(str);
    char path[] = "./file.txt";
    sem_t *semaphore1 = sem_open(SEM_NAME_1, O_CREAT, 0777, 0);
    sem_t *semaphore2 = sem_open(SEM_NAME_2, O_CREAT, 0777, 0);
    for(int i = 0; i < 5; i++){
        sem_wait(semaphore2);
        if((fd = open(path, O_RDWR)) < 0){
            printf("Error!\n");
            return -1;
        }
        read(fd, &str, size);
        close(fd);
	char nc,minc='a',maxc='z'; 
	int n;   
        printf("Prog2 gets : %s\n", str);
	n=atoi(str);
        for(int i=0;i<n;i++){
	   nc = rand() % (maxc-minc + 1) + minc;
	   printf("%c ",nc);
	}
	      printf("\n\n");
        sleep(1);
        sem_post(semaphore1);
    }
    sem_unlink(SEM_NAME_1);
    sem_unlink(SEM_NAME_2);
    return 0;
}

