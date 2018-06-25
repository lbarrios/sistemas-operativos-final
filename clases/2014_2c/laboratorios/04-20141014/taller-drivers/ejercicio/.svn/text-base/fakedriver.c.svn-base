#include "fakeserialhelper.h"
#include <linux/kfifo.h>
#include <linux/semaphore.h>

#define DEVICE_NAME "fakeserial"
#define FAKESERIAL_FIFO_SIZE PAGE_SIZE

struct kfifo fifo;
struct semaphore sem, sem2;

ssize_t fakeserial_read (struct file *archivo, char __user *usuario, size_t tamanio, loff_t *l){
	int total_read, read_size;
	char buffer[800];

	total_read = 0;
	read_size = 0;
	printk(KERN_DEBUG "fakeserial_driver: estoy leyendo la cola del dispositivo falso!\n");
	
	while(total_read<tamanio)
	{
		down_interruptible(&sem2);
		printk(KERN_DEBUG "Leí un dato!\n");
		read_size = 0;
		down_interruptible(&sem);
		read_size = kfifo_out(&fifo, &(buffer[total_read]), 1); //tamanio-total_read);
		up(&sem);
		total_read+=read_size;
	}

	copy_to_user(usuario, buffer, total_read);
	return total_read;
};


struct file_operations fakeserial_fops;

struct miscdevice fakeserial = {
	MISC_DYNAMIC_MINOR,
	"fakeserial",
	&fakeserial_fops,
};

void fakeserial_handler(void) {
	int total_read;
	u8 input;
	printk(KERN_DEBUG "fakeserial_driver: estoy atendiendo una interrupción del dispositivo!\n");
	input = fake_inb(FAKE_SERIAL_PORT);
	total_read = kfifo_in(&fifo, &input, 1);
	for(;total_read>0;total_read--)
	{
		up(&sem2);
	}
};

static int __init fakeserial_init(void) {
    printk(KERN_DEBUG "fakeserial_driver: Initialized!\n");
    kfifo_alloc(&fifo, PAGE_SIZE, GFP_KERNEL);
    fakeserial_fops.read = &fakeserial_read;
    sema_init(&sem, 1);
    sema_init(&sem2, 0);
	fake_serial_init(FAKE_SERIAL_MODE_TEXT, &(fakeserial_handler));
    misc_register(&fakeserial);
    return 0;
}

static void __exit fakeserial_exit(void) {
	misc_deregister(&fakeserial);
	fake_serial_exit();
    printk(KERN_DEBUG "fakeserial_driver: HOLA. DIGO CHAU.\n");
}




module_init(fakeserial_init);
module_exit(fakeserial_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Alumno");
MODULE_DESCRIPTION("Driver del dispositivo serial ficticio");
