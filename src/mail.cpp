#include <curl/curl.h>
#include <string>
#include <iostream>

bool sendMail(const std::string& from,
              const std::string& to,
              const std::string& subject,
              const std::string& body,
              const std::string& smtpServer,
              const std::string& username,
              const std::string& password)
{
    // Inicjalizuje bibliotekę libcurl
    CURL *curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Błąd inicjalizacji CURL" << std::endl;
        return false;
    }

    // Lista odbiorców (do kogo wysyłamy maila)
    struct curl_slist *recipients = nullptr;

    // Kompletna zawartość wiadomości e-mail w formacie SMTP
    std::string data =
        "To: " + to + "\r\n" +
        "From: " + from + "\r\n" +
        "Subject: " + subject + "\r\n" +
        "\r\n" + // Oddzielenie nagłówków od treści
        body + "\r\n";

    // Ustawienie adresu serwera SMTP (np. smtp://smtp.gmail.com:587)
    curl_easy_setopt(curl, CURLOPT_URL, smtpServer.c_str());

    // Ustawienie nadawcy e-maila
    curl_easy_setopt(curl, CURLOPT_MAIL_FROM, ("<" + from + ">").c_str());

    // Dodanie odbiorcy do listy
    recipients = curl_slist_append(recipients, ("<" + to + ">").c_str());
    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

    // Ustawienie danych do logowania SMTP
    curl_easy_setopt(curl, CURLOPT_USERNAME, username.c_str());
    curl_easy_setopt(curl, CURLOPT_PASSWORD, password.c_str());

    // Wymuszenie użycia SSL/TLS
    curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);

    // Informuje curl, że będziemy wysyłać dane (upload e-maila)
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

    // Ustawienie funkcji odczytu danych z pamięci (treści e-maila)
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, [](char* buffer, size_t size, size_t nitems, void* userdata) -> size_t {
        std::string* payload = static_cast<std::string*>(userdata);
        size_t buffer_size = size * nitems;
        size_t copy_size = std::min(payload->size(), buffer_size);
        memcpy(buffer, payload->c_str(), copy_size);
        payload->erase(0, copy_size);
        return copy_size;
    });

    // Przekazujemy wskaźnik do naszej treści e-maila
    curl_easy_setopt(curl, CURLOPT_READDATA, &data);

    // Wykonanie wysyłki e-maila
    CURLcode res = curl_easy_perform(curl);

    // Sprawdzamy, czy się udało
    bool success = (res == CURLE_OK);

    // Jeśli nie, wypisz błąd
    if (!success) {
        std::cerr << "Błąd wysyłania e-maila: " << curl_easy_strerror(res) << std::endl;
    }

    // Zwolnienie pamięci po liście odbiorców i zwolnienie CURLa
    curl_slist_free_all(recipients);
    curl_easy_cleanup(curl);

    return success;
}
