#pragma once
using namespace std;

/**
* @brief
* Class that shows info about logged user
*/
class Log_class {

public:

/**
* @brief
* String which stores username
*/
	string userName;

/**
* @param userName username
* @brief
* Function which set stored username
*/
	void storeUserName(string userName);

/**
* @param cars car model
* @brief
* Function which save into txt file current user rented cars
*/
	void rents(string cars);

/**
* @param cars car model
* @brief
* Function which clears inside of current user rented cars txt file 
*/
	void clearRents(string cars);
};

/**
* @brief
* Function which stores primary car data 
*/
void carData();

/**
* @param carModelInput car model
* @param carStatusInput car status
* @brief
* Function which adds to a car data file cars
*/
void addCarToFile(string carModelInput, string carStatusInput);

/**
* @param car car model
* @brief
* Function which check if car is available in car data file
*/
bool ifCarIsAvailvable(string car);

/**
* @brief
* Function which let user make a decision whether user want to log in, sign in, or exit
*/
void lobby();

/**
* @brief
* Function which let user log in
*/
void logIn();

/**
* @brief
* Function which let user sign in
*/
void signIn();

/**
* @param loginInput username
* @brief
* Function which check if that username is already used
*/
bool checkUser(string loginInput);

/**
* @param loginInput username
* @param passwordInput user password
* @brief
* Function which save signing in user username and user password
*/
void saveLog(string loginInput, string passwordInput);

/**
* @param storedUser username
* @param storedPassword user password
* @brief
* Function which check if username and user password exist
*/
bool getLog(string storedUser, string storedPassword);

/**
* @brief
* Function which let user make a decision whether user want to rent a car, return a car, or exit
*/
void carLobby();

/**
* @brief
* Function which let user rent a car
*/
void rentCar();

/**
* @param carInput car model
* @brief
* Function which check if car exist in car data
*/
bool checkCar(string carInput);

/**
* @brief
* Function which clears car data file
*/
void cleanFile();

/**
* @brief
* Function which let user return rented car
*/
void returnCar();

/**
* @param pFile file
* @brief
* Function which check if file is empty
*/
bool isEmpty(ifstream& pFile);