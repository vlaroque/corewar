/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljigmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 17:03:11 by aljigmon          #+#    #+#             */
/*   Updated: 2020/06/22 17:03:12 by aljigmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static inline t_bool	is_register(t_token *token)
{
	char		*symbol;
	int			register_number;

	symbol = token->content;
	if (*symbol++ != 'r')
		return (FALSE);
	register_number = atoi(symbol);
	if (register_number < 0 || register_number > REG_NUMBER)
	{
		display_register_unknown(token);
		return (FALSE);
	}
	token->type = T_REG;
	return (TRUE);
}

static inline t_bool	is_label(char *label)
{
	uint32_t	offset;

	while (*label)
	{
		offset = 0;
		while (LABEL_CHARS[offset] && LABEL_CHARS[offset] != *label)
			offset++;
		if (!LABEL_CHARS[offset])
			return (FALSE);
		label++;
	}
	return (TRUE);
}

static inline t_token	*get_label(t_token *token, char *label)
{
	t_token			*item;
	size_t			size;
	size_t			label_size;

	if (!is_label(label))
	{
		display_label_unknown(token);
		return (NULL);
	}
	item = token;
	while (item->prev)
		item = item->prev;
	label_size = 0;
	while (label[label_size])
		label_size++;
	while (item)
	{
		size = 0;
		while (item->content[size])
			size++;
		if (size - 1 == label_size
				&& !ft_strncmp(item->content, label, size - 1))
			return (item);
		item = item->next;
	}
	display_label_unknown(token);
	return (NULL);
}

static inline t_bool	is_constant(t_token *token)
{
	char	*symbol;
	t_token	*label;

	symbol = token->content;
	if (*symbol != DIRECT_CHAR)
		return (FALSE);
	symbol++;
	if (*symbol == LABEL_CHAR)
	{
		symbol++;
		label = get_label(token, symbol);
		if (!label)
			return (FALSE);
		label->type = T_LAB;
		token->type = (T_REF | T_DIR);
		return (TRUE);
	}
	token->content++;
	token->type = T_DIR;
	return (TRUE);
}

static inline t_bool	is_symbol(t_token *token)
{
	t_token		*label;
	uint32_t	offset;

	puts(token->content);
	puts("okkkk");
	if (token->content[0] == LABEL_CHAR)
	{
		label = get_label(token, token->content + 1);
		if (!label)
			return (FALSE);
		label->type = T_LAB;
		token->type = (T_REF | T_IND);
		exit(0);
		return (TRUE);
	}
	offset = (token->content[0] == '+' || token->content[0] == '-') ? 1 : 0;
	while (token->content[offset])
	{
		if (token->content[offset] < '0' || token->content[offset] > '9')
			return (FALSE);
		offset++;
	}
	token->type = T_IND;
	return (TRUE);
}

static inline t_bool	get_arguments(t_token *token, t_inst_info *handler)
{
	uint32_t	offset;
	int			param;
	int			params[3];

	memmove(&params, &handler->param1, sizeof(int) * 3);
	offset = 0;
	while ((param = params[offset]) && offset < 3)
	{
		puts(token->content);
		if (((param & T_REG) && is_register(token))
				|| ((param & T_DIR) && is_constant(token))
				|| ((param & T_IND) && is_symbol(token)))
			offset++;
		else
		{
			puts(token->content);
			puts("wtff");
			exit(0);
			return (FALSE);
		}
		token = token->next;
	}
	puts("\n");
	return (TRUE);
}

static inline t_bool	throw_str_exception(t_token *token)
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
	while (*str && *str != '"')
	{
		if (*str == '\\' && *(str + 1) == '"')
		{
			if (!*(str + 2))
			{
				display_string_error(token->content);
				return (TRUE);
			}
			ft_strcpy(str, str + 1);
		}
		str++;
	}
	if (*str != '"' || *(str + 1))
	{
		display_string_error(token->content);
		return (TRUE);
	}
	*str = '\0';
	token->type = T_STR;
	token->content++;
	return (FALSE);
}

static inline t_bool	throw_label_exception(t_token *token)
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

void					syntax_analysis(t_token *token)
{
	uint32_t	offset;
	uint32_t	label;
	uint64_t	inst;

	while (token)
	{
		label = *(uint32_t*)token->content;
		offset = 0;
		while (g_inst_symbol_tab[offset].inst)
		{
			inst = *(uint32_t*)g_inst_symbol_tab[offset].inst;
			if (*token->content == '.')
				token->type = T_PRE;
			if (throw_str_exception(token) || throw_label_exception(token))
				return ;
			if (!token->type && inst == label)
			{
				if (!get_arguments(token->next, &g_inst_symbol_tab[offset]))
					return ;
				token->type = T_MNE;
			}
			offset++;
		}
		token = token->next;
	}
}
