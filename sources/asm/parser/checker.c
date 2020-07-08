#include "asm.h"

t_bool	is_register(t_token *token)
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

t_bool	is_label(char *label)
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

t_token	*get_label(t_token *token, char *label)
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
		if (size - 1 == label_size && !ft_strncmp(item->content, label, size - 1))
			return (item);
		item = item->next;
	}
	display_label_unknown(token);
	return (NULL);
}

t_bool	is_constant(t_token *token)
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

t_bool	is_symbol(t_token *token)
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