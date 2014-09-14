//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    // keep playing until game over
    double velocity = 2 + drand48();
    double velocity1 = velocity;
    int x_las = 1;
    int y_las = 1;
    while (lives > 0 && bricks > 0)
    {
        
        
        while (true)
        {
            // check for mouse event
            GEvent event = getNextEvent(MOUSE_EVENT);

            // if we heard one
            if (event != NULL)
            {
                // if the event was movement
                if (getEventType(event) == MOUSE_MOVED)
                {
                    // ensure circle follows top cursor
                    double x = getX(event) - getWidth(paddle) / 2;
                    double y = HEIGHT - getHeight(paddle);
                    setLocation(paddle, x, y);
                }
            }
            
           
            
            move(ball, x_las * velocity, y_las * velocity);
            
                    
            GObject object = detectCollision(window, ball);
            
            if (object != NULL)
            {
                if (strcmp(getType(object), "GRect") == 0)
                {
                     y_las = - y_las;
                     
                     if (object != paddle)
                     {
                         removeGWindow(window, object);
                         points = points + 1;
                         updateScoreboard(window, label, points);
                         bricks = bricks - 1;
                         
                         
                     }   
                }
            }
            if (bricks == 0)
               break;
            
            
            // bounce off right and left edge of window
            else if (getY(ball)<= 0)
            {    
                 y_las = - y_las; 
                 
            }
            
            // bounce off up and down edge of window
           
            else if (getX(ball) + getWidth(ball) >= getWidth(window) || getX(ball) <= 0)
            {
                x_las = - x_las;
                
            }
            
            else if (getY(ball) + getHeight(ball) >= getHeight(window))
            {
                velocity = 0;
                move(ball, x_las * velocity, y_las * velocity);
                while (velocity == 0)
                {
                    GEvent event1 = getNextEvent(MOUSE_EVENT); 

                    // if we heard one
                    if (event1 != NULL)
                    {
                        // if the event was movement
                        if (getEventType(event1) == MOUSE_CLICKED)
                        {
                            // ensure circle follows top cursor
                            velocity = velocity1;
                            y_las = - y_las;
                            move(ball, x_las * velocity, y_las * velocity);
                            lives = lives - 1;
                            
                        
                        }
                     }
                  }
                
               
                
                
             }
             if (lives == 0)
                break;
            
            
            
            
            
            
            // linger before moving again
            pause(10);
 
       }
        
        
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{   
    int width = 31, height = 5;
    
    for (int i = 0, y = 50; i < 5; i++, y += 10)
    {
        for (int x = 4; x < 400; x += 40)
        {
            GRect brick = newGRect(x, y, width, height);
            setFilled(brick, true);
            if (i == 0)
            {
                setColor(brick, "RED");
            }
             else if (i == 1)
            {
                setColor(brick, "ORANGE");
            }
            else if (i == 2)
            {
                setColor(brick, "YELLOW");
            }
            else if (i == 3)
            {
                setColor(brick, "GREEN");
            }
            else
            {
                setColor(brick, "BLUE");
            }
            add(window, brick);
        }
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    int width = 20, height = 20;
    GOval ball = newGOval(WIDTH / 2 - width / 2, HEIGHT / 2 - height / 2, width, height);
    setFilled(ball, true);
    setColor(ball, "GREEN");
    add(window, ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{   
    int width = 60;
    int height = 20;
    GRect paddle = newGRect(WIDTH / 2 - width / 2, HEIGHT - height, width, height);
    setFilled(paddle, true);
    setColor(paddle, "RED");
    add(window, paddle);
    
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel("");
    setFont(label, "SansSerif-36");
    add(window, label);
    int i = 0;
    
    char s[12];

    // convert i from int to string
    sprintf(s, "%i", i);

    // update label
    setLabel(label, s);

    // center label
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);

        
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
