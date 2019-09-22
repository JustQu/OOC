#compiler
CC	=	clang

#rm utils with flags
RM	=	rm -f

#compiler flags
CFLAGS	=	-I$(INCSDIR)\
			-I$(ATOM_INCSDIR)\
			-I$(STRING_INCSDIR)\
			-std=c99\
			-pedantic

#linker flags
LDLIBS =

LDFLAGS	= -L ./

#--------------------------------------------------------------------------------
#source fiiles and their directory
#--------------------------------------------------------------------------------
SRCS	=	main.c new.c
SRCSDIR	=	./

ATOM_SRCS = Atom.c
ATOM_SRCSDIR = ./

STRING_SRCS = String.c
STRING_SRCSDIR = ./

#--------------------------------------------------------------------------------
#includes fiiles and their directory
#--------------------------------------------------------------------------------
INCSDIR	=	./
INCS	=	new.h new.r
INCS	:=	$(addprefix $(INCSDIR), $(INCS))

ATOM_INCSDIR = ./
ATOM_INCS = String.h
ATOM_INCS := $(addprefix $(ATOM_INCSDIR), $(ATOM_INCS))

STRING_INCS = String.h
STRING_INCSDIR = ./

#--------------------------------------------------------------------------------
#object fiiles and their directory
#--------------------------------------------------------------------------------
OBJSDIR	=	./objs/
OBJS	=	$(addprefix $(OBJSDIR), $(SRCS:.c=.o))

ATOM_OBJSDIR = $(OBJSDIR)atom_objs/
ATOM_OBJS = $(addprefix $(ATOM_OBJSDIR), $(ATOM_SRCS:.c=.o))

STRING_OBJSDIR =  $(OBJSDIR)string_objs/
STRING_OBJS = $(addprefix $(STRING_OBJSDIR), $(STRING_SRCS:.c=.o))

#--------------------------------------------------------------------------------
#name of executable
#--------------------------------------------------------------------------------
ATOM	=	atom
STRING	=	string

.PHONY: all
all: $(ATOM) $(STRING)

$(ATOM): $(OBJS) $(ATOM_OBJS)
	$(CC) $(LDLIBS) $(LDFLAGS) $^ -o $@

$(STRING): $(OBJS) $(STRING_OBJS)
	$(CC) $(LDLIBS) $(LDFLAGS) $^ -o $@

$(OBJS): $(OBJSDIR)%.o: $(SRCSDIR)%.c | $(OBJSDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJS): $(INCS)

$(ATOM_OBJS): $(ATOM_OBJSDIR)%.o: $(ATOM_SRCSDIR)%.c | $(ATOM_OBJSDIR)
	$(CC) $(CFLAGS) -c -o $@ $<  

$(STRING_OBJS): $(ATOM_INCS) $(INCS)

$(STRING_OBJS): $(STRING_OBJSDIR)%.o: $(STRING_SRCSDIR)%.c | $(STRING_OBJSDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(STRING_OBJS): $(STRING_INCS) $(INCS)

$(OBJSDIR):
	mkdir $@

$(ATOM_OBJSDIR):
	mkdir $@

$(STRING_OBJSDIR):
	mkdir $@

.PHONY: clean
clean:
	-$(RM) $(OBJS) $(ATOM_OBJS) $(STRING_OBJS)

.PHONY: fclean
fclean: clean
	-$(RM) $(ATOM) $(STRING)

.PHONY: re
re: fclean all
