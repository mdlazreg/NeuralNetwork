#include "PoolingLayer.h"

static std::default_random_engine rng;
static std::uniform_real_distribution<> dis(0, 1);

PoolingLayer::PoolingLayer(int iInput, int iFilter, int iPatches) : 
    m_iInput(iInput), 
    m_iFilter(iFilter), 
    m_iPatches(iPatches) {
    
    m_iOutput = iInput/iFilter;
    if  (iInput%iFilter) {
        m_iOutput += 1;
    }

    m_dInput = new double * * [m_iPatches]; 
    for (int f = 0; f < m_iPatches; f++) {
        m_dInput[f] = new double * [m_iInput]; 
        for (int i = 0; i < m_iInput; i++) {
            m_dInput[f][i] = new double[m_iInput]; 
            for (int j = 0; j < m_iInput; j++) {
                m_dInput[f][i][j] = 0;
            }
        }
    }

    m_dOutput = new double * * [m_iPatches]; 
    for (int f = 0; f < m_iPatches; f++) {
        m_dOutput[f] = new double * [m_iOutput]; 
        for (int i = 0; i < m_iOutput; i++) {
            m_dOutput[f][i] = new double[m_iOutput]; 
            for (int j = 0; j < m_iOutput; j++) {
                m_dOutput[f][i][j] = 0;
            }
        }
    }

    m_dTarget = new double * * [m_iPatches]; 
    for (int f = 0; f < m_iPatches; f++) {
        m_dTarget[f] = new double * [m_iOutput]; 
        for (int i = 0; i < m_iOutput; i++) {
            m_dTarget[f][i] = new double[m_iOutput]; 
            for (int j = 0; j < m_iOutput; j++) {
                m_dTarget[f][i][j] = 0;
            }
        }
    }

    m_iWeights = new int **[m_iPatches];
    for (int f = 0; f < m_iPatches; f++) {
        m_iWeights[f] = new int * [m_iInput]; 
        for (int i = 0; i < m_iInput; i++) {
            m_iWeights[f][i] = new int [m_iInput]; 
            for (int j = 0; j < m_iInput; j++) {
                m_iWeights[f][i][j] = 0;
            }
        }
    }

    m_dInputDelta = new double * * [m_iPatches]; 
    for (int f = 0; f < m_iPatches; f++) {
        m_dInputDelta[f] = new double * [m_iOutput]; 
        for (int i = 0; i < m_iOutput; i++) {
            m_dInputDelta[f][i] = new double[m_iOutput]; 
            for (int j = 0; j < m_iOutput; j++) {
                m_dInputDelta[f][i][j] = 0;
                //cout << m_dInputDelta[f][i][j] << endl << flush;
            }
        }
    }

    m_dOutputDelta = new double * * [m_iPatches]; 
    for (int f = 0; f < m_iPatches; f++) {
        m_dOutputDelta[f] = new double * [m_iInput]; 
        for (int i = 0; i < m_iInput; i++) {
            m_dOutputDelta[f][i] = new double[m_iInput]; 
            for (int j = 0; j < m_iInput; j++) {
                m_dOutputDelta[f][i][j] = 0;
                //cout << m_dInputDelta[f][i][j] << endl << flush;
            }
        }
    }

}
void PoolingLayer::PrintInput()
{
    cout << "Pooling Layer Input:" << endl << flush;
    for (int f = 0; f < m_iPatches; f++) {
        for (int i = 0; i < m_iInput; i++) {
            for (int j = 0; j < m_iInput; j++) {
                cout << right << setw(NUMBER_WIDTH) << fixed << setprecision(PRECISION) << m_dInput[f][i][j];
            }
            cout << endl << flush;
        }
        cout << endl << flush;
    }
    cout << endl << flush;
}


void PoolingLayer::PrintWeights() {
    cout << "Pooling Layer Weights:" << endl << flush;
    for (int f = 0; f < m_iPatches; f++) {
        for (int i = 0; i < m_iInput; i++) {
            for (int j = 0; j < m_iInput; j++) {    
                cout << right << setw(NUMBER_WIDTH) << fixed << setprecision(PRECISION) << m_iWeights[f][i][j];
            }
            cout << endl << flush;
        }
        cout << endl << flush;
    }
    cout << endl << flush;
}


