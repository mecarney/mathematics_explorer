/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extras.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 06:58:57 by mcarney           #+#    #+#             */
/*   Updated: 2018/08/10 06:58:58 by mcarney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		key_press_hook(int keycode, t_ftl *ftl)
{
	(keycode == 78 && ftl->color * 2 > 10) ? ftl->color /= 2 : 0;
	(keycode == 69 && ftl->color * 2 < 0x00FFFFFF) ? ftl->color *= 2 : 0;
	(keycode == 49) ? ftl_defaults(ftl, ftl->a) : 0;
	(keycode == 123) ? ftl->x_slide -= 1 / ftl->zoom : 0;
	(keycode == 124) ? ftl->x_slide += 1 / ftl->zoom : 0;
	(keycode == 126) ? ftl->y_slide -= 1 / ftl->zoom : 0;
	(keycode == 125) ? ftl->y_slide += 1 / ftl->zoom : 0;
	(keycode == 18) ? ftl->rp += .001 : 0;
	(keycode == 19) ? ftl->rp -= .001 : 0;
	(keycode == 20) ? ftl->ip -= .001 : 0;
	(keycode == 21) ? ftl->ip += .001 : 0;
	(keycode == 43) ? ftl->heads -= 1 : 0;
	(keycode == 47) ? ftl->heads += 1 : 0;
	(keycode == 46) ? ftl_defaults(ftl, 0) : 0;
	(keycode == 38) ? ftl_defaults(ftl, 1) : 0;
	(keycode == 17) ? ftl_defaults(ftl, 2) : 0;
	(keycode == 11) ? ftl_defaults(ftl, 3) : 0;
	if (keycode == 53)
	{
		mlx_destroy_image(ftl->mlx, ftl->img);
		mlx_destroy_window(ftl->mlx, ftl->win);
		exit(EXIT_SUCCESS);
	}
	display(ftl, ftl->a);
	return (0);
}

int		deal_mouse(int button, int x, int y, t_ftl *ftl)
{
	if (x || y)
	{
		if (button == 4 && ftl->zoom < 100000)
			ftl->zoom *= 2;
		else if (button == 5 && ftl->zoom > 2)
			ftl->zoom /= 2;
		mlx_destroy_image(ftl->mlx, ftl->img);
		display(ftl, ftl->a);
	}
	return (0);
}

int		ft_motion(int x, int y, t_ftl *ftl)
{
	if (x >= 0 && x <= ftl->max - 200 && y >= 0 && y <= ftl->max - 200)
	{
		ftl->rp = x * -.001;
		ftl->ip = y * -.001;
	}
	display(ftl, ftl->a);
	return (0);
}

void	decorate_win(void *a, void *b, int c)
{
	mlx_string_put(a, b, c + 26, 420, 0x00FFFFFF, "(M)andelbrot");
	mlx_string_put(a, b, c + 49, 460, 0x00FFFFFF, "(J)ulia");
	mlx_string_put(a, b, c + 42, 500, 0x00FFFFFF, "(T)ricorn");
	mlx_string_put(a, b, c + 17, 540, 0x00FFFFFF, "(B)urning Ship");
	mlx_string_put(a, b, 75, c + 47, 0x00FFFFFF, "Color Change");
	mlx_string_put(a, b, 115, c + 67, 0x00FFFFFF, "+, -");
	mlx_string_put(a, b, 375, c + 20, 0x00FFFFFF, "Quit");
	mlx_string_put(a, b, 379, c + 40, 0x00FFFFFF, "Esc");
	mlx_string_put(a, b, 304, c + 75, 0x00FFFFFF, "Julia Alterations");
	mlx_string_put(a, b, 275, c + 95, 0x00FFFFFF, "Mouse Location, 1, 2, 3, 4");
	mlx_string_put(a, b, 623, c + 47, 0x00FFFFFF, "Slide");
	mlx_string_put(a, b, 596, c + 67, 0x00FFFFFF, "Arrow Keys");
	mlx_string_put(a, b, 823, c + 20, 0x00FFFFFF, "Reset");
	mlx_string_put(a, b, 808, c + 40, 0x00FFFFFF, "Spacebar");
	mlx_string_put(a, b, 825, c + 75, 0x00FFFFFF, "Zoom");
	mlx_string_put(a, b, 800, c + 95, 0x00FFFFFF, "Trackball");
	mlx_string_put(a, b, 970, c + 47, 0x00FFFFFF, "Fractal Parade");
	mlx_string_put(a, b, 1020, c + 67, 0x00FFFFFF, ">, <");
}
