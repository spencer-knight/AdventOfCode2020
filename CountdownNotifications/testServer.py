from flask import Flask
import threading

app = Flask("testServer")
hours = 00
minutes = 15
seconds = 20

@app.route('/')
def index():
    if hours < 10:
        sHours = "0" + str(hours)
    else: 
        sHours =  str(hours)
    
    if minutes < 10:
        sMinutes = "0" + str(minutes)
    else: 
        sMinutes =  str(minutes)
    return """
    <!DOCTYPE html>
    <html>
    <body>
    <span id="calendar-countdown">""" + sHours + ":" + sMinutes + ":" + str(seconds) + """</span>
    </body>
    </html>
    """

def startApp():
    app.run(host="0.0.0.0")

flaskThread = threading.Thread(target = startApp)