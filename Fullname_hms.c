#INCLUDE <16F887.H>
#FUSES HS
#USE DELAY (CLOCK = 20M)

#DEFINE LCD_ENABLE_PIN PIN_E2
#DEFINE LCD_RS_PIN PIN_E0
#DEFINE LCD_RW_PIN PIN_E1
#DEFINE LCD_DATA4 PIN_D4
#DEFINE LCD_DATA5 PIN_D5
#DEFINE LCD_DATA6 PIN_D6
#DEFINE LCD_DATA7 PIN_D7
#INCLUDE <TV_LCD.C>

UNSIGNED INT8 SEC = 0, MIN = 59, HOUR = 23,I;
UNSIGNED INT8 HOTEN[]={78, 103, 117, 121, /* EEX*/ 110, /* DD*/105, 110,104, 75,104,/*AS*/110, 104, 86,121};
UNSIGNED INT8 EEX[8]={0X0A, 0X14, 0X04, 0X0A, 0X0E, 0X0A,0X0C, 0X0F};
UNSIGNED INT8 DD[8]={0x0C, 0X0A, 0X09, 0X1D, 0X09,0X09, 0X0A, 0X0C};
UNSIGNED INT8 AS[8]={0x05,0x0E,0x0A,0x0E,0x11,0x1E,0x0E,0x00};
UNSIGNED INT8 IH[8]={0X00,0X04,0X02,0X04,0X04,0X04,0X0E,0X00};

VOID HOTEN()
{
   //VUNG 0
   LCD_COMMAND(0X40);
   FOR (I=0;I<8;I++)
      LCD_DATA(EEX[I]);
   //VUNG 1
   LCD_COMMAND(0X48);
   FOR (I=0;I<8;I++)
      LCD_DATA(DD[I]);
   //VUNG 2
   LCD_COMMAND(0X50);
   FOR (I=0;I<8;I++)
      LCD_DATA(IH[I]);
   //VUNG 3
   LCD_COMMAND(0X58);
   FOR (I=0;I<8;I++)
      LCD_DATA(AS[I]);
   //HOTEN
   LCD_COMMAND (0X80);
   LCD_DATA ("Nguy");
   LCD_DATA(0);
   LCD_DATA("n ");
      
   LCD_COMMAND (0X87);
   LCD_DATA (1);
   LCD_DATA(2);
   LCD_DATA("nh Kh");
   
   LCD_COMMAND (0X87);
   LCD_DATA (3);
   LCD_DATA("nh Vy");
}   
VOID TIME()
{
   FOR (SEC = 0; SEC < 60; SEC++)
      {
         LCD_COMMAND (0XC5) ;
         LCD_DATA(HOUR);
         LCD_DATA(':');
         LCD_DATA(MIN);
         LCD_DATA(':');
         LCD_DATA(SEC/10);
         DELAY_MS (200) ;
      }
      MIN++;
      IF (MIN > 59)
      {
         HOUR++;
         MIN = 0;
      }
      IF (HOUR > 23)
         HOUR  = 0;
}
VOID MAIN()
{
   SET_TRIS_D (0) ;
   SET_TRIS_E (0) ;
   LCD_setup() ;
   //LCD_GOTOXY (1, 1) ;
   //LCD_PUTC ("NGUYEN DINH KHANH VY") ;
   WHILE (TRUE)
   {
   lcd_command(0xC0);
lcd_data ("MSSV:22161006");
      HOTEN();
      TIME();
   }
}

   

