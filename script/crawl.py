from selenium import webdriver
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.common.by import By
from selenium.webdriver.support.wait import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver import FirefoxOptions, ChromeOptions

options = FirefoxOptions()
options.add_argument("--headless")
driver = webdriver.Firefox(options=options)
link = "https://privatekeyfinder.io/private-keys/bitcoin/"
f = open("out.txt", mode="w")

while True:
    try:
        driver.get(link)
        element = WebDriverWait(driver, 10).until(
            EC.presence_of_element_located((By.CSS_SELECTOR, "#total-balance > span:nth-child(1)"))
        )

        total_balance = int(element.text.split(" ")[-1])
        print(link, total_balance)

        if total_balance > 0:
            f.write(link)

        link = list(filter(lambda x: "/private-keys/bitcoin/" in x,
                           [e.get_attribute("href") for e in driver.find_elements(By.TAG_NAME, "a")]))[-3]

    except:
        driver.quit()
        break
