/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_structures.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljigmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 16:25:10 by aljigmon          #+#    #+#             */
/*   Updated: 2020/07/08 13:44:42 by aljigmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_STRUCTURES_H
# define ASM_STRUCTURES_H

# include "asm_typedefs.h"
# include "op.h"

typedef struct		s_token
{
	int				num;
	int				type;
	int				offset;
	char			*content;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct		s_label_info
{
	char				*label;
	struct s_label_info *next;
}					t_label_info;

typedef struct		s_inst_info
{
	char	*inst;
	int		param1;
	int		param2;
	int		param3;
	int		opcode;
}					t_inst_info;

typedef struct		s_file
{
	int			fd;
	char		*buffer;
	uint8_t		page;
	uint32_t	size;
}					t_file;

typedef union
{
	int				param1;
	int				param2;
	int				param3;
}					t_params;

static t_inst_info	g_inst_symbol_tab[17] =
{
	{"live", T_DIR, 0, 0, 0x01},
	{"ld", T_DIR | T_IND, T_REG, 0, 0x02},
	{"st", T_REG, T_IND | T_REG, 0, 0x03},
	{"add", T_REG, T_REG, T_REG, 0x04},
	{"sub", T_REG, T_REG, T_REG, 0x05},
	{"and", T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG, 0x06},
	{"or", T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG, 0x07},
	{"xor", T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG, 0x08},
	{"zjmp", T_DIR, 0, 0, 0x09},
	{"ldi", T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG, 0x0A},
	{"sti", T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG, 0x0B},
	{"fork", T_DIR, 0, 0, 0x0C},
	{"lld", T_DIR | T_IND, T_REG, 0, 0x0D},
	{"lldi", T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG, 0x0E},
	{"lfork", T_DIR, 0, 0, 0x0F},
	{"aff", T_REG, 0, 0, 0x10},
	{NULL, 0, 0, 0, 0}
};

#endif
