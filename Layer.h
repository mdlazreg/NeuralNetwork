#ifndef _LAYER_H
#define _LAYER_H
#include <cstdint>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>
#include <math.h>
#include <list>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
#define NUMBER_WIDTH 8
#define PRECISION 2

class Layer {
    private:
        int m_iOutput;
        int m_iInput;
        double * * m_dWeights;
        double * * m_dChangeWeights;
        double * m_dInput;
        double * m_dTarget;
        double m_dError;
        double * m_dOutput;
        double * m_dInputDelta;
        double * m_dOutputDelta;
    protected:
        double m_dLearningRate;
        double m_dMomentum;
    public:
        Layer(double fLearningRate, double fMomentum);
        virtual void PrintInput() = 0;
        virtual void PrintWeights() = 0;
        virtual void PrintOutput() = 0;
        virtual void ForwardCalculate() = 0;
        virtual void CalculateError() = 0;
        virtual void BackwardCalculate() = 0;



        virtual int GetOutputSize() = 0;
        virtual int GetInputSize() = 0;
        virtual double GetError() = 0;
        virtual void SetError(double dError) = 0;
};
#endif
