/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljigmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 17:03:11 by aljigmon          #+#    #+#             */
/*   Updated: 2020/07/08 13:57:52 by aljigmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static inline t_bool		get_arguments(t_token *token, t_inst_info *handler)
{
	uint32_t	offset;
	int			param;
	int			params[3];

	ft_memmove(&params, &handler->param1, sizeof(int) * 3);
	offset = 0;
	while ((param = params[offset]) && offset < 3)
	{
		if (!token)
			return (FALSE);
		if (((param & T_REG) && is_register(token))
				|| ((param & T_DIR) && is_constant(token))
				|| ((param & T_IND) && is_symbol(token)))
			offset++;
		token = token->next;
	}
	return (TRUE);
}

static inline t_bool		throw_str_exception(t_token *token)
{
	char *str;

	str = token->content;
	if (!token->prev || *str++ != '"')
		return (FALSE);
	if (token->prev->type != T_PRE)
	{
		display_string_error("Assembly syntax error");
		return (TRUE);
	}
	return (throw_check_quotes(str, token));
}

static inline t_bool		throw_label_exception(t_token *token)
{
	char *symbol;

	if (*token->content == DIRECT_CHAR)
		return (FALSE);
	symbol = token->content;
	while (*symbol && *symbol != ':')
		symbol++;
	if (*symbol == ':')
	{
		if (!*(symbol + 1))
			token->type = T_LAB;
		else
		{
			display_label_error(token->content);
			return (TRUE);
		}
	}
	return (FALSE);
}

static inline t_inst_info	*get_schema(t_token *token)
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

void						syntax_analysis(t_token *token)
{
	t_inst_info	*schema;

	while (token)
	{
		if (*token->content == '.')
			token->type = T_PRE;
		if (throw_str_exception(token) || throw_label_exception(token))
			return ;
		if (token->type != T_PRE)
		{
			if ((schema = get_schema(token)))
			{
				token->type = T_MNE;
				if (!token->next)
					return ;
				if (!(get_arguments(token->next, schema)))
					return ;
			}
		}
		token = token->next;
	}
}
