""" 
Niklas Månzén IOTGBG - Examinationsuppgifter - Uppgift1
downloadAndReadBlob.py
Detta program Laddar ner Blob genom storage och läser Jsonfil (Ej annat format) 
"""

import os
import time
import json
from azure.storage.blob import BlobServiceClient, BlobClient  # VID IMPORTFEL!! använd - pip install azure-storage-blob --upgrade  - VID IMPORTFEL!!
from azure.storage.blob import ContentSettings, ContainerClient
 
# Importerar storage blob-bibliotek och använder serviceclient, blobclient, contentsettings samt containerclient.
# Importerar json för att kunna läsa av dess värde senare i koden.

MY_CONNECTION_STRING = "DefaultEndpointsProtocol=https;AccountName=niklasmstorage;AccountKey=tk7zfYPoM3yDIcEDuJEfzoSSG1Dgs+Yt+E6IPmA1KTmCDb5S9TeUK7liRmK2DAt/jZRGG/by931c6AQVL1Rgnw==;EndpointSuffix=core.windows.net"
# Använder mig av Connection String nu istället för key eftersom de inbyggda funktionerna och metoderna från bilbiotek kräver det.
 
MY_BLOB_CONTAINER = "niklasmblob" # min blobcontainer sedan innan
 
LOCAL_BLOB_PATH = os.path.abspath(os.path.curdir) # Där programmet körs, där skall blobs laddas ned.

JSONFILE = "tempfukt.json"

print("\t~~ Welcome! ~~") # Lite artigheter!
time.sleep(1)
print("---------------------------------------------")
print("It's now time to Download the blobs...")
time.sleep(1)
input("Press Enter To Execute!")
time.sleep(1)
print("---------------------------------------------")

class AzureBlobFileDownloader: # Skapar en class med olika metoder!
    def __init__(self):
        print("--- Executing Azure Blob File Downloader! ---")
        print("---------------------------------------------")
 
    #Initierar uppkopplingen till min Azure Storage Account
        self.blob_service_client =  BlobServiceClient.from_connection_string(MY_CONNECTION_STRING) # Tilldelar variabeln metoden från BlobServiceClienten med MIN CONNECTION STRING som argument
        self.my_container = self.blob_service_client.get_container_client(MY_BLOB_CONTAINER) # Tilldelar variabeln den förgående variabeln samt metoden från BlobserviceClienten med MIN BLOB CONTAINER som argument
 
    def saving_blob(self,file_name,file_content): # SparaBlobfunktion! Som senare används i nästa funktion
    # Hela sökfilsvägen för filen och vart den ska laddas ner
        download_file_path = os.path.join(LOCAL_BLOB_PATH, file_name)
 
    # För nestlade blobs skapas det en lokal väg
        os.makedirs(os.path.dirname(download_file_path), exist_ok=True)
 
        with open(download_file_path, "wb") as file:
            file.write(file_content) # Öppnar och skriver dess content.
 
    def download_blobs_in_container(self): # Laddar-ner-allt-funktion!
        my_blobs = self.my_container.list_blobs() #List_blobs är en metod från BlobServiceClient som listar blobs. På så sätt kan jag skriva ut vad jag laddar ner.
        time.sleep(1)
        print(f"Downloading to {LOCAL_BLOB_PATH}") # Mer utförlig information exakt vart det laddas ned någonstans.
        print("---------------------------------------------")
        time.sleep(1)
    
        for blob in my_blobs:
            print("Blob :\t" + blob.name) # Skriver ut respektive namn
            time.sleep(1)
            bytes = self.my_container.get_blob_client(blob).download_blob().readall() # Hanterar respektive blob
            self.saving_blob(blob.name, bytes) # Sparar blob genom förgående funktion.
        
        print("---------------------------------------------")
        print("SUCESS!")
        time.sleep(1)
        input("Press Enter To Read The JSON String...")
           
# Initierar klassen samt metoden.
azure_blob_file_downloader = AzureBlobFileDownloader()
azure_blob_file_downloader.download_blobs_in_container()

# öppnar min JSONfil och läser dess content.
time.sleep(1)
with open(JSONFILE, 'r') as openfile:
  
    # Läser från JSONfile
    json_object = json.load(openfile)

print("---------------------------------------------------------") 
print(f"{JSONFILE} + = {json_object}") # skriver ut JSONfilens namn och dess värden.
print("---------------------------------------------------------") 

time.sleep(1)    
print("\t~~ Farewell! ~~") 