/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_float1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoures <afoures@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/24 12:12:53 by marvin            #+#    #+#             */
/*   Updated: 2018/02/01 12:25:37 by afoures          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_printf_utils.h"

void	pf_h_ff_putinf(long double nb, t_flags *f)
{
	if (nb < 0)
		pf_put_buf(f->fd, "-", 1, 1);
	else if (f->plus || f->space)
		pf_put_buf(f->fd, (f->plus ? "+" : " "), 1, 1);
	pf_put_buf(f->fd, "INF", 3, 1);
}

void	pf_h_ff_putnan(long double nb, t_flags *f)
{
	if (signbit(nb))
		pf_put_buf(f->fd, "-", 1, 1);
	else if (f->plus || f->space)
		pf_put_buf(f->fd, (f->plus ? "+" : " "), 1, 1);
	pf_put_buf(f->fd, "NAN", 3, 1);
}

int		pf_h_ff_infinite(long double nb, t_flags *f)
{
	char	c;

	c = ' ' + 16 * (f->zero);
	f->len = 3 + ((nb < 0 || ((f->plus || f->space)
			&& (f->precision || f->c_prec))) && f->width);
	f->width = (f->width - f->len) * (f->width - f->len > 0);
	if (!f->minus)
	{
		if (f->width && pf_put_width(c, f->width, f) < 0)
			return (-1);
		pf_h_ff_putinf(nb, f);
	}
	else
	{
		pf_h_ff_putinf(nb, f);
		if (f->width && pf_put_width(c, f->width, f) < 0)
			return (-1);
	}
	return (f->width + f->len);
}

int		pf_h_ff_nan(long double nb, t_flags *f)
{
	char	c;

	c = ' ' + 16 * (f->zero);
	f->len = 3 + ((signbit(nb) || ((f->plus || f->space)
			&& (f->precision || f->c_prec))) && f->width);
	f->width = (f->width - f->len) * (f->width - f->len > 0);
	if (!f->minus)
	{
		if (f->width && pf_put_width(c, f->width, f) < 0)
			return (-1);
		pf_h_ff_putnan(nb, f);
	}
	else
	{
		pf_h_ff_putnan(nb, f);
		if (f->width && pf_put_width(c, f->width, f) < 0)
			return (-1);
	}
	return (f->width + f->len);
}

int		pf_h_ff_nanorinf(long double nb, t_flags *f)
{
	if (!(nb == nb))
		return (pf_h_ff_nan(nb, f));
	return (pf_h_ff_infinite(nb, f));
}
