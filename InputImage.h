#include <cstdint>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>
#include <math.h>
#include <list>
#include <stdio.h>
#include <stdlib.h>
using namespace std;


double * * FromBinaryFile(int iPatterns, int iHeight, string sFile);
double * * FromBinaryFile(int iPatterns, int iPatches, int iHeight, string sFile);
//double * * * * FromHardcodedTarget(int iPatterns, int iPatches, int iOutput);
double * * FromHardcodedTarget(int iPatterns, int iOutput);
double * * * FromHardcodedInput(int iPatterns, int iInput);