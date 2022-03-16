#include <iostream>
#include <cmath>

/* Niklas Månzén C++ Uppgift1.cpp

Detta program räknar ut Volt, Ampere, Watt &
Resistans beroende på val från användaren och vad användaren skriver in för värden.
Baserat på Ohms lag. */

class Ohmslag 
{
    private:
        double ampere, volt, resistans, watt, svar; // Kör på doubles för stora & mer nogranna uträkningar & svar.

    public: // Här i public finns alla classmetoder för att räkna ut respektive enhet!
        void calc_volt() // U = R*I | U = P/I | U = √R*P | Utgår från uppgiften
        {
            std::cout << "Ange Ampere(I) : ";
            std::cin >> this->ampere;   // Det användaren skriver in är DENNA (respektive privata variabel). Gäller för alla klassmetoder nedan.

            std::cout << "Ange Resistans(R) : ";
            std::cin >> this->resistans;

            this->svar = resistans * ampere;    // Kalkuleringen görs här! R*I

            std::cout << "Antal Volt(V) baserat p\x86 dina v\x84rden : " <<  svar << " Volt."<< std::endl;
            std::cout << "Utr\x84kningen \x84r nu klar!"<< std::endl;  
            return; // Returnerar tillbaka till loopmenyn
        }

        void calc_ampere() // I = U/R | I = P/U | I = √P/R | Utgår från uppgiften
        {
            std::cout << "Ange Volt(V) : ";
            std::cin >> this->volt;

            std::cout << "Ange Resistans(R) : ";
            std::cin >> this->resistans;

            this->svar = volt / resistans;  // Kalkuleringen görs här! U/R

            std::cout << "Antal Ampere(I) baserat p\x86 dina v\x84rden : " <<  svar << " Ampere."<< std::endl;
            std::cout << "Utr\x84kningen \x84r nu klar!"<< std::endl; 
            return;
        }

        void calc_watt() // P = U*I | P = U²/R | P = R*I² | Utgår från uppgiften
        {
            std::cout << "Ange Volt(V) : ";
            std::cin >> this->volt;

            std::cout << "Ange Resistans(R) : ";
            std::cin >> this->resistans;

            this->svar = volt * resistans; // Kalkuleringen görs här! U*I

            std::cout << "Antal Watt(P) baserat p\x86 dina v\x84rden : " <<  svar << " Watt." << std::endl;
            std::cout << "Utr\x84kningen \x84r nu klar!"<< std::endl;  
            return;
        }

        void calc_resistans() // R = U/I | R = P/I² | R = U²/P | Utgår från uppgiften
        { 
            std::cout << "Ange Volt(V) : ";
            std::cin >> this->volt;

            std::cout << "Ange Ampere(I) : ";
            std::cin >> this->ampere;

            this->svar = volt / ampere; // Kalkuleringen görs här! U/I

            std::cout << "Antal Watt(P) baserat p\x86 dina v\x84rden : " <<  svar << " Ohm." << std::endl;
            std::cout << "Utr\x84kningen \x84r nu klar!"<< std::endl; 
            return;
        }

        void meny() // Gör en meny som loopas tills användaren Vill Avsluta. Om man vill testa mer!
        {
            char answer;
            while (toupper(answer) != 'E')  // Använder mig av toupper för att få bokstäverna att bli VERSALER. Så länge answer IS NOT E : Exit - körs menyn.
            {
                std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~\n";
                std::cout << "Var god g\x94r ett val : \n\nV : R\x84kna ut Volt\nI : R\x84kna ut Ampere\nP : R\x84kna ut Watt\nR : R\x84kna ut Resistans\nE : Exit\n";
                std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~\n";
                std::cin >> answer;

                switch (toupper(answer))    // Beroende på val av användaren körs respektive Omhslag-klass-metod!
                {
                    case 'V' :
                        calc_volt();
                        break;
                    
                    case 'I' :
                        calc_ampere();
                        break;
                    
                    case 'P' :
                        calc_watt();
                        break;

                    case 'R' :
                        calc_resistans();
                        break;
                    
                    case 'E' :
                        break;
                    
                    default:
                        std::cout << "Du m\x86ste g\x94ra ett Val!\n";
                        std::cin.clear(); // Rensar input.
                        std::cin.ignore(1000,'\n');
                        break;
                }

                std::cin.clear();
                std::cin.ignore(1000,'\n'); // Rensar input mellan varje loop för extra säkerhet.
            }   
        }
};

int main()
{
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~\n--- Hej & V\x84lkommen! ---" << std::endl; 

    class Ohmslag user1;    // Instansierar ett objekt (user1) från min klass.

    user1.meny(); // Kallar på klassmetoden genom objektet user1.

    std::cout << "--- Farv\x84l! ---\n" << std::endl; 

    return 0;
}