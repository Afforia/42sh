# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wveta <wveta@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/20 13:59:52 by thaley            #+#    #+#              #
#    Updated: 2019/08/31 18:40:22 by wveta            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = readline.a
FILES = autocomplition cursor history init\
		input match_key move_char move_line\
		readline signal ft_free ascii_sort\
		cut_paste get_next_line print_tab\
		search_tab copy space recurs_search\
		update_hist history_back_n ft_exit insert_char\
		delete parsepath mall_check
		
SRC_D = .
SRC	= $(patsubst %,$(SRC_D)/%.c,$(FILES))
OBJ	= $(patsubst %,%.o,$(FILES))

all: ${NAME}

${NAME}:
	gcc -g -Wall -Wextra -Werror -I ../libft -c $(SRC)
	@ar rc ${NAME} ${OBJ}
	@ranlib ${NAME}

so:
	@gcc -shared -o readline.so -fPIC *.c -I ../libft

clean:
	@rm -f ${OBJ}

fclean: clean
	@rm -f ${NAME}

re: fclean all
