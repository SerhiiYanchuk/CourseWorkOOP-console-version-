#pragma once
#include <string>

class DriverDependent;
class DriverIndependent;

class Car {
private:
	std::string m_model;
	std::string m_regPlate;
	bool m_isVip;
public:
	Car(std::string model = "undefined", std::string regPlate = "undefined", bool isVip = false)
		: m_model{ model }, m_regPlate{ regPlate }, m_isVip{ isVip }
	{
	}
	Car(const Car &cpyCar)
		: m_model{ cpyCar.m_model }, m_regPlate{ cpyCar.m_regPlate }, m_isVip{ cpyCar.m_isVip }
	{
	}
	
	void setAttributesCar(std::string model, std::string regPlate, bool isInsured);
	const std::string& getModel();
	const std::string& getRegPlate();
	bool isVip();
	~Car() {}
	friend std::istream& operator>> (std::istream&, Car&);
};

std::ostream& operator<< (std::ostream&, Car&);