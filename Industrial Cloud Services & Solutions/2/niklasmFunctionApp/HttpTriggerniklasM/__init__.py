import logging
import uuid
import json
import random

import azure.functions as func # Gör ett alias för biblioteket

speed = random.randrange(100,200) # Randomiserar en hastighet mellan 100 & 200 genom random & randrange och postar det i min table under "Speed"

"""
Mainfunktion för att kunna skicka det jag vill skicka till tablestorage. Som dessutom returnerar ett svar om det lyckades! När den triggas.

Genom metoden set bestämmer jag värdet på min output data. I detta fall är det en jsondump med MIN "data" - variabel.

"""


def main(req: func.HttpRequest, message: func.Out[str]) -> func.HttpResponse:

    rowKey = str(uuid.uuid4())

    data = {
        "Speed": speed,
        "Name": "SPEEDING",
        "PartitionKey": "message",
        "RowKey": rowKey
    }

    message.set(json.dumps(data))

    return func.HttpResponse(f"SUCESS! Data sent to tablestorage created with the rowKey: {rowKey}")