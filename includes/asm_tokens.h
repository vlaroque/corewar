/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_tokens.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljigmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 20:00:34 by aljigmon          #+#    #+#             */
/*   Updated: 2020/07/08 13:45:10 by aljigmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_TOKENS_H
# define ASM_TOKENS_H

t_token	*new_token(int num, char *content, int type);
int		append_token(int num, char *content, int type, t_token *token);
t_token	*free_tokens(t_token **tokens);

#endif
