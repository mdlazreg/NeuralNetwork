#include "ConvolutionLayer.h"

static std::default_random_engine rng;
static std::uniform_real_distribution<> dis(0, 1);

ConvInputOutputLayer::ConvInputOutputLayer(int iInput, int iFilter, int iPadding, int iStride, int iPatches, double dLearningRate, double dMomentum) : 
    m_iInput(iInput), 
    m_iFilter(iFilter), 
    m_iPadding(iPadding), 
    m_iStride(iStride), 
    m_iPatches(iPatches), 
    Layer(dLearningRate,dMomentum) {

    m_dInput = new double * [m_iInput]; 
    m_dInputDelta = new double * [m_iInput]; 
    for (int i = 0; i < m_iInput; i++) {
        m_dInput[i] = new double[m_iInput]; 
        m_dInputDelta[i] = new double[m_iInput]; 
        for (int j = 0; j < m_iInput; j++) {
            m_dInput[i][j] = 0;
            m_dInputDelta[i][j] = 0;
        }
    }

    m_dWeights = new double **[m_iPatches];
    m_dChangeWeights = new double **[m_iPatches]; 
    m_dBiases = new double [m_iPatches];
    m_dChangeBiases = new double [m_iPatches];
    for (int f = 0; f < m_iPatches; f++) {
        m_dBiases[f] = dis(rng) - 0.5;
        m_dChangeBiases[f] = dis(rng) - 0.5;
        m_dWeights[f] = new double * [m_iFilter];
        m_dChangeWeights[f] = new double * [m_iFilter];
        for (int i = 0; i < m_iFilter; i++) {
            m_dWeights[f][i] = new double [m_iFilter];
            m_dChangeWeights[f][i] = new double [m_iFilter];
            for (int j = 0; j < m_iFilter; j++) {     
                m_dWeights[f][i][j] = dis(rng) - 0.5;
                m_dChangeWeights[f][i][j] = 0;
            }
        }
    }

    m_iOutput = (iInput - iFilter + 2*iPadding)/iStride + 1;
    m_dOutput = new double * * [m_iPatches]; 
    m_dTarget = new double * * [m_iPatches]; 
    m_dOutputDelta = new double * * [m_iPatches]; 
    for (int f = 0; f < m_iPatches; f++) {
        m_dOutput[f] = new double * [m_iOutput]; 
        m_dTarget[f] = new double * [m_iOutput]; 
        m_dOutputDelta[f] = new double * [m_iOutput]; 
        for (int i = 0; i < m_iOutput; i++) {
            m_dOutput[f][i] = new double[m_iOutput]; 
            m_dTarget[f][i] = new double[m_iOutput]; 
            m_dOutputDelta[f][i] = new double[m_iOutput]; 
            for (int j = 0; j < m_iOutput; j++) {
                m_dOutput[f][i][j] = 0;
                m_dTarget[f][i][j] = 0;
                m_dOutputDelta[f][i][j] = 0;
            }
        }
    }
}
void ConvInputOutputLayer::PrintInput()
{
    cout << "Convolution Layer Input:" << endl << flush;
    for (int i = 0; i < m_iInput; i++) {
        for (int j = 0; j < m_iInput; j++) {
            cout << right << setw(NUMBER_WIDTH) << fixed << setprecision(PRECISION) << m_dInput[i][j];
        }
        cout << endl << flush;
    }
    cout << endl << flush;
}
void ConvInputOutputLayer::PrintWeights() {
    cout << "Convolution Layer Weights:" << endl << flush;
    for (int f = 0; f < m_iPatches; f++) {
        for (int i = 0; i < m_iFilter; i++) {
            for (int j = 0; j < m_iFilter; j++) {     
                cout << right << setw(NUMBER_WIDTH) << fixed << setprecision(PRECISION) << m_dWeights[f][i][j];
            }
            cout << endl << flush;
        }
        cout << right << setw(NUMBER_WIDTH) << fixed << setprecision(PRECISION) << m_dBiases[f] << endl << flush;
        cout << endl << flush;
    }
    cout << endl << flush;
}
void ConvInputOutputLayer::PrintOutput() {
    cout << "Convolution Layer Output:" << endl << flush;
    for (int f = 0; f < m_iPatches; f++) {
        for (int i = 0; i < m_iOutput; i++) {
            for (int j = 0; j < m_iOutput; j++) {
                cout << right << setw(NUMBER_WIDTH) << fixed << setprecision(PRECISION) << m_dOutput[f][i][j];
            }
            cout << endl << flush;
        }
        cout << endl << flush;
    }
    cout << endl << flush;
}

