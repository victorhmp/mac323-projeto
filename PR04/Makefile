SRCDIR = ./src
INCDIR = ./include
OBJDIR=./obj

CC=gcc
CFLAGS=-Wall -std=c99 -pedantic -O2 -Wextra -I$(INCDIR)

DEPS = $(INCDIR)/error.h $(INCDIR)/stable.h $(INCDIR)/buffer.h $(INCDIR)/mactypes.h $(INCDIR)/asmtypes.h $(INCDIR)/opcodes.h $(INCDIR)/optable.h $(INCDIR)/parser.h

OBJ = $(OBJDIR)/parse_test.o

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) -c $< $(CFLAGS)
	mkdir -p obj
	mv *.o ./obj

parse_test: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

clean:
	rm -rf parse_test $(OBJDIR)