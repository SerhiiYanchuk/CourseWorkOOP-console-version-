#pragma once
#include <string>
#include "driver.h"

class DriverDependent : public Driver {
private:
	float m_salary{ 10 };
	static constexpr float m_percentageOfOrder = 0.25f;
public:
	DriverDependent(std::string name = "undefined", int yearExp = 0, const Car& car = Car("undefined", "undefined", false))
		: Driver{ name, yearExp, car }
	{
	}
	void setSalary(float);
	float getSalary();
	static float getPercentageOfOrder();
	virtual void calculatePrice(double) override final;
	virtual ~DriverDependent() {}
	friend std::istream& operator>> (std::istream& in, DriverDependent&);
};

std::ostream& operator<< (std::ostream&, DriverDependent&);

float operator+(float money, DriverDependent& driver);
float operator+(DriverDependent& driver, float money);
float operator+=(float money, DriverDependent& driver);