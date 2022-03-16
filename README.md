# SNEC1

https://www.youtube.com/watch?v=n5gor3Bdmmk#t=795s

---

https://circuitdigest.com/microcontroller-projects/arduino-xbee-module-interfacing-tutorial

https://www.instructables.com/How-to-Use-XBee-Modules-As-Transmitter-Receiver-Ar/

---

```cpp
#include <SD.h>
#include <SPI.h>

File myFile;

int pinCS = 10; // Pin 53 on Arduino Mega

void setup() {
    
  Serial.begin(9600);
  pinMode(pinCS, OUTPUT);
  
  // Initialisation carte SD
  if (SD.begin())
  {
    Serial.println("Carte SD est prète à être utilisée.");
  } else
  {
    Serial.println("Echec de l'initailisation de la carte SD");
    return;
  }
  
  // Création/Ouverture du fichier 
  myFile = SD.open("Test.txt", FILE_WRITE);
  
  // Si le fichier est bien ouvert, on écrit dans le fichier :
  if (myFile) {
    Serial.println("Ecriture dans le fichier ...");
    // Ecriture dans le fichier
    myFile.println("Texte de test 1, 2 ,3...");
    myFile.close(); // Ferméture du fichier
    Serial.println("Terminé.");
  }
  // Si le fichier ne peut pas être ouvert, afficher erreur :
  else {
    Serial.println("erreur d'ouverture du fichier Test.txt");
  }

  // Lecture du fichier
  myFile = SD.open("Test.txt");
  if (myFile) {
    Serial.println("Lecture :");
    // Lire tout le fichier
    while (myFile.available()) {
      Serial.write(myFile.read());
   }
    myFile.close();
  }
  else {
    Serial.println("Erreur d'ouverture Test.txt");
  }
  
}
void loop() {
  // empty
}

---

## Afficheur

```cpp
char A=0, B=1, C=2, D=3, E=4, F=5, G=6;

void setup()
{
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);    
}
 
void loop ()
{
  chiffre(0b0111111);//0
  delay(1000);
  chiffre(0b0000110);//1
  delay(1000);
  chiffre(0b1011011);//2
  delay(1000);
  chiffre(0b1001111);//3
  delay(1000);
  chiffre(0b1100110);//4
  delay(1000);
  chiffre(0b1101101);//5
  delay(1000);
  chiffre(0b1111101);//6
  delay(1000);
  chiffre(0b0000111);//7
  delay(1000);
  chiffre(0b1111111);//8
  delay(1000);
  chiffre(0b1101111);//9
  delay(1000);
}
            
void chiffre(int num)
{
  digitalWrite(A, num & 0b0000001);
  digitalWrite(B, num & 0b0000010);
  digitalWrite(C, num & 0b0000100);
  digitalWrite(D, num & 0b0001000);
  digitalWrite(E, num & 0b0010000);
  digitalWrite(F, num & 0b0100000);
  digitalWrite(G, num & 0b1000000);
}

