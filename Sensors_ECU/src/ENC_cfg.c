/*
 * ENC_cfg.c
 *
 *  Created on: Jun 24, 2022
 *      Author: سابق و لاحق
 */

#include <stdint.h>
#include <diag/trace.h>
#include "../system/include/cmsis/stm32f10x.h"
#include "../system/include/stm32f1-stdperiph/stm32f10x_tim.h"
#include "../system/include/stm32f1-stdperiph/stm32f10x_rcc.h"
#include "../system/include/stm32f1-stdperiph/stm32f10x_gpio.h"
#include "../HAL/Encoder/ENC.h"
#include "../HAL/Encoder/ENC_cfg.h"

const ENC_tstrCfg ENC_strCfgArr[ENC_u8ENCODERS_NUM] = {
		[ENC_u8MOTOR1_ENCODER] = {
				.ENC_u32Port = ENC_u32PORTA,
				.ENC_u64Pin = ENC_u64PIN_0
		}
};

