/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 06:58:39 by mcarney           #+#    #+#             */
/*   Updated: 2018/08/10 06:58:43 by mcarney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void		change_addr(t_ftl *ftl, int x, int y, int color)
{
	ftl->addr[y * ftl->l + x * ftl->bpp] = color;
	ftl->addr[y * ftl->l + x * ftl->bpp + 1] = color >> 8;
	ftl->addr[y * ftl->l + x * ftl->bpp + 2] = color >> 16;
}

void		m_equation(t_equ m, t_ftl *ftl, int x, int y)
{
	float	rp;
	float	ip;
	int		i;

	rp = ((x / (ftl->max * .5)) - 1) / (.7 * ftl->zoom) - ftl->x_slide - .7;
	ip = ((y / (ftl->max * .5)) - 1) / (.7 * ftl->zoom) - ftl->y_slide;
	i = 0;
	while (i < ftl->maxi / 4 && m.newr * m.newr + m.newi * m.newi < 4)
	{
		m.oldr = m.newr;
		m.oldi = m.newi;
		m.newr = m.oldr * m.oldr - m.oldi * m.oldi + rp;
		m.newi = ftl->heads * m.oldr * m.oldi + ip;
		i = (i > 100) ? i + 100 : i + 1;
	}
	change_addr(ftl, x, y, ftl->color * i);
}

void		t_equation(t_equ m, t_ftl *ftl, int x, int y)
{
	float	rp;
	float	ip;
	int		i;

	rp = ((x / (ftl->max * .5)) - 1) / (.5 * ftl->zoom) - ftl->x_slide - .4;
	ip = ((y / (ftl->max * .5)) - 1) / (.5 * ftl->zoom) - ftl->y_slide;
	i = 0;
	while (i < ftl->maxi / 4 && m.newr * m.newr + m.newi * m.newi < 4)
	{
		m.oldr = m.newr;
		m.oldi = m.newi;
		m.newr = m.oldr * m.oldr - m.oldi * m.oldi + rp;
		m.newi = ftl->heads * m.oldr * m.oldi + ip;
		i = (i > 100) ? i + 100 : i + 1;
	}
	change_addr(ftl, x, y, ftl->color * i);
}

void		j_equation(t_equ m, t_ftl *ftl, int x, int y)
{
	int		i;

	m.newr = (x - ftl->max * .5) / (.3 * ftl->zoom * ftl->max) - ftl->x_slide;
	m.newi = (y - ftl->max * .5) / (.5 * ftl->zoom * ftl->max) - ftl->y_slide;
	i = 0;
	while (i < ftl->max / 4 && m.newr * m.newr + m.newi * m.newi < 4)
	{
		m.oldr = m.newr;
		m.oldi = m.newi;
		m.newr = m.oldr * m.oldr - m.oldi * m.oldi + ftl->rp;
		m.newi = ftl->heads * m.oldr * m.oldi + ftl->ip;
		i = (i > 100) ? i + 200 : i + 1;
	}
	change_addr(ftl, x, y, ftl->color * i);
}

void		b_equation(t_equ m, t_ftl *ftl, int x, int y)
{
	float	rp;
	float	ip;
	int		i;

	rp = ((x / (ftl->max * 0.7)) - 1) / (.4 * ftl->zoom) - ftl->x_slide + .4;
	ip = ((y / (ftl->max * 0.7)) - 1) / (.4 * ftl->zoom) - ftl->y_slide;
	i = 0;
	while (i < ftl->maxi / 4 && m.newr * m.newr + m.newi * m.newi < 4)
	{
		m.oldr = m.newr;
		m.oldi = m.newi;
		m.newr = fabs(m.oldr * m.oldr - m.oldi * m.oldi + rp);
		m.newi = fabs(ftl->heads * m.oldr * m.oldi) + ip;
		i = (i > 100) ? i + 100 : i + 1;
	}
	change_addr(ftl, x, y, ftl->color * i);
}
