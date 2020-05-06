#include "op.h"
#include "corewar.h"
#include "operation_reading.h"

static t_octet		bits_to_octet_type(t_octet two_bits)
{
	if (two_bits == 1)
		return (T_REG);
	else if (two_bits == 2)
		return (T_DIR);
	else if (two_bits == 3)
		return (T_IND);
	else
		return (0);
}

t_octet		*decode_encoding_byte(t_data *data, t_process *process,
		t_octet *tmp_types)
{
	char	c;

	c = data->mars[(process->pc + 1) % MEM_SIZE];
	tmp_types[0] = bits_to_octet_type((c >> (3 * 2)) & 3);
	tmp_types[1] = bits_to_octet_type((c >> (2 * 2)) & 3);
	tmp_types[2] = bits_to_octet_type((c >> (1 * 2)) & 3);
	tmp_types[3] = bits_to_octet_type((c >> (0 * 2)) & 3);
	return (tmp_types);
}

int			incorrect_encoding_byte(int op, t_octet *types)
{
	int			i;

	i = 0;
	while (i < op_tab[op - 1].param_number)
	{
		if (!(types[i] & op_tab[op - 1].types_tab[i]))
			return (1);
		i++;
	}
	return (0);
}
