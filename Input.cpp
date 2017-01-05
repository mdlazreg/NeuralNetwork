#include "Input.h"
double * * FromBinaryFile(int iPatterns, int iHeight, string sFile)
{    
    double** fInputSurrogate = new double*[iPatterns];
    std::ifstream is(sFile); 
    char in;
    int iPattern = 0;
    fInputSurrogate[iPattern] = new double[iHeight];
    int iIndex = 0;
    while (is.get(in)) {
        for (int i = 0; i < 8; i++) {
            fInputSurrogate[iPattern][iIndex] = 0;
            if (!!((in << i) & 0x80)) {
                fInputSurrogate[iPattern][iIndex] = 1;
            }

            iIndex++;
            if (iIndex == iHeight)
            {
                iIndex = 0;
                iPattern++;
                if (iPattern == iPatterns) {
                    break;
                }
                fInputSurrogate[iPattern] = new double[iHeight];
            }
        }
        if (iPattern == iPatterns) {
            break;
        }
    }
    is.close(); 
    return fInputSurrogate;
}


const int   PatternCount     = 10;
const int   InputNodes       = 7;
const int   OutputNodes      = 4;
double Input [PatternCount][InputNodes]= {

  { 1, 1, 1, 1, 1, 1, 0 },  // Code 7 segments du 0
  { 0, 1, 1, 0, 0, 0, 0 },  // Code 7 segments du 1
  { 1, 1, 0, 1, 1, 0, 1 },  // Code 7 segments du 2
  { 1, 1, 1, 1, 0, 0, 1 },  // Code 7 segments du 3
  { 0, 1, 1, 0, 0, 1, 1 },  // Code 7 segments du 4
  { 1, 0, 1, 1, 0, 1, 1 },  // Code 7 segments du 5
  { 0, 0, 1, 1, 1, 1, 1 },  // Code 7 segments du 6
  { 1, 1, 1, 0, 0, 0, 0 },  // Code 7 segments du 7
  { 1, 1, 1, 1, 1, 1, 1 },  // Code 7 segments du 8
  { 1, 1, 1, 0, 0, 1, 1 }   // Code 7 segments du 9
};

double Target[PatternCount][OutputNodes] = {

  { 0, 0, 0, 0 },  // Code binaire du 0
  { 0, 0, 0, 1 },  // Code binaire du 1
  { 0, 0, 1, 0 },  // Code binaire du 2
  { 0, 0, 1, 1 },  // Code binaire du 3
  { 0, 1, 0, 0 },  // Code binaire du 4
  { 0, 1, 0, 1 },  // Code binaire du 5
  { 0, 1, 1, 0 },  // Code binaire du 6
  { 0, 1, 1, 1 },  // Code binaire du 7
  { 1, 0, 0, 0 },  // Code binaire du 8
  { 1, 0, 0, 1 }   // Code binaire du 9
};
//xxd -b Input.bin
void FromPatternToBinary(double * * fSurrogate, int iPatterns, int iHeight, string sFile)
{
    ofstream fInput(sFile, ios::out | ios::binary);
    char iChar = 0;
    int Bin[8] = {1,2,4,8,16,32,64,128};
    int iIndex = 7;
    for( int p = 0 ; p < iPatterns ; p++ ) {
        for( int i = 0 ; i < iHeight  ; i++ ) {
            if (fSurrogate[p][i] == 1) {
                iChar += Bin[iIndex];
            }
            iIndex--;
            if (iIndex < 0) {
                fInput << iChar;
                iIndex = 7;
                iChar = 0;
            }
        }   
    }
    if (iIndex != 7) {
        fInput << iChar;
    }
}

double * * FromHardcodedInput() {
    double** fInputSurrogate = new double*[PatternCount];
    for(int i = 0; i < PatternCount; i++)
    {
        fInputSurrogate[i] = new double[InputNodes];
        for( int j = 0 ; j < InputNodes ; j++ ) {
                fInputSurrogate[i][j] = Input[i][j];
        }
    }
    return fInputSurrogate;
}

double * * FromHardcodedTarget() {
    double** fInputSurrogate = new double*[PatternCount];
    for(int i = 0; i < PatternCount; i++)
    {
        fInputSurrogate[i] = new double[OutputNodes];
        for( int j = 0 ; j < OutputNodes ; j++ ) {
                fInputSurrogate[i][j] = Target[i][j];
        }
    }
    return fInputSurrogate;
}

void FromHardcodedInputToBinaryFile()
{
    double** fInputSurrogate = FromHardcodedInput();
    FromPatternToBinary(fInputSurrogate, PatternCount, InputNodes, "Input.bin");
}

void FromHardcodedTargetToBinaryFile()
{
    double** fInputSurrogate = FromHardcodedTarget();
    FromPatternToBinary(fInputSurrogate, PatternCount, OutputNodes, "Output.bin");
}