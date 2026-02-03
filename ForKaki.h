#ifndef Kaki_H
#define Kaki_H

#define CALC_SUCCESS 0
#define CALC_ERROR 1
#define CALC_RETURN_VAL 0.0

typedef struct {
    int left_operand, middle_operand, right_operand;
    char first_operator, second_operator;
    int tokens_read;
} Input;

typedef enum {
    PRECEDENCE_EQUAL = 1,   
    PRECEDENCE_LEFT_FIRST = 2,   
    PRECEDENCE_RIGHT_FIRST = 3   
} Priority;

typedef enum {
    INTAKE_ERROR = 0,
    INTAKE_SINGLE_OPERATOR = 3, 
    INTAKE_DOUBLE_OPERATOR = 5  
} IntakeStatus;

#endif