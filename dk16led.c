#INCLUDE <16F887.H>
#FUSES HS
#USE DELAY (CLOCK = 20M)

UNSIGNED INT8 YC, YD;
UNSIGNED INT16 Y,I, K, SAVE, RUN;

VOID XUAT_16LED ()
{
   YD = Y;
   YC = Y >>8;
   OUTPUT_C (YC);
   OUTPUT_D (YD);
}
VOID SANGDON()
{
   Y = 0; //tat ca den deu tat; 0000 0000 0000 0000
   XUAT_16LED ();
   SAVE = 0; // 0000 0000 0000 0000 
   FOR (K = 0; K<16; K++)
   {
      RUN = 0X0001; // 0000 0000 0000 0001
      FOR (I = K; I<16; I++)
      {
         Y = RUN | SAVE; // luu trang thai sang, diem sang dang chay
         XUAT_16LED ();
         DELAY_MS(70);
         RUN = RUN <<1; //dich diem sang
      }
      SAVE = Y; //luu trang thai sang
   }
}
VOID TATDON ()
{
   Y = 0XFFFF;//1111 1111 1111 1111
   XUAT_16LED ();
   SAVE = 0XFFFE;//luu diem toi, 1111 1111 1111 1110
   FOR (K=0; K<16; K++)
   {
      RUN = 0X0001 <<K;
      FOR (I = 0; I < K+1; I++)
      {
         RUN = RUN >> 1;
         Y = RUN | SAVE;
         XUAT_16LED();
         DELAY_MS(70);
      }
      SAVE = SAVE <<1;
   }
}  
VOID SANGDANTRAI()
{
   Y = 0;//0000 0000 0000 0000
   FOR (I = 0; I < 16; I++)
   {
      Y = (Y<<1) + 1;
      OUTPUT_D (Y);
      OUTPUT_C (Y >> 8);
      DELAY_MS (100);
   }
}  
VOID TATDANPHAI ()
{
   Y = 0XFFFF;//1111 1111 1111 1111
   FOR (I = 0; I < 16; I++)
   {
      Y = (Y>>1);
      OUTPUT_D (Y);
      OUTPUT_C (Y >> 8);
      DELAY_MS (100);
   }
}
VOID XENKE ()
{
      Y = 0XAAAA;//1010 1010 1010 1010
      XUAT_16LED ();
      DELAY_MS (100);
      Y = 0X5555; //0101 0101 0101 0101
      XUAT_16LED ();
      DELAY_MS (100);
}
VOID CHOPTAT ()
{  
      Y = 0XFFFF;//1111 1111 1111 1111
      XUAT_16LED ();
      DELAY_MS(200);
      Y = ~Y;
      XUAT_16LED ();
      DELAY_MS(200);
}
VOID SANGGIUARA()
{
   Y = 0;
   FOR (I = 0; I < 8; I++)
   {
      YD = (YD >> 1) + 0X80;//0X80:  1000 0000
      YC = (YC << 1) + 1;
      OUTPUT_C (YC);
      OUTPUT_D (YD);
      DELAY_MS(150);
   }
}
VOID TATNGOAIVAO()
{
   Y = 1;
   FOR (I = 0; I < 8; I++)
   {
      YD = (YD <<1);
      YC = (YC>>1);
      OUTPUT_C (YC);
      OUTPUT_D (YD);
      DELAY_MS(150);
   }
}
VOID SANGNGOAIVAO ()
{
   Y = 0X0000;
   FOR (I = 0; I < 8; I++)
   {
      YD = (YD << 1) +1;
      YC = (YC >>1) + 0X80;//1000 0000
      OUTPUT_C (YC);
      OUTPUT_D (YD);
      DELAY_MS(200);
   }
}
VOID TATGIUARA()
{
   Y = 1;
   FOR (I = 0; I < 8; I++)
   {
      YD = (YD >> 1) ;
      YC = (YC << 1);
      OUTPUT_C (YC);
      OUTPUT_D (YD);
      DELAY_MS(250);
   }
}
VOID MAIN ()
{
   WHILE (TRUE)
   {
      //SANGDON();
      //TATDON();
      SANGDANTRAI();
      TATDANPHAI();
      //XENKE();
      // CHOPTAT();
      //SANGGIUARA();
      //TATNGOAIVAO();
      //SANGNGOAIVAO();
      //TATGIUARA();
   }
}
   
   
