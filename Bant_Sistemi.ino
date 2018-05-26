#include<Servo.h>
int kirmizi = 14; // RGB LED
int mavi = 15; // RGB LED
char deger;
char col;
Servo servo_on;
Servo servo_arka;
Servo servo_el;
Servo servo_alt;
int S2 = 3; // TCS3200 bağlantı
int S3 = 4;// TCS3200 bağlantı
int outpin = 2;// TCS3200 bağlantı
int r ; // kirmizi renk
int g ;// yesil renk
int b ;// mavi renk
int w ;// beyaz renk
unsigned int plusewidth;
#define Motor_enable  11 // motor sürücü hız kontrolü
#define Motor_ileri 12// motor sürücü ileri
int val_1; // IR Sensör-1
int val_2;// IR Sensör-2
int d_alt = 8;
int d_ust = 7;
void setup() {
  pinMode(kirmizi, OUTPUT);
  pinMode(mavi, OUTPUT);
  Serial.begin(9600);
  pinMode(d_alt, INPUT);
  pinMode(d_ust, INPUT);
  pinMode(Motor_enable, OUTPUT);
  pinMode(Motor_ileri, OUTPUT);    // MOTOR  çıkış pinleri
  pinMode(S3, OUTPUT);            // TCS3200  sensör çikis pinleri
  pinMode(S2, OUTPUT);
  pinMode(outpin, INPUT);
  servo_arka.attach(5);
  servo_on.attach(10);
  servo_el.attach(9);
  servo_alt.attach(6);
}

void loop() {
  /*
    char col = renk_oku();
    Serial.print("R : ");
    Serial.print(r);
    Serial.print(" G : ");
    Serial.print(g);
    Serial.print(" B : ");
    Serial.print(b);
    Serial.print( " W : ");
    Serial.print(w);
    Serial.println("");
  */

  basla_motor();
  int val_2 = digitalRead(d_ust);
  int val_1 = digitalRead(d_alt);
  Serial.println(val_1);
  Serial.println(val_2);
  if (val_2 == 0 && val_1 == 0 ) {
    deger = 'b'; // dur  büyük
  }
  else if (val_1 == 0 && val_2 == 1 ) {
    deger = 'd'; // dur
  }
  else if (val_1 == 1) {
    deger = 'e'; //devam et
  }
  switch (deger) {
    case 'd': // küçük için
      delay(150);
      dur_motor();
      delay(200);
      col = renk_oku();
      delay(200);
      if (col == 'r') {
        digitalWrite(kirmizi, HIGH);
        en_sola_birak();
        digitalWrite(kirmizi, LOW);
      }

      else if (col == 'b') {
        digitalWrite(mavi, HIGH);
        en_saga_birak();
        digitalWrite(mavi, LOW);
      }
      else delay(5000);
      Serial.println("kol çalismaz");
      break;
    case 'b': // büyük için
      delay(100);
      dur_motor();
      delay(10);
      col = renk_oku();
      delay(10);
      if (col == 'r') {
        digitalWrite(kirmizi, HIGH);
        sola_birak();
        digitalWrite(kirmizi, LOW);
      } else if (col == 'b') {
        digitalWrite(mavi, HIGH);
        saga_birak();

        digitalWrite(mavi, LOW);
      }
      else delay(5000); Serial.println("kol çalismaz");
    case 'e': basla_motor();
      break;
  }
}
void al() {
  servo_arka.write(25);//60-25
  ac();
  ileri();
  kapat();
  geri();
}
void saga_birak() {
  servo_arka.write(45);//60-25
  ac();
  ileri();
  kapat();
  geri();
  saga();
  en_ileri();
  ac();
  en_geri();
  sagdan_baslangica();
}
void sola_birak() {
  servo_arka.write(45);//60-25
  ac();
  ileri();
  kapat();
  geri();
  sola();
  en_ileri();
  ac();
  en_geri();
  soldan_baslangica();
}
void en_sola_birak() {
  al();
  en_sola();
  en_ileri();
  ac();
  en_geri();
  en_soldan_baslangica();
}

