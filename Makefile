#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/20 10:05:51 by zadrien           #+#    #+#              #
#    Updated: 2019/10/24 23:04:42 by zadrien          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

.PHONY: all clean fclean name re

CC= gcc
SNAME= nm-otool
CFLAGS= -g -Wall -Werror -Wextra
CPATH= srcs/
OPATH= obj/
HPATH= includes/ libft/includes/
INC= $(addprefix -I , $(HPATH))
SFILES= main.c nm.c options.c\
	/commands/symtab.c  commands/stabs.c\

OSFILES= $(SFILES:.c=.o)

HFILES= libft/includes/libft.h	\
		includes/nm.h \

SOBJ= $(addprefix $(OPATH), $(OSFILES))

all: $(SNAME) $(CNAME)

$(SNAME): $(SOBJ)
	make -C libft
	$(CC) $(CFLAGS) $(SOBJ) libft/libft.a -o $(SNAME)

$(OPATH)%.o: $(CPATH)%.c $(HFILES)
	@mkdir -p $(OPATH)
	@mkdir -p $(OPATH)/commands
	$(CC) -g -Wall -Werror -Wextra  $(INC) $< -c -o $@

clean:
	make -C libft clean
	rm -rf $(SOBJ)

fclean: clean
	make -C libft fclean
	rm -rf $(SNAME)
	rm -rf $(OPATH)

re: fclean all

norme:
		@norminette srcs/**/**.[ch]
		@norminette libft/*.[ch]

