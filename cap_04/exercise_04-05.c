/*
 * Add access to library functions like sin, exp, and pow. See <math.h> in
 * Appendix B, Section 4.
 */

#include <stdio.h>
#include <stdlib.h>		/* for atof() */
#include <math.h>
#include <string.h>

#define MAXOP	100		/* max size of operand or operator */
#define NUMBER 	'0'		/* signal that a number was found */
#define FUNC	'f'

int getop(char [], int);
void push(double);
double pop(void);
void callmath(char []);

/* reverse Polish calculator */
main()
{
	int type;
	double op2;
	char s[MAXOP];

	while ((type = getop(s, MAXOP)) != EOF) {
		switch (type) {
			case NUMBER:
				push(atof(s));
				break;
			case FUNC:
				callmath(s);
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
				if (op2 != 0)
					push(pop() / op2);
				else
					printf("error: zero divisor\n");
				break;
			case '\n':
				printf("\t%.8g\n", pop());
				break;
			default:
				printf("error: unknown command %s\n", s);
				break;
		}
	}
	return 0;
}

#define MAXVAL	100		/* maximum depth of val stack */

int sp = 0;				/* next free stack position */
double val[MAXVAL];		/* value stack */

/* push: push f onto value stack */
void push(double f)
{
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
	if (sp > 0)
		return val[--sp];
	else {
		printf("error: stack empty\n");
		return 0.0;
	}
}

#include <ctype.h>

int getch(void);
void ungetch(int);

/* getop: get next operator or numeric operand */
int getop(char s[], int len)
{
	int i, c;

	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';
	if (islower(c)) {
		for (i=1; i < len-1 && islower(s[i] = c = getch()); i++)
			;
		s[i] = '\0';
		ungetch(c);
		return i > 1 ? FUNC : s[0];
	}
	if (!isdigit(c) && c != '.')
		return c;	  	/* not a number */
	i = 0;
	if (isdigit(c))		/* collect integer part */
		while (isdigit(s[++i] = c = getch()) && i < len - 1)
			;
	if (i < len - 1 && c == '.')		/* collect fraction part */
		while (isdigit(s[++i] = c = getch()) && i < len - 1)
			;
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}

void callmath(char s[])
{
	double op2;

	if (0 == strcmp(s, "sin"))
		push(sin(pop()));
	else if (0 == strcmp(s, "exp"))
		push(exp(pop()));
	else if (0 == strcmp(s, "pow")) {
		op2 = pop();
		push(pow(pop(), op2));
	} else {
		printf("error: unknown expression '%s'\n", s);
	}
}

#define BUFSIZE	100

char buf[BUFSIZE];	/* buffer for ungetch */
int bufp = 0;		/* next free position in buf */

int getch(void)	/* get a (possibly pushed back) character */
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}
