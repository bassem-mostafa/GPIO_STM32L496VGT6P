// #############################################################################
// #### Copyright ##############################################################
// #############################################################################

/*
 * Copyright 2024 BaSSeM
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

// #############################################################################
// #### Description ############################################################
// #############################################################################

// #############################################################################
// #### Control Include(s) #####################################################
// #############################################################################

#include "Platform.h"

// #############################################################################
// #### Control Macro(s) #######################################################
// #############################################################################

#ifndef DEBUG
    #define DEBUG
#endif

#ifdef DEBUG
    #undef DEBUG
#endif

// #############################################################################
// #### File Guard #############################################################
// #############################################################################

#ifdef STM32L496xx

// #############################################################################
// #### Include(s) #############################################################
// #############################################################################

    #include <stdbool.h>

    #include "../../GPIO_Internal.h"
    #include "GPIO_STM32L496VGT6P.h"

    #include "stm32l4xx.h"

// #############################################################################
// #### Private Macro(s) #######################################################
// #############################################################################

// #############################################################################
// #### Private Type(s) ########################################################
// #############################################################################

typedef enum GPIO_STM32L496VGT6P_Event
{
    GPIO_STM32L496VGT6P_Event_None = 0,
    GPIO_STM32L496VGT6P_Event_ExternalInterrupt = UTIL_BIT( 0 ),
} GPIO_STM32L496VGT6P_Event_t;

typedef struct GPIO_STM32L496VGT6P_Instance
{
    GPIO_TypeDef * GPIOx;
    GPIO_InitTypeDef InitType;
    GPIO_STM32L496VGT6P_Event_t Event;
    GPIO_STM32L496VGT6P_OnInterrupt_t OnInterrupt;
} GPIO_STM32L496VGT6P_Instance_t;

typedef struct GPIO_STM32L496VGT6P_Context
{
    bool IsInitialized;
    GPIO_STM32L496VGT6P_Instance_t Instance[ GPIO_STM32L496VGT6P_Count ];
} GPIO_STM32L496VGT6P_Context_t;

// #############################################################################
// #### Private Method(s) Prototype ############################################
// #############################################################################

void HAL_GPIO_EXTI_Callback( uint16_t GPIO_Pin );

void EXTI0_IRQHandler( void );
void EXTI1_IRQHandler( void );
void EXTI2_IRQHandler( void );
void EXTI3_IRQHandler( void );
void EXTI4_IRQHandler( void );
void EXTI9_5_IRQHandler( void );
void EXTI15_10_IRQHandler( void );

static GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_Context_Initialize( void );
static GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_Context_Cycle( void );
static GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_Context_DeInitialize( void );

// #############################################################################
// #### Private Variable(s) ####################################################
// #############################################################################

static GPIO_STM32L496VGT6P_Context_t GPIO_STM32L496VGT6P_Context = {
    .IsInitialized = false,
};

// #############################################################################
// #### Private Method(s) ######################################################
// #############################################################################

void HAL_GPIO_EXTI_Callback( uint16_t GPIO_Pin )
{
    const GPIO_STM32L496VGT6P_t GPIO_PIN_0_Pool[] = {
        GPIO_STM32L496VGT6P_12, // PH0
        GPIO_STM32L496VGT6P_15, // PC0
        GPIO_STM32L496VGT6P_23, // PA0
        GPIO_STM32L496VGT6P_35, // PB0
        GPIO_STM32L496VGT6P_81, // PD0
        GPIO_STM32L496VGT6P_97, // PE0
    };
    const GPIO_STM32L496VGT6P_t GPIO_PIN_1_Pool[] = {
        GPIO_STM32L496VGT6P_13, // PH1
        GPIO_STM32L496VGT6P_16, // PC1
        GPIO_STM32L496VGT6P_24, // PA1
        GPIO_STM32L496VGT6P_36, // PB1
        GPIO_STM32L496VGT6P_82, // PD1
    };
    const GPIO_STM32L496VGT6P_t GPIO_PIN_2_Pool[] = {
        GPIO_STM32L496VGT6P_1,  // PE2
        GPIO_STM32L496VGT6P_17, // PC2
        GPIO_STM32L496VGT6P_25, // PA2
        GPIO_STM32L496VGT6P_37, // PB2
        GPIO_STM32L496VGT6P_83, // PD2
    };
    const GPIO_STM32L496VGT6P_t GPIO_PIN_3_Pool[] = {
        GPIO_STM32L496VGT6P_2,  // PE3
        GPIO_STM32L496VGT6P_18, // PC3
        GPIO_STM32L496VGT6P_26, // PA3
        GPIO_STM32L496VGT6P_84, // PD3
        GPIO_STM32L496VGT6P_89, // PB3
        GPIO_STM32L496VGT6P_94, // PH3
    };
    const GPIO_STM32L496VGT6P_t GPIO_PIN_4_Pool[] = {
        GPIO_STM32L496VGT6P_3,  // PE4
        GPIO_STM32L496VGT6P_29, // PA4
        GPIO_STM32L496VGT6P_33, // PC4
        GPIO_STM32L496VGT6P_85, // PD4
        GPIO_STM32L496VGT6P_90, // PB4
    };
    const GPIO_STM32L496VGT6P_t GPIO_PIN_5_Pool[] = {
        GPIO_STM32L496VGT6P_4,  // PE5
        GPIO_STM32L496VGT6P_30, // PA5
        GPIO_STM32L496VGT6P_34, // PC5
        GPIO_STM32L496VGT6P_86, // PD5
        GPIO_STM32L496VGT6P_91, // PB5
    };
    const GPIO_STM32L496VGT6P_t GPIO_PIN_6_Pool[] = {
        GPIO_STM32L496VGT6P_5,  // PE6
        GPIO_STM32L496VGT6P_31, // PA6
        GPIO_STM32L496VGT6P_63, // PC6
        GPIO_STM32L496VGT6P_87, // PD6
        GPIO_STM32L496VGT6P_92, // PB6
    };
    const GPIO_STM32L496VGT6P_t GPIO_PIN_7_Pool[] = {
        GPIO_STM32L496VGT6P_32, // PA7
        GPIO_STM32L496VGT6P_38, // PE7
        GPIO_STM32L496VGT6P_64, // PC7
        GPIO_STM32L496VGT6P_88, // PD7
        GPIO_STM32L496VGT6P_93, // PB7
    };
    const GPIO_STM32L496VGT6P_t GPIO_PIN_8_Pool[] = {
        GPIO_STM32L496VGT6P_39, // PE8
        GPIO_STM32L496VGT6P_55, // PD8
        GPIO_STM32L496VGT6P_65, // PC8
        GPIO_STM32L496VGT6P_67, // PA8
        GPIO_STM32L496VGT6P_95, // PB8
    };
    const GPIO_STM32L496VGT6P_t GPIO_PIN_9_Pool[] = {
        GPIO_STM32L496VGT6P_40, // PE9
        GPIO_STM32L496VGT6P_56, // PD9
        GPIO_STM32L496VGT6P_66, // PC9
        GPIO_STM32L496VGT6P_68, // PA9
        GPIO_STM32L496VGT6P_96, // PB9
    };
    const GPIO_STM32L496VGT6P_t GPIO_PIN_10_Pool[] = {
        GPIO_STM32L496VGT6P_41, // PE10
        GPIO_STM32L496VGT6P_47, // PB10
        GPIO_STM32L496VGT6P_57, // PD10
        GPIO_STM32L496VGT6P_69, // PA10
        GPIO_STM32L496VGT6P_78, // PC10
    };
    const GPIO_STM32L496VGT6P_t GPIO_PIN_11_Pool[] = {
        GPIO_STM32L496VGT6P_42, // PE11
        GPIO_STM32L496VGT6P_58, // PD11
        GPIO_STM32L496VGT6P_70, // PA11
        GPIO_STM32L496VGT6P_79, // PC11
    };
    const GPIO_STM32L496VGT6P_t GPIO_PIN_12_Pool[] = {
        GPIO_STM32L496VGT6P_43, // PE12
        GPIO_STM32L496VGT6P_51, // PB12
        GPIO_STM32L496VGT6P_59, // PD12
        GPIO_STM32L496VGT6P_71, // PA12
        GPIO_STM32L496VGT6P_80, // PC12
    };
    const GPIO_STM32L496VGT6P_t GPIO_PIN_13_Pool[] = {
        GPIO_STM32L496VGT6P_7,  // PC13
        GPIO_STM32L496VGT6P_44, // PE13
        GPIO_STM32L496VGT6P_52, // PB13
        GPIO_STM32L496VGT6P_60, // PD13
        GPIO_STM32L496VGT6P_72, // PA13
    };
    const GPIO_STM32L496VGT6P_t GPIO_PIN_14_Pool[] = {
        GPIO_STM32L496VGT6P_8,  // PC14
        GPIO_STM32L496VGT6P_45, // PE14
        GPIO_STM32L496VGT6P_53, // PB14
        GPIO_STM32L496VGT6P_61, // PD14
        GPIO_STM32L496VGT6P_76, // PA14
    };
    const GPIO_STM32L496VGT6P_t GPIO_PIN_15_Pool[] = {
        GPIO_STM32L496VGT6P_9,  // PC15
        GPIO_STM32L496VGT6P_46, // PE15
        GPIO_STM32L496VGT6P_54, // PB15
        GPIO_STM32L496VGT6P_62, // PD15
        GPIO_STM32L496VGT6P_77, // PA15
    };

    do
    {
        const GPIO_STM32L496VGT6P_t * GPIO_Pool = NULL;
        uint32_t GPIO_PoolSize = 0;
        switch ( GPIO_Pin )
        {
            case GPIO_PIN_0:
                GPIO_Pool = GPIO_PIN_0_Pool;
                GPIO_PoolSize = UTIL_ArraySize( GPIO_PIN_0_Pool );
                break;

            case GPIO_PIN_1:
                GPIO_Pool = GPIO_PIN_1_Pool;
                GPIO_PoolSize = UTIL_ArraySize( GPIO_PIN_1_Pool );
                break;

            case GPIO_PIN_2:
                GPIO_Pool = GPIO_PIN_2_Pool;
                GPIO_PoolSize = UTIL_ArraySize( GPIO_PIN_2_Pool );
                break;

            case GPIO_PIN_3:
                GPIO_Pool = GPIO_PIN_3_Pool;
                GPIO_PoolSize = UTIL_ArraySize( GPIO_PIN_3_Pool );
                break;

            case GPIO_PIN_4:
                GPIO_Pool = GPIO_PIN_4_Pool;
                GPIO_PoolSize = UTIL_ArraySize( GPIO_PIN_4_Pool );
                break;

            case GPIO_PIN_5:
                GPIO_Pool = GPIO_PIN_5_Pool;
                GPIO_PoolSize = UTIL_ArraySize( GPIO_PIN_5_Pool );
                break;

            case GPIO_PIN_6:
                GPIO_Pool = GPIO_PIN_6_Pool;
                GPIO_PoolSize = UTIL_ArraySize( GPIO_PIN_6_Pool );
                break;

            case GPIO_PIN_7:
                GPIO_Pool = GPIO_PIN_7_Pool;
                GPIO_PoolSize = UTIL_ArraySize( GPIO_PIN_7_Pool );
                break;

            case GPIO_PIN_8:
                GPIO_Pool = GPIO_PIN_8_Pool;
                GPIO_PoolSize = UTIL_ArraySize( GPIO_PIN_8_Pool );
                break;

            case GPIO_PIN_9:
                GPIO_Pool = GPIO_PIN_9_Pool;
                GPIO_PoolSize = UTIL_ArraySize( GPIO_PIN_9_Pool );
                break;

            case GPIO_PIN_10:
                GPIO_Pool = GPIO_PIN_10_Pool;
                GPIO_PoolSize = UTIL_ArraySize( GPIO_PIN_10_Pool );
                break;

            case GPIO_PIN_11:
                GPIO_Pool = GPIO_PIN_11_Pool;
                GPIO_PoolSize = UTIL_ArraySize( GPIO_PIN_11_Pool );
                break;

            case GPIO_PIN_12:
                GPIO_Pool = GPIO_PIN_12_Pool;
                GPIO_PoolSize = UTIL_ArraySize( GPIO_PIN_12_Pool );
                break;

            case GPIO_PIN_13:
                GPIO_Pool = GPIO_PIN_13_Pool;
                GPIO_PoolSize = UTIL_ArraySize( GPIO_PIN_13_Pool );
                break;

            case GPIO_PIN_14:
                GPIO_Pool = GPIO_PIN_14_Pool;
                GPIO_PoolSize = UTIL_ArraySize( GPIO_PIN_14_Pool );
                break;

            case GPIO_PIN_15:
                GPIO_Pool = GPIO_PIN_15_Pool;
                GPIO_PoolSize = UTIL_ArraySize( GPIO_PIN_15_Pool );
                break;

            default:
                break;
        }
        if ( GPIO_Pool == NULL )
        {
            break;
        }

        // Loop over port pin numbers equal to `GPIO_Pin` ex: GPIO_Pin=0, should loop over PA0, PB0, PC0, PD0, PE0, ...etc
        for ( uint32_t GPIO_Index = 0; GPIO_Index < GPIO_PoolSize; ++GPIO_Index )
        {
            GPIO_STM32L496VGT6P_t GPIO_x = GPIO_Pool[ GPIO_Index ];
            GPIO_STM32L496VGT6P_Instance_t * Instance = &GPIO_STM32L496VGT6P_Context.Instance[ GPIO_x ];
            GPIO_InitTypeDef * InitType = &Instance->InitType;

            if ( InitType->Pin == GPIO_Pin
                 && ( InitType->Mode == GPIO_MODE_IT_RISING
                      || InitType->Mode == GPIO_MODE_IT_FALLING
                      || InitType->Mode == GPIO_MODE_IT_RISING_FALLING ) )
            {
                Instance->Event |= GPIO_STM32L496VGT6P_Event_ExternalInterrupt;

                if ( Instance->OnInterrupt.Callback )
                {
                    Instance->OnInterrupt.Callback( GPIO_x, Instance->OnInterrupt.Context );
                }
            }
        }
    }
    while ( 0 );
}

void EXTI0_IRQHandler( void )
{
    HAL_GPIO_EXTI_IRQHandler( GPIO_PIN_0 );
}

void EXTI1_IRQHandler( void )
{
    HAL_GPIO_EXTI_IRQHandler( GPIO_PIN_1 );
}

void EXTI2_IRQHandler( void )
{
    HAL_GPIO_EXTI_IRQHandler( GPIO_PIN_2 );
}

void EXTI3_IRQHandler( void )
{
    HAL_GPIO_EXTI_IRQHandler( GPIO_PIN_3 );
}

void EXTI4_IRQHandler( void )
{
    HAL_GPIO_EXTI_IRQHandler( GPIO_PIN_4 );
}

void EXTI9_5_IRQHandler( void )
{
    HAL_GPIO_EXTI_IRQHandler( GPIO_PIN_5 );
    HAL_GPIO_EXTI_IRQHandler( GPIO_PIN_6 );
    HAL_GPIO_EXTI_IRQHandler( GPIO_PIN_7 );
    HAL_GPIO_EXTI_IRQHandler( GPIO_PIN_8 );
    HAL_GPIO_EXTI_IRQHandler( GPIO_PIN_9 );
}

void EXTI15_10_IRQHandler( void )
{
    HAL_GPIO_EXTI_IRQHandler( GPIO_PIN_10 );
    HAL_GPIO_EXTI_IRQHandler( GPIO_PIN_11 );
    HAL_GPIO_EXTI_IRQHandler( GPIO_PIN_12 );
    HAL_GPIO_EXTI_IRQHandler( GPIO_PIN_13 );
    HAL_GPIO_EXTI_IRQHandler( GPIO_PIN_14 );
    HAL_GPIO_EXTI_IRQHandler( GPIO_PIN_15 );
}

static GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_Context_Initialize( void )
{
    GPIO_STM32L496VGT6P_Status_t Status = GPIO_STM32L496VGT6P_Status_Success;

    do
    {
        GPIO_Trace( "%s( void )", __FUNCTION__ );

        if ( GPIO_STM32L496VGT6P_Context.IsInitialized )
        {
            // Already initialized
            break;
        }

        // FIXME Remove the usage of `MX_GPIO_Init()`
    #if 1
        extern void MX_GPIO_Init( void );
        MX_GPIO_Init( );
    #endif

        // TODO Enable All External Interrupts

        GPIO_STM32L496VGT6P_Context.IsInitialized = true;
    }
    while ( 0 );

    return Status;
}

static GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_Context_Cycle( void )
{
    GPIO_STM32L496VGT6P_Status_t Status = GPIO_STM32L496VGT6P_Status_Success;

    do
    {
        GPIO_Trace( "%s( void )", __FUNCTION__ );

        UTIL_UNUSED( GPIO_STM32L496VGT6P_Context );
    }
    while ( 0 );

    return Status;
}

static GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_Context_DeInitialize( void )
{
    GPIO_STM32L496VGT6P_Status_t Status = GPIO_STM32L496VGT6P_Status_Success;

    do
    {
        GPIO_Trace( "%s( void )", __FUNCTION__ );

        UTIL_UNUSED( GPIO_STM32L496VGT6P_Context );

        // TODO Disable All External Interrupts
    }
    while ( 0 );

    return Status;
}

// #############################################################################
// #### Public Method(s) #######################################################
// #############################################################################

GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_Initialize( GPIO_STM32L496VGT6P_t GPIOx )
{
    GPIO_STM32L496VGT6P_Status_t Status = GPIO_STM32L496VGT6P_Status_Success;

    do
    {
        GPIO_Trace( "%s( GPIOx=%d )", __FUNCTION__, GPIOx );

        if ( ( Status = GPIO_STM32L496VGT6P_Context_Initialize( ) ) != GPIO_STM32L496VGT6P_Status_Success )
        {
            break;
        }

        GPIO_STM32L496VGT6P_Instance_t * Instance = &GPIO_STM32L496VGT6P_Context.Instance[ GPIOx ];
        GPIO_InitTypeDef * InitType = &Instance->InitType;

        Instance->GPIOx = NULL;
        Instance->Event = GPIO_STM32L496VGT6P_Event_None;
        Instance->OnInterrupt = ( GPIO_STM32L496VGT6P_OnInterrupt_t ) {
            .Callback = NULL,
            .Context = NULL,
        };

        switch ( GPIOx )
        {
            case GPIO_STM32L496VGT6P_1:
            case GPIO_STM32L496VGT6P_2:
            case GPIO_STM32L496VGT6P_3:
            case GPIO_STM32L496VGT6P_4:
            case GPIO_STM32L496VGT6P_5:
                __HAL_RCC_GPIOE_CLK_ENABLE( );
                Instance->GPIOx = GPIOE;
                InitType->Pin = GPIO_PIN_2 << ( GPIOx - GPIO_STM32L496VGT6P_1 );
                break;

            case GPIO_STM32L496VGT6P_6:
                break;

            case GPIO_STM32L496VGT6P_7:
                __HAL_RCC_GPIOC_CLK_ENABLE( );
                Instance->GPIOx = GPIOC;
                InitType->Pin = GPIO_PIN_13 << ( GPIOx - GPIO_STM32L496VGT6P_7 );
                break;

            case GPIO_STM32L496VGT6P_8:
            case GPIO_STM32L496VGT6P_9:
            case GPIO_STM32L496VGT6P_10:
            case GPIO_STM32L496VGT6P_11:
            case GPIO_STM32L496VGT6P_12:
            case GPIO_STM32L496VGT6P_13:
            case GPIO_STM32L496VGT6P_14:
                break;

            case GPIO_STM32L496VGT6P_15:
            case GPIO_STM32L496VGT6P_16:
            case GPIO_STM32L496VGT6P_17:
            case GPIO_STM32L496VGT6P_18:
                __HAL_RCC_GPIOC_CLK_ENABLE( );
                Instance->GPIOx = GPIOC;
                InitType->Pin = GPIO_PIN_0 << ( GPIOx - GPIO_STM32L496VGT6P_15 );
                break;

            case GPIO_STM32L496VGT6P_19:
            case GPIO_STM32L496VGT6P_20:
            case GPIO_STM32L496VGT6P_21:
            case GPIO_STM32L496VGT6P_22:
                break;

            case GPIO_STM32L496VGT6P_23:
            case GPIO_STM32L496VGT6P_24:
            case GPIO_STM32L496VGT6P_25:
            case GPIO_STM32L496VGT6P_26:
                __HAL_RCC_GPIOA_CLK_ENABLE( );
                Instance->GPIOx = GPIOA;
                InitType->Pin = GPIO_PIN_0 << ( GPIOx - GPIO_STM32L496VGT6P_23 );
                break;

            case GPIO_STM32L496VGT6P_27:
            case GPIO_STM32L496VGT6P_28:
                break;

            case GPIO_STM32L496VGT6P_29:
            case GPIO_STM32L496VGT6P_30:
            case GPIO_STM32L496VGT6P_31:
            case GPIO_STM32L496VGT6P_32:
                __HAL_RCC_GPIOA_CLK_ENABLE( );
                Instance->GPIOx = GPIOA;
                InitType->Pin = GPIO_PIN_4 << ( GPIOx - GPIO_STM32L496VGT6P_29 );
                break;

            case GPIO_STM32L496VGT6P_33:
            case GPIO_STM32L496VGT6P_34:
                __HAL_RCC_GPIOC_CLK_ENABLE( );
                Instance->GPIOx = GPIOC;
                InitType->Pin = GPIO_PIN_4 << ( GPIOx - GPIO_STM32L496VGT6P_33 );
                break;

            case GPIO_STM32L496VGT6P_35:
            case GPIO_STM32L496VGT6P_36:
            case GPIO_STM32L496VGT6P_37:
                __HAL_RCC_GPIOB_CLK_ENABLE( );
                Instance->GPIOx = GPIOB;
                InitType->Pin = GPIO_PIN_0 << ( GPIOx - GPIO_STM32L496VGT6P_35 );
                break;

            case GPIO_STM32L496VGT6P_38:
            case GPIO_STM32L496VGT6P_39:
            case GPIO_STM32L496VGT6P_40:
            case GPIO_STM32L496VGT6P_41:
            case GPIO_STM32L496VGT6P_42:
            case GPIO_STM32L496VGT6P_43:
            case GPIO_STM32L496VGT6P_44:
            case GPIO_STM32L496VGT6P_45:
            case GPIO_STM32L496VGT6P_46:
                __HAL_RCC_GPIOE_CLK_ENABLE( );
                Instance->GPIOx = GPIOE;
                InitType->Pin = GPIO_PIN_7 << ( GPIOx - GPIO_STM32L496VGT6P_38 );
                break;

            case GPIO_STM32L496VGT6P_47:
                __HAL_RCC_GPIOB_CLK_ENABLE( );
                Instance->GPIOx = GPIOB;
                InitType->Pin = GPIO_PIN_10 << ( GPIOx - GPIO_STM32L496VGT6P_47 );
                break;

            case GPIO_STM32L496VGT6P_48:
            case GPIO_STM32L496VGT6P_49:
            case GPIO_STM32L496VGT6P_50:
                break;

            case GPIO_STM32L496VGT6P_51:
            case GPIO_STM32L496VGT6P_52:
            case GPIO_STM32L496VGT6P_53:
            case GPIO_STM32L496VGT6P_54:
                __HAL_RCC_GPIOB_CLK_ENABLE( );
                Instance->GPIOx = GPIOB;
                InitType->Pin = GPIO_PIN_12 << ( GPIOx - GPIO_STM32L496VGT6P_51 );
                break;

            case GPIO_STM32L496VGT6P_55:
            case GPIO_STM32L496VGT6P_56:
            case GPIO_STM32L496VGT6P_57:
            case GPIO_STM32L496VGT6P_58:
            case GPIO_STM32L496VGT6P_59:
            case GPIO_STM32L496VGT6P_60:
            case GPIO_STM32L496VGT6P_61:
            case GPIO_STM32L496VGT6P_62:
                __HAL_RCC_GPIOD_CLK_ENABLE( );
                Instance->GPIOx = GPIOD;
                InitType->Pin = GPIO_PIN_8 << ( GPIOx - GPIO_STM32L496VGT6P_55 );
                break;

            case GPIO_STM32L496VGT6P_63:
            case GPIO_STM32L496VGT6P_64:
            case GPIO_STM32L496VGT6P_65:
            case GPIO_STM32L496VGT6P_66:
                __HAL_RCC_GPIOC_CLK_ENABLE( );
                Instance->GPIOx = GPIOC;
                InitType->Pin = GPIO_PIN_6 << ( GPIOx - GPIO_STM32L496VGT6P_63 );
                break;

            case GPIO_STM32L496VGT6P_67:
            case GPIO_STM32L496VGT6P_68:
            case GPIO_STM32L496VGT6P_69:
                __HAL_RCC_GPIOA_CLK_ENABLE( );
                Instance->GPIOx = GPIOA;
                InitType->Pin = GPIO_PIN_8 << ( GPIOx - GPIO_STM32L496VGT6P_67 );
                break;

            case GPIO_STM32L496VGT6P_70:
            case GPIO_STM32L496VGT6P_71:
            case GPIO_STM32L496VGT6P_72:
            case GPIO_STM32L496VGT6P_73:
            case GPIO_STM32L496VGT6P_74:
            case GPIO_STM32L496VGT6P_75:
            case GPIO_STM32L496VGT6P_76:
                break;

            case GPIO_STM32L496VGT6P_77:
                __HAL_RCC_GPIOA_CLK_ENABLE( );
                Instance->GPIOx = GPIOA;
                InitType->Pin = GPIO_PIN_15 << ( GPIOx - GPIO_STM32L496VGT6P_77 );
                break;

            case GPIO_STM32L496VGT6P_78:
            case GPIO_STM32L496VGT6P_79:
            case GPIO_STM32L496VGT6P_80:
                __HAL_RCC_GPIOC_CLK_ENABLE( );
                Instance->GPIOx = GPIOC;
                InitType->Pin = GPIO_PIN_10 << ( GPIOx - GPIO_STM32L496VGT6P_78 );
                break;

            case GPIO_STM32L496VGT6P_81:
            case GPIO_STM32L496VGT6P_82:
            case GPIO_STM32L496VGT6P_83:
            case GPIO_STM32L496VGT6P_84:
            case GPIO_STM32L496VGT6P_85:
            case GPIO_STM32L496VGT6P_86:
            case GPIO_STM32L496VGT6P_87:
            case GPIO_STM32L496VGT6P_88:
                __HAL_RCC_GPIOD_CLK_ENABLE( );
                Instance->GPIOx = GPIOD;
                InitType->Pin = GPIO_PIN_0 << ( GPIOx - GPIO_STM32L496VGT6P_81 );
                break;

            case GPIO_STM32L496VGT6P_89:
            case GPIO_STM32L496VGT6P_90:
            case GPIO_STM32L496VGT6P_91:
            case GPIO_STM32L496VGT6P_92:
            case GPIO_STM32L496VGT6P_93:
                __HAL_RCC_GPIOB_CLK_ENABLE( );
                Instance->GPIOx = GPIOB;
                InitType->Pin = GPIO_PIN_3 << ( GPIOx - GPIO_STM32L496VGT6P_89 );
                break;

            case GPIO_STM32L496VGT6P_94:
                break;

            case GPIO_STM32L496VGT6P_95:
            case GPIO_STM32L496VGT6P_96:
                __HAL_RCC_GPIOB_CLK_ENABLE( );
                Instance->GPIOx = GPIOB;
                InitType->Pin = GPIO_PIN_8 << ( GPIOx - GPIO_STM32L496VGT6P_95 );
                break;

            case GPIO_STM32L496VGT6P_97:
                __HAL_RCC_GPIOE_CLK_ENABLE( );
                Instance->GPIOx = GPIOE;
                InitType->Pin = GPIO_PIN_0 << ( GPIOx - GPIO_STM32L496VGT6P_97 );
                break;

            case GPIO_STM32L496VGT6P_98:
            case GPIO_STM32L496VGT6P_99:
            case GPIO_STM32L496VGT6P_100:
                break;

            default:
                Status = GPIO_STM32L496VGT6P_Status_NotSupported;
                break;
        }

        if ( Status != GPIO_STM32L496VGT6P_Status_Success )
        {
            break;
        }

        // TODO Check the applicability of the following on special function IOs
        InitType->Mode = GPIO_MODE_ANALOG;
        InitType->Pull = GPIO_NOPULL;

        // FIXME This overwrites what MX_GPIO_Init is doing
        // Status = GPIO_STM32L496VGT6P_Commit( GPIOx );
    }
    while ( 0 );

    return Status;
}

GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_Cycle( GPIO_STM32L496VGT6P_t GPIOx )
{
    GPIO_STM32L496VGT6P_Status_t Status = GPIO_STM32L496VGT6P_Status_Success;

    do
    {
        GPIO_Trace( "%s( GPIOx=%d )", __FUNCTION__, GPIOx );

        if ( ( Status = GPIO_STM32L496VGT6P_Context_Cycle( ) ) != GPIO_STM32L496VGT6P_Status_Success )
        {
            break;
        }

        GPIO_STM32L496VGT6P_Instance_t * Instance = &GPIO_STM32L496VGT6P_Context.Instance[ GPIOx ];
        GPIO_STM32L496VGT6P_Event_t Event = Instance->Event; // CAUTION: Has to copy events occurred at the early start of the cycle, so as to be cleared at the end of the cycle,
                                                             //          which let events occurs after that for the next cycle call
        Instance->Event &= ~Event;                           //          Clear captured events

        if ( ( Event & GPIO_STM32L496VGT6P_Event_ExternalInterrupt ) == GPIO_STM32L496VGT6P_Event_ExternalInterrupt )
        {
            Event &= ~GPIO_STM32L496VGT6P_Event_ExternalInterrupt;
            GPIO_Debug( "External Interrupt: GPIO=%d", GPIOx );
        }

        if ( Event )
        {
            GPIO_Warning( "Not handled events %X: GPIOx=%d", Event, GPIOx );
        }
    }
    while ( 0 );

    return Status;
}

GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_DeInitialize( GPIO_STM32L496VGT6P_t GPIOx )
{
    GPIO_STM32L496VGT6P_Status_t Status = GPIO_STM32L496VGT6P_Status_Success;

    do
    {
        GPIO_Trace( "%s( GPIOx=%d )", __FUNCTION__, GPIOx );

        // TODO De-Initialize & Disable
        // TODO Apply Lowest Power Mode

        Status = GPIO_STM32L496VGT6P_Context_DeInitialize( );
    }
    while ( 0 );

    return Status;
}

GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_SetOnInterrupt( GPIO_STM32L496VGT6P_t GPIOx, GPIO_STM32L496VGT6P_OnInterrupt_t OnInterrupt )
{
    GPIO_STM32L496VGT6P_Status_t Status = GPIO_STM32L496VGT6P_Status_Success;

    do
    {
        GPIO_Trace( "%s( GPIOx=%d, OnInterrupt={Callback=%p, Context=%p} )", __FUNCTION__, GPIOx, OnInterrupt.Callback, OnInterrupt.Context );

        GPIO_STM32L496VGT6P_Instance_t * Instance = &GPIO_STM32L496VGT6P_Context.Instance[ GPIOx ];

        Instance->OnInterrupt = OnInterrupt;
    }
    while ( 0 );

    return Status;
}

GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_SetMode( GPIO_STM32L496VGT6P_t GPIOx, GPIO_STM32L496VGT6P_Mode_t Mode )
{
    GPIO_STM32L496VGT6P_Status_t Status = GPIO_STM32L496VGT6P_Status_Success;

    do
    {
        GPIO_Trace( "%s( GPIOx=%d, Mode=%d )", __FUNCTION__, GPIOx, Mode );

        GPIO_STM32L496VGT6P_Instance_t * Instance = &GPIO_STM32L496VGT6P_Context.Instance[ GPIOx ];

        switch ( Mode )
        {
            case GPIO_STM32L496VGT6P_Mode_Input:
                Instance->InitType.Mode = GPIO_MODE_INPUT;
                break;

            case GPIO_STM32L496VGT6P_Mode_Output:
                Instance->InitType.Mode = GPIO_MODE_OUTPUT_PP;
                break;

            case GPIO_STM32L496VGT6P_Mode_OutputOpenDrain:
                Instance->InitType.Mode = GPIO_MODE_OUTPUT_OD;
                break;

            case GPIO_STM32L496VGT6P_Mode_Interrupt:
                Instance->InitType.Mode = GPIO_MODE_IT_RISING_FALLING;
                break;

            case GPIO_STM32L496VGT6P_Mode_InterruptRising:
                Instance->InitType.Mode = GPIO_MODE_IT_RISING;
                break;

            case GPIO_STM32L496VGT6P_Mode_InterruptFalling:
                Instance->InitType.Mode = GPIO_MODE_IT_FALLING;
                break;

            case GPIO_STM32L496VGT6P_Mode_Event:
                Instance->InitType.Mode = GPIO_MODE_EVT_RISING_FALLING;
                break;

            case GPIO_STM32L496VGT6P_Mode_EventRising:
                Instance->InitType.Mode = GPIO_MODE_EVT_RISING;
                break;

            case GPIO_STM32L496VGT6P_Mode_EventFalling:
                Instance->InitType.Mode = GPIO_MODE_EVT_FALLING;
                break;

            case GPIO_STM32L496VGT6P_Mode_Alternate:
                Instance->InitType.Mode = GPIO_MODE_AF_PP;
                break;

            case GPIO_STM32L496VGT6P_Mode_AlternateOpenDrain:
                Instance->InitType.Mode = GPIO_MODE_AF_OD;
                break;

            case GPIO_STM32L496VGT6P_Mode_Analog:
                Instance->InitType.Mode = GPIO_MODE_ANALOG;
                break;

            case GPIO_STM32L496VGT6P_Mode_AnalogADC:
                Instance->InitType.Mode = GPIO_MODE_ANALOG_ADC_CONTROL;
                break;

            default:
                Status = GPIO_STM32L496VGT6P_Status_NotSupported;
                break;
        }
    }
    while ( 0 );

    return Status;
}

GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_SetPull( GPIO_STM32L496VGT6P_t GPIOx, GPIO_STM32L496VGT6P_Pull_t Pull )
{
    GPIO_STM32L496VGT6P_Status_t Status = GPIO_STM32L496VGT6P_Status_Success;

    do
    {
        GPIO_Trace( "%s( GPIOx=%d, Pull=%d )", __FUNCTION__, GPIOx, Pull );

        GPIO_STM32L496VGT6P_Instance_t * Instance = &GPIO_STM32L496VGT6P_Context.Instance[ GPIOx ];

        switch ( Pull )
        {
            case GPIO_STM32L496VGT6P_Pull_None:
                Instance->InitType.Pull = GPIO_NOPULL;
                break;

            case GPIO_STM32L496VGT6P_Pull_Up:
                Instance->InitType.Pull = GPIO_PULLUP;
                break;

            case GPIO_STM32L496VGT6P_Pull_Down:
                Instance->InitType.Pull = GPIO_PULLDOWN;
                break;

            default:
                Status = GPIO_STM32L496VGT6P_Status_NotSupported;
                break;
        }
    }
    while ( 0 );

    return Status;
}

GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_SetSpeed( GPIO_STM32L496VGT6P_t GPIOx, GPIO_STM32L496VGT6P_Speed_t Speed )
{
    GPIO_STM32L496VGT6P_Status_t Status = GPIO_STM32L496VGT6P_Status_Success;

    do
    {
        GPIO_Trace( "%s( GPIOx=%d, Speed=%d )", __FUNCTION__, GPIOx, Speed );

        GPIO_STM32L496VGT6P_Instance_t * Instance = &GPIO_STM32L496VGT6P_Context.Instance[ GPIOx ];

        switch ( Speed )
        {
            case GPIO_STM32L496VGT6P_Speed_Low:
                Instance->InitType.Speed = GPIO_SPEED_FREQ_LOW;
                break;

            case GPIO_STM32L496VGT6P_Speed_Medium:
                Instance->InitType.Speed = GPIO_SPEED_FREQ_MEDIUM;
                break;

            case GPIO_STM32L496VGT6P_Speed_High:
                Instance->InitType.Speed = GPIO_SPEED_FREQ_HIGH;
                break;

            case GPIO_STM32L496VGT6P_Speed_VeryHigh:
                Instance->InitType.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
                break;

            default:
                Status = GPIO_STM32L496VGT6P_Status_NotSupported;
                break;
        }
    }
    while ( 0 );

    return Status;
}

GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_SetFunction( GPIO_STM32L496VGT6P_t GPIOx, GPIO_STM32L496VGT6P_Function_t Function )
{
    GPIO_STM32L496VGT6P_Status_t Status = GPIO_STM32L496VGT6P_Status_Success;

    do
    {
        GPIO_Trace( "%s( GPIOx=%d, Function=%d )", __FUNCTION__, GPIOx, Function );

        GPIO_STM32L496VGT6P_Instance_t * Instance = &GPIO_STM32L496VGT6P_Context.Instance[ GPIOx ];

        switch ( Function )
        {
            case GPIO_STM32L496VGT6P_Function_0:
            case GPIO_STM32L496VGT6P_Function_1:
            case GPIO_STM32L496VGT6P_Function_2:
            case GPIO_STM32L496VGT6P_Function_3:
            case GPIO_STM32L496VGT6P_Function_4:
            case GPIO_STM32L496VGT6P_Function_5:
            case GPIO_STM32L496VGT6P_Function_6:
            case GPIO_STM32L496VGT6P_Function_7:
            case GPIO_STM32L496VGT6P_Function_8:
            case GPIO_STM32L496VGT6P_Function_9:
            case GPIO_STM32L496VGT6P_Function_10:
            case GPIO_STM32L496VGT6P_Function_11:
            case GPIO_STM32L496VGT6P_Function_12:
            case GPIO_STM32L496VGT6P_Function_13:
            case GPIO_STM32L496VGT6P_Function_14:
            case GPIO_STM32L496VGT6P_Function_15:
                // TODO Verify Alternate Function Application
                break;

            default:
                Status = GPIO_STM32L496VGT6P_Status_NotSupported;
                break;
        }
        if ( Status != GPIO_STM32L496VGT6P_Status_Success )
        {
            break;
        }

        Instance->InitType.Alternate = Function;
    }
    while ( 0 );

    return Status;
}

GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_Commit( GPIO_STM32L496VGT6P_t GPIOx )
{
    GPIO_STM32L496VGT6P_Status_t Status = GPIO_STM32L496VGT6P_Status_Success;

    do
    {
        GPIO_Trace( "%s( GPIOx=%d )", __FUNCTION__, GPIOx );

        GPIO_STM32L496VGT6P_Instance_t * Instance = &GPIO_STM32L496VGT6P_Context.Instance[ GPIOx ];

        if ( Instance->GPIOx != NULL )
        {
            HAL_GPIO_Init( Instance->GPIOx, &Instance->InitType );
        }
    }
    while ( 0 );

    return Status;
}

GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_Write( GPIO_STM32L496VGT6P_t GPIOx, GPIO_STM32L496VGT6P_Value_t Value )
{
    GPIO_STM32L496VGT6P_Status_t Status = GPIO_STM32L496VGT6P_Status_Success;

    do
    {
        GPIO_Trace( "%s( GPIOx=%d, Value=%d )", __FUNCTION__, GPIOx, Value );

        GPIO_STM32L496VGT6P_Instance_t * Instance = &GPIO_STM32L496VGT6P_Context.Instance[ GPIOx ];

        if ( Instance->GPIOx != NULL )
        {
            HAL_GPIO_WritePin( Instance->GPIOx, Instance->InitType.Pin, Value );
        }
    }
    while ( 0 );

    return Status;
}

GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_Read( GPIO_STM32L496VGT6P_t GPIOx, GPIO_STM32L496VGT6P_Value_t * Value )
{
    GPIO_STM32L496VGT6P_Status_t Status = GPIO_STM32L496VGT6P_Status_Success;

    do
    {
        GPIO_Trace( "%s( GPIOx=%d, Value=%p )", __FUNCTION__, GPIOx, Value );

        if ( Value == NULL )
        {
            Status = GPIO_STM32L496VGT6P_Status_ArgumentInvalid;
            break;
        }

        GPIO_STM32L496VGT6P_Instance_t * Instance = &GPIO_STM32L496VGT6P_Context.Instance[ GPIOx ];

        if ( Instance->GPIOx == NULL )
        {
            // Bypass not assigned
            break;
        }

        *Value = HAL_GPIO_ReadPin( Instance->GPIOx, Instance->InitType.Pin );
    }
    while ( 0 );

    return Status;
}

// #############################################################################
// #### Public Variable(s) #####################################################
// #############################################################################

const char GPIO_STM32L496VGT6P_VERSION[] = "0.0.0.v20260913-1832";

// #############################################################################
// #### File Guard #############################################################
// #############################################################################

#endif /* STM32L496xx */

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################
