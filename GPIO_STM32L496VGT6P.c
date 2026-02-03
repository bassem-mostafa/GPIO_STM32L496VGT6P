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

typedef struct GPIO_STM32L496VGT6P_Instance_Context
{
    GPIO_TypeDef * GPIOx;
    GPIO_InitTypeDef InitType;
    GPIO_STM32L496VGT6P_Event_t Event;
} GPIO_STM32L496VGT6P_Instance_Context_t;

typedef struct GPIO_STM32L496VGT6P_Context
{
    TIM_Timestamp_t Timestamp;
    GPIO_STM32L496VGT6P_Instance_Context_t Context[ GPIO_STM32L496VGT6P_Count ];
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

static GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_Instance_Initialize( GPIO_STM32L496VGT6P_Instance_t * Instance );
static GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_Instance_Cycle( GPIO_STM32L496VGT6P_Instance_t * Instance );
static GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_Instance_DeInitialize( GPIO_STM32L496VGT6P_Instance_t * Instance );

static GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_Instance_Write( GPIO_STM32L496VGT6P_Instance_t * Instance, GPIO_STM32L496VGT6P_Value_t Value );
static GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_Instance_Read( GPIO_STM32L496VGT6P_Instance_t * Instance, GPIO_STM32L496VGT6P_Value_t * Value );

static GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_Instance_SetMode( GPIO_STM32L496VGT6P_Instance_t * Instance, GPIO_STM32L496VGT6P_Mode_t Mode );
static GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_Instance_SetPull( GPIO_STM32L496VGT6P_Instance_t * Instance, GPIO_STM32L496VGT6P_Pull_t Pull );
static GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_Instance_SetSpeed( GPIO_STM32L496VGT6P_Instance_t * Instance, GPIO_STM32L496VGT6P_Speed_t Speed );
static GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_Instance_SetFunction( GPIO_STM32L496VGT6P_Instance_t * Instance, GPIO_STM32L496VGT6P_Function_t Function );
static GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_Instance_Commit( GPIO_STM32L496VGT6P_Instance_t * Instance );

// #############################################################################
// #### Private Variable(s) ####################################################
// #############################################################################

static GPIO_STM32L496VGT6P_Context_t GPIO_STM32L496VGT6P_Context;

// #############################################################################
// #### Private Method(s) ######################################################
// #############################################################################

void HAL_GPIO_EXTI_Callback( uint16_t GPIO_Pin )
{
    for ( GPIO_STM32L496VGT6P_t GPIO_x = GPIO_STM32L496VGT6P_1; GPIO_x < GPIO_STM32L496VGT6P_Count; ++GPIO_x )
    {
        GPIO_STM32L496VGT6P_Instance_Context_t * Context = &GPIO_STM32L496VGT6P_Context.Context[ GPIO_x ];
        GPIO_InitTypeDef * InitType = &Context->InitType;

        if ( InitType->Pin == GPIO_Pin
             && ( InitType->Mode == GPIO_MODE_IT_RISING
                  || InitType->Mode == GPIO_MODE_IT_FALLING
                  || InitType->Mode == GPIO_MODE_IT_RISING_FALLING ) )
        {
            Context->Event |= GPIO_STM32L496VGT6P_Event_ExternalInterrupt;
        }
    }
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

        // FIXME Remove the usage of `MX_GPIO_Init()`
    #if 1
        extern void MX_GPIO_Init( void );
        MX_GPIO_Init( );
    #endif

        // TODO Enable All External Interrupts
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

        // TODO Disable All External Interrupts
    }
    while ( 0 );

    return Status;
}

static GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_Instance_Initialize( GPIO_STM32L496VGT6P_Instance_t * Instance )
{
    GPIO_STM32L496VGT6P_Status_t Status = GPIO_STM32L496VGT6P_Status_Success;

    do
    {
        GPIO_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        if ( Instance == NULL )
        {
            Status = GPIO_STM32L496VGT6P_Status_ArgumentInvalid;
            break;
        }

        GPIO_STM32L496VGT6P_Instance_Context_t * Context = &GPIO_STM32L496VGT6P_Context.Context[ Instance->GPIOx ];
        GPIO_InitTypeDef * InitType = &Context->InitType;

        switch ( Instance->GPIOx )
        {
            case GPIO_STM32L496VGT6P_1:
            case GPIO_STM32L496VGT6P_2:
            case GPIO_STM32L496VGT6P_3:
            case GPIO_STM32L496VGT6P_4:
            case GPIO_STM32L496VGT6P_5:
                __HAL_RCC_GPIOE_CLK_ENABLE( );
                Context->GPIOx = GPIOE;
                InitType->Pin = GPIO_PIN_2 << ( Instance->GPIOx - GPIO_STM32L496VGT6P_1 );
                break;

            case GPIO_STM32L496VGT6P_6:
                break;

            case GPIO_STM32L496VGT6P_7:
                __HAL_RCC_GPIOC_CLK_ENABLE( );
                Context->GPIOx = GPIOC;
                InitType->Pin = GPIO_PIN_13 << ( Instance->GPIOx - GPIO_STM32L496VGT6P_7 );
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
                Context->GPIOx = GPIOC;
                InitType->Pin = GPIO_PIN_0 << ( Instance->GPIOx - GPIO_STM32L496VGT6P_15 );
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
                Context->GPIOx = GPIOA;
                InitType->Pin = GPIO_PIN_0 << ( Instance->GPIOx - GPIO_STM32L496VGT6P_23 );
                break;

            case GPIO_STM32L496VGT6P_27:
            case GPIO_STM32L496VGT6P_28:
                break;

            case GPIO_STM32L496VGT6P_29:
            case GPIO_STM32L496VGT6P_30:
            case GPIO_STM32L496VGT6P_31:
            case GPIO_STM32L496VGT6P_32:
                __HAL_RCC_GPIOA_CLK_ENABLE( );
                Context->GPIOx = GPIOA;
                InitType->Pin = GPIO_PIN_4 << ( Instance->GPIOx - GPIO_STM32L496VGT6P_29 );
                break;

            case GPIO_STM32L496VGT6P_33:
            case GPIO_STM32L496VGT6P_34:
                __HAL_RCC_GPIOC_CLK_ENABLE( );
                Context->GPIOx = GPIOC;
                InitType->Pin = GPIO_PIN_4 << ( Instance->GPIOx - GPIO_STM32L496VGT6P_33 );
                break;

            case GPIO_STM32L496VGT6P_35:
            case GPIO_STM32L496VGT6P_36:
            case GPIO_STM32L496VGT6P_37:
                __HAL_RCC_GPIOB_CLK_ENABLE( );
                Context->GPIOx = GPIOB;
                InitType->Pin = GPIO_PIN_0 << ( Instance->GPIOx - GPIO_STM32L496VGT6P_35 );
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
                Context->GPIOx = GPIOE;
                InitType->Pin = GPIO_PIN_7 << ( Instance->GPIOx - GPIO_STM32L496VGT6P_38 );
                break;

            case GPIO_STM32L496VGT6P_47:
                __HAL_RCC_GPIOB_CLK_ENABLE( );
                Context->GPIOx = GPIOB;
                InitType->Pin = GPIO_PIN_10 << ( Instance->GPIOx - GPIO_STM32L496VGT6P_47 );
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
                Context->GPIOx = GPIOB;
                InitType->Pin = GPIO_PIN_12 << ( Instance->GPIOx - GPIO_STM32L496VGT6P_51 );
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
                Context->GPIOx = GPIOD;
                InitType->Pin = GPIO_PIN_8 << ( Instance->GPIOx - GPIO_STM32L496VGT6P_55 );
                break;

            case GPIO_STM32L496VGT6P_63:
            case GPIO_STM32L496VGT6P_64:
            case GPIO_STM32L496VGT6P_65:
            case GPIO_STM32L496VGT6P_66:
                __HAL_RCC_GPIOC_CLK_ENABLE( );
                Context->GPIOx = GPIOC;
                InitType->Pin = GPIO_PIN_6 << ( Instance->GPIOx - GPIO_STM32L496VGT6P_63 );
                break;

            case GPIO_STM32L496VGT6P_67:
            case GPIO_STM32L496VGT6P_68:
            case GPIO_STM32L496VGT6P_69:
                __HAL_RCC_GPIOA_CLK_ENABLE( );
                Context->GPIOx = GPIOA;
                InitType->Pin = GPIO_PIN_8 << ( Instance->GPIOx - GPIO_STM32L496VGT6P_67 );
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
                Context->GPIOx = GPIOA;
                InitType->Pin = GPIO_PIN_15 << ( Instance->GPIOx - GPIO_STM32L496VGT6P_77 );
                break;

            case GPIO_STM32L496VGT6P_78:
            case GPIO_STM32L496VGT6P_79:
            case GPIO_STM32L496VGT6P_80:
                __HAL_RCC_GPIOC_CLK_ENABLE( );
                Context->GPIOx = GPIOC;
                InitType->Pin = GPIO_PIN_10 << ( Instance->GPIOx - GPIO_STM32L496VGT6P_78 );
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
                Context->GPIOx = GPIOD;
                InitType->Pin = GPIO_PIN_0 << ( Instance->GPIOx - GPIO_STM32L496VGT6P_81 );
                break;

            case GPIO_STM32L496VGT6P_89:
            case GPIO_STM32L496VGT6P_90:
            case GPIO_STM32L496VGT6P_91:
            case GPIO_STM32L496VGT6P_92:
            case GPIO_STM32L496VGT6P_93:
                __HAL_RCC_GPIOB_CLK_ENABLE( );
                Context->GPIOx = GPIOB;
                InitType->Pin = GPIO_PIN_3 << ( Instance->GPIOx - GPIO_STM32L496VGT6P_89 );
                break;

            case GPIO_STM32L496VGT6P_94:
                break;

            case GPIO_STM32L496VGT6P_95:
            case GPIO_STM32L496VGT6P_96:
                __HAL_RCC_GPIOB_CLK_ENABLE( );
                Context->GPIOx = GPIOB;
                InitType->Pin = GPIO_PIN_8 << ( Instance->GPIOx - GPIO_STM32L496VGT6P_95 );
                break;

            case GPIO_STM32L496VGT6P_97:
                __HAL_RCC_GPIOE_CLK_ENABLE( );
                Context->GPIOx = GPIOE;
                InitType->Pin = GPIO_PIN_0 << ( Instance->GPIOx - GPIO_STM32L496VGT6P_97 );
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

        Instance->Context = Context;

        Status = GPIO_STM32L496VGT6P_Instance_Commit( Instance );
    }
    while ( 0 );

    return Status;
}

static GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_Instance_Cycle( GPIO_STM32L496VGT6P_Instance_t * Instance )
{
    GPIO_STM32L496VGT6P_Status_t Status = GPIO_STM32L496VGT6P_Status_Success;

    do
    {
        GPIO_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        GPIO_STM32L496VGT6P_Instance_Context_t * Context = &GPIO_STM32L496VGT6P_Context.Context[ Instance->GPIOx ];
        GPIO_STM32L496VGT6P_Event_t Event = Context->Event; // CAUTION: Has to copy events occurred at the early start of the cycle, so as to be cleared at the end of the cycle,
                                                            //          which let events occurs after that for the next cycle call

        if ( ( Event & GPIO_STM32L496VGT6P_Event_ExternalInterrupt ) == GPIO_STM32L496VGT6P_Event_ExternalInterrupt )
        {
            Context->Event &= ~GPIO_STM32L496VGT6P_Event_ExternalInterrupt;
            GPIO_Debug( "External Interrupt: Instance=%p, GPIO=%d", Instance, Instance->GPIOx );

            if ( Instance->OnInterrupt != NULL )
            {
                Instance->OnInterrupt( Instance );
            }
        }
    }
    while ( 0 );

    return Status;
}

static GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_Instance_DeInitialize( GPIO_STM32L496VGT6P_Instance_t * Instance )
{
    GPIO_STM32L496VGT6P_Status_t Status = GPIO_STM32L496VGT6P_Status_Success;

    do
    {
        GPIO_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        // TODO De-Initialize & Disable
        // TODO Apply Lowest Power Mode
    }
    while ( 0 );

    return Status;
}

static GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_Instance_Write( GPIO_STM32L496VGT6P_Instance_t * Instance, GPIO_STM32L496VGT6P_Value_t Value )
{
    GPIO_STM32L496VGT6P_Status_t Status = GPIO_STM32L496VGT6P_Status_Success;

    do
    {
        GPIO_Trace( "%s( Instance=%p, Value=%d )", __FUNCTION__, Instance, Value );

        if ( Instance == NULL )
        {
            Status = GPIO_STM32L496VGT6P_Status_ArgumentInvalid;
            break;
        }

        GPIO_STM32L496VGT6P_Instance_Context_t * Context = &GPIO_STM32L496VGT6P_Context.Context[ Instance->GPIOx ];

        if ( Context->GPIOx != NULL )
        {
            HAL_GPIO_WritePin( Context->GPIOx, Context->InitType.Pin, Value );
        }
    }
    while ( 0 );

    return Status;
}

static GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_Instance_Read( GPIO_STM32L496VGT6P_Instance_t * Instance, GPIO_STM32L496VGT6P_Value_t * Value )
{
    GPIO_STM32L496VGT6P_Status_t Status = GPIO_STM32L496VGT6P_Status_Success;

    do
    {
        GPIO_Trace( "%s( Instance=%p, Value=%p )", __FUNCTION__, Instance, Value );

        if ( Instance == NULL || Value == NULL )
        {
            Status = GPIO_STM32L496VGT6P_Status_ArgumentInvalid;
            break;
        }

        GPIO_STM32L496VGT6P_Instance_Context_t * Context = &GPIO_STM32L496VGT6P_Context.Context[ Instance->GPIOx ];

        if ( Context->GPIOx != NULL )
        {
            *Value = HAL_GPIO_ReadPin( Context->GPIOx, Context->InitType.Pin );
        }
    }
    while ( 0 );

    return Status;
}

static GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_Instance_SetMode( GPIO_STM32L496VGT6P_Instance_t * Instance, GPIO_STM32L496VGT6P_Mode_t Mode )
{
    GPIO_STM32L496VGT6P_Status_t Status = GPIO_STM32L496VGT6P_Status_Success;

    do
    {
        GPIO_Trace( "%s( Instance=%p, Mode=%d )", __FUNCTION__, Instance, Mode );

        if ( Instance == NULL )
        {
            Status = GPIO_STM32L496VGT6P_Status_ArgumentInvalid;
            break;
        }

        GPIO_STM32L496VGT6P_Instance_Context_t * Context = &GPIO_STM32L496VGT6P_Context.Context[ Instance->GPIOx ];

        switch ( Mode )
        {
            case GPIO_STM32L496VGT6P_Mode_Input:
                Context->InitType.Mode = GPIO_MODE_INPUT;
                break;

            case GPIO_STM32L496VGT6P_Mode_Output:
                Context->InitType.Mode = GPIO_MODE_OUTPUT_PP;
                break;

            case GPIO_STM32L496VGT6P_Mode_OutputOpenDrain:
                Context->InitType.Mode = GPIO_MODE_OUTPUT_OD;
                break;

            case GPIO_STM32L496VGT6P_Mode_Interrupt:
                Context->InitType.Mode = GPIO_MODE_IT_RISING_FALLING;
                break;

            case GPIO_STM32L496VGT6P_Mode_InterruptRising:
                Context->InitType.Mode = GPIO_MODE_IT_RISING;
                break;

            case GPIO_STM32L496VGT6P_Mode_InterruptFalling:
                Context->InitType.Mode = GPIO_MODE_IT_FALLING;
                break;

            case GPIO_STM32L496VGT6P_Mode_Event:
                Context->InitType.Mode = GPIO_MODE_EVT_RISING_FALLING;
                break;

            case GPIO_STM32L496VGT6P_Mode_EventRising:
                Context->InitType.Mode = GPIO_MODE_EVT_RISING;
                break;

            case GPIO_STM32L496VGT6P_Mode_EventFalling:
                Context->InitType.Mode = GPIO_MODE_EVT_FALLING;
                break;

            case GPIO_STM32L496VGT6P_Mode_Alternate:
                Context->InitType.Mode = GPIO_MODE_AF_PP;
                break;

            case GPIO_STM32L496VGT6P_Mode_AlternateOpenDrain:
                Context->InitType.Mode = GPIO_MODE_AF_OD;
                break;

            case GPIO_STM32L496VGT6P_Mode_Analog:
                Context->InitType.Mode = GPIO_MODE_ANALOG;
                break;

            case GPIO_STM32L496VGT6P_Mode_AnalogADC:
                Context->InitType.Mode = GPIO_MODE_ANALOG_ADC_CONTROL;
                break;

            default:
                Status = GPIO_STM32L496VGT6P_Status_NotSupported;
                break;
        }
    }
    while ( 0 );

    return Status;
}

static GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_Instance_SetPull( GPIO_STM32L496VGT6P_Instance_t * Instance, GPIO_STM32L496VGT6P_Pull_t Pull )
{
    GPIO_STM32L496VGT6P_Status_t Status = GPIO_STM32L496VGT6P_Status_Success;

    do
    {
        GPIO_Trace( "%s( Instance=%p, Pull=%d )", __FUNCTION__, Instance, Pull );

        if ( Instance == NULL )
        {
            Status = GPIO_STM32L496VGT6P_Status_ArgumentInvalid;
            break;
        }

        GPIO_STM32L496VGT6P_Instance_Context_t * Context = &GPIO_STM32L496VGT6P_Context.Context[ Instance->GPIOx ];

        switch ( Pull )
        {
            case GPIO_STM32L496VGT6P_Pull_None:
                Context->InitType.Pull = GPIO_NOPULL;
                break;

            case GPIO_STM32L496VGT6P_Pull_Up:
                Context->InitType.Pull = GPIO_PULLUP;
                break;

            case GPIO_STM32L496VGT6P_Pull_Down:
                Context->InitType.Pull = GPIO_PULLDOWN;
                break;

            default:
                Status = GPIO_STM32L496VGT6P_Status_NotSupported;
                break;
        }
    }
    while ( 0 );

    return Status;
}

static GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_Instance_SetSpeed( GPIO_STM32L496VGT6P_Instance_t * Instance, GPIO_STM32L496VGT6P_Speed_t Speed )
{
    GPIO_STM32L496VGT6P_Status_t Status = GPIO_STM32L496VGT6P_Status_Success;

    do
    {
        GPIO_Trace( "%s( Instance=%p, Speed=%d )", __FUNCTION__, Instance, Speed );

        if ( Instance == NULL )
        {
            Status = GPIO_STM32L496VGT6P_Status_ArgumentInvalid;
            break;
        }

        GPIO_STM32L496VGT6P_Instance_Context_t * Context = &GPIO_STM32L496VGT6P_Context.Context[ Instance->GPIOx ];

        switch ( Speed )
        {
            case GPIO_STM32L496VGT6P_Speed_Low:
                Context->InitType.Speed = GPIO_SPEED_FREQ_LOW;
                break;

            case GPIO_STM32L496VGT6P_Speed_Medium:
                Context->InitType.Speed = GPIO_SPEED_FREQ_MEDIUM;
                break;

            case GPIO_STM32L496VGT6P_Speed_High:
                Context->InitType.Speed = GPIO_SPEED_FREQ_HIGH;
                break;

            case GPIO_STM32L496VGT6P_Speed_VeryHigh:
                Context->InitType.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
                break;

            default:
                Status = GPIO_STM32L496VGT6P_Status_NotSupported;
                break;
        }
    }
    while ( 0 );

    return Status;
}

static GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_Instance_SetFunction( GPIO_STM32L496VGT6P_Instance_t * Instance, GPIO_STM32L496VGT6P_Function_t Function )
{
    GPIO_STM32L496VGT6P_Status_t Status = GPIO_STM32L496VGT6P_Status_Success;

    do
    {
        GPIO_Trace( "%s( Instance=%p, Function=%d )", __FUNCTION__, Instance, Function );

        if ( Instance == NULL )
        {
            Status = GPIO_STM32L496VGT6P_Status_ArgumentInvalid;
            break;
        }

        GPIO_STM32L496VGT6P_Instance_Context_t * Context = &GPIO_STM32L496VGT6P_Context.Context[ Instance->GPIOx ];

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

        Context->InitType.Alternate = Function;
    }
    while ( 0 );

    return Status;
}

static GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_Instance_Commit( GPIO_STM32L496VGT6P_Instance_t * Instance )
{
    GPIO_STM32L496VGT6P_Status_t Status = GPIO_STM32L496VGT6P_Status_Success;

    do
    {
        GPIO_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        GPIO_STM32L496VGT6P_Instance_Context_t * Context = &GPIO_STM32L496VGT6P_Context.Context[ Instance->GPIOx ];

        if ( Context->GPIOx != NULL )
        {
            HAL_GPIO_Init( Context->GPIOx, &Context->InitType );
        }
    }
    while ( 0 );

    return Status;
}

// #############################################################################
// #### Public Method(s) #######################################################
// #############################################################################

GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_Initialize( GPIO_STM32L496VGT6P_Instance_t * Instance )
{
    GPIO_STM32L496VGT6P_Status_t Status = GPIO_STM32L496VGT6P_Status_Success;

    do
    {
        GPIO_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        if ( ( Status = GPIO_STM32L496VGT6P_Context_Initialize( ) ) != GPIO_STM32L496VGT6P_Status_Success )
        {
            break;
        }

        Status = GPIO_STM32L496VGT6P_Instance_Initialize( Instance );
    }
    while ( 0 );

    return Status;
}

GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_Cycle( GPIO_STM32L496VGT6P_Instance_t * Instance )
{
    GPIO_STM32L496VGT6P_Status_t Status = GPIO_STM32L496VGT6P_Status_Success;

    do
    {
        GPIO_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        if ( ( Status = GPIO_STM32L496VGT6P_Context_Cycle( ) ) != GPIO_STM32L496VGT6P_Status_Success )
        {
            break;
        }

        Status = GPIO_STM32L496VGT6P_Instance_Cycle( Instance );
    }
    while ( 0 );

    return Status;
}

GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_DeInitialize( GPIO_STM32L496VGT6P_Instance_t * Instance )
{
    GPIO_STM32L496VGT6P_Status_t Status = GPIO_STM32L496VGT6P_Status_Success;

    do
    {
        GPIO_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        if ( ( Status = GPIO_STM32L496VGT6P_Instance_DeInitialize( Instance ) ) != GPIO_STM32L496VGT6P_Status_Success )
        {
            break;
        }

        Status = GPIO_STM32L496VGT6P_Context_DeInitialize( );
    }
    while ( 0 );

    return Status;
}

GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_SetMode( GPIO_STM32L496VGT6P_Instance_t * Instance, GPIO_STM32L496VGT6P_Mode_t Mode )
{
    GPIO_STM32L496VGT6P_Status_t Status = GPIO_STM32L496VGT6P_Status_Success;

    do
    {
        GPIO_Trace( "%s( Instance=%p, Mode=%d )", __FUNCTION__, Instance, Mode );

        Status = GPIO_STM32L496VGT6P_Instance_SetMode( Instance, Mode );
    }
    while ( 0 );

    return Status;
}

GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_SetPull( GPIO_STM32L496VGT6P_Instance_t * Instance, GPIO_STM32L496VGT6P_Pull_t Pull )
{
    GPIO_STM32L496VGT6P_Status_t Status = GPIO_STM32L496VGT6P_Status_Success;

    do
    {
        GPIO_Trace( "%s( Instance=%p, Pull=%d )", __FUNCTION__, Instance, Pull );

        Status = GPIO_STM32L496VGT6P_Instance_SetPull( Instance, Pull );
    }
    while ( 0 );

    return Status;
}

GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_SetSpeed( GPIO_STM32L496VGT6P_Instance_t * Instance, GPIO_STM32L496VGT6P_Speed_t Speed )
{
    GPIO_STM32L496VGT6P_Status_t Status = GPIO_STM32L496VGT6P_Status_Success;

    do
    {
        GPIO_Trace( "%s( Instance=%p, Speed=%d )", __FUNCTION__, Instance, Speed );

        Status = GPIO_STM32L496VGT6P_Instance_SetSpeed( Instance, Speed );
    }
    while ( 0 );

    return Status;
}

GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_SetFunction( GPIO_STM32L496VGT6P_Instance_t * Instance, GPIO_STM32L496VGT6P_Function_t Function )
{
    GPIO_STM32L496VGT6P_Status_t Status = GPIO_STM32L496VGT6P_Status_Success;

    do
    {
        GPIO_Trace( "%s( Instance=%p, Function=%d )", __FUNCTION__, Instance, Function );

        Status = GPIO_STM32L496VGT6P_Instance_SetFunction( Instance, Function );
    }
    while ( 0 );

    return Status;
}

GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_Commit( GPIO_STM32L496VGT6P_Instance_t * Instance )
{
    GPIO_STM32L496VGT6P_Status_t Status = GPIO_STM32L496VGT6P_Status_Success;

    do
    {
        GPIO_Trace( "%s( Instance=%p )", __FUNCTION__, Instance );

        Status = GPIO_STM32L496VGT6P_Instance_Commit( Instance );
    }
    while ( 0 );

    return Status;
}

GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_Write( GPIO_STM32L496VGT6P_Instance_t * Instance, GPIO_STM32L496VGT6P_Value_t Value )
{
    GPIO_STM32L496VGT6P_Status_t Status = GPIO_STM32L496VGT6P_Status_Success;

    do
    {
        GPIO_Trace( "%s( Instance=%p, Value=%d )", __FUNCTION__, Instance, Value );

        Status = GPIO_STM32L496VGT6P_Instance_Write( Instance, Value );
    }
    while ( 0 );

    return Status;
}

GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_Read( GPIO_STM32L496VGT6P_Instance_t * Instance, GPIO_STM32L496VGT6P_Value_t * Value )
{
    GPIO_STM32L496VGT6P_Status_t Status = GPIO_STM32L496VGT6P_Status_Success;

    do
    {
        GPIO_Trace( "%s( Instance=%p, Value=%p )", __FUNCTION__, Instance, Value );

        Status = GPIO_STM32L496VGT6P_Instance_Read( Instance, Value );
    }
    while ( 0 );

    return Status;
}

// #############################################################################
// #### Public Variable(s) #####################################################
// #############################################################################

const char GPIO_STM32L496VGT6P_VERSION[] = "0.0.0.v20260203-0213";

// #############################################################################
// #### File Guard #############################################################
// #############################################################################

#endif /* STM32L496xx */

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################
