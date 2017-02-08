#include "NeuralNetwork.h"


NeuralNetwork::NeuralNetwork(int iPatterns, double * * dInput, double * * dTarget, vector<int> vectorLayers, double dSuccess, double dLearningRate, double dMomentum) : 
    m_iPatterns(iPatterns), 
    m_arrayInput(dInput), 
    m_arrayTarget(dTarget), 
    m_vectorLayers(vectorLayers), 
    m_dSuccess(dSuccess), 
    m_dLearningRate(dLearningRate), 
    m_dMomentum(dMomentum) {
    for (int i = 1; i < (int)m_vectorLayers.size(); i++) {
        FullyConnectedLayer * pFullyConnectedLayer = new FullyConnectedLayer(m_vectorLayers.at(i), m_vectorLayers.at(i - 1), m_dLearningRate, m_dMomentum);
        m_vectorInputOutputLayers.push_back(pFullyConnectedLayer);
    }
    m_iInput = m_vectorLayers.front();
    m_iOutput = m_vectorLayers.back();
    m_pLastLayer = m_vectorInputOutputLayers.back();


    m_iRandomizedIndex = new int[m_iPatterns];
    for (int p = 0; p < m_iPatterns; p++) {
        m_iRandomizedIndex[p] = p;
    }
}
void NeuralNetwork::RandomizePatterns() {
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, m_iPatterns - 1); // define the range
    for( int p = 0 ; p < m_iPatterns ; p++) {  
        int q = distr(eng);
        int r = m_iRandomizedIndex[p] ;
        m_iRandomizedIndex[p] = m_iRandomizedIndex[q] ;
        m_iRandomizedIndex[q] = r ;
    }
    /*
    for (int p = 0; p < m_iPatterns; p++) {
        cout << m_iRandomizedIndex[p];
    }
    cout << endl << flush;
    */
}

void NeuralNetwork::SetInputTarget(int i)
{
    ((FullyConnectedLayer *)m_vectorInputOutputLayers.at(0))->SetInput(m_arrayInput[i]);
    ((FullyConnectedLayer *)m_vectorInputOutputLayers.back())->SetTarget(m_arrayTarget[i]);
}

void NeuralNetwork::SetRandomizedInput(int p) {
    int i = m_iRandomizedIndex[p];
    SetInputTarget(i);
}

int NeuralNetwork::GetPatterns() {
    return m_iPatterns;
}

void NeuralNetwork::PrintInputs()
{
    for (int i = 0; i < (int)m_vectorInputOutputLayers.size(); i++) {
        cout << "Input At Layer " << i << endl << flush;
        m_vectorInputOutputLayers.at(i)->PrintInput();
        cout << endl << flush;
    }
    cout << endl << flush;
}
void NeuralNetwork::PrintOutputs()
{
    for (unsigned int i = 0; i < m_vectorInputOutputLayers.size(); i++) {
        cout << "Output At Layer " << i << endl << flush;
        m_vectorInputOutputLayers.at(i)->PrintOutput();
        cout << endl << flush;
    }
    cout << endl << flush;
}
void NeuralNetwork::PrintWeights()
{
    for (unsigned int i = 0; i < m_vectorInputOutputLayers.size(); i++) {
        cout << "Weights At Layer " << i << " " << m_vectorInputOutputLayers.at(i)->GetInputSize() << "x" << m_vectorInputOutputLayers.at(i)->GetOutputSize() << endl << flush;
        m_vectorInputOutputLayers.at(i)->PrintWeights();
    }
}
void NeuralNetwork::PrintPatterns()
{
    for( int p = 0 ; p < m_iPatterns ; p++ ) {
        for( int i = 0 ; i < m_iInput ; i++ ) {
            cout << right << setw(NUMBER_WIDTH) << fixed << setprecision(PRECISION) << m_arrayInput[p][i];
        }
        cout << "\n";
        for( int i = 0 ; i < m_iOutput ; i++ ) {
                cout << right << setw(NUMBER_WIDTH) << fixed << setprecision(PRECISION) << m_arrayTarget[p][i];
        }

        SetInputTarget(p);


        cout << "\n";
        ForwardCalculate();
        //ConvolutionalForwardCalculate();
        m_pLastLayer->PrintOutput();
        cout << "\n\n";
    }
}
void NeuralNetwork::ForwardCalculate()
{
    for (unsigned int i = 0; i < m_vectorInputOutputLayers.size(); i++) {
        m_vectorInputOutputLayers.at(i)->ForwardCalculate();
        if (i < m_vectorInputOutputLayers.size() - 1) {
            ((FullyConnectedLayer *)m_vectorInputOutputLayers.at(i + 1))->SetInput(((FullyConnectedLayer *)m_vectorInputOutputLayers.at(i))->GetOutput());
        }
    }
}


void NeuralNetwork::CalculateError()
{
    Layer * pLastLayer = m_vectorInputOutputLayers.at(m_vectorInputOutputLayers.size() - 1);
    pLastLayer->CalculateError();
    m_dError = pLastLayer->GetError();
    //cout << m_dError << endl << flush;
}
void NeuralNetwork::BackwardCalculate()
{
    for (int i = (int)m_vectorInputOutputLayers.size() - 1; i >= 0; i--) {
        m_vectorInputOutputLayers.at(i)->BackwardCalculate();
        if (i > 0)
        {
            ((FullyConnectedLayer *)m_vectorInputOutputLayers.at(i - 1))->SetOutputDelta(((FullyConnectedLayer *)m_vectorInputOutputLayers.at(i))->GetInputDelta());
        }
    }
}

void NeuralNetwork::SetError(double dError) {
    Layer * pLastLayer = m_vectorInputOutputLayers.at(m_vectorInputOutputLayers.size() - 1);
    pLastLayer->SetError(dError);   
}
double NeuralNetwork::GetError() {
    return m_dError;        
}
double NeuralNetwork::GetSuccess() {
    return m_dSuccess;        
}


