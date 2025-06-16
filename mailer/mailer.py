import smtplib
import json
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart

def load_config():
    with open("config.json", "r") as f:
        return json.load(f)

def get_username_from_email(email):
    return email.split("@")[0]

def send_email(quote):
    config = load_config()
    sender = config["smtp"]["username"]
    recipient = config["recipient"]
    username = get_username_from_email(recipient)

    msg = MIMEMultipart()
    msg["From"] = sender
    msg["To"] = recipient
    msg["Subject"] = "Złota myśl na dziś"

    body = f"Cześć {username}!\n\nTwoja złota myśl na dziś:\n\n\"{quote}\""
    msg.attach(MIMEText(body, "plain"))

    with smtplib.SMTP(config["smtp"]["server"], config["smtp"]["port"]) as server:
        server.starttls()
        server.login(sender, config["smtp"]["password"])
        server.send_message(msg)

    print(f"Wysłano cytat do {recipient}")
