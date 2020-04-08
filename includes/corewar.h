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
# include "libft.h"
typedef unsigned long long	t_llu;
# include "common.h"
typedef unsigned char		t_octet;
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

typedef struct			s_todo
{
	t_bool				something_to_do;
	int					pc_add;
	t_bool				life_cmd;
	int					champ_id_life;
	t_bool				cmd_write_on_mars;
	int					mars_content;
	t_bool				cmd_change_register;
	int					reg_content;
	t_bool				cmd_change_carry;
	int					carry_content;
	t_bool				cmd_fork;
	int					fork_pc;
	t_bool				cmd_aff;
	t_octet				char_to_aff;
}						t_todo;

typedef struct			s_op
{
	char		*name;
	int			param_number;
	t_octet		param_possible_types[4];
	t_octet		op_code;
	int			cycle;
	char		*complete_name;
	t_octet		encoding_byte;
	int			direct_size_two;
}						t_op;

//# include "../sources/common/op.c"

typedef struct			s_process
{
	int					id;
	t_reg				pc;
	unsigned int		carry;
	t_reg				reg[REG_NUMBER];
	t_todo				todo;
	int					cooldown;
	int					life;
	struct s_process	*next;
}						t_process;

/*
** used for bonus of champs number id
*/

typedef struct			s_champid
{
	int					id;
	int					carry;
	int					carried_nbr;
}						t_champid;


/*
** champion
*/

typedef struct			s_champ
{
	int					id;
	t_octet				prog_name[PROG_NAME_LENGTH + 1];
	unsigned int		prog_size;
	t_octet				comment[COMMENT_LENGTH + 1];
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
	int					lives_count;
}						t_data;

/*
** debug
*/
int			show_mars(t_data *data);
int			battle(t_data *data);
void		hex_dump(t_octet *src, size_t len);
int			champ_dump(t_champ *champ);
int			buff_mars(t_data *data);
int			err(char *s);
int			debug_process(t_process *process);
int			debug_global(t_data *data, int turn);

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
 ** operation_reading
 */
j
int		read_operation(t_data *data, t_process *process);

/*
 ** op_exe
 */

int		execute_operation(t_data *data, t_process *process)

/*
 ** differents functions
 */
int		op_live(t_data *data, t_process *process);
int		op_ld(t_data *data, t_process *process);
int		op_st(t_data *data, t_process *process);
int		op_add(t_data *data, t_process *process);
int		op_sub(t_data *data, t_process *process);
int		op_and(t_data *data, t_process *process);
int		op_or(t_data *data, t_process *process);
int		op_xor(t_data *data, t_process *process);
int		op_zjmp(t_data *data, t_process *process);
int		op_ldi(t_data *data, t_process *process);
int		op_sti(t_data *data, t_process *process);
int		op_fork(t_data *data, t_process *process);
int		op_lld(t_data *data, t_process *process);
int		op_lldi(t_data *data, t_process *process);
int		op_lfork(t_data *data, t_process *process);
int		op_aff(t_data *data, t_process *process);

#endif
