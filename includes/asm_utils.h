/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljigmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 14:47:34 by aljigmon          #+#    #+#             */
/*   Updated: 2020/07/08 13:45:37 by aljigmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_UTILS_H
# define ASM_UTILS_H

# include "asm_structures.h"

char	*read_file(const int fd);
void	*free_tab(char ***tab);
char	**del_useless(char const *s);

#endif
