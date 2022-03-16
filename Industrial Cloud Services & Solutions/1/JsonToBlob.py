"""
Niklas Månzén IOTGBG - Examinationsuppgifter - Uppgift1
JsonToBlob.py
Detta program laddar upp en specifik JSON upp till min blobstorage/container och tar sedan bort den lokala JSONfilen. 
"""

import os, uuid, sys
import time
from azure.storage.blob import BlockBlobService, PublicAccess # VID IMPORTFEL!! använd - pip install azure-storage-blob==0.37.1   - VID IMPORTFEL!!

def execute():
    try: #Vi testar detta block. Blir det Error fångar vi det i exception som printar ut ERROR genom E-variabeln
        block_blob_service = BlockBlobService(account_name='niklasmstorage', account_key='tk7zfYPoM3yDIcEDuJEfzoSSG1Dgs+Yt+E6IPmA1KTmCDb5S9TeUK7liRmK2DAt/jZRGG/by931c6AQVL1Rgnw==')
        # Tilldelar account_name & account_key från de jag skapat och hittat via Azureportalen.
        container_name ='niklasmblob' # mitt namn på min blob som jag skapat sedan innan genom Azureportalen.

        block_blob_service.set_container_acl(container_name, public_access=PublicAccess.Container) # Dubbelkollar så den är publikt tillgänglig. Sätter den pub.

        local_path=os.path.abspath(os.path.curdir) # Den lokala "vägen" där programmet utföres.
        local_file_name = "tempfukt.json" # Mina värden finnes i denna fil
        full_path_to_file =os.path.join(local_path, local_file_name) # Hämtar den lokala vägen där min sparade Jsonfil finnes.
        
        print("\t~~ Welcome! ~~") # Artigheter
        time.sleep(1)
        print(f"It's time to upload the Jsonfile : {local_file_name} to {container_name}...\n")
        time.sleep(1)
        
        input("Press Enter To Execute!\n")
        print("-------------------------------------------------")

        print("Json File = " + full_path_to_file)
        time.sleep(1)
        print("\nUploading to Blob storage as blob : " + local_file_name)
        time.sleep(1)

        # Laddar upp bloben från mina filsökvägar
        block_blob_service.create_blob_from_path(container_name, local_file_name, full_path_to_file)

        print("-------------------------------------------------")
        
        print("\n-- List blobs in the container --") # Listar alla blobs i containern.
        time.sleep(1)
        generator = block_blob_service.list_blobs(container_name)
        for blob in generator: 
            print("\t Blob Name : " + blob.name)
        
        print("-------------------------------------------------")
        
        time.sleep(1)

        sys.stdout.write("Finished! When you hit Enter, the application will Exit and Delete the Json File.")
        sys.stdout.flush()
        input()
        
        os.remove(full_path_to_file) # Tar bort JSON fil. Den laddas ned i nästa program så ingen fara.
        
        print("\t~~ Farewell! ~~")

    except Exception as e:
        print(e)

# Mainmetoden.
if __name__ == '__main__':
    execute()