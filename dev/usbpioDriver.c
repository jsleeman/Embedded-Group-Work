#include <linux/module.h> /* Needed by all modules */
#include <linux/kernel.h> /* Needed for KERN_ALERT */
#include <linux/slab.h>   /* Needed for kmalloc  */
#include "usbPioDriver.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("James Sleeman"); 
MODULE_DESCRIPTION("USB - PIO Driver, Sets up the connection offers reading and writing, and can close the connection too.");

static int usbPioInit()
{
  int result;
  
  printk("Initialising USB PIO driver\n");
  result = usb_register(&usbPioKeypadDriver);
  if (result)
    {
      printk("Error: USB failed to reigster, error number : %d", result);
    }
}

static int usbPioExit()
{
  printk("About to deregister the driver\n");
  usb_deregister(&usbPioKeypadDriver);
}

module_init(usbPioInit);
module_exit(usbPioExit);

static int usbPioProbe(struct usb_interface *interface, const struct usb_device_id *id)
{
  int i, retval = -ENOMEM;
  struct usb_host_interface *ifaceDesc;
  struct usb_endpoint_descriptor *endpoint;
  struct usb_device *usb_dev;
  usbPioDeviceT usbPioDevice;

  printk("Starting usbPioProbe\n");  
  usbPioDevice = kzalloc(sizeof(usbPioDevice), GFP_KERNEL);

  usbPioDevice->usbdev = usb_get_dev(interface_to_usbdev(interface));
  usbPioDevice->interface = interface;

  iface_desc = interface->cur_altsetting;
  for(i=0; i<ifaceDesc.desc.bNumEndpoints; i++)
    {
      endpoint = &ifaceDesc->endpoint[i].desc;
      
      if(!usbPioDevice->bulkInAddr && usb_endpoint_bulk_in(endpoint))
	{
	  usbPioDevice->bulkInLen = le16_to_cpu(endpoint->wMaxPacket);
	  usbPioDevice->bulkInAddr = endpoint->bEndpointAddress;
	  usbPioDevice->bulkInBuffer = kmalloc(usbPioDevice->bulkInLen, GFP_KERNEL);
	}
      if (usbPioDevice->bulkOutAddr && usb_endpoint_is_bulk_out(endpoint))
	{
	  /* Bulk out endpoint */
	  usbPioDevice->bulkOutAddr = endpoint->bEndpointAddress;
	}
    }
  
  if(usbPioDevice->bulkInAddr && usbPioDevice->bulkOutAddr)
    {
      return reval;
    }

  usb_set_intfdata(interface, usbPioDevice);
  retval = usb_register_dev(interface, &usbPioDevice);
  if (retval)
    {
      usb_set_intfdata(interface, NULL);
      return retval;
    }

  printk("Device now attached\n");
  return 0;
  
}

static void usbPioDisconnect(struct usb_interface *interface)
{
  printk("usbPioDisconnect");
 usbPioDeviceT usbPioDevice;

 usb_set_intfdata(interface, NULL);
 

}

static int usbPioRelsease(struct inode *inode, struct file *file)
{
  printk("Starting usbPioRelease\n");
  return 0;
}



