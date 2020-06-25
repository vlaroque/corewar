/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stherkil <stherkil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 17:19:57 by vlaroque          #+#    #+#             */
/*   Updated: 2020/06/26 00:07:49 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <stdio.h>
# include <stdlib.h>
# include "typedefs.h"
# include "op.h"
# include "champ_id.h"
# include "libft.h"
# include "operation_reading.h"
# include "structures.h"

/*
** debug
*/
int		show_mars(t_data *data);
void	hex_dump(t_octet *src, size_t len);
int		champ_dump(t_champ *champ);
int		err(char *s);
int		debug_process(t_process *process);
int		debug_global(t_data *data, int turn);
int		dump_option_mars(t_data *data);

/*
** battle
*/
int		battle(t_data *data);

/*
** init
*/
int		init_corewar(t_data *data, int ac, char **av);
int		mars_fill(t_data *data);
int		new_champ(t_data *data, char *source, t_champid *champ_id);

/*
** init errors
*/
int		print_error(t_data *data, int error);
int		ft_isnbr(char *str);
int		print_usage(t_data *data);

/*
** process_new
*/
int		new_process(t_data *data, int loc, int champ_id);

/*
** checks
*/
int		checks(t_data *data);

/*
** operation_reading
*/
int		read_operation(t_data *data, t_process *process);

/*
** op_exe
*/
int		execute_operation(t_data *data, t_process *process);

/*
** it_functions
*/
int		it_live(t_data *data, t_process *process, int champ_id);
int		it_fork(t_data *data, t_process *process, int pc);
int		it_aff(t_data *data, t_process *process, char pc);

/*
** pre_execute_op
*/
int		pre_execute_op(t_data *data, t_process *proc, t_cache *c);

/*
** read_mars
*/
int		pc_fix(int pc);
int		read_int_mars(t_data *data, int pc);
short	read_short_mars(t_data *data, int pc);
t_octet	read_oct_mars(t_data *data, int pc);

/*
** write_mars
*/
int		write_oct_mars(t_data *data, t_octet c, int pc);
int		write_short_mars(t_data *data, short nbr, int pc);
int		write_int_mars(t_data *data, int nbr, int pc);

/*
** encoding_byte
*/
t_octet	*decode_encoding_byte(t_data *data, t_process *process,
		t_octet *tmp_types);
int		incorrect_encoding_byte(int op, t_octet *types);

/*
** get_data_from_args.c
*/
int		get_int_from_direct_arg(t_data *d, t_process *p, t_args *arg,
		int idx_lim);
int		get_int_from_indirect_arg(t_data *d, t_process *p, t_args *arg,
		int idx_lim);

/*
** differents functions
*/
int		op_just_next(t_data *data, t_process *process, t_cache *c);
int		op_live(t_data *data, t_process *process, t_cache *c);
int		op_ld(t_data *data, t_process *process, t_cache *c);
int		op_st(t_data *data, t_process *process, t_cache *c);
int		op_add(t_data *data, t_process *process, t_cache *c);
int		op_sub(t_data *data, t_process *process, t_cache *c);
int		op_and(t_data *data, t_process *process, t_cache *c);
int		op_or(t_data *data, t_process *process, t_cache *c);
int		op_xor(t_data *data, t_process *process, t_cache *c);
int		op_zjmp(t_data *data, t_process *process, t_cache *c);
int		op_ldi(t_data *data, t_process *process, t_cache *c);
int		op_sti(t_data *data, t_process *process, t_cache *c);
int		op_fork(t_data *data, t_process *process, t_cache *c);
int		op_lld(t_data *data, t_process *process, t_cache *c);
int		op_lldi(t_data *data, t_process *process, t_cache *c);
int		op_lfork(t_data *data, t_process *process, t_cache *c);
int		op_aff(t_data *data, t_process *process, t_cache *c);
int		op_bad_encoding_byte(t_data *data, t_process *process, t_cache *c);
void	if_null_carry_up(t_process *p, int value);

/*
** verbose functions
*/
int		v_st(t_data *data, t_process *process, t_cache *c);
int		v_sti(t_data *data, t_process *process, t_cache *c);
int		v_ldi(t_data *data, t_process *process, t_cache *c);
int		v_lldi(t_data *data, t_process *process, t_cache *c);

/*
** todo functions
*/
void	todo_change_reg(t_process *p, int reg_id, int content);
void	todo_write_mars(t_process *p, int where, int what);
void	todo_fork(t_process *p, int where);
void	todo_carry(t_process *p, int carry);
void	todo_change_pc(t_process *p, int pc);

/*
** verbosity
*/
int		show_turn(t_data *data, int i);
int		show_cycle_to_die(t_data *data, int i);
int		show_live(t_data *data, t_champ *champ);
int		show_process_death(t_data *data, t_process *process);

/*
** frees.c
*/
int		free_data(t_data *data);
int		exit_error(t_data *data, char *str);

/*
** Messages
*/
int		introduce_contestants(t_data *data);
int		victory(t_data *data);

/*
** buff_mars
*/
int		buff_mars(t_data *data);
int		write_in_buffer(char *buff, char *str, int i);
void	char_hexa_str(t_octet c, char *str);
int		is_pointed(t_data *data, int pc);

/*
** buff_mars_color
*/
int		what_color(t_data *data, char *buff, int buff_i, int i);
int		color_octet(t_data *data, char *buff, int buff_i, int i);

/*
** visual_operations
*/

int		verbose_operations(t_data *data, t_process *p);
int		verbose_opertation_end(t_data *data, t_process *p);
int		show_reg_elsif_number(t_data *data, t_args *arg, int nbr);
int		verbose_space(t_data *data);
int		verbose_putnbr(t_data *data, int nbr);

/*
** verbose_utility
*/
int		nbr_len(int nbr);
int		print_x_spaces(int x);

#endif
