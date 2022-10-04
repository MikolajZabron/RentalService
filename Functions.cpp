#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstring>
#include <map>
#include <string>
#include "Functions.h"
using namespace std;

Log_class LogObj;

void carData() {
    addCarToFile("Audi_A5", "true");
    addCarToFile("BMW_M2", "true");
    addCarToFile("BMW_Series-5", "true");
    addCarToFile("Lamborgini_Huracane", "true");
    addCarToFile("Mercedes_A-Class", "true");
    addCarToFile("Mercedes_C-Class", "true");
    addCarToFile("Peugeot_RCZ", "true");
    addCarToFile("Renault_Megane", "true");
    addCarToFile("Toyota_Avensis", "true");
    addCarToFile("Toyota_Supra", "true");
}

void addCarToFile(string carModelInput, string carStatusInput) {
    fstream file("CarData.txt", ios::in | ios::out | ios::app);
    if (!(ifCarIsAvailvable(carModelInput))) {
        file << carModelInput << endl;
        file << carStatusInput << endl;
    }
    file.close();
}

bool ifCarIsAvailvable(string car) {
    map<string, string> carModelAndStatus;
    ifstream file("CarData.txt");
    string carModel;
    string carStatus;
    while (getline(file, carModel) && getline(file, carStatus)) {
        carModelAndStatus.insert(pair<string, string>(carModel, carStatus));
    }
    file.close();
    auto give = carModelAndStatus.find(car);
    if (give != carModelAndStatus.cend()) {
        return true;
    }
    else {
        return false;
    }
}

void lobby() {
    int log_choice;
    cout << "CRS - Car Rental Service" << endl;
    cout << endl;
    cout << "Press [1] to log in to our service" << endl;
    cout << "Press [2] to sign in to our service" << endl;
    cout << "Press [3] to exit" << endl;
    cin >> log_choice;
    switch (log_choice)
    {
    case 1:
        system("cls");
        logIn();
        break;
    case 2:
        system("cls");
        signIn();
        break;
    case 3:
        system("cls");
        cout << "\nThank you" << endl;
        break;
    default:
        system("cls");
        cout << "Please select one of the options \n" << endl;
        lobby();
    }
}

void logIn() {
    cout << "\t\tLog In\n";
    cout << "To log in enter your username: ";
    string userName;
    cin >> userName;
    cout << "To log in enter your password: ";
    string userPassword;
    cin >> userPassword;
    if (getLog(userName, userPassword)) {
        system("cls");
        cout << "Succesfull Logging in!" << endl;
        LogObj.storeUserName(userName);
        carLobby();
    }
    else {
        cout << "Incorrect Name or Password, try again" << endl;
        logIn();
    }
}

void Log_class::storeUserName(string userName) {
    this->userName = userName;
}

void signIn() {
    cout << "\t\tSign In\n";
    cout << "To sign in enter your username: ";
    string userName;
    cin >> userName;
    cout << "To sign in enter your password: ";
    string userPassword;
    cin >> userPassword;
    if (!(checkUser(userName))) {
        saveLog(userName, userPassword);
        system("cls");
        cout << "Successful Registeration!\n\n";
        lobby();
    }
    else {
        cout << "Username is already taken, try again" << endl;
        signIn();
    }
}

bool checkUser(string loginInput) {
    map<string, string> userNameAndPassword;
    ifstream MyFile("LogData.txt");
    string userName;
    string userPassword;
    while (getline(MyFile, userName) && getline(MyFile, userPassword)) {
        userNameAndPassword.insert(pair<string, string>(userName, userPassword));
    }
    MyFile.close();
    auto give = userNameAndPassword.find(loginInput);
    if (give != userNameAndPassword.cend()) {
        return true;
    }
    else {
        return false;
    }
}

void saveLog(string loginInput, string passwordInput) {
    fstream MyFile("LogData.txt", ios::in | ios::out | ios::app);
    MyFile << loginInput << endl;
    MyFile << passwordInput << endl;
    MyFile.close();
}

