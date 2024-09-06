#include <iostream>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <math.h>
using namespace std;

bool ValidSegmentLength(int seglen)
{
    for (int i = 1; i <= seglen / 2; i++)
    {
        if (pow(2, i) == seglen)
            return true;
    }
    return false;
}

string MakeValidDataLength(char dataword[], int seglen)
{
    int datalen = strlen(dataword);

    if (datalen % seglen != 0)
    {
        int extraBits = seglen - (datalen % seglen);

        char temp[datalen + extraBits] = {'\0'};
        for (int i = 0; i < extraBits; i++)
        {
            temp[i] = '0';
        }
        strcat(temp, dataword);
        strcpy(dataword, temp);
    }
    return dataword;
}

string Ones_Complement(char data[])
{
    for (unsigned int i = 0; i < strlen(data); i++)
    {
        if (data[i] == '0')
            data[i] = '1';
        else
            data[i] = '0';
    }
    return data;
}

string CheckSum(char dataword[], int seglen)
{
    int dl = strlen(dataword);
    char sum[seglen + 1] = {'\0'};
    for (int i = 0; i < seglen; i++)
        sum[i] = '0';

    for (int i = dl - 1; i >= 0; i -= seglen)
    {
        int c = 0;
        int k = seglen - 1;
        for (int j = i; j > i - seglen; j--)
        {
            int t = (sum[k] - '0') + (dataword[j] - '0') + c;
            sum[k] = (t % 2) + '0';
            c = t / 2;
            k--;
        }
        if (c == 1)
        {
            for (int j = seglen - 1; j >= 0; j--)
            {
                int t = (sum[j] - '0') + c;
                sum[j] = (t % 2) + '0';
                c = t / 2;
            }
        }
    }
    return Ones_Complement(sum);
}

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

    int seglen;
    while (1)
    {
        cout << "Enter segment length -> ";
        cin >> seglen;
        if (ValidSegmentLength(seglen))
            break;
        else
            cout << "|| Segment length must be power of 2, Try again ||" << endl;
    }

    MakeValidDataLength(dataword, seglen);
    cout << "Checksum = " << CheckSum(dataword, seglen) << endl;

    send(sd, dataword, sizeof(dataword), 0);
    close(sd);
}