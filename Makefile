all: compile exe

compile:
	gcc -fopenmp -o main main.c

exe:
	time ./all.sh

clean:
	rm -f main *.bin* *.bin.new
