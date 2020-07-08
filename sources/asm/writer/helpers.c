/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endianness.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljigmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 17:05:46 by aljigmon          #+#    #+#             */
/*   Updated: 2020/06/22 17:05:47 by aljigmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_bool	is_parameter(t_token *token)
{
	return (token && ((token->type & T_DIR) == T_DIR || ((token->type & T_IND) == T_IND) || token->type == T_REG));
}



t_bool	ocp_required(uint32_t inst)
{
	return (inst != 0x1 && inst != 0x09 && inst != 0x0c);
}


void	to_big_endian16(char *buff)
{
	uint16_t	data;
	uint16_t	value;

	data = *(uint16_t*)buff;
	value = (((data & 0xff) << 8) | (data >> 8));
	memcpy(buff, (void*)&value, sizeof(uint16_t));
}

void	to_big_endian32(char *buff)
{
	uint32_t	data;
	uint32_t	value;

	data = *(uint32_t*)buff;
	value = (
			((data << 24) & 0xff000000) |
			((data << 8) & 0xff0000) |
			((data >> 24) & 0xff) |
			((data >> 8) & 0xff00));
	memcpy(buff, (void*)&value, sizeof(uint32_t));
}

void	to_big_endian64(char *buff)
{
	uint64_t	data;
	uint64_t	value;

	data = *(uint64_t*)buff;
	value = (
			((data << 56) & 0xff00000000000000) |
			((data << 40) & 0xff000000000000) |
			((data << 24) & 0xff0000000000) |
			((data << 8) & 0xff00000000) |
			((data >> 8) & 0xff000000) |
			((data >> 24) & 0xff0000) |
			((data >> 40) & 0xff00) |
			((data >> 56) & 0xff));
	memcpy(buff, (void*)&value, sizeof(uint64_t));
}
