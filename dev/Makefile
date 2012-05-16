KERNELDIR = ../linux
ARCH      = $(LINTARCH)

all:
	$(MAKE) ARCH=$(ARCH) -C $(KERNELDIR) M=$(PWD)

install:
	@echo "copy modexample.ko to your module directory"

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
	@rm -f Module.symvers

