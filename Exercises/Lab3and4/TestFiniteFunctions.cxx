#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "FiniteFunctions.h"
#include "CustomFunctions.h"

using namespace std;

int main(){

    //reads in the mystery data
    string line;
    ifstream data_file("Outputs/data/MysteryData16162.txt");

    //double vector ready to take in the data points
    vector<double> mysteryData;

    //reads the data file line by line and stores the contents in mysteryData
    while(getline(data_file,line)){
        mysteryData.push_back(stod(line));
    }

    data_file.close();

    //creates an instance of the FiniteFunction class, with the low end of the function range 
    FiniteFunction myFunction(-10, 10, "MysteryData16162Plot");

    //creates an instance of each of subclasses for each distribution
    Normal normalDist(-10, 10, 3, 0.9, "NormalDistributionTest");
    CauchyLorentz lorentzDist(-10, 10, 3, 0.77, "LorentzDistTest");
    CrystalBall crystDist(-10, 10, 3, 0.8, 2, 1, "CrystalBallTest");

    //sets a number of bins to use
    int myBins = 50;

    //sets isData to true, which will plot the data points as black points
    //this is already true as default, so not **really** needed, but allows us to easily toggle it to false should we want to do so
    bool isData = true; 

    //number of divisions used to do the integration, we choose 1000
    int myDivs = 1000;

    //plots the test function, which is now normalised, i.e. scaled by the value of its integral over the given function range
    //myFunction.plotFunction();
    //plots the mysterydata, on the same plot as the function
    //myFunction.plotData(mysteryData, myBins, isData);
    

    //generates 100000 randomly sampled points from the normal distribution
    normalDist.generateRandomNumbers(100000, "NormalDistributionMysteryData");

    //stores the sampled points in an appropriate container
    vector<double> normalMysteryData;
    string normalLine;

    ifstream normalDataFile("Outputs/data/NormalDistributionMysteryData.txt");

    while(getline(normalDataFile, normalLine)){

        normalMysteryData.push_back(stod(normalLine));

    }

    normalDataFile.close();

    //generates 100000 randomly sampled points from the normal distribution
    lorentzDist.generateRandomNumbers(100000, "LorentzDistributionMysteryData");

    //stores the sampled points in an appropriate container
    vector<double> lorentzMysteryData;
    string lorentzLine;

    ifstream lorentzDataFile("Outputs/data/LorentzDistributionMysteryData.txt");

    while(getline(lorentzDataFile, lorentzLine)){

        lorentzMysteryData.push_back(stod(lorentzLine));

    }

    lorentzDataFile.close();

    //calculates the integral of the normal distribution with a chosen number of divisions
    normalDist.integral(myDivs);
    //prints information about the distribution
    normalDist.printInfo();
    //plots the function, the mystery data, and the data sampled from the normal distribution
    normalDist.plotFunction();
    normalDist.plotData(normalMysteryData, myBins, false);
    normalDist.plotData(mysteryData, myBins, isData);

    //calculates integral of the Cauchy-Lorentz distribution
    lorentzDist.integral(myDivs);
    //prints information about the Cauchy-Lorentz distribution
    lorentzDist.printInfo();
    //plots the distribution, the mystery data, and the sampled points
    lorentzDist.plotFunction();
    lorentzDist.plotData(lorentzMysteryData, myBins, false);
    lorentzDist.plotData(mysteryData, myBins, isData);

    //generates 100000 randomly sampled points from the normal distribution
    crystDist.generateRandomNumbers(100000, "CrystalBallDistributionMysteryData");

    //stores the sampled points in an appropriate container
    vector<double> crystalMysteryData;
    string crystalLine;

    ifstream crystalDataFile("Outputs/data/CrystalBallDistributionMysteryData.txt");

    while(getline(crystalDataFile, crystalLine)){

        crystalMysteryData.push_back(stod(crystalLine));

    }

    crystalDataFile.close();
    
    crystDist.integral(myDivs);
    crystDist.printInfo();
    crystDist.plotFunction();
    crystDist.plotData(crystalMysteryData, myBins, false);
    crystDist.plotData(mysteryData, myBins, isData);

    //after testing, it is clear that the mystery data came from a Cauchy-Lorentz distribution 
    //centred at x=3, with a half-width at half-maximum of 0.77

}
