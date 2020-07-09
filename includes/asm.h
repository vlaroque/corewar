/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljigmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 14:48:01 by aljigmon          #+#    #+#             */
/*   Updated: 2020/07/08 22:57:06 by aljigmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

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

t_bool		throw_fields(char *name, char *comment);
int			yield_token_offset(t_token *token,
		uint32_t *direct_size, int *offset);
t_bool		throw_check_quotes(char *str, t_token *token);
t_bool		is_parameter(t_token *token);
t_bool		ocp_required(uint32_t inst);
size_t		get_dir_size(uint32_t inst);
t_inst_info	*get_token_schema(t_token *token);
uint8_t		get_opc(t_inst_info *schema, t_token *token);
int			get_token_offset(t_token *start, t_token *search, t_bool mnemonic);
int			resolve_reference(t_token *start, t_token *token);
t_bool		is_register(t_token *token);
t_bool		is_label(char *label);
t_token		*get_label(t_token *token, char *label);
t_bool		is_constant(t_token *token);
t_bool		is_symbol(t_token *token);
char		*read_file(const int fd);
void		*free_tab(char ***tab);
char		**del_useless(char const *s);
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
int			load_file(t_file *file, char *filename);
void		write_buffer(t_file *file, char *data, uint32_t size);
void		file_flush(t_file *file);
void		clear_file(t_file *file);
int			syntax_analysis(t_token *token);

#endif
