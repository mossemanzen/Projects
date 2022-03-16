"""
Niklas Månzén - Examinationsuppgifter - Uppgift 2
readTableStorage.py

Detta program läser alla värdena från min valda tablestorage ut till terminalen.
"""

from azure.data.tables import TableClient
import time

my_filter = "PartitionKey eq 'message'" # Sätter min partionkey till min "message".

table_client = TableClient.from_connection_string(conn_str="DefaultEndpointsProtocol=https;AccountName=niklasmstorage;AccountKey=tk7zfYPoM3yDIcEDuJEfzoSSG1Dgs+Yt+E6IPmA1KTmCDb5S9TeUK7liRmK2DAt/jZRGG/by931c6AQVL1Rgnw==;EndpointSuffix=core.windows.net", table_name="messages")

# Sätter MIN primary connectionstring från niklasmstorage som argument för metoden samt table_name till MIN "tablename"
# Tilldelar sedan table_client - Metoden från TableClient så jag kan hantera MIN table storage. Tack vare mina nycklar blir detta möjligt.

entities = table_client.query_entities(my_filter) # Entities blir tilldelad, från grund och botten, metoden query_entities från TableClient. För att kunna lista mina entiteter.

print("\t\t~~ Welcome! ~~") # Artigheter.
print("----------------------------------------------------------")
time.sleep(1)
print("We shall now print out all of the SPEEDING DATA\nfrom Table Storage (niklasmstorage)")
print("----------------------------------------------------------")
time.sleep(1)
input ("\t--- Press Enter To Continue ---")
print("----------------------------------------------------------")

for entity in entities: # Skriver ut respektive värde från respektive key från min datastorage genom en for-loop från entities.
    for key in entity.keys():
        print("KEY: {} | VALUE: {}".format(key, entity[key]))
        time.sleep(0.5)
    print("----------------------------------------------------------")
    time.sleep(1)
        
print("\t\t~~ Goodbye! ~~")