#include <cstdint>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>
#include <math.h>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include "NeuralLayer.h"

using namespace std;
#define NUMBER_WIDTH 8
#define PRECISION 2

class NeuralNetwork {
    private:
        int m_iPatterns;
        int m_iInput;
        int m_iTarget;
        int   * m_iRandomizedIndex;
        vector<int> m_vectorRandomizedIndex;
        vector<int> m_vectorLayers;
        vector<NeuralLayer *> m_vectorNeuralLayers;
        NeuralLayer * m_pLastLayer;
        double m_fError;
        double m_fSuccess;
        double m_fLearningRate;
        double m_fMomentum;
        double * m_fTarget;
        double * m_fInputDelta;
        double * * m_arrayTarget;
        double * * m_arrayInput;
    public:
        NeuralNetwork(int iPatterns, double * * fInput, double * * fTarget, vector<int> vectorLayers, double fSuccess, double fLearningRate, double fMomentum);
        void NeuralNetwork::RandomizePatterns();
        void NeuralNetwork::SetRandomizedInput(int p);
        int NeuralNetwork::GetPatterns();
        void NeuralNetwork::PrintInputs();
        void NeuralNetwork::PrintOutputs();
        void NeuralNetwork::PrintWeights();
        void NeuralNetwork::PrintPatterns();
        void NeuralNetwork::ForwardCalculate();
        void NeuralNetwork::CalculateError();
        void NeuralNetwork::BackwardCalculate();
        void NeuralNetwork::SetError(double fError);
        double NeuralNetwork::GetError();
        double NeuralNetwork::GetSuccess();
};

