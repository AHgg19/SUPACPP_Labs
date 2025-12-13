#include <iostream> //needed to print to terminal
#include <string>
#include <vector>
#include <cmath> //needed for various mathematical functions like the error function, power function, as well as the value of pi
#include <random>
#include <fstream>
#include "FiniteFunctions.h" //header files for the main class
#include "CustomFunctions.h" //header file for the subclasses

#include "gnuplot-iostream.h" //Needed to produce plots (not part of the course) 

using namespace std;

//empty constructor for the normal distribution

Normal::Normal(){

    m_RMin = -10;
    m_RMax = 10;
    m_x0 = 4;
    m_sigma = 1;
    m_integral = NULL;
    m_IntDiv = 0;
    this->checkPath("DefaultFunction");
}

//initialised constructor for the normal distribution

Normal::Normal(double range_min, double range_max, double x0, double sigma, string outfile){

    m_RMin = range_min;
    m_RMax = range_max;
    m_x0 = x0;
    m_sigma = sigma;
    m_integral = NULL;
    m_IntDiv = 0;
    this->checkPath(outfile);
}

//empty constructor for Lorentz distribution

CauchyLorentz::CauchyLorentz(){

    m_RMin = -10;
    m_RMax = 10;
    m_x0 = 4;
    m_gamma = 1;
    m_integral = NULL;
    m_IntDiv = 0;
    this->checkPath("DefaultFunction");
}

//initialised constructor for Lorentz distribution

CauchyLorentz::CauchyLorentz(double range_min, double range_max, double x0, double gamma, string outfile){

    m_RMin = range_min;
    m_RMax = range_max;
    m_gamma = gamma;
    m_x0 = x0;
    m_integral = NULL;
    m_IntDiv = 0;
    this->checkPath(outfile);
}

//empty constructor for Crystal Ball distribution

CrystalBall::CrystalBall(){

    m_RMin = -10;
    m_RMax = 10;
    m_sigma = 1;
    m_x0 = 4;
    m_alpha = 1;
    m_n = 2;
    m_integral = NULL;
    m_IntDiv = 0;
    this->checkPath("DefaultFunction");
}

//initialised constructor for the Crystal Ball distribution

CrystalBall::CrystalBall(double range_min, double range_max, double x0, double sigma, double n, double alpha, string outfile){

    m_RMin = range_min;
    m_RMax = range_max;
    m_sigma = sigma;
    m_x0 = x0;
    m_n = n;
    m_alpha = alpha;
    m_integral = NULL;
    m_IntDiv = 0;
    this->checkPath(outfile);
}


//Setters

void Normal::setx0(double x0) {m_x0 = x0;};
void Normal::setsigma(double sigma) {m_sigma = sigma;};

void CauchyLorentz::setx0(double x0) {m_x0 = x0;};
void CauchyLorentz::setgamma(double gamma) {m_gamma = gamma;};

void CrystalBall::setx0(double x0) {m_x0 = x0;};
void CrystalBall::setsigma(double sigma) {m_sigma = sigma;};
void CrystalBall::setalpha(double alpha) {m_alpha = alpha;};
void CrystalBall::setn(double n) {m_n = n;};


//Getters 

double Normal::x0() {return m_x0;};
double Normal::sigma() {return m_sigma;};

double CauchyLorentz::x0() {return m_x0;};
double CauchyLorentz::gamma() {return m_gamma;};

double CrystalBall::x0() {return m_x0;};
double CrystalBall::sigma() {return m_sigma;};
double CrystalBall::alpha() {return m_alpha;};
double CrystalBall::n() {return m_n;};

//overrides the callFunction() function in the finite functions class, and replacing the inverse square with
//the normal distribution with mean x0 and standard deviation sigma

double Normal::callFunction(double x){

    return (1/(m_sigma*sqrt(2*M_PI)))*exp(-0.5*pow( ((x - m_x0)/m_sigma), 2 ));

}

//overrides callFunction(), now have a Cauchy-Lorentz distribution with mean x0 and half-width at half maximum

double CauchyLorentz::callFunction(double x){

    if (m_gamma > 0){

        return 1/(M_PI*m_gamma*(1+pow( (x-m_x0)/m_gamma , 2)));

    }
    //quickly checks that gamma if >0 (which it needs to be), if not program returns error
    else{

        cout << "Gamma must be >0!" << endl;
        return 1;
    }

}

//overrides callFunction for a Crystal Ball

double CrystalBall::callFunction(double x){

    //checks that the m and n parameters are valid

    if (m_n>1 and m_alpha > 0){

        //sets up the various constants in the distribution
        //from the cmath library, we use sqrt for square roots, erf for the error function, exp for the exponential function
        //pow(a,b) for a^b, and M_PI for the numerical value of pi
        //also, while in the various formulae for the distribution, we always have |alpha|. But, alpha > 0, so we don't
        //need the absolute value

        double D = sqrt(M_PI/2)*(1+erf(m_alpha/sqrt(2)));
        double C = (m_n/m_alpha)*(1/(m_n-1))*exp(-m_alpha*m_alpha/2);
        double N = 1/(m_sigma*(C+D));
        double B = (m_n/m_alpha)-m_alpha;
        double A = pow( (m_n/m_alpha), m_n )*exp(-m_alpha*m_alpha/2);
        
        double quantity = (x-m_x0)/m_sigma;

        //Crystal Ball is basically a Gaussian and a power function glued together, this checks which part of the function
        //we're in

        if (quantity > -m_alpha){

            return N*exp(-0.5*quantity*quantity);
        }
        if (quantity <= -m_alpha){

            return N*A*pow( B-quantity, -m_n );

        }

    }
    else {

        cout << "Must have alpha>0, n>1!" << endl;
        return 1;

    }

}

