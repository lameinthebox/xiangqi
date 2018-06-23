CC = g++
CFLAGS = -std=c++14 -W -Wall
TARGET = xiangqi.exe

$(TARGET) : xiangqi.o main.o
	$(CC) $(CFLAGS) -o $(TARGET) xiangqi.o main.o

xiangqi.o : xiangqi.cpp
	$(CC) $(CFLAGS) -c -o xiangqi.o xiangqi.cpp

main.o : main.cpp
	$(CC) $(CFLAGS) -c -o main.o main.cpp

clean :
	rm *.o $(TARGET)
