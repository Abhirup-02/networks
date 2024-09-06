#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

void ParityChecker(char codeword[])
{
    char data[50];
    cout << "Enter Data -----> ";
    scanf("%[^\n]s", data);

    int i = 0, count_1 = 0;
    while (data[i] != '\0')
    {
        if (data[i] == '1')
            count_1++;
        i++;
    }

    char ch;
    cout << "Enter 'e' for Even Parity --- 'o' for Odd Parity -> ";
    cin >> ch;
    switch (ch)
    {
    case 'e':
        if (count_1 % 2 == 0)
            strcat(data, "0");
        else
            strcat(data, "1");
        break;

    case 'o':
        if (count_1 % 2 == 0)
            strcat(data, "1");
        else
            strcat(data, "0");
        break;
    }

    if (strcmp(data, codeword) == 0)
        cout << "DATA IS CORRECT" << endl;
    else
        cout << "DATA IS INCORRECT" << endl;
}

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

    ParityChecker(codeword);

    close(cd);
    close(sd);
}