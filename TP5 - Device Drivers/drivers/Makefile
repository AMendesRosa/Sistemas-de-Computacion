MODULE_NAME := sensor_driver

KERNEL_DIR := /usr/src/linux-headers-6.1.0-49-arm64

obj-m := $(MODULE_NAME).o

all:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) clean
