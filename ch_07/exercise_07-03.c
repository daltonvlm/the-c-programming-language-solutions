/*
 * Revise minprintf to handle more of the other facilities of printf.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

#define FMT_LEN 81

struct fields {
	char sign;
	int width;
	int period;
	int precision;
	char type;
};

static int is_conv_char(char);
static int is_fields_valid(struct fields *, char);
static int is_numeric(char);
static int is_integer(char);
static void set_formatter(char *, struct fields *, char);
static void init_fields(struct fields *);

/* minprintf: minimal printf with variable argument list */
void minprintf(char *fmt, ...)
{
	va_list ap;		/* points to each unnamed arg in turn */
	char *p, *sval, formatter[FMT_LEN];
	int i, s_len, s_pad, parse;
	struct fields flds;

	va_start(ap, fmt);	/* make ap point to 1st unnamed arg */
	for (p = fmt; *p; p++) {
		if (*p != '%') {
			putchar(*p);
			continue;
		}
		init_fields(&flds);
		parse = 1;
		while (parse && *++p && !is_conv_char(*p)) {
			switch (*p) {
				case '-':
				case '+':
					flds.sign = *p;
					break;
				case '.':
					flds.period = 1;
					flds.precision = 0;
					break;
				case 'h':
				case 'l':
					flds.type = *p;
					break;
				default:
					if (isdigit(*p)) {
						if (flds.period)
							flds.precision = atoi(p);
						else
							flds.width = atoi(p);
						while (isdigit(*++p))
							;
						p--;
					} else {
						printf("'%c' is not a valid field\n", *p);
						parse = 0;
					}
					break;
			}
		}
		if (!is_conv_char(*p) || !is_fields_valid(&flds, *p)) {
			printf("minprintf: error parsing '%s'\n", fmt);
			break;
		}
		if ('s' == *p) {
			sval = va_arg(ap, char *);
			s_len = strlen(sval);
			s_pad = flds.width - s_len;

			if (flds.precision < 0 || flds.precision > s_len)
				flds.precision = s_len;
			if ('-' == flds.sign)
				for (i = 0; i < flds.precision; i++)
					putchar(*sval++);
			for (i = 0; i < s_pad; i++)
				putchar(' ');
			if (flds.sign != '-')	/* it saves lines of code, even seeming redundant */
				for (i = 0; i < flds.precision; i++)
					putchar(*sval++);
		} else if ('%' == *p)
			putchar(*p);
		else {
			set_formatter(formatter, &flds, *p);
			if (is_numeric(*p)) {
				if (is_integer(*p)) {
					if ('l' == flds.type)
						printf(formatter, va_arg(ap, long));
					else
						printf(formatter, va_arg(ap, int));
				} else
					printf(formatter, va_arg(ap, double));
			} else if ('p' == *p)
				printf(formatter, va_arg(ap, void *));
		}
	}
	va_end(ap);		/* clean up when done */
}

static const char *conv_chars = "dioxXucsfeEgGp%";

static int is_conv_char(char c)
{
	const char *p = conv_chars;

	while (*p)
		if (c == *p++)
			return 1;
	return 0;
}

static int is_numeric(char c)
{
	return !('%' == c || 's' == c || 'p' == c);
}

static int is_integer(char c)
{
	return 'd' == c || 'i' == c || 'o' == c || 'x' == c || 'X' == c || 'u' == c;
}

static int is_fields_valid(struct fields *p, char c)
{
	if ('+' == p->sign && !is_numeric(c))
		return 0;
	if (('h' == p->type || 'l' == p->type) && !is_integer(c))
		return 0;
	if (p->period && !is_numeric(c) && 's' != c)
		return 0;
	if ('%' == c && (p->sign || p->width != -1 || p->period || p->precision != -1))
		return 0;
	return 1;
}

static void set_formatter(char *fmt, struct fields *p, char c)
{
	char tmp[FMT_LEN] = "";

	sprintf(fmt, "%%%c", p->sign);
	if (p->width != -1) {
		sprintf(tmp, "%d", p->width);
		strcat(fmt, tmp);
	}
	if (p->period)
		strcat(fmt, ".");
	if (p->precision != -1) {
		sprintf(tmp, "%d", p->precision);
		strcat(fmt, tmp);
	}
	if (p->type) {
		sprintf(tmp, "%c", p->type);
		strcat(fmt, tmp);
	}
	sprintf(tmp, "%c", c);
	strcat(fmt, tmp);
}

static void init_fields(struct fields *p)
{
	p->sign = '\0';
	p->width = -1;
	p->period = 0;
	p->precision = -1;
	p->type = '\0';
}
