NAME = minishell

LIBFT = srcs/libft

SRCS = 	srcs/minishell/main.c \
		srcs/minishell/env/env_init.c \
		srcs/minishell/env/env_operations.c \
		srcs/minishell/env/env_conversion.c \
		srcs/minishell/env/env_utils.c \
		srcs/minishell/builtins/builtins.c \
		srcs/minishell/builtins/echo.c \
		srcs/minishell/builtins/env.c \
		srcs/minishell/builtins/pwd.c \
		srcs/minishell/builtins/unset.c \
		srcs/minishell/builtins/export.c \
		srcs/minishell/builtins/utils/export_utils.c \
		srcs/minishell/builtins/utils/export_sort.c \
		srcs/minishell/builtins/cd.c \
		srcs/minishell/process/process.c \
		srcs/minishell/lexer/lexer.c \
		srcs/minishell/lexer/lexer_utils.c \
		srcs/minishell/signal/init_signal.c \
		srcs/minishell/parsing/parsing.c \
		srcs/minishell/parsing/checker.c \
		srcs/minishell/parsing/path_checker.c \
		srcs/minishell/parsing/utils_parsing.c \
		srcs/minishell/parsing/get_args.c

OBJS = $(SRCS:.c=.o)

CFLAGS = -I$(LIBFT) -g -ggdb3 -fsanitize=address #-Wall -Werror -Wextra
LDFLAGS = -L$(LIBFT) -lft -lreadline -g -ggdb3 -fsanitize=address

RED=\033[0;31m
GREEN=\033[0;32m
NC=\033[0m

all: $(NAME)

$(LIBFT)/libft.a:
	$(MAKE) -C $(LIBFT) 

$(NAME): $(OBJS) $(LIBFT)/libft.a
	@gcc $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "\n${RED}███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     ${NC}"
	@echo   "${RED}████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     ${NC}"
	@echo   "${RED}██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     ${NC}"
	@echo   "${RED}██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     ${NC}"
	@echo   "${RED}██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗${NC}"
	@echo   "${RED}╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝${NC}"
	@echo   "${GREEN}./minishell${NC}\n"

%.o: %.c
	@gcc $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT) clean
	@rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT) fclean
	@rm -f $(NAME)

re: fclean all

run: all
	./$(NAME)

.PHONY: all clean fclean re