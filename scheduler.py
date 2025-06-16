import schedule
import time
from datetime import datetime
from mailer.mailer import send_email
from quotes.quotes import get_random_quote
from mailer.mailer import load_config

def job():
    quote = get_random_quote()
    send_email(quote)

def start_scheduler():
    config = load_config()
    send_time = config["send_time"]
    schedule.every().day.at(send_time).do(job)
    print(f"Zaplanowano wysyłanie codziennie o {send_time}")
    while True:
        schedule.run_pending()
        time.sleep(1)
