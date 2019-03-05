/*
 * Write the program expr, which evaluates a reverse Polish expression from the command
 * line, where each operator or operand is a separate argument. For example,
 *
 *      expr 2 3 4 + *
 * 
 * evaluates  2 x (3 + 4).
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define NUMBER 0

void push(double);
double pop(void);
int getop(char *arg);

main(int argc, char *argv[])
{
    double op2;
    int type;

    while (--argc > 0)
        switch (type = getop(*++argv)) {
            case NUMBER:
                push(atof(*argv));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (0 == op2) {
                    printf("expr: invalid expression (division by 0)\n");
                    return -1;
                }
                push(pop() / op2);
                break;
            default:
                printf("expr: invalid operand %s\n", *argv);
                return -1;
        }
    printf("%g\n", pop());
    return 0;
}

int getop(char *arg)
{
    if (('+' == *arg || '-' == *arg || '*' == *arg || '/' == *arg) && '\0' == *(arg+1))
        return *arg;
    if ('+' == *arg || '-' == *arg) {
        while (isdigit(*++arg))
            ;
        return '\0' == *arg ? NUMBER : -1;
    }
    if (isdigit(*arg)) {
        while (isdigit(*++arg))
            ;
        return '\0' == *arg ? NUMBER : -1;
    }
    return -1;
}
