#ifndef OPERATION_READING_H
# define OPERATION_READING_H

typedef struct			s_args
{
	t_octet		type;
	int			size;
	t_octet		octet_data;
	short		short_data;
	int			int_data;
}						t_args;

typedef struct			s_cache
{
	int			op;
	int			pc_delta;
	int			nb_args;
	t_octet		types[4];
	t_args		args[4];
	int			bad_encoding_byte;
}						t_cache;

# endif
