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

//height and width of the paddle
#define PHEIGHT 10
#define PWIDTH 70

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
    while (lives > 0 && bricks > 0)
    {
     
        
          
        // TODO
        //Initial velocities
        double velocityx = 2 + drand48();
        double velocityy = 2 + drand48();
          
         
        while (true && lives>0 && bricks>0)
        {
          
          // check for mouse event
          GEvent event = getNextEvent(MOUSE_EVENT);

          // if we heard one
          if (event != NULL)
          {
              // if the event was movement
              if (getEventType(event) == MOUSE_MOVED)
              {
                  // ensure paddle follows top cursor
                  double x = getX(event);
                  setLocation(paddle, x, 535);
              }
          }
            
            
            
          // move ball along x and y-axis
          move(ball, velocityx, velocityy);
            
            
            
          GObject object = detectCollision(window, ball);
            
          
          // bounce off right edge of window
          if (getX(ball) + getWidth(ball) >= getWidth(window))
          {
              velocityx = -velocityx;
          }

          // bounce off left edge of window
          else if (getX(ball) <= 0)
          {  
              velocityx = -velocityx;
          }
            
          // bounce off bottom edge of window
          if (getY(ball) + getWidth(ball) >= getHeight(window))
          {
              lives--;
              printf("%i\n", lives);
              setLocation(ball,190,300);
              bool paused= true;
              while(paused)
              {
                GEvent event = getNextEvent(MOUSE_EVENT);
                if (event != NULL)
                {
                   // if the event was movement
                   if (getEventType(event) == MOUSE_CLICKED)
                   {
                      paused= false;
                   }
                }    
               }
                
            }

            // bounce off top edge of window
            else if (getY(ball) + getWidth(ball) <= 0)
            {  
                velocityy = -velocityy;
            }
            
            //bounce off paddle
            else if(object == paddle)
            {
                if(velocityy>0)
                  velocityy = -velocityy;
            }
            
            //Hit a brick
            else if(object!= NULL)
            {
                
                  
                if (strcmp(getType(object), "GRect") == 0 && object!= paddle )
                {
                   bricks--;
                   char s[3];
                   int score = COLS*ROWS - bricks;
                   sprintf(s, "%i", score);
                   setLabel(label, s);
                   removeGWindow(window, object);
                   velocityy = -velocityy;
                }
            }
                                               
            
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

    //Draws the matrix of bricks in the window
    int x=2;
    int y=50;
    GRect bricks[ROWS][COLS];
    char* colors[5]= {"RED","GREEN","BLUE","YELLOW", "ORANGE"};
    
    for(int i=0; i<ROWS; i++)
    {
      for(int j=0; j<COLS; j++)
      {
        bricks[i][j] = newGRect(x,y,36,8);
        setColor(bricks[i][j], colors[i]);
        setFilled(bricks[i][j], true);
        add(window, bricks[i][j]);
        x+=40;
      }
      
      x=2;
      y+=12;
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
 
    //Initializes the ball at the center of the window.
    GOval ball = newGOval(190, 300, 20, 20);
    setColor(ball, "BLACK");
    setFilled(ball, true);
    add(window, ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    
    //Instantiate the paddle
    GRect paddle = newGRect(165,535,PWIDTH, PHEIGHT);
    setColor(paddle, "BLACK");
    setFilled(paddle, true);
    add(window, paddle);
    
    //Return the paddle
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // TODO
    GLabel label = newGLabel("0");
    setFont(label, "SansSerif-36");
    add(window, label);
    setLocation(label, 200,200);
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
