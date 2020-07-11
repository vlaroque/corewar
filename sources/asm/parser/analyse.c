/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljigmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 17:03:11 by aljigmon          #+#    #+#             */
/*   Updated: 2020/07/11 20:20:24 by aljigmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static inline t_bool		get_arguments(t_token *token, t_inst_info *handler)
{
	uint32_t	offset;
	int			param;
	int			params[3];
	uint32_t	count;

	ft_memmove(&params, &handler->param1, sizeof(int) * 3);
	count = 0;
	while (count < 3 && params[count])
		count++;
	offset = 0;
	while ((param = params[offset]) && offset < 3 && token)
	{
		if (((param & T_REG) && is_register(token))
				|| ((param & T_DIR) && is_constant(token))
				|| ((param & T_IND) && is_symbol(token)))
			offset++;
		if (!token->type)
			offset = 4;
		token = token->next;
	}
	if (offset != count)
		display_string_error("Assembly syntax error");
	return (offset == count);
}

static inline t_bool		throw_str_exception(t_token *token)
{
	char *str;

	if (*token->content == '.' && (!ft_strcmp(token->content, ".name")
		|| !ft_strcmp(token->content, ".comment")))
	{
		token->type = T_PRE;
		return (FALSE);
	}
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

	if (token->type || *token->content == DIRECT_CHAR)
		return (FALSE);
	symbol = token->content;
	while (*symbol && *symbol != ':')
		symbol++;
	if (*symbol == ':')
	{
		*symbol = '\0';
		if (!*(symbol + 1) && is_label(token->content))
		{
			*symbol = ':';
			token->type = T_LAB;
		}
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
	uint32_t		offset;
	uint32_t		length;

	offset = 0;
	length = ft_strlen(token->content);
	while (g_inst_symbol_tab[offset].inst)
	{
		if (!ft_strcmp(token->content, g_inst_symbol_tab[offset].inst)
				&& length == ft_strlen(g_inst_symbol_tab[offset].inst))
			return (&g_inst_symbol_tab[offset]);
		offset++;
	}
	return (NULL);
}

int							syntax_analysis(t_token *token)
{
	t_inst_info		*schema;
	int				count;

	count = -1;
	while (token && !throw_str_exception(token)
			&& !throw_label_exception(token))
	{
		if (!token->type)
		{
			if ((schema = get_schema(token)))
			{
				token->type = T_MNE;
				if (!token->next || !(get_arguments(token->next, schema)))
					return (!token->next ? -1 : count + 1);
				count++;
			}
		}
		if (!token->type)
		{
			display_string_error("Assembly syntax error");
			return (FALSE);
		}
		token = token->next;
	}
	return (token ? 0 : count + 1);
}
