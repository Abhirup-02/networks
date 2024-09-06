#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    printf("------------------>   CLIENT   <-----------------\n\n\n\n");

    int sd;
    struct sockaddr_in sad;
    char str[50];

    sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    sad.sin_family = AF_INET;
    sad.sin_addr.s_addr = inet_addr("127.0.0.1");
    sad.sin_port = htons(8080);

    connect(sd, (struct sockaddr *)&sad, sizeof(sad));

    do
    {
        recv(sd, str, sizeof(str), 0);
        printf("Received from sender -----> %s\n", str);
        printf("Enter message -> ");
        fflush(stdin);
        scanf("%s", str);
        send(sd, str, sizeof(str), 0);
    } while (strcmp(str, "bye") != 0);

    close(sd);
}