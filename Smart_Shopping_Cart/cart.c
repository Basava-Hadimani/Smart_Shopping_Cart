#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
charinData[20]; 
charinChar; 
byte index = 0; 
byteledb = A2;
byteleda = A3;
byteledc=A4;
intca[20];
int c=0;
int i;
charqw='v';
charzx='i';
LiquidCrystalLCD(12, 11, 5, 4, 3, 2);
SoftwareSerialXBee(8,9); // RX, TX
byte DOUT=A0;
byte gain=1;
byte PD_SCK=A1;
float SCALE=2280.f/5.26;
int td=90;
struct barcode{
intser;
  String name;
int price;
float weight;
inted;
} product[5]={{89,"wheel",6,137,120},{75,"Otorex",68,37.7,90},{95,"Surfexcel_small",15,155,200},{99,"SHIKAKAI",16,73,200},{91,"Bourbon",10,63.5,200}};

inttotprice=0;
floatwgt=0.0;

intget_weight(int t){
int i;
for(i=0;i<5;i++){
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
	returnget_value(times)*1.37 / SCALE;
}
float off;
void setup()
{
pinMode(leda, OUTPUT);     
pinMode(ledb, OUTPUT); 
pinMode(ledc, OUTPUT);    

  // put your setup code here, to run once:
pinMode(PD_SCK, OUTPUT);
pinMode(DOUT, INPUT);
digitalWrite(PD_SCK, LOW);
Serial.begin(9600);
XBee.begin(9600);
LCD.begin(16,2);
off=(get_units(10));
LCD.print("started");
delay(1000);
  }

void loop()
{
digitalWrite(leda, LOW);   // 
digitalWrite(ledb, LOW);   // 
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
LCD.print("scan now");
int y=0;
while(1){

      t=0;
while(1){
if(Serial.available()>0){
ab=Serial.readString();
    a=ab.toInt();
break;
    }

  }
int p=get_weight(a);
float btw=product[p].weight;
if(abs(btw-temp)<10){
LCD.clear();
LCD.print("matched");
digitalWrite(leda, LOW);   
digitalWrite(ledb, LOW);   
LCD.setCursor(0,1);
LCD.print(product[p].name);
if((product[p].ed-td)<=0){
LCD.clear();
LCD.print("ExpiryDateOver");
    }
digitalWrite(ledc, HIGH);
delay(1000);
digitalWrite(ledc, LOW);
ca[c]=p;
    c=c+1;
zx=p+'0';
XBee.write(zx);
delay(500);
wgt+=temp;
totprice+=product[p].price;

delay(500);
break;
  }
else{
    y=y+1;
if(y>1){
digitalWrite(leda, HIGH);   // 
    }
else{
digitalWrite(ledb, HIGH);   // 
    }
LCD.clear();
LCD.print("Scan again");
LCD.setCursor(0,1);
LCD.print(temp);
  }
}
}

else if((temp-wgt)<-5){
temp=abs(temp-wgt);
LCD.clear();
LCD.print("Item removed");
delay(1000);
LCD.clear();
LCD.print("scan now");
int y=0;
while(1){

      t=0;
while(1){
if(Serial.available()>0){
ab=Serial.readString();
    a=ab.toInt();
break;
    }

  }
int p=get_weight(a);
float btw=product[p].weight;
if(abs(btw-temp)<5){
LCD.clear();
LCD.print("matched");
intgd=0;
digitalWrite(ledc, HIGH);
delay(1000);
digitalWrite(ledc, LOW);
while(gd<c){
if(ca[gd]==p){
ca[gd]=9;
gd=gd+1;  
    }
    }
LCD.setCursor(0,1);
LCD.print(product[p].name);
delay(500);
wgt-=temp;
totprice-=product[p].price;

delay(500);
break;
  }
else{
     y=y+1;
if(y>1){
digitalWrite(leda, HIGH);   // 
    }
else{
digitalWrite(ledb, HIGH);   // 
    }
LCD.clear();
LCD.print("Scan again");
LCD.setCursor(0,1);
LCD.print(temp);
  }
}
}
  }
LCD.clear();
LCD.print("Crtwgt");
LCD.setCursor(9,0);
LCD.print(wgt);
LCD.setCursor(0,1);
LCD.print("crtpri");
LCD.setCursor(9,1);
LCD.print(totprice);
delay(1000);
if(Serial.available()>0)
{
    String m=Serial.readString();
int f=m.toInt();
if(f==93){
LCD.clear();
LCD.print("Final Price");
LCD.setCursor(0,1);
LCD.print(totprice);
int k=0;
XBee.write(qw);
while(k<c){
Serial.println(ca[k]);
      k=k+1;
qw=ca[k]+'0';
XBee.write(qw);
delay(200);
      }
qw='x';
XBee.write(qw);
while(1){
if(XBee.available()){
char f=XBee.read();
if(f=='z'){
while(1);
       }
       } 

floatval=abs(get_units(10)-off);
if(abs(val-wgt)>7){
delay(1000);
float temp=abs(get_units(5)-off);
if((temp-wgt)>7){
digitalWrite(leda, HIGH);   // 
digitalWrite(ledb, HIGH); 
while(1){
if(XBee.available()){
char f=XBee.read();
if(f=='z'){
digitalWrite(leda,LOW);   // 
digitalWrite(ledb, LOW);
while(1);
       }
       } 

      };

  } 
  }     
      };
    }
else
    {
LCD.clear();
LCD.print("Put the item");
Serial.println("Weght");
Serial.println(wgt);

while(1){
floatval=abs(get_units(10)-off);
if(abs(val-wgt)>7){
delay(1000);
float temp=abs(get_units(5)-off);
Serial.println(temp);
if((temp-wgt)>5){

temp=temp-wgt;
    }
intasd=get_weight(f);
float btw=product[asd].weight;
if(abs(btw-temp)<5){
LCD.clear();
LCD.print("Item matched");
if((product[asd].ed-td)<=0){
LCD.clear();
LCD.print("ExpiryDateOver");
    }
ca[c]=asd;
    c=c+1;
digitalWrite(ledb, LOW);
digitalWrite(ledc, HIGH);
delay(1000);
digitalWrite(ledc, LOW);
zx=asd+'0';
XBee.write(zx);

delay(1000);
wgt+=temp;
totprice+=product[asd].price;
break;
}
else{
digitalWrite(ledb, HIGH);
Serial.println(val);
Serial.println(temp);
Serial.println(btw);
LCD.clear();
LCD.print("Error!!");
              }
            }
	  }
       }
    }
}
