int x;  //x-Position festlegen
int y;  //y-Position festlegen
String initText;  //Text anzeigen
String text;  //Text anzeigen
enum Direction {UP, DOWN, LEFT, RIGHT};  //mögliche Bewegungsrichtungen festlegen hoch, runter, links und rechts

void setup() {
    fullScreen(); //ganzen Bildschirm verwenden
    frameRate(60);
    x = displayWidth / 2;
    y = displayHeight / 2;
    initText = "Welcome to Squareland!"; //Text schreiben
}
void draw() {
    background(0, 0, 0); //Hintergrund schwarz füllen
    
    showText();
    
    rectMode(CENTER);  //Rechteck in der Mitte vom Bildschirm anzeigen
    fill(0, 100, 100);  //mit Farben füllen
    rect(x, y, displayWidth * 0.3, displayHeight * 0.3);  
    
    textAlign(CENTER);  //Text in der Mitte vom Rechteck anzeigen
    fill(255, 255, 255);  //Textfarbe
    text(text, x, y);
    
    showOverlay();
}

String showText() {
    if (keyPressed && key == ' ') {  //solange man die Leertaste drückt erscheint ein anderer Text
    return text = "This is some info about awesome Squareland!";
    } else {
        return text = initText;
    }
}

void showOverlay() {
    if (keyPressed && key == '+') {  //solange man die + Taste drückt erscheint ein zusätzliches Feld mit Text
        String moreInfo = "WOW, more info about awesome Squareland!";
        
        rectMode(CORNER);  //Position für das zusätzliche Rechteck
        fill(50, 0, 150);  //Farbe
        rect(x, y + 20, textWidth(moreInfo) + 100, displayHeight * 0.2);
        
        textAlign(CORNER);  //Text auf dem Rechteck
        fill(255, 255, 255);  //Textfarbe
        text(moreInfo, x + 40, y + displayHeight * 0.1);
    }
}

void keyPressed() {  //Festlegen was passiert, wenn man die Pfeiltasten drückt
    switch(keyCode) {
        case RIGHT :
            moveRect(Direction.RIGHT);
            break;
        case LEFT :
            moveRect(Direction.LEFT);
            break;
        case UP :
            moveRect(Direction.UP);
            break;
        case DOWN :
            moveRect(Direction.DOWN);
            break;  
        default :
        break;
    }
}

void moveRect(Direction dir) {  //festlegen wie weit das Element bewegt wird 
    switch(dir) {
        case UP:
            y -= 5;
            break;
        case DOWN:
            y += 5;
            break;
        case LEFT:
            x -= 5;
            break;
        case RIGHT:
            x += 5;
            break;
        default :    
        break;
    }
}
