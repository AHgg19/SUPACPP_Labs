#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>

using namespace std;

#pragma once

void readData(ifstream&, vector<string>&, vector<double>&, vector<double>&);
void printData(ifstream&);
vector<double> calcMagnitudes(ifstream&);
vector<double> doLeastSquares(ifstream&);
double xToTheY(double, int);
vector<double> calcXtotheY(ifstream&);
void saveToFile(string&, vector<double>&);