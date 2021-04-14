#pragma once

class QuackBehavior {
public:
	virtual void quack() = 0;
};

class Quack : public QuackBehavior {
	virtual void quack();
};

class MuteQuack : public QuackBehavior {
	virtual void quack();
};

class Squeak : public QuackBehavior {
	virtual void quack();
};
