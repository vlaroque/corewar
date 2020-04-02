/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itobighex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stherkil <stherkil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 11:01:42 by stherkil          #+#    #+#             */
/*   Updated: 2020/01/30 18:14:54 by stherkil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char			decitohex(int nb)
{
	return (nb);
}

void			putmax(char *NUM)
{
	int i;

	i = -1;
	while (++i < 8)
		NUM[i] = 'f';
}

static void		hexbig(char *NUM, long long nb)
{
	if (nb / 4294967296 > 0)
	{
		putmax(NUM);
		return ;
	}
	NUM[0] = decitohex(nb / 268435456);
	nb -= 268435456 * (nb / 268435456);
	NUM[1] = decitohex(nb / 16777216);
	nb -= 16777216 * (nb / 16777216);
	NUM[0] = NUM[0] * 16 + NUM[1];
	NUM[2] = decitohex(nb / 1048576);
	nb -= 1048576 * (nb / 1048576);
	NUM[3] = decitohex(nb / 65536);
	nb -= 65536 * (nb / 65536);


	NUM[1] = NUM[2] * 16 + NUM[3];
	NUM[4] = decitohex(nb / 4096);
	nb -= 4096 * (nb / 4096);
	NUM[5] = decitohex(nb / 256);
	nb -= 256 * (nb / 256);


	NUM[2] = NUM[4] * 16 + NUM[5];
	NUM[6] = decitohex(nb / 16);
	nb -= 16 * (nb / 16);
	NUM[7] = decitohex(nb);


	NUM[3] = NUM[6] * 16 + NUM[7];
}

void			itobh(unsigned char *BUF, int *bufpt, long long nb)
{
	char NUM[8];

	hexbig(NUM, nb);
	ft_memcpy(BUF + *bufpt, NUM, 4);
	*bufpt += 4;
}	
		
