CC = g++
TARGET = emu
OBJS = emu.o cpu.o mmu.o interrupt.o instructions.o timer.o registers.o cartridge.o

CXXFLAGS = -O3 -Wall -Wextra -std=c++2b

.PHONY: all
all: $(TARGET)

.PHONY: clean
clean:
	rm -rf *.o $(TARGET)

.PHONY: run
run:
	./$(TARGET) $(FILE)

$(TARGET): $(OBJS) Makefile
	$(CC) $(OBJS) -o $@

%.o: %.cpp Makefile
	$(CC) $(CXXFLAGS) -c $<