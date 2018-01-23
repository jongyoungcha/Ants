CC=gcc
OBJS=str2hex.o test_main.o
TARGET=test_main

.SUFFIXES : .c .o

all : $(TARGET)


$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS)

clean :
	rm -f $(OBJS) $(TARGET)

