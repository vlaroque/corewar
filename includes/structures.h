/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 00:05:33 by vlaroque          #+#    #+#             */
/*   Updated: 2020/06/26 00:09:29 by vlaroque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef union			u_subint
{
	int					nbr;
	short				short_nbr;
	t_octet				char_nbr[4];
}						t_subint;

typedef struct			s_todo
{
	t_bool				something_to_do;
	int					pc_add;
	t_bool				cmd_life;
	int					champ_id_life;
	t_bool				cmd_write_on_mars;
	int					pc;
	int					mars_content;
	t_bool				cmd_change_register;
	int					reg;
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
	char				*name;
	int					param_number;
	t_octet				types_tab[4];
	t_octet				op_code;
	int					cycle;
	char				*complete_name;
	t_octet				encoding_byte;
	int					direct_size_two;
}						t_op;

extern t_op				g_op_tab[17];

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
	int					last_live_turn;
	struct s_process	*next;
}						t_process;

/*
** champion
*/

typedef struct			s_champ
{
	int					id;
	int					n_option;
	int					champ_rank;
	char				prog_name[PROG_NAME_LENGTH + 1];
	int					prog_size;
	char				comment[COMMENT_LENGTH + 1];
	t_octet				content[CHAMP_MAX_SIZE];
	struct s_champ		*next;
}						t_champ;

typedef struct			s_data
{
	int					ac;
	char				**av;
	int					turn;
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
	int					verbosity;
	int					aff_option;
	int					c_option;
}						t_data;

#endif
