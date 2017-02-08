#include "FullyConnectedLayer.h"

static std::default_random_engine rng;
static std::uniform_real_distribution<> dis(0, 1);

FullyConnectedLayer::FullyConnectedLayer(int iInput, int iPatches, int iOutput, double dLearningRate, double dMomentum):
    m_iOutput(iOutput), 
    m_iPoolingInput(iInput),
    m_iPatches(iPatches),
    Layer(dLearningRate, dMomentum) {
    m_iInput = m_iPoolingInput*m_iPoolingInput*m_iPatches;
    Initialize();
}
FullyConnectedLayer::FullyConnectedLayer(int iOutput, int iInput, double fLearningRate, double fMomentum) : 
    m_iOutput(iOutput), 
    m_iInput(iInput),
    Layer(fLearningRate, fMomentum) {
    Initialize();
}

void FullyConnectedLayer::Initialize() {
    m_dInput = new double [m_iInput]; 
    m_dInputDelta = new double [m_iInput]; 
    for (int j = 0; j < m_iInput; j++) {
        m_dInput[j] = 0;
        m_dInputDelta[j] = 0;
    }

    m_dWeights = new double *[m_iOutput]; 
    m_dChangeWeights = new double *[m_iOutput]; 
    m_dBiases = new double [m_iOutput];
    m_dChangeBiases = new double [m_iOutput];
    m_dOutput = new double [m_iOutput];
    m_dTarget = new double [m_iOutput]; 
    m_dOutputDelta = new double [m_iOutput]; 

    for (int i = 0; i < m_iOutput; i++) {
        m_dWeights[i] = new double[m_iInput];
        m_dChangeWeights[i] = new double[m_iInput];
        for (int j = 0; j < m_iInput; j++) {
            m_dWeights[i][j] = dis(rng) - 0.5;
            m_dChangeWeights[i][j] = 0;
        }
        m_dBiases[i] = dis(rng) - 0.5;
        m_dChangeBiases[i] = 0;
        m_dOutput[i] = 0;
        m_dTarget[i] = 0;
        m_dOutputDelta[i] = 0;
    }
}
void FullyConnectedLayer::PrintInput()
{
    for (int j = 0 ; j < m_iInput ; j++ ) {
        cout << right << setw(NUMBER_WIDTH) << fixed << setprecision(PRECISION) << m_dInput[j];
    }
}
void FullyConnectedLayer::PrintWeights() {
    for (int i = 0 ; i < m_iOutput ; i++ ) {
        for (int j = 0 ; j < m_iInput ; j++ ) {
    	    cout << right << setw(NUMBER_WIDTH) << fixed << setprecision(PRECISION) << m_dWeights[i][j];
        }
        cout << right << setw(NUMBER_WIDTH) << fixed << setprecision(PRECISION) << m_dBiases[i];
        cout << endl << flush;
    }
    cout << flush << endl;
}
void FullyConnectedLayer::PrintOutput() {
    cout << "FullyConnected Layer Output:" << m_iOutput << endl << flush;
    for (int i = 0 ; i < m_iOutput ; i++ ) {
        cout << right << setw(NUMBER_WIDTH) << fixed << setprecision(PRECISION) << m_dOutput[i];
    }
    cout << endl << flush;
}

void FullyConnectedLayer::ForwardCalculate()
{
    for (int i = 0 ; i < m_iOutput ; i++ ) {
        m_dOutput[i] = 0;       
        for (int j = 0 ; j < m_iInput ; j++ ) {  
    	    m_dOutput[i] += m_dWeights[i][j] * m_dInput[j];
        }
        //m_dOutput[i] += m_dWeights[i][m_iInput] * m_dInput[m_iInput];//bias
        m_dOutput[i] += m_dBiases[i];
        m_dOutput[i] = 1.0/(1.0 + exp(-m_dOutput[i])) ;
        
    }
}
void FullyConnectedLayer::BackwardCalculate()
{
    for( int i = 0 ; i < m_iOutput ; i++ ) {
        for( int j = 0 ; j < m_iInput; j++ ) {
            m_dChangeWeights[i][j] = m_dLearningRate * m_dOutputDelta[i] * m_dInput[j]  + m_dMomentum * m_dChangeWeights[i][j];
            m_dWeights[i][j] += m_dChangeWeights[i][j] ;
        }
        m_dChangeBiases[i] = m_dLearningRate * m_dOutputDelta[i] + m_dMomentum * m_dChangeBiases[i];
        m_dBiases[i] += m_dChangeBiases[i];
    }

    for( int i = 0 ; i < m_iInput ; i++ ) {
        m_dInputDelta[i] = 0.0 ;
        for( int j = 0 ; j < m_iOutput ; j++ ) {
            m_dInputDelta[i] += m_dWeights[j][i] * m_dOutputDelta[j] ;
        }
        m_dInputDelta[i] = m_dInputDelta[i] * m_dInput[i] * (1.0 - m_dInput[i]) ;
        
    }
}
void FullyConnectedLayer::SetInput(double * Input)
{
    for (int i = 0; i < m_iInput; i++) {
        m_dInput[i] = Input[i];
    }
}

void FullyConnectedLayer::SetInput(double *** Input)
{
    for (int f = 0; f < m_iPatches; f++) {
        for (int i = 0; i < m_iPoolingInput; i++) {
            for (int j = 0; j < m_iPoolingInput; j++) {
                m_dInput[f*m_iPoolingInput*m_iPoolingInput + i*m_iPoolingInput + j] = Input[f][i][j];
            }
        }
    }
}


void FullyConnectedLayer::SetTarget(double * Target)
{
    for (int j = 0; j < m_iOutput; j++) {
        m_dTarget[j] = Target[j];
    }
}


void FullyConnectedLayer::CalculateError()
{
    for( int i = 0 ; i < m_iOutput ; i++ ) {
        
        m_dOutputDelta[i] = (m_dTarget[i] - m_dOutput[i]) * m_dOutput[i] * (1.0 - m_dOutput[i]) ;  
        m_dError += 0.5 * (m_dTarget[i] - m_dOutput[i]) * (m_dTarget[i] - m_dOutput[i]) ;
        //cout << m_dError << endl << flush;
        //cout << m_dTarget[i] << " " << m_dOutput[i] << endl << flush;
        //cout << m_iOutput << " D " << m_dError << endl << flush;
    }
    
}

void FullyConnectedLayer::SetError(double dError) {
    m_dError = dError;        
}

double FullyConnectedLayer::GetError() {
    return m_dError;        
}

void FullyConnectedLayer::SetOutputDelta(double * OutputDetla)
{
    for (int i = 0; i < m_iOutput; i++) {
        m_dOutputDelta[i] = OutputDetla[i];
    }
}
double * FullyConnectedLayer::GetInputDelta()
{
    return m_dInputDelta;
}
double * FullyConnectedLayer::GetOutput()
{
    return m_dOutput;
}
int FullyConnectedLayer::GetOutputSize()
{
    return m_iOutput;
}
int FullyConnectedLayer::GetInputSize()
{
    return m_iInput;
}

