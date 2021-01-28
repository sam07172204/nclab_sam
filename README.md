test_driver

$ sudo insmod demo_driver.ko
$ sudo mknod dev/demo c 60 0
./user_application
