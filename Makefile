NAME	=	21sh
FILES	=	built_in exec_list ft_built_cd ft_built_env main parser\
			readline_sh sort utils utils2 utils3 utils4 utils5\
			do_cmd_shellrev ft_split_pipes ft_calc_full_path\
			ft_redir_2less ft_redir_great ft_redir_less \
			ft_test_pipes ft_test_redir redir_io_rest utils_dup\
			utils_great utils_great2 utils_pipe utils_pipe2 utils_pipe3\
			utils_pipe_split utils_pipe_split2 utils_great3\
			ft_get_less_tst hash heredoc ft_replace exec_list2\
			ft_built_cd2 locals ft_built_env2 ft_built_env3 \
			ft_built_env4 ft_replays_subs hash_cmd hash_cmd_add

SRC_D	=	srcs
INC_D	=	includes
LIB_D	=	libft
LIB_D2	=	readline
SRC		=	$(patsubst %,$(SRC_D)/%.c,$(FILES))
OBJ		=	$(patsubst %,%.o,$(FILES))
FLAGS	= -g -Wall -Wextra -Werror
LIB_LNK =	-L $(LIB_D) -lft readline/readline.a -ltermcap

all: $(NAME)

$(NAME):
	@make -C $(LIB_D)
	@make -C $(LIB_D2)
	@gcc $(FLAGS) -I $(INC_D) -I $(LIB_D)  -c $(SRC)
	@gcc -g -o $(NAME) $(OBJ) $(LIB_LNK) -lreadline

clean:
	@make -C $(LIB_D) clean
	@make -C $(LIB_D2) clean
	@rm -f $(OBJ)

fclean: clean
	@make -C $(LIB_D) fclean
	@make -C $(LIB_D2) fclean
	@rm -f $(OBJ)
	@rm -f $(NAME)

re: fclean all