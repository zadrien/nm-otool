# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/11 16:22:07 by zadrien           #+#    #+#              #
#    Updated: 2020/01/29 18:58:11 by zadrien          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean name re

CC= gcc
NM_NAME= nm
OTOOL_NAME= otool
CFLAGS= -g -Wall -Werror -Wextra
CPATH= srcs/
OPATH= obj/
HPATH= includes/ libft/includes/
INC= $(addprefix -I , $(HPATH))

COMMON_FILES= 	common/flags.c common/check_file.c common/map_file.c \
				common/archive.c common/swap.c common/swap2.c common/misc.c \
				common/section.c \

NM_FILES= 	nm/main.c nm/nm.c nm/section.c nm/section_utils.c nm/archive.c \
			nm/fat.c nm/print.c nm/commands/symtab.c  nm/commands/stabs.c \
			nm/commands/symbol.c nm/commands/sort.c nm/print_utils.c \

OTOOL_FILES= otool/main.c otool/otool.c otool/section.c otool/section_utils.c \
			otool/print.c otool/utils.c otool/otool_ar.c \

NM_OFILES= $(NM_FILES:.c=.o)
OTOOL_OFILES= $(OTOOL_FILES:.c=.o)
COMMON_OFILES= $(COMMON_FILES:.c=.o)

HFILES= libft/includes/libft.h	\
		includes/nm.h \
		includes/otool.h \
		includes/common.h \


NM_OBJ= $(addprefix $(OPATH), $(NM_OFILES))
OTOOL_OBJ= $(addprefix $(OPATH), $(OTOOL_OFILES))
COMMON_OBJ= $(addprefix $(OPATH), $(COMMON_OFILES))

all: $(NM_NAME) $(OTOOL_NAME)

$(NM_NAME): $(NM_OBJ) $(COMMON_OBJ)
	make -C libft
	$(CC) $(CFLAGS) -ltermcap $(NM_OBJ) $(COMMON_OBJ) libft/libft.a -o $(NM_NAME)

$(OTOOL_NAME): $(OTOOL_OBJ) $(COMMON_OBJ)
	$(CC) $(CFLAGS) -ltermcap $(OTOOL_OBJ) $(COMMON_OBJ) libft/libft.a -o $(OTOOL_NAME)

$(OPATH)%.o: $(CPATH)%.c $(HFILES)
	@mkdir -p $(OPATH)nm/commands
	@mkdir -p $(OPATH)otool/
	@mkdir -p $(OPATH)common/

	$(CC) $(CFLAGS)  $(INC) $< -c -o $@

clean:
	make -C libft clean
	rm -rf $(NM_OBJ) $(OTOOL_OBJ)

fclean: clean
	make -C libft fclean
	rm -rf $(NM_NAME) $(OTOOL_NAME)
	rm -rf $(OPATH)

re: fclean all

norme:
		@norminette srcs/**/**.[ch]
		@norminette libft/**/*.[ch]

