CC = g++
OBJS = main.o twoseq.o

prog: $(OBJS)
	$(CC) $(OBJS) -o prog

main.o: main.cpp
	$(CC) -c main.cpp

twoseq.o: twoseq.cpp
	$(CC) -c twoseq.cpp

clean:
	\rm *.o prog