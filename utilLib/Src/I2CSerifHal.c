#include "I2CSerifHal.h"

extern I2C_HandleTypeDef hi2c1;

static int i2c_read_reg(void * context, uint8_t reg, uint8_t * rbuffer, uint32_t rlen)
{
        (void)context, (void)reg, (void)rbuffer, (void)rlen;

        HAL_StatusTypeDef retVal = HAL_OK;

        retVal = HAL_I2C_Mem_Read(&hi2c1,
                                  (uint16_t)(I2C_SLAVE_ADDRESS<<1),
                                  (uint16_t)reg,
                                  I2C_MEMADD_SIZE_8BIT,
                                  rbuffer,
                                  (uint16_t)rlen,
                                  100);

        return (int)retVal;
}

static int i2c_write_reg(void * context, uint8_t reg, const uint8_t * wbuffer, uint32_t wlen)
{
        (void)context, (void)reg, (void)wbuffer, (void)wlen;

        HAL_StatusTypeDef retVal = HAL_OK;

        retVal = HAL_I2C_Mem_Write(&hi2c1,
                                   (uint16_t)(I2C_SLAVE_ADDRESS<<1),
                                   (uint16_t)reg,
                                   I2C_MEMADD_SIZE_8BIT,
                                   (uint8_t*)wbuffer,
                                   (uint16_t)wlen,
                                   100);

        return (int)retVal;
}

static const inv_serif_hal_t serif_instance_i2c = {
        i2c_read_reg,
        i2c_write_reg,
        MAX_RW_TRANS_SIZE,
        MAX_RW_TRANS_SIZE,
        INV_SERIF_HAL_TYPE_I2C,
        0
};

const inv_serif_hal_t* get_serif_inst_i2c(void)
{
    return &serif_instance_i2c;
}
