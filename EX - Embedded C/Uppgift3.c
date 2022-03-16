#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <stdbool.h>

/*
* Fil: Uppgift3.c & pinkod.txt
* Upphovsman: Niklas Månzén
* Kort beskrivning om programmet: 
* Simpelt Bankprogram 
* - Insättning, uttag av pengar & Saldocheck med PINkodkontroll
* - pinkod1337.txt med koden 1337 samt SALDO.TXT MÅSTE vara med i samma MAPP som du arbetar i.
* - Då fungerade det för mig i alla fall.
*/

int utbetalning(); // Tar UT och skriver och läser i SALDO
int insättning(); // Tar IN och skriver och läser i SALDO
int pinKod(); // Kontrollerar om användaren skriver in rätt PINKOD.
int meny(); // Menyn anropas ENDAST om PINkod går igenom i pinKodfunktion. Användaren blir inloggad & får alternativ.
int kollaSaldo(); // Visar saldot.

int main(void)
{
    printf("___________________________\nV\x84lkommen till EC-Bank!\n");
    printf("\t- EC PC!\n___________________________\n");

    pinKod(); 
    
    return 0;
}

int meny()
{ 
    int retur; // deklarar en int retur. Som hanterar respektive funktions retur. 0 eller 1.  
    
    do
    {
        Sleep(1000);
        printf("G\x94r ett av f\x94ljande alternativ :\n");
        Sleep(1000);
        printf("1. S\x84tt in Pengar\n2. Ta ut Pengar\n3. Kolla Saldo\n4. Logga ut\n");
    
        int val;
        scanf("%d", &val);

        switch (val)        // beroende på vad användaren väljer hamnar vi i respektive funktion.
        {
        case 1 :
            retur = insättning();
            break;

        case 2 :
            retur = utbetalning();
            break;

        case 3 :
            retur = kollaSaldo();
            break;

        case 4 :
            Sleep(1000);
            printf("...Du har loggat ut.");
            retur = 0;
            break;              

        default:                // Fångar felaktiga val
            Sleep(1000);
            printf("Du har angivit ett felaktigt val. Var god f\x94rs\x94k igen!\n_______________________\n");
            retur = 1;          // Tilldelar retur = 1 för att komma tillbaka in i do whilen här i "menyn".
            break;
        }
    } while(retur == 1);
}

int pinKod() // Kontrollerar om användaren skriver in rätt PINKOD.
{
    
    FILE *pekare;
    pekare = fopen ("pinkod1337.txt","r");

    if (pekare == NULL)
    {
        printf("\n_______________________\nKunde inte l\x84sa in PINKOD-Fil...\n_______________________\n");
        fclose(pekare);     // Stänger filen som pekare pekar på.
        return 0;
    }

    Sleep(1000);
    printf("Var god skriv in din PINKOD\n\t4 Siffror\n:");
    
    int input;
    scanf("%d", &input);

    int kod;
    fscanf(pekare, "%d", &kod);

    if (input == kod)               // Jämför om värdet från pinkod1337.txt är samma som input från användare 
    {
        Sleep(500);
        printf("Kommunicerar med bank");
        Sleep(500);
        printf("...");
        Sleep(500);
        printf("...\n");
        Sleep(1000);
        printf("___________________________\nPINKOD Godk\x84nd!\n___________________________\n");
        Sleep(1000);
        printf("Hej & V\x84lkommen!\n___________________________\n");
        fclose(pekare); // Stänger filen som pekare pekar på
        meny();     // Anropar meny så de får tillgång till allt.
    }
    
    else            // Fångar upp om personen skriver fel. Stänger pekare och kör pinKod(); igen.
    {
        Sleep(500);
        printf("Kommunicerar med bank");
        Sleep(500);
        printf("...");
        Sleep(500);
        printf("...\n");
        Sleep(500);
        printf("___________________________\nPINKOD EJ Godk\x84nd!\n");
        Sleep(1000);
        printf("Var God F\x94rs\x94k Igen");
        Sleep(1000);
        printf("\n___________________________\n");
        fclose(pekare); // Stänger filen som pekare pekar på
        pinKod();       // Anropar pinkod igen för nytt försök... "Dessvärre" får användaren hur många försök som helst :)
    }  

}

int insättning() // Tar IN och skriver och läser i SALDO. Returnerar 1 eller 0 tillbaka till "menyn"
{
    
    FILE *pekare;
    pekare = fopen ("SALDO.txt","r");           // Tilldelar pekaren till SALDO.TXT att öppna fil för att kunna LÄSA endast.

    if(pekare == NULL)                          // Fångar om programmet ej hittar filen.
    {
        printf("\n_______________________\nKunde inte läsa in SALDO-Fil...\n_______________________\n");
        fclose(pekare);
        return 0;
    }

    double kollaSaldo;
    fscanf(pekare, "%lf",&kollaSaldo);          // Vi kollar vad filen vi pekar på har för värde
    Sleep(1000);
    printf("Du har just nu %.2lf antal kronor p\x86 ditt konto i EC-Banken.\nAnge hur mycket du vill s\x84tta in : ", kollaSaldo);
    Sleep(1000);
    double sättaIn;
    scanf("%lf", &sättaIn);

    fclose(pekare);                         // Stänger för att öppna på nytt. Fick inte till "bådeoch" läget.

    pekare = fopen ("SALDO.txt","w+");       // Tilldelar pekaren ännu en gång för att öppna fil för att kunna SKRIVA & LÄSA.

    double nyaSaldo;
    nyaSaldo = kollaSaldo + sättaIn;        //Gamla saldot + Nya insättning.

    fprintf(pekare, "%.2lf", nyaSaldo);     // Ersätter gamla saldo med nya.

    
    printf("\nDu har satt in %.2lf antal kronor p\x86 kontot.\n", sättaIn);
    Sleep(1000);
    printf("Nytt Saldo : %.2lf\n", nyaSaldo);
    Sleep(1000);
    printf("_______________________\n\x8Fter till menyn\n_______________________\n");
    fclose(pekare);
    return 1;       // Så vi kommer säkert tillbaka in do whilen i "menyn"

}

