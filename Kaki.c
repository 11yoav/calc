#include <stdio.h>
#include <math.h>

typedef struct {
    int num1, num2, num3;
    char op1, op2;
    int intake;
} input;

input GetInput(){
    input ui  = {0};  

    ui.intake = scanf("%d %c %d", &ui.num1, &ui.op1, &ui.num2);
    if (ui.intake != 3) return ui;

    char c = getchar(); 
    if (c != '\n' && c != EOF) {
            ungetc(c, stdin); 
            int intake2 = scanf(" %c %d", &ui.op2, &ui.num3);
            if (intake2 == 2) ui.intake = 5;
        }
    return ui;}

double calc(double a, double b, char op, int *err){   
    *err = 0;
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;   
    case '/': if (b == 0) {
        printf("no dividing by 0 ERROR! ");
        *err = 1;
        return 0;}
            
        return a / b;
    default: printf("Bad op!"); 
        *err = 1;
        return 0;}}

int check(char op1, char op2) {
    int val1 = 0;
    int val2 = 0;

    if (op1 == '+' || op1 == '-') val1 = 1;
    if (op2 == '+' || op2 == '-') val2 = 1;
    if (op1 == '/' || op1 == '*') val1 = 2;
    if (op2 == '/' || op2 == '*') val2 = 2;
    if (val1 == 0 || val2 == 0) return 0;
    if (val1 == val2) return 1;
    if (val1 > val2) return 2;
    
    else {return 3;}}

double Final_Calc(input data, int *err) {
    double res;
    
    if (data.intake == 3) return calc(data.num1, data.num2, data.op1, err);
    
    int temp = check(data.op1, data.op2);
    
    if (temp == 1 || temp == 2) {   
        res = calc(data.num1, data.num2, data.op1, err);
        if (*err) return 0;
        return calc(res, data.num3, data.op2, err);}
    
    else {
        res = calc(data.num2, data.num3, data.op2, err);
        if (*err) return 0;
        return calc(data.num1, res, data.op1, err);}}



int main() {
    int err = 0; 
    input myData = GetInput();
    if (myData.intake < 3)  return 1;
    double Fres = Final_Calc(myData, &err);
    if (err) return 1;
    printf("Result: %d\n", (int)round(Fres));
    return 0;
}   