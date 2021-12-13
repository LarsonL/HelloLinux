CC = gcc

OUTFILE = hello_shm.o
TARGET = hello_shm

%.o: %.c
	$(CC) -c $^ -o $@

all: $(OUTFILE)
	$(CC) $^ -o $(TARGET)

clean:
	rm $(TARGET) $(OUTFILE)