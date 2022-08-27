//
//  main.c
//  socketClient
//
//  Created by Lu Kejin on 1/22/12.
//  Copyright (c) 2012 Taobao.com. All rights reserved.
//

#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024
#define CHAT_SERVER_PORT 9898

int main(int argc, const char *argv[])
{
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(CHAT_SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    bzero(&(server_addr.sin_zero), 8);

    int server_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock_fd == -1)
    {
        perror("socket error");
        return 1;
    }
    char recv_msg[BUFFER_SIZE], input_msg[BUFFER_SIZE];

    if (connect(server_sock_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in)) == 0)
    {
        // fd_set client_fd_set;
        // struct timeval tv;
        // tv.tv_sec = 20;
        // tv.tv_usec = 0;

        // FD_ZERO(&client_fd_set);
        // FD_SET(STDIN_FILENO, &client_fd_set);
        // FD_SET(server_sock_fd, &client_fd_set);

        // int ret = select(server_sock_fd + 1, &client_fd_set, NULL, NULL, &tv);
        // if (ret < 0)
        // {
        //     printf("select error!\n");
        //     continue;
        // }
        // else if (ret == 0)
        // {
        //     printf("select se acabó el tiempo!\n");
        //     continue;
        // }
        // if (FD_ISSET(STDIN_FILENO, &client_fd_set))
        // {
            bzero(input_msg, BUFFER_SIZE);
            // fgets(input_msg, BUFFER_SIZE, stdin);

            FILE *f;
            int words = 0;
            int i;

            f = fopen("glad.txt", "r");
            while (getc(f) != EOF)
            {
                fscanf(f, "%s", input_msg);
                words++;
                if (strlen(input_msg)/4 != 0)
                {
                    words = words + (strlen(input_msg) / 4) - 1;
                }
            }

            printf("%d\n", words);
            send(server_sock_fd, &words, sizeof(words), 0);
            rewind(f);

            char ch;
            while (getc(f) != EOF)
            {
                fscanf(f, "%s", input_msg);
               // int sizeW = strlen(input_msg);
                printf("%s\n", input_msg);
              //  printf("%d\n", sizeW);
               // i = send(server_sock_fd, &sizeW, sizeof(sizeW), 0);
                
                i = send(server_sock_fd, input_msg, strlen(input_msg), 0);
                bzero(input_msg, BUFFER_SIZE);
            }

            
            
            //send(server_sock_fd, '0', BUFFER_SIZE, 0);
            // printf("%s", input_msg);
            /*
            send(server_sock_fd, words, sizeof(int), 0);
           

            //printf("%s\n", input_msg);

            char ch;
            while (ch != EOF)
            {
                fscanf(f, "%s", input_msg);
                printf("%s\n", input_msg);
                send(server_sock_fd, input_msg, BUFFER_SIZE, 0);
                ch = fgetc(f);
            }

*/
            printf("The file has been successfully sent. Thank you");
            int consonantes;
            read(server_sock_fd, &consonantes, sizeof(consonantes));
            printf("\n La cantidad de consonantes que habian eran: %d", consonantes);
    
/*
            if (send(server_sock_fd, input_msg, words, 0) == -1)
            {
                perror("Error al enviar mensaje!\n");
            }
            */
        // }

        // if (FD_ISSET(server_sock_fd, &client_fd_set))
        // {
        //     bzero(recv_msg, BUFFER_SIZE);
        //     long byte_num = recv(server_sock_fd, recv_msg, BUFFER_SIZE, 0);
        //     if (byte_num > 0)
        //     {
        //         if (byte_num > BUFFER_SIZE)
        //         {
        //             byte_num = BUFFER_SIZE;
        //         }
        //         recv_msg[byte_num] = '\0';
        //         printf("servidor:%s\n", recv_msg);
        //     }
        //     else if (byte_num < 0)
        //     {
        //         printf("Error al recibir el mensaje!\n");
        //     }
        //     else
        //     {
        //         printf("Salida del lado del servidor!\n");
        //         close(server_sock_fd);
        //         exit(0);
        //     }
        // }
    }

    close(server_sock_fd);
    return 0;
}
/*
FILE *f;
int words = 0;

char c;
f = fopen("glad.txt", "r");
while ((c = getc(f)) != EOF)
{
    fscanf(f, "%s", buffer);
    if (isspace(c) || c == '\t')
        words++;
}

write(sockfd, &words, sizeof(int));
rewind(f);

char ch;
while (ch != EOF)
{
    fscanf(f, "%s", buffer);
    write(sockfd, buffer, 255);
    ch = fgetc(f);
}

printf("The file has been successfully sent. Thank you");

close(sockfd);
return 0;
*/