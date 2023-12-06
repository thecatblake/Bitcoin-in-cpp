import random
import sys
import time
import requests
import re

file_name = sys.argv[1]
f = open(file_name, mode="r")
f_out = open("out.txt", mode="w")

status_code = 200
line = f.readline()

while line:
    secret, address = line.replace("\n", "").split(" ")
    line = f.readline()
    url = f"https://explorer.btc.com/btc/search/{address}"
    req = requests.get(url)
    status_code = req.status_code

    if req.status_code != 200:
        continue

    matches = re.findall(" *[0-9] BTC", req.text)
    balances = [int(s.split(" ")[0]) for s in matches]

    if len(balances) != 0:
        print(secret, address, max(balances))

        if max(balances) > 0:
            f_out.write(f"{secret} {address}\n")

    time.sleep(random.random() + 1)
