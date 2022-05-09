CC = gcc
CFLAGS = -W -Wall

TARGET = uledger
OBJECTS = main.c uledger.c

all : $(TARGET)

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

clean :
	rm -f $(TARGET)
	rm -f *.o
	rm -f $(TARGET).txt