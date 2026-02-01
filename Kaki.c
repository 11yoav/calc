#include <stdio.h>
#include <math.h>



typedef struct {
    int left_operand, middle_operand, right_operand;
    char first_operator, second_operator;
    int tokens_read;
} Input;

typedef enum {
    PRIORITY_SAME = 1,   
    PRIORITY_LEFT = 2,   
    PRIORITY_RIGHT = 3   
} EPriority;



Input GetInput(){
    Input user_input  = {0};  

    user_input.tokens_read = scanf("%d %c %d", &user_input.left_operand, &user_input.first_operator, &user_input.middle_operand);
    if (user_input.tokens_read != 3) return user_input;

    char c = getchar(); 
    if (c != '\n' && c != EOF) {
            ungetc(c, stdin); 
            int secondary_tokens_read = scanf(" %c %d", &user_input.second_operator, &user_input.right_operand);
            if (secondary_tokens_read == 2) user_input.tokens_read = 5;
        }
    return user_input;}



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




EPriority CheckPriority(char first_operator, char second_operator) {
    int val1 = 1;
    int val2 = 1;

    if (first_operator == '*' || first_operator == '/') val1 = 2;
    if (second_operator == '*' || second_operator == '/') val2 = 2;

    if (val1 == val2) return PRIORITY_SAME;
    
    else if (val1 > val2) return PRIORITY_LEFT; 
    
    else return PRIORITY_RIGHT;
    
}


double FinalCalc(Input data, int *err) {
    double inter_result;
    int short_intake = 3;
    
    if (data.tokens_read == short_intake) return CalcFor2(data.left_operand, data.middle_operand, data.first_operator, err);
    
    EPriority order = CheckPriority(data.first_operator, data.second_operator);
    
    if (order == PRIORITY_SAME || order == PRIORITY_LEFT) {   
        inter_result = CalcFor2(data.left_operand, data.middle_operand, data.first_operator, err);
        if (*err) return 0;
        return CalcFor2(inter_result, data.right_operand, data.second_operator, err);}
    
    else {
        inter_result = CalcFor2(data.middle_operand, data.right_operand, data.second_operator, err);
        if (*err) return 0;
        return CalcFor2(data.left_operand, inter_result, data.first_operator, err);}
    }



int main() {
    int err = 0; 
    Input myData = GetInput();
    if (myData.tokens_read < 3)  return 1;
    double finale_result = FinalCalc(myData, &err);
    if (err) return 1;
    printf("Result: %d\n", (int)round(finale_result));
    return 0;
}   