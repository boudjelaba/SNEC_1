# SNEC1

https://www.youtube.com/watch?v=n5gor3Bdmmk#t=795s

---

https://www.framboise314.fr/wp-content/uploads/2017/11/03_1_1_InstallationQt_LED_v2.pdf

https://www.electronicsforu.com/electronics-projects/setting-qt-software-on-raspberry-pi

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

