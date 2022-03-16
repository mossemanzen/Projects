# Niklas Månzén Uppgift 2 - Detta är en subsriber till MQTT samt en socket som hanterar meddelandet från ESPN(Publiceraren) och skickar vidare informationen till Socketservern.
# Detta script kräver att socketservern är igång sedan innan. Annars hänger det sig eller krashar. Detta script är likt från förgående uppgift med har nu inkluderat socketprogrammering.

import paho.mqtt.client as mqtt # Gör ett alias för paho.mqtt.client 
import socket # importerar socket för att kunna hantera socketoperationer och alla dess funktioner

MAXBYTE = 64 # Bestämmer hur många bytes som är mitt max.
PORT = 8090 # Min port i MITT nätverk. Kan behöva ändras för ditt nätverk.
FORMAT = 'utf-8' # Använder 1,2,3 eller 4 bytes för att encoda eller decoda och är standard.
SERVER = "192.168.50.73" # BEHÖVER ÄNDRAS beroende på vart serverprogrammet körs. Detta är min Laptops lokala IPadress i mitt hemmanätverk.
ADDR = (SERVER,PORT) # ADDR är en tuple

mqttBroker = "test.mosquitto.org" # Tilldelar mqttbroker samma brokerserver som ESP.
subclient = mqtt.Client("Android_Smartphone") # Tilldelar variabeln client till mqtt-clienten. Hittar också på ett namn till client.
subclient.connect(mqttBroker) # Uppkopplar min client på samma server som ESPn genom inbygdda connectfunktion från paho.mqtt.client

sockclient = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # Vad för typ server "letar" efter. AF_INET är en adressfamilj som är IPV4! Standardvärde sock_stream. "Vi streamar data genom socketen."
sockclient.connect(ADDR) # Passar in ADDRtuple (server & port).

def skicka_meddelande(medd): # Funktion för att skicka meddelande till socketserver
    meddelande = medd.encode(FORMAT) # Tilldelar meddelande encodningen av medd till bytes via encode i formatet UTF-8.
    medd_length = len(meddelande) # Behöver veta längden av meddelandet. Len returnerar en int.
    
    skicka_length = str(medd_length).encode(FORMAT) # Tilldelar "storleken av skicka" "encodningen" av medd_length med str
    skicka_length += b' ' * (MAXBYTE - len(skicka_length)) # Nu måste det matcha med 64 bytes som är mitt MAX. 
    # MAXBYTE subtraheras med längden av skicka_length som sedan adderar DET värdet TILL skicka_length så det ÄR 64.
    
    sockclient.send(skicka_length) # Sen passas den matchade längden i bytes av det faktiska meddelandet jag vill skicka in i sockclient.send()funktion.
    sockclient.send(meddelande) # och sedan det faktiska meddelandet jag vill skicka i client.send()funktion. Båda i Byteformat för det är så sockets funkar.
    
    print(sockclient.recv(1024).decode(FORMAT)) # Skriver ut meddelandet som skickas från socketSERVER genom recievefunktion med ett högt bytevärde & använder decode() och standard UTF8 .

def on_message(client, userdata, mqttmeddelande): # Funktion som skriver ut ämnet från MQTTbrokerservern. Och för att kunna hantera själva mqttmeddelandet. 
    print("MEDDELANDE från PublishClient Mottaget")
    print(f"Från ämnet - {mqttmeddelande.topic}") # Det viktiga här är meddelandet från mqttpubclienten(ESPN)
    
    print("~~ SKICKAR TILL SOCKETSERVER ~~") # Hanterar sedan mqttmeddelandet med payloadfunktion genom att decoda den till en sträng med UTF8
    faktiskameddelandet = str(mqttmeddelande.payload.decode(FORMAT)) # tilldelar mqttmeddelandet till en ny variabel för att förstå det hela lättare.
    skicka_meddelande(faktiskameddelandet) # Det faktiskta meddelandet som ska skickas vidare till socketSERVER passas in i skicka_meddelandefunktion. Som sedan socketSERVER tar hand om.

subclient.subscribe("TheUnStoppAbleForce/TEMP") # Subscribar på samma ämne/topic som ESP för att kunna "kommunicera"/"läsa av det som publiceras dit".
print("\t~~ [INVÄNTAR MEDDELANDE] ~~ ")
subclient.on_message = on_message # subclient on_messagefunktion tilldelas MIN on_messagefunktion. Där kan vi hantera topic & mqttmeddelande etc.

subclient.loop_forever() 

# subclienten loopas för evigt. Vilket gör att programmet kan fortsätta göra det den gör så länge Publishern(ESPN) publicerar meddelanden till MQTTservern i mitt ämne/topic.
# ...Och så länge det är en lyckad connection till mqttserver. Vilket kan vara problematiskt ibland. Då gäller det att starta om alla program igen samt simulator.