SRCDIR = ./src
INCDIR = ./include
OBJDIR=./obj

CC=gcc
CFLAGS=-Wall -std=c99 -pedantic -O2 -Wextra -I$(INCDIR)

DEPS = $(INCDIR)/buffer.h

OBJ = $(OBJDIR)/buffer.o $(OBJDIR)/center.o

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) -c $< $(CFLAGS)
	mkdir -p obj
	mv *.o ./obj


center: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm -rf center $(OBJDIR)
