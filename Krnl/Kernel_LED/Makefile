obj-m	+=	ledonoff.o

KDIR	=	/usr/src/linux-headers-4.4.50-v7+

all:
	$(MAKE)	-C	$(KDIR)	SUBDIRS=$(PWD)	modules

clean:
	rm	-rf	*.o	*.ko	*.mod	*.symvers	*.order
