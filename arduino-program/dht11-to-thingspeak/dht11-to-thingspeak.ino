//AHMED REZA R - 17/419540/PTK/11650

#include <LiquidCrystal.h>
#include <DHT.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
DHT dht(2, DHT11);
String printTemp;
String dataFormat;
int dataHum;
int dataTemp;
  
void bacaSensor(){
  dataHum = dht.readHumidity();
  dataTemp = dht.readTemperature();
}

void sendToGateway(){
  lcd.setCursor(0,0);
  lcd.print("Sending...");
  delay(3000);
  lcd.clear();
  dataFormat = "-";
  dataFormat += dataTemp;
  dataFormat += ":";
  dataFormat += dataHum;
  dataFormat += "-";
  Serial.println(dataFormat);
}

void setup() {
  lcd.begin(16,2);
  Serial.begin(115200);
  lcd.setCursor(0,0);
  lcd.print("wait a sec..");
  delay(3000);
  lcd.clear();
  bacaSensor();
  delay(300);
  sendToGateway();
}

int counter,oa=0,oe=0;

void loop() {
  counter++;
  
  //string concatenation
  printTemp = "Suhu : ";
  printTemp +=dataTemp;
  printTemp +=" *C | Kelembapan : ";
  printTemp +=dataHum;
  printTemp +=" %";
  
  //atas
  if (counter<=printTemp.length()){
    lcd.setCursor(0,0);
    lcd.print(printTemp.substring(printTemp.length()-counter,printTemp.length()));
  } 
  if (counter > printTemp.length()) {
     lcd.setCursor(counter-printTemp.length(),0);
     lcd.print(printTemp.substring(0,printTemp.length()+oa--));
  }
  
  //bawah
  if (counter<=printTemp.length()){
    lcd.setCursor(16-counter,1);
    lcd.print(printTemp.substring(0,counter));
  } 
  if (counter >= 16) {
     lcd.setCursor(0,1);
     lcd.print(printTemp.substring(oe++,printTemp.length()));
  }
  
  delay(300);
  
  //reset ketika semua karakter sudah ditampilkan lalu ambil data sensor 
  if (counter>=16+printTemp.length()){
    counter = 0;
    oa = 0;
    oe = 0;
    lcd.clear();
    bacaSensor();
    delay(300);
    sendToGateway();
  }
  //Serial.println(counter);
  lcd.clear();


}
