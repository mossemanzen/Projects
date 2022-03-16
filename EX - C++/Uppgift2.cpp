#include <iostream>
#include <string>
#include <vector>
#include <exception>

/* Niklas Månzén C++ Uppgift2.cpp
Sparar information om husdjur och skriver ut all info om de husdjuren användaren skrivit in.*/

class Djur // Basklassen Djur
{
    private:
        int antal_husdjur_;
        std::vector <int> ålder_;
        std::vector <std::string> namn_, kön_; // Privata Vectorer för att tillhandahålla fler husdjur om användaren vill.
    public:
        std::vector <int> ålder = this->ålder_;
        int antal_husdjur = this->antal_husdjur_;
        std::vector <std::string> namn = this->namn_;
        std::vector <std::string> kön = this->kön_;     // Skapar publika variablar så att de kan nås publik och tilldelar de de privata.
};

bool omNummer(const std::string& String) // Denna funktion kollar om det finns en siffra i strängen som passas in ( som användaren skriver in vid input-metod).
{
    for(const char &c : String) // Loopar igenom den refererade strängen i en for loop via refererade const char c.
    {
        if (std::isdigit(c) == 1)    
        {
            return true;    // Om String innehåller EN siffra i någon av dess chars så returnerar isdigit = 1 vilket i sin tur returnerar true tillbaka. 
        }
    }

    return false;  // Om strängen inte innehåller några siffror alls returneras false. Det finns inga siffror i strängen! 
} 

