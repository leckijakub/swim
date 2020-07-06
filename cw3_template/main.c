/**
 * Copyright (c) 2017 - 2019, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#include "nrf.h"
#include "nrf_drv_usbd.h"
#include "nrf_drv_clock.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "nrf_drv_power.h"

#include "app_error.h"

#include "boards.h"
#include "bsp.h"
#include "usb.h"
#include "app_timer.h"

// NOTE: lab3
#include "nrf_drv_gpiote.h"

// NOTE: uzupelnic odpowiednim pinem dla fototranzystora
#define PIN_IN BSP_BUTTON_0

extern char m_rx_buffer[READ_SIZE];
extern char m_tx_buffer[NRF_DRV_USBD_EPSIZE];
extern bool usb_ready;

extern app_usbd_cdc_acm_t m_app_cdc_acm;


static void init_bsp(void)
{
    ret_code_t ret;
    ret = bsp_init(BSP_INIT_LEDS, 0);
    APP_ERROR_CHECK(ret);
}

static void usb_init(app_usbd_config_t usbd_config)
{
    ret_code_t ret;
    
    app_usbd_serial_num_generate();

    ret = app_usbd_init(&usbd_config);
    APP_ERROR_CHECK(ret);

    app_usbd_class_inst_t const * class_cdc_acm = app_usbd_cdc_acm_class_inst_get(&m_app_cdc_acm);
    ret = app_usbd_class_append(class_cdc_acm);
    APP_ERROR_CHECK(ret);

    if (USBD_POWER_DETECTION)
    {
        ret = app_usbd_power_events_enable();
        APP_ERROR_CHECK(ret);
    }
    else
    {
        app_usbd_enable();
        app_usbd_start();
    }
}


int main(void)
{
    ret_code_t ret;
    static const app_usbd_config_t usbd_config = {
        .ev_state_proc = usbd_user_ev_handler
    };

    ret = nrf_drv_clock_init();
    APP_ERROR_CHECK(ret);
    
    nrf_drv_clock_lfclk_request(NULL);

    while(!nrf_drv_clock_lfclk_is_running())
    {
        /* Just waiting */
    }

    ret = app_timer_init();
    APP_ERROR_CHECK(ret);

    usb_init(usbd_config);
    init_bsp();
    
    bsp_board_led_on(BSP_BOARD_LED_0);

    bool msg_sent = 0;

    while (true)
    {

        while (app_usbd_event_queue_process())
        {
            /* Nothing to do */
        }

        if (usb_ready && !msg_sent)
        {
            size_t size = sprintf(m_tx_buffer, "Systemy wbudowane i mikrokontrolery!\r\n");
            app_usbd_cdc_acm_write(&m_app_cdc_acm, m_tx_buffer, size);
            msg_sent = 1;
        }

        /* Sleep CPU only if there was no interrupt since last loop processing */
        __WFE();
    }
}

/** @} */
