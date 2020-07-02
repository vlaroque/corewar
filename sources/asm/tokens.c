/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljigmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 19:44:35 by aljigmon          #+#    #+#             */
/*   Updated: 2020/06/21 20:05:37 by aljigmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_token		*new_token(int num, char *content, int type)
{
	t_token		*token;

	token = (t_token*)malloc(sizeof(*token));
	if (!token)
		return (NULL);
	token->num = num;
	token->content = ft_strdup(content);
	if (!token->content)
	{
		free(token);
		return (NULL);
	}
	token->type = type;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

int			append_token(int num, char *content, int type, t_token *token)
{
	while (token->next)
	{
		token = token->next;
	}
	token->next = (t_token*)malloc(sizeof(*token));
	if (!token->next)
		return (0);
	token->next->num = num;
	token->next->content = ft_strdup(content);
	if (!token->next->content)
	{
		free(token->next);
		return (0);
	}
	token->next->type = type;
	token->next->next = NULL;
	token->next->prev = token;
	return (1);
}

t_token		*free_tokens(t_token **tokens)
{
	t_token	*token;
	t_token	*tmp;

	token = *tokens;
	while (token->prev)
		token = token->prev;
	while (token)
	{
		tmp = token;
		token = tmp->next;
		if (tmp->content)
			ft_strdel(&tmp->content);
		free(tmp);
	}
	return (NULL);
}
