#INCLUDE <16F887.H>
#FUSES HS
#USE DELAY (CLOCK=20M)

CONST UNSIGNED INT8 MA7DOAN[10]={0XC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XF8,0X80,0X90};
SIGNED INT8 DEM, I;

#DEFINE UP PIN_B0
#DEFINE DW PIN_B1
#DEFINE START PIN_B2

VOID GIAIMA7DOAN (UNSIGNED INT8 SO)
{
   OUTPUT_C (MA7DOAN[SO/10]);
   OUTPUT_D (MA7DOAN[SO%10]);
}
VOID MAIN ()
{
   SET_TRIS_C(0);
   SET_TRIS_D(0);
   SET_TRIS_B(0XFF);
   PORT_B_PULLUPS (TRUE);
TD:
   DEM=5;
GM:  
   GIAIMA7DOAN (DEM);
   IF (!INPUT(UP))
   {
      DELAY_MS(10);
      IF (!INPUT(UP))
      {
         WHILE (!INPUT(UP));
         DEM++;
         IF (DEM>15)
            GOTO TD;
      }
   }
   IF (!INPUT(DW))
   {
      DELAY_MS(10);
      IF (!INPUT(DW))
      {
         WHILE (!INPUT(DW));
         DEM = DEM-2;
         IF (DEM<5)
            DEM = 15;
      }
   }
   IF (!INPUT(START))
   {
      DELAY_MS(10);
      IF (!INPUT(START))
      {
         WHILE (!INPUT(START));
         FOR (I=0;I<=DEM;I++)
         {
            GIAIMA7DOAN (I);
            DELAY_MS(100);
         }
      }
   }
   GOTO GM;
}
   

