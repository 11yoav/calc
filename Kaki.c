#include <stdio.h>
#include <math.h>


double calc(double a, double b, char op, int *err){   
    double result;
     *err = 0;

    if (op == '+'){     
            result = a + b ;}
        
    else if (op == '-'){
            result = a - b;}
        
    else if (op == '*'){ 
            result = a * b;}
        
    else if (op == '/'){
        if (b == 0) {
                printf("no dividing by 0 ERROR! ");
                *err = 1;
                return 0;  }
        else{
           result = (double)a / b;}
        }  
        
        
else  {
            printf("Bad op!");
            *err = 1;
            return 0;}
    
    return result;
}


int check(char op1, char op2) {
    int val1 = 0;
    int val2 = 0;

    if (op1 == '+' || op1 == '-') {
        val1 = 1;
    }
    if (op2 == '+' || op2 == '-') {
        val2 = 1;
    }
    if (op1 == '/' || op1 == '*') {
        val1 = 2;
    }
    if (op2 == '/' || op2 == '*') {
        val2 = 2;
    }

    if (val1 == 0 || val2 == 0) return 0;
    
    if (val1 == val2) {
        return 1;
    }

    if (val1 > val2) {
        return 2;
    } else {
        return 3;
    }
}



int main() {
    int num1;    int num2;    int num3;
    char op1;    char op2;
    double res;      double Fres; int err = 0;
   
int intake = scanf("%d %c %d", &num1, &op1, &num2);
if (intake != 3) return 1;

int intake2 = 0;
char c = getchar(); 
    if (c != '\n' && c != EOF) {
        ungetc(c, stdin); 
        intake2 = scanf(" %c %d", &op2, &num3);
    }

if (intake2 == 2) {
        int temp = check(op1, op2);

        if (temp == 1 || temp == 2) {   
            res = calc(num1, num2, op1, &err);
            if (err) return 1;

            Fres = calc(res, num3, op2, &err);
            if (err) return 1;
        } 
        
        else {                          
            res = calc(num2, num3, op2, &err);
            if (err) return 1;
            Fres = calc(num1, res, op1, &err);
            if (err) return 1;
        }
}    

else {
        Fres = calc(num1, num2, op1, &err);
            if (err) return 1;    }
        

   
printf("Result: %d\n", (int)round(Fres));
return 0;


}



