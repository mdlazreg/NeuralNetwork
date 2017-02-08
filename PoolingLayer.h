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
class PoolingLayer {
    private:
        int m_iInput;
        int m_iFilter;
        int m_iOutput;
        int m_iPatches;
        double m_dError;
        int * * * m_iWeights;
        double * * * m_dInput;
        double * * * m_dTarget;
        double * * * m_dOutput;
        double * * * m_dOutputDelta;
        double * * * m_dInputDelta;
    public:
        PoolingLayer(int iInput, int iFilter, int iPatches);
        void PrintInput();
        void PrintWeights();
        void PrintOutput();
        void ForwardCalculate();
        void CalculateError();
        void BackwardCalculate();
        void SetInput(double * * * Input);
        void SetTarget(double * * * Target);
        void SetOutputDelta(double * * * OutputDetla);
        void SetOutputDelta(double * OutputDetla);
        double GetError() ;
        void SetError(double dError);
        double * * * GetInputDelta();
        double * * * GetOutput();
        int GetOutputSize();
        int GetInputSize();
};
