#include "LCD.h"
#include "string.h"
#include "stdio.h"
#include "math.h"

void LCD_Write(uint8_t data)
{
	HAL_GPIO_WritePin(LCD_PORT, LCD_D4, ((data >> 0) & 0x01));
	HAL_GPIO_WritePin(LCD_PORT, LCD_D5, ((data >> 1) & 0x01));
	HAL_GPIO_WritePin(LCD_PORT, LCD_D6, ((data >> 2) & 0x01));
	HAL_GPIO_WritePin(LCD_PORT, LCD_D7, ((data >> 3) & 0x01));

// kich hoat chan enable
	HAL_GPIO_WritePin(LCD_PORT,LCD_E, 1);
	HAL_Delay(1);
	HAL_GPIO_WritePin(LCD_PORT,LCD_E, 0);
}
void LCD_Send(uint8_t Reg, uint8_t data)
{
	HAL_GPIO_WritePin(LCD_PORT, LCD_RS, Reg);   // Reg = 0 : thanh ghi data ; Reg = 1 : thanh ghi lenh
	LCD_Write(data >> 4);
	LCD_Write(data);
}
void LCD_Init()
{
	LCD_Send(cmd_reg, 0x33);                   // lenh de khoi tao
	LCD_Send(cmd_reg, 0x32);                  // lenh de khoi tao
	LCD_Send(cmd_reg, 0x28);                   // che do 4 bit, 2 hang, 5x7
	LCD_Send(cmd_reg, 0x0E);                   // hien thi man hinh va chop con tro
	LCD_Send(cmd_reg, 0x06);                  // tang con tro
	LCD_Send(cmd_reg, 0x01);                   // xoa toan man hinh
}
void LCD_Clear()                                //xoa toan man hinh
{
	LCD_Send(cmd_reg, 0x01);
}
void LCD_Location(uint8_t x, uint8_t y)         // chon vi tri
{
  if(x == 0)
	  LCD_Send(cmd_reg, 0x80 + y);
  else if(x == 1)
	  LCD_Send(cmd_reg, 0xC0 + y);
}
void LCD_Write_String(char* string)              // ghi chuoi ki tu
{
	for(uint8_t i = 0; i < strlen(string); i++)
	{
		LCD_Send(data_reg, string[i]);
	}
}
void LCD_Write_Number(int number)                 // ghi chu so
{
	char buffer[8];
	sprintf(buffer, "%d", number);
	LCD_Write_String(buffer);
}
void LCD_Write_Float(float number)                 // ghi chu so thap phan
{
	char buffer[16];
	floatToStr(number,buffer,3);
	LCD_Write_String(buffer);
}
void floatToStr(float num, char *str, int8_t precision)
{
    int32_t intPart = (int32_t)num;  // Lay phan nguyen
    float decimalPart = num - (float)intPart;  // Lay phan thap phân
    int8_t i = 0;

    // Xu ly phan nguyen
    if (intPart == 0)
    {
        str[i++] = '0';
    }
    else
    {
        if (intPart < 0)
        {
            str[i++] = '-';
            intPart = -intPart;
            decimalPart = -decimalPart;  // Cap nhat phan thap phân theo dau
        }

        // Chuyen tung chu so cua phan nguyen sang chuoi
        int32_t tempInt = intPart;
        int8_t len = 0;
        while (tempInt > 0)
        {
            len++;
            tempInt /= 10;
        }

        for (int8_t j = len - 1; j >= 0; j--)
        {
            str[j + i] = (intPart % 10) + '0';
            intPart /= 10;
        }
        i += len;
    }
    if (decimalPart == 0)
    {
    	str[i] = '\0';
    	return;
    }
    // Them dau cham thap phân
    str[i++] = '.';

    // Tính luy thua cua 10 thay cho pow(10, precision)
    int16_t factor = 1;
    for (int8_t j = 0; j < precision; j++)
    {
        factor *= 10;
    }

    // Xu ly phan thap phan
    int16_t decPartInt = (int16_t)(decimalPart * factor);  // Chuyen phan thap phan thanh so nguyen voi do chinh xac

    // Chuyen phan thap phan thanh chuoi
    for (int8_t j = precision - 1; j >= 0; j--)
    {
        str[i + j] = (decPartInt % 10) + '0';
        decPartInt /= 10;
    }

    // Ket thuc chuoi
    i += precision;
    str[i] = '\0';
}

