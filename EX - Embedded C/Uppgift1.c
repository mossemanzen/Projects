#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <stdbool.h>

/*
* Fil: Uppgift1.c
* Upphovsman: Niklas Månzén
* Kort beskrivning om programmet: 
* Detta program räknar ut om det är skottår eller ej
* på året som användaren ger oss.
*/

void kontrolleraÅr(int år) //Kontrollera skottår på det som anges. Vi behöver inte returnera något.
{
        if ((år % 4 == 0) && (år % 100 != 0 || år % 400 == 0))
        /* 3 Villkor:   Om "år" går jämnt ut med %4 OCH 
                        Om "år" EJ går jämnt ut med %100 ELLER 
                        Om "år" går jämnt ut med %400. DÅ är det ett skottår.*/
        {
                Sleep(1000);
                printf("\x8Fr %d \x8ER ett skott\x86r!\n", år);
        }   

        else // Annars så är det EJ ett skottår.
        {
                Sleep(1000);
                printf("\x8Fr %d \x84r INTE ett skott\x86r!\n", år); 
        }

}

int main(void)
{

printf("...V\x84lkommen till Kontrolleraskott\x86rsprogrammet!...\n"); 
Sleep (1000);

do      // Gör DETTA så länge det är true. Kommer för alltid fråga om årtal tills användaren skriver in 0!
{
        printf("Var god skriv in ett \x86rtal - Tryck 0 F\x94r Att Avsluta\n:");

        int årtal;
        scanf("%d",&årtal);

        if (årtal == 0)         // Stänger ned programmet
        { 
                Sleep(500);
                printf("\tHa det bra!");
                Sleep(500);
                break;
        }

        if (årtal > 0)
        {
                kontrolleraÅr(årtal);  //Passar in användarens inmatning till funktionen kontrolleraÅr's arguemnt
        }

        else
        {
                printf("Du angav inget år...");
        }

} while (true);

return 0;

}