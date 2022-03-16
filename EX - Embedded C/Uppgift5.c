#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <stdbool.h>
#include <time.h>

/*
* Fil: Uppgift5.c 
* Upphovsman: Niklas Månzén
* Kort beskrivning om programmet: Lottningsprogram!
* Ger användaren möjlighet att välja slumpmässiga nr eller välja själv för dragning.
* Sedan görs en dragning på slumpmässiga nr
* Användaren får reda på resultat.
* Ej 0 & Ej samma tal skall ges eller får skrivas.
*/

#define NUM 36 // Här kan man byta det slumpmässiga talet smidigt.

int* automatiskLottorad()     // 1. Funktion för automatisk Lottorad. Vi returnerar en pekare (automatisk)
{   
    
    int *automatisk = malloc(7*sizeof(int));      // Skapar ett allkolerat utrymme för pekaren "automatisk." (int fältvariabel av storlek 7x4 bytes.)

    for (int i = 0; i < 7; i++)         // Loopar igenom varje "element" 7 gånger. 
    {
        int slumpTal = rand()%NUM;      // slumpTal får ett slumpmässigt nummer från rand.
                                           
        bool lagligtTal = false;     // Vi använder oss av en bool. tilldelar lagligtTal till false. För att kontrollera talet enligt villkoren nedan.

        while(!lagligtTal)         
        {
            lagligtTal = true;   // Innocent until proven guilty! Vi litar inte på slumpen.

            if (slumpTal < 1)   // SlumpTal Får ej vara under 0
            {
                slumpTal = rand()%NUM;      //slumpTal får ett nytt slumpmässigt nummer.
                lagligtTal = false;         // Tilldelar lagligtTal till false
            }

            if (slumpTal > 35) // Slumptal får ej bli över 35      
            {
                slumpTal = rand()%NUM;
                lagligtTal = false;
            }
            
            for (int j = 0; j < i; j++) // Kontrollerar om nuvarande slumpTal finns i "automatisk"-fältvariabeln
            {
                if (slumpTal == automatisk[j])
                {
                    slumpTal = rand()%NUM;      
                    lagligtTal = false;
                }
            }

        }
         
        printf("Nummer %d : %d\n", i+1, slumpTal);                 
        Sleep(500);

        automatisk[i] = slumpTal; // Sparar slumpTal på plats "i" i "automatisk"-fältvariabeln       

    }

    printf("\nTryck Enter f\x94r att forts\x84tta...\n");      
    char enter;
    scanf("%c", &enter);
    getchar();
    fflush(stdin);               // Vet att den tar flertal tecken. Men visste inte hur jag skulle lösa det annars.   
    
    return automatisk;

}

int* manuellLottorad()   // 2. Funktion för manuell Lottorad. Vi returnerar också här en pekare. (manuell)
{
    printf("Ange 7st Olika Nummer Mellan 1 & 35, Tack!\n");
    Sleep(1000);
    int *manuell = malloc(7*sizeof(int));   // Skapar ett allkolerat utrymme för pekaren automatisk. (int fältvariabel av storlek 7x4 bytes).

    for (int i = 0; i < 7; i++)             
    {
        int nuvarandeTal;                   // Loopar igenom varje "element" 7 gånger. Men skapar en tillfällig int som i slutet tilldelas till "manuell"[i]
        printf("Ange Nr. %d\n: ", i+1);     
        Sleep(500);
        scanf("%d", &nuvarandeTal);
        
        bool lagligtTal = false;            // Använder en bool. tilldelar lagligtTal till false. För att komma in i While för kontroller.

        while (!lagligtTal)                 
        {
            lagligtTal = true;          // Innocent until proven guilty! Litar inte på användaren.

            if (nuvarandeTal > 35)      // Får ej vara över 35
            {
                printf("Du kan inte ange ett tal st\x94rre \x84n 35!\n"); 
                Sleep(500);
                printf("Ange Nr. %d\n: ", i+1);     // Får ny chans att skriva in nytt tal.
                Sleep(500);
                scanf("%d", &nuvarandeTal);
                lagligtTal = false;             // Ändrar lagligtTal till false för att köra loopen ytterligare en gång. Kontrollerar det NYA talet som användaren skrivit in.
            }

            if (nuvarandeTal < 1)       // Får ej vara under 1
            {
                Sleep(500);
                printf("Du kan inte ange ett tal mindre \x84n 1!\n");
                Sleep(500);
                printf("Ange Nr. %d\n: ", i+1);
                Sleep(500);
                scanf("%d", &nuvarandeTal);      // Får ny chans att skriva in nytt tal.   
                lagligtTal = false;             // Ändrar lagligtTal till false för att köra loopen ytterligare en gång. Kontrollerar det NYA talet som användaren skrivit in.
            }

            for (int j = 0; j < i; j++)         // Kontrollerar om nuvarandeTal finns i manuell-fältvariabeln
            {
                if (nuvarandeTal == manuell[j])  // Får ej vara något man skrivit in sedan innan! Vi jämför "nuvarandeTal" med "manuell"[j].
                {
                    Sleep(500);
                    printf("Du kan inte ange ett tal du redan angett!\nVar god f\x94rs\x94k igen.\n");
                    Sleep(500);
                    printf("Ange Nr. %d\n: ", i+1);
                    Sleep(500);
                    scanf("%d", &nuvarandeTal);        // Får en ny chans ännu en gång...
                    lagligtTal = false;     // Ändrar lagligtTal till false för att köra loopen ytterligare en gång. Kontrollerar det NYA talet som användaren skrivit in.
                }
            }

        }

        manuell[i] = nuvarandeTal;      // Sparar nuvarandeTal på plats "i" i manuell-fältvariabeln.
        
    }

    printf("\nTryck Enter f\x94r att forts\x84tta...\n");   
    char enter;
    scanf("%c", &enter);
    getchar();
    fflush(stdin);     // Vet att den tar emot fler tecken. Men visste inte hur jag skulle lösa det annars.     
    
    return manuell;
}

