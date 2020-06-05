/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stherkil <stherkil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 17:19:57 by vlaroque          #+#    #+#             */
/*   Updated: 2020/03/10 15:36:07 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <stdio.h>
# include <stdlib.h>
# include "op.h"
# include "champ_id.h"
# include "libft.h"
typedef unsigned long long	t_llu;
# include "common.h"
typedef unsigned char		t_octet;
# include "operation_reading.h"
typedef unsigned char		t_bool;

/*
** register size determination
*/
# if REG_SIZE == 1
typedef unsigned char		t_reg;
# elif REG_SIZE == 2
typedef unsigned short		t_reg;
# elif REG_SIZE == 4
typedef unsigned int		t_reg;
# elif REG_SIZE == 8
typedef unsigned long long	t_reg;
# else
#  error register size not accepted
# endif

typedef union	u_subint
{
	int		nbr;
	short	short_nbr;
	t_octet	char_nbr[4];
}				t_subint;

typedef struct			s_todo
{
	t_bool		something_to_do;
	int			pc_add;

	t_bool		cmd_life;
	int			champ_id_life;

	t_bool		cmd_write_on_mars;
	int			pc;
	int			mars_content;

	t_bool		cmd_change_register;
	int			reg;
	int			reg_content;

	t_bool		cmd_change_carry;
	int			carry_content;

	t_bool		cmd_fork;
	int			fork_pc;

	t_bool		cmd_aff;
	t_octet		char_to_aff;
}						t_todo;

typedef struct			s_op
{
	char		*name;
	int			param_number;
	t_octet		types_tab[4];
	t_octet		op_code;
	int			cycle;
	char		*complete_name;
	t_octet		encoding_byte;
	int			direct_size_two;
}						t_op;


typedef struct			s_process
{
	int					id;
	t_octet				op;
	t_reg				pc;
	unsigned int		carry;
	t_reg				reg[REG_NUMBER + 1];
	int					color;
	t_todo				todo;
	int					cooldown;
	int					lives_count;
	struct s_process	*next;
}						t_process;

/*
** champion
*/

typedef struct			s_champ
{
	int					id;
	int					champ_rank;
	char				prog_name[PROG_NAME_LENGTH + 1];
	unsigned int		prog_size;
	char				comment[COMMENT_LENGTH + 1];
	t_octet				content[CHAMP_MAX_SIZE];
	struct s_champ		*next;
}						t_champ;

typedef struct			s_data
{
	t_octet				mars[MEM_SIZE];
	int					colors[MEM_SIZE];
	int					nbr_champs;
	t_champ				*champs;
	t_process			*processes;

	int					cycles_to_die;
	int					max_cycles;
	int					checks_count;
	int					lives_count;
	int					last_alive;

	int					visual_option;
	int					dump_option;
	int					cycles_before_dump;
	int					debug_option;
}						t_data;

/*
** debug
*/
int			show_mars(t_data *data);
void		hex_dump(t_octet *src, size_t len);
int			champ_dump(t_champ *champ);
int			buff_mars(t_data *data);
int			err(char *s);
int			debug_process(t_process *process);
int			debug_global(t_data *data, int turn);
int			dump_option_mars(t_data *data);

/*
 ** battle
 */
int			battle(t_data *data);

/*
** init
*/
int			init_corewar(t_data *data, int ac, char **av);
int			mars_fill(t_data *data);
int			new_champ(t_data *data, char *source, t_champid *champ_id);


/*
** process_new
*/
int			new_process(t_data *data, int loc, int champ_id);

/*
** checks
*/
int			checks(t_data *data);


/*
 ** operation_reading
 */
int		read_operation(t_data *data, t_process *process);


/*
 ** op_exe
 */
int		execute_operation(t_data *data, t_process *process);

/*
 ** pre_execute_op
 */
int		pre_execute_op(t_data *data, t_process *proc, t_cache *c);

/*
 ** read_mars
 */
int			pc_fix(int pc);
int			read_int_mars(t_data *data, int pc);
short		read_short_mars(t_data *data, int pc);
t_octet		read_oct_mars(t_data *data, int pc);

/*
 ** write_mars
 */
int		write_oct_mars(t_data *data, t_octet c, int pc);
int		write_short_mars(t_data *data, short nbr, int pc);
int		write_int_mars(t_data *data, int nbr, int pc);

/*
 ** encoding_byte
 */
t_octet		*decode_encoding_byte(t_data *data, t_process *process,
		t_octet *tmp_types);
int			incorrect_encoding_byte(int op, t_octet *types);

/*
 ** get_data_from_args.c
 */
int		get_int_from_arg(t_data *d, t_process *p, t_cache *c, int arg_id);
int		get_int_from_direct_arg(t_data *d, t_process *p, t_args *arg, int idx_lim);
int		get_int_from_indirect_arg(t_data *d, t_process *p, t_args *arg, int idx_lim);

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

/*
 ** frees.c
 */
int		free_data(t_data *data);
int		exit_error(t_data *data, char* str);

/*
 ** Messages
 */
int		introduce_contestants(t_data *data);
int		victory(t_data *data);



extern	t_op	op_tab[17];

#endif
