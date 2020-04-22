#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>

    /// Обработчик сигналов
    void handler(int i)
    {
    signal(SIGUSR1, handler);
    printf("\nРодительский процесс отправил SIGUSR1 дочернему!\n\n");
    }

    int main()
    {
        pid_t result;
        char a[] = "2";
        char b[] = "3";
        char c[] = "4";
        (void)umask(0); //Обнуление маски создания файлов
        //Порождение нового процесса
        if ((result = fork()) < 0)
        {
        // Если создать процесс не удалось, сообщаем об этом и завершаем работу
        printf("Can\'t fork child\n");
        exit(-1);
        }

        //Родительский процесс
        else if (result > 0)
        {
            key_t ipckey1;
            int mq_id1;
            struct { long type; char text[20]; } mymsg;
            ipckey1 = ftok("laba6.c", 42);
            mq_id1 = msgget(ipckey1, IPC_CREAT | 0666);
            /* Send a message */
            memset(mymsg.text, 0, 20);
            strcpy(mymsg.text, "_");
            mymsg.type = 1;
            msgsnd(mq_id1, &mymsg, sizeof(mymsg), 0);

        write(mq_id1, &a, strlen(a));
        printf("a-> %s\n", a);
        write(mq_id1, &b, strlen(b));
        printf("b-> %s\n", b);
        write(mq_id1, &c, strlen(c));
        printf("c-> %s\n", c);
sleep(1);
 printf("Завершился родительский процесс");
        close(mq_id1);
        }

        //Дочерний процесс
        else
        {
            key_t ipckey2;
            int mq_id2;
            struct { long type; char text[20]; } mymsg;
            int received;
            ipckey2 = ftok("laba6.c", 42);
            mq_id2 = msgget(ipckey2, 0);
            received = msgrcv(mq_id2, &mymsg, sizeof(mymsg), 0, 0);
            signal(SIGUSR1, handler);
            read(mq_id2, &a, strlen(a));
            printf("a<- %s\n", a);
            read(mq_id2, &b, strlen(b));
            printf("b<- %s\n", b);
            read(mq_id2, &c, strlen(c));
            printf("c<- %s\n", c);

            //Нахождение площади
            double p=0;
	    double res=0;
            double _a  = atof(a);
	    double _b = atof(b);
	    double _c  = atof(c);
	    p=(_a+_b+_c)/2;
            res=pow((p*(p-_a)*(p-_b)*(p-_c)),0.5);
            printf("\nПлощадь заданного треугольника: %f\n", res);
printf("Завершился дочерний процесс");
            close(mq_id2);

        }
        return 0;
    }
