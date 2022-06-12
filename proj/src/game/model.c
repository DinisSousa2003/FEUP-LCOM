#include "model.h"

/*MENU MODEL*/

#define ENTRIES 3

int menu_entries[ENTRIES] = {PLAYER1_SELECTED_IMG, PLAYER2_SELECTED_IMG, ABOUT_SELECTED_IMG};
int curEntry = 0;
extern state_t state;

void (addMenuEntry)(){
    if((curEntry + 1) >= ENTRIES) return;
    curEntry++;
}

void (backMenuEntry)(){
    if((curEntry - 1) < 0) return;
    curEntry--;
}

int (getCurrentEntryImg)(){
    return menu_entries[curEntry];
}

/*GAME MODEL*/

int winner = 0;

int player1_initial_x=150, player1_initial_y=300;
int player2_initial_x=650, player2_initial_y=300;
int ball_initial_x=400,ball_initial_y=300;

struct Player player = {150, 300, 0x0000ff, 30, 40, 20, 0};

struct Player player2 = {650, 300, 0xff0000, 30, 40, 20, 0};

struct Player PCplayer = {650, 300, 0xff0000, 5, 40, 20, 0};

struct Ball ball = {400, 300, 0xffffff, 10, 10, 5, 5};

struct Arena arena = {500, 100, 750, 50, 400, 700};

struct Mouse mouse = {400, 300, 0xffff00, 5, 5};

struct Player getPlayer(){
    return player;
}

struct Arena getArena(){
    return arena;
}

struct Ball getBall(){
    return ball;
}

void resetPositions(){
    player.x_pos=player1_initial_x;
    player.y_pos=player1_initial_y;
    if (state==TWOPGAME){
        player2.x_pos=player2_initial_x;
        player2.y_pos=player2_initial_y;    
    }else{
        PCplayer.x_pos=player2_initial_x;
        PCplayer.y_pos=player2_initial_y;      
    }

    ball.x_pos=ball_initial_x;
    ball.y_pos=ball_initial_y;
}

void(resetGame()){
    resetPositions();
    player.score=0;
    if (state==TWOPGAME){
        player2.score=0;    
    }else{
        PCplayer.score=0;    
    }
}


void (playerDown)(struct Player *p){
    if(p->y_pos <= (arena.max_y - p->height - p->vel)){
        p->y_pos += p->vel;
    }
    else if (p->y_pos > (arena.max_y - p->height - p->vel))
    {
        p->y_pos += (arena.max_y - p->y_pos - p->height);
    }
}

void (playerUp)(struct Player *p){
    if(p->y_pos >= (arena.min_y + p->vel)){
        p->y_pos -= p->vel;
    }
    else if (p->y_pos < (arena.min_y + p->vel))
    {
        p->y_pos -= (p->y_pos - arena.min_y);
    }
}

bool goal(){
    if(ball.x_pos > 750){
        player.score++;
        return true;
    }
    if(ball.x_pos < 50){
        if (state==TWOPGAME){
            player2.score++;
        }else{
            PCplayer.score++;
        }
        return true;
    }
    
    return false;
}

bool ballCollidesPlayer(struct Player *p){
    if(!((ball.y_pos + ball.height >= p->y_pos) && (ball.y_pos <= p->y_pos + p->height))){
        return false;
    }
    if(!((ball.x_pos + ball.width >= p->x_pos) && (ball.x_pos <= p->x_pos + p->width))){
        return false;
    }
    return true;
}

bool (moveBall)(){
    
    if (!(260 < ball.y_pos && ball.y_pos < 340))
    {
        if(ball.x_pos + ball.vel_x <= arena.min_x || ball.x_pos + ball.vel_x >= arena.max_x )
        {
            ball.vel_x = -ball.vel_x;
        }    
    }
    if(ball.y_pos + ball.vel_y <= arena.min_y || ball.y_pos + ball.vel_y >= arena.max_y )
    {
        ball.vel_y = -ball.vel_y;
    }

    if(ballCollidesPlayer(&player)){
        ball.vel_x = -ball.vel_x;
    }
    if (state==TWOPGAME){
        if(ballCollidesPlayer(&player2)){
            ball.vel_x = -ball.vel_x;
        }     
    }else{
        if(ballCollidesPlayer(&PCplayer)){
            ball.vel_x = -ball.vel_x;
        }     
    }
    
    ball.x_pos += ball.vel_x;
    ball.y_pos += ball.vel_y;
    if(goal()){
        resetPositions();
        return true;
    }
    return false;
}

void (movePCPlayer)(){
    //idea of moving not good yet
    if(ball.vel_y>0){
        playerDown(&PCplayer);
    }
    else if(ball.vel_y<0){
        playerUp(&PCplayer);
    }
}

bool (gameWinner)(){
    if(player.score == 5){
        winner = 1;
        return true;
    }
    if (state==TWOPGAME){
        if(player2.score == 5){
            winner = 3;
            return true;
        } 
    }else{
         if(PCplayer.score == 5){
            winner = 2;
            return true;
        } 
    }
    return false;   
}

void (moveMouse)(int x, int y){
    mouse.x_pos += x;
    mouse.y_pos -= y;

    if(mouse.x_pos < arena.min_x){
        mouse.x_pos = arena.min_x;
    }
    if(mouse.x_pos > arena.max_x){
        mouse.x_pos = arena.max_x;
    }
    if(mouse.y_pos < arena.min_y){
        mouse.y_pos = arena.min_y;
    }
    if(mouse.y_pos > arena.max_y){
        mouse.y_pos = arena.max_y;
    }
}
