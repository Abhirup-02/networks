#include <iostream>
#include <cstring>
#include <cmath>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

string CRC(char data[], char divisor[])
{
    int datal = strlen(data), divl = strlen(divisor);
    char codeword[datal + divl] = {'\0'}, temp[datal + divl] = {'\0'};
    strcpy(temp, data);
    strcpy(codeword, data);

    for (int i = 0; i < divl - 1; i++)
        temp[datal + i] = '0';

    for (int i = 0; i < datal; i++)
    {
        if (temp[i] == '1')
        {
            for (int j = 0; j < divl; j++)
            {
                if (temp[i + j] == divisor[j])
                    temp[i + j] = '0';
                else
                    temp[i + j] = '1';
            }
        }
    }
    
    for (int i = datal; i < datal + divl - 1; i++)
        codeword[i] = temp[i];

    return codeword;
}

int main()
{
    cout << "------------------>   CLIENT   <-----------------\n\n\n\n";

    int sd;
    struct sockaddr_in sad;
    char dataword[50], divisor[10];

    sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    sad.sin_family = AF_INET;
    sad.sin_addr.s_addr = inet_addr("127.0.0.1");
    sad.sin_port = htons(8080);

    connect(sd, (struct sockaddr *)&sad, sizeof(sad));

    cout << "Enter Dataword ---> ";
    cin >> dataword;

    cout << "Enter Divisor ---> ";
    cin >> divisor;

    cout << "CODEWORD = " << CRC(dataword, divisor) << endl;

    send(sd, dataword, sizeof(dataword), 0);
    close(sd);
}