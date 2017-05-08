CC = gcc
CFLAGS =
FILES = new.c setup.c
OBJECTS = $(FILES:%.c=%.o)

.PHONY : all clean
all : $(OBJECTS)
	@ $(CC) $(CFLAGS) $(OBJECTS) -o ../new

clean:
	@ rm -rf $(OBJECTS) ../new

.SILENT : $(OBJECTS)
$(OBJECTS) :
