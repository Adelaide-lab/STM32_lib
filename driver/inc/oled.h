#ifndef  __OLED_H__
#define  __OLED_H__

#define  OLED_Address				0x78

#define   OLED_COMMAND				0x00
#define   OLED_DATA					0x40
#define	  LOWER_START_PAGE_COL		0x00
#define	  HIGER_START_PAGE_COL		0x10
#define	  SET_MEMORY_PAGE_MODE		0x02
#define	  SET_SEGMENT_REMAP			0x00
#define	  SET_PAGE_START			0x00
#define	  SET_DISPLAY_ON			0xAE
#define	  SET_DISPLAY_OFF			0xAF
#define   OLED_NOT					0xE3
#define	  SET_DISPLAY_SATRT_LINE	0x40


typedef enum{
	Data_Mode,
	Cmd_Mode,
}I2C_Data_Mode;

/**
 * @brief 
 * 
 * @param data 
 * @param mode 
 * @return uint8_t 
 * @version 0.1
 * @author Adelaide ({1479398604xz@gmail.com})
 * @date 2023-03-12
 * @copyright Copyright (c) 2023
 */
uint8_t OLED_Write(uint8_t data, uint8_t mode);

/**
 * @brief 
 * 
 * @param data 
 * @version 0.1
 * @author Adelaide ({1479398604xz@gmail.com})
 * @date 2023-03-12
 * @copyright Copyright (c) 2023
 */
void OLED_Read(uint8_t data);

/**
 * @brief 
 * 
 * @version 0.1
 * @author Adelaide ({1479398604xz@gmail.com})
 * @date 2023-03-12
 * @copyright Copyright (c) 2023
 */
void OLED_Clear_Screen(void);

/**
 * @brief 
 * 
 * @param x 
 * @param y 
 * @param t 
 * @version 0.1
 * @author Adelaide ({1479398604xz@gmail.com})
 * @date 2023-03-12
 * @copyright Copyright (c) 2023
 */
void OLED_DrawPoint(uint8_t x,uint8_t y,uint8_t t);

/**
 * @brief 
 * 
 * @param x 
 * @param y 
 * @param chr 
 * @param size1 
 * @param mode 
 * @version 0.1
 * @author Adelaide ({1479398604xz@gmail.com})
 * @date 2023-03-12
 * @copyright Copyright (c) 2023
 */
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t size1,uint8_t mode);

/**
 * @brief 
 * 
 * @param x 
 * @param y 
 * @param chr 
 * @param size1 
 * @param mode 
 * @version 0.1
 * @author Adelaide ({1479398604xz@gmail.com})
 * @date 2023-03-12
 * @copyright Copyright (c) 2023
 */
void OLED_ShowString(uint8_t x,uint8_t y,uint8_t *chr,uint8_t size1,uint8_t mode);

/**
 * @brief 
 * 
 * @return uint8_t 
 * @version 0.1
 * @author Adelaide ({1479398604xz@gmail.com})
 * @date 2023-03-12
 * @copyright Copyright (c) 2023
 */
uint8_t OLED_Refresh(void);

/**
 * @brief 
 * 
 * @param p_buff 
 * @version 0.1
 * @author Adelaide ({1479398604xz@gmail.com})
 * @date 2023-03-12
 * @copyright Copyright (c) 2023
 */
void OLED_Show(uint8_t *p_buff);

/**
 * @brief 
 * 
 * @param i 
 * @version 0.1
 * @author Adelaide ({1479398604xz@gmail.com})
 * @date 2023-03-12
 * @copyright Copyright (c) 2023
 */
void OLED_ColorTurn(u8 i);

/**
 * @brief 
 * 
 * @param i 
 * @version 0.1
 * @author Adelaide ({1479398604xz@gmail.com})
 * @date 2023-03-12
 * @copyright Copyright (c) 2023
 */
void OLED_DisplayTurn(u8 i);

/**
 * @brief 
 * 
 * @version 0.1
 * @author Adelaide ({1479398604xz@gmail.com})
 * @date 2023-03-12
 * @copyright Copyright (c) 2023
 */
void OLED_DisPlay_On(void);

/**
 * @brief 
 * 
 * @param u8x8 
 * @param msg 
 * @param arg_int 
 * @param arg_ptr 
 * @return uint8_t 
 * @version 0.1
 * @author Adelaide ({1479398604xz@gmail.com})
 * @date 2023-03-12
 * @copyright Copyright (c) 2023
 */
uint8_t u8x8_gpio_and_delay_hw(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);


/**
 * @brief 
 * 
 * @param u8x8 
 * @param msg 
 * @param arg_int 
 * @param arg_ptr 
 * @return uint8_t 
 * @version 0.1
 * @author Adelaide ({1479398604xz@gmail.com})
 * @date 2023-03-12
 * @copyright Copyright (c) 2023
 */
uint8_t u8x8_byte_hw_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);

#endif