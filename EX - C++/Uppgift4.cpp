#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <tuple>

/* Niklas Månzén Tentamen C++ Uppgift4.cpp
Temperatursensorprogram som sorterar i temperaturordning vid programslut beroende på vad användaren skrivit in.
Användaren får skriva in 6 celciustemp.värden lästa från 6 olika rum & 6 olika våningar. 
Mätområden: under 0 grader, 0 till 10 grader, 11 till 20 grader, 21 till 30 grader och över 30 grader. */

int below_zero, zero_to_ten, elev_to_twe, twentyone_thir, above_thir = 0; // Olika Counters för : < 0 grader, 0 - 10 grader, 11 - 20 grader, 21 - 30 grader & >30 grader.

std::vector<std::tuple<int,std::string, int>> input;  // "Vector Tuple" - För Input!

void input_()
{
    for (int i = 0; i < 6; i++) // Loopar 6 gånger så användaren får skriva in sina 6 olika värden genom cin. Vi hoppas att användaren inte skojar med oss.
    {
        std::string room_input;
        int floor_input, celsius_input;     // Temporära variablar för input till "vector-tuplen"

        std::cout << "Which ROOM : ";
        std::cin >> room_input;

        std::cout << "Which FLOOR : ";
        std::cin >> floor_input;

        std::cout << "Which TEMP. in Celsius : ";
        std::cin >> celsius_input;

        if (celsius_input < 0)  // Increasar mina sensorcounters beroende på vad användaren skriver in.
        {
            below_zero++;   // Under 0 grader
        }
        else if (celsius_input >=0 && celsius_input <=10)
        {
            zero_to_ten++;  // 0 till 10 grader
        }
        else if (celsius_input >= 11 && celsius_input <= 20)
        {
            elev_to_twe++; // 11 till 20 grader
        }
        else if (celsius_input >= 21 && celsius_input <= 30 )
        {
            twentyone_thir++; // 21 till 30 grader
        }
        else if (celsius_input > 30)
        {
            above_thir++; // över 30 grader.
        }

        input.push_back(std::make_tuple(celsius_input,room_input,floor_input)); // pusharbackar min tuple vector med hjälp av make_tuple med värdena användaren skriver in!

        std::cin.clear();
        std::cin.ignore(500,'\n');  // Resnar input efter varje gång loopen körs.
    }
}

void print_sensor_sum(int gen_count, int min_temp, int max_temp) // En funktion för att skriva ut meningar för antalet sensorer vid respektive Temperaturområden. 
{
    std::string sensor;
    if (gen_count == 1)   // Om generella countern är 1 blir det singular vid utskrift. Annars plural.
    {
        sensor = "Sensor";     
    }
    else if (gen_count > 1)
    {   
        sensor = "Sensors";
    }

    if (min_temp < 0) // Om minsta temp är under 0. Skrivs denna mening.
    {
        std::cout << gen_count << " " << sensor << " has registered a Temperature below 0 Degree Celsius." << std::endl;
    }
    else if (max_temp > 30) // Om max temp är över 30. Skrivs denna mening.
    {
        std::cout << gen_count << " " << sensor << " has registered a Temperature above 30 Degree Celsius." << std::endl;
    }
    else // Annars skrivs de andra värdena vi passar in. Vilket är våra olika mätområden.
    {
        std::cout << gen_count << " " << sensor << " has registered a Temperature from " << min_temp << " to " << max_temp << " Degree Celsius." << std::endl;
    } 
}

void output()
{   
    std::cout << "__________________________________________________________________\n";
    std::cout << "ROOM\t\t" << "FLOOR\t\t" << "TEMPERATURE\n\n";

    sort(input.begin(), input.end()); // Med hjälp av sort så sorterar den det första elementet by default som är Temperatur från "vector tuplen"

    int tot_counter = 0;    // Skapar en total counter så att utskrift genom printfunktionen ej görs flertal gånger.
    for (auto h : input) // Använder mig av en autoloop för att hämta de olika datatyperna vi har sparat i vår tuple.
    {
        int x = std::get<0>(h); // x = Temperatur
        std::string y = std::get<1>(h); // y = Rum
        int z = std::get<2>(h); // z = Våning 

        std::cout << y << "\t\t" << "Lvl." << z << "\t\t" << x << " Celsius."<<"\n"; // Som sedan skrivs ut i respektive ordning. 
        tot_counter++; // Total counter ökas vid varje loop.

        if (tot_counter == below_zero) // Om det totala antalet ÄR below_zero så har vi skrivit ut ALLA below_zero
        {
            print_sensor_sum(below_zero,-3000,0); // Passar in repsektive countersensor & respektive mätområde i printfunktions argument så det skrivs ut korrekt. (min temp måste vara negativ vid below_zero)
        }
        else if (tot_counter == below_zero + zero_to_ten)   // Om totala antalet ÄR below_zero & zero_to_ten så har vi skrivit ut dessa också.. osv (Detta gäller för alla else if block nedan)
        {
            print_sensor_sum(zero_to_ten,0,10); // Mellan 0-10
        }
        else if (tot_counter == below_zero + zero_to_ten + elev_to_twe)
        {
            print_sensor_sum(elev_to_twe, 11, 20);  // Mellan 11-20
        }
        else if (tot_counter == below_zero + zero_to_ten + elev_to_twe + twentyone_thir)
        {
            print_sensor_sum(twentyone_thir, 21, 30); // Mellan 21-30
        }     
        else if (tot_counter == below_zero + zero_to_ten + elev_to_twe + twentyone_thir + above_thir)
        {
            print_sensor_sum(above_thir, 31, 3000); // Max temp måste vara över 30 för denna utskrift.
        }
    } 

    std::cout << "__________________________________________________________________\n\n";  
}

int main()
{   
    std::cout << "--- Hi & Welcome To The Sensor Program! ---" << std::endl;    // Instruktioner!
    std::cout << "You need to enter in which ROOM you have measured the temperature." << std::endl;
    std::cout << "You need to enter in which FLOOR you have measured the temperature." << std::endl;
    std::cout << "You need to enter which TEMPERATURE in CELCIUS" << std::endl;
    std::cout << "...This will be asked this SIX Times...\n";
    char answer;

    do
    {
        std::cout << "Are You Prepared? Y/N : " << std::endl;   // En relativt komisk meny.
        std::cin >> answer;
        switch (toupper(answer))
        {
            case 'Y':
                std::cout << "--- Let's go! ---\n";
                break; // breakar oss ut ur switch om användaren skriver y / Y

            case 'N':
                std::cout << "--- You Were Not Prepared! ---\n...Closing Application...";
                return 0;   // Returnerar 0 och stänger programmet.

            default:
                std::cout << "You need to enter if you are Prepared or Not! Try again..." << std::endl;
                break; // breakar oss ut ur switch om det skrivs in något annat.
        }

    } while (toupper(answer) != 'N' && toupper(answer) != 'Y'); // Loopas så länge answer IS NOT N/n & Y/y
          
    input_();

    output();   // Kallar på respektive funktion.

    std::cout << "\t--- I Bid Thee Farewell! ---" << std::endl;

    return 0;
}