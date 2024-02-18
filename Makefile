NAME	=	germanVoc

LIBFTPATH	=	./libft
LIBFT		=	$(LIBFTPATH)/libft.a
SRCDIR		=	src
SRCS		=	$(SRCDIR)/main.c	$(SRCDIR)/utils.c	$(SRCDIR)/run.c \
				$(SRCDIR)/files.c	$(SRCDIR)/guess_prioritary.c
OBJDIR		=	.obj
OBJS		=	$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

CC		=	cc
FLAGS	=	-Wall -Wextra -Werror -g3

all			:	$(OBJDIR) $(OBJS) $(LIBFT) $(NAME)

$(OBJDIR)	:
	@mkdir $(OBJDIR)

$(OBJDIR)/%.o	:		$(SRCDIR)/%.c
	@echo -n "Compiling " $< " ... "
	@$(CC) $(FLAGS) -c $< -o $@
	@echo -e '\x1b[32m>>> OK <<<\x1b[37m'

$(LIBFT)	:
	@make -sC $(LIBFTPATH)

$(NAME)		:	$(OBJS) $(LIBFT)
	@clear
	@echo -e '\033[0;34mObjects compilation : \x1b[32m>>> OK <<<\x1b[37m'
	@echo -e '\033[0;34mCompiling executable ...\x1b[37m'
	@$(CC) $(FLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@clear

clean		:
	@echo -e '\033[0;34mRemoving object files ...\x1b[37m'
	@rm -rf $(OBJDIR)
	@make -C $(LIBFTPATH) clean
	@echo -e '\x1b[32m>>> OK <<<\x1b[37m'

fclean		:	clean
	@echo -e '\033[0;34mRemoving executable ...\x1b[37m'
	@rm -f $(NAME)
	@make -C $(LIBFTPATH) fclean
	@echo -e '\x1b[32m>>> OK <<<\x1b[37m'

re		:	fclean all