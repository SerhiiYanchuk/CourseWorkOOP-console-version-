#include "taxiPark.h"
#include <fstream>

void TaxiPark::loadData() {
	std::ifstream fsCar("dataBase\\carsDependent.txt");
	std::ifstream fsDriver("dataBase\\driversDependent.txt");
	std::string name;
	int yearExp;
	std::string model;
	std::string regPlate;
	char symbol;
	bool isInsured;
	while (!fsCar.eof())
	{
		fsDriver >> name;
		fsDriver >> yearExp;
		fsCar >> model;
		fsCar >> regPlate;
		fsCar >> symbol;
		isInsured = (symbol == '+') ? true : false;
		driversDependent.push_back(DriverDependent(name, yearExp, Car(model, regPlate, isInsured)));
	}
	fsCar.close();
	fsDriver.close();
	fsCar.open("dataBase\\carsIndependent.txt");
	fsDriver.open("dataBase\\driversIndependent.txt");
	while (!fsCar.eof())
	{
		fsDriver >> name;
		fsDriver >> yearExp;
		fsCar >> model;
		fsCar >> regPlate;
		fsCar >> symbol;
		isInsured = (symbol == '+') ? true : false;
		driversIndependent.push_back(DriverIndependent(name, yearExp, Car(model, regPlate, isInsured)));
	}
}

void TaxiPark::receiveOrder(Client* client)
{
	m_client = client;
}

void TaxiPark::completeOrder()
{
	delete m_client;
}

DriverDependent TaxiPark::getDependent(int index)
{ 
	return driversDependent[index];
}
DriverIndependent TaxiPark::getIndependent(int index)
{
	return driversIndependent[index];
}

//Driver* TaxiPark::operator[] (const int index)
//{
//	return drivers[index];
//}