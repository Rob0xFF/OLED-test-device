/*!
 * @file E52246.h
 *
 * This is a library for the E52.246 LED/OLED driver from Elmos Semiconductor SE
 *
 * The ELMOS E52.246 use I2C to communicate, additionally this library adds the
 * possibility to toggle the output via the RUN pin.
 *
 * GPL licence
 */
#ifndef E52246_h
#define E52246_h

#include <stdint.h>
#include <util/delay.h>
#include <avr/io.h>
#include "Arduino.h"
#include "Wire.h"

#define LED_CURR_RANGE 0x2E 			//Configures Range of Master Current of all LED channels
#define SETUP_LED_ADC_ENABLE 0x2F 		//Configures SETUP_LED_ENABLE and ADC_CONFIG Register at once
#define LED_DAC_VAL 0x89 				//Configures Master Current of all LED channels simultaneously
#define SETUP_LED_ENABLE 0x8A 			//Activates each LED channel independently

#define DERATE_CONFIG 0x2C 				//Configures behaviour of thermal derating and analog dimming

#define LED_TRIM_ALL 0x80 				//Configures Duty Cycle of all LED channels simultaneously
#define LED1_TRIM 0x81 					//Configures Duty Cycle of LED1
#define LED2_TRIM 0x82 					//Configures Duty Cycle of LED2
#define LED3_TRIM 0x83 					//Configures Duty Cycle of LED3
#define LED4_TRIM 0x84 					//Configures Duty Cycle of LED4
#define LED5_TRIM 0x85 					//Configures Duty Cycle of LED5
#define LED6_TRIM 0x86 					//Configures Duty Cycle of LED6
#define LED7_TRIM 0x87 					//Configures Duty Cycle of LED7
#define LED8_TRIM 0x88 					//Configures Duty Cycle of LED8

#define PWM_FREQ 0x8B 					//Configures Internal PWM-Frequency
#define PWDIM_CONFIG 0x2B 				//Configures synchronization and dimming behaviour of PWDIM pin

#define LED_DUTY_ALL 0x20 				//Customizes Duty Cycle of all LED channels simultaneously (supplementary to TRIM-Value)
#define LED1_DUTY 0x21 					//Customizes Duty Cycle of LED1 (supplementary to TRIM-Value)
#define LED2_DUTY 0x22 					//Customizes Duty Cycle of LED2 (supplementary to TRIM-Value)
#define LED3_DUTY 0x23 					//Customizes Duty Cycle of LED3 (supplementary to TRIM-Value)
#define LED4_DUTY 0x24 					//Customizes Duty Cycle of LED4 (supplementary to TRIM-Value)
#define LED5_DUTY 0x25 					//Customizes Duty Cycle of LED5 (supplementary to TRIM-Value)
#define LED6_DUTY 0x26 					//Customizes Duty Cycle of LED6 (supplementary to TRIM-Value)
#define LED7_DUTY 0x27 					//Customizes Duty Cycle of LED7 (supplementary to TRIM-Value)
#define LED8_DUTY 0x28 					//Customizes Duty Cycle of LED8 (supplementary to TRIM-Value)

#define DERATE_CONFIG 0x2C 				//Configures behaviour of thermal derating and analog dimming
#define ADIM_EDGE 0x2D 					//Voltage at ADIM pin to change LED Current slope
#define ADIM_ADC 0x4C 					//ADC value of voltage at ADIM pin

#define REG_RUN_VIA_I2C 0x8E 			//Determines internal system state in case of RUN_VIA_I2C mode

#define LED1_VOLTAGE 0x41 				//ADC value of voltage VF at LED1
#define LED2_VOLTAGE 0x42 				//ADC value of voltage VF at LED2
#define LED3_VOLTAGE 0x43 				//ADC value of voltage VF at LED3
#define LED4_VOLTAGE 0x44 				//ADC value of voltage VF at LED4
#define LED5_VOLTAGE 0x45 				//ADC value of voltage VF at LED5
#define LED6_VOLTAGE 0x46 				//ADC value of voltage VF at LED6
#define LED7_VOLTAGE 0x47 				//ADC value of voltage VF at LED7
#define LED8_VOLTAGE 0x48 				//ADC value of voltage VF at LED8
#define LED_STATUS 0x49 				//Contains status flags (open/short) of each LED channel
#define VSUP 0x4A 						//ADC value of voltage at VS pin
#define TEMP 0x4B 						//ADC value of temperature depending diode voltage