int* meny()  // Menyn som returnerar lottoRad.                                                                                
{
    Sleep(1000);
    printf("________________________________________\n\tVad vill du g\x94ra?\n________________________________________\n");
    Sleep(1000);
    printf("1. Ge mig en slumpm\x84ssig Lottodragning, tack!\n");
    Sleep(500);
    printf("2. Jag vill g\x84rna v\x84lja mina egna nummer sj\x84lv, tack!\n");
    
    int val;
    scanf("%d", &val);

    int* lottoRad;           // Vi deklarerar en int-pekare "lottoRad" som sedan, genom switchen, tilldelas resultatet av respektive funktion.

    switch (val)
    {
    case 1 :
        lottoRad = automatiskLottorad();
        break;
    
    case 2 :
        lottoRad = manuellLottorad();
        break;

    default:
        Sleep(500);
        printf("Du har tagit ett felaktigt beslut!\n Var god f\x94rs\x94k igen...\n");
        Sleep(1000);
        lottoRad = meny();              // Anropar menyn igen för att fånga felaktiga val.
        break;
    }

    return lottoRad;                                       
}

int* lottoDragning()        // Lottodragningen! Som returnerar "dragning".
{

        int *dragning = malloc(7*sizeof(int)); // Skapar ett allkolerat utrymme för pekaren automatisk. (int fältvariabel av storlek 7x4 bytes).

        printf("________________________________________\n\tLOTTODRAGNING!\n________________________________________\n");
        Sleep(1000);
    
    for (int i = 0; i < 7; i++)
    {
        int slumpTal = rand()%NUM;           
        
        bool lagligtTal = false;     // Vi använder oss av en bool. tilldelar lagligtTal till false. För att komma in första gången.

        while(!lagligtTal)         
        {
            lagligtTal = true;   // Innocent until proven guilty! Vi litar inte på slumpen.

            if (slumpTal > 35)   // slumpTal Får ej vara över 35
            {
                slumpTal = rand()%NUM;
                lagligtTal = false;
            }

            if (slumpTal < 1)   // slumpTal Får ej vara under 1
            {
                slumpTal = rand()%NUM;
                lagligtTal = false;
            }

            for (int j = 0; j < i; j++) // Kontrollerar om nuvarande slumpTal finns i dragning-fältvariabeln
            {
                if (slumpTal == dragning[j])
                {
                    slumpTal = rand()%NUM;
                    lagligtTal = false;
                }
                
            }
            
        }
           
        printf("Boll Nr %d blir... ", i+1);
        Sleep(1000);
        printf("%d\n",  slumpTal);
        Sleep(1000);
        dragning[i] = slumpTal; // Sparar slumptal på plats "i" i dragning

    }

    printf("________________________________________\n");

    return dragning;
}

int main(void)
{
    srand(time(0));      //Använder oss av srand och time för att få slumpmässiga (nya) nummer varje gång programmet körs. Genom klockan.
    printf("\tHEJ OCH V\x8ELKOMMEN\n\tTILL ECLottoBingo!\n");
    int* finalLottorad = meny();
    int* lottoDrag = lottoDragning();

    Sleep(1000);
    printf("Dina nummer \x84r:\n"); // Loopar ut talen där pekaren finalLottorad pekar mot.

        for (int i = 0; i < 7; i++)
        {
            printf("%d ", finalLottorad[i]);
        }

    Sleep(1000);
    printf("\nR\x84tt lottorad:\n");    // Loopar ut talen där pekaren lottoDrag pekar mot.

        for (int i = 0; i < 7; i++)
        {
            printf("%d ", lottoDrag[i]);
        }

    Sleep(1000);
    printf("\n________________________________________\nTack f\x94r att du spelade ECLottoBingo!\n________________________________________\n");
    
    free(lottoDrag);    // frigör heapminnena. Eftersom vi inte behöver de längre.
    free(finalLottorad);

    return 0;
}