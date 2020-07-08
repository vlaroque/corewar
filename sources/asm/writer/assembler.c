#include "asm.h"

static inline void		write_parameters(t_inst_info *schema, t_file *file, t_token *start, t_token *token)
{
	uint32_t		value;
	t_bool			is_ref;
	size_t			dir_size;

	dir_size = get_dir_size(schema->opcode);
	while (is_parameter(token))
	{
		is_ref = ((token->type & T_REF) == T_REF);
		if (token->type == T_REG)
		{
			value = (uint32_t)ft_atoi(token->content + 1);
			write_buffer(file, (char*)&value, 1);
		}
		if (is_ref)
			value = resolve_reference(start, token);
		if ((token->type & T_DIR) == T_DIR)
		{
			if (!is_ref)
				value = (uint32_t)ft_atoi(token->content);
			dir_size == 4 ? to_big_endian32((char*)&value) : to_big_endian16((char*)&value);
			write_buffer(file,(char*) &value, dir_size);
		}
		if ((token->type & T_IND) == T_IND)
		{
			if (!is_ref)
				value = (uint32_t)ft_atoi(token->content);
			to_big_endian16((char*)&value);
			write_buffer(file, (char*)&value, IND_SIZE);
		}
		token = token->next;
	}
}

static inline void		write_bytecode(t_file *file, t_token *token)
{
	t_inst_info		*schema;
	uint8_t			opc;
	t_token			*start;

	start = token;
	while (token)
	{
		if (token->type == T_MNE)
		{
			schema = get_token_schema(token);
			opc = get_opc(schema, token->next);
			write_buffer(file, (char*)&schema->opcode, 1);
			if (ocp_required(schema->opcode))
					write_buffer(file, (char*)&opc, 1);
			write_parameters(schema, file, start, token->next);
		}
		token = token->next;
	}
}

static inline char			*get_symbol(t_token *token, char *symbol_name)
{
	uint32_t		value;

	value = *(uint32_t*)symbol_name;
	while (token)
	{
		if ((*(uint32_t*)token->content & value) == value)
		{
			if (token->next && token->next->type == T_STR)
					return (token->next->content);
		}
		token = token->next;
	}
	return (NULL);
}

static inline t_header *get_header(t_file *file, t_token *token)
{
		t_header *header;
		char	*name;
		char	*comment;

		header = (t_header*)ft_memalloc(sizeof(t_header));
		if (!header)
			return (NULL);
		name = get_symbol(token, NAME_CMD_STRING);
		comment = get_symbol(token, COMMENT_CMD_STRING);
		if (!name)
			display_missing_field(NAME_CMD_STRING);
		else if (!comment)
			display_missing_field(COMMENT_CMD_STRING);
		else {
			header->magic = COREWAR_EXEC_MAGIC;
			ft_strcpy(header->prog_name, name);
			ft_strcpy(header->comment, comment);
			ft_memcpy(&header->prog_size, &file->size,sizeof(unsigned int));
			to_big_endian32((char*)&header->magic);
			to_big_endian32((char*)&header->prog_size);
			return (header);
		}
		free(header);
		return (NULL);
}

void		assemble(char *filename, t_token *token)
{
		t_file   *file;
		t_header *header;

		file = init_file();
		if (!file)
			return (display_allocation_error());
		write_bytecode(file, token);
		if (file->buffer)
		{
			if ((header = get_header(file, token)))
			{
				load_file(file, filename);
				write(file->fd, header, sizeof(t_header));
				free(header);
				file_flush(file);
			}
		}
		else
			display_allocation_error();
		clear_file(file);
}