TARGET := dbgen
OBJECTS := dbgen.o

CC := gcc
CFLAGS := -Wall -O2 -std=c99

.SUFFIXES: .c .o

.c.o:
	$(CC) $(CFLAGS) -c $<

.PHONY: all clean

all: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $^

clean:
	rm -f $(TARGET) $(OBJECTS)
