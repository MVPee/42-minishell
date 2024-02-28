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
		srcs/minishell/builtins/exit.c \
		srcs/minishell/builtins/utils/export_utils.c \
		srcs/minishell/builtins/utils/export_sort.c \
		srcs/minishell/builtins/cd.c \
		srcs/minishell/process/process.c \
		srcs/minishell/parsing/parsing.c \
		srcs/minishell/parsing/utils.c \
		srcs/minishell/signal/init_signal.c

OBJS = $(SRCS:.c=.o)

CFLAGS = -I$(LIBFT) #-ggdb3 -fsanitize=address -g #-Wall -Werror -Wextra
LDFLAGS = -L$(LIBFT) -lft -lreadline #-ggdb3 -fsanitize=address -g

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