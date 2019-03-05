/*
 * Add commands for handling variables. (It's easy to provide twenty-six variables
 * with single-letter names.) Add a variable for the most recently printed value.
 */

#include <stdio.h>
#include <stdlib.h>		/* for atof() */

#define MAXOP	100		/* max size of operand or operator */
#define NUMBER 	'0'		/* signal that a number was found */

int getop(char [], int);
void push(double);
double pop(void);

/* reverse Polish calculator */
main()
{
	int type, i, var;
	double op2, _, vars['Z' - 'A' + 1];
	char s[MAXOP];

	for (i = 0; i < 'Z' - 'A' + 1; i++)
		vars[i] = 0;

	var = EOF;
	while ((type = getop(s, MAXOP)) != EOF) {
		switch (type) {
			case NUMBER:
				push(atof(s));
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
			case '_':
				push(_);
				break;
			case ':':
				if (var >= 'A' && var <= 'Z') {
					pop();
					vars[var - 'A'] = pop();
				} else
					printf("error: no variable '%c'\n", var);
				break;
			case '\n':
				_ = pop();
				printf("\t%.8g\n", _);
				break;
			default:
				var = type;
				if (type >= 'A' && type <= 'Z') {
					push(vars[type - 'A']);
				} else
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
