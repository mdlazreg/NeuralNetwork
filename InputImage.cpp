#include "InputImage.h"
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

const int iPatterns    = 7;
const int iInput       = 9;
const int iPatches     = 3;
const int iOutput      = 1;
double Input[iPatterns][iInput][iInput] = {
    {
        {0,0,	0,	0,	0,	0,	0,	0,	0},
        {0,0,	0,	0,	0,	0,	0,	0,	0},
        {0,0,	0,	1,	1,	1,	0,	0,	0},
        {0,0,	1,	0,	0,	0,	 1,	0,	0},
        {0,0,	1,	0,	0,	0,	 1,	0,	0},
        {0,0,	1,	0,	0,	0,	 1,	0,	0},
        {0,0,	0,	1,	1,	1,	0,	0,	0},
        {0,0,	0,	0,	0,	0,	0,	0,	0},
        {0,0,	0,	0,	0,	0,	0,	0,	0}
    },
    {
        {0,0,	0,	0,	0,	0,	0,	0,	0},
        {0,0,	0,	1,	1,	1,	0,	0,	0},
        {0,0,	0,	0,	0,	0,	0,	0,	0},
        {0,0,	1,	0,	0,	0,	 1,	0,	0},
        {0,0,	1,	0,	0,	0,	 1,	0,	0},
        {0,0,	1,	0,	0,	0,	 1,	0,	0},
        {0,0,	0,	1,	1,	1,	0,	0,	0},
        {0,0,	0,	0,	0,	0,	0,	0,	0},
        {0,0,	0,	0,	0,	0,	0,	0,	0}
    },
    {
        {0,0,	0,	0,	0,	0,	0,	0,	0},
        {0,0,	0,	0,	0,	0,	0,	0,	0},
        {0,0,	1,	0,	0,	0,	1,	0,	0},
        {0,0,	0,	1,	0,	1,	0,	0,	0},
        {0,0,	0,	0,	1,	0,	0,	0,	0},
        {0,0,	0,	1,	0,	1,	0,	0,	0},
        {0,0,	1,	0,	0,	0,	1,	0,	0},
        {0,0,	0,	0,	0,	0,	0,	0,	0},
        {0,0,	0,	0,	0,	0,	0,	0,	0}
    },
    {
        {0,0,	0,	0,	0,	0,	0,	0,	0},
        {0,1,	0,	0,	0,	0,	0,	1,	0},
        {0,0,	1,	0,	0,	0,	1,	0,	0},
        {0,0,	0,	1,	0,	1,	0,	0,	0},
        {0,0,	0,	0,	1,	0,	0,	0,	0},
        {0,0,	0,	1,	0,	1,	0,	0,	0},
        {0,0,	1,	0,	0,	0,	1,	0,	0},
        {0,1,	0,	0,	0,	0,	0,	1,	0},
        {0,0,	0,	0,	0,	0,	0,	0,	0}
    },
    {
        {0,0,	0,	0,	0,	0,	0,	0,	0},
        {0,0,	0,	1,	1,	1,	0,	0,	0},
        {0,0,	1,	0,	0,	0,	1,	0,	0},
        {0,0,	1,	0,	0,	0,	1,	0,	0},
        {0,0,	1,	0,	0,	0,	1,	0,	0},
        {0,0,	0,	1,	1,	1,	0,	0,	0},
        {0,0,	0,	0,	0,	0,	0,	0,	0},
        {0,0,	0,	0,	0,	0,	0,	0,	0},
        {0,0,	0,	0,	0,	0,	0,	0,	0}
    },
    {
        {0,0,	0,	0,	0,	0,	0,	0,	0},
        {0,0,	0,	1,	1,	1,	0,	0,	0},
        {0,0,	0,	0,	0,	0,	0,	0,	0},
        {0,0,	1,	0,	0,	0,	 1,	0,	0},
        {0,0,	1,	0,	0,	0,	 1,	0,	0},
        {0,0,	1,	0,	0,	0,	 1,	0,	0},
        {0,0,	0,	1,	1,	1,	0,	0,	0},
        {0,0,	0,	0,	0,	0,	0,	0,	0},
        {0,0,	0,	0,	0,	0,	0,	0,	0}
    },
    {
        {0,0,	0,	0,	0,	0,	0,	0,	0},
        {0,0,	0,	0,	0,	0,	0,	0,	0},
        {0,0,	1,	0,	0,	0,	1,	0,	0},
        {0,0,	0,	1,	0,	1,	0,	0,	0},
        {0,0,	0,	0,	1,	0,	0,	0,	0},
        {0,0,	0,	1,	0,	1,	0,	0,	0},
        {0,0,	1,	0,	0,	0,	1,	0,	0},
        {0,0,	0,	0,	0,	0,	0,	0,	0},
        {0,0,	0,	0,	0,	0,	0,	0,	0}
    }
};

