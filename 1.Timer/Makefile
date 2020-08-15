CC=g++
CFLAGS= -Wall -fpermissive
OBJS=main.o timer.o
TARGET= result.out
LIB = -lrt

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIB)

	# rm -f *.o 
	# remove .o files
	
main.o: main.cpp
timer.o: timer.h timer.cpp



clean:
	rm -f *.o
	rm -f $(TARGET)
