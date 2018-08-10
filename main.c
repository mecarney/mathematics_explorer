/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 06:59:04 by mcarney           #+#    #+#             */
/*   Updated: 2018/08/10 06:59:05 by mcarney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			*work(void *arguments)
{
	t_arg		*args;
	int			x;

	args = arguments;
	while (++args->start < args->end)
	{
		x = -1;
		while (++x < args->ftl->max)
			(args->func)(args->m, args->ftl, x, args->start);
	}
	return (NULL);
}

void			fill_arg(t_arg *arg, int start, t_ftl *ftl, int a)
{
	t_equ		m;
	void		(*p[4])(t_equ, t_ftl *, int, int);

	p[0] = m_equation;
	p[1] = j_equation;
	p[2] = t_equation;
	p[3] = b_equation;
	m.newr = 0;
	m.newi = 0;
	arg->start = start;
	arg->end = start + 1 + (ftl->max / 4);
	arg->func = (*p[a]);
	arg->m = m;
	arg->ftl = ftl;
}

void			display(t_ftl *ftl, int a)
{
	pthread_t	pt[4];
	t_arg		arg[4];

	ftl->img = mlx_new_image(ftl->mlx, ftl->max, ftl->max);
	ftl->addr = mlx_get_data_addr(ftl->img, &ftl->bpp, &ftl->l, &ftl->endian);
	ftl->bpp /= 8;
	fill_arg(&arg[0], -1, ftl, a);
	fill_arg(&arg[1], ftl->max / 4 - 1, ftl, a);
	fill_arg(&arg[2], ftl->max / 2 - 1, ftl, a);
	fill_arg(&arg[3], 3 * ftl->max / 4 - 1, ftl, a);
	pthread_create(&pt[0], NULL, work, (void*)&arg[0]);
	pthread_create(&pt[1], NULL, work, (void*)&arg[1]);
	pthread_create(&pt[2], NULL, work, (void*)&arg[2]);
	pthread_create(&pt[3], NULL, work, (void*)&arg[3]);
	pthread_join(pt[0], NULL);
	pthread_join(pt[1], NULL);
	pthread_join(pt[2], NULL);
	pthread_join(pt[3], NULL);
	mlx_put_image_to_window(ftl->mlx, ftl->win, ftl->img, 0, 0);
}

void			ftl_defaults(t_ftl *ftl, int a)
{
	ftl->a = a;
	ftl->zoom = 1;
	ftl->x_slide = 0;
	ftl->y_slide = 0;
	ftl->color = 16777000;
	ftl->rp = -.78;
	ftl->ip = .15;
	ftl->heads = (a == 2) ? -2 : 2;
	display(ftl, a);
}

int				main(int ac, char **av)
{
	t_ftl		ftl;

	if (ac != 2)
		ft_return_error("usage: ./fractol <fractal set>\n\
		(availble sets: mandelbrot, julia, tricorn, burning ship)");
	ftl.max = 1000;
	ftl.maxi = 1000;
	ftl.mlx = mlx_init();
	ftl.win = mlx_new_window(ftl.mlx, ftl.max + 200, ftl.max + 170, "Fractol");
	decorate_win(ftl.mlx, ftl.win, ftl.max);
	if (ft_strcmp(av[1], "mandelbrot") == 0)
		ftl_defaults(&ftl, 0);
	else if (ft_strcmp(av[1], "julia") == 0)
		ftl_defaults(&ftl, 1);
	else if (ft_strcmp(av[1], "tricorn") == 0)
		ftl_defaults(&ftl, 2);
	else if (ft_strcmp(av[1], "burning ship") == 0)
		ftl_defaults(&ftl, 3);
	mlx_hook(ftl.win, 2, 0, key_press_hook, &ftl);
	mlx_mouse_hook(ftl.win, deal_mouse, &ftl);
	mlx_hook(ftl.win, 6, 0, ft_motion, &ftl);
	mlx_loop(ftl.mlx);
	return (0);
}
