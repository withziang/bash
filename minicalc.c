#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>



//Error 
// addition: 3 argus, one symbal, 2 ints
// gcd: atleast 2, one symbal, ints
// sqrt: 2, one symbal, one double
// anagram: 3, one symbal, two string

// error case:
//  no argument => 1
//  not following operation => 2
//  number does not match => 3
//  wrong type => 4
//  sqrt neg => 5
//  lowercase => 6
//  gcd neg or zero => 7

// some function

bool strcomp(char* str1, char* str2){
    if (strlen(str1) != strlen(str2))
        return false;
    for (int i = 0; i < strlen(str1); i++)
        if (str1[i] != str2[i])
            return false;
    return true;
    }
    


long int gcd(long int a, long int b){
    //euclidean? algorithm
    if (b ==0)return a;
    return gcd(b, a%b);
}
int comp(const void *a, const void *b){
    return (*(char *)a - *(char *)b);
}
// main function
int main(int argc, char *argv[]){
    // error case 1
    if ( argc < 2 ){
        fputs("Error: atleast one arugment needed\n", stderr);
        return 1;
    }   
        
    // the first argument
    char* op = argv[1];
    
    if ( strcomp(op, "+")){
           //addition
        //check if there is 3 arguments
        if (argc != 4){
            fputs("Error: three arguments needed for plus\n",stderr);
            return 3;
        }
        //check if the arguments are int
        char* end1, *end2, *str1 = argv[2], *str2 = argv[3];
        long int num1 = strtol(str1, &end1, 10), num2 = strtol(str2, &end2, 10);

        if (*end1 != '\0' || *end2 != '\0' ){
            fputs("Error, two ints are expected\n", stderr);
            return 4;
            }
        //final calculation
        printf("%ld\n", num1+num2);

    }else if( strcomp(op, "gcd")){
           //gcd
           //check if there is atleast 2 arguments
           if (argc < 3){
            fputs("Error: at least 2 arguments needed for gcd\n",stderr);
            return 3;
        }
        //check if the int(s) are int and calculation
        char* end,*str1 = argv[2];
        long int res = strtol(str1, &end,10);
        if (*end != '\0'){
            fputs("Error: the arguments have to be all int\n", stderr);
            return 4;
            }
        if (res <= 0){
            fputs("Error: all int has to be greater than 0\n", stderr);
            return 7;
            }
        for (int i = 3; i< argc;i++){
            str1 = argv[i];
            long int temp = strtol(str1, &end, 10);
            
            if (*end != '\0'){
                fputs("Error: the arguments have to be all int\n", stderr);
                return 4;
                }
            if (temp <= 0){
                fputs("Error: all int has to be greater than 0\n", stderr);
                return 7;
            }
            res = gcd(res,temp);
        }
        //final output
        printf("%ld\n", res);
    }else if( strcomp(op, "sqrt")){
        // sqrt
        // check if there is 2 arguments
        if (argc != 3){
            fputs("Error: two arguments needed for sqrt\n",stderr);
            return 3;
        }
        char* end, *str1 = argv[2];
        double d = strtod(str1, &end);
        if (*end != '\0'){
            fputs("Error: the argument needs to be double\n", stderr);
            return 4;
        }
        if (d < 0.0){
            fputs("Error: the argument must be positive or zero\n", stderr);
            return 5;
        }
        //final output
        printf("%f\n", sqrt(d));
    }else if( strcomp(op, "anagram")){
        //anagram
        // check if there is 3 arguments
        if (argc != 4){
            fputs("Error: three arguments needed for anagram\n",stderr);
            return 3;
        }
        char *firststring = strdup(argv[2]), *secondstring = strdup(argv[3]); // deep copy
        //check if they are all small case
        for (int i = 0; i< strlen(firststring);i++){
            if (!islower(firststring[i])){
                fputs("Error: the string has to be small case only\n", stderr);
                return 6;
            }
        }   
        for (int i = 0; i< strlen(secondstring);i++){
            if (!islower(secondstring[i])){
                fputs("Error: the string has to be small case only\n", stderr);
                return 6;
            }
        }
        qsort(firststring, strlen(firststring), sizeof(char), comp);
        qsort(secondstring, strlen(secondstring), sizeof(char), comp);

        if (!strcmp(firststring, secondstring))
            printf("true\n");
        else    printf("false\n"); 
    }else{
        // error
        fputs("Error: only select from the following operator <+> <gcd> <sqrt> <anagram>\n",stderr);
        return 2;
    }   
    

    return 0;
}














