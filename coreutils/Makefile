
OBJS := cat dd echo false ls rm touch true

all: $(OBJS)

%: %.c
	gcc -Wall -Wextra $< -o $@
