/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljigmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 17:02:09 by aljigmon          #+#    #+#             */
/*   Updated: 2020/06/22 17:09:32 by aljigmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	display_file_error(char *filename)
{
	ft_putstr("\033[31mThe output file already exists \"");
	ft_putstr(filename);
	ft_putstr("\" cannot be overwritten.\e[0m\n");
}

void	display_filename_error(char *filename)
{
	ft_putstr("\033[31mThe specified file \"");
	ft_putstr(filename);
	ft_putstr("\" contains too many characters\e[0m\n");
}

void	display_open_error(void)
{
	perror("\033[31mError opening destination");
	ft_putstr("\e[0m\n");
}

void	display_missing_field(char *str)
{
	ft_putstr("\033[31mPlease specify the \"");
	ft_putstr(str);
	ft_putstr("\" field in the source code.\e[0m\n");
}

void	display_allocation_error(void)
{
	ft_putstr("\033[31mThe machine does not have ");
	ft_putstr("enough resources to allocate memory.\e[0m\n");
}
