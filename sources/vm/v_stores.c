#include "corewar.h"

int				v_st(t_data *data, t_process *process, t_cache *c)
{
	int		tostore;

	if (!(data->verbosity & 4))
		return (0);
	tostore = process->reg[c->args[0].octet_data];
	verbose_operations(data, process);
	show_reg_elsif_number(data, &c->args[0], tostore);
	verbose_space(data);
	show_reg_elsif_number(data, &c->args[1], (int)c->args[1].short_data);
	verbose_opertation_end(data, process);
	return (0);
}

static int		sti_second_line(int first, int second, int where)
{
	ft_putstr("       | -> store to ");
	ft_putnbr(first);
	ft_putstr(" + ");
	ft_putnbr(second);
	ft_putstr(" = ");
	ft_putnbr(first + second);
	ft_putstr(" (with pc and mod ");
	ft_putnbr(where);
	ft_putstr(")");
	return (0);
}

int				v_sti(t_data *data, t_process *process, t_cache *c)
{
	int		what;
	int		first;
	int		second;
	int		where;

	if (!(data->verbosity & 4))
		return (0);
	what = process->reg[c->args[0].octet_data];
	first = get_int_from_indirect_arg(data, process, &c->args[1], 1);
	second = get_int_from_indirect_arg(data, process, &c->args[2], 1);
	where = (process->pc + ((first + second) % IDX_MOD)) % MEM_SIZE;

	verbose_operations(data, process);
	show_reg_elsif_number(data, &c->args[0], -1);
	verbose_space(data);
	verbose_putnbr(data, first);
	verbose_space(data);
	verbose_putnbr(data, second);
	verbose_opertation_end(data, process);
	sti_second_line(first, second, where);
	verbose_opertation_end(data, process);
	return (0);
}

static int		ldi_second_line(int first, int second, int where, int l)
{
	ft_putstr("       | -> load from ");
	ft_putnbr(first);
	ft_putstr(" + ");
	ft_putnbr(second);
	ft_putstr(" = ");
	ft_putnbr(first + second);
	if (l)
		ft_putstr(" (with pc ");
	else
		ft_putstr(" (with pc and mod ");
	ft_putnbr(where);
	ft_putstr(")");
	return (0);
}


int				v_ldi(t_data *data, t_process *process, t_cache *c)
{
	int		first;
	int		second;
	int		where;
	int		res;

	if (!(data->verbosity & 4))
		return (0);
	first = get_int_from_indirect_arg(data, process, &c->args[0], 1);
	second = get_int_from_indirect_arg(data, process, &c->args[1], 1);
	where = (process->pc + ((first + second) % IDX_MOD)) % MEM_SIZE;
	res = read_int_mars(data, where);
	verbose_operations(data, process);
	verbose_putnbr(data, first);
	verbose_space(data);
	verbose_putnbr(data, second);
	verbose_space(data);
	show_reg_elsif_number(data, &c->args[2], -1);
	verbose_opertation_end(data, process);
	ldi_second_line(first, second, where, 0);
	verbose_opertation_end(data, process);
	return (0);
}

int				v_lldi(t_data *data, t_process *process, t_cache *c)
{
	int		first;
	int		second;
	int		where;
	int		res;

	if (!(data->verbosity & 4))
		return (0);
	first = get_int_from_indirect_arg(data, process, &c->args[0], 0);
	second = get_int_from_indirect_arg(data, process, &c->args[1], 0);
	where = (process->pc + first + second);
	res = read_int_mars(data, where);
	verbose_operations(data, process);
	verbose_putnbr(data, first);
	verbose_space(data);
	verbose_putnbr(data, second);
	verbose_space(data);
	show_reg_elsif_number(data, &c->args[2], -1);
	verbose_opertation_end(data, process);
	ldi_second_line(first, second, where, 1);
	verbose_opertation_end(data, process);
	return (0);
}
