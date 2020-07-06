#include "app_util.h"
#include "app_usbd_core.h"
#include "app_usbd.h"
#include "app_usbd_string_desc.h"
#include "app_usbd_cdc_acm.h"
#include "app_usbd_serial_num.h"
#include "nrf_delay.h"


/**
 * @brief Enable power USB detection
 *
 * Configure if example supports USB port connection
 */
#ifndef USBD_POWER_DETECTION
#define USBD_POWER_DETECTION true
#endif

#define READ_SIZE 1




void cdc_acm_user_ev_handler(app_usbd_class_inst_t const * p_inst,
                                    app_usbd_cdc_acm_user_event_t event);

void usbd_user_ev_handler(app_usbd_event_type_t event);

#define CDC_ACM_COMM_INTERFACE  0
#define CDC_ACM_COMM_EPIN       NRF_DRV_USBD_EPIN2

#define CDC_ACM_DATA_INTERFACE  1
#define CDC_ACM_DATA_EPIN       NRF_DRV_USBD_EPIN1
#define CDC_ACM_DATA_EPOUT      NRF_DRV_USBD_EPOUT1


///**
// * @brief CDC_ACM class instance
// * */
//APP_USBD_CDC_ACM_GLOBAL_DEF(m_app_cdc_acm,
//                            cdc_acm_user_ev_handler,
//                            CDC_ACM_COMM_INTERFACE,
//                            CDC_ACM_DATA_INTERFACE,
//                            CDC_ACM_COMM_EPIN,
//                            CDC_ACM_DATA_EPIN,
//                            CDC_ACM_DATA_EPOUT,
//                            APP_USBD_CDC_COMM_PROTOCOL_AT_V250
//);