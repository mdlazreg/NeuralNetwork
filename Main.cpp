#include "Input.h"
#include "NeuralNetwork.h"
#include <windows.h>
int main(void)
{
    double fError = 0.0004;
    double fLearningRate = 0.3;
    double fMomentum = 0.9;
    int iPatterns = 10;
    int iInput = 7;
    int iOutput = 4;
    static const int arr[] = {iInput,8,iOutput};
    //static const int arr[] = {iInput,12,8,iOutput};
    //static const int arr[] = {iInput,10,iOutput};
    //static const int arr[] = {iInput,12,iOutput};
    vector<int> vectorLayers(arr, arr + sizeof(arr) / sizeof(arr[0]) );


    double * * Input = FromHardcodedInput();//10 by 7
    double * * Target = FromHardcodedTarget();// 10 by 4

    //FromHardcodedInputToBinaryFile(); 
    //FromHardcodedTargetToBinaryFile();

    //double * * Input = FromBinaryFile(iPatterns,iInput,"Input.bin");
    //double * * Target = FromBinaryFile(iPatterns,iOutput,"Output.bin");


    /*
    for( int p = 0 ; p < iPatterns ; p++ ) {
        for( int i = 0 ; i < iInput ; i++ ) {
            cout << right << setw(NUMBER_WIDTH) << fixed << setprecision(PRECISION) << unsigned(Input[p][i]);
        }
        cout << "\n";
        for( int i = 0 ; i < iOutput ; i++ ) {
            cout << right << setw(NUMBER_WIDTH) << fixed << setprecision(PRECISION) << unsigned(Target[p][i]);
        }
        cout << "\n";
    }
    cout << "\n";
    */

    NeuralNetwork * pNeuralNetwork = new NeuralNetwork(iPatterns,Input, Target, vectorLayers, fError, fLearningRate, fMomentum);
    int iTrainingCycleMax = 2147483647;
    int iTrainingCycle = 0;
    pNeuralNetwork->SetError(0);
    while(iTrainingCycle < iTrainingCycleMax) {
        iTrainingCycle++;
        if (iTrainingCycle % 10000 == 0) {
            std::cout << "Training: " << iTrainingCycle << " Error: " << pNeuralNetwork->GetError() << endl << flush;
        }
        pNeuralNetwork->RandomizePatterns();
        pNeuralNetwork->SetError(0);
        for( int q = 0 ; q < pNeuralNetwork->GetPatterns() ; q++ ) {
            //cout << "pattern " << q << endl << flush;
            pNeuralNetwork->SetRandomizedInput(q);

            //pNeuralNetwork->PrintInputs();

            //pNeuralNetwork->PrintWeights();

            pNeuralNetwork->ForwardCalculate();

            //pNeuralNetwork->PrintOutputs();

            pNeuralNetwork->CalculateError();

            pNeuralNetwork->BackwardCalculate();

            //break;
            //Sleep(10000);
        }
        if( pNeuralNetwork->GetError() <= pNeuralNetwork->GetSuccess() )     
        {
      	    break;
        }
    }
    pNeuralNetwork->PrintWeights(); /*Print the weights of the trained network*/
    std::cout << "Patterns: Input,Target,Output" << endl << flush;
    pNeuralNetwork->PrintPatterns(); /*Compare the outputs from the trained network to the targets*/
    if( pNeuralNetwork->GetError() <= pNeuralNetwork->GetSuccess() )     
    {
        std::cout << "System trained after " << iTrainingCycle << " cycles." << endl << flush;
    }
    else
    {
        std::cout << "System not trained! " << iTrainingCycle << " cycles." << endl << flush;
    }  
    return 0;
}
