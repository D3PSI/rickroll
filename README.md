# rickroll
an ingenious kernel module which just prints https://youtu.be/dQw4w9WgXcQ over and over again

# how to use

## building

run `make`. boom, done.

## inserting into the running kernel

run `sudo insmod rickroll.ko`, check `journalctl -xfe` in the meantime to see the module being loaded. also, note the major number it prints to the logs.

## getting rickrolled

create a new character device with the major number you read from the logs:

    cd /dev && sudo mknod rickroll c <major> 0

run `cat /dev/rickroll` and be amazed.
