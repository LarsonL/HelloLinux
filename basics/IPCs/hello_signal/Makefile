CC = gcc

OUTFILE = hello_signal.o
TARGET = hello_signal

%.o: %.c
	$(CC) -c $^ -o $@

all: $(OUTFILE)
	$(CC) $^ -o $(TARGET)

clean:
	rm $(TARGET) $(OUTFILE)