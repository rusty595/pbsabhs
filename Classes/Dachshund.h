#pragma once
#include "Dog.h"
class Dachshund : public Dog
{
public:
	Dachshund(int lane):Dog(lane, "dachs"){};
	~Dachshund();
};

