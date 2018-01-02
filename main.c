// Written by, David Fentz
//
// This code is open source, dawg. 
// I know it looks like  a lot, but it should be managable. 
// I tried to organize it...


#include <Adafruit_NeoPixel.h>
#include <time.h>
#include <stdlib.h>

#define PIN1 10
#define PIN2 9
#define PIN3 6
#define NUM_LEDS 68
#define BRIGHTNESS 50 // only used in a few functions

Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(NUM_LEDS, PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(NUM_LEDS, PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(NUM_LEDS, PIN3, NEO_GRB + NEO_KHZ800);

// Function forward declerations
int random_number(int min_num, int max_num);
void domino(int toggle);
void push();
void set_all(int num, int r, int g, int b);
void barber();

void setup() {
    // setting a seed for the calls to rand()
    srand(time(NULL));

    // initiating all strips to blank
    strip1.begin();
    strip2.begin();
    strip3.begin();
    push();
}

// In this main loop, the single_wave animation serves to clear previous animations.
void loop() {
    //sparkle();
    single_wave();
    domino(0);
    single_wave();
    domino(1);
    barber();
}

//Kind of looks like a barber pole?
void barber(){
    for(int j=0;j<30;j++){
        int count=0;
        for(int i=0;i<NUM_LEDS;i++){
            if(count==0 || count==1){
                set_all(i,20,0,0);
            } else{
                set_all(i,10,10,10);
            }
            count++;
            count=count%4;
        }
        push();
        delay(100);

        for(int i=0;i<NUM_LEDS;i++){
            if(count==1 || count==2){
                set_all(i,20,0,0);
            } else{
                set_all(i,10,10,10);
            }
            count++;
            count=count%4;
        }
        push();
        delay(100);

        for(int i=0;i<NUM_LEDS;i++){
            if(count==2 || count==3){
                set_all(i,20,0,0);
            } else{
                set_all(i,10,10,10);
            }
            count++;
            count=count%4;
        }
        push();
        delay(100);

        for(int i=0;i<NUM_LEDS;i++){
            if(count==0 || count==3){
                set_all(i,20,0,0);
            } else{
                set_all(i,10,10,10);
            }
            count++;
            count=count%4;
        }
        push();
        delay(100);
    }

}

// creates a sparkling effect (which I think is visually un-nerving). And thus, it is commented out of the main loop.
void sparkle(){
    int pix;
    for(int i=0;i<100;i++){
        pix=random_number(0,255);
        strip1.setPixelColor(pix,250,250,250);
        strip1.show();
        delay(10);
        strip1.setPixelColor(pix,0,0,0);
        strip1.show();
        //delay(100);

        pix=random_number(0,255);
        strip2.setPixelColor(pix,250,250,250);
        strip2.show();
        delay(10);
        strip2.setPixelColor(pix,0,0,0);
        strip2.show();
        //delay(100);

        pix=random_number(0,255);
        strip3.setPixelColor(pix,250,250,250);
        strip3.show();
        delay(10);
        strip3.setPixelColor(pix,0,0,0);
        strip3.show();
        //delay(100);
    }
}

// sends a single 3-pixel-wide wave through the strips simultaneously; from bottom to top.
void single_wave(){
    for(int i=0;i<NUM_LEDS+3;i++){
        set_all(i, BRIGHTNESS, BRIGHTNESS, BRIGHTNESS);

        if(i>0){
            set_all(i-1, BRIGHTNESS/2, BRIGHTNESS/2, BRIGHTNESS/2);
        }
        if(i>1){
            set_all(i-2, BRIGHTNESS/6, BRIGHTNESS/6, BRIGHTNESS/6);
        }

        push();
        delay(50);

        set_all(i,0,0,0);

        if(i>0){
            set_all(i-1,0,0,0);
        }
        if(i>1){
            set_all(i-2,0,0,0);
        }

        push();
    }
    delay(1000);
}

// The parameter 'toggle' serves to allow the domino animation to function in a 'white mode.'
void domino(int toggle){
    int w=toggle;

    for(int j=0;j<10;j++){
        int r;
        int g;
        int b;

        // THIS PART SETS THE COLOR FOR EACH DOMINO ANIMATION
        if(w==1){
            r= random_number(0,100);
            g= random_number(0,100);
            b= random_number(0,100);
        }else {
            r= 50;
            g= 50;
            b= 50;
        }

        // THIS IS REALLY JUST THE DISPLAY ANIMATION 
        for(int i=0;i<68;i=i+4){
            set_all(i+3,0,0,0);
            set_all(i,r,g,b);
            push();
            delay(10);

            set_all(i+1,r,g,b);
            set_all(i,0,0,0);
            push();
            delay(10);

            set_all(i+2,r,g,b);
            set_all(i+1,0,0,0);
            push();
            delay(10);

            set_all(i+3,r,g,b);
            set_all(i+2,0,0,0);
            push();
            delay(10);
        }
    }
}

// this function is as simple as it looks, but it saves a few lines. 
// It sets the same pixel on each strip to the same value. This happens frequently.
void set_all(int num, int r, int g, int b){
    strip1.setPixelColor(num,r,g,b);
    strip2.setPixelColor(num,r,g,b);
    strip3.setPixelColor(num,r,g,b);
}

// pushes current data states out to all strips.
void push(){
    strip1.show();
    strip2.show();
    strip3.show();
}

// generates random numbers for other functions
int random_number(int min_num, int max_num){
    int result = 0;
    result = (rand() % ((max_num+1) - min_num)) + min_num;
    return result;
}
