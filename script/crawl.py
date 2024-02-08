import sys

from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.wait import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver import ChromeOptions
from datetime import datetime

options = ChromeOptions()
options.add_argument("--headless")
driver = webdriver.Chrome(options=options)
currency = sys.argv[1]
start = sys.argv[2]
next_link_type = {
    "incremental": -2,
    "random": -3
}
next_link_index = next_link_type[sys.argv[3]]
f = open("./out.txt", mode="a")

balance_index = {
    "bitcoin": -1,
    "ethereum": 0,
    "binance-smart-chain": 0,
    "arbitrum": 0,
    "polygon-matic": 0,
    "fantom": 0,
    "bitcoin-cash": -2,
    "bitcoin-gold": -1,
    "litecoin": -1,
    "dash": -1
}

unit_index = {
    "bitcoin": None,
    "ethereum": -1,
    "binance-smart-chain": -1,
    "arbitrum": -1,
    "polygon-matic": -1,
    "fantom": -1,
    "bitcoin-cash": -1,
    "bitcoin-gold": None,
    "litecoin": None,
    "dash": None
}

link = "https://privatekeyfinder.io/private-keys/" + currency + "/" + str(start)
i = 1
while True:
    try:
        driver.get(link)
        element = WebDriverWait(driver, 10).until(
            EC.presence_of_element_located((By.CSS_SELECTOR, "#total-balance > span:nth-child(1)"))
        )

        es = element.text.split(" ")
        try:
            total_balance = float(es[balance_index[currency]])
            unit = ""
            if unit_index[currency] is not None:
                unit = es[unit_index[currency]]

            if total_balance > 0:
                f.write(f"{link} {total_balance} {unit}\n")
                f.flush()
            
            print(link, total_balance, unit)
        except:
            continue
    except:
         pass
    finally:
        link = list(filter(lambda x: "/private-keys/" + currency in x,
                           [e.get_attribute("href") for e in driver.find_elements(By.TAG_NAME, "a")]))[next_link_index]