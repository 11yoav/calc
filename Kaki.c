#include <stdio.h>
#include <math.h>
#include "ForKaki.h"

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



double CalcFor2Num(double left_operand, double right_operand, char operator, int *err){   
    *err = CALC_SUCCESS;
    switch (operator) {
    case '+': return left_operand + right_operand;
    case '-': return left_operand - right_operand;
    case '*': return left_operand * right_operand;   
    case '/': if (right_operand == 0) {
        fprintf(stderr, "Error: no division by zero!\n");
       *err = CALC_ERROR;
        return CALC_RETURN_VAL;}
            
        return left_operand / right_operand;
    default: fprintf(stderr, "Error: '%c' is an invalid operator\n", operator);
        *err = CALC_ERROR;
        return CALC_RETURN_VAL;
    }}




Priority CheckPriority(char first_operator, char second_operator) {
    int val1 = (first_operator == '*' || first_operator == '/') ? 2 : 1;
    int val2 = (second_operator == '*' || second_operator == '/') ? 2 : 1;

    if (val1 == val2) return PRECEDENCE_EQUAL;
    return (val1 > val2) ? PRECEDENCE_LEFT_FIRST : PRECEDENCE_RIGHT_FIRST;
}


double FinalCalc(Input data, int *err) {
    double inter_result;
    
    if (data.tokens_read == INTAKE_SINGLE_OPERATOR) return CalcFor2Num(data.left_operand, data.middle_operand, data.first_operator, err);
    
    Priority order = CheckPriority(data.first_operator, data.second_operator);
    
    if (order == PRECEDENCE_EQUAL || order == PRECEDENCE_LEFT_FIRST) {   
        inter_result = CalcFor2Num(data.left_operand, data.middle_operand, data.first_operator, err);
        if (*err == CALC_ERROR) return CALC_RETURN_VAL;
        return CalcFor2Num(inter_result, data.right_operand, data.second_operator, err);}
    
    else {
        inter_result = CalcFor2Num(data.middle_operand, data.right_operand, data.second_operator, err);
        if (*err == CALC_ERROR) return CALC_RETURN_VAL;
        return CalcFor2Num(data.left_operand, inter_result, data.first_operator, err);}
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