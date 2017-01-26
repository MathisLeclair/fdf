#include "fdf.h"

void	draw_line(int x, int y, int a, int b, void *win, void *mlx)
{
	float i;

	if (abs(x - a) >= abs(y - b))
	{
		i = x <= a ? x - 1 : a - 1;
		while (++i <= (x <= a ? a : x))
			mlx_pixel_put(mlx, win, i, i * (y - b) / (x - a) + (b * x - a * y) / (x - a), 0255255000);
	}
	else
	{
		i = y <= b ? y - 1 : b - 1;
		while (++i <= (y <= b ? b : y))
			mlx_pixel_put(mlx, win, i * (x - a) / (y - b) - (b * x - a * y) / (y - b), i, 0255255000);
	}
}

int main(void)
{

	void *mlx;
	void *win;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 1280, 720, "test");
	draw_line(10,10,40,20,win, mlx);
	draw_line(40,20,40,50,win, mlx);
	draw_line(40,50,10,40,win, mlx);
	draw_line(10,40,10,10,win, mlx);
	mlx_loop(mlx);
}
