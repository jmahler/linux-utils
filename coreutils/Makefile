
OBJS := cat dd echo false ls mkdir pwd rm rmdir sleep touch true

all: $(OBJS)

%: %.c
	gcc -Wall -Wextra $< -o $@
