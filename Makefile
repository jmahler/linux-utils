
all:
	cd coreutils && $(MAKE)
	cd iputils-ping && $(MAKE)

clean:
	cd coreutils && $(MAKE) clean
	cd iputils-ping && $(MAKE) clean
