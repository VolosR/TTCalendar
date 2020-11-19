#include "config.h"

TTGOClass *ttgo;
int n=7;

#define orange 0xFC64
#define dark 0x334F
#define darkOrange 0xFB20

int posX[7];

int boxSize=26;
int space=2;
int start=21;
String math="";

String days[7]={"Mo","Tu","We","Th","Fr","Sa","Su"};
int monthsDays[12]={31,29,31,30,31,30,31,31,30,31,30,31};
int startDay[12]={3,6,7,3,5,1,3,6,2,4,7,2};
String monthNames[12]={"January","February","March","April","May","June","July","August","September","October","November","December"};


int m=0;
bool irq = false;

void setup()
{
    ttgo = TTGOClass::getWatch();
    ttgo->begin();
    ttgo->openBL();
    ttgo->tft->fillScreen(TFT_WHITE);
  
    
    ttgo->tft->setTextFont(2);
  
  

   for(int i=0;i<n;i++)
   posX[i]=(start+(i*boxSize)+(space*i));


   fill(0);
  
    
    ttgo->tft->setTextColor(0xB71F);
    
    
    pinMode(AXP202_INT, INPUT_PULLUP);
    attachInterrupt(AXP202_INT, [] {
        irq = true;
    }, FALLING);

    //!Clear IRQ unprocessed  first
    ttgo->power->enableIRQ(AXP202_PEK_SHORTPRESS_IRQ | AXP202_VBUS_REMOVED_IRQ | AXP202_VBUS_CONNECT_IRQ | AXP202_CHARGING_IRQ, true);
    ttgo->power->clearIRQ();

 
}
int pres=1;
int chosen=0;
void loop()
{
    int16_t x, y;
    if (ttgo->getTouch(x, y)) {
       if(pres==1) 
        { 
          if(x>120){
          pres=0;
          chosen++;
        if(chosen==12)
        chosen=0;}

          if(x<=120){
          pres=0;
          chosen--;
        if(chosen==-1)
        chosen=11;}
        
        fill(chosen);
        }
            }
    
    
    
    else {pres=1;}


    

     if (irq) {
        irq = false;
        ttgo->power->readIRQ();

        if (ttgo->power->isPEKShortPressIRQ()) {
            fill(1);
        }
        ttgo->power->clearIRQ(); }
    

}

void fill(int x){
  ttgo->tft->setTextColor(dark);
  ttgo->tft->setTextFont(4);
   ttgo->tft->drawString("<",posX[0],8);
   ttgo->tft->drawString(">",posX[6],8);
 ttgo->tft->setTextFont(2);

 
  
  ttgo->tft->fillRect(60,6,124,34,TFT_WHITE);
  ttgo->tft->drawString(monthNames[x]+" 2020",70,12);
  
   ttgo->tft->setTextColor(TFT_WHITE);
  
  int curr=0;
  for(int i=0;i<n;i++)
   for(int j=0;j<n;j++){
    
    
    if(i==0){
    ttgo->tft->fillRoundRect(posX[j],posX[i]+20,boxSize,boxSize,2,darkOrange);  
    ttgo->tft->drawString(days[j],posX[j]+6,posX[i]+4+20);
    
    }
    else{
    curr++;
    ttgo->tft->fillRoundRect(posX[j],posX[i]+20,boxSize,boxSize,2,TFT_WHITE); 
    if(curr>=startDay[x])  {
    int n=curr-startDay[x]+1;
    if(n<=monthsDays[x]){
    ttgo->tft->fillRoundRect(posX[j],posX[i]+20,boxSize,boxSize,2,dark); 
    ttgo->tft->drawString(String(n),posX[j]+6,posX[i]+4+20);}
   
    }
     }
     
  }}
