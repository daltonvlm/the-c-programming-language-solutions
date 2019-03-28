#include <stdio.h>
#include <string.h>
#include "dcl.h"

main()	/* convert declaration to words */
{
	while (gettoken() != EOF) {		/* 1st token on line */
		*out = *name = *datatype = '\0';
		strcpy(datatype, token);	/* is the datatype */
		dcl();		/* parse rest of line */
		if (tokentype != '\n')
			printf("syntax error\n");
		printf("%s: %s %s\n", name, out, datatype);
	}
	return 0;
}

/* dcl: parse a declarator */
void dcl(void)
{
	int ns;
	for (ns = 0; gettoken() == '*'; )	/* count *'s */
		ns++;

	dirdcl();
	while (ns--)
		strcat(out, " pointer to");
}

/* dirdcl: parse a direct declator */
void dirdcl(void)
{
	int type;

	if (tokentype == '(') {			/* ( dcl ) */
		dcl();
		if (tokentype != ')')
			printf("error: missing )\n");
	} else if (tokentype == NAME)	/* variable name */
		strcpy(name, token);
	else
		printf("error: expected name or (dcl)\n");
	while ((type=gettoken()) == PARENS || type == BRACKETS)
		if (type == PARENS) {
			strcat(out, " function");
			strcat(out, token);
			strcat(out, " returning");
		} else {
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
}
