#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>
#include "CustomFunctions.h"

using namespace std;

int main(){

    //vector that will store the output
    vector<double> outputs;

    //variable that determines whether the program will run or not, initially set to yes
    string run_program = "Y";

    cout << "Welcome to my program!" << endl;

    //while loop that will ask the user what they want to do, as long as they want to run the program
    while (run_program == "Y"){

        //string variable witht data file name
        string input_file = "Exercises/Lab1and2/input2D_float.txt";
        ifstream data_file(input_file);

        outputs.clear();

        //asks the user to choose what process they'd like to run
        string user_choice;
        cout << "Please select what you would like to do:" << endl;
        cout << "-Enter \"A\" to read the data and print N lines," << endl;
        cout << "-Enter \"B\" to calculate and print the magnitude of each point," << endl; 
        cout << "-Enter \"C\" to perform a least squares fit on the data," << endl;
        cout << "-Enter \"D\" to calculate x^y for each data point." << endl;
        cin >> user_choice;

        //prints N lines of the data if the user chooses option A
        if (user_choice == "A"){
        
            printData(data_file);
        }
        //calculates the magnitudes of the data points if the user chooses option  B
        else if (user_choice == "B"){

            outputs = calcMagnitudes(data_file);

        }
        //does the least squares fit if the user chooses option C
        else if (user_choice == "C"){

            outputs = doLeastSquares(data_file);

        }
        //calculates x^y for each point if the user chooses option D
        else if (user_choice == "D"){

            outputs = calcXtotheY(data_file);

        }
        //if the user inputs something different, an eror message is shown, and the program ends
        else {
            cout << "Input not a valid choice! Please enter either \"A\", \"B\", \"C\" or \"D\"." << endl;
        }   

        //if the user chose options B,C or D, they are asked if they wish to save the results to a text file
        if (user_choice == "B" || user_choice == "C" || user_choice == "D"){

            //asks user whether they wish to save the data, yes or no
            string user_print;
            cout << "Would you like to save your results to a file? Y/N:" << endl;
            cin >> user_print;

            //if yes, the data is saved
            if (user_print == "Y"){
                saveToFile(user_choice, outputs);
            }
            //if no, data isn't saved, program ends
            else if (user_print == "N"){
                cout << "Data will not be saved to file." << endl;
            }
            //if the user inputs something else, and error message is shown and the program terminates
            else {
                cout << "Input not recognised, terminating process." << endl;
            }

        }

        //Asks the user if they'd like to continue, if they enter "Y", the while loop continues, otherwise it is broken and the program ends
        cout << "Would you like to do something else? Enter Y to continue, or anything else to quit." << endl;
        cin >> run_program;
    }

    cout << "Thank you for using my program!" << endl;
    

}