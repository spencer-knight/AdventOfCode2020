from selenium import webdriver
import time
import notif

##### DEBUG STUFF #####
#import testServer
##### END DEBUG STUFF #####

from selenium.webdriver.chrome.options import Options

# Needs to be the path to your chrome driver, change this in your implementation. Has to be chrome bc that is what I used.
PATH = "./chromedriver.exe" 

# Makes the chrome page not pop up(I'm doing it this way so that I can run this on my server)
options = Options()
options.add_argument('--headless')
options.add_argument('--disable-gpu')  
driver = webdriver.Chrome(PATH, chrome_options=options)
def getTimeInfo():
    driver.get("https://adventofcode.com/2020")
    sCountdown = driver.find_element_by_id("calendar-countdown").text
    sHours = sCountdown[0:2]
    hours = int(sHours)
    sMinutes = sCountdown[3:5]
    minutes = int(sMinutes)
    sSeconds = sCountdown[6:8]
    seconds = int(sSeconds)

    return hours, minutes, seconds


##### DEBUG STUFF ######
#testServer.flaskThread.start()
#time.sleep(10) # let flask server start
#print("Beginning test\n")
##### END DEBUG STUFF #####

oldHour , oldMinute, oldSecond = getTimeInfo()
while(True):
    hour, minute, second = getTimeInfo()
    if oldHour == 1 and hour == 0:
        print("Less than 1 hour until next puzzle is released")
        notif.alertEmail("Less than 1 hour until next puzzle is released")
    if hour == 0 and oldMinute == 11 and minute == 10:
        print("Less than 10 minutes until next puzzle is released")
        notif.alertEmail("Less than 10 minutes until next puzzle is released")
    if hour == 0 and oldMinute == 1 and minute == 0:
        print("Less than 60 seconds until the next puzzle is released")
        notif.alertEmail("Less than 60 seconds until the next puzzle is released")
        
    oldHour = hour
    oldMinute = minute
    oldSecond = second
    print(str(hour) + ":" + str(minute) + ":" + str(second))

    ##### DEBUG STUFF #####
    #testServer.minutes -= 1
    ##### END DEBUG STUFF #####
    
    time.sleep(180)
    # Please be careful with automated requests; I'm not a massive company, and I can
    # only take so much traffic.  Please be considerate so that everyone gets to play.
    # - Eric Wastle
    #
    # Putting this here so that if someone uses this code they know not to make a crazy amount of requests.
    # At most one every 10 seconds is plenty.
    # Quote found in webpage source
