#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork(int iPatterns, double * * fInput, double * * fTarget, vector<int> vectorLayers, double fSuccess, double fLearningRate, double fMomentum) : m_iPatterns(iPatterns), m_arrayInput(fInput), m_arrayTarget(fTarget), m_vectorLayers(vectorLayers), m_fSuccess(fSuccess), m_fLearningRate(fLearningRate), m_fMomentum(fMomentum) {
    for (int i = 1; i < m_vectorLayers.size(); i++) {
        NeuralLayer * pNeuralLayer = new NeuralLayer(m_vectorLayers.at(i), m_vectorLayers.at(i - 1), m_fLearningRate, m_fMomentum);
        m_vectorNeuralLayers.push_back(pNeuralLayer);
    }
    m_iInput = m_vectorLayers.front();
    m_iTarget = m_vectorLayers.back();
    m_pLastLayer = m_vectorNeuralLayers.back();
    m_fInputDelta = new double [m_vectorLayers.back()]; 
    for (int i = 0; i < m_vectorLayers.back(); i++) {
        m_fInputDelta[i] = 0;
    }

    m_iRandomizedIndex = new int[m_iPatterns];
    for (int p = 0; p < m_iPatterns; p++) {
        m_iRandomizedIndex[p] = p;
    }
}
void NeuralNetwork::RandomizePatterns() {
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, 9); // define the range
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
void NeuralNetwork::SetRandomizedInput(int p) {
    int i = m_iRandomizedIndex[p];
    m_vectorNeuralLayers.at(0)->SetInput(m_arrayInput[i]);
    m_fTarget = m_arrayTarget[i];
}
int NeuralNetwork::GetPatterns() {
    return m_iPatterns;
}
void NeuralNetwork::PrintInputs()
{
    for (int i = 0; i < m_vectorNeuralLayers.size(); i++) {
        cout << "Layer " << i << endl << flush;
        m_vectorNeuralLayers.at(i)->PrintInput();
        cout << endl << flush;
    }
    cout << endl << flush;
}
void NeuralNetwork::PrintOutputs()
{
    for (int i = 0; i < m_vectorNeuralLayers.size(); i++) {
        cout << "Layer " << i << endl << flush;
        m_vectorNeuralLayers.at(i)->PrintOutput();
        cout << endl << flush;
    }
    cout << endl << flush;
}
void NeuralNetwork::PrintWeights()
{
    for (int i = 0; i < m_vectorNeuralLayers.size(); i++) {
        cout << "Layer " << i << endl << flush;
        m_vectorNeuralLayers.at(i)->PrintWeights();
    }
}
void NeuralNetwork::PrintPatterns()
{
    for( int p = 0 ; p < m_iPatterns ; p++ ) {
        for( int i = 0 ; i < m_iInput ; i++ ) {
            cout << right << setw(NUMBER_WIDTH) << fixed << setprecision(PRECISION) << unsigned(m_arrayInput[p][i]);
        }
        cout << "\n";
        for( int i = 0 ; i < m_iTarget ; i++ ) {
                cout << right << setw(NUMBER_WIDTH) << fixed << setprecision(PRECISION) << unsigned(m_arrayTarget[p][i]);
        }

        m_vectorNeuralLayers.at(0)->SetInput(m_arrayInput[p]);
        m_fTarget = m_arrayTarget[p];

        cout << "\n";
        ForwardCalculate();
        m_pLastLayer->PrintOutput();
        cout << "\n\n";
    }
}
void NeuralNetwork::ForwardCalculate()
{
    for (int i = 0; i < m_vectorNeuralLayers.size(); i++) {
        m_vectorNeuralLayers.at(i)->ForwardCalculate();
        if (i < m_vectorNeuralLayers.size() - 1) {
            m_vectorNeuralLayers.at(i + 1)->SetInput(m_vectorNeuralLayers.at(i)->GetOutput());
        }
    }
}
void NeuralNetwork::CalculateError()
{
    NeuralLayer * pLastLayer = m_vectorNeuralLayers.at(m_vectorNeuralLayers.size() - 1);
    double * fOutput = pLastLayer->GetOutput();
    for( int i = 0 ; i < pLastLayer->GetHeight() ; i++ ) {
        m_fInputDelta[i] = (m_fTarget[i] - fOutput[i]) * fOutput[i] * (1.0 - fOutput[i]) ;   
        m_fError += 0.5 * (m_fTarget[i] - fOutput[i]) * (m_fTarget[i] - fOutput[i]) ;
    }
}
void NeuralNetwork::BackwardCalculate()
{
    m_vectorNeuralLayers.at(m_vectorNeuralLayers.size() - 1)->SetInputDelta(m_fInputDelta);
    for (int i = (int)m_vectorNeuralLayers.size() - 1; i >= 0; i--) {
        m_vectorNeuralLayers.at(i)->BackwardCalculate();
        if (i > 0)
        {
            m_vectorNeuralLayers.at(i - 1)->SetInputDelta(m_vectorNeuralLayers.at(i)->GetOutputDelta());
        }
    }
}

void NeuralNetwork::SetError(double fError) {
    m_fError = fError;        
}
double NeuralNetwork::GetError() {
    return m_fError;        
}
double NeuralNetwork::GetSuccess() {
    return m_fSuccess;        
}


