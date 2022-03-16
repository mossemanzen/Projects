"""
Niklas Månzén - Examinationsuppgifter - Uppgift2
D2CsimpleMessage.py

Detta program skickar 3st slumpmässiga hastigheter som meddelande till IoTHuben som i sin tur
hanterar den informationen vidare.
"""
import os
import asyncio
import time
import uuid
import random
from azure.iot.device.aio import IoTHubDeviceClient
from azure.iot.device import Message #importerar de biblioteken som behövs för att skicka dessa meddelanden på mitt sätt.

#

connection_string = "HostName=niklasIotHub.azure-devices.net;DeviceId=niklasm_device;SharedAccessKey=nmBLV2EHG/eIc9fVK1kj7jMNs8qzGVJtp9w5xjoKobE="
# Tilldelar denna client min connection string från min primary connection string.(Device)

async def main():
    device_client = IoTHubDeviceClient.create_from_connection_string(connection_string)
    # Tilldelar device_client metoden create_from_connection_string från IoTHubDeviceClient bibliotek och passar in MIN connection_string i dess argument.

    # Kopplar upp clienten med hjälp av connect()metod från IoTHubDeviceClient. 
    await device_client.connect()
    
    # Await & async är en del av asyncio. Await är som en checkpoint där det är säkert för asyncio att gå från en funktion till en annan. Så länge async finns med.
    
    print("-----------------------------------------------------")
    print("\t\t~~ WELCOME! ~~")
    print("-----------------------------------------------------")
    time.sleep(1)
    print("The recorded speed data will be sent to niklasIotHub.")
    time.sleep(1)
    input("Press enter to execute the order...")
    print("-----------------------------------------------------")

    # Skickar 3 Meddelanden med, förhoppningsvis, 3 olika hastigheter tack vare random-bib. (mellan 100-200km/h)
    for i in range(1, 4):
        print(f"\t... Sending Message nr : {str(i)} ...")
        msg = Message(random.randrange(100, 200))
        msg.message_id = uuid.uuid4()
        msg.correlation_id = "Correlation-1234"
        msg.custom_properties["Speed-Warning"] = "Yes"
        msg.content_encoding = "utf-8"
        msg.content_type = "application/json"   # Bestämmer Messages olika värden och hur contentet skickas (JSON)
        await device_client.send_message(msg) 
        time.sleep(1)
    
    print("-----------------------------------------------------")   
    print("Messages successfully sent!")
    time.sleep(1)
    print("\t\t~~ Farewell ~~") # Artigheter
    print("-----------------------------------------------------")

    await device_client.shutdown() # Stänger ned clienten.

if __name__ == "__main__": # Mainmetoden.
    asyncio.run(main())