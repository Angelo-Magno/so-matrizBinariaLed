#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <math.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

/*#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2*/

//variáveis globais
uint8_t bin[32]; 
float novoValor = 0;

void setup() {
  
//-----------------------------------------------------------------------------------
//variáveis 
  int aux = 0;
  int32_t num = 91; 
     
//conversão de decimal para binario 
  for (aux = 31; aux >= 0; aux--){

    if (num % 2 == 0){
      if(bin[aux]!=0){  //Test para verificar se já foi escrito
       bin[aux] = 0;
      }
    } else{
          if(bin[aux]!=1){ //Test para verificar se já foi escrito
              bin[aux] = 1;
          }
      }
    num = num / 2;

   }

//lê o vetor e converte o binario lido para decimal
    for (aux = 31; aux >= 0; aux--) {
    
      if (bin[aux] == 1) {
        novoValor = novoValor + pow(2,31- aux);
      }
    }     
//-----------------------------------------------------------------------------------
    

//Inicialização do display 128x64 com o logo da Adafruit 0x3C
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
  display.display();
  delay(1000);
  display.clearDisplay();


}

void loop() {
  
  //exibe na tela um numero em binario na horizontal representando "1" como pixel aceso 
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Vetor binario:");
  drawBinario();
  display.display();
  delay(4000);
  display.clearDisplay();


 //exibe na tela o numero em decimal 
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Numero decimal:");
  display.setCursor(12, 12);
  display.print(novoValor);
  display.display();
  delay(2500);
  display.clearDisplay();

}


//Desenha o numero binario pixel a pixel
//A partir do primeiro pixel da ultima coluna no sentido vertical de cima para baixo 
void drawBinario(void) {
    int16_t y, x=0,z=127;
    for (y = 31; y >= 0; y--){
      if(bin[y]==1){
        display.drawPixel(z, x, WHITE);
        display.display();
        delay(1);
       }
       x++;
    }
}
