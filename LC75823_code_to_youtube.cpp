/**********************************************************************/
/*This code is not clean and OFFCOURSE will be possible do it better! */ 
/*this is only a group of functions to be used as independent code,  */ 
/*and by this way will be possible to any person can do the changes   */ 
/*of code and see what happen.                                         */
/*The code don't depend of any external library or extenal functions  */
/*complicated.                                                         */
/*I'm let the values to sent as binnary, this allow swap bit by bit */
/* to is possible test segment by segment without convert to HEX    */
/**********************************************************************/
/* This code show how is possible work with the driver LC75823 Sanyo */
/*Begining of Auto generated code by Atmel studio */

#define VFD_in 7  // This is the pin number 7 on Arduino UNO
#define VFD_clk 8 // This is the pin number 8 on Arduino UNO
#define VFD_ce 9 // This is the pin number 9 on Arduino UNO

//ATT: On the Uno and other ATMEGA based boards, unsigned ints (unsigned integers) are the same as ints in that they store a 2 byte value.
//Long variables are extended size variables for number storage, and store 32 bits (4 bytes), from -2,147,483,648 to 2,147,483,647.

//*************************************************//
void setup() {
  pinMode(VFD_clk, OUTPUT);
  pinMode(VFD_in, OUTPUT);
  pinMode(VFD_ce, OUTPUT);
 
  pinMode(13, OUTPUT);
  Serial.begin(9600); // only to debug
}
void send_char(unsigned char a)
{
 //
 unsigned char transmit = 15; //define our transmit pin
 unsigned char data = 170; //value to transmit, binary 10101010
 unsigned char mask = 1; //our bitmask
  data=a;
  // the validation of data happen when clk go from LOW to HIGH.
  digitalWrite(VFD_ce, LOW); // When strobe is low, all output is enable. If high, all output will be set to low.
  delayMicroseconds(5);
  digitalWrite(VFD_clk,LOW);// need invert the signal to allow 8 bits is is low only send 7 bits
  delayMicroseconds(5);
  for (mask = 0b00000001; mask>0; mask <<= 1) { //iterate through bit mask
  digitalWrite(VFD_clk,LOW);// need invert the signal to allow 8 bits is is low only send 7 bits
  delayMicroseconds(5);
    if (data & mask){ // if bitwise AND resolves to true
      digitalWrite(VFD_in, HIGH);
      //Serial.print(1);
    }
    else{ //if bitwise and resolves to false
      digitalWrite(VFD_in, LOW);
      //Serial.print(0);
    }
    digitalWrite(VFD_clk,HIGH);// need invert the signal to allow 8 bits is is low only send 7 bits
    delayMicroseconds(5);
    //
    digitalWrite(VFD_ce, HIGH); // When strobe is low, all output is enable. If high, all output will be set to low.
  delayMicroseconds(5);
  }
}
/*********************************************************************/
// I h've created 3 functions to send bit's, one with strobe, other without strobe and one with first byte with strobe followed by remaing bits.
void send_char_without(unsigned char a)
{
 unsigned char transmit = 15; //define our transmit pin
 unsigned char data = 170; //value to transmit, binary 10101010
 unsigned char mask = 1; //our bitmask
  data=a;
  for (mask = 0b00000001; mask>0; mask <<= 1) { //iterate through bit mask
  digitalWrite(VFD_clk, LOW);
  delayMicroseconds(5);
    if (data & mask){ // if bitwise AND resolves to true
      digitalWrite(VFD_in, HIGH);
      //Serial.print(1);
    }
    else{ //if bitwise and resolves to false
      digitalWrite(VFD_in, LOW);
      //Serial.print(0);
    }
    digitalWrite(VFD_clk,HIGH);// need invert the signal to allow 8 bits is is low only send 7 bits
    delayMicroseconds(5);
  }
}
/*********************************************************************/
void send_char_8bit_stb(unsigned char a)
{
 unsigned char transmit = 15; //define our transmit pin
 unsigned char data = 170; //value to transmit, binary 10101010
 unsigned char mask = 1; //our bitmask
 int i = -1;
  data=a;
  for (mask = 0b00000001; mask>0; mask <<= 1) { //iterate through bit mask
   i++;
   digitalWrite(VFD_clk, LOW);
  delayMicroseconds(5);
    if (data & mask){ // if bitwise AND resolves to true
      digitalWrite(VFD_in, HIGH);
      //Serial.print(1);
    }
    else{ //if bitwise and resolves to false
      digitalWrite(VFD_in, LOW);
      //Serial.print(0);
    }
    digitalWrite(VFD_clk,HIGH);// 
    delayMicroseconds(1);
    if (i==7){
    Serial.println(i);
    digitalWrite(VFD_ce, HIGH);
    delayMicroseconds(1);
    }  
  }
}
/*******************************************************************/
void allON_LC75823(){
unsigned char group=0;
//send total of 56 bits (7Bytes), the 4 last 14 bits belongs to controls
//The p0, p1, p2 & p3 at 0, means all pins from s1 to s12 will belongs to segments, other's settings tell will px is a port general purpose!
      for(int i=0; i<3;i++){   // Dx until 164 bits
            group=i;
      digitalWrite(VFD_ce, LOW); //
      delayMicroseconds(1);
      // Position of bit(..76543210)
      send_char_8bit_stb(0B01000001); //(0x41) firts 8 bits is address, every fixed as (0B01000001), see if clk finish LOW or HIGH Very important!
      delayMicroseconds(1);
      // On the 75878 the message have first 16*8 bits more 8 times to performe 128 bits(last byte is control: 0BXXX00000)
          
          send_char_without(0B11111111);  send_char_without(0B11111111); //   1:8     -9:16// 
          send_char_without(0B11111111);  send_char_without(0B11111111); //  17:24    -25:32// 
          send_char_without(0B11111111);  send_char_without(0B11111111); //  33:40    -41:48//
          send_char_without(0B11111111);  send_char_without(0B11111111); //  49:56    -57:64//
          send_char_without(0B11111111);  send_char_without(0B11111111); //  65:72    -73:80//
          send_char_without(0B11111111);  send_char_without(0B11111111); //  81:88    -89:96//
          send_char_without(0B11111111);  send_char_without(0B11111111); //  97:104   -105:112//
          send_char_without(0B11111111);  send_char_without(0B11111111); // 113:120   -121:128// 
          send_char_without(0B11111111);  send_char_without(0B11111111); // 120:136   -137:144// 
          send_char_without(0B11111111);  send_char_without(0B00011111); // 145:152   -153:160//
          
      delayMicroseconds(1);
      digitalWrite(VFD_ce, LOW); // 
      delayMicroseconds(1);
      }
}
/**************************************************************************/
void allOFF_LC75823(){
unsigned char group=0;
//send total of 64 bits, the 4 last bits belongs to set of DR, SC, BU, * D'ont care;
//The p0, p1, p2 & p3 at 0, means all pins from s1 to s12 will belongs to segments, other's settings tell will px is a port general purpose!
      for(int i=0; i<3;i++){   // Dx until 600 bits
            group=i;
      digitalWrite(VFD_ce, LOW); //
      delayMicroseconds(1);
      send_char_8bit_stb(0B01000001); //(0x41) firts 8 bits is address, every fixed as (0B01000001), see if clk finish LOW or HIGH Very important!
      delayMicroseconds(1);
      // On the 75878 the message have first 16*8 bits more 8 times to performe 128 bits(last byte is control: 0BXXX00000)
          
          send_char_without(0B00000000);  send_char_without(0B00000000); //   1:8     -9:16// 
          send_char_without(0B00000000);  send_char_without(0B00000000); //  17:24    -25:32// 
          send_char_without(0B00000000);  send_char_without(0B00000000); //  33:40    -41:48//
          send_char_without(0B00000000);  send_char_without(0B00000000); //  49:56    -57:64//
          send_char_without(0B00000000);  send_char_without(0B00000000); //  65:72    -73:80//
          send_char_without(0B00000000);  send_char_without(0B00000000); //  81:88    -89:96//
          send_char_without(0B00000000);  send_char_without(0B00000000); //  97:104   -105:112//
          send_char_without(0B00000000);  send_char_without(0B00000000); // 113:120   -121:128// 
          send_char_without(0B00000000);  send_char_without(0B00000000); // 120:136   -137:144// 
          send_char_without(0B00000000);  send_char_without(0B00010000); // 145:152   -153:160//
      delayMicroseconds(1);
      digitalWrite(VFD_ce, LOW); // 
      delayMicroseconds(1);
      }
}
/*******************************************************************/
void LC75823_numbers_0123(void){
//
digitalWrite(VFD_ce, LOW); //
      delayMicroseconds(1);
      send_char_8bit_stb(0B01000001); //(0x41) firts 8 bits is address, every fixed as (0B01000001), see if clk finish LOW or HIGH Very important!
      delayMicroseconds(1);
          send_char_without(0B00000000);  send_char_without(0B00110000); //   1:8     -9:16// 
          send_char_without(0B00010100);  send_char_without(0B00000011); //  17:24    -25:32// 
          send_char_without(0B10000000);  send_char_without(0B01001001); //  33:40    -41:48//
          send_char_without(0B01010101);  send_char_without(0B10100000); //  49:56    -57:64//
          send_char_without(0B01101010);  send_char_without(0B00000000); //  65:72    -73:80//
          send_char_without(0B00000000);  send_char_without(0B00000000); //  81:88    -89:96//
          send_char_without(0B00000000);  send_char_without(0B00000000); //  97:104   -105:112//
          send_char_without(0B00000000);  send_char_without(0B00000000); // 113:120   -121:128// 
          send_char_without(0B00000000);  send_char_without(0B00000000); // 120:136   -137:144// 
          send_char_without(0B00000000);  send_char_without(0B00010000); // 145:152   -153:160//
      delayMicroseconds(1);
      digitalWrite(VFD_ce, LOW); // 
      delayMicroseconds(1); 
}
/*******************************************************************/
void LC75823_numbers_45678(void){
//
digitalWrite(VFD_ce, LOW); //
      delayMicroseconds(1);
      send_char_8bit_stb(0B01000001); //(0x41) firts 8 bits is address, every fixed as (0B01000001), see if clk finish LOW or HIGH Very important!
      delayMicroseconds(1);
      // On the 75878 the message have first 16*8 bits more 8 times to performe 128 bits(last byte is control: 0BXXX00000)
          send_char_without(0B00000000);  send_char_without(0B00000000); //   1:8     -9:16// 
          send_char_without(0B00000000);  send_char_without(0B00000000); //  17:24    -25:32// 
          send_char_without(0B00000000);  send_char_without(0B00000000); //  33:40    -41:48//
          send_char_without(0B00000000);  send_char_without(0B00000000); //  49:56    -57:64//
          send_char_without(0B00000000);  send_char_without(0B00010001); //  65:72    -73:80//
          send_char_without(0B10110100);  send_char_without(0B10101000); //  81:88    -89:96//
          send_char_without(0B11010010);  send_char_without(0B01010100); //  97:104   -105:112//
          send_char_without(0B00001001);  send_char_without(0B00001000); // 113:120   -121:128// 
          send_char_without(0B00110110);  send_char_without(0B01010101); // 120:136   -137:144// 
          send_char_without(0B00000011);  send_char_without(0B00010000); // 145:152   -153:160//
      delayMicroseconds(1);
      digitalWrite(VFD_ce, LOW); // 
      delayMicroseconds(1);
}
/*******************************************************************/
void LC75823_actionBass_1(void){
//
digitalWrite(VFD_ce, LOW); //
      delayMicroseconds(1);
      send_char_8bit_stb(0B01000001); //(0x41) firts 8 bits is address, every fixed as (0B01000001), see if clk finish LOW or HIGH Very important!
      delayMicroseconds(1);
      // On the 75878 the message have first 16*8 bits more 8 times to performe 128 bits(last byte is control: 0BXXX00000)
          send_char_without(0B00000000);  send_char_without(0B00000000); //   1:8     -9:16//   // 0 // 1
          send_char_without(0B00000000);  send_char_without(0B00000000); //  17:24    -25:32//  // 2 // 3
          send_char_without(0B00000000);  send_char_without(0B00000000); //  33:40    -41:48//  // 4 // 5
          send_char_without(0B00000000);  send_char_without(0B00000000); //  49:56    -57:64//  // 6 // 7
          send_char_without(0B10000000);  send_char_without(0B00000100); //  65:72    -73:80//  // 8 // 9
          send_char_without(0B01000000);  send_char_without(0B00000000); //  81:88    -89:96//  // A // B
          send_char_without(0B00000000);  send_char_without(0B00000000); //  97:104   -105:112//// C // D
          send_char_without(0B00000000);  send_char_without(0B00000000); // 113:120   -121:128//// E // F 
          send_char_without(0B00000000);  send_char_without(0B00000000); // 120:136   -137:144//// G // H 
          send_char_without(0B00000000);  send_char_without(0B00011000); // 145:152   -153:160//// I // J
      delayMicroseconds(1);
      digitalWrite(VFD_ce, LOW); // 
      delayMicroseconds(1);
}
/*******************************************************************/
void LC75823_actionBass_2(void){
//
digitalWrite(VFD_ce, LOW); //
      delayMicroseconds(1);
      send_char_8bit_stb(0B01000001); //(0x41) firts 8 bits is address, every fixed as (0B01000001), see if clk finish LOW or HIGH Very important!
      delayMicroseconds(1);
      // On the 75878 the message have first 16*8 bits more 8 times to performe 128 bits(last byte is control: 0BXXX00000)
          send_char_without(0B00000000);  send_char_without(0B00000000); //   1:8     -9:16//   // 0 // 1
          send_char_without(0B00000000);  send_char_without(0B00000000); //  17:24    -25:32//  // 2 // 3
          send_char_without(0B00000000);  send_char_without(0B00000000); //  33:40    -41:48//  // 4 // 5
          send_char_without(0B00000000);  send_char_without(0B00001000); //  49:56    -57:64//  // 6 // 7
          send_char_without(0B00000000);  send_char_without(0B00000100); //  65:72    -73:80//  // 8 // 9
          send_char_without(0B00000000);  send_char_without(0B00000000); //  81:88    -89:96//  // A // B
          send_char_without(0B00100000);  send_char_without(0B00000000); //  97:104   -105:112//// C // D
          send_char_without(0B00000000);  send_char_without(0B00000000); // 113:120   -121:128//// E // F 
          send_char_without(0B00000000);  send_char_without(0B00000000); // 120:136   -137:144//// G // H 
          send_char_without(0B00000000);  send_char_without(0B00011000); // 145:152   -153:160//// I // J
      delayMicroseconds(1);
      digitalWrite(VFD_ce, LOW); // 
      delayMicroseconds(1);
}
/*******************************************************************/
void LC75823_actionBass_3(void){
//
digitalWrite(VFD_ce, LOW); //
      delayMicroseconds(1);
      send_char_8bit_stb(0B01000001); //(0x41) firts 8 bits is address, every fixed as (0B01000001), see if clk finish LOW or HIGH Very important!
      delayMicroseconds(1);
      // On the 75878 the message have first 16*8 bits more 8 times to performe 128 bits(last byte is control: 0BXXX00000)
          send_char_without(0B00000000);  send_char_without(0B00000000); //   1:8     -9:16//   // 0 // 1
          send_char_without(0B00000000);  send_char_without(0B00000000); //  17:24    -25:32//  // 2 // 3
          send_char_without(0B00000000);  send_char_without(0B00000000); //  33:40    -41:48//  // 4 // 5
          send_char_without(0B00000000);  send_char_without(0B00000001); //  49:56    -57:64//  // 6 // 7
          send_char_without(0B00000000);  send_char_without(0B00000100); //  65:72    -73:80//  // 8 // 9
          send_char_without(0B00000000);  send_char_without(0B00000000); //  81:88    -89:96//  // A // B
          send_char_without(0B00000000);  send_char_without(0B00000001); //  97:104   -105:112//// C // D
          send_char_without(0B00000000);  send_char_without(0B00000000); // 113:120   -121:128//// E // F 
          send_char_without(0B00000000);  send_char_without(0B00000000); // 120:136   -137:144//// G // H 
          send_char_without(0B00000000);  send_char_without(0B00011000); // 145:152   -153:160//// I // J
      delayMicroseconds(1);
      digitalWrite(VFD_ce, LOW); // 
      delayMicroseconds(1);
}
/*******************************************************************/
void LC75823_actionBass_4(void){
//
digitalWrite(VFD_ce, LOW); //
      delayMicroseconds(1);
      send_char_8bit_stb(0B01000001); //(0x41) firts 8 bits is address, every fixed as (0B01000001), see if clk finish LOW or HIGH Very important!
      delayMicroseconds(1);
      // On the 75878 the message have first 16*8 bits more 8 times to performe 128 bits(last byte is control: 0BXXX00000)
          send_char_without(0B00000000);  send_char_without(0B00000000); //   1:8     -9:16//   // 0 // 1
          send_char_without(0B00000000);  send_char_without(0B00000000); //  17:24    -25:32//  // 2 // 3
          send_char_without(0B00000000);  send_char_without(0B00010000); //  33:40    -41:48//  // 4 // 5
          send_char_without(0B00000000);  send_char_without(0B00000000); //  49:56    -57:64//  // 6 // 7
          send_char_without(0B00000000);  send_char_without(0B00000100); //  65:72    -73:80//  // 8 // 9
          send_char_without(0B00000000);  send_char_without(0B00000000); //  81:88    -89:96//  // A // B
          send_char_without(0B00000000);  send_char_without(0B00000000); //  97:104   -105:112//// C // D
          send_char_without(0B00000000);  send_char_without(0B00000000); // 113:120   -121:128//// E // F 
          send_char_without(0B00001000);  send_char_without(0B00000000); // 120:136   -137:144//// G // H 
          send_char_without(0B00000000);  send_char_without(0B00011000); // 145:152   -153:160//// I // J
      delayMicroseconds(1);
      digitalWrite(VFD_ce, LOW); // 
      delayMicroseconds(1);
}
/*******************************************************************/
void LC75823_actionBass_5(void){
//
digitalWrite(VFD_ce, LOW); //
      delayMicroseconds(1);
      send_char_8bit_stb(0B01000001); //(0x41) firts 8 bits is address, every fixed as (0B01000001), see if clk finish LOW or HIGH Very important!
      delayMicroseconds(1);
      // On the 75878 the message have first 16*8 bits more 8 times to performe 128 bits(last byte is control: 0BXXX00000)
          send_char_without(0B00000000);  send_char_without(0B00000000); //   1:8     -9:16//   // 0 // 1
          send_char_without(0B00000000);  send_char_without(0B00100000); //  17:24    -25:32//  // 2 // 3
          send_char_without(0B00000000);  send_char_without(0B00000000); //  33:40    -41:48//  // 4 // 5
          send_char_without(0B00000000);  send_char_without(0B00000000); //  49:56    -57:64//  // 6 // 7
          send_char_without(0B00000000);  send_char_without(0B00000100); //  65:72    -73:80//  // 8 // 9
          send_char_without(0B00000000);  send_char_without(0B00000000); //  81:88    -89:96//  // A // B
          send_char_without(0B00000000);  send_char_without(0B00000000); //  97:104   -105:112//// C // D
          send_char_without(0B00000000);  send_char_without(0B00000000); // 113:120   -121:128//// E // F 
          send_char_without(0B00000000);  send_char_without(0B00000000); // 120:136   -137:144//// G // H 
          send_char_without(0B00000100);  send_char_without(0B00011000); // 145:152   -153:160//// I // J
      delayMicroseconds(1);
      digitalWrite(VFD_ce, LOW); // 
      delayMicroseconds(1);
}
/*******************************************************************/
void LC75823_actionBass_6(void){
//
digitalWrite(VFD_ce, LOW); //
      delayMicroseconds(1);
      send_char_8bit_stb(0B01000001); //(0x41) firts 8 bits is address, every fixed as (0B01000001), see if clk finish LOW or HIGH Very important!
      delayMicroseconds(1);
      // On the 75878 the message have first 16*8 bits more 8 times to performe 128 bits(last byte is control: 0BXXX00000)
          send_char_without(0B00000000);  send_char_without(0B00000000); //   1:8     -9:16//   // 0 // 1
          send_char_without(0B00000000);  send_char_without(0B00000100); //  17:24    -25:32//  // 2 // 3
          send_char_without(0B00000000);  send_char_without(0B00000000); //  33:40    -41:48//  // 4 // 5
          send_char_without(0B00000000);  send_char_without(0B00000000); //  49:56    -57:64//  // 6 // 7
          send_char_without(0B00000000);  send_char_without(0B00000100); //  65:72    -73:80//  // 8 // 9
          send_char_without(0B00000000);  send_char_without(0B00000000); //  81:88    -89:96//  // A // B
          send_char_without(0B00000000);  send_char_without(0B00000000); //  97:104   -105:112//// C // D
          send_char_without(0B00000000);  send_char_without(0B00000000); // 113:120   -121:128//// E // F 
          send_char_without(0B00000000);  send_char_without(0B00000000); // 120:136   -137:144//// G // H 
          send_char_without(0B00100000);  send_char_without(0B00011000); // 145:152   -153:160//// I // J
      delayMicroseconds(1);
      digitalWrite(VFD_ce, LOW); // 
      delayMicroseconds(1);
}
/*******************************************************************/
void LC75823_actionBass_7(void){
//
digitalWrite(VFD_ce, LOW); //
      delayMicroseconds(1);
      send_char_8bit_stb(0B01000001); //(0x41) firts 8 bits is address, every fixed as (0B01000001), see if clk finish LOW or HIGH Very important!
      delayMicroseconds(1);
      // On the 75878 the message have first 16*8 bits more 8 times to performe 128 bits(last byte is control: 0BXXX00000)
          send_char_without(0B00000000);  send_char_without(0B01000000); //   1:8     -9:16//   // 0 // 1
          send_char_without(0B00000000);  send_char_without(0B00000000); //  17:24    -25:32//  // 2 // 3
          send_char_without(0B00000000);  send_char_without(0B00000000); //  33:40    -41:48//  // 4 // 5
          send_char_without(0B00000000);  send_char_without(0B00000000); //  49:56    -57:64//  // 6 // 7
          send_char_without(0B00000000);  send_char_without(0B00000000); //  65:72    -73:80//  // 8 // 9
          send_char_without(0B00000000);  send_char_without(0B00000000); //  81:88    -89:96//  // A // B
          send_char_without(0B00000000);  send_char_without(0B00000000); //  97:104   -105:112//// C // D
          send_char_without(0B00000000);  send_char_without(0B00000000); // 113:120   -121:128//// E // F 
          send_char_without(0B00000000);  send_char_without(0B00000000); // 120:136   -137:144//// G // H 
          send_char_without(0B00000000);  send_char_without(0B00011001); // 145:152   -153:160//// I // J
      delayMicroseconds(1);
      digitalWrite(VFD_ce, LOW); // 
      delayMicroseconds(1);
}
/*******************************************************************/
void LC75823_Blaupunkt(void){
//
digitalWrite(VFD_ce, LOW); //
      delayMicroseconds(1);
      send_char_8bit_stb(0B01000001); //(0x41) firts 8 bits is address, every fixed as (0B01000001), see if clk finish LOW or HIGH Very important!
      delayMicroseconds(1);
      // On the 75878 the message have first 16*8 bits more 8 times to performe 128 bits(last byte is control: 0BXXX00000)
          send_char_without(0B00000000);  send_char_without(0B00000000); //   1:8     -9:16//   // 0 // 1
          send_char_without(0B01011100);  send_char_without(0B00011011); //  17:24    -25:32//  // 2 // 3
          send_char_without(0B00001000);  send_char_without(0B01001100); //  33:40    -41:48//  // 4 // 5
          send_char_without(0B11010001);  send_char_without(0B00000110); //  49:56    -57:64//  // 6 // 7
          send_char_without(0B01100010);  send_char_without(0B01010011); //  65:72    -73:80//  // 8 // 9
          send_char_without(0B10010100);  send_char_without(0B10000001); //  81:88    -89:96//  // A // B
          send_char_without(0B11011000);  send_char_without(0B00000010); //  97:104   -105:112//// C // D
          send_char_without(0B01101110);  send_char_without(0B01000010); // 113:120   -121:128//// E // F 
          send_char_without(0B00000001);  send_char_without(0B00001100); // 120:136   -137:144//// G // H 
          send_char_without(0B00000000);  send_char_without(0B00000000); // 145:152   -153:160//// I // J
      delayMicroseconds(1);
      digitalWrite(VFD_ce, LOW); // 
      delayMicroseconds(1);
}
/*******************************************************************/
void loop() {
 //
 allOFF_LC75823(); // All off
 delay(1000);
 allON_LC75823(); // All on
 delay(3000);
 LC75823_Blaupunkt(); //Write Blaupunkt on the LCD
 delay(4000);
 LC75823_actionBass_1();
 delay(500);
 LC75823_actionBass_2();
 delay(500);
 LC75823_actionBass_3();
 delay(500);
 LC75823_actionBass_4();
 delay(500);
 LC75823_actionBass_5();
 delay(500);
 LC75823_actionBass_6();
 delay(500);
 LC75823_actionBass_7();
 delay(500);
 LC75823_numbers_0123();
 delay(1000);
 LC75823_numbers_45678();
 delay(1000);

}
