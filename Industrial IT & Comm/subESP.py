import paho.mqtt.client as mqtt # Gör ett alias för paho.mqtt.client 

mqttBroker = "test.mosquitto.org" # Tilldelar mqttbroker samma brokerserver som ESP.
client = mqtt.Client("Android_Smartphone") # Tilldelar variabeln client till mqtt-clienten. Hittar också på ett namn till client.
client.connect(mqttBroker) # Uppkopplar min client på samma server som ESPn genom inbygdda connectfunktion från paho.mqtt.client

def on_message(client, userdata, message): # Skriver ut meddelandet från ämnet som skickades till MQTTbrokerservern. 
    print("-------------------------------------------")
    print("[MESSAGE] :", str(message.payload.decode("utf-8")), "\nFrom the topic -", message.topic)

"""
Client & Userdata argumenten behöver inte tas hänsyn till i detta fall. Det viktiga är meddelandet. 
Skriver ut payload av meddelandet och avkodar det samt vilket topic/ämne det handlar om. 
"""

client.subscribe("TheUnStoppAbleForce/BUTTON") # Se nedan.
client.on_message = on_message  
client.loop_forever() 

"""  
Subbar till samma topic/ämne som ESPn.
.on_message funktionen från paho.mqtt.client tilldelas till min on_message-callback-funktion. 
Så länge vi får ett meddelande i topic/ämnet medans vi subscribar kommer on_message-funktionen att köras.  
loop_forever() är en del av paho.mqtt.client och körs tills användaren stänger ned programmet.
"""