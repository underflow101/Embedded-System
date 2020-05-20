from smbus import SMBus

bus = SMBus(2)

BH1750 = 0x23
ONE_TIME_HIGH_RES_MODE_1 = 0x20
ONE_TIME_HIGH_RES_MODE_2 = 0x21

bus = SMBus(1)

while True:
    word = bus.read_word_data(BH1750, ONE_TIME_HIGH_RES_MODE_2)
    swap = (word & 0xff) * 256 + (word >> 8)
    print(swap)