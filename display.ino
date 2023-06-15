#include <Arduino_GFX_Library.h>


Arduino_DataBus *bus = create_default_Arduino_DataBus();
Arduino_GFX *gfx = new Arduino_GC9A01(bus, 7 /* RST */, 0 /* rotation */, true /* IPS */);

char buf_o[5];
char buf_u[5];
int up_pos_x  = 70;
int up_pos_y  = 70;
int do_pos_x  = 70;
int do_pos_y  = 140;

void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  gfx->begin();
  gfx->fillScreen(PINK);
  gfx->setCursor(30, 130);
  //gfx->setFont(u8g2_font_helvB24_te);
  gfx->setTextSize(3);
  gfx->setTextColor(WHITE, PINK);
  gfx->println("Hello World!");
  delay(5000);
  gfx->fillScreen(PINK);
}

void loop() {
  // put your main code here, to run repeatedly:
  sprintf(buf_o, "%-10s", "Wert"); 
  gfx->setCursor(up_pos_x, up_pos_y);
  gfx->print(buf_o);
  sprintf(buf_u, "%-10d", analogRead(A0));  
  gfx->setCursor(do_pos_x, do_pos_y);
  gfx->print(buf_u);
}
