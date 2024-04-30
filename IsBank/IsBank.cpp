#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <string>

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
    string name, surname, line;

    cout << "IsBank'a Hosgeldiniz. \n"
        "_____________________ \n"
        "1. Hesap Olustur \n"
        "2. Bakiye Sorgu \n"
        "3. Para Yatir \n"
        "4. Para Cek \n"
        "5. Para Gonder \n"
        "6. Hesabi Sil \n"
        "7. Cikis \n";

    cin >> startSelect;

    switch (startSelect) {
    case 1: {
        cout << "İsminizi girin: \n";
        cin >> name;
        cout << "Soyisminizi girin: \n";
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
            cout << "Hesap basariyla olusturuldu ve kaydedildi.\n";
        }
        else {
            cout << "Dosya acilmadi.\n";
        }
        break;
    }
    case 2: {
        cout << "İsminizi girin: \n";
        cin >> name;
        cout << "Soyisminizi girin: \n";
        cin >> surname;

        ifstream inputFile("accounts.txt");
        if (!inputFile.is_open()) {
            cout << "Dosya acilmadi!\n";
            break;
        }

        bool found = false;
        string currentName, currentSurname;
        while (getline(inputFile, line)) {
            if (line.find("Name: ") == 0) {
                currentName = line.substr(7);
            }
            else if (line.find("Surname: ") == 0) {
                currentSurname = line.substr(11);
            }
            else if (line.find("Balance: ") == 0 && currentName == name && currentSurname == surname) {
                cout << "Bakiyeniz: " << line.substr(9) << endl;
                found = true;
            }
        }
        inputFile.close();

        if (!found) {
            cout << "Hesap bulunamadi\n";
        }
        break;
    }
    case 3: {
        cout << "İsminizi girin: \n";
        cin >> name;
        cout << "Soyisminizi girin: \n";
        cin >> surname;

        ifstream inputFile("accounts.txt");
        if (!inputFile.is_open()) {
            cout << "Dosya acilmadi!\n";
            break;
        }

        // Bakiyeyi güncellemek için hesabı bulmalıyız
        bool found = false;
        stringstream newContent;
        string currentName, currentSurname;
        while (getline(inputFile, line)) {
            if (line.find("Name: ") == 0) {
                currentName = line.substr(7);
            }
            else if (line.find("Surname: ") == 0) {
                currentSurname = line.substr(11);
            }

            newContent << line << "\n";

            if (currentName == name && currentSurname == surname) {
                if (line.find("Balance: ") == 0) {
                    int currentBalance = stoi(line.substr(9));
                    int amount;
                    cout << "Yatirmak istediginiz miktari girin: \n";
                    cin >> amount;

                    currentBalance += amount;
                    newContent << "Balance: " << currentBalance << "\n";
                    found = true;
                }
            }
        }

        inputFile.close();

        if (found) {
            ofstream outputFile("accounts.txt");
            outputFile << newContent.str();
            outputFile.close();
            cout << "Bakiye basariyla guncellendi.\n";
        }
        else {
            cout << "Hesap bulunamadi.\n";
        }
        break;
    }
    default:
        cout << "Gecersiz secim.\n";
        break;
    }

    return 0;
}
