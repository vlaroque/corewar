# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlaroque <vlaroque@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/20 10:33:13 by vlaroque          #+#    #+#              #
#    Updated: 2020/07/10 21:35:27 by vlaroque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# GLOBAL

NAME1 = asm
NAME2 = corewar
CC = clang
CFLAGS = -Wextra -Werror -Wall 

#-fsanitize=address#
# SOURCES

SRC_ASM = main.c writer/assembler.c writer/helpers.c writer/resolution.c \
		writer/writer.c writer/display.c parser/parser.c \
		parser/analyse.c parser/checker.c parser/display.c tokens.c \
		utils/file.c utils/read_file.c utils/del_useless.c utils/free_tab.c
SRC_VM = main.c debug.c battle.c champ_load.c init_corewar.c process_new.c\
		operation_reading.c functions.c operation_execution.c read_mars.c\
		write_mars.c op_just_next.c pre_execute_operation.c encoding_byte.c\
		get_data_from_args.c check.c frees.c messages.c it_functions.c\
		todo_functions.c buff_mars.c init_errors.c verbosity.c\
		op_loads.c op_arithmetics.c op_stores.c op_jump_n_fork.c\
		op_live_aff_badenc.c buff_mars_color.c visual_operations.c\
		v_stores.c verbose_utility.c
SRC_COMMON = op.c

# PATH

SRC_PATH = sources
OBJ_PATH = obj
INC_PATH = "includes"
INC_LIBFT = "-Ilibft/includes"

ASM_PATH = asm
VM_PATH = vm
COMMON_PATH = common

# ASSIGNATION

ASM_SRC_FILES = $(addprefix $(ASM_PATH)/,$(SRC_ASM))
ASM_SRC_FILES += $(addprefix $(COMMON_PATH)/,$(SRC_COMMON))
VM_SRC_FILES = $(addprefix $(COMMON_PATH)/,$(SRC_COMMON))
VM_SRC_FILES += $(addprefix $(VM_PATH)/,$(SRC_VM))

ASM_OBJ = $(addprefix $(OBJ_PATH)/,$(ASM_SRC_FILES:.c=.o))
VM_OBJ = $(addprefix $(OBJ_PATH)/,$(VM_SRC_FILES:.c=.o))

EPENDS = $(ASM_OBJ:%.o=%.d)
DEPENDS += $(VM_OBJ:%.o=%.d)

# LIBRARIES
LIBFT = libft/libft.a

.PHONY: all
all : $(NAME1) $(NAME2)

$(NAME1) : $(ASM_OBJ) $(LIBFT)
	@echo "\tLinking $@'s files"
	@$(CC) $(ASM_OBJ) -o $@ $(CFLAGS) -lft -L libft
	@echo "\t\tDone !"

$(NAME2) : $(VM_OBJ) $(LIBFT)
	@echo "\tLinking $@'s files"
	@$(CC) $(VM_OBJ) -o $@ $(CFLAGS) -lft -L libft
	@echo "\t\tDone !"

$(LIBFT):
	@echo "\t\tMaking Libft !"
	@make -C libft

-include $(DEPENDS)
$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	@mkdir -p $(@D)
	@echo "\tCompiling $@"
	@$(CC) $(CFLAGS) -I$(INC_PATH) $(INC_LIBFT) -Ilibft -MMD -c $< -o $@

.PHONY: clean
clean :
	@echo "\tCleaning..."
	@rm -Rf obj
	@echo "\t\tDone !"
	@make -C libft clean

.PHONY: fclean
fclean : clean
	@rm -Rf $(NAME1) $(NAME2)
	@make -C libft fclean

.PHONY: re
re :
	@$(MAKE) fclean
	@$(MAKE)

git :
	@$(MAKE) fclean
	@git add .
