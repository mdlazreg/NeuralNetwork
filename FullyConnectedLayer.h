#include "Layer.h"

class FullyConnectedLayer : public Layer {
    private:
        int m_iOutput;
        int m_iInput;
        int m_iPoolingInput;
        int m_iPatches;
        double * * m_dWeights;
        double * * m_dChangeWeights;
        double * m_dBiases;
        double * m_dChangeBiases;
        double * m_dInput;
        double * m_dTarget;
        double m_dError;
        double * m_dOutput;
        double * m_dOutputDelta;
        double * m_dInputDelta;
    public:
        FullyConnectedLayer(int iOutput, int iInput, double dLearningRate, double dMomentum);
        FullyConnectedLayer(int iInput, int iPatches, int iOutput, double dLearningRate, double dMomentum);
        void Initialize();
        void PrintInput();
        void PrintWeights();
        void PrintOutput();
        void ForwardCalculate();
        void CalculateError();
        void BackwardCalculate();
        void SetInput(double * * * Input);
        void SetInput(double * Input);
        void SetTarget(double * Target);
        void SetOutputDelta(double * OutputDetla);
        double * GetInputDelta();
        double * GetOutput();
        int GetOutputSize();
        int GetInputSize();
        double GetError() ;
        void SetError(double dError);
};
