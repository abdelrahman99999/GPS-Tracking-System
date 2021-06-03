from selenium import webdriver
import sys

driver = webdriver.Edge()
driver.get("https://www.google.com/maps/")

search_input_box = driver.find_element_by_name("q")
search_input_box.send_keys(sys.argv[1])
driver.find_element_by_id("searchbox-searchbutton").click()