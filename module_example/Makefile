obj-m := module_example2.o
 
PWD := $(shell pwd)
KDIR := /lib/modules/$(shell uname -r)/build
 
default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
