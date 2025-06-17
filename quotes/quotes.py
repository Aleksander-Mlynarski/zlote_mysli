import random
import os

USED_QUOTES_FILE = "quotes/used_quotes.txt"

def load_quotes():
    with open("quotes/quotes.txt", encoding="utf-8") as f:
        return [line.strip() for line in f if line.strip()]

def load_used_indexes():
    if not os.path.exists(USED_QUOTES_FILE):
        return set()
    with open(USED_QUOTES_FILE, "r") as f:
        return set(map(int, f.readlines()))

def save_used_index(index):
    with open(USED_QUOTES_FILE, "a") as f:
        f.write(f"{index}\n")

def get_random_quote():
    quotes = load_quotes()
    used = load_used_indexes()
    available = [i for i in range(len(quotes)) if i not in used]

    if not available:
        # Reset jeśli wszystkie zostały użyte
        open(USED_QUOTES_FILE, "w").close()
        available = list(range(len(quotes)))

    chosen = random.choice(available)
    save_used_index(chosen)
    return quotes[chosen]
