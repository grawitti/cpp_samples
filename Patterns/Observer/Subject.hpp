#pragma once

#include "Observer.hpp"

class Subject {
	public:
		virtual void registerObserver(Observer o) = 0;
		virtual void removeObserver(Observer o) = 0;
		virtual void notifyObservers() = 0;
};
