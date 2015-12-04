#pragma once
#include "Dog.h"
class Dachshund : public Dog
{
public:
	Dachshund(int lane, cocos2d::Layer*scene) :Dog(lane, "dachs", scene){};
	~Dachshund();
};

