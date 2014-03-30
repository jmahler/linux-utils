
OBJS := cat dd echo false ls pwd rm sleep touch true

all: $(OBJS)

%: %.c
	gcc -Wall -Wextra $< -o $@
