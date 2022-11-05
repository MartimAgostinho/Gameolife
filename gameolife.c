#include <stdio.h>

#define x  10
#define y  10

void print_game(int dimy,int dimx,char matrx[dimy][dimx]){

    for(int i = 0;i < dimy;++i){
        
        for(int j = 0;j < dimx;++j){
            
            if( matrx[i][j] ){ printf("#"); }
            else{printf(" ");}
            
        
        }printf("\n");
    }
}

void char_matrix(int dimy,int dimx,char matrx[dimy][dimx]){

    for(int i = 0;i < dimy;++i){
        
        for(int j = 0;j < dimx;++j){

            if( matrx[i][j] ){ matrx[i][j] = '#'; }
            else{ matrx[i][j] = ' '; }
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

void game_main(int dimy,int dimx,char matrx[dimy][dimx]){

    char out;
    char matraux[dimy][dimx];

    for(int i = 0;i < dimy;++i){
        
        for(int j = 0;j < dimx;++j){
            matraux[i][j] = matrx[i][j];            
        }
    }

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
    for(int i = 0;i < dimy;++i){
        
        for(int j = 0;j < dimx;++j){
            matrx[i][j] = matraux[i][j] ;            
        }
    }
}

int main(){

    //unsigned int dimx = 10,dimy = 10;
    
    char matrx[y][x] ={ {0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,1,0,0,0,0,0},
                        {0,0,1,0,1,0,0,0,0,0},
                        {0,0,0,1,1,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0} };

    while(1){

        print_game(y, x, matrx);
        game_main(y, x, matrx);
        getchar();
        printf("---------------------------\n");

    }

    return 0;
}