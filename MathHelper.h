#pragma once

#include <random>

class MathHelper
{
private:
	MathHelper();
	~MathHelper();
public:
	static float random(float r, float l);
	static float interpolateCubic(float min, float max, float x);
	static float inverseInterpolateCubic(float min, float max, float x);
private:
	static std::random_device* m_RandomDevice;
	static std::mt19937* m_RandomGenerator;
};

