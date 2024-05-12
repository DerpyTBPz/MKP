#include <iostream>
#include "./lib/serialib.h"

#define     COM    "\\\\.\\COM3"

int main()
{
    serialib com;
    int bitMode = -1;
    int iterations = -1;
    int workMode = -1;
    int threshold = -1;

    char tst[128] = "ITS WORKING";
    char string[128];
    char sendString[128];
    char color;

    int errorOpening = com.openDevice(COM, 2400, SERIAL_DATABITS_8, 
                                      SERIAL_PARITY_NONE, SERIAL_STOPBITS_1);
    if (errorOpening == 1)
    {
        std::cout << "Opening successful\n";
    }
    else 
    {
        std::cout << "Opening error with code:" << errorOpening;
        return 0;
    }

    while (true)
    {
        std::cin >> string;
        com.writeString(string);
        int readError = com.readString(string, '\r', 128, 500);
        if (readError < 0)
        {
            std::cout << "\nError with code: " << readError;
            return 0;
        }        
        else
        {
            std::cout << "\nString read: " << string;
        } 
    }

   while (true)
    {
        com.writeString(tst);
        int readError = com.readString(string, '\r', 128, 500);
        if (readError < 0)
        {
            std::cout << "\nError with code: " << readError;
            return 0;
        }        
        else
        {
            std::cout << "\nString read: " << string;
        }  
    }

    while (true)
    {
        std::cout << "\nEnter color (red / green / blue): ";
        std::cin >> color;

        if (color == 'r' || color == 'g' || color == 'b')
        {
            com.writeString(string);
            com.readString(sendString, '\n', 128, 2000);
            std::cout << sendString;
        }
        else 
        {
            std::cout << "no";
        }
    }
    

    // while (true)
    // {

    //     while (true)
    //     {
    //         std::cout << "\nEnter number of iterations: ";
    //         std::cin >> iterations;

    //         if (iterations > 0)
    //         {
    //             break;
    //         }
    //     }  

    //     while (true)
    //     {          
    //         std::cout << "\nChoose mode: \n\t 1) 8bit \n\t 2) 10bit";
    //         std::cin >> bitMode;

    //         if ((bitMode == 1) || (bitMode == 2))
    //         {
    //             break;
    //         }        
    //         else 
    //         {
    //             bitMode == -1;
    //         }  
    //     }  

    //     std::cout << "Enter threshold: ";
    //     std::cin >> workMode;

    //     while (true)
    //     {
    //         std::cout << "Choose working mode: \n\t 1) Samples unpper threshold \n\t 2) All \n\t 3) Samples under threshold";
    //         std::cin >> workMode;

    //         if ((workMode == 1) || (workMode == 2) || (workMode == 3)) 
    //         {
    //             break;
    //         }            
    //         else
    //         {
    //             workMode = -1;
    //         }
    //     }

        // int readError = com.readString(string, '\n', 128, 2000);
        // if (readError < 0)
        // {
        //     std::cout << "\nError with code: " << readError;
        //     return 0;
        // }        
        // else
        // {std::cout << "\nPress enter to start ";
    // std::cin;

    // com.writeString("Get");

    // itoa(iterations, sendString, 10);
    // com.writeString(sendString);

    // itoa(threshold, sendString, 10);
    // com.writeString(sendString);

    // itoa(workMode, sendString, 10);
    // com.writeString(sendString);

    // itoa(bitMode, sendString, 10);
    // com.writeString(sendString);
        //     std::cout << "String read: " << string;
        // }        
    // }    

    // 
    return 0;
}

void ErrorCheck(int errCode)
{
    std::cout << " ";
}
