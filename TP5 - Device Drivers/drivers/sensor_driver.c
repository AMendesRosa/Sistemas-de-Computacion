#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/random.h>
#include <linux/types.h>

#define DRIVER_NAME  "sensor_driver"
#define DEVICE_NAME  "sensor"
#define NUM_DEVICES  1

static dev_t dev_number;
static struct cdev sensor_cdev;
static struct class  *sensor_class;
static struct device *sensor_device;

/* 0 o 1  que sensor está activo */
static volatile int sensor_seleccionado = 0;

/* -------------------------------------------------------
 * Genera un valor simulado para cada sensor.
 * Sensor 0: simula temperatura (20 a 35 grados)
 * Sensor 1: simula humedad    (40 a 90 %)
 * En hardware real, acá iría la lectura del GPIO o ADC.
 * ------------------------------------------------------- */
static int leer_sensor(int sensor)
{
    u32 val;
    get_random_u32_below(100); /* calentar el RNG */
    val = get_random_u32_below(100);

    if (sensor == 0)
        return 20 + (val % 16);   /* 20..35 */
    else
        return 40 + (val % 51);   /* 40..90 */
}

static int my_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "%s: abierto\n", DRIVER_NAME);
    return 0;
}

static int my_close(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "%s: cerrado\n", DRIVER_NAME);
    return 0;
}

static ssize_t my_read(struct file *file, char __user *buf,
                       size_t count, loff_t *ppos)
{
    char respuesta[64];
    int valor, len;

    if (*ppos > 0)
        return 0;

    valor = leer_sensor(sensor_seleccionado);

    if (sensor_seleccionado == 0)
        len = snprintf(respuesta, sizeof(respuesta),
                       "sensor:0 valor:%d unidad:C\n", valor);
    else
        len = snprintf(respuesta, sizeof(respuesta),
                       "sensor:1 valor:%d unidad:%%\n", valor);

    if (copy_to_user(buf, respuesta, len))
        return -EFAULT;

    *ppos += len;

    printk(KERN_INFO "%s: read() sensor=%d valor=%d\n",
           DRIVER_NAME, sensor_seleccionado, valor);

    return len;
}

static ssize_t my_write(struct file *file, const char __user *buf,
                        size_t count, loff_t *ppos)
{
    char kbuf[4];
    int nuevo;

    if (count > sizeof(kbuf) - 1)
        return -EINVAL;

    if (copy_from_user(kbuf, buf, count))
        return -EFAULT;

    kbuf[count] = '\0';
    nuevo = kbuf[0] - '0';

    if (nuevo != 0 && nuevo != 1) {
        printk(KERN_WARNING "%s: valor invÃ¡lido, usÃ¡ 0 o 1\n", DRIVER_NAME);
        return -EINVAL;
    }

    sensor_seleccionado = nuevo;
    printk(KERN_INFO "%s: sensor cambiado a %d\n", DRIVER_NAME, nuevo);

    return count;
}

static struct file_operations sensor_fops = {
    .owner   = THIS_MODULE,
    .open    = my_open,
    .release = my_close,
    .read    = my_read,
    .write   = my_write,
};

static int __init sensor_driver_init(void)
{
    int ret;

    ret = alloc_chrdev_region(&dev_number, 0, NUM_DEVICES, DRIVER_NAME);
    if (ret < 0) {
        printk(KERN_ERR "%s: no se pudo reservar major/minor\n", DRIVER_NAME);
        return ret;
    }
    printk(KERN_INFO "%s: major=%d minor=%d\n",
           DRIVER_NAME, MAJOR(dev_number), MINOR(dev_number));

    cdev_init(&sensor_cdev, &sensor_fops);
    sensor_cdev.owner = THIS_MODULE;

    ret = cdev_add(&sensor_cdev, dev_number, NUM_DEVICES);
    if (ret < 0) {
        unregister_chrdev_region(dev_number, NUM_DEVICES);
        return ret;
    }

    sensor_class = class_create(THIS_MODULE, "sensor_class");
    if (IS_ERR(sensor_class)) {
        cdev_del(&sensor_cdev);
        unregister_chrdev_region(dev_number, NUM_DEVICES);
        return PTR_ERR(sensor_class);
    }

    sensor_device = device_create(sensor_class, NULL, dev_number,
                                  NULL, DEVICE_NAME);
    if (IS_ERR(sensor_device)) {
        class_destroy(sensor_class);
        cdev_del(&sensor_cdev);
        unregister_chrdev_region(dev_number, NUM_DEVICES);
        return PTR_ERR(sensor_device);
    }

    printk(KERN_INFO "%s: cargado â€” /dev/%s listo\n", DRIVER_NAME, DEVICE_NAME);
    return 0;
}

static void __exit sensor_driver_exit(void)
{
    device_destroy(sensor_class, dev_number);
    class_destroy(sensor_class);
    cdev_del(&sensor_cdev);
    unregister_chrdev_region(dev_number, NUM_DEVICES);
    printk(KERN_INFO "%s: descargado\n", DRIVER_NAME);
}

module_init(sensor_driver_init);
module_exit(sensor_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Agustin");
MODULE_DESCRIPTION("Driver de dos sensores simulados");
MODULE_VERSION("1.0");