// IZP projekt 2
// Rosinska Monika
// Version 1
// 11.11. 2018

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

//function: validate_number - control of right input
int validate_double(const char* argv, double** d, int c){
    int size = strlen(argv); //lenght of argv
    int decpoint = 0; //number of decimal points
    int minus = 0; //number of minuses
    if (strcmp(argv, "inf") == 0){
        **d = INFINITY; //set INFINITY if 'inf' was given
        return 1;
    }
    if (strcmp(argv, "INF") == 0){
        **d = INFINITY; //set INFINITY if 'INF' was given
        return 1;
    }
        
    switch (c) //swtich between controlling x (only positive numbers) and controlling y (can be negative)
    {
        case 1:
            for (int i = 0; i < size-1; i++){
                if((argv[i] < 48) || (argv[i] > 57)){ //if there's different character than numbers or '.', return 0 and break process
                    if (argv[i] == 46)
                        decpoint++;
                    else
                        return 0;    
                }    
            }
            break;
        case 2:
            for (int i = 0; i < size-1; i++){
                if((argv[i] < 48) || (argv[i] > 57)){ //if there's different character than numbers or '.', return 0 and break process
                    if (argv[i] == 46)
                        decpoint++;
                else if (argv[i] == 45)
                    minus++;
                else
                    return 0;        
                }
            }
        default:
            break;
    }
    if (decpoint > 1 && minus > 1) //can be only one decimal point and only one minus
        return 0;
    else //if everything is correct
        return 1;
}



//function: try_input_to_double
int try_input_to_num_double(char* argv, double* d, int c){
    double i;
    if(c == 1){
        if(!validate_double(argv, &d, c) || !sscanf(argv, "%lg", &i)){
            fprintf(stderr, "Wrong argument: %s \nNuber must be greater or equal to 0.\nPlease use decimal point.\n", argv);
            return 0;
        }
    }
    else if(c == 2){
        if(!validate_double(argv, &d, c) || !sscanf(argv, "%lg", &i)){
            fprintf(stderr, "Wrong argument: %s \nNuber must be greater or equal to 0.\nPlease use decimal point.\n", argv);
            return 0;
        }
    }
    *d = i;
    return 1;
}

int validate_n(char* argv){
    int size = strlen(argv); //lenght of argv
    int i;
    for (i = 0; i < size-1; i++){
        if((argv[i] < 48) || (argv[i] > 57)) //if there's different character than numbers, return 0 and break process
            return 0;        
    }
    return 1;   
}

int try_input_to_num_int(char* argv, unsigned int* d){
    unsigned int i;
    if(!validate_n(argv) || !sscanf(argv, "%d", &i)){
        fprintf(stderr, "Wrong argument: %s \nRepetition count must be whole possitive number.\n", argv);
        return 0;
    }
    if (i <= 0){
        fprintf(stderr, "Count can't be 0 or less.\n");
        return 0;
    } 

    *d = i;
    printf("%d\n", i);
    return 1;
}

//function: taylor_log - count log(x) by Taylor polynomial
double taylor_log(double x, unsigned int n){
    if(x == INFINITY)
        return INFINITY;
    else if (x == 0)
        return -INFINITY;
    else if (x > 0 && x < 1){ //algorithm for 0 < x < 1
        double yn = 1.0; //variable for y power to n
        double sum = 0.0; //sum of gradually steps
        for (unsigned int i = 1; i <= n; i++){
            yn *= (1 - x);    //"maiking" y power to n
            sum = sum - (yn)/i;   //increasing sum of next part of algorithm
        }
        return sum;
    }
    else if (x >= 1){
        double yn = 1.0; //variable for y power to i, y "is" (x-1)/x, so y power to i is ((x-1)/x) power to n
        double sum = 0.0; //sum of gradually steps
        for (unsigned int i = 1; i <= n; i++){
            yn *= ((x - 1)/x);   //"maiking" y power to i
            sum += (yn/i);   //increasing sum of next part of algorithm
        }
        return sum;
    }
    else if (x == 0){
        return INFINITY;
    }
    else{
        fprintf(stderr, "Number must be higher than 0.\n"); //for sure
        return -1;
    }
}

//function fa - choosig between i power to i multiple z power to z and 2 multiple z
//for cfrac_log function
double fa(double i, double z){
    i--;
    if(i == 0)
        return 2.0 * z;
    else
        return i*i * z*z;
}

