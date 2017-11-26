TARGET=frameBuffer
#CC=arm-cortex_a9-linux-gnueabi-
CC=

all:$(TARGET)
$(TARGET):main.cpp
	@$(CC)gcc $< -std=c++11 -Ofast -lstdc++ -o $@
clean:
	rm -rf *.o $(TARGET) a.out
.PHONY:all clean $(TARGET)
