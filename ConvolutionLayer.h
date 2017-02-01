#include "Layer.h"

class ConvInputOutputLayer : public Layer {
    private:
        int m_iInput;
        int m_iFilter;
        int m_iPadding;
        int m_iStride;
        int m_iOutput;
        int m_iPatches;
        double * * * m_dWeights;
        double * * * m_dChangeWeights;
        double * m_dBiases;
        double * m_dChangeBiases;
        double * * m_dInput;

        double m_dError;
        double * * * m_dTarget;

        double * * * m_dOutput;
        double * * * m_dInputDelta;
        double * * m_dOutputDelta;
    public:
        ConvInputOutputLayer(int iInput, int iFilter, int iPadding, int iStride, int iPatches, double dLearningRate, double dMomentum);
        void PrintInput();
        void PrintWeights();
        void PrintOutput();
        void ForwardCalculate();
        void CalculateError();
        void BackwardCalculate();
        void SetInput(double * * Input);
        void SetTarget(double * * * Target);
        void SetInputDelta(double * * * InputDetla);
        double * * GetOutputDelta();
        double * * * GetOutput();
        double GetError() ;
        void SetError(double dError);
        int GetOutputSize();
        int GetInputSize();
};
