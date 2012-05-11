KERNELDIR = ../linux
ARCH      = $(LINTARCH)

all:
	$(MAKE) ARCH=$(ARCH) -C $(KERNELDIR) M=$(PWD)

install:
	@echo "copy modexample.ko to your module directory"

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
	@rm -f Module.symvers

usbpioDriver.c: In function '__exittest':
/usbpioDriver.c:34: warning: return from incompatible pointer type
/usbpioDriver.c: In function 'usbPioProbe':
/usbpioDriver.c:45: error: incompatible types when assigning to type 'usbPioDeviceT' from type 'void *'
/usbpioDriver.c:47: error: invalid type argument of '->' (have 'usbPioDeviceT')
/usbpioDriver.c:48: error: invalid type argument of '->' (have 'usbPioDeviceT')
/usbpioDriver.c:50: error: 'iface_desc' undeclared (first use in this function)
/usbpioDriver.c:50: error: (Each undeclared identifier is reported only once
/usbpioDriver.c:50: error: for each function it appears in.)
/usbpioDriver.c:52: error: request for member 'desc' in something not a structure or union
/usbpioDriver.c:53: error: request for member 'desc' in something not a structure or union
/usbpioDriver.c:58: error: invalid type argument of '->' (have 'usbPioDeviceT')
/usbpioDriver.c:58: error: implicit declaration of function 'usb_endpoint_bulk_in'
/usbpioDriver.c:60: error: invalid type argument of '->' (have 'usbPioDeviceT')
/usbpioDriver.c:60: error: 'struct usb_endpoint_descriptor' has no member named 'wMaxPacket'
/usbpioDriver.c:61: error: invalid type argument of '->' (have 'usbPioDeviceT')
/usbpioDriver.c:62: error: invalid type argument of '->' (have 'usbPioDeviceT')
/usbpioDriver.c:62: error: invalid type argument of '->' (have 'usbPioDeviceT')
/usbpioDriver.c:66: error: invalid type argument of '->' (have 'usbPioDeviceT')
/usbpioDriver.c:69: error: invalid type argument of '->' (have 'usbPioDeviceT')
/usbpioDriver.c:70: error: invalid type argument of '->' (have 'usbPioDeviceT')
/usbpioDriver.c:70: error: invalid type argument of '->' (have 'usbPioDeviceT')
/usbpioDriver.c:75: error: invalid type argument of '->' (have 'usbPioDeviceT')
/usbpioDriver.c:75: error: invalid type argument of '->' (have 'usbPioDeviceT')
/usbpioDriver.c:77: error: 'reval' undeclared (first use in this function)
/usbpioDriver.c:80: error: incompatible type for argument 2 of 'usb_set_intfdata'
include/linux/usb.h:193: note: expected 'void *' but argument is of type 'usbPioDeviceT'
/usbpioDriver.c:81: warning: passing argument 2 of 'usb_register_dev' from incompatible pointer type
include/linux/usb.h:936: note: expected 'struct usb_class_driver *' but argument is of type 'struct usbPioDeviceT *'
/usbpioDriver.c:85: error: 'usbPioDeviceT' has no member named 'name'
/usbpioDriver.c:89: error: 'usbPioDeviceT' has no member named 'name'
/usbpioDriver.c:41: warning: unused variable 'usb_dev'
/usbpioDriver.c: In function 'usbPioDisconnect':
/usbpioDriver.c:116: error: 'usbPiodeviceT' undeclared (first use in this function)
/usbpioDriver.c:116: error: 'usbPiodevice' undeclared (first use in this function)
/usbpioDriver.c: In function 'usbPioOpen':
/usbpioDriver.c:134: warning: ISO C90 forbids mixed declarations and code
/usbpioDriver.c:138: error: 'usbPioDriver' undeclared (first use in this function)
/usbpioDriver.c:141: warning: format '%d' expects type 'int', but argument 2 has type 'const char *'
/usbpioDriver.c:141: warning: too many arguments for format
/usbpioDriver.c:148: error: expected expression before ')' token
/usbpioDriver.c: In function 'usbPioRead':
/usbpioDriver.c:162: warning: ISO C90 forbids mixed declarations and code
/usbpioDriver.c:171: error: 'usb' undeclared (first use in this function)
/usbpioDriver.c:171: error: implicit declaration of function 'urb_alloc_urb'
/usbpioDriver.c:178: error: 'usbPioDeviceT' has no member named 'usbDev'
/usbpioDriver.c:178: error: 'usbPioDeviceT' has no member named 'inBulkBufferSize'
/usbpioDriver.c:187: error: 'usbPioDeviceT' has no member named 'usbDev'
/usbpioDriver.c:190: error: 'usbPioReadCallBack' undeclared (first use in this function)
/usbpioDriver.c:191: warning: passing argument 3 of 'usb_fill_bulk_urb' makes integer from pointer without a cast
include/linux/usb.h:1261: note: expected 'unsigned int' but argument is of type 'char *'
/usbpioDriver.c:191: warning: passing argument 4 of 'usb_fill_bulk_urb' makes pointer from integer without a cast
include/linux/usb.h:1261: note: expected 'void *' but argument is of type 'size_t'
/usbpioDriver.c:191: warning: passing argument 6 of 'usb_fill_bulk_urb' from incompatible pointer type
include/linux/usb.h:1261: note: expected 'usb_complete_t' but argument is of type 'struct usbPioDeviceT *'
/usbpioDriver.c:191: error: too few arguments to function 'usb_fill_bulk_urb'
/usbpioDriver.c:193: error: 'usbPioDeviceT' has no member named 'ctrl_urb'
/usbpioDriver.c: In function 'usbPioWrite':
/usbpioDriver.c:207: warning: ISO C90 forbids mixed declarations and code
/usbpioDriver.c:214: warning: assignment from incompatible pointer type
/usbpioDriver.c:217: error: 'usb' undeclared (first use in this function)
/usbpioDriver.c:225: error: dereferencing pointer to incomplete type
/usbpioDriver.c:225: error: dereferencing pointer to incomplete type
/usbpioDriver.c:233: error: implicit declaration of function 'copy_from_user'
/usbpioDriver.c: In function 'usbPioWriteCallBack':
/usbpioDriver.c:253: warning: format '%s' expects type 'char *', but argument 2 has type 'int'
/usbpioDriver.c: In function 'usbOioKeypadReadCallBack':
/usbpioDriver.c:272: warning: format '%s' expects type 'char *', but argument 2 has type 'int'
/usbpioDriver.c:276: error: implicit declaration of function 'copy_to_user'
/usbpioDriver.c:276: error: dereferencing pointer to incomplete type
make[2]: *** [/usbpioDriver.o] Error 1
make[1]: *** [_module_/home/netlab/jcsleema/year3/esd/Embedded-Group-Work/dev] Error 2
make: *** [all] Error 2