void PoolingLayer::PrintOutput() {
    cout << "Pooling Layer Output:" << m_iOutput << endl << flush;
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

void PoolingLayer::ForwardCalculate()
{
    for (int f = 0; f < m_iPatches; f++) {
        for (int i = 0; i < m_iOutput; i++) {
            for (int j = 0; j < m_iOutput; j++) {
                m_dOutput[f][i][j] = 0;
                int iPrevi = 0;
                int iPrevj = 0;
                for (int fi = 0; fi < m_iFilter; fi++) {
                    for (int fj = 0; fj < m_iFilter; fj++) {
                        if (i*m_iFilter + fi < m_iInput && j*m_iFilter + fj < m_iInput && m_dOutput[f][i][j] < m_dInput[f][i*m_iFilter + fi][j*m_iFilter + fj])
                        {
                            m_iWeights[f][iPrevi][iPrevj] = 0;
                            iPrevi = i*m_iFilter + fi;
                            iPrevj = j*m_iFilter + fj;
                            m_iWeights[f][i*m_iFilter + fi][j*m_iFilter + fj] = 1;
                            m_dOutput[f][i][j] = m_dInput[f][i*m_iFilter + fi][j*m_iFilter + fj];
                        }
                    }
                }
            }
        }
    }
}

void PoolingLayer::CalculateError()
{
    for( int f = 0 ; f < m_iPatches ; f++ ) {
        for( int i = 0 ; i < m_iOutput ; i++ ) {
            for( int j = 0 ; j < m_iOutput ; j++ ) {
                m_dInputDelta[f][i][j] = (m_dTarget[f][i][j] - m_dOutput[f][i][j]) * m_dOutput[f][i][j] * (1.0 - m_dOutput[f][i][j]) ;  
                m_dError += 0.5 * (m_dTarget[f][i][j] - m_dOutput[f][i][j]) * (m_dTarget[f][i][j] - m_dOutput[f][i][j]) ;
            }
        }
    }
}

void PoolingLayer::SetError(double dError) {
    m_dError = dError;        
}

double PoolingLayer::GetError() {
    return m_dError;        
}


void PoolingLayer::BackwardCalculate()
{
    for (int f = 0; f < m_iPatches; f++) {
        for (int i = 0; i < m_iOutput; i++) {
            for (int j = 0; j < m_iOutput; j++) {
                for (int fi = 0; fi < m_iFilter; fi++) {
                    for (int fj = 0; fj < m_iFilter; fj++) {
                        //cout << i*m_iFilter + fi << " " << j*m_iFilter + fj  << "    " << flush;
                        if (i*m_iFilter + fi < m_iInput && j*m_iFilter + fj < m_iInput)
                        {
                            m_dOutputDelta[f][i*m_iFilter + fi][j*m_iFilter + fj] = 0;
                            if (m_iWeights[f][i*m_iFilter + fi][j*m_iFilter + fj] == 1) {
                                m_dOutputDelta[f][i*m_iFilter + fi][j*m_iFilter + fj] = m_dInputDelta[f][i][j];
                            }
                        }
                    }
                }
            }
        }
    }


    /*
    for (int f = 0; f < m_iPatches; f++) {
        for( int i = 0 ; i < m_iInput ; i++ ) {
            for( int j = 0 ; j < m_iInput ; j++ ) {
                m_dOutputDelta[f][i][j] = 0.0 ;
                for (int io = 0; io < m_iOutput; io++) {
                    for (int jo = 0; jo < m_iOutput; jo++) {
                        for(int fi = 0; fi < m_iFilter; fi++) {
                            for (int fj = 0; fj < m_iFilter; fj++) {
                                if (m_iWeights[f][io][jo] == 1) {
                                    m_dOutputDelta[f][i][j] = m_dInputDelta[f][io][jo] ;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    */
}

void PoolingLayer::SetTarget(double * * * Target)
{
    for( int f = 0 ; f < m_iPatches ; f++ ) {
        for( int i = 0 ; i < m_iOutput ; i++ ) {
            for( int j = 0 ; j < m_iOutput ; j++ ) {
                m_dTarget[f][i][j] = Target[f][i][j];
            }
        }
    }
}

void PoolingLayer::SetInput(double * * * Input)
{
    for (int f = 0; f < m_iPatches; f++) {
        for (int i = 0; i < m_iInput; i++) {
            for (int j = 0; j < m_iInput; j++) {
                m_dInput[f][i][j] = Input[f][i][j];
            }
        }
    }
}
void PoolingLayer::SetInputDelta(double * * * InputDetla)
{
    for (int f = 0; f < m_iPatches; f++) {
        for (int i = 0; i < m_iOutput; i++) {
            for (int j = 0; j < m_iOutput; j++) {
                m_dInputDelta[f][i][j] = InputDetla[f][i][j];
            }
        }
    }
}
void PoolingLayer::SetInputDelta(double * InputDetla)
{
    for (int f = 0; f < m_iPatches; f++) {
        for (int i = 0; i < m_iOutput; i++) {
            for (int j = 0; j < m_iOutput; j++) {
                m_dInputDelta[f][i][j] = InputDetla[f*m_iOutput*m_iOutput + i*m_iOutput + j];
            }
        }
    }
}
double * * * PoolingLayer::GetOutputDelta()
{
    return m_dOutputDelta;
}
double * * * PoolingLayer::GetOutput()
{
    return m_dOutput;
}
int PoolingLayer::GetOutputSize()
{
    return m_iOutput;
}
int PoolingLayer::GetInputSize()
{
    return m_iInput;
}

