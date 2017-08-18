#include "MathHelper.h"

std::random_device* MathHelper::m_RandomDevice = NULL;
std::mt19937* MathHelper::m_RandomGenerator = NULL;

MathHelper::MathHelper()
{
}


MathHelper::~MathHelper()
{
}

float MathHelper::random(float r, float l)
{
	if (!m_RandomDevice) {
		m_RandomDevice = new std::random_device();
		m_RandomGenerator = new std::mt19937((*m_RandomDevice)());
	}

	std::uniform_real_distribution<double> distr(r, l);

	return distr(*m_RandomGenerator);
}

float MathHelper::interpolateCubic(float min, float max, float x)
{
	return (max - min)*x*x + min;
}

float MathHelper::inverseInterpolateCubic(float min, float max, float x)
{
	return max + (min - max)*(x - 1)*(x - 1);
}
