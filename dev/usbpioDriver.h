#define BMCM_ID 0x09ca
#define PRODUCT_ID 0x5544
#define MINOR_BASE TODO /*TOOOO DOOOO*/

/* Function Prototypes*/
static int usbPioInit();
static int usbPioExit();
static int usbPioProbe(struct usb_interface *interface, const struct usb_device_id *id);
static void usbPioDisconnect(struct usb_interface *interface);
static ssize_t usbPioRead(struct file *file, char __user *buffer, size_t count, loff_t *ppos);
static ssize_t usbPioWrite(struct file *file, const char __user *user_buffer, size_t count, loff_t *ppos);
static int usbPioOpen(struct inode *inode, struct file *file);
static int usbPioRelsease(struct inode *inode, struct file *file);
static void usbPioWriteCallBack(struct urb *urb)
static void usbOioKeypadReadCallBack(struct urb *urb)

static struct usb_device_id usbPioKeypadIdTable = 
  {
    { USB_DEVICE(BMCM_ID, PRODUCT_ID) },
    {} /* Terminate */
  };

MODULE_DEVICE_TABLE(usb, usbPioKeypadIdTable);

static struct usb_driver usbPioKeypadDriver =
  {
    .name = "USB PIO driver",
    .probe = usbPioProbe,
    .disconnect = usbPioDisconnect,
    .id_table = usbPioKeypadIdTable, /* See previous struct*/
  };

static struct file operations usbPioFops =
  {
    .owner = THIS_MODULE,      /* Owner*/
    .read = usbPioRead,        /* Read Method*/
    .write = usbPioWrite,      /* Write Method*/ 
    .ioctl = usbPioIoctl,       /* Ioctl Method*/
    .open = usbPioOpen,        /* Open Method*/
    .release = usbPioRelease, /* Release Method*/
  };

static struct usb_class_driver usbPioClass = 
  {
    .name = usbPio,
    .fops = &usbPioFops,
    .minor_base = MINOR_BASE,
  };

typedef struct 
{
  struct usb_device *usbdev;
  struct usb_ctrlrequest ctrlReq;
  unsigned char *bulkInBuffer;
  unsigned char *bulkOutBuffer;
  size_t bulkBufferSize;
  __u8 bulkInAddr;
  __u8 bulkOutAddr;
  unsigned char *userBuffer;
} usbPioDevice;


   
        
  

 
