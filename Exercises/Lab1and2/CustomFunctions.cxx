#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>

using namespace std;

//function that reads in a data file, given the file, and three (empty) vectors to hold the data
void readData(ifstream& data_file, vector<string>& lines, vector<double>& x, vector<double>& y){
    
    //creates a string ready to hold the contents of a given line of the file
    string line;
    //loops through file line by line
    while(getline(data_file,line)){

        //code that skips the first line which contains the column headings
        if(line.find('x') !=string::npos){continue;}

        //stores the first entry in the xs vector, and the second (after the comma) in the y vector
        string::size_type idx;
        x.push_back(stod(line, &idx));
        y.push_back(stod(line.substr(idx+1)));

        //stores the entire line as a string 
        lines.push_back(line);

    }

}

//function that calculates the magnitude of each point, stores it in a vector, as well as printing the result,
//given the file
vector<double> calcMagnitudes(ifstream& data_file){
    
    //prepares variables for the data in the file
    vector<double> x;
    vector<double> y;
    vector<string> data;

    //reads in the data
    readData(data_file, data, x, y);

    //creates vector for the output magnitudes
    vector<double> magnitudes;
    
    //loops through the points
    for(int i = 0; i<=x.size()-1; i++){
        //calculates the magnitude (squared) of each point
        magnitudes.push_back(sqrt(x[i]*x[i]+y[i]*y[i]));
        //prints each magnitude to the terminal
        cout << "The magnitude of the point (" << x[i] << "," << y[i] << ") is " << magnitudes[i] << endl;
    }
    return magnitudes;

}

//function to print the first N lines of a data file
void printData(ifstream& data_file){

    //agains sets everything up to read in the data file
    vector<double> x; 
    vector<double> y;
    vector<string> data;

    readData(data_file, data, x, y);

    //asks the user to input an integer number, stores it as a string
    string user_input;
    cout << "Please enter how many lines of the file you wish to print out" << endl;
    cin >> user_input;

    //converts user input to an integer
    int N = stoi(user_input);

    //checks whether the user input is greater than the size of the data; if it is, N is set to 5
    if (N <= data.size()){
        cout << "Input accepted, printing the first " << N << " lines:" << endl;
    }
    else if (N>data.size()){
        cout << "Input too large, now printing 5 lines instead:" << endl;
        N = 5;
    }

    //prints the first N lines of the data
    for (int i = 0; i<N; i++){
        cout << data[i] << endl;
    }

}

//fuinction to perform a least squares fit on the data, returning a vector with the fitted gradient and y-offset, as well as the
//chi squared of the fit, given a data file
vector<double> doLeastSquares(ifstream& data_file){

    //reads in the given data file
    vector<double> x; 
    vector<double> y;
    vector<string> data;

    vector<double> outputs;

    readData(data_file, data, x, y);

    //sets up a variable N equal to the number of data points, so we can use this later in loops
    int N = x.size();

    //initialises some variables to hold the values of:
    //the sum of all the xs
    double sumX=0; 
    //the sum of all the ys
    double sumY=0;
    //the sum of x times y for all points
    double sumXY=0;
    //the sum of x^2 for all points
    double sumXX=0;

    //looping through the points
    for (int i = 0; i<N; i++){
        //each line performs the appropriate sum for the given variables, for example the first line
        //adds the current x to sumX
        sumX += x[i];
        sumY += y[i];
        sumXY += x[i]*y[i];
        sumXX += x[i]*x[i];
    }

    //calculates the gradient p and y offset q using the formulae of the method of least squares
    double p = (N*sumXY-sumX*sumY)/(N*sumXX-sumX*sumX);
    double q = (sumXX*sumY-sumXY*sumX)/(N*sumXX - sumX*sumX);

    //prints the results of the least squares
    cout << "The fitted function is y=" << p << "x+" << q << endl;

    //initialises some variables ready to read in the expected errors
    vector<double> xerrs; 
    vector<double> yerrs;
    vector<string> errors;

    //reads in the file error2D_float.txt, storing the expected x errors in xerrs, and the expected y errors in yerrs
    string error_file_name = "Exercises/Lab1and2/error2D_float.txt";

    ifstream error_file(error_file_name);

    readData(error_file, errors, xerrs, yerrs);

    //initialises a variable for chi squared
    double chiSquared;

    //calculates chi squared according to the formula provided
    for (int i =0; i<=N-1; i++){
        chiSquared += (p*x[i]+q-y[i])*(p*x[i]+q-y[i])/(yerrs[i]*yerrs[i]+xerrs[i]*xerrs[i]);
    }

    //prints the value of chi squared
    cout << "The chi squared for the line of best fit is: " << chiSquared << endl;

    //prepares a variable to create or open a file StraightLineFunction.txt
    ofstream outStream;

    string filename = "Exercises/Lab1and2/StraightLineFunction.txt";

    //opens the file (or creates it if it does not exist)
    outStream.open(filename);

    //checks that the file has opened correctly, if not, an error message is displayed
    if (!outStream.is_open()) {
        cout << "Error opening file!" << endl;
    }

    //writes both the fitted function and the chi squared to the file
    outStream << "y=" << p << "x+" << q << endl;
    outStream << "Chi^2=" << chiSquared << endl;

    //closes the file
    outStream.close();

    //saves the gradient, y offset and chi squared to the outputs vector, and returns it
    outputs.push_back(p);
    outputs.push_back(q);
    outputs.push_back(chiSquared);

    return outputs;
}

