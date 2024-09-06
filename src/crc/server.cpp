#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

int main()
{
    cout << "------------------>   SERVER   <-----------------\n\n\n\n";

    int sd, cd;
    struct sockaddr_in sad, cad;
    char codeword[50];

    sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    sad.sin_family = AF_INET;
    sad.sin_addr.s_addr = inet_addr("127.0.0.1");
    sad.sin_port = htons(8080);

    bind(sd, (struct sockaddr *)&sad, sizeof(sad));
    listen(sd, 10);

    unsigned int cadl = sizeof(cad);
    cd = accept(sd, (struct sockaddr *)&cad, &cadl);

    recv(cd, codeword, sizeof(codeword), 0);
    cout << "Codeword Received -----> " << codeword << endl;

    close(cd);
    close(sd);
}
