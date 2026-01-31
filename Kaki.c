#include <stdio.h>
#include <math.h>



typedef struct {
    int num1, num2, num3;
    char op1, op2;
    int intake;
} Input;

typedef enum {
    PRIORITY_SAME = 1,   
    PRIORITY_LEFT = 2,   
    PRIORITY_RIGHT = 3   
} EPriority;



Input GetInput(){
    Input ui  = {0};  

    ui.intake = scanf("%d %c %d", &ui.num1, &ui.op1, &ui.num2);
    if (ui.intake != 3) return ui;

    char c = getchar(); 
    if (c != '\n' && c != EOF) {
            ungetc(c, stdin); 
            int intake2 = scanf(" %c %d", &ui.op2, &ui.num3);
            if (intake2 == 2) ui.intake = 5;
        }
    return ui;}



double CalcFor2(double a, double b, char op, int *err){   
    *err = 0;
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;   
    case '/': if (b == 0) {
        fprintf(stderr, "Error: no division by zero!\n");
        *err = 1;
        return 0;}
            
        return a / b;
    default: fprintf(stderr, "Error: '%c' is an invalid operator\n", op);
        *err = 1;
        return 0;}
    }




EPriority CheckPriority(char op1, char op2) {
    int val1 = 1;
    int val2 = 1;

    if (op1 == '*' || op1 == '/') val1 = 2;
    if (op2 == '*' || op2 == '/') val2 = 2;

    if (val1 == val2) return PRIORITY_SAME;
    
    else if (val1 > val2) return PRIORITY_LEFT; 
    
    else return PRIORITY_RIGHT;
    
}


double FinalCalc(Input data, int *err) {
    double res;
    int short_intake = 3;
    
    if (data.intake == short_intake) return CalcFor2(data.num1, data.num2, data.op1, err);
    
    EPriority order = CheckPriority(data.op1, data.op2);
    
    if (order == PRIORITY_SAME || order == PRIORITY_LEFT) {   
        res = CalcFor2(data.num1, data.num2, data.op1, err);
        if (*err) return 0;
        return CalcFor2(res, data.num3, data.op2, err);}
    
    else {
        res = CalcFor2(data.num2, data.num3, data.op2, err);
        if (*err) return 0;
        return CalcFor2(data.num1, res, data.op1, err);}
    }



int main() {
    int err = 0; 
    Input myData = GetInput();
    if (myData.intake < 3)  return 1;
    double Fres = FinalCalc(myData, &err);
    if (err) return 1;
    printf("Result: %d\n", (int)round(Fres));
    return 0;
}   