#include "Layer.h"

static std::default_random_engine rng;
static std::uniform_real_distribution<> dis(0, 1);

Layer::Layer(double dLearningRate, double dMomentum) : m_dLearningRate(dLearningRate), m_dMomentum(dMomentum) {
}



