#include <linux/module.h> /* Needed by all modules */
#include <linux/kernel.h> /* Needed for KERN_ALERT */
#include <linux/slab.h>   /* Needed for kmalloc  */
#include <linux/usb.h>    /* Needed for USB functions */
#include "usbPioDriver.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("James Sleeman"); 
MODULE_DESCRIPTION("USB - PIO Driver, Sets up the connection offers reading and writing, and can close the connection too.");

static int usbPioInit()
{
  int result = -1;
  
  printk("Initialising USB PIO driver\n");
  result = usb_register(&usbPioKeypadDriver);
  if (result)
    {
      printk("Error: USB failed to reigster, error number : %d", result);
    }
  printk("Successfully registered USB, result number : %d", result);
  return result;
}

static int usbPioExit()
{
  int result = 0;
  printk("About to deregister the driver\n");
  usb_deregister(&usbPioKeypadDriver);
  return result;
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
  
  printk(KERN_ALERT "%d Endpoints found" , ifaceDesc.desc.bNumEndpoints);
  for(i=0; i<ifaceDesc.desc.bNumEndpoints; i++)
    {
      endpoint = &ifaceDesc->endpoint[i].desc;

      /* Sets up end point for input*/
      if(!usbPioDevice->bulkInAddr && usb_endpoint_bulk_in(endpoint))
	{
	  usbPioDevice->bulkInLen = le16_to_cpu(endpoint->wMaxPacket);
	  usbPioDevice->bulkInAddr = endpoint->bEndpointAddress;
	  usbPioDevice->bulkInBuffer = kmalloc(usbPioDevice->bulkInLen, GFP_KERNEL);
	  printk(KERN_ALERT "Endpoint %d is a bulk in endpoint\n", i);
	}
      /* Sets up end point for output */
      if (usbPioDevice->bulkOutAddr && usb_endpoint_is_bulk_out(endpoint))
	{
	  /* Bulk out endpoint */
	  usbPioDevice->bulkOutAddr = endpoint->bEndpointAddress;
	  usbPioDevice->bulkOutBuffer = kmalloc(usbPioDevice->bulkInLen, GFP_KERNEL);
	  printk(KERN_ALERT "Endpoint %d is a bulk out endpoint\n", i);
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
      printk(KERN_ALERT "%s could not be attached\n", usbPioDevice.name);
      return retval;
    }

  printk("%s now attached\n", usbPioDevice.name);
  return 0;
  
}

static int usbPioRelsease(struct inode *inode, struct file *file)
{
  printk("Starting usbPioRelease\n");
  return 0;
}

/* Sources: Essential Linux Device Drivers 
            http://www.cems.uwe.ac.uk/~cduffy/dwd/usbpio.pdf
	    http://www.cems.uwe.ac.uk/~cduffy/lkmpg.pdf
*/

/* Kernel return error codes: ENOMEM = Used when no mem available
                              EFAULT = Used when accessing memory outside you address space
*/

/* Pipes -> interger encoding of: endpoint address, direction (in /out), type of data transfer(control, bulk, irq, bulk, isochronous) */

static void usbPioDisconnect(struct usb_interface *interface)
  {
    printk("Starting usbPioDisconnect\n");
    usbPiodeviceT *usbPiodevice;
    
    /*Retrieve data saved with usb_set_intfdata - Free memory*/
    usbPiodevice = usb_get_intfdata(interface); //TODO Free memory
    
    /*Zero out interface data*/
    usb_set_intfdata(interface, NULL);
    
    /* release /dev/usbPio */
    usb_deregister_dev(interface, &usbPioClass);
    
    usbPiodevice->interface = NULL;
  }

static int usbPioOpen(struct inode *inode, struct file *file)
  {
    printk("Starting UsbPioOpen");

    usbPioDeviceT *usbPioDevice;
    struct usb_interface *interface;

    /* Get the interface the device is associated with */
    interface = usb_find_interface(&usbPioDriver, iminor(inode));
    if (!interface)
      {
	printk (KERN_ALERT "Error: Can't find device for minor %d\n",__FUNCTION__, iminor(inode));
	return -ENODEV;
      }

    /* This data was saved in usbPioProbe*/
    usbPioDevice = usb_get_intfdata(interface);
    
    if()
      {
	printk (KERN_ALERT "usb_get_intfdata failed\n");
	return -ENODEV;
      }

    /* Saves the device specific object for use with read and write*/
    file->private_data = usbPioDevice;
  }

static ssize_t usbPioRead(struct file *file, char __user *buffer, size_t count, loff_t *ppos)
  {
    printk("starting usbPioRead\n");
    
    int retval;
    usbPioDeviceT *usbPioDevice;
    struct urb *urb;
    char *dma_buffer;
    
    /* Get the address of the device, data saved in open */
    usbPioDevice = (usbPioDeviceT *)file->private_data;

    /* Allocate some mem for the URB*/
    usb = urb_alloc_urb(0, GFP_KERNEL);
    if (!usb)
      {
	printk(KERN_ALERT "Memory allocation for the URB failed\n");
	return -ENOMEM;
      }
    
    dma_buffer = usb_alloc_coherent(usbPioDevice->usbDev, usbPioDevice->inBulkBufferSize, GFP_KERNEL, &urb->transfer_dma);
    if (!dma_buffer)
      {
	printk(KERN_ALERT "Error: failed to allocate mem for usb dma buffer\n");
	return -ENOMEM;
      }

    /*Init the urb*/
    usb_fill_bulk_urb(urb,
		      usbPioDevice->usbDev,
		      dma_buffer,
		      count,
		      usbPioReadCallBack,
		      usbPioDevice);

    retval = usb_submit_urb(usbPioDevice->ctrl_urb, GFP_ATOMIC);
    if (retval)
      {
	printk(KERN_ALERT "Error: failed to submit the URB, error number: %d", retval);
	return-EFAULT;
      }
   
    return count;
  }

static ssize_t usbPioWrite(struct file *file, const char __user *user_buffer, size_t count, loff_t *ppos)
  {
    printk("Starting usbPioWrite");
    
    size_t bufferSize = count;
    char *dmaBuffer; /*used for usb_buffer_alloc*/
    struct urb *urb;
    struct usbPioDeviceT *usbPioDevice;
    int retval;

    /* Get the address of the device, data saved in open */
    usbPioDevice = (usbPioDeviceT *)file->private_data;

    /* Allocate some mem for the URB*/
    usb = urb_alloc_urb(0, GFP_KERNEL);
    if (!usb)
      {
	printk(KERN_ALERT "Memory allocation for the URB failed\n");
	return -ENOMEM;
      }
    
    /* sets up the dma*/
    dmaBuffer = usb_alloc_coherent(usbPioDevice->usbDev, usbPioDevice->inBulkBufferSize, GFP_KERNEL, &urb->transfer_dma);
    if (!dmaBuffer)
      {
	printk(KERN_ALERT "Error: failed to allocate mem for usb dma buffer\n");
	return -ENOMEM;
      }
    
    /* Copies the data from userland to kernel land */
    if(copy_from_user(dmaBuffer, user_buffer, bufferSize))
      {
	printk(KERN_ALERT"Error: Failed to copy data from user land to the DMA buffer, error number: %d", retval);
	return-EFAULT;
      }
    
    retval = usb_submit_urb(urb, GFP_KERNEL);
    if(retval)
      {
	printk(KERN_ALERT "usb_submit_urb, error: %d", retval);
	return-EFAULT;
      }

    return bufferSize;
  }
static void usbPioWriteCallBack(struct urb *urb)
{
  /* urb->status contains the submission status. 0 if seccessful, ignore the 3 errors in the if below, dunno why the good book says too */
  if (urb->status && !(urb->status == -ENOENT || urb->status == -ECONNRESET || urb->status == -ESHUTDOWN))
    {
      printk(KERN_ALERT "Error: URB Status:%s",urb->status);
    }
  /* free up our allocated buffer */
  usb_free_coherent(urb->dev, urb->transfer_buffer_length,urb->transfer_buffer, urb->transfer_dma);
}

static void usbOioKeypadReadCallBack(struct urb *urb)
{
  char *buf;
  struct usbPioDeviceT *usbPioDevice;

  usbPioDevice = (struct usbPioDeviceT*)urb->context;

  /*Print what is returned the read urb*/
  buf = (char *)urb->transfer_buffer;

  /* urb->status contains the submission status. 0 if seccessful, ignore the 3 errors in the if below, dunno why the good book says too */
  if (urb->status && !(urb->status == -ENOENT || urb->status == -ECONNRESET || urb->status == -ESHUTDOWN))
  {
           printk(KERN_ALERT "Error: URB Status:%s",urb->status);
  }

  /* Copy to userspace */
  copy_to_user(usbPioDevice->user_buffer, buf, urb->actual_length);
 
  /* free up our allocated buffer */
  usb_free_coherent(urb->dev, urb->transfer_buffer_length,
  urb->transfer_buffer, urb->transfer_dma);
}

