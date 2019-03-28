#ifndef DCL_H
#define DCL_H

#define MAXTOKEN	100

enum { NAME, PARENS, BRACKETS };

int gettoken(void);
int tokentype;				/* type of last token */
char token[MAXTOKEN];		/* last token string */
char name[MAXTOKEN];		/* identifier name */
char datatype[MAXTOKEN];	/* data type = char, int, etc. */
char out[1000];				/* output string */

void dcl(void);
void dirdcl(void);
int gettoken(void);

#endif
