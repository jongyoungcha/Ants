CC = gcc

OBJS = test_main.o chk_num.o

TARGET = test_main

.SUFFIX : .c .o

$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS)

clean :
	rm -rf $(OBJS) $(TARGET)
