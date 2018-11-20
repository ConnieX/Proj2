// IZP projekt 2
// Rosinska Monika
// Version 1
// 11.11. 2018

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

//function: try_input_to_int
double try_input_to_int(char* argv){
    double i;
    sscanf(argv, "%lg", &i);
    if (i > LONG_MAX){
        fprintf(stderr, "Count is too large.\n");
        return -1;
    }
    printf("%lg\n", i);
    return 1;
}

//function: tylor_log - count log(x) by Tylor polynomial
double tylor_log(double x, unsigned int n){
    if (x > 0 && x < 1){ //algorithm for 0 < x < 1
        double yn = 1.0; //variable for y power to n
        double sum = 0.0; //sum of gradually steps
        for (unsigned int i = 1; i <= n; i++){
            yn *= (1 - x);    //"maiking" y power to n
            sum = sum - (yn)/i;   //increasing sum of next part of algorithm
        }
        return sum;
    }
    else if (x >= 1){
        double yn = 1.0; //variable for y power to n
        double sum = 0.0; //sum of gradually steps
        for (unsigned int i = 1; i <= n; i++){
            yn *= (x - 1)/x;   //"maiking" y power to n
            sum += (yn/i);   //increasing sum of next part of algorithm
        }
        return sum;
    }
    else{
        fprintf(stderr, "Number must be higher than 0.\n");
        return -1;
    }
}

double cfrac_log(double x, unsigned int n){
    double z = (x - 1)/(x + 1); //auxiliary variable - simplification for more readable code
    double sum = 1.0; //sum of gradually steps
    for (unsigned int i = n; i > 0; i--){
        sum = (2*i - 1) - ((i*i * z*z) / sum);   //increasing sum of next part of algorithm
    }
    sum = 2*z / sum;
    return sum;
}

double tylor_pow(double x, double y, unsigned int n){
     //renaming constants - in algorithm is entered 'a' powered to 'x', but pow returns 'x' power to 'y'
    double a = x;
    x = y;

    double an = 1.0; //variable for a power to n
    double lnn = 1.0; //variable for ln(a) power to n
    int fact = 1; //variable for counting factorial
    double sum = 1.0;    //sum of gradually steps

    for(unsigned int i = 1; i <= n; i++){
        an *= x;
        fact *= i;
        lnn *= tylor_log(a, n);
        sum += (an * lnn)/fact;   //increasing sum of next part of algorithm
    }
    return sum;
}

double tylorcf_pow(double x, double y, unsigned int n){
    //renaming constants - in algorithm is entered 'a' powered to 'x', but pow returns 'x' power to 'y'
    double a = x;
    x = y;

    double an = 1; //variable for a power to n
    double lnn = 1; //variable for ln(y) power to n
    int fact = 1; //variable for counting factorial
    double sum = 1;   //sum of gradually steps

    for(unsigned int i = 1; i <= n; i++){
        an *= x;  //"maiking" a power to n
        fact *= i;  //"maiking" factorial n!
        lnn *= cfrac_log(a, n);  //"maiking" ln(a) power to n
        sum += (an * lnn)/fact;   //increasing sum of next part of algorithm
    }
    return sum;
}

int main(int argc, char* argv[]){
    if(argc == 4){
        if (strstr(argv[1], "--log") == NULL)
            fprintf(stderr, "Wrong argument.\nUse >>./proj2 --log x n<< for calculation the logarithm of x (n is polynomial repetition count). \nUse >>./proj2 --pow x y n<< for calculation the exponential equation x power to y (n is polynomial repetition count).\n\n")  ;       

        double x = try_input_to_int(argv[2]);
        unsigned int n = try_input_to_int(argv[3]);

        double test_log;
        test_log = log(x);
        printf("Logarithm: %.12g\n", test_log);
        printf("cfrac_log(1.1314) = %.12g\n", cfrac_log(x, n));
        printf("tylor_log(1.1314) = %.12g\n", tylor_log(x, n));    
    }
    else if(argc == 5){
        if (strstr(argv[1], "--pow") == NULL)
            fprintf(stderr, "Wrong argument.\nUse >>./proj2 --log x n<< for calculation the logarithm of x (n is polynomial repetition count). \nUse >>./proj2 --pow x y n<< for calculation the exponential equation x power to y (n is polynomial repetition count).\n\n")  ;       
        
        double x = try_input_to_int(argv[2]);
        double y = try_input_to_int(argv[3]);
        unsigned int n = try_input_to_int(argv[4]);
        double test_exp;
        test_exp = pow(x, y);
        printf("pow: %.12g\n", test_exp);
        printf("tylor_pow(1.23, 4.2) = %.12g\n", tylor_pow(x, y, n));
        printf("tylorcf_pow(1.23, 4.2) = %.12g\n", tylorcf_pow(x, y, n));
    }
    else
        fprintf(stderr, "Wrong argument.\nUse >>./proj2 --log x n<< for calculation the logarithm of x (n is polynomial repetition count). \nUse >>./proj2 --pow x y n<< for calculation the exponential equation x power to y (n is polynomial repetition count).\n\n")  ;       
    
    return 1;
}

