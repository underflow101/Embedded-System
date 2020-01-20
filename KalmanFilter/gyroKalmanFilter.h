#ifndef _GYROKALMANFILTER_H_
#define _GYROKALMANFILTER_H_

#define SERIAL_SPEED 115200

// MPU-6050 Sensor
#define MPU6050_ACCEL_XOUT_H 0x3B   // R
#define MPU6050_PWR_MGMT_1   0x6B   // R/W
#define MPU6050_PWR_MGMT_2   0x6C   // R/W
#define MPU6050_WHO_AM_I     0x75   // R
#define MPU6050_I2C_ADDRESS  0x68   // I2C Address

// Kalman Filter
struct GyroKalman {
    // Variable to represent state matrix x
    float x_angle, x_bias;

    // Error covariance matrix
    float P_00, P_01, P_10, P_11;

    /******************************************************************
     * Q is 2x2 matriax of covariance
     * Gyro and accelerometer noise is independent of each other
     * x = F(x) + B(u) + w
     * w has a normal distribution with covariance Q
     * covariance = E[(X - E[X]) * (X - E[X])']
     * Covariance R: observation noise from accelerometer (1x1 Matrix)
     ******************************************************************/

    float Q_angle, Q_gyro;
    float R_angle;
};

static const float R_angle = 0.3;
static const float Q_angle = 0.01;
static const float Q_gyro = 0.04;

// Value limitation of accelerometer (may vary)
const int lowX = -2150;
const int highX = 2210;
const int lowY = -2150;
const int highY = 2210;
const int lowZ = -2150;
const int highZ = 2550;

// Time
unsigned long prevSensoredTime = 0;
unsigned long curSensoredTime = 0;

typedef union accel_t_gyro_union {
    struct {
        uint8_t x_accel_h, x_accel_l;
        uint8_t y_accel_h, y_accel_l;
        uint8_t z_accel_h, z_accel_l;
        uint8_t t_h, t_l;
        uint8_t x_gyro_h, x_gyro_l;
        uint8_t y_gyro_h, y_gyro_l;
        uint8_t z_gyro_h, z_gyro_l;
    } reg;
    struct {
        int x_accel, y_accel, z_accel;
        int temperature;
        int x_gyro, y_gyro, z_gyro;
    } value;
};

int xInit[5] = { 0, 0, 0, 0, 0 };
int yInit[5] = { 0, 0, 0, 0, 0 };
int zInit[5] = { 0, 0, 0, 0, 0 };
int initIndex = 0;
int initSize = 5;
int xCal = 0, yCal = 0, zCal = 1800;

// Peripheral
#define SWAP(x, y, tmp) tmp = x; x = y; y = tmp;


#endif /*_GYROKALMANFILTER_H_*/