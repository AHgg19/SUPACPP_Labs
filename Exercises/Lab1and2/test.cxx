#include <iostream>
#include <cmath>

int main(){

    std::cout << "Hello World!!" <<std::endl; //prints Hello World!!
    
    float x = 7.5; //defines two floats
    float y = 3.4;

    float magnitude = sqrt(x*x+y*y); //computes the magnitude squared of (x,y)

    //prints everything
    std::cout << "The magnitude of the vector with components (" << x << "," << y << ") is " << magnitude <<std::endl;

    //defines string variable to hold user input
    std::string user_input;

    //takes the first user input as a string
    std::cout << "Please enter the first component of the vector" <<std::endl;
    std::cin >> user_input;
    // std::cout << user_input <<std::endl;

    //converts the string to a float
    float a = std::stof(user_input);

    //same again
    std::cout << "Please enter the second component of the vector" <<std::endl;
    std::cin >> user_input;

    float b = std::stof(user_input);

    float magnitude2 = sqrt(a*a+b*b);

    //prints the magnitude of the vector (a,b), with a,b user defined
    std::cout << "The magnitude of your vector is " << magnitude2 << std::endl;

    return 0;
}
