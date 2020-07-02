/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljigmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 14:48:01 by aljigmon          #+#    #+#             */
/*   Updated: 2020/06/20 20:59:55 by aljigmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "libft.h"
# include "asm_typedefs.h"
# include "asm_structures.h"
# include "asm_tokens.h"

void		display_string_error(char *str);
void		display_label_unknown(t_token *token);
void		display_type_error(t_token *token);
void		display_label_error(char *label);
void		display_register_unknown(t_token *token);
void		display_file_error(char *filename);
void		display_open_error(void);
void		display_filename_error(char *filename);
void		display_missing_field(char *str);
void		display_allocation_error(void);
t_token		*parser(const int fd);
void		to_big_endian16(char *buff);
void		to_big_endian32(char *buff);
void		to_big_endian64(char *buff);
void		write_binary(char *in_file, t_token *token);
void		assemble(char *filename, t_token *token);
t_file		*init_file(void);
int		load_file(t_file *file, char *filename);
void		write_buffer(t_file *file, char *data, uint32_t size);
void		file_flush(t_file *file);
void		clear_file(t_file *file);
void		syntax_analysis(t_token *token);

#endif