void en_saga_birak() {
  al();
  en_saga();
  en_ileri();
  ac();
  en_geri();
  en_sagdan_baslangica();
}
void geri() {
  for (int i = 140; i > 65; i--)
  { // geri
    servo_on.write(i); delay(7);
  }
}
void ileri() {
  for (int i = 65; i < 140; i++)
  { //ileri
    servo_on.write(i); delay(7);
  }
}
void en_ileri() {
  for (int i = 70; i < 160; i++)
  { //ileri
    servo_on.write(i); delay(7);
  }
}
void en_geri() {
  for (int i = 160; i > 70; i--)
  { // geri
    servo_on.write(i); delay(7);
  }
}
void kapat() {
  for (int i = 85; i < 115; i++)
  { // kapa
    servo_el.write(i); delay(7);
  }
}
void ac() {
  for (int i = 115; i > 85; i--)
  { // ac
    servo_el.write(i); delay(7);
  }
}
void sola() {
  for (int i = 87; i < 120; i++)
  { //sola
    servo_alt.write(i); delay(7);
  }
}
void soldan_baslangica() {
  for (int i = 120; i > 87; i--)
  { //soldan saga
    servo_alt.write(i); delay(7);
  }
}
void en_sola() {
  for (int i = 87; i < 180; i++)
  { //en_sola
    servo_alt.write(i); delay(7);
  }
}
void en_soldan_baslangica() {
  for (int i = 180; i > 87; i--)
  { //soldan saga
    servo_alt.write(i); delay(7);
  }
}
void saga() {
  for (int i = 87; i > 30; i--)
  { //saga
    servo_alt.write(i); delay(7);
  }
}
void sagdan_baslangica() {
  for (int i = 30; i < 87; i++)
  { //sagdan baslangica
    servo_alt.write(i); delay(7);
  }
}
void en_saga() {
  for (int i = 87; i > 0; i--)
  { //en_saga
    servo_alt.write(i); delay(7);
  }
}
void en_sagdan_baslangica() {
  for (int i = 0; i < 87; i++)
  { //sagdan baslangica
    servo_alt.write(i); delay(7);
  }
}
/* RENK ALGILAMA KODLARI */
char renk_oku() {
  char color;
  // kirimizi renk için okuma islemi
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  r = pulseIn(outpin, LOW);
  //  r = plusewidth / 400. - 1;
  //  r = (255 - r);
  /*----------------------*/

  //yesil renk için okuma islemi
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  g = pulseIn(outpin, LOW);
  // g = plusewidth / 400. - 1;
  //    g = (255 - g);

  /*----------------------*/

  //mavi renk için okuma islemi
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  b = pulseIn(outpin, LOW);
  //   b = plusewidth / 400. - 1;
  //  b = (255 - b);

  /*----------------------*/

  //beyaz renk için okuma islemi
  digitalWrite(S2, HIGH);
  digitalWrite(S3, LOW);
  w = pulseIn(outpin, LOW);
  //
  //    w = (255 - w);


  if ( r < g && r > b && r > w && g > b && g > w && b > w ) {
    Serial.println("*! Red *!");
    color = 'r';
    //R : 502 G : 596 B : 464 W : 176
    //R : 500 G : 612 B : 459 W : 182
    //R : 514 G : 599 B : 468 W : 180

  }

  /* else if ( r > g && r > b && r > w  && g > w && b > w ) {
     Serial.println("*! GREEN *!");
     color = 'g';

    }*/

  else if (r > g  && r > b && g > b && g > w && b > w ) {
    Serial.println("*! Blue *!");
    color = 'b';
    // 610 G : 583 B : 399 W : 177
    //R : 625 G : 580 B : 395 W : 175
    //R : 617 G : 580 B : 387 W : 169
  }
  else {
    Serial.println("!----------------------OKUNAMADI----------------------!");
  }
  return color;
}

/* MOTOR SÜRÜCÜ KODLARI*/
void basla_motor() {
  digitalWrite(Motor_ileri, HIGH);
  analogWrite(Motor_enable, 100);
}

void dur_motor() {
  digitalWrite(Motor_ileri, LOW);
  analogWrite(Motor_enable, 0);
}
