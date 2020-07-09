/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endian.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 15:36:02 by vlaroque          #+#    #+#             */
/*   Updated: 2020/07/09 23:09:04 by aljigmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		big_endian_int(void *ptr)
{
	int		nbr;
	int		loop;
	char	tmp;

	nbr = 0;
	loop = 0;
	tmp = ptr;
	while (loop < 4)
	{
		nbr *= 256;
		nbr += *tmp;
		tmp++;
		loop++;
	}
	return (nbr);
}

t_llu	read_bin_to_nbr(void *ptr, size_t len)
{
	t_llu				br;
	t_octet				*octet;

	nbr = 0;
	octet = ptr;
	while (len)
	{
		nbr = nbr * 256 + *octet;
		octet += 1;
		len--;
	}
	return (nbr);
}

void	write_nbr_to_bin(t_llu nbr, void *dst, size_t len)
{
	t_octet				*octet;

	octet = dst;
	while (len)
	{
		*(octet + len - 1) = nbr % 256;
		nbr /= 256;
		len--;
	}
}
