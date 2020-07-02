/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljigmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 17:02:42 by aljigmon          #+#    #+#             */
/*   Updated: 2020/06/22 17:02:45 by aljigmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	display_label_unknown(t_token *token)
{
	ft_putstr("\033[31mThe label \"");
	ft_putstr(token->content);
	ft_putstr("\" is unknown.\e[0m\n");
	(void)token;
}

void	display_type_error(t_token *token)
{
	ft_putstr("\033[31m\"");
	ft_putstr(token->content);
	ft_putstr("\" is an invalid operand.\e[0m\n");
}

void	display_label_error(char *label)
{
	ft_putstr("\033[31mThe label \"");
	ft_putstr(label);
	ft_putstr("\" contains a prohibited character.\e[0m\n");
}

void	display_register_unknown(t_token *token)
{
	ft_putstr("\033[31mThe specified register \"");
	ft_putstr(token->content);
	ft_putstr("\" does not exist.\e[0m\n");
}

void	display_string_error(char *str)
{
	ft_putstr("\033[31mA specified string error: \e[0m");
	ft_putstr(str);
	ft_putchar('\n');
}
