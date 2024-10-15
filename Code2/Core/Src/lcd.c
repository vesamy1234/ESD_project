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
void floatToStr(float num, char *str, int8_t precision) {
    int intPart = (int)num;  // L?y ph?n nguyên
    float decimalPart = num - (float)intPart;  // L?y ph?n th?p phân
    int i = 0;

    // X? lý ph?n nguyên
    if (intPart == 0) {
        str[i++] = '0';
    } else {
        if (intPart < 0) {
            str[i++] = '-';
            intPart = -intPart;
            decimalPart = -decimalPart;  // C?p nh?t ph?n th?p phân theo d?u
        }

        // Chuy?n t?ng ch? s? c?a ph?n nguyên sang chu?i
        int tempInt = intPart;
        int len = 0;
        while (tempInt > 0) {
            len++;
            tempInt /= 10;
        }

        for (int j = len - 1; j >= 0; j--) {
            str[j + i] = (intPart % 10) + '0';
            intPart /= 10;
        }
        i += len;
    }

    // Thêm d?u ch?m th?p phân
    str[i++] = '.';

    // Tính luy th?a c?a 10 th? công d? thay cho pow(10, precision)
    int factor = 1;
    for (int j = 0; j < precision; j++) {
        factor *= 10;
    }

    // X? lý ph?n th?p phân
    int decPartInt = (int)(decimalPart * factor);  // Chuy?n ph?n th?p phân thành s? nguyên v?i d? chính xác

    // Chuy?n ph?n th?p phân thành chu?i
    for (int j = precision - 1; j >= 0; j--) {
        str[i + j] = (decPartInt % 10) + '0';
        decPartInt /= 10;
    }

    // K?t thúc chu?i
    i += precision;
    str[i] = '\0';
}

