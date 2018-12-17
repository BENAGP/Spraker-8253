KSRC := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

obj-o := speaker.o

default:
	$(MAKE) -C $(KSRC) SUBDIRS = $(PWD) modules
clean:
	$(MAKE) -C $(KSRC) SUBDIRS = $(PWD) clean
