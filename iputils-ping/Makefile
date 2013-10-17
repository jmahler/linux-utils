
ARGS := -Wall -Wextra -O2 -g

all: ping

ping.o: ping.c ping.h
	gcc -c $(ARGS) $< -o $@

main.o: main.c
	gcc -c $(ARGS) $< -o $@

ping: main.o ping.o
	gcc $^ -o $@
	sudo chown root ping
	sudo chmod u+s ping

clean:
	-rm -f ping.o main.o ping
