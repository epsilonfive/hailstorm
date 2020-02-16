// Hailstorm CE 0.0.1
// Author: epsilon5
// License: none
// Description: a fun game

//build you fucker
#include "sprites.h"

/* Keep these headers */
#include <tice.h>

/* Standard headers - it's recommended to leave them included */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
/* Other available headers */
// including stdarg.h, setjmp.h, assert.h, ctype.h, float.h, iso646.h, limits.h, errno.h
/* Available libraries */
// including lib/ce/graphc.h, lib/ce/fileioc.h, and lib/ce/keypadc.h
// Sample: #include <lib/ce/graphc.h>
#include <graphx.h>
#include <fileioc.h>
#include <keypadc.h>
#include <intce.h>
#include <tice.h>
#include <math.h>
/* Put your function prototypes here */
void WhiText(void) {
    gfx_SetTextBGColor(0);
    gfx_SetTextFGColor(255);
    gfx_SetTextTransparentColor(0);
}

void BlaText(void) {
    gfx_SetTextBGColor(255);
    gfx_SetTextFGColor(0);
    gfx_SetTextTransparentColor(255);
}

bool Confirm(void) {
    uint8_t y;
    bool keypress;
    char str1[9];
    y = 0;
    keypress = true;
    while(!((kb_Data[6] & kb_Enter) || (kb_Data[1] & kb_2nd))) {
        kb_Scan();
        gfx_SetColor(0);
        gfx_FillRectangle(90,90, 140, 60);
        WhiText();
        gfx_SetTextScale(2, 2);
        strcpy(str1, "Really?");
        gfx_PrintStringXY(str1, 160 - gfx_GetStringWidth(str1) / 2, 95);
        gfx_SetTextScale(1, 1);
        strcpy(str1, "Yes");
        gfx_PrintStringXY(str1, 160 - gfx_GetStringWidth(str1) / 2, 117);
        strcpy(str1, "No.");
        gfx_PrintStringXY(str1, 160 - gfx_GetStringWidth(str1) /2 , 133);
        if ((kb_Data[7] & kb_Down) && (y < 1) && (keypress)) {
            y++;
            keypress = false;
        }
        if ((kb_Data[7] & kb_Up) && (y > 0) && (keypress)) {
            y--;
            keypress = false;
        }
        if (!kb_AnyKey()) keypress = true;
        gfx_SetColor(7);
        gfx_Rectangle(90, y * 16 + 114, 140, 14);
        gfx_Rectangle(91, y * 16 + 115, 138, 12);
        //outside of box
        gfx_SetColor(74);
        gfx_Rectangle(90, 90, 140, 60);
        gfx_Rectangle(91, 91, 138, 58);
        gfx_SetTextBGColor(0);
        gfx_SetTextFGColor(255);
        gfx_SetTextTransparentColor(0);
        if (y == 0) {
            strcpy(str1, "Yeah.");
        } else {
            strcpy(str1, "No.");
        }
        gfx_SetTextFGColor(20);
        gfx_PrintStringXY(str1, 160 - gfx_GetStringWidth(str1) / 2, y * 16 + 117);
        gfx_SwapDraw();
    }
    while((kb_Data[6] & kb_Enter) || (kb_Data[1] & kb_2nd)) {
        kb_Scan();
        gfx_SetColor(255);
        gfx_Rectangle(90, y * 16 + 114, 140, 14);
        gfx_Rectangle(91, y * 16 + 115, 138, 12);
        gfx_SetColor(74);
        gfx_Rectangle(90, 90, 140, 60);
        gfx_Rectangle(91, 91, 138, 58);
        gfx_SetTextFGColor(255);
        gfx_PrintStringXY(str1, 160 - gfx_GetStringWidth(str1) / 2, y * 16 + 117);
        gfx_SwapDraw();
    }
    if (y == 0) {
        return true;
    } else {
        return false;
    }
}


