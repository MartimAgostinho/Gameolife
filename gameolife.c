#include <stdio.h>
#include <stdlib.h>

#define DIMX  96
#define DIMY  42
#define DCHAR '.'
#define LCHAR '#'

void print_game(int dimy,int dimx,char matrx[dimy][dimx]){

    for(int i = 0;i < dimy;++i){
        
        for(int j = 0;j < dimx;++j){
            
            if( matrx[i][j] ){ printf("%c",LCHAR); }
            else{printf("%c",DCHAR);}
        }//printf("\n");
    }
}

void print_matrix(int dimy,int dimx,char matrx[dimy][dimx]){

    for(int i = 0;i < dimy;++i){
        
        for(int j = 0;j < dimx;++j){
            
            printf("%c",matrx[i][j]);
        }printf("\n");
    }
}

void char_matrix(int dimy,int dimx,char matrx[dimy][dimx]){

    for(int i = 0;i < dimy;++i){
        
        for(int j = 0;j < dimx;++j){

            if( matrx[i][j] ){ matrx[i][j] = LCHAR; }
            else{ matrx[i][j] = DCHAR; }
        }
    }
}

//0, acontece nada , 1 - cell morre , 2 -cell criada
char cell_status(int dimy,int dimx,char matrx[dimy][dimx],int posy,int posx){

    int viz = 0;
    int x0 = -1,x1 = 2,y0 = -1,y1 = 2;

    if( !posy ){ y0 = 0; }
    if( !posx ){ x0 = 0; }
    if( posy == (dimy - 1) ){ y1 = 1; }
    if( posx == (dimy - 1) ){ x1 = 1; }
    //printf("| j:%d,i:%d |",x1,y1);

    for(int i = y0;i < y1;++i){
        
        for(int j = x0;j < x1;++j){
            
            if( !(j == 0 && i == 0) ){ 
                
                if( matrx[posy + i][posx + j] ){ ++viz; };
                //printf("%d,%d|",i,j);
            }
        }
    }

    if( !matrx[posy][posx] && viz == 3 ){return 2;}
    if( matrx[posy][posx] && (viz < 2 || viz > 3) ){return 1;}
    return 0;   
}

void cpy_matrix(int dimy,int dimx,char matrx[dimy][dimx],char cpy[dimy][dimx]){
    
    for(int i = 0;i < dimy;++i){
        
        for(int j = 0;j < dimx;++j){
            cpy[i][j] = matrx[i][j];            
        }
    }
}

void fill_matrx(int dimy,int dimx,char matrx[dimy][dimx]){

    char matr_aux[dimy][dimx];
    char inp = 0;
    int posx = 0, posy = 0; 
    int i,j;

    for(i = 0;i < dimy;++i){

        for(j = 0;j < dimx;++j ){
            if( matrx[i][j] ){ matr_aux[i][j] = LCHAR; }
            else{ matr_aux[i][j] = DCHAR; }
        }
    }
    
    system("clear");
    system("stty cbreak");     //uninterrupted input
    
    while(inp != 27){
        
        system("clear");
        if( matr_aux[posy][posx] == LCHAR){ matr_aux[posy][posx] = LCHAR; }
        else{ matr_aux[posy][posx] = DCHAR; }
         
        switch(inp){
            
            case 'w':
                --posy;
                if(posy == -1){ posy = dimy - 1; }
                break;
            
            case 'a':
                --posx;
                if(posx == -1){ posx = dimx - 1; }
                break;
            case 's':
                ++posy;
                if(posy == dimy){ posy = 0; }
                break;
            
            case 'd':
                ++posx;
                if(posx == dimx){ posx = 0; }
                break;
            
            case '\n':
                if( matrx[posy][posy] ){ 
                    
                    //matr_aux[posy][posx] = DCHAR;
                    matrx[posy][posx] = 0;
                }
                else{ 
                    
                    //matr_aux[posy][posx] = LCHAR;
                    matrx[posy][posx] = 1;
                }
                break;
        }
        
        for(i = 0;i < dimy;++i){

            for(j = 0;j < dimx;++j ){
                if( matrx[i][j] ){ matr_aux[i][j] = LCHAR; }
                else{ matr_aux[i][j] = DCHAR; }
            }
        }

        matr_aux[posy][posx] = '*';
        print_matrix(dimy,dimx,matr_aux);
        printf("x:%d,y:%d\n",posx,posy);
        inp = getchar();
    }
    system("stty cooked");  // back to normal
    

}

void game_main(int dimy,int dimx,char matrx[dimy][dimx]){

    char out;
    char matraux[dimy][dimx];

    cpy_matrix(dimy,dimx,matrx,matraux);

    for(int i = 0;i < dimy;++i){
        
        for(int j = 0;j < dimx;++j){
            //printf("%d",out);

           out = cell_status(dimy, dimx, matrx,i,j);
           if( !out ){ continue; }
           if( out == 1){ 
            
            matraux[i][j] = 0;
            continue;
        }
        matraux[i][j] = 1;
            
        }//printf("\n");
    }

    cpy_matrix(dimy,dimx,matraux,matrx);
}

int main(){

    //unsigned int dimx = 10,dimy = 10;
    char matrx[DIMY][DIMX] = {0};
    
    // char matrx[y][x] ={ {0,0,0,0,0,0,0,0,0,0},
   //                     {0,0,0,0,0,0,0,0,0,0},
   //                     {0,0,0,0,0,0,0,0,0,0},
   //                     {0,0,0,0,1,0,0,0,0,0},
   //                     {0,0,1,0,1,0,0,0,0,0},
   //                     {0,0,0,1,1,0,0,0,0,0},
   //                     {0,0,0,0,0,0,0,0,0,0},
   //                     {0,0,0,0,0,0,0,0,0,0},
   //                     {0,0,0,0,0,0,0,0,0,0},
   //                     {0,0,0,0,0,0,0,0,0,0} };

    fill_matrx(DIMY,DIMX,matrx);

    while(1){

        print_game(DIMY, DIMX, matrx);
        game_main(DIMY, DIMX, matrx);
        getchar();
        printf("---------------------------\n");

    }

    return 0;
}
