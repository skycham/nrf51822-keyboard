/**
 * @brief EEPROM存储
 * 
 * @file storage.c
 * @author Jim Jiang
 * @date 2018-05-13
 */
#include "app_error.h"
#include "eeconfig.h"
#include "pstorage.h"
#include <stdint.h>

bool realIsInit = false;

pstorage_handle_t pstorage_base_block_id;
pstorage_handle_t block_handle;
custom_config_t custom_config;

void config_pstorage_init(void);
void config_write(void);
void config_read(void);
void config_update(void);

static uint8_t config_buffer[8] __attribute__((aligned(4))) = { EECONFIG_MAGIC_NUMBER >> 8, EECONFIG_MAGIC_NUMBER % 0x100, 0, 0, 0, 0, 0, 0 };

static void eeconfig_set_default()
{
    config_buffer[0] = EECONFIG_MAGIC_NUMBER >> 8;
    config_buffer[1] = EECONFIG_MAGIC_NUMBER % 0x100;
    config_buffer[2] = 0;   //EECONFIG_DEBUG
    config_buffer[3] = 0;   //EECONFIG_DEFAULT_LAYER
    config_buffer[4] = 0;   //EECONFIG_KEYMAP
    config_buffer[5] = 0;   //EECONFIG_MOUSEKEY_ACCEL
    config_buffer[6] = 0;   //EECONFIG_CUSTOM
#ifdef BACKLIGHT_ENABLE
    config_buffer[7] = 0;
#endif
}

bool eeconfig_is_enabled(void)
{
    return realIsInit;
}

void eeconfig_init(void)
{
    if (realIsInit) {
        eeconfig_set_default();
        config_update();
    } else {
        config_pstorage_init();
        realIsInit = true;
    }
}

void eeconfig_enable(void)
{
}

void eeconfig_disable(void)
{
}

uint8_t eeconfig_read_debug(void)
{
    return config_buffer[2];
}

void eeconfig_write_debug(uint8_t val)
{
    config_buffer[2] = val;
    config_update();
}

uint8_t eeconfig_read_default_layer(void)
{
    return config_buffer[3];
}

void eeconfig_write_default_layer(uint8_t val)
{
    config_buffer[3] = val;
    config_update();
}

uint8_t eeconfig_read_keymap(void)
{
    return config_buffer[4];
}
void eeconfig_write_keymap(uint8_t val)
{
    config_buffer[4] = val;
    config_update();
}
//add by geno
uint8_t eeconfig_read_custom(void)
{
    return config_buffer[6];
}
void eeconfig_write_custom(uint8_t val)
{
    config_buffer[6] = val;
    config_update();
}
void eeconfig_toggle_power(void)
{
    custom_config.raw = eeconfig_read_custom();
	  if(custom_config.power == 1) {
		custom_config.power = 0;
    eeconfig_write_custom(custom_config.raw);
		}	else {
	  custom_config.power = 1;
    eeconfig_write_custom(custom_config.raw);
		}
}
//----add by geno
#ifdef BACKLIGHT_ENABLE
uint8_t eeconfig_read_backlight(void)
{
    return config_buffer[7];
}
void eeconfig_write_backlight(uint8_t val)
{
    config_buffer[7] = val;
    config_update();
}
#endif

static void config_pstorage_callback_handler(pstorage_handle_t* p_handle, uint8_t op_code, uint32_t result, uint8_t* p_data, uint32_t data_len)
{
    switch (op_code) {
    case PSTORAGE_LOAD_OP_CODE:
        if (result == NRF_SUCCESS) {
            // Store operation successful.
        } else {
            // Store operation failed.
        }
        // Source memory can now be reused or freed.
        break;
    case PSTORAGE_UPDATE_OP_CODE:
        if (result == NRF_SUCCESS) {
            // Update operation successful.
        } else {
            // Update operation failed.
        }
        break;
    case PSTORAGE_CLEAR_OP_CODE:
        if (result == NRF_SUCCESS) {
            // Clear operation successful.
        } else {
            // Clear operation failed.
        }
        break;
    }
}

static void config_pstorage_init(void)
{
    //pstorage init in device manager, so do not init here

    //registe some parames
    pstorage_module_param_t param;
    uint32_t err_code;

    param.block_size = 0x10; // 4 byte is enough, but pstorage minimum block size is 0x10
    param.block_count = 1;
    param.cb = config_pstorage_callback_handler;

    err_code = pstorage_register(&param, &pstorage_base_block_id);
    APP_ERROR_CHECK(err_code);

    err_code = pstorage_block_identifier_get(&pstorage_base_block_id, 0, &block_handle);
    APP_ERROR_CHECK(err_code);

    config_read();
    if (config_buffer[0] != EECONFIG_MAGIC_NUMBER >> 8 || config_buffer[1] != EECONFIG_MAGIC_NUMBER % 0x100) {
        eeconfig_set_default();
        config_write();
    }
}

static void config_pstorage_write(uint8_t addr, uint8_t* data, uint8_t len)
{
    uint32_t err_code = pstorage_store(&block_handle, data, len, addr);
    APP_ERROR_CHECK(err_code);
}

static void config_pstorage_read(uint8_t addr, uint8_t* data, uint8_t len)
{
    uint32_t err_code = pstorage_load(data, &block_handle, len, addr);
    APP_ERROR_CHECK(err_code);
}

static void config_pstorage_update(uint8_t addr, uint8_t* data, uint8_t len)
{
    uint32_t err_code = pstorage_update(&block_handle, data, len, addr);
    APP_ERROR_CHECK(err_code);
}

static void config_update()
{
    config_pstorage_update(0, config_buffer, sizeof(config_buffer));
}
static void config_read()
{
    config_pstorage_read(0, config_buffer, sizeof(config_buffer));
}
static void config_write()
{
    config_pstorage_write(0, config_buffer, sizeof(config_buffer));
}
