
OBJS := ls dd cat touch rm

all: $(OBJS)

%: %.c
	gcc -Wall -Wextra -O2 $< -o $@
