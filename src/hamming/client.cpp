#include <iostream>
#include <cstring>
#include <cmath>
#include <unistd.h>
#include <arpa/inet.h>
using namespace std;

string reverseCharArray(char *arr)
{
    int n = strlen(arr);
    char data[n + 1] = {'\0'};
    int k = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        data[k++] = arr[i];
    }

    for (int i = 0; i < n; i++)
    {
        arr[i] = data[i];
    }
    return arr;
}

int NumberOfParityBits(int datawordlen)
{
    int r = 1;
    while (datawordlen + r + 1 > pow(2, r))
        r++;
    return r;
}

string parity(int n, char *arr)
{
    int bit = 0;
    for (int i = 0; i < n; i = (i + 1) * 2)
    {
        int count = 0;
        for (int j = i + 2; j < n; j++)
        {
            if (j & (1 << bit))
            {
                if (arr[j] == '1')
                    count++;
            }
        }

        if (count & 1)
            arr[i] = '1';
        else
            arr[i] = '0';
    }

    return arr;

    // int sum = 0;
    // for (int i = 0; i < n; i++)
    // {
    //     if ((i & (1 << p - 1)) == 0)
    //     {
    //         sum ^= (arr[i] - '0');
    //     }
    // }
    // return sum;
}

string Hamming(char *data)
{
    int n = strlen(data);
    int r = NumberOfParityBits(n);
    char encoded[n + r + 1] = {'\0'};

    reverseCharArray(data);

    int j = 0;
    for (int i = 0; i < n + r; i++)
    {
        if ((i & (i + 1)) == 0)
        {
            encoded[i] = '0';
        }
        else
        {
            encoded[i] = data[j];
            j++;
        }
    }
    parity(n + r, encoded);
    // for (int i = 0; i < r; i++)
    // {
    //     encoded[(1 << i) - 1] = parity(n + r, encoded) + '0';
    // }
    return reverseCharArray(encoded);
}

int main()
{
    cout << "------------------>   CLIENT   <-----------------\n\n\n\n";

    int sd;
    struct sockaddr_in sad, cad;
    char dataword[50];

    // sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // sad.sin_family = AF_INET;
    // sad.sin_port = htons(8080);
    // sad.sin_addr.s_addr = inet_addr("127.0.0.1");

    // connect(sd, (struct sockaddr *)&sad, sizeof(sad));

    cout << "Enter Dataword -----> ";
    cin >> dataword;

    cout << Hamming(dataword) << endl;

    // send(sd, str, sizeof(str), 0);
    // close(sd);
}