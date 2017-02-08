#include "ConvNeuralNetwork.h"
#include "InputImage.h"
ConvNeuralNetwork::ConvNeuralNetwork(int iPatterns, double * * * dInput, double * * dTarget, int iInput, int iOutput, int iFilter, int iPadding, int iStride, int iPatches, double dSuccess, double dLearningRate, double dMomentum) : 
    m_iPatterns(iPatterns), 
    m_arrayInput(dInput), 
    m_arrayTarget(dTarget), 
    m_iInput(iInput), 
    m_iOutput(iOutput), 
    m_iFilter(iFilter), 
    m_iPadding(iPadding), 
    m_iStride(iStride), 
    m_iPatches(iPatches), 
    m_dSuccess(dSuccess), 
    m_dLearningRate(dLearningRate), 
    m_dMomentum(dMomentum) {
    m_pConvInputOutputLayer = new ConvInputOutputLayer(iInput, iFilter, iPadding, iStride, iPatches, dLearningRate, dMomentum);
    int iPoolingLayerInput = (iInput - iFilter + 2*iPadding)/iStride + 1;
    m_pPoolingLayer = new PoolingLayer(iPoolingLayerInput, 2, iPatches);

    m_pFullyConnectedLayer = new FullyConnectedLayer(m_pPoolingLayer->GetOutputSize(), iPatches, 1, dLearningRate, dMomentum); 



    m_iRandomizedIndex = new int[m_iPatterns];
    for (int p = 0; p < m_iPatterns; p++) {
        m_iRandomizedIndex[p] = p;
    }
}

void ConvNeuralNetwork::RandomizePatterns() {
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
void ConvNeuralNetwork::SetInputTarget(int i)
{
    m_pConvInputOutputLayer->SetInput(m_arrayInput[i]);
    m_pFullyConnectedLayer->SetTarget(m_arrayTarget[i]);
}
void ConvNeuralNetwork::SetRandomizedInput(int p) {
    int i = m_iRandomizedIndex[p];
    SetInputTarget(i);
}
int ConvNeuralNetwork::GetPatterns() {
    return m_iPatterns;
}
void ConvNeuralNetwork::PrintInputs()
{
    m_pConvInputOutputLayer->PrintInput();
    m_pPoolingLayer->PrintInput();
    m_pFullyConnectedLayer->PrintInput();

}
void ConvNeuralNetwork::PrintOutputs()
{
    m_pConvInputOutputLayer->PrintOutput();
    m_pPoolingLayer->PrintOutput();
    m_pFullyConnectedLayer->PrintOutput();
}
void ConvNeuralNetwork::PrintWeights()
{
    m_pConvInputOutputLayer->PrintWeights();
    m_pPoolingLayer->PrintWeights();
    m_pFullyConnectedLayer->PrintWeights();
}
void ConvNeuralNetwork::PrintPatterns()
{
    for( int p = 0 ; p < m_iPatterns ; p++ ) {
        for( int i = 0 ; i < m_iInput ; i++ ) {
            for( int j = 0 ; j < m_iInput ; j++ ) {
                cout << right << setw(NUMBER_WIDTH) << fixed << setprecision(PRECISION) << m_arrayInput[p][i][j];
            }
            cout << endl << flush;
        }
        cout << endl << flush;
        cout << endl << flush;
        for( int i = 0 ; i < m_iOutput ; i++ ) {
                cout << right << setw(NUMBER_WIDTH) << fixed << setprecision(PRECISION) << m_arrayTarget[p][i];
        }

        SetInputTarget(p);

        cout << "\n";
        ForwardCalculate();
        m_pFullyConnectedLayer->PrintOutput();
        cout << "\n\n";
    }
}


void ConvNeuralNetwork::PrintTests()
{
    double * * * Input = FromHardcodedInput(7, 9);//2 by 25
    double * * Target = FromHardcodedTarget(7, 1);
    for( int p = 3 ; p < 7 ; p++ ) {
        for( int i = 0 ; i < m_iInput ; i++ ) {
            for( int j = 0 ; j < m_iInput ; j++ ) {
                cout << right << setw(NUMBER_WIDTH) << fixed << setprecision(PRECISION) << Input[p][i][j];
            }
            cout << endl << flush;
        }
        cout << endl << flush;
        cout << endl << flush;
        for( int i = 0 ; i < m_iOutput ; i++ ) {
                cout << right << setw(NUMBER_WIDTH) << fixed << setprecision(PRECISION) << Target[p][i];
        }

        m_pConvInputOutputLayer->SetInput(Input[p]);
        m_pFullyConnectedLayer->SetTarget(Target[p]);


        cout << "\n";
        ForwardCalculate();
        m_pFullyConnectedLayer->PrintOutput();
        cout << "\n\n";
    }
}

void ConvNeuralNetwork::ForwardCalculate()
{
    m_pConvInputOutputLayer->ForwardCalculate();
    m_pPoolingLayer->SetInput(m_pConvInputOutputLayer->GetOutput());
    m_pPoolingLayer->ForwardCalculate();
    m_pFullyConnectedLayer->SetInput(m_pPoolingLayer->GetOutput());
    m_pFullyConnectedLayer->ForwardCalculate();
}


void ConvNeuralNetwork::CalculateError()
{
    m_pFullyConnectedLayer->CalculateError();
}
void ConvNeuralNetwork::BackwardCalculate()
{
    m_pFullyConnectedLayer->BackwardCalculate();
    m_pPoolingLayer->SetOutputDelta(m_pFullyConnectedLayer->GetInputDelta());
    m_pPoolingLayer->BackwardCalculate();
    m_pConvInputOutputLayer->SetOutputDelta(m_pPoolingLayer->GetInputDelta());
    m_pConvInputOutputLayer->BackwardCalculate();
}

void ConvNeuralNetwork::SetError(double dError) {
    m_pFullyConnectedLayer->SetError(dError);
}
double ConvNeuralNetwork::GetError() {
    return m_pFullyConnectedLayer->GetError();;        
}
double ConvNeuralNetwork::GetSuccess() {
    return m_dSuccess;        
}


