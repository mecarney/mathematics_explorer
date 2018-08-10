/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 06:58:48 by mcarney           #+#    #+#             */
/*   Updated: 2018/08/10 06:58:49 by mcarney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx.h"
# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <pthread.h>

typedef struct		s_ftl
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bpp;
	int				l;
	int				endian;
	int				x;
	int				y;
	float			rp;
	float			ip;
	float			zoom;
	int				max;
	int				maxi;
	float			x_slide;
	float			y_slide;
	int				color;
	int				a;
	int				heads;
}					t_ftl;

typedef struct		s_equ
{
	float			newr;
	float			newi;
	float			oldr;
	float			oldi;
}					t_equ;

typedef struct		s_arg
{
	int				start;
	int				end;
	void			(*func)(t_equ, t_ftl *, int, int);
	t_equ			m;
	t_ftl			*ftl;
}					t_arg;

int					key_press_hook(int keycode, t_ftl *ftl);
int					ft_motion(int x, int y, t_ftl *ftl);
int					deal_mouse(int button, int x, int y, t_ftl *ftl);
void				decorate_win(void *a, void *b, int c);
void				display(t_ftl *ftl, int a);
void				ftl_defaults(t_ftl *ftl, int a);
void				m_equation(t_equ m, t_ftl *ftl, int x, int y);
void				t_equation(t_equ m, t_ftl *ftl, int x, int y);
void				j_equation(t_equ m, t_ftl *ftl, int x, int y);
void				b_equation(t_equ m, t_ftl *ftl, int x, int y);

#endif
