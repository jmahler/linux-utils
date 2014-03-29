
OBJS := cat dd echo false ls pwd rm touch true

all: $(OBJS)

%: %.c
	gcc -Wall -Wextra $< -o $@
