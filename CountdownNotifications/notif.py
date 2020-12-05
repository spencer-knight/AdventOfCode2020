import smtplib, ssl
import getpass

# You *could* make this plaintext, but for security reasons I'd just enter it manually each time.
password = getpass.getpass(prompt = "Please enter your password: ")

def alertEmail( message):
    global password
    port = 465  
    smtp_server = "smtp.gmail.com"

    # Replace this with your email 
    sender_email = "sender@gmail.com" 
    # Replace this with where you want to get notifacations
    receiver_email = "receiver@gmail.com",

    context = ssl.create_default_context()
    with smtplib.SMTP_SSL(smtp_server, port, context=context) as server:
        server.login(sender_email, password)
        server.sendmail(sender_email, receiver_email, message)