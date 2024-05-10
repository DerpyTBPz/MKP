#include <iostream>
#include "./lib/serialib.h"

#define     COM    "\\\\.\\COM7"

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

    // while (true)
    // {
    //     com.writeString(tst);

    //     com.readString(rtst, '\n', 128, 500);
    //     std::cout << "\nRead String: " << rtst;
    // }

    while (true)
    {

        while (true)
        {
            std::cout << "\nEnter number of iterations: ";
            std::cin >> iterations;

            if (iterations > 0)
            {
                break;
            }
        }  

        while (true)
        {          
            std::cout << "\nChoose mode: \n\t 1) 8bit \n\t 2) 10bit";
            std::cin >> bitMode;

            if ((bitMode == 1) || (bitMode == 2))
            {
                break;
            }        
            else 
            {
                bitMode == -1;
            }  
        }  

        std::cout << "Enter threshold: ";
        std::cin >> workMode;

        while (true)
        {
            std::cout << "Choose working mode: \n\t 1) Samples unpper threshold \n\t 2) All \n\t 3) Samples under threshold";
            std::cin >> workMode;

            if ((workMode == 1) || (workMode == 2) || (workMode == 3)) 
            {
                break;
            }            
            else
            {
                workMode = -1;
            }
        }

        // int readError = com.readString(string, '\n', 128, 2000);
        // if (readError < 0)
        // {
        //     std::cout << "\nError with code: " << readError;
        //     return 0;
        // }        
        // else
        // {
        //     std::cout << "String read: " << string;
        // }        
    }    

    std::cout << "\nPress enter to start ";
    std::cin;

    com.writeString("Get");

    itoa(iterations, sendString, 10);
    com.writeString(sendString);

    itoa(threshold, sendString, 10);
    com.writeString(sendString);

    itoa(workMode, sendString, 10);
    com.writeString(sendString);

    itoa(bitMode, sendString, 10);
    com.writeString(sendString);

    while (true)
    {
        int readError = com.readString(string, '\n', 128, 2000);
        if (readError < 0)
        {
            std::cout << "\nError with code: " << readError;
            return 0;
        }        
        else
        {
            std::cout << "String read: " << string;
        }  
    }

    // while (true)
    // {
    //     if (bitMode == 1)
    //     {
    //         int errorOpening = com.openDevice(COM, 2400, SERIAL_DATABITS_8, 
    //                                           SERIAL_PARITY_NONE, SERIAL_STOPBITS_1);
    //     }
    //     else if (bitMode == 2)
    //     {
    //         std::cout << "\nOpening error";
    //         return 0;
    //     } 
    // }

    return 0;
}

void ErrorCheck(int errCode)
{
    std::cout << " ";
}
