# i2c control

import os
import fcntl
import time

I2C_SLAVE = 0x703
TSL2561 = 0x39

CONTINUOUS_HIGH_RES_MODE_1 = 0x26
CONTINUOUS_HIGH_RES_MODE_2 = 0x27
ONE_TIME_HIGH_RES_MODE_1 = 0x36
ONE_TIME_HIGH_RES_MODE_2 = 0x37

fd = os.open('/dev/i2c-1', os.O_RDWR)
fcntl.ioctl(fd, I2C_SLAVE, TSL2561)
r = os.write(fd, bytes([CONTINUOUS_HIGH_RES_MODE_2]))

try:
    while True:
        data = os.read(fd, 2)
        print(int(data[0]) * 256 + int(data[1]))
        time.sleep(0.2)
except KeyboardInterrupt:
    os.close(fd)