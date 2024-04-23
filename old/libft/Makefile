#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anvincen <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/11 15:03:29 by anvincen          #+#    #+#              #
#    Updated: 2022/11/28 16:10:01 by anvincen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a
SRCS	=	ft_isalnum.c ft_isprint.c ft_memcmp.c  ft_putchar_fd.c ft_split.c \
			ft_strlcat.c ft_strncmp.c ft_substr.c ft_atoi.c ft_isalpha.c \
			ft_itoa.c ft_memcpy.c  ft_putendl_fd.c ft_strchr.c  ft_strlcpy.c \
			ft_strnstr.c ft_tolower.c ft_bzero.c   ft_isascii.c \
			ft_memmove.c ft_putnbr_fd.c  ft_strdup.c  ft_strlen.c \
			ft_strrchr.c ft_toupper.c ft_calloc.c  ft_isdigit.c ft_memchr.c \
			ft_memset.c ft_putstr_fd.c  ft_strjoin.c ft_strmapi.c \
			ft_strtrim.c ft_striteri.c \
			ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
			ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
			ft_lstclear.c ft_lstiter.c ft_lstmap.c \

FLAGS	=	-Werror -Wall -Wextra -g3

OBJDIR	=	.obj
OBJS	=	$(SRCS:.c=.o)


all:		$(OBJDIR) $(OBJS) $(NAME)

$(OBJDIR)	:
	@mkdir $(OBJDIR)


$(OBJDIR)/%.o	:		$(SRCDIR)/%.c
		@cc $(FLAGS) -c $< -o $@


$(NAME):	$(OBJS)
		@ar rcs $(NAME) $(OBJS)

clean:
		@rm -rf $(OBJDIR)
		@rm -f $(OBJS)

fclean:		clean
		@rm -f $(NAME)

re:			fclean	all
