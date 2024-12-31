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

/**
 *  @file
 *
 *  @brief Platform GPIO STM32L496VGT6P Driver
 */

// #############################################################################
// #### Control Include(s) #####################################################
// #############################################################################

// #############################################################################
// #### Control Macro(s) #######################################################
// #############################################################################

// #############################################################################
// #### File Guard #############################################################
// #############################################################################

/**
 *  @addtogroup Platform_GPIO_Driver
 *
 *  @{
 */

/**
 *  @defgroup Platform_GPIO_STM32L496VGT6P STM32L496VGT6P
 *
 *  @image html STM32L496Vx_external-SMPS-device_LQFP100.png
 *
 *  @{
 */

#ifndef GPIO_STM32L496VGT6P_H_
    #define GPIO_STM32L496VGT6P_H_

    #ifdef __cplusplus
extern "C"
{
    #endif /* __cplusplus */

    // #############################################################################
    // #### Include(s) #############################################################
    // #############################################################################

    // #############################################################################
    // #### Public Macro(s) ########################################################
    // #############################################################################

    // #############################################################################
    // #### Public Type(s) #########################################################
    // #############################################################################

    /**
     *  @brief GPIO STM32L496VGT6P Operation Status
     *
     *  @enum GPIO_STM32L496VGT6P_Status_t
     */
    typedef enum GPIO_STM32L496VGT6P_Status
    {
        GPIO_STM32L496VGT6P_Status_Success = 0,     ///< Success
        GPIO_STM32L496VGT6P_Status_ArgumentInvalid, ///< Argument Invalid
        GPIO_STM32L496VGT6P_Status_NotSupported,    ///< Not Supported
        GPIO_STM32L496VGT6P_Status_Error,           ///< General Error
        GPIO_STM32L496VGT6P_Status_Busy,            ///< Busy
        GPIO_STM32L496VGT6P_Status_Timeout,         ///< Timeout
    } GPIO_STM32L496VGT6P_Status_t;

    /**
     *  @brief GPIO STM32L496VGT6P
     *
     *  @enum GPIO_STM32L496VGT6P_t
     */
    typedef enum GPIO_STM32L496VGT6P
    {
        GPIO_STM32L496VGT6P_1 = 0, ///< GPIO 1 [PE2] (Minimum)
        GPIO_STM32L496VGT6P_2,     ///< GPIO 2 [PE3]
        GPIO_STM32L496VGT6P_3,     ///< GPIO 3 [PE4]
        GPIO_STM32L496VGT6P_4,     ///< GPIO 4 [PE5]
        GPIO_STM32L496VGT6P_5,     ///< GPIO 5 [PE6]
        GPIO_STM32L496VGT6P_6,     ///< GPIO 6 [VBAT]
        GPIO_STM32L496VGT6P_7,     ///< GPIO 7 [PC13]
        GPIO_STM32L496VGT6P_8,     ///< GPIO 8 [PC14-OSC32_IN]
        GPIO_STM32L496VGT6P_9,     ///< GPIO 9 [PC15-OSC32_OUT]
        GPIO_STM32L496VGT6P_10,    ///< GPIO 10 [VSS]
        GPIO_STM32L496VGT6P_11,    ///< GPIO 11 [VDD]
        GPIO_STM32L496VGT6P_12,    ///< GPIO 12 [PH0-OSC_IN]
        GPIO_STM32L496VGT6P_13,    ///< GPIO 13 [PH1-OSC_OUT]
        GPIO_STM32L496VGT6P_14,    ///< GPIO 14 [NRST]
        GPIO_STM32L496VGT6P_15,    ///< GPIO 15 [PC0]
        GPIO_STM32L496VGT6P_16,    ///< GPIO 16 [PC1]
        GPIO_STM32L496VGT6P_17,    ///< GPIO 17 [PC2]
        GPIO_STM32L496VGT6P_18,    ///< GPIO 18 [PC3]
        GPIO_STM32L496VGT6P_19,    ///< GPIO 19 [VSSA]
        GPIO_STM32L496VGT6P_20,    ///< GPIO 20 [VREF-]
        GPIO_STM32L496VGT6P_21,    ///< GPIO 21 [VREF+]
        GPIO_STM32L496VGT6P_22,    ///< GPIO 22 [VDDA]
        GPIO_STM32L496VGT6P_23,    ///< GPIO 23 [PA0]
        GPIO_STM32L496VGT6P_24,    ///< GPIO 24 [PA1]
        GPIO_STM32L496VGT6P_25,    ///< GPIO 25 [PA2]
        GPIO_STM32L496VGT6P_26,    ///< GPIO 26 [PA3]
        GPIO_STM32L496VGT6P_27,    ///< GPIO 27 [VSS]
        GPIO_STM32L496VGT6P_28,    ///< GPIO 28 [VDD]
        GPIO_STM32L496VGT6P_29,    ///< GPIO 29 [PA4]
        GPIO_STM32L496VGT6P_30,    ///< GPIO 30 [PA5]
        GPIO_STM32L496VGT6P_31,    ///< GPIO 31 [PA6]
        GPIO_STM32L496VGT6P_32,    ///< GPIO 32 [PA7]
        GPIO_STM32L496VGT6P_33,    ///< GPIO 33 [PC4]
        GPIO_STM32L496VGT6P_34,    ///< GPIO 34 [PC5]
        GPIO_STM32L496VGT6P_35,    ///< GPIO 35 [PB0]
        GPIO_STM32L496VGT6P_36,    ///< GPIO 36 [PB1]
        GPIO_STM32L496VGT6P_37,    ///< GPIO 37 [PB2]
        GPIO_STM32L496VGT6P_38,    ///< GPIO 38 [PE7]
        GPIO_STM32L496VGT6P_39,    ///< GPIO 39 [PE8]
        GPIO_STM32L496VGT6P_40,    ///< GPIO 40 [PE9]
        GPIO_STM32L496VGT6P_41,    ///< GPIO 41 [PE10]
        GPIO_STM32L496VGT6P_42,    ///< GPIO 42 [PE11]
        GPIO_STM32L496VGT6P_43,    ///< GPIO 43 [PE12]
        GPIO_STM32L496VGT6P_44,    ///< GPIO 44 [PE13]
        GPIO_STM32L496VGT6P_45,    ///< GPIO 45 [PE14]
        GPIO_STM32L496VGT6P_46,    ///< GPIO 46 [PE15]
        GPIO_STM32L496VGT6P_47,    ///< GPIO 47 [PB10]
        GPIO_STM32L496VGT6P_48,    ///< GPIO 48 [VDD12]
        GPIO_STM32L496VGT6P_49,    ///< GPIO 49 [VSS]
        GPIO_STM32L496VGT6P_50,    ///< GPIO 50 [VDD]
        GPIO_STM32L496VGT6P_51,    ///< GPIO 51 [PB12]
        GPIO_STM32L496VGT6P_52,    ///< GPIO 52 [PB13]
        GPIO_STM32L496VGT6P_53,    ///< GPIO 53 [PB14]
        GPIO_STM32L496VGT6P_54,    ///< GPIO 54 [PB15]
        GPIO_STM32L496VGT6P_55,    ///< GPIO 55 [PD8]
        GPIO_STM32L496VGT6P_56,    ///< GPIO 56 [PD9]
        GPIO_STM32L496VGT6P_57,    ///< GPIO 57 [PD10]
        GPIO_STM32L496VGT6P_58,    ///< GPIO 58 [PD11]
        GPIO_STM32L496VGT6P_59,    ///< GPIO 59 [PD12]
        GPIO_STM32L496VGT6P_60,    ///< GPIO 60 [PD13]
        GPIO_STM32L496VGT6P_61,    ///< GPIO 61 [PD14]
        GPIO_STM32L496VGT6P_62,    ///< GPIO 62 [PD15]
        GPIO_STM32L496VGT6P_63,    ///< GPIO 63 [PC6]
        GPIO_STM32L496VGT6P_64,    ///< GPIO 64 [PC7]
        GPIO_STM32L496VGT6P_65,    ///< GPIO 65 [PC8]
        GPIO_STM32L496VGT6P_66,    ///< GPIO 66 [PC9]
        GPIO_STM32L496VGT6P_67,    ///< GPIO 67 [PA8]
        GPIO_STM32L496VGT6P_68,    ///< GPIO 68 [PA9]
        GPIO_STM32L496VGT6P_69,    ///< GPIO 69 [PA10]
        GPIO_STM32L496VGT6P_70,    ///< GPIO 70 [PA11-USB_D-]
        GPIO_STM32L496VGT6P_71,    ///< GPIO 71 [PA12-USB_D+]
        GPIO_STM32L496VGT6P_72,    ///< GPIO 72 [PA13-SWDIO]
        GPIO_STM32L496VGT6P_73,    ///< GPIO 73 [VDDUSB]
        GPIO_STM32L496VGT6P_74,    ///< GPIO 74 [VSS]
        GPIO_STM32L496VGT6P_75,    ///< GPIO 75 [VDD]
        GPIO_STM32L496VGT6P_76,    ///< GPIO 76 [PA14-SWCLK]
        GPIO_STM32L496VGT6P_77,    ///< GPIO 77 [PA15]
        GPIO_STM32L496VGT6P_78,    ///< GPIO 78 [PC10]
        GPIO_STM32L496VGT6P_79,    ///< GPIO 79 [PC11]
        GPIO_STM32L496VGT6P_80,    ///< GPIO 80 [PC12]
        GPIO_STM32L496VGT6P_81,    ///< GPIO 81 [PD0]
        GPIO_STM32L496VGT6P_82,    ///< GPIO 82 [PD1]
        GPIO_STM32L496VGT6P_83,    ///< GPIO 83 [PD2]
        GPIO_STM32L496VGT6P_84,    ///< GPIO 84 [PD3]
        GPIO_STM32L496VGT6P_85,    ///< GPIO 85 [PD4]
        GPIO_STM32L496VGT6P_86,    ///< GPIO 86 [PD5]
        GPIO_STM32L496VGT6P_87,    ///< GPIO 87 [PD6]
        GPIO_STM32L496VGT6P_88,    ///< GPIO 88 [PD7]
        GPIO_STM32L496VGT6P_89,    ///< GPIO 89 [PB3]
        GPIO_STM32L496VGT6P_90,    ///< GPIO 90 [PB4]
        GPIO_STM32L496VGT6P_91,    ///< GPIO 91 [PB5]
        GPIO_STM32L496VGT6P_92,    ///< GPIO 92 [PB6]
        GPIO_STM32L496VGT6P_93,    ///< GPIO 93 [PB7]
        GPIO_STM32L496VGT6P_94,    ///< GPIO 94 [PH3-BOOT0]
        GPIO_STM32L496VGT6P_95,    ///< GPIO 95 [PB8]
        GPIO_STM32L496VGT6P_96,    ///< GPIO 96 [PB9]
        GPIO_STM32L496VGT6P_97,    ///< GPIO 97 [PE0]
        GPIO_STM32L496VGT6P_98,    ///< GPIO 98 [VDD12]
        GPIO_STM32L496VGT6P_99,    ///< GPIO 99 [VSS]
        GPIO_STM32L496VGT6P_100,   ///< GPIO 100 [VDD] (Maximum)
        GPIO_STM32L496VGT6P_Count  ///< Count
    } GPIO_STM32L496VGT6P_t;

    /**
     *  @brief GPIO STM32L496VGT6P Mode
     *
     *  @enum GPIO_STM32L496VGT6P_Mode_t
     */
    typedef enum GPIO_STM32L496VGT6P_Mode
    {
        GPIO_STM32L496VGT6P_Mode_Input = 0,          ///< Input (High Impedance)
        GPIO_STM32L496VGT6P_Mode_Output,             ///< Output (Push-Pull)
        GPIO_STM32L496VGT6P_Mode_OutputOpenDrain,    ///< Output (Open-Drain)
        GPIO_STM32L496VGT6P_Mode_Interrupt,          ///< Interrupt (On Change)
        GPIO_STM32L496VGT6P_Mode_InterruptRising,    ///< Interrupt (On Rising)
        GPIO_STM32L496VGT6P_Mode_InterruptFalling,   ///< Interrupt (On Falling)
        GPIO_STM32L496VGT6P_Mode_Event,              ///< Event (On Change)
        GPIO_STM32L496VGT6P_Mode_EventRising,        ///< Event (On Rising)
        GPIO_STM32L496VGT6P_Mode_EventFalling,       ///< Event (On Falling)
        GPIO_STM32L496VGT6P_Mode_Alternate,          ///< Alternate Function (Push-Pull)
        GPIO_STM32L496VGT6P_Mode_AlternateOpenDrain, ///< Alternate Function (Open-Drain)
        GPIO_STM32L496VGT6P_Mode_Analog,             ///< Analog
        GPIO_STM32L496VGT6P_Mode_AnalogADC,          ///< Analog (ADC Controlled)
    } GPIO_STM32L496VGT6P_Mode_t;

    /**
     *  @brief GPIO STM32L496VGT6P Pull
     *
     *  @enum GPIO_STM32L496VGT6P_Pull_t
     */
    typedef enum GPIO_STM32L496VGT6P_Pull
    {
        GPIO_STM32L496VGT6P_Pull_None = 0, ///< No Pull
        GPIO_STM32L496VGT6P_Pull_Up,       ///< Pull-Up
        GPIO_STM32L496VGT6P_Pull_Down,     ///< Pull-Down
    } GPIO_STM32L496VGT6P_Pull_t;

    /**
     *  @brief GPIO STM32L496VGT6P Speed
     *
     *  @enum GPIO_STM32L496VGT6P_Speed_t
     */
    typedef enum GPIO_STM32L496VGT6P_Speed
    {
        GPIO_STM32L496VGT6P_Speed_Low = 0,  ///< Low
        GPIO_STM32L496VGT6P_Speed_Medium,   ///< Medium
        GPIO_STM32L496VGT6P_Speed_High,     ///< High
        GPIO_STM32L496VGT6P_Speed_VeryHigh, ///< Very High
    } GPIO_STM32L496VGT6P_Speed_t;

    /**
     *  @brief GPIO STM32L496VGT6P Function
     *
     *  @enum GPIO_STM32L496VGT6P_Function_t
     */
    typedef enum GPIO_STM32L496VGT6P_Function
    {
        GPIO_STM32L496VGT6P_Function_0 = 0, ///< Function 0 (Minimum)
        GPIO_STM32L496VGT6P_Function_1,     ///<
        GPIO_STM32L496VGT6P_Function_2,     ///<
        GPIO_STM32L496VGT6P_Function_3,     ///<
        GPIO_STM32L496VGT6P_Function_4,     ///<
        GPIO_STM32L496VGT6P_Function_5,     ///<
        GPIO_STM32L496VGT6P_Function_6,     ///<
        GPIO_STM32L496VGT6P_Function_7,     ///<
        GPIO_STM32L496VGT6P_Function_8,     ///<
        GPIO_STM32L496VGT6P_Function_9,     ///<
        GPIO_STM32L496VGT6P_Function_10,    ///<
        GPIO_STM32L496VGT6P_Function_11,    ///<
        GPIO_STM32L496VGT6P_Function_12,    ///<
        GPIO_STM32L496VGT6P_Function_13,    ///<
        GPIO_STM32L496VGT6P_Function_14,    ///<
        GPIO_STM32L496VGT6P_Function_15,    ///< Function 15 (Maximum)
    } GPIO_STM32L496VGT6P_Function_t;

    /**
     *  @brief GPIO STM32L496VGT6P Value
     */
    typedef enum GPIO_STM32L496VGT6P_Value
    {
        GPIO_STM32L496VGT6P_Value_Low = 0,
        GPIO_STM32L496VGT6P_Value_High,
    } GPIO_STM32L496VGT6P_Value_t;

    /**
     *  @brief GPIO STM32L496VGT6P Instance (Forward Declaration)
     */
    typedef struct GPIO_STM32L496VGT6P_Instance GPIO_STM32L496VGT6P_Instance_t;

    /**
     *  @brief GPIO STM32L496VGT6P Callback On Interrupt
     */
    typedef GPIO_STM32L496VGT6P_Status_t ( *GPIO_STM32L496VGT6P_CallbackOnInterrupt_t )( GPIO_STM32L496VGT6P_Instance_t * Instance );

    /**
     *  @brief GPIO STM32L496VGT6P Instance Context
     *
     *  @struct GPIO_STM32L496VGT6P_Instance_Context_t
     */
    typedef struct GPIO_STM32L496VGT6P_Instance_Context GPIO_STM32L496VGT6P_Instance_Context_t;

    /**
     *  @brief GPIO STM32L496VGT6P Instance
     *
     *  @struct GPIO_STM32L496VGT6P_Instance_t
     */
    typedef struct GPIO_STM32L496VGT6P_Instance
    {
        GPIO_STM32L496VGT6P_t GPIOx;

        GPIO_STM32L496VGT6P_CallbackOnInterrupt_t OnInterrupt;

        // Managed Internally
        GPIO_STM32L496VGT6P_Instance_Context_t * Context;
    } GPIO_STM32L496VGT6P_Instance_t;

    // #############################################################################
    // #### Public Method(s) #######################################################
    // #############################################################################

    /**
     *  @brief Initializes specified GPIO STM32L496VGT6P Instance
     *
     *  @param[in] Instance Instance
     *
     *  @return GPIO_STM32L496VGT6P_Status_t
     */
    GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_Initialize( GPIO_STM32L496VGT6P_Instance_t * Instance );

    /**
     *  @brief Cycles specified GPIO STM32L496VGT6P Instance
     *
     *  @param[in] Instance Instance
     *
     *  @return GPIO_STM32L496VGT6P_Status_t
     */
    GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_Cycle( GPIO_STM32L496VGT6P_Instance_t * Instance );

    /**
     *  @brief De-initializes specified GPIO STM32L496VGT6P Instance
     *
     *  @param[in] Instance Instance
     *
     *  @return GPIO_STM32L496VGT6P_Status_t
     */
    GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_DeInitialize( GPIO_STM32L496VGT6P_Instance_t * Instance );

    /**
     *  @brief Sets mode of specified GPIO STM32L496VGT6P Instance
     *
     *  @param[in] Instance Instance
     *  @param[in] Mode     Mode
     *
     *  @return GPIO_STM32L496VGT6P_Status_t
     */
    GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_SetMode( GPIO_STM32L496VGT6P_Instance_t * Instance, GPIO_STM32L496VGT6P_Mode_t Mode );

    /**
     *  @brief Sets pull of specified GPIO STM32L496VGT6P Instance
     *
     *  @param[in] Instance Instance
     *  @param[in] Pull     Pull
     *
     *  @return GPIO_STM32L496VGT6P_Status_t
     */
    GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_SetPull( GPIO_STM32L496VGT6P_Instance_t * Instance, GPIO_STM32L496VGT6P_Pull_t Pull );

    /**
     *  @brief Sets speed of specified GPIO STM32L496VGT6P Instance
     *
     *  @param[in] Instance Instance
     *  @param[in] Speed    Speed
     *
     *  @return GPIO_STM32L496VGT6P_Status_t
     */
    GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_SetSpeed( GPIO_STM32L496VGT6P_Instance_t * Instance, GPIO_STM32L496VGT6P_Speed_t Speed );

    /**
     *  @brief Sets function of specified GPIO STM32L496VGT6P Instance
     *
     *  @param[in] Instance Instance
     *  @param[in] Function Function
     *
     *  @return GPIO_STM32L496VGT6P_Status_t
     */
    GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_SetFunction( GPIO_STM32L496VGT6P_Instance_t * Instance, GPIO_STM32L496VGT6P_Function_t Function );

    /**
     *  @brief Commit settings of specified GPIO STM32L496VGT6P Instance
     *
     *  @param[in] Instance Instance
     *
     *  @return GPIO_STM32L496VGT6P_Status_t
     */
    GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_Commit( GPIO_STM32L496VGT6P_Instance_t * Instance );

    /**
     *  @brief Write value to specified GPIO STM32L496VGT6P Instance
     *
     *  @param[in] Instance Instance
     *  @param[in] Value    Value
     *
     *  @return GPIO_STM32L496VGT6P_Status_t
     */
    GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_Write( GPIO_STM32L496VGT6P_Instance_t * Instance, GPIO_STM32L496VGT6P_Value_t Value );

    /**
     *  @brief Read value of specified GPIO STM32L496VGT6P Instance
     *
     *  @param[in]  Instance Instance
     *  @param[out] Value    Value pointer
     *
     *  @return GPIO_STM32L496VGT6P_Status_t
     */
    GPIO_STM32L496VGT6P_Status_t GPIO_STM32L496VGT6P_Read( GPIO_STM32L496VGT6P_Instance_t * Instance, GPIO_STM32L496VGT6P_Value_t * Value );

    // TODO Add More APIs

    // #############################################################################
    // #### Public Variable(s) #####################################################
    // #############################################################################

    /**
     *  @brief Version
     */
    extern const char GPIO_STM32L496VGT6P_VERSION[];

    // #############################################################################
    // #### File Guard #############################################################
    // #############################################################################

    #ifdef __cplusplus
} /* extern "C" */
    #endif /* __cplusplus */

#endif /* GPIO_STM32L496VGT6P_H_ */

/**
 *  @}
 *
 *  @}
 */

// #############################################################################
// #### END OF FILE ############################################################
// #############################################################################
