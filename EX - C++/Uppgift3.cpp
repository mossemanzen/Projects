#include <iostream>
#include <string>

/* Niklas Månzén Tentamen C++ Uppgift3.cpp
Detta program räknar ut hur mycket du kan ta ut i pension
på ett ungefär "innan allmänna pensionen" */

class Pension
{
    private :
        std::string name;
        int lived_years,salary, working_years;    // Håller dessa variablar privata!
        
    public :
        void set_name(std::string name_)    // Leker med flera metoder och bestämmer argument för de. 
        {
            this->name = name_; // Tilldelar nya publika variablar som pekar på de privata. Gäller i samtliga metoder.
        }

        void set_age(int year_,int month_, int day_)  // Överslagsräknar på hur gammal personen är. Kunde inte lösa hur jag kunde göra om personen fyllde 18 år PÅ DENNA DAGEN.
        {
            int age = 2021 - year_; 
            this->lived_years = age; // Privata levda år "hur gammal personen är" ÄR age
        }

        void set_salary(int salary_)
        {
            this->salary = salary_; // Det vi passade in ÄR och förblir den privata salaryn.
        }

        void set_working_years(int working_years_)
        {
            if (working_years_ >= this->lived_years)   // Om arbetade år är högre ,eller lika med, än levda år
            {
                throw 'C';  // Throwar tillbaka en char som char catch tar emot samt returnerar funktion
                return;
            }
            
            this->working_years = working_years_; // Annars så är den "passade workings_years_" den privata working_years
        }

        void calc_pension() // Överslagsuträkning på pensionen. Vi vet omöjligt hur exakt nationalekonomin kommer att vara livet ut. Samt hur mycket personen sparar extra i månaden etc.
        {
            int old_when_started_w, wy_l_to_65;
            unsigned long int pension, tot_salary, year_salary;

            year_salary = this->salary * 12; // Kalkulerar årslön

            old_when_started_w = this->lived_years - this->working_years; // Hur gammal personen var när den började arbeta

            wy_l_to_65 = 65 - old_when_started_w; // Antal working years kvar till 65

            tot_salary = year_salary * wy_l_to_65;  // Tot. inkomsten totalt. Vi utgår från att personen jobbar konstant fram tills den dagen.

            pension = tot_salary * 0.35; // 65% av den Totala inkomsten.

            pension /= 24; // "Års-Pensionen". 65-89 = 24 år av egen pension innan Allmänna. 

            pension /= 12; // Vad personen får i månaden! CA...

            std::cout << "When " << this->name << " goes in pension. The calculated pension could be approximately : " << pension << " SEK before taxes.\n"; 
        }
};

int main()
{
    std::cout << "\t--- WELCOME! ---\nThis program will calculate your PENSION!\n";
    Pension user1; // Instansierar ett objekt (user1) från min klass Pension.

    std::string temp_name;  // Gör temporära variablar som jag passar in i respektive klassmetods argument.
    int temp_age,temp_ybirth, temp_mbirth, temp_dbirth, temp_salary, y_of_service;
    
    try
    {
        std::cout << "What is your name? : ";   // Här får vi hoppas att användaren inte skämtar-aprillo med oss!
        getline(std::cin, temp_name); // Tar hela raden tills användaren "endar line"
        user1.set_name(temp_name); // Kallar på klassmetoden set_name från objektet user1 och passar in input (temp_name). Gäller för alla frågor nedan.

        std::cout << "What's your date of birth? (XXXX MM DD) With spacing! : ";
        std::cin >> temp_ybirth >> temp_mbirth >> temp_dbirth; 

        if (temp_ybirth <= 1920 || temp_ybirth >= 2004) 
        {   // Om året är lika med eller under 1920 (Förmodligen DÖD) ELLER om året är 2004 eller över (Under 18)
            throw 1; // Ifsats Throwar ett heltal som int catchen tar emot och stänger programmet. För vi kommer inte vidare efter det med frågorna.
        }
        else if (temp_mbirth <= 0 || temp_mbirth > 12)  // Om månad är 0 eller under ELLER om månad är ÖVER 12
        {
            throw 1;
        }
        else if (temp_dbirth <= 0 || temp_dbirth > 31)  // Om dagen är 0 eller under ELLER om dagen är över 31
        {
            throw 1;
        }
        
        user1.set_age(temp_ybirth,temp_mbirth,temp_dbirth); // Kommer vi förbi våra ifs passas inputs in i respektive klassmetod som kallas genom classobjektet!

        std::cout << "What is your salary? IN SEK (No Taxes) : ";
        std::cin >> temp_salary;

        if (temp_salary <= 0)
        {
            throw "Throwing To Default Catch"; // Om salary är 0 eller mindre throwas det till default catch och stänger programmet. För vi kommer inte vidare efter det med frågorna.
        }
        
        user1.set_salary(temp_salary);   // Kallar på klassmetoden set_salary från objektet user1 och passar in input (temp_salary).
        

        std::cout << "How many years have you been in service? : ";
        std::cin >> y_of_service;

        if (y_of_service <= 0) 
        {
            throw "Throwing To Default Catch"; // Om arbetare år är 0 eller mindre throwas det till default catch. Och stänger programmet.
        }

        user1.set_working_years(y_of_service); // Kallar på klassmetoden set_working_years från objektet user1 och passar in input (y_of_service).

        user1.calc_pension(); // Kallar på klassmetoden från objektet user1 som räknar ut ev. pension.
    }

    catch (int error) // int catch.
    {
        std::cout << "-----------------------------------------------------\n";
        std::cout << "\tWrong date of birth.........\n\t\tClosing application.\n";
        std::cout << "----------------------------FAREWELL-----------------\n";
    }

    catch (const char error) // const char catch.
    {
        std::cout << "-------------------------------------------------------------------------\n";
        std::cout << "Incorrect : You can't possible been working longer than you have lived!\n\t\tClosing application.\n";
        std::cout << "-------------------------------FAREWELL----------------------------------\n";
    }

    catch (...) // Default catch.
    {
        std::cout << "-----------------------------------------------------\n";
        std::cout << "Error : Can't calculate your Pension with that value!\n\t\tClosing application.\n";
        std::cout << "-------------------------FAREWELL--------------------\n";
    }

    // Kommer man till respektive catch kommer inte programmet fortsätta att fråga nästa fråga. Programmet stängs ned.

    return 0;
}