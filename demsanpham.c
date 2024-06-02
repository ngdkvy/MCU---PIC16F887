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
#INCLUDE <LCD.C>

#DEFINE UP PIN_B0
#DEFINE DW PIN_B1

UNSIGNED INT8 SP, SOMAX;

VOID HTSP()
{
   LCD_GOTOXY(1,2);
   PRINTF(LCD_PUTC, "SAN PHAM: %02U", SP);
}
VOID HIENTHI_SOMAX()
{
   LCD_GOTOXY(1,1);
   PRINTF(LCD_PUTC, "SAN PHAM MAX: %02U", SOMAX);
}
VOID MAIN ()
{
   SET_TRIS_D(0);
   SET_TRIS_E(0);
   LCD_INIT();
   SOMAX = 15;
   HIENTHI_SOMAX();
   SETUP_TIMER_0 (T0_EXT_L_TO_H|T0_DIV_1);
   SET_TIMER0(0);
LOOP:
   SP = GET_TIMER0();
   HTSP();
   IF (!INPUT(UP))
   {
      DELAY_MS (5);
      IF (!INPUT(UP))
      {
         WHILE (!INPUT(UP));
         IF (SOMAX<20)
            SOMAX++;
      }
   }
   IF (!INPUT(DW))
   {
      DELAY_MS (5);
      IF (!INPUT(DW))
      {
         WHILE (!INPUT(DW));
         IF (SOMAX>10)
            SOMAX--;
      }
   }
   HIENTHI_SOMAX();
   IF (SP == SOMAX)
      WHILE (TRUE)
      {
         LCD_GOTOXY(1,2);
         LCD_PUTC("DA DU SAN PHAM ");
         DELAY_MS(300);
         LCD_GOTOXY(1,2);
         LCD_PUTC("               ");
         DELAY_MS(300); 
      }
   GOTO LOOP;
}
         
   
   
