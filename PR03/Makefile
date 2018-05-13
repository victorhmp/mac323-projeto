SRCDIR = ./src
INCDIR = ./include
OBJDIR=./obj

CC=gcc
CFLAGS=-Wall -std=c99 -pedantic -O2 -Wextra -I$(INCDIR)

DEPS = $(INCDIR)/stable.h

OBJ = $(OBJDIR)/stable.o $(OBJDIR)/freq.o

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) -c $< $(CFLAGS)
	mkdir -p obj
	mv *.o ./obj

freq: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

clean:
	rm -rf freq $(OBJDIR)