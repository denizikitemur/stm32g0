#include "stm32g0xx.h"
#include<stdio.h>
void delay(volatile uint32_t);
volatile uint32_t LEDDELAY=10UL;
volatile uint32_t LEDDELAY1=80UL;
volatile uint32_t millis;
uint32_t dakika2[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x47, 0x7F,
0x6F};
uint32_t kontrol[4] = {0x10, 0x20, 0x40, 0x80};
uint32_t dakika1[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x47, 0x7F,
0x6F};
uint32_t saniye2[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x47, 0x7F,
0x6F};
uint32_t saniye1[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x47, 0x7F,
0x6F};
int ctrl=0;
volatile int i=2;
volatile int j=4;
volatile int k=5;
volatile int l=9;
enum MOD {mod0=0, mod1=16000001, mod2=8000001, mod3=1600001, mod4=160001,
mod5=16001};
volatile enum MOD currentMod=mod0;
void durum(){
switch(currentMod) {
case mod0:
currentMod = mod1;
break;
case mod1:
currentMod = mod2;
break;
case mod2:
currentMod = mod3;
break;
case mod3:
currentMod = mod4;

break;
case mod4:
currentMod = mod5;
break;
case mod5:
currentMod = mod0;
break;
}
}
uint32_t buton(){
uint32_t count;
count=GPIOA->IDR;
count &=2U;
if(count==1){
count =1U;//0001; GPIOB->IDR=xxx1;
return 1;
}
else{
return 0;
}
}
void systickinit(uint32_t tick){
SysTick->CTRL = 0;
SysTick->LOAD = tick - 1;
SysTick->VAL = 0;
SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
NVIC_EnableIRQ(SysTick_IRQn);
NVIC_SetPriority (SysTick_IRQn,0);
}
 void SysTick_Handler(void) {
 l--;
 if(l < 0 ){
 l=9;
 k--;
 if(k < 0 ){
 j--;
 k=5;
 }
 if(j < 0 ){
 j=9;

 i--;
 }
 }
 if(i == 0 && j == 0 && k == 0 && l == 0){
 i=2;
 j=4;
 l=9;
 k=5;
 }
}
void segment1(uint32_t x){
GPIOB->ODR &= 0x00;
GPIOA->ODR |= ~(kontrol[0]);
GPIOA->ODR &= ~(kontrol[0]);
GPIOB->ODR &= dakika2[x];
GPIOB->ODR |= dakika2[x];
}
void segment2(uint32_t x){
GPIOB->ODR &= 0x00;
GPIOA->ODR |= ~(kontrol[1]);
GPIOA->ODR &= ~(kontrol[1]);
GPIOB->ODR &= dakika1[x];
GPIOB->ODR |= dakika1[x];
GPIOB->ODR |=0x80;
}
void segment3(uint32_t x){
GPIOB->ODR &= 0x00;
GPIOA->ODR |= ~(kontrol[2]);
GPIOA->ODR &= ~(kontrol[2]);
GPIOB->ODR &= saniye2[x];
GPIOB->ODR |= saniye2[x];
}
void segment4(uint32_t x){
GPIOB->ODR &= 0x00;
GPIOA->ODR |= ~(kontrol[3]);
GPIOA->ODR &= ~(kontrol[3]);
GPIOB->ODR &= saniye1[x];
GPIOB->ODR |= saniye1[x];
}
void baslangic(){
segment1(0);
delay(LEDDELAY1);

segment2(0);
delay(LEDDELAY1);
segment3(0);
delay(LEDDELAY1);
segment4(0);
delay(LEDDELAY1);
}
void display(){
segment1(i);
delay(LEDDELAY1);
segment2(j);
delay(LEDDELAY1);
segment3(k);
delay(LEDDELAY1);
segment4(l);
delay(LEDDELAY1);
}
void delay(volatile uint32_t s){
for(;s>0; s--);
}
int main(void){
RCC->IOPENR |=3U; // 3U=0011; RCC->IOPENR = xxxx...xx11;
GPIOA->MODER &= ~(0xFF<<8);// GPIOA->MODER |
GPIOA->MODER |= (0x55<<8); // 0101 0101 << 8 = 0101
GPIOA->MODER &= ~(0xF); //xxxx...0000
GPIOA->MODER |= 0x1 ;// xxxx...0001 buton için PA1 ayarlandı
GPIOB->MODER |= (0xFFFF);
GPIOB->MODER &= (0x5555);
while(1){
if(currentMod == mod0){
if(buton() == 0){
display();
delay(LEDDELAY1);
}
else if(buton() == 1){
durum();
}
}
else if(currentMod == mod1){

if(buton() == 0){
systickinit(currentMod);
display();
}
else if(buton() == 1){
durum();
}
}
else if (currentMod == mod2){
if(buton() == 0){
systickinit(currentMod);
display();
}
else if(buton() == 1){
durum();
}
}
else if(currentMod == mod3){
if(buton() == 0){
systickinit(currentMod);
display();
}
else if(buton() == 1){
durum();
}
}
else if(currentMod == mod4){
if(buton() == 0){
systickinit(currentMod);
display();
}
else if(buton() == 1){
durum();
}
}
else if(currentMod == mod5){
if(buton() == 0){
systickinit(currentMod);
display();
}
else if(buton() == 1){
durum();
}
}
}

return 0;
}
