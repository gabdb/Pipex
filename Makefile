NAME = pipex

LIBFT = libft/libft.a

CC = cc

CFLAGS = -Werror -Wall -Wextra

RM = rm -rf

SRCS =	source/parse.c \
		source/path.c	\
		source/pipex.c	\
		source/free_exit.c	\
		source/support_funct.c	\

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT)

$(LIBFT) :
	@make -C libft

%.o : %.c
	@$(CC) -o $@ -c $<

fclean : clean
	@make fclean -C libft
	@$(RM) $(NAME)

clean :
	@make clean -C libft
	@$(RM) $(OBJS)

re : fclean all
