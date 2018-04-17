SRC = ./src
OBJDIR=./obj

OBJ = $(OBJDIR)/lmt.maco $(OBJDIR)/back.maco $(OBJDIR)/write.maco $(OBJDIR)/just.maco
DEPS = $(SRC)/just.as $(SRC)/lmt.as $(SRC)/back.as $(SRC)/write.as

$(OBJDIR)/%.maco: $(DEPS)
	./macas $(SRC)/just.as &&  ./macas $(SRC)/lmt.as && ./macas $(SRC)/back.as && ./macas $(SRC)/write.as

just.mac: $(OBJ)
	mkdir -p obj
	mv ./src/lmt.maco ./src/back.maco ./src/write.maco ./src/just.maco ./obj
	./maclk just.mac $(OBJ)

clean:
	rm -r obj just.mac