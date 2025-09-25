#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int w,h;
int last_byte = 0;

int coord_To_byte(int y, int x) {
    return (x-1)+(y-1)*(w+1);
}

void printDVD(char output[], int row, int col) {
    //clean last DVD
    if(last_byte){
        output[last_byte-1] = ' ';
        output[last_byte]   = ' ';
        output[last_byte+1] = ' ';
    }
    int mid_byte = coord_To_byte(row, col);
    output[mid_byte-1] = 'D';
    output[mid_byte]   = 'V';
    output[mid_byte+1] = 'D';
    last_byte = mid_byte;
    printf("\033[2;1H\033[J"); // moves to second row (to keep info text), erase everything under
    printf("%s\n", output);
}
int main(int argc, char *argv[]) {

    printf("\033[H\033[J"); // clears screen
    
    //default value for gridsize
    w = 40;
    h = 10;

    if(argc == 3){
        w = atoi(argv[1]);
        h = atoi(argv[2]);
    }

    //Ads Columns
    int outputBytes = (w+1) * h;
    char output[outputBytes];
    memset(output, '#', (outputBytes-1)*sizeof(char));
    
    //adding 
    for(int i = 1; i < h; i++){
        output[i*(w+1)-1] = '\n';
    }
    
    for(int j = 0; j < h-2; j++){
        memset(output+(w+2) + j * (w+1), ' ', (w-2)*sizeof(char));
    }
    
    printf("printing grid of %d x %d, using total of %d bytes\n", w+1,h,outputBytes);
    printf("%s", output);

    //starting position and velocity
    int posY = 3;
    int posX = 5;
    int velY = 1;
    int velX = 1;

    // four fantastic corners BOP BOP
    // printDVD(output, 2,3);
    // printDVD(output, 2,w-2);
    // printDVD(output, h-1,3);
    // printDVD(output, h-1,w-2);

    while(1){
        if(posY+velY > h-1 || posY+velY < 2)
            velY = velY * -1;
        if(posX+velX > w-2 || posX+velX < 3)
            velX = velX * -1;
        
        posY += velY; 
        posX += velX;

        printDVD(output, posY, posX);
        
        usleep(500000);
    }
}