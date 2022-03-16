#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

/*
* Fil: Uppgift4.c
* Upphovsman: Niklas Månzén 
* Kort beskrivning om programmet: Kortleksspelet!
* Ger användaren slumpmässigt antal kort och slumpmässig färg från kortlek beroende på vad användaren skriver in.
*/

char *vilketKort[13] = {"Tv\x86","Tre","Fyra","Fem","Sex","Sju","\x8Ftta","Nio","Tio","Kn\x84""ckt","Dam","Kung","Ess"};
// Det finns 13 kort. Skapar en pekarfältvariabel och tilldelar den alla kort för att hålla koll på dessa.
char *vilkenFärg[4] = {"Hj\x84rter","Kl\x94ver","Ruter","Spader"};  // Det finns 4 olika färger. Skapar en pekarfältvariabel och tilldelar alla färger för att hålla koll på dessa.

int slumpTal(int X) // "Slumptal-Generator"-funktion! 
{
    return rand() % X; // Returnerar ett slumpmässigt nummer via rand enligt vad som passas in (int X) från funktion "KortDragning". Dvs alltid 4 & 13 varje gång.
}

void kortDragning() // Skall ej returnera något. Bara skriva ut. 
{   
        
    int A = slumpTal(4);    // Använder slumpTal-funktionen för att generera ett slumpmässigt tal som sedan passas in i respektive pekar-fältvariabel.
    int B = slumpTal(13);  //  Färg = har Index 0-3 (4 Element = 4 Färger) & vilketKort = har Index 0-12 (13 Element = 13 Färger)

    printf("\n%s %s\n",vilkenFärg[A], vilketKort[B]); // Skriver ut resultatet & skapar magi!
    Sleep(1000);

}           // Försökte få funktionen att jämföra kort med kort så man inte kunde få samma kort. Men misslyckades tyvärr.

int main()
{
    srand(time(0)); // Använder srand och timefunktionen för att få tillgång till slumpmässiga tal genom klockan.

    printf("_________________________________\nV\x84lkommen till detta kortspel!\n_________________________________\n");
    Sleep(1000);
    
    do   // Gör DETTA medans while är true(1) ända tills användaren skriver in 0. antalKort blir då 0 & den går ur loopen och avslutar programmet genom return 0; .
    {

    printf("\nSkriv In Antal Kort Som Ska Dras! (Tryck 0 F\x94r Att Avsluta)\n: ");
    
    int antalKort;
    scanf("%i",&antalKort);

        if(antalKort == 0)  // Här går den ut ur do while loopen genom break som sedan kommer returnera 0 som i sin tur stänger programmet.  

        {
            break;
        }

        if(antalKort > 52)  // Vill inte att användaren ska kunna få mer kort än max antalet kort som finns i en kortlek.

        {
            Sleep(1000);
            printf("Du kan inte dra mer kort \x84n vad som finns i kortleken!\n Max antal kort som finns \x84r 52st. F\x94rs\x94k igen!\n_________________________________\n");
            Sleep(1000);
        }

        else  // Kör vidare om "antalKort" är godkänt
        {
            // Deklarerar en temporär int variabel för att kunna använda den i en loop tillsammans med "antalKort".
            for(int temp = 1; temp <= antalKort; temp++) // temp börjar på 1. Så att användaren ska få rätt antal kort dragna.

            {
                kortDragning(); // Kör funktionen så många gånger som loopen körs. Antal gånger är utefter "antalKort". 
            } 

        } 
    
    }   while(true);

    printf("Tack f\x94r att du har spelat detta kortspel!\n");
    Sleep(1000);

    return 0;
}