class Husdjur : public Djur // Husdjur ärver från Basklassen - Djur
{
    private :
        std::vector <std::string> typ;  // Typ av husdjur sparas i en private string vector!  
    public:
        void input() // Input-metod!
        {   
            char user_input;
            std::string input_namn, input_kön,input_typ;
            int input_ålder;    // Definierar mina inputvariablar.
            antal_husdjur = 0; // Startar counter på 0.

            while (toupper(user_input) != 'N') // Allt sker inom en enda stor while. Körs så länge user_input IS NOT N / n. Hör ihop med sista frågan.
            {
                antal_husdjur++; // Ökar counter på husdjur varje gång loopen körs.
                bool korrektInput;  // Använder en boolean för att kunna loopa frågorna i respektive do-while vid respektive try-block!

                do  // Använder mig av en do-while för respektive try-catch-block för att kunna loopa respektive fråga gång på gång.
                {
                    try
                    {
                        std::cout << "Vad heter ditt husdjur? : "; // Namn-try-blocket.
                        std::cin >> input_namn;

                        if (omNummer(input_namn) == true) // Om omNummer ger tillbaka sant throwar vi invalid_argument.
                        {
                            throw std::invalid_argument("Kan EJ best\x86 av siffror!");   
                        }

                        korrektInput = true; // OM det går vägen med strängen tilldelas korrektInput till true!
                        namn.push_back(input_namn); // Annars pushbackas input_namn längst bak i publika strängvectorn "namn" från Djur och nästa fråga ställs.                         
                    } 

                    catch(const std::exception& e)
                    {
                        std::cin.clear(); // Rensar input och användaren får skriva in input igen.
                        std::cin.ignore(10000, '\n');
                        korrektInput = false;   // korrektInput tilldelas till false!
                        std::cerr << e.what() << '\n'; // Invalid_argument skrivs ut genom cerr & e.what().
                    }
                    
                } while (korrektInput != true); // Körs så länge korrektInput IS NOT true. Gäller i alla try-blocks nedan.           

                do
                {
                    try // Ålder-Try-Blocket. Använder mig av namn.back() för att få det senaste namnet tillagd i vectoren.
                    {   
                        std::cout << "\n\x8Flder p\x86 " << namn.back() << " : "; 
                        std::cin >> input_ålder;

                        if (std::cin.fail()) // Om cin.fail() får in fel datatyp (strings/chars) throwas invalid_argument.
                        {
                            throw std::invalid_argument("Kan ej best\x86 av bokst\x84ver!");
                        }

                        korrektInput = true;
                        ålder.push_back(input_ålder); // Annars pushbackar input_ålder i den publika int-vectorn "ålder" från Djur. 
                    }

                    catch(const std::exception& e) // Rensar input och användaren får skriva in input igen.
                    {
                        std::cin.clear();
                        std::cin.ignore(10000, '\n');
                        korrektInput = false;
                        std::cerr << e.what() << '\n';
                    }
                    
                } while (korrektInput != true); // Som sagt. Så länge korrektInput IS NOT true loopas detta.
                             
                do  // Samma taktik som innan!
                {
                    try // Hona eller Hane-try-blocket
                    {
                        std::cout << "\n\x8Er " << namn.back() << " en Hona eller Hane? : "; 
                        std::cin >> input_kön;
                    
                        if (omNummer(input_kön) == true) // Samma taktik som innan!
                        {
                            throw std::invalid_argument("Endast Hona eller Hane \x84r ett k\x94n...");
                        }

                        korrektInput = true;
                        kön.push_back(input_kön); // Annars pushbackar input_kön i den publika kön-vectorn från Djur. 
                    }

                    catch(const std::exception& e) // Samma taktik som tidigare catchar!
                    {
                        std::cin.clear();
                        std::cin.ignore(10000, '\n');
                        korrektInput = false;
                        std::cerr << e.what() << '\n';
                    }   

                } while (korrektInput != true);
                
                do  // Samma taktik som innan!
                {
                    try // typ-try-blocket
                    {
                        std::cout << "\nVad \x84r " << namn.back() << " f\x94r typ av djur? : "; // Typ av djur
                        std::cin >> input_typ;

                        if (omNummer(input_typ) == true) // Samma taktik som tidigare tryblock!
                        {
                            throw std::invalid_argument("Kan ej best\x86 av siffror!");
                        }

                        korrektInput = true;
                        typ.push_back(input_typ); // MEN här pushbackas det till den privata strängvectorn "typ" från Husdjur.
                    }

                    catch(const std::exception& e) // Samma taktik som tidigare catchar!
                    {
                        std::cin.clear();
                        std::cin.ignore(10000, '\n');
                        korrektInput = false;
                        std::cerr << e.what() << '\n';
                    }

                } while (korrektInput != true);
                                           
                do  // En sista do while för den sista frågan!
                {
                    try
                    {
                        std::cout << "Vill du ange fler husdjur? (J/N)" << std::endl; 
                        std::cin >> user_input;
                    
                        if (toupper(user_input) == 'J') // Konverterar via toupper till VERSALER.
                        {
                            korrektInput = true;    // Tilldelas true för att komma ut ur denna do-while. Eftersom user_input är J/j så fortsätter den stora while-loopen att köras.
                        }
                        else if (toupper(user_input) == 'N')
                        {
                            korrektInput = true;    // Tilldelas true för att komma ut ur denna do-while. MEN user_input är N/j vilket gör att den stora whilen-loopen kommer att avbrytas.
                        }
                        else
                        {
                            throw std::invalid_argument("Felaktigt Val!");  // Throwar invalid argument så länge användaren skriver in fel information som vanligt!
                        }
                    }

                    catch(const std::exception& e)
                    {
                        std::cin.clear();
                        std::cin.ignore(10000, '\n');
                        korrektInput = false;
                        std::cerr << e.what() << '\n';  // Rensar cin, korrektInput blir false och invalid argument skrivs ut igen.
                    }
                                    
                } while (korrektInput != true);  // Körs så länge korrektInput IS NOT true.
            }
        }

        void print_out() // Utskrift-metod! Skriver ut alla olika husdjur.
        {
            std::cout << "_________________________________________" << std::endl;
            std::cout << "Antal Husdjur = " << antal_husdjur << " st." << std::endl; // Countern för husdjur visas

            for (int i = 0; i < namn.size(); i++) // Använder mig av den klassiska loopen istället för auto. Använder i för att få till sammanhängande publika vectorer från Djur & Husdjur.
            {
                std::cout << namn[i] << " \x84r en " << kön[i] << " som \x84r en "  << typ[i] << " p\x86 " << ålder[i] << " \x86r!"<< std::endl;
            }
            std::cout << "_________________________________________" << std::endl;
        }
};

int main()
{   // Tjusar till det lite!
    std::cout << ".......................................\n...V\x84lkommen till Husdjurprogrammet!...\n......................................." << std::endl;

    class Husdjur djur1;    // Instansierar ett objekt (djur1) från min Husdjurklass.

    djur1.input();
    djur1.print_out();  // Kallar på respektive klassmetod genom objektet djur1.

    std::cout << ".........................................\n..............FARV\x8EL.....................\n........................................." << std::endl;
    
    return 0;
}