/*
double Target[iPatterns][iPatches][iOutput][iOutput] = {
    {
        {
            {0,0,	0,	0,	0,	0,	0},
            {0,0,	0,	0,	0,	0,	0},
            {0,0,	0,	 1,	 1,	 1,	0},
            {0,0,	 1,	0,	0,	0,	 1},
            {0,0,	 1,	0,	0,	0,	 1},
            {0,0,	 1,	0,	0,	0,	 1},
            {0,0,	0,	 1,	 1,	 1,	0}
        },
        {
            {0,0,	0,	0,	0,	0,	0},
            {0,0,	0,	0,	0,	0,	0},
            {0,0,	0,	 1,	 1,	 1,	0},
            {0,0,	0,	0,	0,	0,	 1},
            {0,0,	 1,	0,	0,	0,	 1},
            {0,0,	 1,	0,	0,	0,	0},
            {0,0,	0,	 1,	 1,	 1,	0}
        },
        {
            {0,0,	0,	0,	0,	0,	0},
            {0,0,	0,	0,	0,	0,	0},
            {0,0,	0,	 1,	 1,	 1,	0},
            {0,0,	 1,	0,	0,	0,	 1},
            {0,0,	0,	0,	0,	0,	 1},
            {0,0,	 1,	0,	0,	0,	 1},
            {0,0,	0,	 1,	0,	0,	0}
        }
    }
};
*/

/*
double Target[iPatterns][iPatches][iOutput][iOutput] = {
    {
        {
            {0,0,	0,	0},
            {0,0,	0,	0},
            {0,0,	0,	 1},
            {0,0,	 1,	0}
        },
        {
            {0,0,	0,	0},
            {0,0,	0,	0},
            {0,0,	0,	 1},
            {0,0,	0,	0}
        },
        {
            {0,0,	0,	0},
            {0,0,	0,	0},
            {0,0,	0,	 1},
            {0,0,	 1,	0}
        }
    }
};
*/
double Target[iPatterns][iOutput] = {
    {
        0
    },
    {
        0
    },
    {
        1
    },
    {
        1
    },
    {
        0
    },
    {
        0
    },
    {
        1
    }
};

//xxd -b Input.bin
void FromPatternToBinary(double * * * fSurrogate, int iPatterns, int iInput, string sFile)
{
    ofstream fInput(sFile, ios::out | ios::binary);
    char iChar = 0;
    int Bin[8] = {1,2,4,8,16,32,64,128};
    int iIndex = 7;
    for( int p = 0 ; p < iPatterns ; p++ ) {
        for( int i = 0 ; i < iInput  ; i++ ) {
            for( int j = 0 ; j < iInput  ; j++ ) {
                if (fSurrogate[p][i][j] == 1) {
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
    }
    if (iIndex != 7) {
        fInput << iChar;
    }
}


void FromPatternToBinary(double * * * * fSurrogate, int iPatterns, int iPatches, int iInput, string sFile)
{
    ofstream fInput(sFile, ios::out | ios::binary);
    char iChar = 0;
    int Bin[8] = {1,2,4,8,16,32,64,128};
    int iIndex = 7;
    for( int p = 0 ; p < iPatterns ; p++ ) {
        for( int f = 0 ; f < iPatches ; p++ ) {
            for( int i = 0 ; i < iInput  ; i++ ) {
                for( int j = 0 ; j < iInput  ; j++ ) {
                    if (fSurrogate[p][f][i][j] == 1) {
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
        }
    }
    if (iIndex != 7) {
        fInput << iChar;
    }
}

#define NUMBER_WIDTH 8
#define PRECISION 2
double * * * FromHardcodedInput(int iPatterns, int iInput) {
    double * * * fInputSurrogate = new double * * [iPatterns];
    for(int p = 0; p < iPatterns; p++)
    {
        fInputSurrogate[p] = new double * [iInput];
        for( int i = 0 ; i < iInput ; i++ ) {
            fInputSurrogate[p][i] = new double[iInput];
            for( int j = 0 ; j < iInput ; j++ ) {
                fInputSurrogate[p][i][j] = Input[p][i][j];
            }
        }
    }
    return fInputSurrogate;
}

/*
double * * * * FromHardcodedTarget(int iPatterns, int iPatches, int iOutput) {
    double * * * * fInputSurrogate = new double * * * [iPatterns];
    for(int p = 0; p < iPatterns; p++)
    {
        fInputSurrogate[p] = new double * * [iPatches];
        for(int f = 0; f < iPatches; f++)
        {
            fInputSurrogate[p][f] = new double * [iOutput];
            for( int i = 0 ; i < iOutput ; i++ ) {
                fInputSurrogate[p][f][i] = new double[iOutput];
                for( int j = 0 ; j < iOutput ; j++ ) {
                        fInputSurrogate[p][f][i][j] = Target[p][f][i][j];
                }
            }
        }
    }
    return fInputSurrogate;
}
*/

double * * FromHardcodedTarget(int iPatterns, int iOutput) {
    double** fInputSurrogate = new double*[iPatterns];
    for(int i = 0; i < iPatterns; i++)
    {
        fInputSurrogate[i] = new double[iOutput];
        for( int j = 0 ; j < iOutput ; j++ ) {
                fInputSurrogate[i][j] = Target[i][j];
        }
    }
    return fInputSurrogate;
}

void FromHardcodedInputToBinaryFile()
{
    double* * * fInputSurrogate = FromHardcodedInput(iPatterns, iInput);
    FromPatternToBinary(fInputSurrogate, iPatterns, iInput, "Input.bin");
}

void FromHardcodedTargetToBinaryFile()
{
    double* * fInputSurrogate = FromHardcodedTarget(iPatterns,  iOutput);
    //FromPatternToBinary(fInputSurrogate, iPatterns, iPatches, iOutput, "Output.bin");
}
