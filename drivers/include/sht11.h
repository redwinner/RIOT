/*
 * Copyright 2009, Freie Universitaet Berlin (FUB). All rights reserved.
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#ifndef SHT11_H
#define SHT11_H

/**
 * @defgroup    drivers_sht11 SHT11 Humidity and Temperature Sensor
 * @ingroup     drivers_sensors
 * @brief       Driver for Sensirion SHT11 Humidity and Temperature Sensor
 * @{
 *
 * @file
 * @brief       SHT11 Device Driver
 *
 * @author      Freie Universität Berlin, Computer Systems & Telematics
 */

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SHT11_NO_ACK        (0)     /**< don't ack read in `read_byte` */
#define SHT11_ACK           (1)     /**< do acknowledge read in `read_byte` */
/* adr command  r/w */
#define SHT11_STATUS_REG_W  (0x06)  /**< will write to status register */
#define SHT11_STATUS_REG_R  (0x07)  /**< will read from status register */
#define SHT11_MEASURE_TEMP  (0x03)  /**< tell sensor to measure temperature */
#define SHT11_MEASURE_HUMI  (0x05)  /**< tell sensor to measure humidity */
#define SHT11_RESET         (0x1E)  /**< reset the sensor */

/** time to wait after toggling the data line */
#define SHT11_DATA_WAIT     (1)
/** time to wait after toggling the clock line */
#define SHT11_CLK_WAIT      (1)

/** set measurement timeout to 1 second */
#define SHT11_MEASURE_TIMEOUT   (1000)

/**
 * @brief   sht11 measureable data
 */
typedef struct {
    float   temperature;    /**< temperature value */
    float   relhum;         /**< linear relative humidity */
    float   relhum_temp;    /**< temperature compensated relative humidity */
} sht11_val_t;

/**
 * @brief   SHT11 modes that can be measured
 */
typedef enum {
    TEMPERATURE = 1,
    HUMIDITY = 2
} sht11_mode_t;

/**
 * @brief   Initialize SHT11 ports
 */
void sht11_init(void);

/**
 * @brief   Read sensor
 *
 * @param value The struct to be filled with measured values
 * @param mode  Specifies type of data to be read
 *
 * @return  1 on success, 0 otherwise
 *
 * Example:
 * \code sht11_val sht11;
 * sht11_read_sensor(&sht11, HUMIDITY|TEMPERATURE);
 * printf("%-6.2f °C %5.2f %% %5.2f %%\n", sht11.temperature, sht11.relhum, sht11.relhum_temp); \endcode
 */
uint8_t sht11_read_sensor(sht11_val_t *value, sht11_mode_t mode);

/**
 * @brief   Write status register
 *
 * @param   p_value The value to write
 *
 * @return  1 on success, 0 otherwise
 */
uint8_t sht11_write_status(uint8_t *p_value);

/**
 * @brief   Read status register with checksum
 *
 * @param   p_value The read value
 * @param   p_checksum The received checksum
 *
 * return   1 on success, 0 otherwise
 */
uint8_t sht11_read_status(uint8_t *p_value, uint8_t *p_checksum);

#ifdef __cplusplus
}
#endif

/** @} */
#endif /* SHT11_H */
