#  |  |  ___ \    \  |         |
#  |  |     ) |  |\/ |   _  |  |  /   _
# ___ __|  __/   |   |  (   |    <    __/
#    _|  _____| _|  _| \__,_| _|\_\ \___|
#                              by jcluzet
################################################################################
#                                     CONFIG                                   #
################################################################################

NAME        := minishell
CC        := gcc
#FLAGS    := -fsanitize=address
FLAGS       := -g -O0

################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

SRCS        :=            libft/ft_isalnum.c \
                          libft/ft_lstsize.c \
                          libft/ft_memmove.c \
                          libft/ft_lstiter.c \
                          libft/ft_isprint.c \
                          libft/ft_strdup.c \
                          libft/ft_tolower.c \
                          libft/ft_striteri.c \
                          libft/ft_split.c \
                          libft/ft_putnbr_fd.c \
                          libft/ft_lstadd_back.c \
                          libft/ft_strjoin.c \
                          libft/ft_strtrim.c \
                          libft/ft_strncmp.c \
                          libft/ft_substr.c \
                          libft/ft_strlen.c \
                          libft/ft_putendl_fd.c \
                          libft/ft_memchr.c \
                          libft/ft_lstdelone.c \
                          libft/ft_lstnew.c \
                          libft/ft_lstadd_front.c \
                          libft/ft_bzero.c \
                          libft/ft_memcpy.c \
                          libft/ft_putchar_fd.c \
                          libft/ft_putstr_fd.c \
                          libft/ft_memset.c \
                          libft/ft_strrchr.c \
                          libft/ft_toupper.c \
                          libft/ft_memcmp.c \
                          libft/ft_strmapi.c \
                          libft/ft_atoi.c \
                          libft/ft_itoa.c \
                          libft/ft_isdigit.c \
                          libft/ft_lstclear.c \
                          libft/ft_strchr.c \
                          libft/ft_strnstr.c \
                          libft/ft_strlcpy.c \
                          libft/ft_strlcat.c \
                          libft/ft_lstlast.c \
                          libft/ft_lstmap.c \
                          libft/ft_isascii.c \
                          libft/ft_isalpha.c \
                          libft/ft_calloc.c \
                          main.c \
                          lexer/lexer.c\
                          lexer/lexer_utils.c\
                          lexer/get_token_count.c\
                          lexer/assign_tokens.c\
                          lexer/assign_tokens_utils.c\
                          parser/parser.c\
                          parser/create_redirections.c\
                          parser/handle_redirection.c\
                          parser/utils.c\
                          parser/handle_connections.c\
                          parser/split_token.c\
                          parser/clear_redirections.c\
                          parser/handle_simple_command.c\
                          parser/parse_error/uses_of_parantheses.c\
                          parser/parse_error/error_utils.c\
                          parser/parse_error/parse_error.c\
                          parser/parse_error/check_parantheses.c\
                          parser/parse_error/quotes_reds.c\
                          parser/parse_error/token_error.c\
                          parser/parse_error/check_first.c\
                          parser/parse_error/check_operators.c\
                          parser/assign_operators.c\
                            parser/connection_utils.c\
                            parser/operators_utils.c\
                          expander/expander.c\
                          expander/env/handle_env.c\
                          expander/env/env_utils.c\
                          expander/env/assign_env.c\
                          expander/env/handle_node_env.c\
                          expander/env/delete_quotes.c\
                          expander/wildcard/wildcard.c\
                          expander/wildcard/handle_node_wildcard.c\
                          expander/wildcard/command.c\
                          expander/wildcard/args.c\
                          expander/wildcard/utils.c\
                          expander/wildcard/right_side.c\
                          expander/wildcard/left_side.c\
                          expander/wildcard/middle.c\
                          expander/wildcard/match_arg_files.c\
                          expander/wildcard/command_file.c\
                          expander/env/assign_env_utils.c\
                          execute/execute.c\
                          execute/builtins/cd.c\
                          execute/builtins/echo.c\
                          execute/builtins/pwd.c\
                          execute/builtins/env.c\
                          execute/builtins/export.c\
                            execute/builtins/unset.c\
                            execute/builtins/exit.c\
                            execute/builtins/utils.c\


OBJS        := $(SRCS:.c=.o)

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

################################################################################
#                                  Makefile  objs                              #
################################################################################


CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m
RM		    := rm -f

${NAME}:	${OBJS}
			@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
			${CC} ${FLAGS} -o ${NAME} ${OBJS} -lreadline
			@echo "$(GREEN)$(NAME) created[0m ✔️"

all:		${NAME}

bonus:		all

clean:
			@ ${RM} *.o */*.o */*/*.o
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"

fclean:		clean
			@ ${RM} ${NAME}
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"

re:			fclean all

.PHONY:		all clean fclean re
