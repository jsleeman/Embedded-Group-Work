ARCH=arm
CC=/home/netlab/jclseema/year3/buildroot/output/host/usr/bin/arm-unknown-linux-uclibcgnueabi-gcc
obj= usbPioKeypad.o
KDIR= /home/netlab/jclseema/year3/buildroot/output/build/linux-

all:


clean:
	  rm -f *.o

ins: usbPioKeypad.ko
          sudo insmod usbPioKeypad.ko

rmm: usbPioKeypad.ko
          sudo rmmod usbPioKeypad.ko

KERNELDIR = ../linux
ARCH      = $(LINTARCH)
 
all:
    $(MAKE) ARCH=$(ARCH) -C $(KERNELDIR) M=$(PWD)
 
install:
    @echo "copy modexample.ko to your module directory"
 
clean:
    $(MAKE) -C $(KERNELDIR) M=$(PWD) clean
    @rm -f Module.symvers
 
use with:
make ARCH=arm CROSS_COMPILE=/home/netlab/sjackson/EmbeddedOS/buildroot-2011.08/output/host/usr/bin/arm-unknown-linux-uclibcgnueabi- KERNELDIR=/home/netlab/sjackson/EmbeddedOS/buildroot-2011.08/output/build/linux-2.6.35.13