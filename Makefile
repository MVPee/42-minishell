NAME = minishell

LIBFT = srcs/libft

SRCS = 	srcs/minishell/main.c \
		srcs/minishell/env/env_init.c \
		srcs/minishell/env/env_operations.c \
		srcs/minishell/builtins/echo.c

OBJS = $(SRCS:.c=.o)

CFLAGS = -I$(LIBFT) #-ggdb3 -fsanitize=address -g #-Wall -Werror -Wextra
LDFLAGS = -L$(LIBFT) -lft -lreadline# -ggdb3 -fsanitize=address -g

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