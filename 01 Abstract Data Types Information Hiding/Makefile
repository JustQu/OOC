#compiler
CC	=	clang

#rm utils with flags
RM	=	rm -f

#compiler flags
CFLAGS	=	-I$(INCSDIR)\
			-std=c99\
			-pedantic

#linker flags
LDFLAGS	= 

SRCS	=	main.c Set.c
SRCSDIR	=	./

INCS	=	Set.h Object.h new.h
INCSDIR	=	./

OBJS	=	$(SRCS:.c=.o)
OBJSDIR	=	./

NAME	=	a.out

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS) 
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJS): $(OBJSDIR)%.o: $(SRCSDIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS): $(INCS)

.PHONY: clean
clean:
	$(RM) $(OBJS)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)

.PHONY: re
re: fclean all