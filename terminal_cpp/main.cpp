#include <iostream>
#include "./lib/serialib.h"

int main()
{
    serialib com;
    int bitMode = -1;
    int iterations = -1;
    int workMode = -1;
    int threshold = -1;

    // int errorOpening = com.openDevice("\\\\.\\COM5", 2400, SERIAL_DATABITS_8, 
    //                                   SERIAL_PARITY_NONE, SERIAL_STOPBITS_1);

    // if (errorOpening == 1)
    // {
    //     std::cout << "Opening successful\n";
    // }
    // else 
    // {
    //     std::cout << "Opening error with code:" << errorOpening;
    //     return 0;
    // }

    char string[128];

    while (true)
    {

        while (true)
        {
            std::cout << "Enter number of iterations: \n\t 1) 8bit \n\t 2) 10bit \n\t 0) Exit \n\t";
            std::cin >> iterations;

            if (iterations > 0)
            {
                break;
            }
        }  

        while (true)
        {          
            std::cout << "Choose mode: \n\t 1) 8bit \n\t 2) 10bit";
            std::cin >> bitMode;
            if (bitMode == 1)
            {
                int errorOpening = com.openDevice("\\\\.\\COM5", 2400, SERIAL_DATABITS_8, 
                                                SERIAL_PARITY_NONE, SERIAL_STOPBITS_1);
                if (errorOpening == 1)
                {
                    std::cout << "\nOpening successful";
                    break;
                }
                else 
                {
                    std::cout << "\nOpening error with code:" << errorOpening;                
                }
            }
            else if (bitMode == 2)
            {
                std::cout << "\nOpening error";
                return 0;
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
            if (workMode == 1)
            {

            }
            else if (workMode == 2)
            {

            }
            else if (workMode == 3)
            {

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

    return 0;
}
