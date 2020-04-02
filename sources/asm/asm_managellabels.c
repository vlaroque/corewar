/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_managellabels.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stherkil <stherkil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 11:01:42 by stherkil          #+#    #+#             */
/*   Updated: 2020/02/19 15:48:43 by stherkil         ###   ########.fr       */
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
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0}
};

static char	*ft_strdupspace(const char *s1)
{
	char *out;
	int i;

	i = 0;
	while (s1[i] > ' ')
		++i;
	if (!(out = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	ft_strncpy(out, s1, i + 1);
	return (out);
}

int		check_labelname(char *s)
{
	int i;
	int j;
	int oknext;

	i = 0;
	while (s[i] > ' ')
	{
		oknext = 0;
		j = -1;
		while (LABEL_CHARS[++j])
			if (LABEL_CHARS[j] == s[i])
				oknext = 1;
		if (!oknext)
			return (0);
		++i;
	}
	return (i);
}

static int		label_checkdup(labels_t *labels, char *s)
{
	while (labels)
	{
		if (!ft_strcmp(labels->name, s))
			return (1);
		labels = labels->next;
	}
	return (0);
}

void	manage_label(char *s, int type, header_t *header)
{
	labels_t *new;

	check_labelname(s);
	if (label_checkdup(header->labels, ft_strdupspace(s)))
		return ;
	if (!(new = malloc(sizeof(labels_t))))
		errorparser("malloc error", header);
	new->name = ft_strdupspace(s);
	new->nb = (header->lastlabelnb += 1);
	new->row = header->row;
	new->row = header->col;
	new->next = header->labels;
	header->labels = new;
}