bool getLog(string loginInput, string passwordInput) {
    map<string, string> userNameAndPassword;
    ifstream MyFile("LogData.txt");
    string userName;
    string userPassword;
    while (getline(MyFile, userName) && getline(MyFile, userPassword)) {
        userNameAndPassword.insert(pair<string, string>(userName, userPassword));
    }
    MyFile.close();
    auto give = userNameAndPassword.find(loginInput);
    if (give != userNameAndPassword.cend()) {
        if (give->second == passwordInput) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

void carLobby() {
    int rent_choice;
    cout << "\nCRS - Car Rental Service" << endl;
    cout << " " << endl;
    cout << "Press [1] to rent the car" << endl;
    cout << "Press [2] to return the car" << endl;
    cout << "Press [3] to exit" << endl;
    cin >> rent_choice;
    switch (rent_choice)
    {
    case 1:
        system("cls");
        rentCar();
        break;
    case 2:
        system("cls");
        returnCar();
        break;
    case 3:
        system("cls");
        cout << "\n\tThank you" << endl;
        break;
    default:
        system("cls");
        cout << "Please select one of the options \n" << endl;
        carLobby();
    }
}

void rentCar() {
    cout << "\tCars to rent:" << endl;
    ifstream file("CarData.txt");
    map<string, string> carModelAndStatus;
    string carModel;
    string carStatus;
    while (getline(file, carModel) && getline(file, carStatus)) {
        carModelAndStatus.insert(pair<string, string>(carModel, carStatus));
    }
    file.close();
    int i = 1;
    for (auto const& p : carModelAndStatus) {
        if (p.second == "true") {
            cout << "[" << i << "] rent" << " " << p.first << " (" << p.second << ")" << endl;
        }
        i++;
    }
    cout << "Type car model you want to rent!" << endl;
    string car;
    cin >> car;
    if (car != "Back") {
        auto give = carModelAndStatus.find(car);
        if (give != carModelAndStatus.cend()) {
            give->second = "false";
            LogObj.rents(car);
            system("cls");
            cout << " Thanks for renting " << car << endl;
        }
        else {
            system("cls");
            cout << "Wrong name, we don't have a car named " << car << endl;
        }
    }
    else {
        system("cls");
        cout << "\tBack" << endl;
    }
    cleanFile();
    std::fstream fileWrite("CarData.txt", std::ios::in | std::ios::out | std::ios::app);
    for (const auto& p : carModelAndStatus) {
        fileWrite << p.first << std::endl;
        fileWrite << p.second << std::endl;
    }
    fileWrite.close();
    carLobby();
}

bool checkCar(string carInput) {
    map<string, string> carModelAndStatus;
    ifstream file("CarData.txt");
    string carModel;
    string carStatus;
    while (getline(file, carModel) && getline(file, carStatus)) {
        carModelAndStatus.insert(pair<string, string>(carModel, carStatus));
    }
    file.close();
    auto give = carModelAndStatus.find(carInput);
    if (give == carModelAndStatus.cend()) {
        return true;
    }
    else {
        return false;
    }
}

void cleanFile() {
    ofstream file("CarData.txt");
    file.close();
}

void Log_class::rents(string cars) {
    fstream file(this->userName + "_RentData.txt", std::ios::in | std::ios::out | std::ios::app);
    file << cars << std::endl;
    file << "false" << std::endl;
    file.close();
}

void Log_class::clearRents(string cars) {
    ofstream file(this->userName + "_RentData.txt");
    file.close();
}

void returnCar() {
    ifstream file("CarData.txt");
    map<string, string> carModelAndStatus;
    string carModel;
    string carStatus;
    while (getline(file, carModel) && getline(file, carStatus)) {
        carModelAndStatus.insert(pair<string, string>(carModel, carStatus));
    }
    file.close();
    ifstream rentfile(LogObj.userName + "_RentData.txt");
    map<string, string> carRentsAndStatus;
    string RentModel;
    string RentStatus;
    if (isEmpty(rentfile)) {
        cout << "\tYou have no rented cars" << endl;
    }
    else {
        cout << "\tCars to return:" << endl;
        while (getline(rentfile, RentModel) && getline(rentfile, RentStatus)) {
            carRentsAndStatus.insert(pair<string, string>(RentModel, RentStatus));
        }
        int i = 1;
        for (auto const& p : carRentsAndStatus) {
            if (p.second == "false") {
                cout << "[" << i << "] return" << " " << p.first << " (" << p.second << ")" << endl;
            }
            i++;
        }
        cout << "[" << i << "]" << " " << "Type 'Back' to go back" << endl;
        string car;
        cin >> car;
        if (car != "Back") {
            auto give = carRentsAndStatus.find(car);
            if (give != carRentsAndStatus.cend()) {
                for (const auto& p : carRentsAndStatus) {
                    if (p.second == "false") {
                        give->second = "true";
                        LogObj.clearRents(car);
                        fstream fileRent(LogObj.userName + "_RentData.txt", std::ios::in | std::ios::out | std::ios::app);
                        fileRent << p.first << endl;
                        fileRent << p.second << endl;
                        system("cls");
                        cout << "Thanks for returning " << car << endl;
                    }
                }
            } 
            else {
                system("cls");
                cout << "Wrong name, we don't have a car named " << car << endl;
            }
        }
        else {
            system("cls");
            cout << "\tBack" << endl;
        }
        auto have = carModelAndStatus.find(car);
        if (have != carModelAndStatus.cend()) {
            have->second = "true";
        }
        cleanFile();
        std::fstream fileWrite("CarData.txt", std::ios::in | std::ios::out | std::ios::app);
        for (const auto& p : carModelAndStatus) {
            fileWrite << p.first << endl;
            fileWrite << p.second << endl;
        }
        fileWrite.close();
    }
    rentfile.close();
    carLobby();
}

bool isEmpty(ifstream& pFile) {
    return pFile.peek() == ifstream::traits_type::eof();
}