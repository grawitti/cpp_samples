#pragma once

class FlyBehavior {
	public:
	virtual void fly() = 0;
};

class FlyWithWings : public FlyBehavior {
	virtual void fly();
};

class FlyNoWay : public FlyBehavior {
	virtual void fly();
};

class FlyRocketPowered : public FlyBehavior {
	virtual void fly();
};

