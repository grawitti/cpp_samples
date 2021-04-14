#pragma once

class Observer {
	public:
		virtual void update(double temp, double numidity, double pressure) = 0;
};
