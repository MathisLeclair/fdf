// #include "fdf.h"
#include <stdlib.h>
#include <stdio.h>

int		trace_line(int x, int y, int a, int b)
{
	return(a * (y - b) / (x - a) + (b * x - a * y) / (x - a));
	// ft_pixel(i * (x - a) / (y - b) - (b * x - a * y) / (y - b), i);
}

int		main()
{
	printf("truc = %d\n", trace_line(100, 100, 200, 300));
}