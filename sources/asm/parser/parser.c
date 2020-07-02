/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljigmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 20:01:37 by aljigmon          #+#    #+#             */
/*   Updated: 2020/06/21 20:09:59 by aljigmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	upgrade(int *i, int *num_line, char *line, char **tab)
{
	*i = 0;
	(*num_line)++;
	ft_strdel(&line);
	free_tab(&tab);
}

t_token		*lexical_analysis(const int fd, char *line, int num_line, int i)
{
	int		rt;
	char	**tab;
	t_token	*tokens;

	tokens = NULL;
	while ((rt = get_next_line(fd, &line)) > 0)
	{
		if ((tab = del_useless(line)) == NULL)
			return (free_tokens(&tokens));
		if (tokens == NULL && tab[i] && tab[i][0] != '#')
		{
			if (!(tokens = new_token(num_line, tab[i], 0)))
				return (free_tab(&tab));
			i++;
		}
		while (tab[i] && tab[i][0] != '#')
		{
			if (append_token(num_line, tab[i], 0, tokens) == 0)
				return (free_tokens(&tokens));
			i++;
		}
		upgrade(&i, &num_line, line, tab);
	}
	return (rt == -1 ? free_tokens(&tokens) : tokens);
}

t_token		*parser(const int fd)
{
	t_token	*tokens;

	tokens = lexical_analysis(fd, NULL, 1, 0);
	if (!tokens)
	{
		ft_putstr("error reading file, format not recognized\n");
		return (NULL);
	}
	syntax_analysis(tokens);
	return (tokens);
}
