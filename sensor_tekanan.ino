/*Create By Angga Saputa & Delfita Sari
   * COPY RIGHT @ANGRANAU
   * MOMMY CARE
   * Agustus 2019
   * Skripsi 2019
   */
//   eeeee
#include <Wire.h>
#include <Adafruit_MLX90614.h> //librari suhu
#define USE_ARDUINO_INTERRUPTS true
#include <PulseSensorPlayground.h>// librari jantung
#include <LiquidCrystal.h> // includes the LiquidCrystal Library 
LiquidCrystal lcd(1, 2, 4, 5, 6, 7);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
#include <SoftwareSerial.h>
SoftwareSerial s(11,12);
const int PulseWire = A0;
int Threshold = 550;
PulseSensorPlayground pulseSensor;
float sensor = A1;
float pressure;
float myBPM;

float BPM,Sistolik,Diastolik,Suhu;

//float mlx.readAmbientTempC();


void setup() {
 lcd.begin(16,2);
 mlx.begin();
 s.begin(9600);  
}

void loop(){

  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("SELAMAT DATANG!!");
  lcd.setCursor(0,1);
  lcd.print("DI MOMMY CARE!!! ");
  delay(3000);
  lcd.clear();
  delay(1000);
  jantung (); 
  }

  void tensi(){
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Cek Tensi");
  lcd.setCursor(3,1);
  lcd.print("Darah?");
  lcd.clear();
  delay(3500);
  pinMode(9,OUTPUT);
  pinMode(3,OUTPUT);
//  digitalWrite(3,LOW);
  digitalWrite(9,LOW);
  delay(5000);//tempat seting lama pompa
  digitalWrite(9,HIGH);
//  digitalWrite(3,HIGH);
  float pressure = (50000/1024) * analogRead(sensor) ;
  delay(1000);
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Sistolik :");
  lcd.setCursor(3,1);
  lcd.print(pressure/1000*10);
  lcd.setCursor(7,1);
  lcd.print(" Mmhg");
  delay(2000);
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Diastolik :");
  lcd.setCursor(3,1);
  lcd.print(pressure/1000*10-45);
  lcd.setCursor(7,1);
  lcd.print(" Mmhg");
  delay(1000);
  lcd.clear();
//  digitalWrite(9,HIGH);
//  delay(1000);
//  digitalWrite(3,HIGH);
//  delay(1000);
   
  
  Sistolik=pressure/1000*10;
  Diastolik=pressure/1000*10-45;
//komunikasi dengan node mcu
//Serial.println("Kirim data Sistolik");
//Serial.println(pressure/1000*10);
// s.write(Sistolik);
// delay(1000);
 //komunikasi dengan node mcu
//Serial.println("Kirim data Diastolik");
//Serial.println(pressure/1000*10-45);
// s.write(Distolik);
// delay(1000);
    }
void jantung (){

  pulseSensor.analogInput(PulseWire);
  pulseSensor.setThreshold(Threshold);
  if (pulseSensor.begin()) {
    lcd.setCursor(3,0);
    lcd.print("Cek Detak");
    lcd.setCursor(3,1);
    lcd.print("Jantung??");
    delay(3000);
    lcd.clear();
   
  }
  int myBPM = pulseSensor.getBeatsPerMinute();
  if (pulseSensor.sawStartOfBeat()) { 
    lcd.setCursor(6,0);
    lcd.print(myBPM-150);
    lcd.setCursor(6,1);
    lcd.print("BPM");
    delay(1000);
    lcd.clear();
    BPM=myBPM-150;

    tensi();
    suhu();
    akhir();
    kirimdata();
    
   
    }else {
    lcd.setCursor(0,0);
    lcd.print("Silahkan Tempel!");
    lcd.setCursor(0,1);
    lcd.print("Sensor jantung!!");
    delay(2000);
    lcd.clear();
    
      } 
    //komunikasi dengan node mcu
//Serial.println("Kirim data Bpm");
//Serial.println(myBPM-150);
//    s.write(BPM);
//    delay(1000);
    }

 void suhu(){
    lcd.clear();
    delay(1000);
    lcd.setCursor(3,0);
    lcd.print("Cek Suhu");
    lcd.setCursor(3,1);
    lcd.print("Badan??");
    delay(3000);
    lcd.clear();
    lcd.setCursor(4,0);
    lcd.print(mlx.readAmbientTempC());
    lcd.setCursor(3,1);
    lcd.print("Celcius");
    delay(1000);
    lcd.clear();
    delay(5000);

  Suhu=mlx.readAmbientTempC();
  //komunikasi dengan node mcu
//Serial.println("Kirim data Suhu");
//Serial.println(mlx.readAmbientTempC());
//    s.write(mlx.readAmbientTempC());
//    delay(1000);
      }

 void akhir(){
  lcd.setCursor(1,0);
  lcd.print("TUGAS AKHIR2019");
  lcd.setCursor(3,1);
  lcd.print("FIK SI UBL");
  lcd.setCursor(3,1);
  delay(1000);
  lcd.clear();

  lcd.setCursor(2,0);
  lcd.print("ANGGA SAPUTRA");
  lcd.setCursor(2,1);
  lcd.print("DELFITA SARI");
  lcd.setCursor(3,1);
  delay(1000);
  lcd.clear();
  delay(3000);
  }


  
void kirimdata (){

jantung;
suhu;
tensi;

 lcd.setCursor(1,0);
  lcd.print("Please Wait!!!");
  lcd.setCursor(1,1);
  lcd.print("..............");
  delay(3000);
  lcd.clear();
//Serial.begin(9600);
  
//komunikasi dengan node mcu
//Serial.println("Kirim data Bpm");
//Serial.println(BPM);
    s.write(BPM);
    delay(1000);
//  komunikasi dengan node mcu
//Serial.println("Kirim data Sistolik");
//Serial.println(Sistolik);
 s.write(Sistolik);
 delay(1000);
// //komunikasi dengan node mcu
Serial.println("Kirim data Diastolik");
//Serial.println(Diastolik);
 s.write(Diastolik);
 delay(1000);
// //komunikasi dengan node mcu
// Serial.println("Kirim data Suhu");
// Serial.println(mlx.readAmbientTempC());
    s.write(mlx.readAmbientTempC());
    delay(1000);
  }

  /*Create By Angga Saputa & Delfita Sari
   * COPY RIGHT @ANGRANAU
   * /
   */