//for print info, we can use the printInfo() function from the parent class
//we can then add some distribution specific information, e.g. for the normal distribution we can print the mean and standard deviation

void Normal::printInfo(){

    cout << "Normal distribution with mean " << m_x0 << " and standard deviation " << m_sigma << "." << endl;   
    FiniteFunction::printInfo();

}

void CauchyLorentz::printInfo(){

    cout << "Cauchy-Lorentz distribution with mean " << m_x0 << " and half-width at half-maximum " << m_gamma << "." << endl;   
    FiniteFunction::printInfo();

}

void CrystalBall::printInfo(){

    cout << "Crystal Ball distribution with mean " << m_x0 << ", standard deviation " << m_sigma << ", n=" << m_n << ", and alpha=" << m_alpha << "." << endl;   
    FiniteFunction::printInfo();

}

//implementation of the metropolis algorithm, given a file name to write to, and the number of points the user wishes to generate
void Normal::generateRandomNumbers(int NpointsNormal, string fnameNormal){

    //sets up a random number generator
    random_device rd;
    mt19937 mtEngine{rd()};
    //have uniform distributions for x_i and T in the metropolis algorithm formulae
    uniform_real_distribution<double> uniformDist{m_RMin, m_RMax};
    uniform_real_distribution<double> uniformDist2{0,1};

    //sets up vector for the sampled points
    vector<double> pointsNormal;
    //when using the min function, it seems both inputs need to be the same, so this is just 1 as a double (clunk, but it works)
    double numberOne = 1;

    // generates the first random data point
    double x0 = uniformDist(mtEngine);

    pointsNormal.push_back(x0); 

    //now loop for the rest of the points
    for (int j = 1 ; j <=NpointsNormal-1 ; j++){

        //generates gaussian with sigma=0.7 (seems to work), centred on the previous point

        normal_distribution<float> gaussianPDF{pointsNormal[j-1], 0.7};

        //samples from the gaussian
        double y = gaussianPDF(mtEngine);


        //calculates the ratio f(y)/f(x_i) for the given distribution
        double ratio = Normal::callFunction(y)/Normal::callFunction(pointsNormal[j-1]);

        //calculates the minimum of the ratio and 1
        double A = min(ratio, numberOne);

        //random number sampled uniformly in the range 0 to 1
        double T = uniformDist2(mtEngine);

        //determines whether to accept y or not
        if (T < A){

            pointsNormal.push_back(y);

        }
        else{

            pointsNormal.push_back(pointsNormal[j-1]);

        }

    }

    //prepares file to write data to
    ofstream outStream;

    outStream.open("Outputs/data/" + fnameNormal + ".txt");

    //check if the file has been opened properly
    if (!outStream.is_open()) {
    cout << "Error opening file!" << endl;
    }

    //writes data to the file
    for (int i = 0 ; i<=pointsNormal.size()-1 ; i++){

        outStream << pointsNormal[i] << endl;

    }

    //closes file
    outStream.close();

}

//the exact same as above, except we now call either the Cauchy-Lorentz or Crystal Ball distributions

void CauchyLorentz::generateRandomNumbers(int NpointsLorentz, string fnameLorentz){

    random_device rd;
    mt19937 mtEngine{rd()};
    uniform_real_distribution<double> uniformDist{m_RMin, m_RMax};
    uniform_real_distribution<double> uniformDist2{0,1};

    vector<double> pointsLorentz;
    double numberOne = 1;

    double x0 = uniformDist(mtEngine);

    pointsLorentz.push_back(x0); 

    for (int j = 1 ; j <=NpointsLorentz-1 ; j++){

        normal_distribution<float> gaussianPDF{pointsLorentz[j-1], 0.7};

        double y = gaussianPDF(mtEngine);

        double ratio = CauchyLorentz::callFunction(y)/CauchyLorentz::callFunction(pointsLorentz[j-1]);

        double A = min(ratio, numberOne);

        double T = uniformDist2(mtEngine);

        if (T < A){

            pointsLorentz.push_back(y);

        }
        else{

            pointsLorentz.push_back(pointsLorentz[j-1]);

        }

    }

    ofstream outStream;

    outStream.open("Outputs/data/" + fnameLorentz + ".txt");

    //check if the file has been opened properly
    if (!outStream.is_open()) {
    cout << "Error opening file!" << endl;
    }

    for (int i = 0 ; i<=pointsLorentz.size()-1 ; i++){

        outStream << pointsLorentz[i] << endl;

    }

    outStream.close();

}

void CrystalBall::generateRandomNumbers(int NpointsCrystal, string fnameCrystal){

    random_device rd;
    mt19937 mtEngine{rd()};
    uniform_real_distribution<double> uniformDist{m_RMin, m_RMax};
    uniform_real_distribution<double> uniformDist2{0,1};

    vector<double> points;
    double numberOne = 1;

    double x0 = uniformDist(mtEngine);

    points.push_back(x0); 

    for (int j = 1 ; j <=NpointsCrystal-1 ; j++){

        normal_distribution<float> gaussianPDF{points[j-1], 0.7};

        double y = gaussianPDF(mtEngine);

        double ratio = CrystalBall::callFunction(y)/CrystalBall::callFunction(points[j-1]);

        double A = min(ratio, numberOne);

        double T = uniformDist2(mtEngine);

        if (T < A){

            points.push_back(y);

        }
        else{

            points.push_back(points[j-1]);

        }

    }

    ofstream outStream;

    outStream.open("Outputs/data/" + fnameCrystal + ".txt");

    //check if the file has been opened properly
    if (!outStream.is_open()) {
    cout << "Error opening file!" << endl;
    }

    for (int i = 0 ; i<=points.size()-1 ; i++){

        outStream << points[i] << endl;

    }

    outStream.close();

}
