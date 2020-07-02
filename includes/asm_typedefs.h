/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljigmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 16:23:39 by aljigmon          #+#    #+#             */
/*   Updated: 2020/06/20 21:03:44 by aljigmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include <string.h>
# include <stdint.h>

# define ERROR -1
# define SUCCESS 1
# define PAGE_SIZE 4096
# define FALSE 0
# define TRUE 1

typedef int		t_bool;

# define T_REG                                  1
# define T_DIR                                  2
# define T_IND                                  4
# define T_LAB                                  8
# define T_MNE                                  16
# define T_REF                                  32
# define T_STR                                  64
# define T_PRE                                  128
# define T_INT                                  256

#endif