/* Put all your code here */
int main(void) {
    short keypressed;
    bool keypress;
    ti_var_t slota;
    //things for the appvar
    bool menuwrapping;
    bool showfps;
    int highscore;
    uint8_t currship;
    int asteroidsdestroyed;
    uint16_t gamesplayed;
    int shotsfired;
    uint8_t playershieldcolor;
    uint8_t playerbulletcolor;
    int plx;
    float plangle;
    uint8_t i;
    uint8_t j;
    short playerhealth;
    uint8_t numasteroids;
    uint16_t frametime;
    int loopsplayeroff;
    char str1[20];
    int count;
    uint8_t numbullets;
    int bulletcountdown;
    short bulletsfired;
    bool canfire;
    short shieldcountdown;
    typedef struct {
        uint16_t x;
        uint8_t y;
    } fstar_t;
    fstar_t fstar[20];
    typedef struct {
        uint16_t x;
        float y;
    } bstar_t;
    bstar_t bstar[20];
    typedef struct {
        uint8_t size;
        int y;
        uint16_t x;
        uint8_t speed;
        uint8_t type;
    } asteroid_t;
    asteroid_t asteroid[20];
    gfx_sprite_t *spr[14][3];
    char menutext[4][20] = {"Select Ship", "Statistics", "Settings", "About"};
    char menutextb[5][20] = {"Menu Wrapping", "Show FPS", "Reset Highscore", "Shield Color", "Bullet Color"};
    char menutextc[35][40] = {" Introduction", "Thanks for downloading and playing", "HailStorm, which aims to be a fun space", "shooter with many features. With smooth", "and consistent gameplay, many available", "spaceships and quality graphics, it", "it is a fun game to play in math class", "or anywhere else.", " Gameplay", "The gameplay is very simple: just dodge", "the asteroids, shooting them or", "activating your shield when necessary.", "With that said, here are the controls:", "[<] and [>]: move left or right", "[2nd]: fire", "[alpha]: activate shield", "[y=]: pause", " Credits", "Thanks to everyone who helped out with", "this project.", "Graphics: matkeller19", "Feedback: tr1p1ea, malagas, Jeffitus,", "beckadamtheinventor, tr1wrk", "Help: MateoConLechuga, Runer112", " Conclusion", "Thanks again for downloading. If you", "want to check out some of my other", "programs or submit feature requests", "or sprites for this one, please", "visit www.cemetech.net and search for", "HailStorm CE."};

    typedef struct {
        uint16_t x;
        uint8_t y;
        float xinc;
        float yinc;
    } bullet_t;
    bullet_t bullet[20];
    //pointers
    fstar_t *f;
    bstar_t *t;
    bullet_t *b;
    asteroid_t *s;
    //spaceships!
    typedef struct {
        gfx_sprite_t *spr;
        bool unlocked;
    } spaceship_t;
    spaceship_t spaceship[10];
    gfx_sprite_t *currspaceship;
    spaceship[0].spr = spaceshipa;
    spaceship[1].spr = spaceshipb;
    spaceship[2].spr = spaceshipc;
    spaceship[3].spr = spaceshipd;
    spaceship[4].spr = spaceshipe;
    spaceship[5].spr = spaceshipf;
    spaceship[6].spr = spaceshipg;
    for (i = 0; i < 10; i++) {
        spaceship_t *s = &spaceship[i];
        s->unlocked = false;
    }
//store some asteroids in the array
    gfx_Begin();
    gfx_SetDraw(1);
    gfx_SetTransparentColor(255);
    for (i = 2; i < 15; i++) {
        gfx_FillScreen(255);
        gfx_RotatedScaledTransparentSprite_NoClip(asteroida, 0, 0, 0, i * 8.5);
        spr[i - 2][0] = gfx_MallocSprite(i * 4, i * 4);
        gfx_GetSprite(spr[i - 2][0], 0, 0);
    }
    for (i = 2; i < 15; i++) {
        gfx_FillScreen(255);
        gfx_RotatedScaledTransparentSprite_NoClip(asteroidb, 0, 0, 0, i * 8.5);
        spr[i - 2][1] = gfx_MallocSprite(i * 4, i * 4);
        gfx_GetSprite(spr[i - 2][1], 0, 0);
    }
    for (i = 2; i < 15; i++) {
        gfx_FillScreen(255);
        gfx_RotatedScaledTransparentSprite_NoClip(asteroidc, 0, 0, 0, i * 8.5);
        spr[i - 2][2] = gfx_MallocSprite(i * 4, i * 4);
        gfx_GetSprite(spr[i - 2][2], 0, 0);
    }
//highscore stuff
    ti_CloseAll();
    if (!(slota = ti_Open("HSTRMDAT", "r"))) {
        highscore = 0;
        currship = 0;
        gamesplayed = 0;
        asteroidsdestroyed = 0;
        shotsfired = 0;
        playershieldcolor = 20;
        playerbulletcolor = 231;
        menuwrapping = true;
        showfps = false;
    } else {
        ti_Read(&highscore, 3, 1, slota);
        ti_Read(&currship, 1, 1, slota);
        ti_Read(&gamesplayed, 2, 1, slota);
        ti_Read(&asteroidsdestroyed, 3, 1, slota);
        ti_Read(&shotsfired, 3, 1, slota);
        ti_Read(&playershieldcolor, 1, 1, slota);
        ti_Read(&playerbulletcolor, 1, 1, slota);
        ti_Read(&menuwrapping, 1, 1, slota);
        ti_Read(&showfps, 1, 1, slota);
    }
//main menu
    WhiText();
    for (i = 0; i < 20; ++i) {
        f = &fstar[i];
        t = &bstar[i];
        f->x = randInt(0, 320);
        f->y = randInt(0, 240);
        t->x = randInt(0, 320);
        t->y = randInt(0, 240);
    }
    currspaceship = spaceship[currship].spr;
MAINMENU:
    //mainmenu start
    keypressed = 0;
    keypress = false;
    while (kb_AnyKey()) kb_Scan();
    while ((keypressed == 0) || (keypress == true)) {
        kb_Scan();
        //update star positions
        for (i = 0; i < 20; ++i) {
            f = &fstar[i];
            t = &bstar[i];
            f->y += 1;
            if (f->y > 240) f->y = 0;
            t->y += 0.5;
            if (t->y > 240) t->y = 0;
        }
        //draw everything
        gfx_ZeroScreen();
        gfx_SetColor(255);
        for (i = 0; i < 20; ++i) {
            f = &fstar[i];
            t = &bstar[i];
            gfx_FillRectangle(320 - f->x, f->y, 2, 2);
            gfx_SetPixel(320 - t->x, t->y);
        }
        //left
        if (kb_Data[1] & kb_Yequ) {
            gfx_SetColor(255);
            keypress = true;
            keypressed = 1;
        } else {
            gfx_SetColor(20);
        }
        gfx_Circle(50, 195, 30);
        gfx_Circle(50, 195, 31);
        gfx_FillCircle(50, 195, 6);
        gfx_FillCircle(70, 195, 6);
        gfx_FillCircle(30, 195, 6);
        gfx_SetTextFGColor(20);
        strcpy(str1, "HailStorm");
        gfx_SetTextScale(2, 2);
        gfx_PrintStringXY(str1, 160 - gfx_GetStringWidth(str1) / 2, 10);
        gfx_SetTextScale(1, 1);
        //right
        if (kb_Data[1] & kb_Graph) {
            gfx_SetColor(255);
            keypress = true;
            keypressed = 3;
        } else {
            gfx_SetColor(20);
        }
        gfx_Circle(270, 195, 30);
        gfx_Circle(270, 195, 31);
        //center
        if (kb_Data[1] & kb_Zoom) {
            gfx_SetColor(255);
            keypress = true;
            keypressed = 2;
        } else {
            gfx_SetColor(20);
        }
        gfx_Circle(160, 190, 37);
        gfx_Circle(160, 190, 36);
        gfx_Circle(160, 190, 35);
        gfx_FillTriangle(186, 190, 160 + 26 * cos(2.09), 190 + 26 * sin(2.09), 160 + 26 * cos(4.19), 190 + 26 * sin(4.19));
        gfx_SetColor(0);
        gfx_FillTriangle(180, 190, 160 + 20 * cos(2.09), 190 + 20 * sin(2.09), 160 + 20 * cos(4.19), 190 + 20 * sin(4.19));
        //end
        if (!kb_AnyKey()) keypress = false;
        gfx_SwapDraw();
    }
    if (keypressed == 3) goto QUIT;
    if (keypressed == 1) {
        plx = 0;
        keypress = true;
        j = currship;
        playerhealth = 0;
        loopsplayeroff = 0;
        WhiText();
        while (!(kb_Data[1] & kb_Zoom)) {
            gfx_ZeroScreen();
            gfx_SetTextScale(1, 1);
            //NOTE: bottom toolbar code is embedded here
            kb_Scan();
            if (kb_Data[1] & kb_Yequ) {
                if ((keypress) && (plx > 0)) {
                    plx--;
                    keypress = false;
                }
                gfx_SetColor(255);
                gfx_SetTextFGColor(255);
            } else {
                gfx_SetColor(20);
                gfx_SetTextFGColor(20);
            }
            if (plx > 0) {
                gfx_FillTriangle(5, 225, 15 + 10 * cos(1.05), 225 + 10 * sin(1.05), 15 + 10 * cos(5.24), 225 + 10 * sin(5.24));
                gfx_SetColor(0);
                gfx_FillTriangle(9, 225, 15 + 6 * cos(1.05), 225 + 6 * sin(1.05), 15 + 6 * cos(5.24), 225 + 6 * sin(5.24));
                gfx_PrintStringXY(menutext[plx - 1], 23, 222);
            }
            if ((kb_Data[1] & kb_Graph)) {
                if ((keypress) && (plx < 3)) {
                    plx++;
                    keypress = false;
                }
                gfx_SetColor(255);
                gfx_SetTextFGColor(255);
            } else {
                gfx_SetColor(20);
                gfx_SetTextFGColor(20);
            }
            if (plx < 3) {
                gfx_FillTriangle(315, 225, 305 + 10 * cos(2.09), 225 + 10 * sin(2.09), 305 + 10 * cos(4.19), 225 + 10 * sin(4.19));
                gfx_SetColor(0);
                gfx_FillTriangle(311, 225, 305 + 6 * cos(2.09), 225 + 6 * sin(2.09), 305 + 6 * cos(4.19), 225 + 6 * sin(4.19));
                gfx_PrintStringXY(menutext[plx + 1], 297 - gfx_GetStringWidth(menutext[plx + 1]), 222);
            }
            if (kb_Data[1] & kb_Zoom) goto MAINMENU;
            gfx_SetColor(20);
            //do some making of the button that returns to the main menu
            gfx_SetTextFGColor(20);
            if (!kb_AnyKey()) keypress = true;
            for (i = 0; i < 20; ++i) {
                f = &fstar[i];
                t = &bstar[i];
                f->y += 1;
                if (f->y > 240) f->y = 0;
                t->y += 0.5;
                if (t->y > 240) t->y = 0;
            }
            //draw everything
            //title text and stuff
            gfx_SetTextScale(2, 2);
            gfx_PrintStringXY(menutext[plx], 160 - gfx_GetStringWidth(menutext[plx]) / 2, 10);
            gfx_HorizLine(15, 30, 290);
            gfx_HorizLine(30, 215, 260);
            //stars
            gfx_SetColor(255);
            for (i = 0; i < 20; ++i) {
                f = &fstar[i];
                t = &bstar[i];
                gfx_FillRectangle(320 - f->x, f->y, 2, 2);
                gfx_SetPixel(320 - t->x, t->y);
            }
            //menu specific stuff
            if (plx == 0) {
                if (kb_Data[7] & kb_Left) {
                    if ((keypress) && (j > 0)) {
                        j--;
                        keypress = false;
                    }
                    gfx_SetColor(255);
                } else {
                    gfx_SetColor(20);
                }
                if (j > 0) {
                    gfx_FillTriangle(64, 120, 90 + 26 * cos(1.05), 120 + 26 * sin(1.05), 90 + 26 * cos(5.24), 120 + 26 * sin(5.24));
                    gfx_SetColor(0);
                    gfx_FillTriangle(70, 120, 90 + 20 * cos(1.05), 120 + 20 * sin(1.05), 90 + 20 * cos(5.24), 120 + 20 * sin(5.24));
                }
                if (kb_Data[7] & kb_Right) {
                    if ((keypress) && (j < 6)) {
                        j++;
                        keypress = false;
                    }
                    gfx_SetColor(255);
                } else {
                    gfx_SetColor(20);
                }
                if (j < 6) {
                    gfx_FillTriangle(256, 120, 230 + 26 * cos(2.09), 120 + 26 * sin(2.09), 230 + 26 * cos(4.19), 120 + 26 * sin(4.19));
                    gfx_SetColor(0);
                    gfx_FillTriangle(250, 120, 230 + 20 * cos(2.09), 120 + 20 * sin(2.09), 230 + 20 * cos(4.19), 120 + 20 * sin(4.19));
                }
                currspaceship = spaceship[j].spr;
                gfx_ScaledTransparentSprite_NoClip(currspaceship, 130, 90, 2, 2);
                sprintf(str1, "%d / 7", j + 1);
                gfx_SetTextScale(1, 1);
                gfx_SetTextFGColor(255);
                gfx_PrintStringXY(str1, 160 - gfx_GetStringWidth(str1) / 2, 155);
                sprintf(str1, "Unlocked: %d", spaceship[j].unlocked);
                gfx_PrintStringXY(str1, 160 - gfx_GetStringWidth(str1) / 2, 77);
                //if some condition is fulfilled
                currship = j;
            }
            if (plx == 1) {
                gfx_SetTextScale(1, 1);
                gfx_SetTextFGColor(255);
                gfx_PrintStringXY("Highscore :", 40, 40);
                sprintf(str1, "%d", highscore);
                gfx_PrintStringXY(str1, 280 - gfx_GetStringWidth(str1), 40);
                gfx_PrintStringXY("Games Played :", 40, 55);
                sprintf(str1, "%d", gamesplayed);
                gfx_PrintStringXY(str1, 280 - gfx_GetStringWidth(str1), 55);
                gfx_PrintStringXY("Asteroids Destroyed:", 40, 70);
                sprintf(str1, "%d", asteroidsdestroyed);
                gfx_PrintStringXY(str1, 280 - gfx_GetStringWidth(str1), 70);
                gfx_PrintStringXY("Shots Fired :", 40, 85);
                sprintf(str1, "%d", shotsfired);
                gfx_PrintStringXY(str1, 280 - gfx_GetStringWidth(str1), 85);
                gfx_PrintStringXY("Accuracy :", 40, 100);
                sprintf(str1, "%d %s", asteroidsdestroyed * 100 / shotsfired, "%");
                gfx_PrintStringXY(str1, 280 - gfx_GetStringWidth(str1), 100);
            }
            if (plx == 2) {
                if (kb_Data[7] & kb_Up) {
                    if ((keypress) && (playerhealth > 0)) {
                        playerhealth--;
                        keypress = false;
                    }
                }
                if (kb_Data[7] & kb_Down) {
                    if ((keypress) && (playerhealth < 4)) {
                        playerhealth++;
                        keypress = false;
                    }
                }
                if (kb_Data[7] & kb_Right) {
                    if (playerhealth == 0) menuwrapping = true;
                    if (playerhealth == 1) showfps = true;
                    if ((playerhealth == 3) && (playershieldcolor < 255)) playershieldcolor++;
                    if ((playerhealth == 4) && (playerbulletcolor < 255)) playerbulletcolor++;
                }
                if (kb_Data[7] & kb_Left) {
                    if (playerhealth == 0) menuwrapping = false;
                    if (playerhealth == 1) showfps = false;
                    if ((playerhealth == 3) && (playershieldcolor > 1)) playershieldcolor--;
                    if ((playerhealth == 4) && (playerbulletcolor > 1)) playerbulletcolor--;
                }
                gfx_SetTextFGColor(255);
                gfx_SetTextScale(1, 1);
                for (i = 0; i < 5; i++) {
                    gfx_PrintStringXY(menutextb[i], 40, 40 + i * 15);
                }
                //the box
                if ((kb_Data[6] & kb_Enter) || (kb_Data[1] & kb_2nd)) {
                    if (playerhealth == 2) {
                            while (kb_AnyKey()) kb_Scan();
                            if (Confirm()) {
                                asteroidsdestroyed = 0;
                                highscore = 0;
                                currship = 0;
                                gamesplayed = 0;
                                asteroidsdestroyed = 0;
                                shotsfired = 0;
                            }
                    }
                    if ((playerhealth == 0) && (keypress)) {
                        menuwrapping = !menuwrapping;
                        keypress = false;
                    }
                    if ((playerhealth == 1) && (keypress)) {
                        showfps = !showfps;
                        keypress = false;
                    }
                    gfx_SetColor(20);
                    WhiText();
                } else {
                    gfx_SetColor(255);
                    BlaText();
                }
                gfx_FillCircle(40, 44 + playerhealth * 15, 6);
                gfx_FillRectangle(40, 38 + playerhealth * 15, 110, 13);
                gfx_FillCircle(150, 44 + playerhealth * 15, 6);
                gfx_PrintStringXY(menutextb[playerhealth], 40, 40 + playerhealth * 15);
                //colors
                gfx_SetColor(playershieldcolor);
                gfx_FillCircle(240, 89, 6);
                gfx_FillRectangle(240, 83, 40, 13);
                gfx_FillCircle(280, 89, 6);
                gfx_SetColor(playerbulletcolor);
                gfx_FillCircle(240, 104, 6);
                gfx_FillRectangle(240, 98, 40, 13);
                gfx_FillCircle(280, 104, 6);
                gfx_SetColor(255);
                for (i = 0; i < 2; i++) {
                    if (i == 0) {
                        canfire = menuwrapping;
                    } else {
                        canfire = showfps;
                    }
                    gfx_SetColor(224);
                    if (canfire) gfx_SetColor(7);
                    gfx_FillCircle(240, 44 + i * 15, 6);
                    gfx_FillRectangle(240, 38 + i * 15, 40, 13);
                    gfx_FillCircle(280, 44 + i * 15, 6);
                    gfx_SetColor(255);
                    if (canfire) {
                        gfx_FillCircle(280, 44 + i * 15, 4);
                    } else {
                        gfx_FillCircle(240, 44 + i * 15, 4);
                    }
                }
                for (i = 0; i < 2; i++) {
                    if (i == 0) {
                        count = playershieldcolor;
                    } else {
                        count = playerbulletcolor;
                    }
                    if ((count > 1) && (count < 255)) sprintf(str1, "< %d >", count);
                    if (count == 1) sprintf(str1, "%d >", count);
                    if (count == 255) sprintf(str1, "< %d", count);
                    gfx_FillCircle(243, 89 + i * 15, 4);
                    gfx_FillRectangle(243, 85 + i * 15, 34, 9);
                    gfx_FillCircle(277, 89 + i * 15, 4);
                    gfx_PrintStringXY(str1, 260 - gfx_GetStringWidth(str1) / 2, 86 + i * 15);
                }
                WhiText();
            }
            if (plx == 3) {
                gfx_SetColor(20);
                if (kb_Data[7] & kb_Up) {
                    if ((keypress) && (loopsplayeroff > 0)) {
                        loopsplayeroff--;
                        keypress = false;
                    }
                    gfx_SetColor(255);
                }
                if (kb_Data[7] & kb_Down) {
                    if ((keypress) && (loopsplayeroff < 21)) {
                        loopsplayeroff++;
                        keypress = false;
                    }
                    gfx_SetColor(255);
                }
                //the scrolling box thing
                gfx_FillRectangle(17, 37 + loopsplayeroff * 7, 5, 17);
                gfx_FillCircle(19, 37 + loopsplayeroff * 7, 2);
                gfx_FillCircle(19, 54 + loopsplayeroff * 7, 2);
                WhiText();
                gfx_SetTextScale(1, 1);
                //bulletcountdown is used for text y position because why not
                bulletcountdown = 0;
                for (i = 0; i < 10; ++i) {
                    if (" "[0] == menutextc[i + loopsplayeroff][0]) {
                        gfx_SetTextScale(2, 2);
                        bulletcountdown++;
                        gfx_PrintStringXY(menutextc[i + loopsplayeroff], 160 - gfx_GetStringWidth(menutextc[i + loopsplayeroff]) / 2, 44 + (bulletcountdown - 1) * 15);
                        bulletcountdown++;
                    } else {
                        gfx_SetTextScale(1, 1);
                        gfx_PrintStringXY(menutextc[i + loopsplayeroff], 40, 40 + bulletcountdown * 15);
                        bulletcountdown++;
                    }
                    if (bulletcountdown > 10) break;
                }
            }
            gfx_SwapDraw();
        }
        goto MAINMENU;
    }
    numasteroids = 0;
    for (i = 0; i < 20; ++i) {
        asteroid_t *s = &asteroid[i];
        s->x = randInt(320, 640);
        s->y = randInt(0, 240);
        s->speed = randInt(2, 7);
        s->size = randInt(2, 15);
        s->type = randInt(0, 2);
    }
    count = 0;
    playerhealth = 100;
    numbullets = 0;
    plx = 160;
    plangle = 1.55;
    bulletsfired = 0;
    bulletcountdown = 0;
    shieldcountdown = 0;
    canfire = true;
    keypress = true;
    gamesplayed++;
    WhiText();
    while ((!(kb_Data[6] & kb_Clear)) && (playerhealth > 0)) {
        timer_Control = TIMER1_ENABLE | TIMER1_32K | TIMER1_UP;
        numasteroids = count / 150;
        if (numasteroids > 20) numasteroids = 20;
        ++count;
        kb_Scan();
        if (kb_AnyKey()) {
            if ((kb_Data[2] & kb_Alpha) && (shieldcountdown == 0)) shieldcountdown = 1000;
            if (kb_Data[7] & kb_Left) {
                if (plangle < 2.55) plangle += 0.1;
            }
            if (kb_Data[7] & kb_Right) {
                if (plangle > 0.55) plangle -= 0.1;
            }
            //bullet stuff
            if (kb_Data[1] & kb_2nd) {
                if ((canfire) && (keypress)) {
                    bullet_t *b = &bullet[numbullets++];
                    b->x = plx + 15 * cos(plangle) + 8;
                    b->y = 165;
                    b->xinc = 10 * cos(plangle);
                    b->yinc = 10 * sin(plangle);
                    b = &bullet[numbullets++];
                    b->x = plx + 15 * cos(plangle) - 8;
                    b->y = 165;
                    b->xinc = 10 * cos(plangle);
                    b->yinc = 10 * sin(plangle);
                    if (bulletsfired == 0) bulletcountdown = 200;
                    if (bulletsfired < 5) bulletsfired++;
                    keypress = false;
                    shotsfired++;
                }
            } else {
                keypress = true;
            }
        } else {
            if (plangle < 1.55) {
                plangle += 0.1;
            }
            if (plangle > 1.65) {
                plangle -= 0.1;
            }
        }
        //plx update
        plx = plx + 6 * cos(plangle);
        if (bulletcountdown == 0) {
            bulletsfired = 0;
            canfire = true;
        }
        if (bulletcountdown > 0) bulletcountdown--;
        if (bulletsfired > 4) {
            canfire = false;
        } else {
            canfire = true;
        }
        if (shieldcountdown > 0) shieldcountdown--;
//update asteroids
        for (i = 0; i < numasteroids; ++i) {
            s = &asteroid[i];
            s->y += s->speed;
            if (s->y > 240) {
                s->x = randInt(0, 320);
                s->size = randInt(2, 15);
                s->y = -s->size;
                s->speed = randInt(2, 7);
                s->type = randInt(0, 2);
                continue;
            }
            if ((abs(180 - s->y) <= s->size) && (abs(plx - s->x) <= s->size + 10))
                if (shieldcountdown > 800) {
                    s->x = randInt(0, 320);
                    s->size = randInt(2, 15);
                    s->y = -s->size;
                    s->speed = randInt(2, 7);
                    s->type = randInt(0, 2);
                    continue;
                } else {
                    playerhealth -= 3;
                }
            //eventually something here that makes the asteroids break up
        }
        //update bullets
        for (i = 0; i < numbullets; ++i) {
            b = &bullet[i];
            b->x += b->xinc;
            b->y -= b->yinc;
            if ((b->x > 320) || (b->x < 0) || (b->y > 240)) {
                bullet[i] = bullet[--numbullets];
                continue;
            }
            for (j = 0; j < numasteroids; j++) {
                s = &asteroid[j];
                if ((abs(b->x - s->x) <= s->size + 2)) {
                    if ((abs(b->y - s->y) <= s->size + 2) && (s->y > 0)) {
                        s->x = randInt(0, 320);
                        s->size = randInt(2, 15);
                        s->y = -s->size;
                        s->speed = randInt(2, 7);
                        s->type = randInt(0, 2);
                        bullet[i] = bullet[--numbullets];
                        asteroidsdestroyed++;
                    }
                }
            }
        }
//graphics start here
        gfx_ZeroScreen();
        //highscore line thing
        if (abs(highscore - count) < 54) {
            gfx_SetColor(randInt(0, 255));
            gfx_FillRectangle(0, 165 - (highscore - count) * 3, 120, 2);
            gfx_FillRectangle(200, 165 - (highscore - count) * 3, 120, 2);
            gfx_SetTextFGColor(randInt(0, 255));
            strcpy(str1, "Highscore!");
            if (161 - (highscore - count) < 190) gfx_PrintStringXY(str1, 160 - gfx_GetStringWidth(str1) / 2, 161 - (highscore - count) * 3);
        }
        gfx_SetColor(255);
        for (i = 0; i < 20; ++i) {
            f = &fstar[i];
            t = &bstar[i];
            f->y += 1;
            if (f->y > 240) f->y = 0;
            t->y += 0.5;
            if (t->y > 240) t->y = 0;
            //graphics
            gfx_FillRectangle(320 - f->x, f->y, 2, 2);
            gfx_SetPixel(320 - t->x, t->y);
        }
        if (plx < 0 || plx > 320) {
            loopsplayeroff++;
            if (loopsplayeroff > 60) playerhealth--;
            gfx_SetTextFGColor(224);
            gfx_SetTextScale(2, 2);
            if (plx < 15) gfx_PrintStringXY("!", 8, 172);
            if (plx > 305) gfx_PrintStringXY("!", 312, 172);
            gfx_SetTextFGColor(255);
            gfx_SetTextScale(1, 1);
        } else {
            loopsplayeroff = 0;
            gfx_RotatedTransparentSprite_NoClip(currspaceship, plx - 15, 165, -plangle * 41 + 64);
            if (shieldcountdown > 800) {
                gfx_SetColor(playershieldcolor);
                gfx_Circle(plx, 180, 18);
            }
        }
        for (i = 0; i < numasteroids; ++i) {
            asteroid_t *s = &asteroid[i];
            gfx_TransparentSprite(spr[s->type][s->size - 2], s->x - s->size, s->y - s->size);
        }
        gfx_SetColor(0);
        gfx_FillRectangle(0, 228, 320, 12);
        if (playerhealth > 70) gfx_SetColor(7);
        if (playerhealth < 80) gfx_SetColor(231);
        if (playerhealth < 40) gfx_SetColor(224);
        gfx_FillRectangle(160 - playerhealth, 232, playerhealth * 2, 6);
        if (bulletcountdown > 0) {
            gfx_SetColor(224);
            gfx_FillRectangle(2, 232, bulletcountdown / 3.6, 6);
        } else {
            gfx_SetColor(7);
            gfx_FillRectangle(2, 232, 52, 6);
        }
        if (shieldcountdown >= 800) {
            gfx_SetColor(20);
            gfx_FillRectangle(318 - (shieldcountdown - 800) / 3.8, 232, (shieldcountdown - 800) / 3.8, 6);
        }
        if ((shieldcountdown < 800) && (shieldcountdown > 0)) {
            gfx_SetColor(224);
            gfx_FillRectangle(318 - shieldcountdown / 15.2, 232, shieldcountdown / 15.2, 6);
        }
        if (shieldcountdown == 0) {
            gfx_SetColor(7);
            gfx_FillRectangle(266, 232, 52, 6);
        }
        //bottom toolbar
        gfx_SetTextFGColor(20);
        gfx_PrintStringXY("HEALTH", 136, 218);
        gfx_PrintStringXY("SHIELD", 267, 218);
        gfx_PrintStringXY("BULLET", 5, 218);
        gfx_SetTextFGColor(255);
        gfx_SetColor(20);
        gfx_FillRectangle(0, 228, 320, 2);
        gfx_FillRectangle(56, 228, 2, 12);
        gfx_FillRectangle(262, 228, 2, 12);
        gfx_SetColor(playerbulletcolor);
        for (i = 0; i < numbullets; ++i) {
            bullet_t *b = &bullet[i];
            gfx_Line(b->x, b->y, b->x + b->xinc / 2, b->y - b->yinc / 2);
        }
        sprintf(str1, "Score = %d", count);
        gfx_PrintStringXY(str1, 5, 5);
        if (showfps) {
        sprintf(str1, "FPS = %d", 32768 / timer_1_Counter);
        gfx_PrintStringXY(str1, 5, 15);
        }
        gfx_SwapDraw();
        //update frametime and stuff
        frametime = timer_1_Counter;
        timer_1_Counter = 0;
    }
    while (kb_AnyKey()) kb_Scan();
    while (!kb_AnyKey()) {
        kb_Scan();
        for (i = 0; i < 20; ++i) {
            f = &fstar[i];
            t = &bstar[i];
            f->y += 1;
            if (f->y > 240) f->y = 0;
            t->y += 0.5;
            if (t->y > 240) t->y = 0;
        }
        //draw everything
        gfx_ZeroScreen();
        gfx_SetColor(255);
        for (i = 0; i < 20; ++i) {
            f = &fstar[i];
            t = &bstar[i];
            gfx_FillRectangle(320 - f->x, f->y, 2, 2);
            gfx_SetPixel(320 - t->x, t->y);
        }
        gfx_SetTextScale(2, 2);
        gfx_SetTextFGColor(20);
        gfx_PrintStringXY("Finished", 160 - gfx_GetStringWidth("Finished") / 2, 10);
        gfx_SetColor(20);
        gfx_HorizLine(15, 30, 290);
        if (count >= highscore) {
            gfx_SetTextFGColor(randInt(0, 255));
            strcpy(str1, "New highscore!");
            gfx_PrintStringXY(str1, 160 - gfx_GetStringWidth(str1) / 2, 180);
            highscore = count;
        }
        gfx_SwapDraw();
    }
    goto MAINMENU;
//save highscore to appvar
QUIT:
    gfx_End();
    ti_CloseAll();
    slota = ti_Open("HSTRMDAT", "w+");
    ti_Write(&highscore, 3, 1, slota);
    ti_Write(&currship, 1, 1, slota);
    ti_Write(&gamesplayed, 2, 1, slota);
    ti_Write(&asteroidsdestroyed, 3, 1, slota);
    ti_Write(&shotsfired, 3, 1, slota);
    ti_Write(&playershieldcolor, 1, 1, slota);
    ti_Write(&playerbulletcolor, 1, 1, slota);
    ti_Write(&menuwrapping, 1, 1, slota);
    ti_Write(&showfps, 1, 1, slota);
    ti_SetArchiveStatus(true, slota);
}



