# Niklas Månzén Uppgift 2 - Detta är en socketserver som hanterar meddelandet som kommer från subsocketClient.py. Detta program bör köras först.
import socket
import threading

MAXBYTE = 64 # Bestämmer hur många bytes som är mitt max.
PORT = 8090 # Min port i MITT nätverk. Kan behöva ändras.
SERVER = socket.gethostbyname(socket.gethostname()) # Hämtar den lokala IP oavsett där programmet körs.
ADDR = (SERVER, PORT) # ADDR är en tuple
FORMAT = 'utf-8' # Använder 1,2,3 eller 4 bytes för att encoda eller decoda och är standard.

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # Vad för typ server "letar" efter. AF_INET är en adressfamilj som är IPV4! Standardvärde sock_stream. "Vi streamar data genom socketen."
server.bind(ADDR) # Binder socketen till ADDRvariabeln. Vad som connectar till denna adress kommer att bindas till denna socket.

def hantera_klient(conn,addr): # Hanterar all kommunikation mellan klient och server. Körs pararellt för varje klient tack vare threading.
    print(f"~~ NY UPPKOPPLING :{addr} Uppkopplades. ~~\n") 
# Skriver ut vilken uppkoppling som just precis "connectade". Genom f-string (formaterad strängliteral) är det möjligt att skriva ut variablar på detta vis.
    
    uppkopplad = True
    while uppkopplad: # Allt detta loopas och är igång hela tiden tills vi stänger ned programmen. Servern kan ta emot flera "temperaturer" (meddelanden)...
        medd_length = conn.recv(MAXBYTE).decode(FORMAT) 
        # Medans uppkopplad tas det emot längden av meddelande genom recieve. MAX 64 BYTES. Som också decodas enligt FORMATET UTF-8.
        if medd_length: # Kollar om ett meddelande har något innehåll överhuvudtaget.
        
            medd_length = int(medd_length) # DÅ Konverteras det sedan till en integer.
            medd = conn.recv(medd_length).decode(FORMAT) # Hur många bytes från Det "riktiga" meddelandet! Tas emot genom recieve med medd_length som passas in, decodas genom UTF-8 tilldelas till medd.
            
            vilken_lampa = int(medd) # Konverterar meddelandet genom int()funktion, till en int. Tilldelar DET värdet till en ny variabel - För att skriva ut korrekt lampa som tändes hos ESPN.
            
            if (vilken_lampa < 0): # Värden under 0 = Röd Lampa
                print(f"~~ FRÅN : {addr} - Temperaturen är : {medd} Grader Celcius. RÖD Lampa Tändes. ~~")
            else: # Allt annat = Grön Lampa.
                print(f"~~ FRÅN : {addr} - Temperaturen är : {medd} Grader Celcius. GRÖN Lampa Tändes. ~~")
                              
            conn.send("[SERVER] --- TEMP. MOTTAGET! ---".encode(FORMAT)) 
            # Skickar en bekräftelse till client/connectionen att temperatur har tagits emots av servern. Genom .send() och encode() med standardformatet UTF8. Detta tas emot i "sobsocketCLIENT"-programmet
            
    conn.close() # Stänger ned den nuvarande uppkopplingen. Vet inte om denna fyller någon funktion eftersom det loopas i evighet...
        
def starta(): # Lyssnar på uppkopplingar och hanterar dessa uppkopplingar till hantera_klient funktion med threading.
    server.listen()
    print(f"~~ LYSSNAR PÅ {SERVER} ~~")
    while True:
        conn, addr = server.accept() # När en ny uppkoppling sker, lagras den adressen (IP & PORT) i addr  
                                    # Sedan lagras det i ett objekt som låter programmet att skicka tillbaka information till den uppkopplingen
        thread = threading.Thread(target=hantera_klient, args=(conn, addr)) 
        thread.start()
# Threading låter flera saker hända samtidigt. Det passas vidare för varje uppkoppling till hantera_klientfunktion och skriver in dess argument i Thread.
        print(f"~~ AKTIVA UPPKOPPLINGAR : {threading.active_count() - 1} ~~") # Berättar hur många threads som är aktiva i denna "process" -1 eftersom threadstart aktivt lyssnar hela tiden.

print("\t---\ SERVERN STARTAR /---")
starta() # Kör igång servern!