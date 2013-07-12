
OBJS := ls dd cat touch

all: $(OBJS)

%: %.c
	gcc -Wall -Wextra -O2 $< -o $@
