#include "FiniteFunctions.h" //header file for the parent class
#include <vector>
#include <string>

using namespace std;

#pragma once

class Normal : public FiniteFunction {

    public:
        Normal();
        Normal(double range_min, double range_max, double x0, double sigma, string outfile);
        //setters
        double x0(); //mean of the distribution
        double sigma(); //standard deviation of the distribution
        
        //getters
        void setx0(double x0);
        void setsigma(double sigma);
        void generateRandomNumbers(int NpointsNormal, string fnameNormal);

        double callFunction(double x); //overrides the function "callFunction()", replaces everything with a normal distribution
        void printInfo(); //overrides printInfo() to print info specific to the distribution

    private:

        double m_x0;
        double m_sigma;
        double m_integral; //holds value of the integral
        int m_IntDiv; //holds value of the number of divisions used

};

class CauchyLorentz : public FiniteFunction {

    public:

        CauchyLorentz();
        CauchyLorentz(double range_min, double range_max, double x0, double gamma, string outfile);

        //setters
        double x0(); //mean of the distribution
        double gamma(); //half-width at half-maximum of Cauchy Lorentz distribution

        //getters
        void setx0(double x0);
        void setgamma(double gamma);
        void generateRandomNumbers(int NpointsLorentz, string fnameLorentz);

        double callFunction(double x);
        void printInfo();

    private:

        double m_x0;
        double m_gamma;
        double m_integral;
        int m_IntDiv;

};

class CrystalBall : public FiniteFunction{

    public:

        CrystalBall();
        CrystalBall(double range_min, double range_max, double x0, double sigma, double n, double alpha, string outfile);

        //setters
        double sigma(); //standard deviation of the distribution
        double x0(); //mean of the distribution
        double alpha(); //point where crystal ball changes from power law to Gaussian
        double n(); //power of the power-law tail in crystal ball

        //getters
        void setx0(double x0);
        void setsigma(double sigma);
        void setalpha(double alpha);
        void setn(double n);
        void generateRandomNumbers(int NpointsCrystal, string fnameCrystal);

        double callFunction(double x);
        void printInfo();

    private:

        double m_sigma;
        double m_x0;
        double m_alpha;
        double m_n;
        double m_integral;
        int m_IntDiv;

};