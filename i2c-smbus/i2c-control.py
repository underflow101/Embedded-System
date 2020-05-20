# i2c control

import os
import fcntl
import time

I2C_SLAVE = 0x703
BH1750 = 0x23

CONTINUOUS_HIGH_RES_MODE_1 = 0x10
CONTINUOUS_HIGH_RES_MODE_2 = 0x11
ONE_TIME_HIGH_RES_MODE_1 = 0x20
ONE_TIME_HIGH_RES_MODE_2 = 0x21

fd = os.open('/dev/i2c-2', os.O_RDWR)
fcntl.ioctl(fd, I2C_SLAVE, BH1750)
r = os.write(fd, bytes([CONTINUOUS_HIGH_RES_MODE_2]))

try:
    while True:
        data = os.read(fd, 2)
        print(int(data[0]) * 256 + int(data[1]))
        time.sleep(0.2)
except KeyboardInterrupt:
    os.close(fd)