/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parttwo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stherkil <stherkil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 11:01:42 by stherkil          #+#    #+#             */
/*   Updated: 2020/01/30 18:56:06 by stherkil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

static t_op		op_tab[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
};

void			asm_ld(header_t *header, instr_t *instr, unsigned char *BUF, int *bufptout)
{
	int i;

	i = -1;
	BUF[*bufptout] = instr->instr;
	*bufptout += 1;
	if (instr->instr != 1)
	{
	BUF[*bufptout] = instr->enc;
	*bufptout += 1;
	}
	printf("len is %d\n", instr->ptlen);
	while (++i < instr->ptlen)
	{
		if (instr->instr == 1)
		{
			itobh(BUF, bufptout, instr->data[i]);
		}
		else
		{
			BUF[*bufptout] = instr->data[i];
			*bufptout += 1;
		}
	}
}

void			parttwo(unsigned char *BUF, int *bufptout, header_t *header)
{
	int bufpt;

	//hexlittle(header->NUM, 42);
	bufpt = *bufptout;
	while (header->firstinstr->instr != -1)
	{
		asm_ld(header, header->firstinstr, BUF, &bufpt);
		header->firstinstr = header->firstinstr->next;
	}
	/*	
		printf("big hex is %s\n", header->NUM);
		ft_memcpy(BUF + bufpt, header->NUM, 4);
		bufpt += 4;
		*/
	*bufptout = bufpt;
}
