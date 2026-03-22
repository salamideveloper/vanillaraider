#include <iostream>
#include <string>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <thread>
#include <chrono>
#include <winhttp.h>
#include <csignal>
#include <cstdlib>

#pragma comment(lib, "winhttp.lib")

std::string g_webhookUrl;
std::string g_customMessage;

void EnableANSI()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hOut, &mode);
    SetConsoleMode(hOut, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}

void PrintWhiteToBlueGradient(const std::string& text)
{
    if (text.size() < 5)
    {
        std::cerr << "no.\n";
        return;
    }
    int len = static_cast<int>(text.size());
    for (int i = 0; i < len; i++)
    {
        float t = static_cast<float>(i) / (len - 1);
        int r = static_cast<int>(255 * (1.0f - t));
        int g = static_cast<int>(255 * (1.0f - t));
        int b = 255;
        std::cout << "\x1b[38;2;" << r << ";" << g << ";" << b << "m" << text[i];
    }
    std::cout << "\x1b[0m\n";
}

void SendCustomMessage() // i copy pasted this from the C++ manual DO NOT FUCKING ROAST ME I WAS NOT GONNA WRITE THIS BEAST INSIDE THIS FUNCTION MYSELF
{
    std::string url = g_webhookUrl;
    std::wstring wurl(url.begin(), url.end());
    URL_COMPONENTS parts{};
    parts.dwStructSize = sizeof(parts);
    wchar_t host[256], path[1024];
    parts.lpszHostName = host;
    parts.dwHostNameLength = 256;
    parts.lpszUrlPath = path;
    parts.dwUrlPathLength = 1024;
    WinHttpCrackUrl(wurl.c_str(), 0, 0, &parts);
    std::string escaped;
    for (char c : g_customMessage) {
        if (c == '"') escaped += "\\\"";
        else if (c == '\\') escaped += "\\\\";
        else if (c == '\n') escaped += "\\n";
        else escaped += c;
    }
    std::string jsonStr = "{\"content\":\"" + escaped + "\"}";
    const char* json = jsonStr.c_str();
    HINTERNET s = WinHttpOpen(L"agent", 0, 0, 0, 0);
    HINTERNET c = WinHttpConnect(s, parts.lpszHostName, parts.nPort, 0);
    HINTERNET r = WinHttpOpenRequest(c, L"POST", parts.lpszUrlPath, 0, 0, 0, WINHTTP_FLAG_SECURE);
    WinHttpSendRequest(r, L"Content-Type: application/json\r\n", -1,
        (LPVOID)json, strlen(json), strlen(json), 0);
    WinHttpReceiveResponse(r, 0);
    WinHttpCloseHandle(r);
    WinHttpCloseHandle(c);
    WinHttpCloseHandle(s);
}

void OnExit()
{
    SendCustomMessage();
}

void OnSignal(int)
{
    SendCustomMessage();
    exit(0);
}

BOOL WINAPI ConsoleHandler(DWORD type)
{
    if (type == CTRL_CLOSE_EVENT) {
        SendCustomMessage();
        Sleep(500);
    }
    return FALSE;
}

int main()
{
    EnableANSI();
    system("title VanillaRaider made by salami");
    PrintWhiteToBlueGradient("VanillaRaider");

    std::cout << "Webhook url >> ";
    std::cin >> g_webhookUrl;
    std::cin.ignore();
    std::cout << "Custom message (sent whenever the fuck you close) >> ";
    std::getline(std::cin, g_customMessage);

    atexit(OnExit);
    signal(SIGINT, OnSignal);
    signal(SIGTERM, OnSignal);
    SetConsoleCtrlHandler(ConsoleHandler, TRUE); // 

    const char* json = "{\"content\":\"\\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n \\u3164\\n\"}";

    while (true) {
        std::wstring wurl(g_webhookUrl.begin(), g_webhookUrl.end());
        URL_COMPONENTS parts{};
        parts.dwStructSize = sizeof(parts);
        wchar_t host[256], path[1024];
        parts.lpszHostName = host;
        parts.dwHostNameLength = 256;
        parts.lpszUrlPath = path;
        parts.dwUrlPathLength = 1024;
        WinHttpCrackUrl(wurl.c_str(), 0, 0, &parts);

        HINTERNET s = WinHttpOpen(L"agent", 0, 0, 0, 0);
        HINTERNET c = WinHttpConnect(s, parts.lpszHostName, parts.nPort, 0);
        HINTERNET r = WinHttpOpenRequest(c, L"POST", parts.lpszUrlPath, 0, 0, 0, WINHTTP_FLAG_SECURE);
        WinHttpSendRequest(r, L"Content-Type: application/json\r\n", -1,
            (LPVOID)json, strlen(json), strlen(json), 0);
        WinHttpReceiveResponse(r, 0);
        WinHttpCloseHandle(r);
        WinHttpCloseHandle(c);
        WinHttpCloseHandle(s);

        PrintWhiteToBlueGradient("| | [*] - <WEBHOOK MSG SENT MUHAHA> - [*] | |");
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}
