// com_port.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <windows.h>
#include <time.h>
#include <vector>
#include <fstream>
#include <windows.h>
using namespace std;
HANDLE hSerial;
string name;
#pragma warning(disable : 4996)
void ReadCOM()
{
    DWORD iSize;
    char sReceivedChar;
    vector<char> symbol_mass;
    ofstream txt_file;
    int size_m = 0;
    while (true)
    {
        
        ReadFile(hSerial, &sReceivedChar, 1, &iSize, 0);  // получаем 1 байт
        if (iSize > 0)   // если что-то принято, выводим
        {
            symbol_mass.push_back(sReceivedChar);         
            cout << sReceivedChar;
        }
        if (sReceivedChar=='\n')
        {
            txt_file.open("log_data/"+name, ios_base::app);
            struct tm* u;
            time_t timer = time(NULL);
            u = localtime(&timer);
            time_t next = mktime(u);
            for (size_t i = 0; i < symbol_mass.size() && symbol_mass[i]!='\n'; i++)
            {
               cout << symbol_mass[i];
               txt_file<< symbol_mass[i];
            }
            size_m = symbol_mass.size();
            //cout << "__________" << endl;
            for (size_t i = 0; i < size_m; i++)
            {
                symbol_mass.pop_back();
            }
           cout<<endl;
           txt_file << "[";
           cout << u->tm_mday << "." << u->tm_mon << "." << u->tm_year-100 << " " << u->tm_hour<< ":" << u->tm_min << "." << u->tm_sec<<'\n'<<'\n';
           txt_file << u->tm_mday << "." << u->tm_mon+1 << "." << u->tm_year-100 << " " << u->tm_hour<< ":" << u->tm_min << ":" << u->tm_sec;
           txt_file << "]\n";
           txt_file.close();
            
        }
    }
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    CreateDirectory(L"log_data", NULL);
    LPCTSTR sPortName = L"";
    int port;
    cout << "Выберите порт [1-7] ";
    cin >> port;
    switch (port)
    {
    case 1:
        sPortName = L"COM1";
    case 2:
        sPortName = L"COM2";
    case 3:
        sPortName = L"COM3";
    case 4:
        sPortName = L"COM4";
    case 5:
        sPortName = L"COM5";
    case 6:
        sPortName = L"COM6";
    case 7:
        sPortName = L"COM7";
    default:
        break;
    }
    cout << "Введите имя файла с .txt на конце "<<endl;
    cin >> name;
    hSerial = ::CreateFile(sPortName, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if (hSerial == INVALID_HANDLE_VALUE)
    {
        if (GetLastError() == ERROR_FILE_NOT_FOUND)
        {
            cout << "Порт не найден"<<endl;
        }
    }
    DCB dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams))
    {
        cout << "Порт не отвечает..."<<endl;
    }
    dcbSerialParams.BaudRate = 230400;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    if (!SetCommState(hSerial, &dcbSerialParams))
    {
        cout << "error setting serial port state\n";
    }
   
    while (1)
    {
        
        ReadCOM();
    }
}