#define ADC_CONFIG 0x29 				//Settings ADC Measurement
#define VS_CHECK_LEVEL 0x2A 			//Configures Comparison Value for additional plausibility check

#define SHORT_LIM_ALL 0xA0 				//Configures Threshold Voltage for Short Detection of all LED channels simultaneously
#define SHORT_LIM1 0xA1 				//Configures Threshold Voltage for Short Detection of LED1
#define SHORT_LIM2 0xA2 				//Configures Threshold Voltage for Short Detection of LED2
#define SHORT_LIM3 0xA3 				//Configures Threshold Voltage for Short Detection of LED3
#define SHORT_LIM4 0xA4 				//Configures Threshold Voltage for Short Detection of LED4
#define SHORT_LIM5 0xA5 				//Configures Threshold Voltage for Short Detection of LED5
#define SHORT_LIM6 0xA6 				//Configures Threshold Voltage for Short Detection of LED6
#define SHORT_LIM7 0xA7 				//Configures Threshold Voltage for Short Detection of LED7
#define SHORT_LIM8 0xA8 				//Configures Threshold Voltage for Short Detection of LED8

#define ERROR_STATUS 0x40 				//Contains system information, incl. warnings and error flags
#define SETUP_ERROR_HANDL 0x8C 			//State Machine Settings for Error Handling
#define SETUP_IRQMASK 0x8D 				//Masking Interrupt Events

#define EE_PROG 0x14 					//Initializes E2PROM-Programming sequence
#define EE_STATUS 0x4D 					//Contains system informations of E2PROM Programming
#define I2C_Slave 0x8F 					//Prefix[5:0] of I2C Slave Address


/*!
 * @brief E52246 main class
 */
class E52246
{
  public:
    /*!
    * @brief E52246 class constructor
    * @param I2C address of the E52.246
    * @param pin connected to RUN, use -1 if not connected
    */
    E52246(uint8_t addr, uint8_t runPin);

    /*!
      * @brief configures RUN pin output, call first
      */
    void begin(void);

    /*!
      * @brief Enables E52.246 run state (RUN pin must be connected)
      */
    void run(void);

    /*!
      * @brief Disables E52.246 run state (RUN pin must be connected)
      */
    void stop(void);

    /*!
      * @brief Enables each LED channel independently, or enables all channels simultanously
      * @param [1:8] to enable channel 1-8 independently, 0 to enable all channels simultanously
      */
    void enableChannel(uint8_t channel);

    /*!
      * @brief Disables each LED channel independently, or disables all channels simultanously
      * @param [1:8] to disable channel 1-8 independently, 0 to disable all channels simultanously
      */
    void disableChannel(uint8_t channel);

    /*!
      * @brief Sets constant LED/OLED current on all channels simultanously
      * @param 1.0 - 26.5 to set constant current in mA
      */
    void setMilliamps(float milliamps);

    /*!
      * @brief Sets pulse width dimming on each LED channel, or sets pulse width dimming on all channels simultanously
      * @param [1:8] to select channel 1-8, 0 to select all channels simultanously
    * @param [0:255] duty cycle
      */
    void setPWM(uint8_t channel, uint8_t duty);

    /*!
      * @brief Reads external voltage supplied at Vs pin
    * @return External voltage supplied at Vs pin in Volts
      */
    float getSupplyVoltage(void);

    /*!
      * @brief Reads temperature of internal chip sensor
    * @return Temperature at internal chip sensor in °C
      */
    float getTemp(void);

    /*!
      * @brief Reads voltage supplied to individual channel
    * @param [1:8] to select channel 1-8
    * @return LED Voltage in Volts
      */
    float getVoltage(uint8_t channel);

    /*!
      * @brief Reads LED error status (okay/short/open) for individual channel
    * @param [1:8] to select channel 1-8
    * @return 0 - okay, 1 - short, 2 - open, 3 - throttling active due to chip overtemperature
      */
    uint8_t getErrStatus(uint8_t channel);

  private:
    uint8_t _addr;
    uint8_t _runPin = -1;
    void writeRegister8(uint8_t reg, uint8_t data);
    void writeEEPROM();
    uint8_t readRegister8(uint8_t reg);
    uint16_t readRegister16(uint8_t reg);
};
#endif