double cfrac_log(double x, unsigned int n){
    if(x == INFINITY)
        return INFINITY;
    if (x == 0){
        return -INFINITY;
    }
    double z = (x - 1.0)/(x + 1.0); //auxiliary variable - simplification for more readable code
    double sum = 0.0; //sum of gradually steps
    for (unsigned int i = n; i > 0; i--){
        sum = fa(i, z)/ ((2*i - 1) - sum);   //increasing sum of next part of algorithm
    }

    return sum;
}

double taylor_pow(double x, double y, unsigned int n){
     //renaming constants - in algorithm is entered 'a' powered to 'x', but pow returns 'x' power to 'y'
    if (x == 0)
        return 0;
    double a = x;
    x = y;

    double an = 1.0; //variable for a power to n
    double lnn = 1.0; //variable for ln(a) power to n
    double fact = 1; //variable for counting factorial
    double sum = 00.0;    //sum of gradually steps

    for(unsigned int i = 1; i <= n; i++){
        sum += (an * lnn)/fact;   //increasing sum of next part of algorithm
        an *= x;    //"maiking" a power to n
        fact *= i; //variable for counting factorial
        lnn *= taylor_log(a, n); //"maiking" ln(a) power to n
    }
    return sum;
}

double taylorcf_pow(double x, double y, unsigned int n){
    if (x == 0)
        return 0;
    //renaming constants - in algorithm is entered 'a' powered to 'x', but pow returns 'x' power to 'y'
    double a = x;
    x = y;

    double an = 1.0; //variable for a power to n
    double lnn = 1.0; //variable for ln(y) power to n
    double fact = 1; //variable for counting factorial
    double sum = 0.0;   //sum of gradually steps

    for(unsigned int i = 1; i <= n; i++){
        sum += (an * lnn)/fact;   //increasing sum of next part of algorithm
        an *= x;  //"maiking" a power to n
        fact *= i;  //"maiking" factorial n!
        lnn *= cfrac_log(a, n);  //"maiking" ln(a) power to n
    }
    return sum;
}

int main(int argc, char* argv[]){
    if(argc == 4){ //was 3 arguments given?
        if (strstr(argv[1], "--log") == NULL) //is first argument '--log'?
            fprintf(stderr, "Wrong argument.\nUse >>./proj2 --log x n<< for calculation the logarithm of x (n is polynomial repetition count). \nUse >>./proj2 --pow x y n<< for calculation the exponential equation x power to y (n is polynomial repetition count).\n\n");       
        double x;
        if(!try_input_to_num_double(argv[2], &x, 1))
            return 0;
        unsigned int n;
        if(!try_input_to_num_int(argv[3], &n))
            return 0;

        double test_log;
        test_log = log(x);
        printf("Logarithm: %.12g\n", test_log);
        printf("cfrac_log(%.12g) = %.12g\n", x, cfrac_log(x, n));
        printf("taylor_log(%.12g) = %.12g\n", x, taylor_log(x, n));    
    }
    else if(argc == 5){
        if (strstr(argv[1], "--pow") == NULL)
            fprintf(stderr, "Wrong argument.\nUse >>./proj2 --log x n<< for calculation the logarithm of x (n is polynomial repetition count). \nUse >>./proj2 --pow x y n<< for calculation the exponential equation x power to y (n is polynomial repetition count).\n\n")  ;       
        
        double x;
        if(!try_input_to_num_double(argv[2], &x, 1))
            return 0;
        double y;
        if(!try_input_to_num_double(argv[3], &y, 2))
            return 0;
        unsigned int n;
        if(!try_input_to_num_int(argv[4], &n))
            return 0;

        double test_exp;
        test_exp = pow(x, y);
        printf("pow: %.12g\n", test_exp);
        printf("taylor_pow(%.12g, %.12g) = %.12g\n", x, y, taylor_pow(x, y, n));
        printf("taylorcf_pow(%.12g, %.12g) = %.12g\n", x, y, taylorcf_pow(x, y, n));
    }
    else
        fprintf(stderr, "Wrong argument.\nUse >>./proj2 --log x n<< for calculation the logarithm of x (n is polynomial repetition count). \nUse >>./proj2 --pow x y n<< for calculation the exponential equation x power to y (n is polynomial repetition count).\n\n")  ;       
    
    return 1;
}

