
OBJS := cat dd echo env factor false kill ls mkdir mv pwd rm rmdir \
		sum sleep touch true yes wc chmod

all: $(OBJS)

%: %.c
	gcc -Wall -Wextra $< -o $@
