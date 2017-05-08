CC = gcc
CFLAGS =
FILES = new.c setup.c
OBJECTS = $(FILES:%.c=%.o)

.PHONY : all
all : $(OBJECTS)
	@ $(CC) $(CFLAGS) $(OBJECTS) -o ../new

.SILENT : $(OBJECTS)
$(OBJECTS) :
