#include <REG51.H>
#include "Delay.h"
#include "OLED.h"
#include "DS18B20.h"

extern uint32_t DS18B20_Tempreature;

sbit LED = P2^5;//LED引脚 低电平点亮


uint8_t TMAX=30;//温度限制值
uint8_t HT,LT,MT;//分别对应十位，个位，小数位

void LED_ON(void)
{
    LED = 0;
}

void LED_OFF(void)
{
    LED = 1;
}


void Start_F(void)//一级界面
{
    uint8_t i;
    OLED_ShowString(1,1,"TemperatureAlarm");
    OLED_ShowString(3,4,"Watting");
    DS18B20_Get_Tempreature();
    for(i=0; i<10; i++)
    {
        OLED_ShowString(3,11,".  ");
        OLED_ShowString(3,11," . ");
        OLED_ShowString(3,11,"  .");
    }//等待系统运行稳定
    OLED_Clear();
}

void Start_S(void)//一级界面
{
    OLED_ShowString(1,1,"TemperatureAlarm");
    OLED_ShowString(2,4,"Tem:+   . C");
    OLED_ShowString(3,3,"State:");
}

void DATA_Reflesh(void)
{
    OLED_ShowNum(2,9,HT,2);
    OLED_ShowNum(2,11,LT,1);
    OLED_ShowNum(2,13,MT,1);
    
}
void main()
{
    OLED_Init();
    Start_F();//一级界面
    Start_S();//二级界面
    while(1)
    {
        DS18B20_Get_Tempreature();
        HT=DS18B20_Tempreature/100;
        LT=DS18B20_Tempreature/10%10;
        MT=DS18B20_Tempreature%10;
        
        DATA_Reflesh();
        
        if(HT*10+LT>=TMAX)
        {
            LED_ON();
            OLED_ShowString(3,9,"Warning");
        }
        else 
        {
            LED_OFF();
            OLED_ShowString(3,9,"Normal ");
        }
    }
}
