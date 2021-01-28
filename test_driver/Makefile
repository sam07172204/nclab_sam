CC=arm-linux-gcc

obj-m := demo_driver.o

all:
	make -C /home/sam/linux M=$(PWD) ARCH=arm modules
clean:
	make -C /home/sam/linux M=$(PWD) ARCH=arm clean

