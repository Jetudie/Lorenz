CC = gcc
CFLAGS = -g -O0
OBJS = lorenz.o
RM = rm
N = 1000

all: lorenz

lorenz: main.o lorenz.o 
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) -c -o $@ $<


.PHONY: plot clean
plot: plot.gp
	./lorenz $(N) > log.txt
	gnuplot plot.gp

clean:
	$(RM) $(EXEC) *.o *.txt *.png
