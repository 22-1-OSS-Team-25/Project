CC = gcc
CFLAGS = -W -Wall

TARGET = uledger
DTARGET = uledger_debug

OBJECTS = main.c uledger.c

all : $(TARGET) $(DTARGET)

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

$(DTARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -DDEBUG -o $@ $^

clean :
	rm -f $(TARGET) $(DTARGET)
	rm -f *.o