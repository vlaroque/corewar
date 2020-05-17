#include "corewar.h"

int		write_oct_mars(t_data *data, t_octet c, int pc)
{
	pc = pc_fix(pc);
	data->mars[pc % MEM_SIZE] = c;
	return (0);
}

int		write_short_mars(t_data *data, short nbr, int pc)
{
	t_subint temp;
	
	pc = pc_fix(pc);
	temp.short_nbr = nbr;
	write_oct_mars(data, temp.char_nbr[1], pc);
	write_oct_mars(data, temp.char_nbr[0], pc + 1);
	return (0);
}

int		write_int_mars(t_data *data, int nbr, int pc)
{
	t_subint temp;
	
	pc = pc_fix(pc);
	temp.nbr = nbr;
	write_oct_mars(data, temp.char_nbr[3], pc);
	write_oct_mars(data, temp.char_nbr[2], pc + 1);
	write_oct_mars(data, temp.char_nbr[1], pc + 2);
	write_oct_mars(data, temp.char_nbr[0], pc + 3);
	return (0);
}