//function that will calculate a^b (for integer b) recursively
double xToTheY(double a, int b){
    // first checks if b = 0, if so then the result is 1
    if (b == 0){
        return 1;
    }
    else {
        // otherwise, the function calls itself with the power reduced by one, and multiplied by the base
        // which is the fact that a^a*a^(n-1), which we can then iterate until the exponent becomes zero
        return xToTheY(a, b-1)*a;
    }

}

// calculates x^y for each data point
vector<double> calcXtotheY(ifstream& data_file){

    vector<double> x;
    vector<double> y;
    vector<string> data;
    
    vector<double> xToTheYs;

    // temporary variable to store the y value rounded to the nearest integer
    int ytemp = 0;


    readData(data_file, data, x, y);

    //loops through each data point
    for (int i = 0; i<=data.size()-1; i++){
        // rounds the current y value to an integer, which ytemp is then set to
        ytemp = round(y[i]);
        //evaluates x^y using the xToTheY function, which uses recursion, saving the result to xToTheYs
        xToTheYs.push_back(xToTheY(x[i],ytemp));
        //prints the results to the terminal
        cout << xToTheYs[i] << endl;
    }

    // returns the results
    return xToTheYs;

}

//function that will save the output of a process to a text file
//this will work for either calculating the magnitudes, doing the least squares, or calculating x^y
//here X is the user choice made when running AnalyseData.cxx, and will tell us what the user chose to do
//B corresponds to calculating magnitudes, C to least squares, and D to x^y
void saveToFile(string& X, vector<double>& data){

    //prepares variable to open file
    ofstream outStream;

    //B means calculating magnitudes, so we know a vector of doubles of length N (where N is the number of data points) will be passed in
    if (X == "B"){

        //creates an appropriate file name
        string fname = "Exercises/Lab1and2/magnitudes.txt";

        //opens (or creates) the file with the given name
        outStream.open(fname);

        //check if the file has been opened properly
        if (!outStream.is_open()) {
        cout << "Error opening file!" << endl;
        }


        outStream << "The magnitudes are:" << endl;
        //loops through the magnitudes, printing them line by line
        for (int i = 0 ; i<=data.size()-1; i++){
            outStream << data[i] << endl;
        }

        //closes the file
        outStream.close();

        //sends a message to the terminal to let the user know what their new file is called
        cout << "Data saving to \"magnitudes.txt\"" << endl;
    }

    //C means least squares fit, so we know a vector of length 3, of the format (gradient, y offset, chi squared) will be passed in
    else if (X == "C"){

        //creates an file with an appropriate name
        string fname = "Exercises/Lab1and2/least_squares.txt";

        outStream.open(fname);

        //check that file opened properly
        if (!outStream.is_open()) {
        cout << "Error opening file!" << endl;
        }

        //prints the results of the least squares fit to the file
        outStream << "The line of least fit is:" << endl;
        outStream << "y=" << data[0] << "x+" << data[1] << endl;
        outStream << "The chi squared of this fit is:" << endl;
        outStream << data[2] << endl;

        //closes file
        outStream.close();

        //prints message to terminal letting the user know what their new file is called
        cout << "Data saving to \"least_squares.txt\"" << endl;

    }

    //D means x^y, so again we expect a vector of length N to be passed in
    else if (X == "D") {

        //creates file with an appropriate name
        string fname = "Exercises/Lab1and2/x_to_the_ys.txt";

        outStream.open(fname);

        //check if file opened properly
        if (!outStream.is_open()) {
        cout << "Error opening file!" << endl;
        }

        outStream << "For each point, x^y is:" << endl;
        //loops through the data, printing it to the file line by line
        for (int i = 0 ; i<=data.size()-1; i++){
            outStream << data[i] << endl;
        }

        //closes file
        outStream.close();

        //prints message to the terminal to let the user know what their new file is called
        cout << "Data saving to \"x_to_the_ys.txt\"" << endl;
    }

}