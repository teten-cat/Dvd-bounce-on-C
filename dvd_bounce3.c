#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define COOLDOWN_MICROSECOND 500000

char border = '#';
int w = 40;
int h = 10;

int id = 7;

void pprint_char(char c, int n){
    int i;
    for(i = 0; i < n; i++){
        printf("%c",c);
    }
}

void line(){
    printf("%c",border);
    pprint_char(' ',w-2);
    printf("%c\n",border);
}

void line_edge(){
    pprint_char(border,w);
    printf("\n");
}

void DVD_line(int xPos, int yPos){
    printf("%c",border);
    pprint_char(' ',xPos-3);
    printf("\033[1;38;5;%dmDVD\033[0;38;5;7m",id);
    pprint_char(' ',w-xPos-2);
    printf("%c\n",border);
}

int Shuffle_colorid(){
    return (rand() % 256);
}

int main() {
    srand(time(NULL));

    int i = 0;

    int posX = 3;
    int posY = 2;

    int velX = 1;
    int velY = 1;

    printf("\033[H\033[J"); // clears screen
    while(1){
        printf("\033[H\033[J"); // clears screen
        // Top line
        line_edge();

        // Empty lines until DVD
        for(int i = 0; i < posY-2; i++) {
            line();
        }

        DVD_line(posX,posY);

        for(int i = 0; i < h-posY-1; i++) {
            line();
        }

        // Bottom line
        line_edge();

        // Update position
        if(posX + velX < 3 || posX + velX > w-2){
            id = Shuffle_colorid();
            velX *= -1;
        }
        if(posY + velY < 2 || posY + velY > h-1){
            id = Shuffle_colorid();
            velY *= -1;
        }

        posX += velX;
        posY += velY;

        usleep(COOLDOWN_MICROSECOND);
    }
}