#include "model.h"

/*MENU MODEL*/

#define ENTRIES 3

int menu_entries[ENTRIES] = {PLAYER1_SELECTED_IMG, PLAYER2_SELECTED_IMG, ABOUT_SELECTED_IMG};
int curEntry = 0;


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

int player1_initial_x=650, player1_initial_y=300;
int player2_initial_x=150, player2_initial_y=300;
int ball_initial_x=400,ball_initial_y=300;

struct Player player = {650, 300, 0xffffff, 20, 40, 20, 0};

struct Player player2 = {150, 300, 0xffffff, 5, 40, 20, 0};

struct Ball ball = {400, 300, 0xffffff, 10, 10, 5, 5};

struct Arena arena = {500, 100, 750, 50, 400, 700};

struct Player getPlayer(){
    return player;
}

struct Arena getArena(){
    return arena;
}

struct Ball getBall(){
    return ball;
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
    if(ball.x_pos == arena.min_x && (ball.y_pos >=270 && ball.y_pos <= 330)){
        player.score++;
        return true;
    }
     if(ball.x_pos == arena.max_x && (ball.y_pos >=270 && ball.y_pos <= 330)){
        player2.score++;
        return true;
    }
    return false;

}

bool ballCollidesPlayer(){
    if(!((ball.y_pos + ball.height >= player.y_pos) && (ball.y_pos <= player.y_pos + player.height))){
        return false;
    }
    if(!((ball.x_pos + ball.width >= player.x_pos) && (ball.x_pos <= player.x_pos + player.width))){
        return false;
    }
    return true;
}
bool ballCollidesPlayer2(){
    if(!((ball.y_pos + ball.height >= player2.y_pos) && (ball.y_pos <= player2.y_pos + player2.height))){
        return false;
    }
    if(!((ball.x_pos + ball.width >= player2.x_pos) && (ball.x_pos <= player2.x_pos + player2.width))){
        return false;
    }
    return true;
}
void (moveBall)(){
    if(ball.x_pos + ball.vel_x <= arena.min_x || ball.x_pos + ball.vel_x >= arena.max_x ){
        ball.vel_x = -ball.vel_x;
    }
    if(ball.y_pos + ball.vel_y <= arena.min_y || ball.y_pos + ball.vel_y >= arena.max_y ){
        ball.vel_y = -ball.vel_y;
    }
    if(ballCollidesPlayer()){
        ball.vel_x = -ball.vel_x;
    }
    if(ballCollidesPlayer2()){
        ball.vel_x = -ball.vel_x;
    }
    ball.x_pos += ball.vel_x;
    ball.y_pos += ball.vel_y;
    if(goal()){
        player.x_pos=player1_initial_x;
        player.y_pos=player1_initial_y;
        player2.x_pos=player2_initial_x;
        player2.y_pos=player2_initial_y;
        ball.x_pos=ball_initial_x;
        ball.y_pos=ball_initial_y;
    }
}

void (movePlayer2)(){
    //idea of moving not good yet
    //pc player down (code duplicate)
    if(ball.vel_y>0){
        playerDown(&player2);
    }
    //pc player up (code duplicate)
    else if(ball.vel_y<0){
        playerUp(&player2);
    }
}
