#include <unistd.h>
#include <sys/types.h>
#include <semaphore.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#define SEM_NAME_1 "/semaphore1"
#define SEM_NAME_2 "/semaphore2"
int main(){
    int fd,r;
    char a;
    char str[20];
    srand(42);
    int size;
    char path[] = "./file.txt";
    sem_t *semaphore1 = sem_open(SEM_NAME_1, O_CREAT, 0777, 0);
    sem_t *semaphore2 = sem_open(SEM_NAME_2, O_CREAT, 0777, 0);
    sem_post(semaphore1);
// Создаем файл
    if((fd = open(path,O_WRONLY | O_CREAT | O_TRUNC, 0777)) < 0){
        printf("Error!\n");
        return -1;
    }
    (void)umask(0);
    printf("Enter the symbol: ");
    scanf("%s", &a);
    r=10 + rand() %20; 
    sprintf(str, "%d", r);
    size= sizeof(str);
    printf("Prog1 sends %s\n\n", str);
    write(fd, &str, size);
    close(fd);
    str[20]="";
    sem_post(semaphore2);
     for(int i = 0; i < 2; i++){
	
        sem_wait(semaphore1);
        if((fd = open(path, O_RDWR)) < 0){
            printf("Error!\n");
            return -1;
        }
        printf("Enter the symbol: ");
        scanf("%s", &a);
        r=10+ rand() %20;  //исходное число 
        sprintf(str, "%d", r);
        size= sizeof(str);
        printf("Prog1 sends %s\n\n", str);
        write(fd, &str, size);
        close(fd);
	str[20]="";
        sem_post(semaphore2);
    }sleep(2);
    sem_unlink(SEM_NAME_1);
    sem_unlink(SEM_NAME_2);
    return 0;
}

