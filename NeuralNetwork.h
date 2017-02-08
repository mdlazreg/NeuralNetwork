#include <cstdint>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>
#include <math.h>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include "FullyConnectedLayer.h"

using namespace std;
#define NUMBER_WIDTH 8
#define PRECISION 2

class NeuralNetwork {
    private:
        int m_iPatterns;
        int m_iInput;
        int m_iOutput;
        int   * m_iRandomizedIndex;
        vector<int> m_vectorRandomizedIndex;
        vector<int> m_vectorLayers;
        vector<Layer *> m_vectorInputOutputLayers;
        Layer * m_pLastLayer;
        double m_dError;
        double m_dSuccess;
        double m_dLearningRate;
        double m_dMomentum;
        double * m_dOutputDelta;
        double * * m_arrayTarget;
        double * * m_arrayInput;
    public:
        NeuralNetwork(int iPatterns, double * * dInput, double * * dTarget, vector<int> vectorLayers, double dSuccess, double dLearningRate, double dMomentum);
        void RandomizePatterns();
        void SetInputTarget(int i);
        void SetRandomizedInput(int p);
        int GetPatterns();
        void PrintInputs();
        void PrintOutputs();
        void PrintWeights();
        void PrintPatterns();
        void ForwardCalculate();
        void ConvolutionalForwardCalculate();
        void CalculateError();
        void BackwardCalculate();
        void SetError(double fError);
        double GetError();
        double GetSuccess();
};

