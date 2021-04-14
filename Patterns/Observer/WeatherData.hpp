#pragma once

#include <list>

#include "Subject.hpp"
#include "Observer.hpp"

class WeatherData : public Subject {
public:
	WeatherData() {}

	virtual void registerObserver(Observer o);
	virtual void removeObserver(Observer o);
	virtual void notifyObserver(Observer o);

private:
	std::List<Observer> observers;
	double tempereture;
	double humidity;
	double pressure;
};