void ConvInputOutputLayer::ForwardCalculate()
{
    for (int f = 0; f < m_iPatches; f++) {
        for (int i = 0; i < m_iOutput; i++) {
            for (int j = 0; j < m_iOutput; j++) {
                for (int fi = 0; fi < m_iFilter; fi++) {
                    for (int fj = 0; fj < m_iFilter; fj++) {
                        m_dOutput[f][i][j] += m_dWeights[f][fi][fj] * m_dInput[i + fi][j + fj];
                    }
                }
                m_dOutput[f][i][j] += m_dBiases[f];
                m_dOutput[f][i][j] = 1.0/(1.0 + exp(-m_dOutput[f][i][j])) ;
            }
        }
    }
}


void ConvInputOutputLayer::CalculateError()
{
    for( int f = 0 ; f < m_iPatches ; f++ ) {
        for( int i = 0 ; i < m_iOutput ; i++ ) {
            for( int j = 0 ; j < m_iOutput ; j++ ) {
                m_dOutputDelta[f][i][j] = (m_dTarget[f][i][j] - m_dOutput[f][i][j]) * m_dOutput[f][i][j] * (1.0 - m_dOutput[f][i][j]) ;  
                m_dError += 0.5 * (m_dTarget[f][i][j] - m_dOutput[f][i][j]) * (m_dTarget[f][i][j] - m_dOutput[f][i][j]) ;
            }
        }
    }
}

void ConvInputOutputLayer::SetError(double dError) {
    m_dError = dError;        
}

double ConvInputOutputLayer::GetError() {
    return m_dError;        
}

void ConvInputOutputLayer::BackwardCalculate()
{
    for (int f = 0; f < m_iPatches; f++) {
        for (int i = 0; i < m_iOutput; i++) {
            for (int j = 0; j < m_iOutput; j++) {
                for(int fi = 0; fi < m_iFilter; fi++) {
                    for (int fj = 0; fj < m_iFilter; fj++) {
                        m_dChangeWeights[f][fi][fj] = m_dLearningRate * m_dOutputDelta[f][i][j] * m_dInput[i + fi][j + fi]  + m_dMomentum * m_dChangeWeights[f][fi][fj];
                        m_dWeights[f][fi][fj] += m_dChangeWeights[f][fi][fj];
                    }
                }
                m_dChangeBiases[f] = m_dLearningRate * m_dOutputDelta[f][i][j] * m_dBiases[f]  + m_dMomentum * m_dChangeBiases[f];
                m_dBiases[f] += m_dChangeBiases[f];
            }
           
        }
    }

    for( int i = 0 ; i < m_iInput ; i++ ) {
        for( int j = 0 ; j < m_iInput ; j++ ) {
            m_dInputDelta[i][j] = 0.0 ;
            for (int f = 0; f < m_iPatches; f++) {
                for (int io = 0; io < m_iOutput; io++) {
                    for (int jo = 0; jo < m_iOutput; jo++) {
                        for(int fi = 0; fi < m_iFilter; fi++) {
                            for (int fj = 0; fj < m_iFilter; fj++) {
                                m_dInputDelta[i][j] += m_dWeights[f][fi][fj] * m_dOutputDelta[f][io][jo] ;
                            }
                        }
                        m_dInputDelta[i][j] += m_dBiases[f] * m_dOutputDelta[f][io][jo] ;
                    }
                }
            }
            m_dInputDelta[i][j] = m_dInputDelta[i][j] * m_dInput[i][j] * (1.0 - m_dInput[i][j]);
        }
    }
}

void ConvInputOutputLayer::SetInput(double * * Input)
{
    for (int i = 0; i < m_iInput; i++) {
        for (int j = 0; j < m_iInput; j++) {
            m_dInput[i][j] = Input[i][j];
        }
    }
}

void ConvInputOutputLayer::SetTarget(double * * * Target)
{
    for( int f = 0 ; f < m_iPatches ; f++ ) {
        for( int i = 0 ; i < m_iOutput ; i++ ) {
            for( int j = 0 ; j < m_iOutput ; j++ ) {
                m_dTarget[f][i][j] = Target[f][i][j];
            }
        }
    }
}

void ConvInputOutputLayer::SetOutputDelta(double * * * OutputDetla)
{
    for (int f = 0; f < m_iPatches; f++) {
        for (int i = 0; i < m_iOutput; i++) {
            for (int j = 0; j < m_iOutput; j++) {
                m_dOutputDelta[f][i][j] = OutputDetla[f][i][j];
            }
        }
    }
}
double * * ConvInputOutputLayer::GetInputDelta()
{
    return m_dInputDelta;
}
double * * * ConvInputOutputLayer::GetOutput()
{
    return m_dOutput;
}
int ConvInputOutputLayer::GetOutputSize()
{
    return m_iOutput;
}
int ConvInputOutputLayer::GetInputSize()
{
    return m_iInput;
}

