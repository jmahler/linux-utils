
OBJS := cat dd echo false ls mkdir mv pwd rm rmdir sum sleep touch true

all: $(OBJS)

%: %.c
	gcc -Wall -Wextra $< -o $@
