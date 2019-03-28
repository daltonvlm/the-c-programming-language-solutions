/*
 * Define a macro swap(t,x,y) that interchanges two arguments of type
 * t. (Block structure will help).
 */

#define swap(t, x, y) 	\
{						\
	t tmp = x;			\
	x = y;				\
	y = tmp;			\
}
