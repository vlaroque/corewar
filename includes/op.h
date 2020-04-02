/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stherkil <stherkil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
/*   Updated: 2020/02/19 18:17:54 by stherkil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 ** Toutes les tailles sont en octets.
 ** On part du principe qu'un int fait 32 bits. Est-ce vrai chez vous ?
 */
#ifndef OP_H
#define OP_H

# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE


# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3


# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4*1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define COMMENT_CHAR			'#'
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','

# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"

# define REG_NUMBER				16

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

/*
 **
 */

typedef char	t_arg_type;

# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8

/*
 **
 */

# define PROG_NAME_LENGTH		128
# define COMMENT_LENGTH			2048
# define COREWAR_EXEC_MAGIC 0xea83f3

typedef struct		s_num
{
	int nb;
	int nb2;
	int nb3;
}					t_num;

typedef struct		labels_s
{
	char		*name;
	struct		labels_s *next;
}					labels_t;

typedef struct		instr_s
{
	int				instr;
	unsigned char	enc;
	int				totinstr;
	int				data[3];
	int				islabel[3];
	char			*labelname[3];
	int				len;
	int				ptlen;
	int				pterofinstr;
	struct		instr_s *next;
}					instr_t;

typedef struct		header_s
{
	int					lastlabelnb;
	instr_t				*instr;
	instr_t				*firstinstr;
	int					fd;
	char				prog_name[PROG_NAME_LENGTH + 1];
	unsigned int		prog_size;
	char				comment[COMMENT_LENGTH + 1];
	int					tot_len;
	int					col;
	int					row;
	int					par;
	labels_t			*labels;
}					header_t;

#endif
