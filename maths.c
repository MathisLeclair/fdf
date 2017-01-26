#include <math.h>

int		norme(int *V, int *W)
{
	return (sqrt((V[0] - W[0]) * (V[0] - W[0]) + (V[1] - W[1]) * (V[1] - W[1]) + (V[2] - W[2]) * (V[2] - W[2])));
}

int		scal_3d(int *V, int *W)
{
	return (V[0] * W[0] + V[1] * W[1] + V[2] * W[2]);
}
