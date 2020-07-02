/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljigmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 20:00:34 by aljigmon          #+#    #+#             */
/*   Updated: 2020/06/21 20:06:35 by aljigmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

t_token	*new_token(int num, char *content, int type);
int		append_token(int num, char *content, int type, t_token *token);
t_token	*free_tokens(t_token **tokens);

#endif
