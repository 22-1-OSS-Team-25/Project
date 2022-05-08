CC = gcc
CFLAGS = -W -Wall

TARGET = uledger
DTARGET = uledger_debug

OBJECTS = main.c uledger.c

all : $(TARGET) $(DTARGET)

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

$(DTARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -DDEBUG -o $(DTARGET) $(OBJECTS)

clean :
	rm -f $(TARGET) $(DTARGET)
	rm -f *.o