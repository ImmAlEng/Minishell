
NAME	=	minishell

SRCS	=	ft_minishell.c	\
			ft_input_parser.c	\
			ft_input_parser2.c	\
			ft_input_parser3.c	\
			ft_linked_lists.c	\
			ft_linked_lists2.c	\
			ft_linked_lists3.c	\
			ft_input_check.c	\
			ft_truncate.c	\
			ft_builtins.c	\
			ft_builtins2.c	\
			ft_builtin_helper.c	\
			ft_do_operator.c	\
			ft_child.c	\
			ft_signal.c	\
			ft_init.c	\
			ft_path.c	\
			ft_free.c	\
			ft_prompt.c	\
			ft_emptystrings.c	\
			ft_quotes.c	\
			ft_make_space.c	\
			ft_truncate_helper.c	\
			ft_get_env.c

OBJS	=	$(SRCS:.c=.o)

CC		=	cc

CFLAGS	=	-Wall -Werror -Wextra -g

all :		$(NAME)

$(NAME) :	
			(cd libft && make)
			cp libft/libft.a libft.a
			$(CC) $(CFLAGS) -c $(SRCS)
			$(CC) $(CFLAGS) -g -o $(NAME) $(OBJS) libft.a -lreadline

clean :
			(cd libft && make fclean)
			rm -f $(OBJS)
			rm -f libft.a

fclean :	clean
			rm -f minishell

re :		fclean all

.PHONY:		all clean fclean re
