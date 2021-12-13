CC = gcc

OUTFILE = hello_fifo.o
TARGET = hello_fifo

%.o: %.c
	$(CC) -c $^ -o $@

all: $(OUTFILE)
	$(CC) $^ -o $(TARGET)

clean:
	rm $(TARGET) $(OUTFILE)