#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>


char output_string[50]="test\n";


static ssize_t drv_read(struct file *filp, char *buf, size_t count, loff_t *ppos)
{

   printk("<1>EXAMPLE: read  (size=%d)\n" ,strlen(output_string));
   if(copy_to_user(buf, output_string, strlen(output_string))!=0)  
      printk("output error!!\n");
   return strlen(output_string);
 
}

static ssize_t drv_write(struct file *filp, char *buf, size_t count, loff_t *ppos)
{ 
  size_t pos;
  uint8_t byte;
  printk("<1>EXAMPLE: write  (size=%d)\n" ,count);
  for( pos = 0; pos < count; ++pos){
       if(copy_from_user(&byte, buf + pos, 1)!=0)  break;
       
       printk("<1>EXAMPLE: write  (buf[%d] = %c)\n",pos ,(unsigned)byte);
  }  
   
   return pos;

}

static int drv_open(struct inode *inode, struct file *filp)
{
  printk("device open\n");
    
   return 0;
}
static int drv_release(struct inode *inode, struct file *filp)
{
   printk("device release\n");
   
    return 0;
}
struct file_operations drv_fops =
{

   read:           drv_read,
   write:          drv_write,
   open:           drv_open,
   release:        drv_release,
};


#define MAJOR_NUM          60
#define MODULE_NAME        "NCLAB_DEMO"


static int demo_init(void) {
   
   if (register_chrdev(MAJOR_NUM, "demo", &drv_fops) < 0) {
      printk("<1>%s: can't get major %d\n", MODULE_NAME, MAJOR_NUM);
      return (-EBUSY);
   }
   printk("<1>%s: started\n", MODULE_NAME);
   return 0;
}

static void demo_exit(void) {

   unregister_chrdev(MAJOR_NUM, "demo");
   printk("<1>%s: removed\n", MODULE_NAME);
}

module_init(demo_init);

module_exit(demo_exit);
