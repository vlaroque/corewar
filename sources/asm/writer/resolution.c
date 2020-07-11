/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolution.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljigmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 15:08:02 by aljigmon          #+#    #+#             */
/*   Updated: 2020/07/08 15:11:16 by aljigmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_inst_info	*get_token_schema(t_token *token)
{
	uint32_t offset;

	offset = 0;
	while (g_inst_symbol_tab[offset].inst)
	{
		if (!ft_strcmp(token->content, g_inst_symbol_tab[offset].inst))
			return (&g_inst_symbol_tab[offset]);
		offset++;
	}
	return (NULL);
}

uint8_t		get_opc(t_inst_info *schema, t_token *token)
{
	uint8_t			opc;
	uint32_t		offset;
	int				params[3];
	int				type;

	ft_memmove(&params, &schema->param1, sizeof(int) * 3);
	opc = 0;
	offset = 0;
	while (params[offset] && offset < 3)
	{
		type = token->type;
		if ((type & T_REF) == T_REF)
			type ^= T_REF;
		if (is_parameter(token))
		{
			if (type > 3)
				type--;
			opc |= (type << (6 + (offset * -2)));
		}
		token = token->next;
		offset++;
	}
	return (opc);
}

size_t		get_dir_size(uint32_t inst)
{
	if (inst == 0x9 || inst == 0xa || inst == 0xb
			|| inst == 0xc || inst == 0xe || inst == 0xf)
		return (2);
	return (4);
}

int			get_token_offset(t_token *start, t_token *search, t_bool mnemonic)
{
	int			offset;
	int			mne_offset;
	t_token		*token;
	uint32_t	direct_size;

	token = start;
	offset = 0;
	while (token)
	{
		if ((token->type & T_MNE) == T_MNE)
			mne_offset = yield_token_offset(token, &direct_size, &offset);
		if ((token->type & T_DIR) == T_DIR)
			offset += direct_size;
		else if ((token->type & T_REG) == T_REG)
			offset++;
		else if ((token->type & T_IND) == T_IND)
			offset += IND_SIZE;
		if (token == search)
			return (mnemonic ? mne_offset : offset);
		token = token->next;
	}
	return (0);
}

int			resolve_reference(t_token *start, t_token *token)
{
	char	*reference_name;
	int		reference_offset;
	t_token	*label_token;
	int		label_offset;
	size_t	length;

	reference_name = (token->type & T_IND) == T_IND
			? token->content + 1 : token->content + 2;
	reference_offset = get_token_offset(start, token, TRUE);
	length = (size_t)ft_strlen(reference_name);
	label_token = start;
	while (label_token)
	{
		if (label_token->type == T_LAB &&
				!ft_strncmp(label_token->content, reference_name, length)
				&& (!label_token->content[length + 1]))
			break ;
		label_token = label_token->next;
	}
	if (!label_token)
		return (0);
	label_offset = get_token_offset(start, label_token, FALSE);
	return (label_offset - reference_offset);
}
