/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljigmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 20:01:37 by aljigmon          #+#    #+#             */
/*   Updated: 2020/07/09 15:09:12 by aljigmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_bool		throw_check_quotes(char *str, t_token *token)
{
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

static void	upgrade(int *i, int *num_line, char *line, char **tab)
{
	*i = 0;
	(*num_line)++;
	ft_strdel(&line);
	free_tab(&tab);
}

static int	check_line(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ',' && line[i + 1] == ',')
			return (-1);
		i++;
	}
	return (0);
}

t_token		*lexical_analysis(const int fd, char *line, int num_line, int i)
{
	int		rt;
	char	**tab;
	t_token	*tokens;

	tokens = NULL;
	while ((rt = get_next_line(fd, &line)) > 0)
	{
		if ((tab = del_useless(line)) == NULL || (check_line(line) == -1))
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
	int		count;

	tokens = lexical_analysis(fd, NULL, 1, 0);
	if (!tokens)
	{
		ft_putstr("error reading file, format not recognized\n");
		return (NULL);
	}
	count = syntax_analysis(tokens);
	if (count <= 0)
	{
		if (count == -1)
			ft_putstr("The file does not contain instructions to execute\n");
		free_tokens(&tokens);
		return (NULL);
	}
	return (tokens);
}
