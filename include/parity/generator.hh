#ifndef PARITY_GENERATOR
#define PARITY_GENERATOR

string ParityGenerator(char data[])
{
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
    return data;
}

#endif