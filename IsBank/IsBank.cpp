#include <iostream>
#include <Windows.h>
#include <fstream>
#include <sstream>
#include <random>

using namespace std;

string generateRandomNumber(int length) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 9);
    stringstream ss;
    for (int i = 0; i < length; i++) {
        ss << dis(gen);
    }
    return ss.str();
}

int main() {
    cout << "_______    ____              _     \n"
        "|_   _|   |  _ \\            | |    \n"
        "  | |  ___| |_) | __ _ _ __ | | __ \n"
        "  | | / __|  _ < / _` | '_ \\| |/ / \n"
        " _| |_\\__ \\ |_) | (_| | | | |   <  \n"
        "|_____|___/____/ \\__,_|_| |_|_|\\_\\ \n";

    int startSelect;
    string name, surname;

    cout << "IsBank'a Hosgeldiniz. \n"
        "_____________________ \n"
        "1. Hesap Oluştur \n"
        "2. Bakiye Sorgu \n"
        "3. Para Yatır \n"
        "4. Para Çek \n"
        "5. Para Gönder \n"
        "6. Hesabı Sil \n"
        "7. Çıkış \n";

    cin >> startSelect;

    switch (startSelect) {
    case 1: {
        cout << "İsminizi girin: \n";
        cin >> name;
        cout << "Soyisminizi girin: \n ";
        cin >> surname;

        string accountNumber = generateRandomNumber(12);
        string creditCardNumber = generateRandomNumber(16);
        string iban = "TR" + generateRandomNumber(24);
        int balance = 0;

        ofstream accountFile("accounts.txt", ios::app);
        if (accountFile.is_open()) {
            accountFile << "Name: " << name << "\n";
            accountFile << "Surname: " << surname << "\n";
            accountFile << "Account Number: " << accountNumber << "\n";
            accountFile << "Credit Card Number: " << creditCardNumber << "\n";
            accountFile << "IBAN: " << iban << "\n";
            accountFile << "Balance: " << balance << "\n";
            accountFile << "---------------------------\n";
            accountFile.close();
            cout << "Hesap başarıyla oluşturuldu ve kaydedildi.\n";
        }
        else {
            cout << "Dosya açılmadı \n";
        }
        break;
    }
    case 2: {
        cout << "İsminizi girin: \n";
        cin >> name;
        cout << "Soyisminizi girin: \n";
        cin >> surname;

        ifstream inputFile("accounts.txt");
        bool found = false;

        if (inputFile.is_open()) {
            string currentName, currentSurname;
            while (getline(inputFile, line)) {
                if (line.find("Name: ") == 0) {
                    currentName = line.substr(6);
                }
                else if (line.find("Surname: ") == 0) {
                    currentSurname = line.substr(10);
                }
                else if (line.find("Balance: ") == 0 && currentName == name && currentSurname == surname) {
                    string balanceStr = line.substr(9);
                    cout << "Bakiyeniz: " << balanceStr << endl;
                    found = true;
                    break;
                }
            }
            inputFile.close();

            if (!found) {
                cout << "Hesap bulunamadı" << endl;
            }
        }
        else {
            cout << "Dosya acilamadi" << endl;
        }
        break;
    }
    default:
        cout << "Gecersiz secim.\n";
        break;
    }


    return 0;
}
