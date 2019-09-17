#compiler
CC	=	clang

#rm utils with flags
RM	=	rm -f

#compiler flags
CFLAGS	=	-I$(INCSDIR)\
			-std=c99\
			-pedantic

#linker flags
LDLIBS = 

LDFLAGS	= -L /

#--------------------------------------------------------------------------------
#source fiiles and their directory
#--------------------------------------------------------------------------------
SRCS	=	main.c Set.c
SRCSDIR	=	./

#--------------------------------------------------------------------------------
#includes fiiles and their directory
#--------------------------------------------------------------------------------
INCSDIR	=	./
INCS	=	Set.h Object.h new.h
INCS	:=	$(addprefix $(INCSDIR), $(INCS))

#--------------------------------------------------------------------------------
#object fiiles and their directory
#--------------------------------------------------------------------------------
OBJSDIR	=	./
OBJS	=	$(addprefix $(OBJSDIR), $(SRCS:.c=.o))

#--------------------------------------------------------------------------------
#name of executable
#--------------------------------------------------------------------------------
NAME	=	a.out

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(LDLIBS) $(LDFLAGS) $^ -o $@

$(OBJS): $(OBJSDIR)%.o: $(SRCSDIR)%.c | $(OBJSDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS): $(INCS)

$(OBJSDIR):
	mkdir $@

.PHONY: clean
clean:
	-$(RM) $(OBJS)

.PHONY: fclean
fclean: clean
	-$(RM) $(NAME)

.PHONY: re
re: fclean all
