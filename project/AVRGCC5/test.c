#include <stdio.h>

void SendString(char* str);
void ReceiveString(char* str);

char string[128];

int main()
{
    ReceiveString(string);
	SendString(string);
}

void SendString(char* str)
{
    while (1)
    {
        if (str != '\0')
        {
            printf(str);
            str++;
        }
        else
        {
            break;
        }
    }
}