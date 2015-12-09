#pragma once
#include "Dog.h"
class Dachshund : public Dog
{
public:
	Dachshund(int lane, cocos2d::Layer*scene) :Dog(lane, "dachs", scene, Vec2(-32.0f, 32.0f)){};
	~Dachshund(){};
};

