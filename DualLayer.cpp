#include "NeuralLayer.h"

NeuralLayer::NeuralLayer(int iHeight, int iWidth, double fLearningRate, double fMomentum) : m_iHeight(iHeight), m_iWidth(iWidth), m_fLearningRate(fLearningRate), m_fMomentum(fMomentum) {
    m_iWeights = new double *[m_iHeight]; 
    for (int i = 0; i < m_iHeight; i++) {
        m_iWeights[i] = new double[m_iWidth + 1];
        for (int j = 0; j < m_iWidth + 1; j++) {
            m_iWeights[i][j] = dis(rng) - 0.5;
        }
    }

    m_fChangeWeights = new double *[m_iHeight]; 
    for (int i = 0; i < m_iHeight; i++) {
        m_fChangeWeights[i] = new double[m_iWidth + 1];
        for (int j = 0; j < m_iWidth + 1; j++) {
            m_fChangeWeights[i][j] = dis(rng) - 0.5;
        }
    }

    m_iInput = new double [m_iWidth + 1]; 
    for (int j = 0; j < m_iWidth; j++) {
        m_iInput[j] = 0;
    }
    m_iInput[m_iWidth] = 1;

    m_iOutput = new double [m_iHeight]; 
    for (int i = 0; i < m_iHeight; i++) {
        m_iOutput[i] = 0;
    }

    m_fInputDelta = new double [m_iHeight]; 
    for (int i = 0; i < m_iHeight; i++) {
        m_fInputDelta[i] = 0;
    }

    m_fOutputDelta = new double [m_iWidth]; 
    for (int j = 0; j < m_iWidth; j++) {
        m_fOutputDelta[j] = 0;
    }
}
void NeuralLayer::PrintInput()
{
    for (int j = 0 ; j < m_iWidth + 1 ; j++ ) {
        cout << right << setw(NUMBER_WIDTH) << fixed << setprecision(PRECISION) << m_iInput[j];
    }
}
void NeuralLayer::PrintWeights() {
    for (int i = 0 ; i < m_iHeight ; i++ ) {
        for (int j = 0 ; j < m_iWidth + 1 ; j++ ) {  		
    	    cout << right << setw(NUMBER_WIDTH) << fixed << setprecision(PRECISION) << m_iWeights[i][j];
        }
        cout << flush << endl;
    }
}
void NeuralLayer::PrintOutput() {
    for (int i = 0 ; i < m_iHeight ; i++ ) {
        cout << right << setw(NUMBER_WIDTH) << fixed << setprecision(PRECISION) << m_iOutput[i];
    }
}
void NeuralLayer::ForwardCalculate()
{
    for (int i = 0 ; i < m_iHeight ; i++ ) {
        m_iOutput[i] = 0;
        for (int j = 0 ; j < m_iWidth + 1 ; j++ ) {  		
    	    m_iOutput[i] += m_iWeights[i][j] * m_iInput[j];
        }
        m_iOutput[i] = 1.0/(1.0 + exp(-m_iOutput[i])) ;
    }
}
void NeuralLayer::BackwardCalculate()
{
    for( int i = 0 ; i < m_iHeight ; i++ ) {
        for( int j = 0 ; j < m_iWidth + 1 ; j++ ) {
            m_fChangeWeights[i][j] = m_fLearningRate * m_fInputDelta[i] * m_iInput[j]  + m_fMomentum * m_fChangeWeights[i][j];
            m_iWeights[i][j] += m_fChangeWeights[i][j] ;
        }
    }

    for( int i = 0 ; i < m_iWidth ; i++ ) {
        m_fOutputDelta[i] = 0.0 ;
        for( int j = 0 ; j < m_iHeight ; j++ ) {
            m_fOutputDelta[i] += m_iWeights[j][i] * m_fInputDelta[j] ;
        }
        m_fOutputDelta[i] = m_fOutputDelta[i] * m_iInput[i] * (1.0 - m_iInput[i]) ;
    }
}
void NeuralLayer::SetInput(double * Input)
{
    for (int j = 0; j < m_iWidth; j++) {
        m_iInput[j] = Input[j];
    }
}
void NeuralLayer::SetInputDelta(double * InputDetla)
{
    for (int i = 0; i < m_iHeight; i++) {
        m_fInputDelta[i] = InputDetla[i];
    }
}
double * NeuralLayer::GetOutputDelta()
{
    return m_fOutputDelta;
}
double * NeuralLayer::GetOutput()
{
    return m_iOutput;
}
int NeuralLayer::GetHeight()
{
    return m_iHeight;
}

