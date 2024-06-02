#INCLUDE <16F887.H>
#FUSES HS
#USE DELAY (CLOCK = 20M)

UNSIGNED INT8  DLHT[8]={0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF};
CONST UNSIGNED INT8 MA7DOAN[10]={0XC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XF8,0X80,0X90},
                    MSSV[8]={0XA4,0XA4,0XF9,0X82,0XF9,0XC0,0X99,0XB0};

UNSIGNED INT8 GIAY, QUET, PHUT;
SIGNED INT8 DEM1, DEM2;

VOID HIENTHIMSSV()
{
   UNSIGNED INT8 I, Q;
   FOR (Q = 0;Q < 30;Q++)
   {
      QUET = 0XFE;//1111 1110
      FOR (I = 0;I < 8;I++)
      {
         OUTPUT_D (QUET);
         OUTPUT_C (MSSV[I]);
         DELAY_MS (4);
         OUTPUT_C (0XFF);
         QUET = (QUET<<1) + 1;
      }
   }
}
VOID HIENTHI()
{
   UNSIGNED INT8 I, Q;
   FOR (Q = 0;Q < 30;Q++)
   {
      QUET = 0XFE;
      FOR (I = 0;I < 8;I++)
      {
         OUTPUT_D (QUET);
         OUTPUT_C (DLHT[I]);
         DELAY_MS (3);
         OUTPUT_C (0XFF);
         QUET = (QUET<<1) + 1;
      }
   }
}
VOID XOASOLIEU()
{
   UNSIGNED INT8 N, K;
   FOR (N = 0; N < 8; N++)
   {
      FOR (K = 0;K < 7;K++)
         DLHT[K] = DLHT[K+1];
      DLHT[7] = 0XFF;
      HIENTHI();
   }
}
VOID DEMSO()
{ 
   DLHT[2]=DLHT[3]=DLHT[4]=DLHT[5]=0XBF;//00----00
   UNSIGNED INT8 SOLAN = 0;
   DEM1 = 0;
   DEM2 = 26;
   DO 
   {
      DLHT[7] = MA7DOAN[DEM1%10];
      DLHT[6] = MA7DOAN[DEM1/10];
      DLHT[1] = MA7DOAN[DEM2%10];
      DLHT[0] = MA7DOAN[DEM2/10];
      HIENTHI();
      DEM1++;
      IF (DEM1 > 15) 
      {
         DEM1 = 0;
         SOLAN++;
      }
      DEM2 = DEM2 - 2;
      IF (DEM2 < 0)
         DEM2 = 26;
      
   }
   WHILE (SOLAN<1);
   XOASOLIEU();
}
VOID COCACOLA()
{
   CONST UNSIGNED INT8 COCACOLA[8]={0XC6,0XC0,0XC6,0X88,0XC6,0XC0,0XC7,0X88};
   UNSIGNED INT8 N, K;
   FOR (N = 0; N < 16; N++)
   {
      FOR (K = 0;K < 7;K++)
         DLHT[K] = DLHT[K+1];
      IF (N < 8 )
         DLHT[7] = COCACOLA[N];
      ELSE
         DLHT[7] = 0XFF;
      HIENTHI();
   }
}
VOID HELLO()
{
   CONST UNSIGNED INT8 HELLO[6]={0X89,0X86,0XC7,0XC7,0XC0,0XFF};
   UNSIGNED INT8 N, K;
   FOR (N = 0; N < 13; N++)
   {
      FOR (K = 0;K < 7;K++)
         DLHT[K] = DLHT[K+1];
      IF (N < 5 )
         DLHT[7] = HELLO[N];
      ELSE
         DLHT[7] = 0XFF;
      HIENTHI();
   }
}
VOID GIATRIHIENTHI()
{
     DLHT[5]=DLHT[2]=0XBF;//00-00-00
     DLHT[7] = MA7DOAN[GIAY%10];
     DLHT[6] = MA7DOAN[GIAY/10];
     DLHT[4] = MA7DOAN[PHUT%10];
     DLHT[3] = MA7DOAN[PHUT/10];
     DLHT[1] = MA7DOAN[0];
     DLHT[0] = MA7DOAN[0];
     HIENTHI();
}
VOID DEMGIAY ()
{
   WHILE (PHUT<2)
   {
      FOR (GIAY = 0; GIAY < 60; GIAY++)
         GIATRIHIENTHI();
      IF (GIAY>59)
         PHUT++;
   }
}
VOID MAIN ()
{
   SET_TRIS_C(0);
   SET_TRIS_D(0);
   WHILE (TRUE)
   {
      HIENTHIMSSV();
      DEMSO();
      COCACOLA();
      HELLO();
      DEMGIAY();
   }
}
   
   
