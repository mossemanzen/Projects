#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <stdbool.h>

/*
* Fil: Uppgift2.c
* Upphovsman: Niklas Månzén
* Kort beskrivning om programmet: Konverteringsprogram! 
* Yard till Meter eller Tum till Centimeter beroende på vad användaren väljer. 
* In English...
*/

void yardtoMeter() // Yard to Meter. void datatype function. No need for return, in this case.
{

    Sleep(500);
    printf("Type Your Yard Value : ");
    double yard;     //datatype double to make sure that the user can type big numbers with decimals if needed.
    scanf("%lf",&yard);
    double sum;
    sum = (yard/1.0936);    // The Mathematical equation for yard to meter is given to sum.
    Sleep(1000);

    printf("%.2lf Yards = %.2lf Meters.\n", yard, sum);

}

void inchtoCentimeter()  // Inch to Centimeter. Also a void datatype function.
{
    Sleep(500);
    printf("Type Your Inch Value : ");
    double inch;
    scanf("%lf",&inch);
    double sum;             
    sum = (inch/0.39370);   // The Mathematical equation for inch to cm is given to sum.
    Sleep(1000);

    printf("%.2lf Inches = %.2lf Centimeters.\n", inch, sum);

}

void menu()     // Meny for the different choices.
{

        printf(".....You now have 2 Choices.....\n");
        Sleep(500);
   
        printf("1. Convert Yard to Meter.\n2. Convert Inch To Centimeter.\n: ");

        int choice;
        scanf("%d",&choice);
        fgetchar();         // Catches the char value if the user decides tries with chars.

        switch (choice)     // depending of the value of choice it will do yardtoMeter-function or inchtoCentimeter-function
        {
            case 1 :
            yardtoMeter();
            break;

            case 2 :
            inchtoCentimeter();
            break;
        
            default:
            Sleep(500);
            printf("Invalid choice...\nPlease Try Again!\n");          // Saves invalid int input from the user. Calling function menu once again.
            Sleep(1000);
            menu();
            break;
        }
}

int main (void)
{

    printf("Welcome To The Conversion Program\n");
    Sleep(1000);
    
    menu(); 

    Sleep(1000);
    printf("\nThank you for using this program...Have a nice day!");

    return 0;

}