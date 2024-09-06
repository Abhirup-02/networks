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

    printf("Enter Dataword -----> ");
    scanf("%[^\n]s", str);
    send(sd, str, sizeof(str), 0);

    close(sd);
}