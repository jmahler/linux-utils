
OBJS := cat dd echo env false ls mkdir mv pwd rm rmdir sum sleep touch true \
		yes

all: $(OBJS)

%: %.c
	gcc -Wall -Wextra $< -o $@