int utbetalning() // Tar UT och skriver och läser i SALDO. Returnerar 1 eller 0 tillbaka till "menyn"
{
        FILE *pekare;
        pekare = fopen ("SALDO.txt","r");

        if(pekare == NULL)
        {
            printf("\n_______________________\nKunde inte l\x84sa in SALDO-fil...\n_______________________\n");
            fclose(pekare);
            return 0;
        }
    
        double kollaSaldo;
        fscanf(pekare, "%lf",&kollaSaldo);      // Snarlik insättningsfunktionen
        printf("Du har just nu %.2lf antal kronor p\x86 ditt konto i EC-Banken.\nAnge hur mycket du vill ta ut fr\x86n kontot : \n", kollaSaldo);
        Sleep(1000);

        double taUt;
        scanf("%lf",&taUt);

        double kontrolleraSaldo;
        kontrolleraSaldo = kollaSaldo - taUt;

        if(kollaSaldo == 0) // Fångar om saldot är 0 från början!
        {
            Sleep(1000);
            printf("Du kan inte ta ut n\x86gra kronor alls fr\x86n kontot eftersom saldot \x84r %.2lf...\n", kollaSaldo);
            fclose(pekare);
            return 1;
        } 

        if (kontrolleraSaldo < 0)  // Fångar om det blir mindre än 0!
        {
            printf("Du har f\x94r lite i Saldo f\x94r att kunna ta ut %.2lf antal kronor.\n", taUt);
            Sleep(1000);
            printf("_______________________\n\x8Fter till menyn\n_______________________\n");
            fclose(pekare);
            return 1;
        }

        fclose(pekare);   // Stänger för att öppna på nytt. Fick inte till "bådeoch" läget.

        pekare = fopen ("SALDO.txt","w+");  //Tilldelar pekaren ännu en gång

        if (kontrolleraSaldo == 0) // Fångar om det ÄR PRECIS 0!
        {
            printf("Du tog PRECIS ut : %.2lf antal kronor.\n", taUt);
            Sleep(1000);
            fprintf(pekare, "%lf", kontrolleraSaldo);   // Skriver över gammalt värde i .txt fil
            
            printf("Nytt saldo p\x86 kontot : %.2lf antal kronor.\n", kontrolleraSaldo);
            Sleep(1000);
            fclose(pekare);
            
            printf("_______________________\n\x8Fter till menyn\n_______________________\n");
            return 1;
        }

        else    // Annars gör den inget märkvärdigt
        {
            printf("Du tog ut : %.2lf antal kronor.\n", taUt);
            fprintf(pekare, "%.2lf", kontrolleraSaldo);
            Sleep(1000);
            
            printf("Nytt saldo p\x86 kontot : %.2lf antal kronor\n", kontrolleraSaldo);
            Sleep(1000);

            fclose(pekare);
            Sleep(1000);
            printf("_______________________\n\x8Fter till menyn\n_______________________\n");
            return 1;
        }

}

int kollaSaldo()       // Kollar bara SALDOT. Saldot anges alltid i de andra funktionerna men här får man längre tid på sig att exempelvis skriva ner saldot...
{
    FILE *pekare;
    pekare = fopen ("SALDO.txt","r");           

    if(pekare == NULL)                          
    {
        printf("\n_______________________\nKunde inte läsa in SALDO-Fil...\n_______________________\n");
        fclose(pekare);
        return 0;
    }

    double kollaSaldo;
    fscanf(pekare, "%lf",&kollaSaldo);          
    Sleep(1000);
    printf("SALDO \t\t= \t %.2lf kr\np\x86 ditt konto i EC-Banken.\n___________________________\nTryck 0 F\x94r Att Komma Tillbaka till Menyn\n: ", kollaSaldo);
    
    fclose(pekare);         // Lik till punkt och pricka som i de andra funktionerna.

    do    // Användaren får möjligheten att komma tillbaka till "menyn" tills denne trycker på 0. Vid Felaktig inmatning så görs detta om och om igen.
    {
        int noll;
        scanf("%d", &noll);
        fgetchar();         // Fångar bokstavens värde.

        if(noll == 0)
        {       
            printf("_______________________\n\x8Fter till menyn\n_______________________\n");
            return 1;   // returnerar tillbaka 1 till "menyn"
        }

        if((noll < 0) || (noll > 0))
        {
            Sleep(1000);
            printf("Du angav en felaktig siffra.\nF\x94rs\x94k igen!\n: ");
        }

    }while(true);

}