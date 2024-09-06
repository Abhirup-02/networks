#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    printf("------------------>   SERVER   <-----------------\n\n\n\n");

    int sd, cd;
    struct sockaddr_in sad, cad;
    char str[50];

    sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    sad.sin_family = AF_INET;
    sad.sin_port = htons(8080);
    sad.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(sd, (struct sockaddr *)&sad, sizeof(sad));
    listen(sd, 10);

    unsigned int cadl = sizeof(cad);
    printf("%d", cadl);
    cd = accept(sd, (struct sockaddr *)&cad, &cadl);

    recv(cd, str, sizeof(str), 0);
    printf("Client -----> %s", str);

    close(cd);
    close(sd);
}