#include "InputImage.h"
#include "ConvNeuralNetwork.h"
#include <windows.h>
int main(void)
{
    double dSuccess = 0.0004;
    double dLearningRate = 0.9;
    double dMomentum = 0.1;

    /*
    int iPatterns = 2;
    int iInput = 25;
    int iOutput = 9;
    */
    int iPatterns   = 3;
    int iInput      = 9;
    int iFilter     = 3;
    int iStride     = 1;
    int iPadding    = 0;
    int iPatches    = 3;
    int iOutput     = 1;

    static const int arr[] = {iInput,iOutput};
    //static const int arr[] = {iInput,12,8,iOutput};
    //static const int arr[] = {iInput,10,iOutput};
    //static const int arr[] = {iInput,12,iOutput};
    vector<int> vectorLayers(arr, arr + sizeof(arr) / sizeof(arr[0]) );

    double * * * Input = FromHardcodedInput(iPatterns, iInput);//2 by 25
    double * * Target = FromHardcodedTarget(iPatterns, iOutput);
    //double * * * * Target = FromHardcodedTarget(iPatterns, iPatches, iOutput);// 2 by 2
    //FromHardcodedInputToBinaryFile(); 
    //FromHardcodedTargetToBinaryFile();

    //double * * Input = FromBinaryFile(iPatterns,iInput,"Input.bin");
    //double * * Target = FromBinaryFile(iPatterns,iOutput,"Output.bin");


  /*  
    for( int p = 0 ; p < iPatterns ; p++ ) {
        for( int i = 0 ; i < iInput ; i++ ) {
            for( int j = 0 ; j < iInput ; j++ ) {
                cout << right << setw(NUMBER_WIDTH) << fixed << setprecision(PRECISION) << Input[p][i][j];
            }
            cout << endl << flush;
        }
        cout << endl << flush;
        cout << endl << flush;
        for( int f = 0 ; f < iPatches ; f++ ) {
            for( int i = 0 ; i < iOutput ; i++ ) {
                for( int j = 0 ; j < iOutput ; j++ ) {
                    cout << right << setw(NUMBER_WIDTH) << fixed << setprecision(PRECISION) << Target[p][f][i][j];
                }
                cout << endl << flush;
            }
            cout << endl << flush;
        }
        cout << endl << flush;
        cout << endl << flush;
    }
    */

    ConvNeuralNetwork * pNeuralNetwork = new ConvNeuralNetwork(iPatterns, Input, Target, iInput, iOutput, iFilter, iPadding, iStride, iPatches,  dSuccess, dLearningRate, dMomentum);
    int iTrainingCycleMax = 2147483647;
    int iTrainingCycle = 0;
    while(iTrainingCycle < iTrainingCycleMax) {
        pNeuralNetwork->RandomizePatterns();
        pNeuralNetwork->SetError(0);
        for( int q = 0 ; q < pNeuralNetwork->GetPatterns() ; q++ ) {
            pNeuralNetwork->SetRandomizedInput(q);
            //pNeuralNetwork->PrintInputs();

            //pNeuralNetwork->PrintWeights();

            pNeuralNetwork->ForwardCalculate();
            //pNeuralNetwork->PrintOutputs();
            //break;

            pNeuralNetwork->CalculateError();

            pNeuralNetwork->BackwardCalculate();
            //pNeuralNetwork->PrintWeights();
            //Sleep(1000);
        }
        if( pNeuralNetwork->GetError() <= pNeuralNetwork->GetSuccess() )     
        {
            cout << pNeuralNetwork->GetError() << " : " <<  pNeuralNetwork->GetSuccess() << endl << flush;
      	    break;
        }
        if (iTrainingCycle % 100 == 0) {
            std::cout << "Training: " << iTrainingCycle << " Error: " << pNeuralNetwork->GetError() << endl << flush;
        }
        iTrainingCycle++;
    }
    //std::cout << "Weights:" << endl << flush;
    pNeuralNetwork->PrintWeights(); /*Print the weights of the trained network*/
    std::cout << "Patterns: Input,Target,Output" << endl << flush;
    //pNeuralNetwork->PrintPatterns(); /*Compare the outputs from the trained network to the targets*/
    std::cout << "Tests: Input,Target,Output" << endl << flush;
  
    if( pNeuralNetwork->GetError() <= pNeuralNetwork->GetSuccess() )     
    {
        std::cout << "System trained after " << iTrainingCycle << " cycles." << endl << flush;
      //    pNeuralNetwork->PrintTests();
    }
    else
    {
        std::cout << "System not trained! " << iTrainingCycle << " cycles." << endl << flush;
    }  
    return 0;
}
