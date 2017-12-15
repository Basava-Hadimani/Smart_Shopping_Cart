#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
int i;
int m=0;
char d='c';
byteleda=A2;
byteledb=A3;
byte DOUT=A0;
byte gain=1;
byte PD_SCK=A1;
float SCALE=2280.f/5.26;
LiquidCrystalLCD(12, 11, 5, 4, 3, 2);
SoftwareSerialXBee(8, 9); // RX, TX
char c='e';
struct barcode{
intser;
  String name;
int price;
float weight;
int q;
} product[5]={{89,"wheel",6,135,2},{75,"Otorex",68,37.7,2},{95,"Surfexcel_small",15,149,2},{99,"SHIKAKAI",16,75,3},{91,"bourbon",10,63.5,2}};


voidgetit(int t){
int i;
for(i=0;i<5;i++){
if(t==product[i].ser){
product[i].q=product[i].q-1;
LCD.clear();
LCD.print(product[i].name);
    }
    }
    }

voidshata(int t){
if(t>=5){
LCD.clear();
LCD.print("Error");
delay(500);
  }
else {
LCD.clear();
LCD.print(product[t].name);
      //delay(2000);
product[t].q=product[t].q-1;
if( product[t].q==0){
digitalWrite(leda, HIGH);   // turn the LED on (HIGH is the voltage level)
delay(3000);               // wait for a second
digitalWrite(leda, LOW);    // turn the LED off by making the voltage LOW
  //delay(1000);        

      }
else{
digitalWrite(ledb, HIGH);   // turn the LED on (HIGH is the voltage level)
delay(2000);               // wait for a second
digitalWrite(ledb, LOW);    // turn the LED off by making the voltage LOW
  //delay(1000);        
      }

  }

}

inttotprice=0;
floatwgt=0.0;

intget_weight(int t){
int i;
for(i=0;i<4;i++){
if(t==product[i].ser){
return i;
    }
    }
}

booleanis_ready() {
	return (digitalRead(DOUT) == LOW);
}

long tread() {
	// wait for the chip to become ready
	while (!is_ready()){
         //Serial.print(".");
       };

	byte data[3];

	// pulse the clock pin 24 times to read the data
	for (byte j = 3; j--;) {
		for (char i = 8; i--;) {
			digitalWrite(PD_SCK, HIGH);
			bitWrite(data[j], i, digitalRead(DOUT));
			digitalWrite(PD_SCK, LOW);
		}
	}

	// set the channel and the gain factor for the next reading using the clock pin
	
for (int i = 0; i < gain; i++) {
		digitalWrite(PD_SCK, HIGH);
		digitalWrite(PD_SCK, LOW);
	}

	data[2] ^= 0x80;

	return ((uint32_t) data[2] << 16) | ((uint32_t) data[1] << 8) | (uint32_t) data[0];
}

longread_average(byte times) {
	long sum = 0;
	for (byte i = 0; i < times; i++) {
		sum=sum+( tread());
	}
	return sum / times;
}
long OFFSET=0;
doubleget_value(byte times) {
	return (read_average(times)-OFFSET);
}

floatget_units(byte times) {
	returnget_value(times)*1.07 / SCALE;
}
float off;

void setup() {
pinMode(leda, OUTPUT);
pinMode(ledb, OUTPUT);
pinMode(PD_SCK, OUTPUT);
pinMode(DOUT, INPUT);
digitalWrite(PD_SCK, LOW);  
LCD.begin(16, 2);
Serial.begin(9600);
XBee.begin(9600);
off=(get_units(10));
LCD.print("hello, world!");
delay(1000);
}


void loop() {
if(Serial.available())
 {
LCD.clear();
char g=Serial.read();
   d=g;
XBee.write(d);

 }

if (XBee.available())
  { 
LCD.clear();
  c=XBee.read();
if(c=='v')
     {     
Serial.println("Cart No: A001 Finished Shoping");
while(1){
if (XBee.available()){
        c=XBee.read();
if(c=='x')
        {
break;
        }
int i=c-'0';
Serial.print(product[i].name);
Serial.print("     Rs.");
Serial.print(product[i].price);
Serial.println("/-");
m=product[i].price+m;
      }
    }
Serial.print("Total price: Rs.");
Serial.print(m);
Serial.println(" only");

   }
int i=c-'0';
convert(i);
Serial.println(c);

  }

int t=0,a=0;
  String ab;
floatval=abs(get_units(10)-off);
LCD.clear();
if(abs(val-wgt)>7){
delay(1000);
float temp=abs(get_units(5)-off);
if((temp-wgt)>7){  
temp=temp-wgt;
LCD.clear();
LCD.print("Item added");
delay(500);
LCD.clear();
LCD.print("processing...");

for(a=0;a<=5;a++){
float btw=product[a].weight;
if(abs(btw-temp)<9){
LCD.clear();
LCD.print("match found!");
LCD.setCursor(0,1);
LCD.print(product[a].name);

 }
 }

delay(500);
wgt+=temp;
totprice+=product[a].price;

delay(500);

  }

else if((temp-wgt)<-5){
temp=abs(temp-wgt);
LCD.clear();
LCD.print("Item removed");
delay(1000);    
for(a=0;a<=5;a++){
float btw=product[a].weight;
if(abs(btw-temp)<5){
LCD.clear();
LCD.print(product[a].name);
LCD.setCursor(0,1);
product[a].q=product[a].q-1;
LCD.print(product[a].q);

             }
           }    
wgt-=temp;

     }
   }
}