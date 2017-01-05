#include <cstdint>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>
#include <math.h>
#include <list>
#include <stdio.h>
#include <stdlib.h>
static std::default_random_engine rng;
static std::uniform_real_distribution<> dis(0, 1);

using namespace std;
#define NUMBER_WIDTH 8
#define PRECISION 2
class NeuralLayer {
    private:
        int m_iHeight;
        int m_iWidth;
        double m_fLearningRate;
        double m_fMomentum;
        double * * m_iWeights;
        double * * m_fChangeWeights;
        double * m_iInput;
        double * m_iOutput;
        double * m_fInputDelta;
        double * m_fOutputDelta;
    public:
        NeuralLayer(int iHeight, int iWidth, double fLearningRate, double fMomentum);
        void NeuralLayer::PrintInput();
        void NeuralLayer::PrintWeights();
        void NeuralLayer::PrintOutput();
        void NeuralLayer::ForwardCalculate();
        void NeuralLayer::BackwardCalculate();
        void NeuralLayer::SetInput(double * Input);
        void NeuralLayer::SetInputDelta(double * InputDetla);
        double * NeuralLayer::GetOutputDelta();
        double * NeuralLayer::GetOutput();
        int NeuralLayer::GetHeight();
};
