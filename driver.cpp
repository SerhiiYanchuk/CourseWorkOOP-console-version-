#include "driver.h"
#include "car.h"
#include "driverMap.h"
#include "map.h"
#include <iostream>

//-------------------������� �������-------------------- 
const std::string& Driver::getName()
{
	return m_name;
}
int Driver::getYearExp()
{
	return m_yearExp;

}
Car& Driver::getCar()
{
	return m_car;
}

bool Driver::isBusy()
{
	return m_isBusy;
}

void Driver::changeIsBusy() {
	m_isBusy = !m_isBusy;
}

double Driver::getBusyTime()
{
	return m_busyTime;
}

std::chrono::steady_clock::time_point& Driver::getStartTime()
{
	return m_startTime;
}

const std::string& Driver::getLocation()
{
	return m_location;
}

void Driver::setLocation(const std::string& location)
{
	m_location = location;
}

DriverMap* Driver::m_driverMap = NULL;

void Driver::setDriverMap(DriverMap* map)
{
	m_driverMap = map;
}

DriverMap* Driver::getDriverMap()
{
	return m_driverMap;
}

//---------------�������� �������� �� ������ ������� �����-------------
float Driver::findWay(const std::string& from, const std::string& destination)
{
	int n = m_driverMap->m_map.quantityStreet;
	const int INF{ 1000000000 };
	int s = m_driverMap->m_map.listOfStreets[from];
	std::vector<float> d(n, INF), p(n);
	d[s] = 0;
	std::vector<bool> u(n);
	for (int i = 0; i < n; ++i) {
		int v = -1;
		for (int j = 0; j < n; ++j)
			if (!u[j] && (v == -1 || d[j] < d[v]))
				v = j;
		if (m_driverMap->m_map.listOfStreets[destination] == v) break;
		if (d[v] == INF)
			break;
		u[v] = true;

		for (size_t j = 0; j < m_driverMap->m_trafficJams[v].size(); ++j) {
			int to = m_driverMap->m_trafficJams[v][j].first;
			float len = m_driverMap->m_trafficJams[v][j].second;
			if (d[v] + len < d[to]) {
				d[to] = d[v] + len;
				p[to] = v;
			}
		}
	}

	std::vector<int> path;
	for (int v = m_driverMap->m_map.listOfStreets[destination]; v != s; v = p[v])
		path.push_back(v);
	path.push_back(s);
	reverse(path.begin(), path.end());

	for (auto index = path.begin(); index != path.end(); ++index)
	{
		for (auto street = m_driverMap->m_map.listOfStreets.begin(); street != m_driverMap->m_map.listOfStreets.end(); ++street)
			if (street->second == (*index))
			{
				std::cout << street->first << " -> ";
				break;
			}
	}
	/*std::cout << std::endl;*/

	return d[m_driverMap->m_map.listOfStreets[destination]];
}

void Driver::setTimeAttributes(double time)
{
	m_busyTime = time;
	m_startTime = std::chrono::steady_clock::now();
}

//-------------------���������� ����������-------------------- 
std::ostream& operator<< (std::ostream& out, Driver& driver)
{
	out << "Name: " << driver.getName() << "\nYear experience: " << driver.getYearExp() << "\n" << driver.getCar();
	return out;
}

std::istream& operator>> (std::istream& in, Driver& driver)
{
	std::cout << "Name: ";
	in >> driver.m_name;
	std::cout << "Year experience: ";
	in >> driver.m_yearExp;
	in >> driver.getCar();
	return in;
}