#ifndef LIBRARY_H
#define LIBRARY_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <string>

using namespace std;

//Random sayı fonksiyonu
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


//Hesap oluşturma fonksiyonu
void createAccount(string name, string surname, string line) {

        cout << "Isminizi girin: \n";
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

}


//Bakiye sorgu fonksiyonu
void bakiyeSorgu(string name, string surname, string line) {
    cout << "Isminizi girin: \n";
    cin >> name;
    cout << "Soyisminizi girin: \n";
    cin >> surname;

    ifstream inputFile("accounts.txt");
    if (!inputFile.is_open()) {
        cout << "Dosya acilmadi!\n";
    }

    bool found = false;
    string currentName, currentSurname;
    while (getline(inputFile, line)) {
        if (line.find("Name: ") == 0) {
            currentName = line.substr(6);
        }
        else if (line.find("Surname: ") == 0) {
            currentSurname = line.substr(9);
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
}


//Para yatırma fonksiyonu
void paraYatir(string name, string surname, string line) {
        cout << "Isminizi girin: \n";
        cin >> name;
        cout << "Soyisminizi girin: \n";
        cin >> surname;

        ifstream inputFile("accounts.txt");
        if (!inputFile.is_open()) {
            cout << "Dosya acilmadi!\n";
        }

   
        bool found = false;
        stringstream newContent;
        string currentName, currentSurname;
        while (getline(inputFile, line)) {
            if (line.find("Name: ") == 0) {
                currentName = line.substr(6);
            }
            else if (line.find("Surname: ") == 0) {
                currentSurname = line.substr(9);
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
}


//Para çekme fonksiyonu
void paraCek(string name, string surname, string line) {
    cout << "Isminizi girin: \n";
        cin >> name;
        cout << "Soyisminizi girin: \n";
        cin >> surname;

        ifstream inputFile("accounts.txt");
        if (!inputFile.is_open()) {
            cout << "Dosya acilmadi!\n";
        }


        bool found = false;
        stringstream newContent;
        string currentName, currentSurname;
        while (getline(inputFile, line)) {
            if (line.find("Name: ") == 0) {
                currentName = line.substr(6);
            }
            else if (line.find("Surname: ") == 0) {
                currentSurname = line.substr(9);
            }

            newContent << line << "\n";

            if (currentName == name && currentSurname == surname) {
                if (line.find("Balance: ") == 0) {
                    int currentBalance = stoi(line.substr(9));
                    int amount;
                    cout << "Cekmek istediginiz Miktari Girin: \n";
                    cin >> amount;

                    if(currentBalance < amount) {
                        cout << "Islem basarisiz." << "\n";
                    } else {
                        currentBalance -= amount;
                        newContent << "Balance: " << currentBalance << "\n";
                        found = true;
                    }
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
}

#endif
