#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

#include <parity/generator.hh>


int main()
{
    cout << "------------------>   CLIENT   <-----------------\n\n\n\n";

    int sd;
    struct sockaddr_in sad;
    char dataword[50];

    sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    sad.sin_family = AF_INET;
    sad.sin_addr.s_addr = inet_addr("127.0.0.1");
    sad.sin_port = htons(8080);

    connect(sd, (struct sockaddr *)&sad, sizeof(sad));

    cout << "Enter Dataword -----> ";
    cin >> dataword;

    ParityGenerator(dataword);

    send(sd, dataword, sizeof(dataword), 0);
    close(sd);
}
