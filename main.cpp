#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <SFML/Audio.hpp>
#include "physics.h"
#include "Brick.h"
#include "Ball.h"
#include "paddle.h"
#include "powerup.h"
#include "Laser.h"
#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf; //for graphics


int main()
{
    RenderWindow window(VideoMode(800,600),"SFML Works");  //creates a window on the screen that is 800 by 600
    window.setFramerateLimit(60); //sets the game loop to run 60 times per second
    b2World world(b2Vec2(0.0, 0.0));

    vector<Powerup> powerups;
    vector<Laser> laser;
    vector<Brick> walls;

    int j = 0;
    int j2 = 0;
    int col=0;
    int lasertime=0;
    int score=0;
    int life=5;
    int xstart=0;
    int ystart=0;
    float ballsize=10;
    bool doubleball=false;
    bool gameover=false;
    bool lasers=false;
    bool start= false;
    bool startoption= true;
    bool colours = false;
    bool play=false;
    bool startcreate=false;
    bool longer=false;
    int titlecolor1=244;
    int titlecolor2=66;
    int titlecolor3=66;
    int level=1;
    int longertime;
    int xmin=75;
    int xmax=725;
    int xover=0;
    int yover=0;

    walls.push_back(Brick(world,0, 0, 5, 600));
    walls.push_back(Brick(world,0, 0, 800, 10));
    walls.push_back(Brick(world,795, 0, 5, 600));
    walls.push_back(Brick(world,0, 590, 800, 10));
    bool levelup=false;
    Font f1;
    f1.loadFromFile("Rocket Rinder.otf");
    Text pointsw;
    Text livesw;
    Text pointsn;
    Text livesn;
    Text playw;
    Text gameoverw;
    Text retryw;
    Text gameoverscore;
    Text gameoverscoren;
    Text levelw;
    Text leveln;
    Text gameoverlevelw;
    Text gameoverleveln;
    Text pressspace;

//    Texture t1;
//    t1.loadFromFile("ballsprite.png");

    vector <Text> rpgpoints;
    vector <int> rpgpointsy;
    vector <float> rpgvisibility;
    vector <int> rpgpointsx;
    vector <int> rpglife;

    bool bull=false;
    int bulltime;

    pressspace.setFont(f1);
    levelw.setFont(f1);
    leveln.setFont(f1);
    gameoverscoren.setFont(f1);
    gameoverscore.setFont(f1);
    gameoverw.setFont(f1);
    retryw.setFont(f1);
    pointsw.setFont(f1);
    livesw.setFont(f1);
    livesn.setFont(f1);
    pointsn.setFont(f1);
    playw.setFont(f1);

    Text title;
    title.setFont(f1);
    Text startw;
    startw.setFont(f1);

    int xspace=0;
    int yspace=0;

    Texture space;
    space.loadFromFile("retroback.png");

    Texture sphereball;
    sphereball.loadFromFile("ballsprite.png");

    Texture Startscreen;
    Startscreen.loadFromFile("Beginscreen.png");

    Texture gameoverback;
    gameoverback.loadFromFile("gameoverback.png");

    vector <int> xsphere;
    vector <int> ysphere;
    vector <float> sphereposx;
    vector <float> sphereposy;


//   RectangleShape background;

    vector <Brick> bricks;

    vector <Ball> ball1;
    Paddle p1(world, 325, 550, 150, 10);

    vector <Sprite> ballshape;



    pressspace.setPosition(Vector2f(165, 300));
    pressspace.setString("Press Space!");
    pressspace.setCharacterSize(62);
    pressspace.setColor(Color(255, 0, 102));

    Music song;
    song.openFromFile("ParadiseWarfare.ogg");

    song.play();
    song.setLoop(true);




//    ball1.setVelocity(0,3.14/4.0);

    while (window.isOpen()&& !Keyboard::isKeyPressed(Keyboard::Escape))     //the main game loop, exits if someone closes the window
    {
        Event event; //creates an event object, events include mouse clicks, mouse movement, keyboard presses, etc..
        while (window.pollEvent(event)) //loop that checks for events
        {
            if (event.type == Event::Closed) //checks if window is closed
                window.close();
        }   //ends the event loop





        if(play==true && gameover==false)
        {
            if (startcreate == true)
            {


                for (int i=0; i<bricks.size(); i++)
                {
                    bricks[i].removeBody();
                }
                bricks.clear();

                j = 0;
                j2 = 0;
                col=0;

                for (int i = 0; i < 120; i++)
                {
                    bricks.push_back(Brick(world, 47+59*j2, 40+ 25*j, 59, 25));
                    bricks.back().setFillColor(Color::Black);
                    bricks.back().setOutlineThickness(-2.0);
                    if (level%1==0)
                    {
                        bricks.back().setOutlineColor(Color(0,255,0));
                    }
                    if (level%1==0 && level%2==0)
                    {
                        bricks.back().setOutlineColor(Color(255,0,255));
                    }
                    if (level%1==0 && level%3==0)
                    {
                        bricks.back().setOutlineColor(Color(0,0,255));
                    }
                    if (level%1==0 && level%2==0 && level%4==0)
                    {
                        bricks.back().setOutlineColor(Color(0,255,225));
                    }
                    if (level%1==0 && level%5==0)
                    {
                        bricks.back().setOutlineColor(Color(255,0,0));
                    }
                    if (level%1==0 && level%2==0 && level%3==0 && level%6==0)
                    {
                        bricks.back().setOutlineColor(Color(255,175,20));
                    }
                    if (level%1==0 && level%7==0)
                    {
                        bricks.back().setOutlineColor(Color(255,0,rand()%255));
                    }
                    if (level%1==0 && level%2==0 && level%4==0 && level%8==0)
                    {
                        bricks.back().setOutlineColor(Color(255,0,rand()%255));
                    }


                    j2++;

                    if (bricks.size() % 12 == 0)
                    {
                        j++;
                        j2 = 0;
                        col++;
                    }

                }

                lasertime=0;
                ballsize=10;
                doubleball=false;
                p1.setPosition(Vector2f(425, 550));
                p1.setSize(Vector2f(150,10));
                p1.updatePosition();
                lasers=false;
                for (int i=0; i<ball1.size(); i++)
                {
                    ball1[i].removeBody();
                }
                for (int i=0; i<powerups.size(); i++)
                {
                    powerups[i].removeBody();
                }
                powerups.clear();
                ball1.clear();
                startoption=true;

                rpglife.clear();
                rpgpoints.clear();
                rpgpointsx.clear();
                rpgvisibility.clear();
                rpgpointsy.clear();
                laser.clear();



                levelup=false;
                startcreate = false;



            }


            sf::Sprite spaceback(space,sf::IntRect(xspace,yspace,500,500));
            xspace+=332;
            if(yspace<1992)
            {
                if(xspace >= 2324)
                {
                    xspace=0;
                    yspace+=332;
                }
            }
            else if(xspace>=1660)
            {
                yspace=0;
                xspace=0;
            }
            spaceback.setPosition(0,0);
            spaceback.setScale(2.40963855422,2.40963855422);

            p1.setFillColor(Color::Black);
            p1.setOutlineColor(Color(255, 255, 0));
            p1.setOutlineThickness(-2);

            if(Keyboard::isKeyPressed(Keyboard::L))
            {
                life=0;
            }



            if(Keyboard::isKeyPressed(Keyboard::H))
            {
                for(int i=0; i<bricks.size(); i++)
                {
                    bricks[i].removeBody();
                }
                bricks.clear();
                if (bricks.size()<=0)
                {
                    levelup=true;
                    level++;
                }

            }


            if (startoption==true)
            {
                if  (Keyboard::isKeyPressed(Keyboard::Space) == true)
                {
                    ball1.push_back(Ball(world,p1.getPosition().x,540, ballsize));
                    ball1.back().res->SetActive(true);
                    ball1.back().setFillColor(Color(255,0,0));
                    ball1.back().setOutlineColor(Color(0, 249, 250));
                    ball1.back().setOutlineThickness(-2);


                    startoption = false;
                }
            }



            if (ball1.size()>0)
            {
                for(int i=0; i<xsphere.size(); i++)
                {
                    xsphere[i]+=500;
                    if (xsphere[i]>=2000)
                    {
                        xsphere[i]=0;
                        ysphere[i]+=500;
                    }
                    if (ysphere[i]>=3500)
                    {
                        ysphere[i]=0;
                    }


                }
                for (int i=0; i<ballshape.size(); i++)
                {
                    ballshape[i].setPosition(ball1[i].getPosition().x,ball1[i].getPosition().y);
                    ballshape[i].setTextureRect(sf::IntRect(xsphere[i],ysphere[i],500,500));
                    ballshape[i].setOrigin(250,250);
                }
            }



            if (ball1.size()>1)
            {

                for (int i = 0; i<ball1.size(); i++)
                {
                    if (ball1[i].checkCollision(walls[3].res)==true)
                    {
                        ball1[i].removeBody();
                        ball1.erase(ball1.begin() + i);

                    }
                }
            }

            if (ball1.size()==1)
            {
                if (ball1[0].checkCollision(walls[3].res)==true)
                {
                    life-=1;
                    ball1[0].removeBody();
                    ball1.erase(ball1.begin() + 0);
                    startoption=true;
                }
            }

            if (life<1)
            {
                gameover=true;
                play=false;
            }

            if (doubleball==true)
            {
                int balsize=ball1.size();
                for (int i=0; i<balsize; i++)
                {
                    float balx= ball1[i].getPosition().x;
                    float baly= ball1[i].getPosition().y;
                    ball1.push_back(Ball(world,ball1[i].getPosition().x,ball1[i].getPosition().y, ballsize));
                    ball1.back().res->SetActive(true);
                    ball1.back().setFillColor(Color(255,0,0));
                    ball1.back().setOutlineColor(Color(0, 249, 250));
                    ball1.back().setOutlineThickness(-2);
                }

                doubleball=false;
            }

            if (bull==true)
            {
                bulltime-=1;

                for (int i=0; i<ball1.size(); i++)
                {
                    if (ball1[i].getPosition().x>20 && ball1[i].getPosition().x<788 && ball1[i].getPosition().y> 20 && ball1[i].getPosition().y<388)
                    {
                        ball1[i].res->GetFixtureList()->SetSensor(true);
                    }
                    else
                    {
                        ball1[i].res->GetFixtureList()->SetSensor(false);
                    }
                }


                if (bulltime<1)
                {
                    bull=false;
                    for (int i=0; i<ball1.size(); i++)
                    {
                        ball1[i].res->GetFixtureList()->SetSensor(false);
                    }

                }
            }

            if (ball1.size()>0)
            {
                for (int i=0; i<ball1.size() ; i++)
                {
                    ball1[i].setRadius(ballsize);
                    float ballorgin = ballsize;
                    ball1[i].setOrigin(ballorgin,ballorgin);
                }
            }

            if (lasers==true)
            {
                lasertime++;
                if ((lasertime%5)== 0 || (lasertime%5)== 10 || (lasertime%5)== 20 || (lasertime%5)== 30 || (lasertime%5)== 40)
                {
                    laser.push_back(Laser(world,p1.getPosition().x,p1.getPosition().y,5,30));
                    laser.back().res->GetFixtureList()->SetSensor(true);
                    laser.back().res->SetType(b2_dynamicBody);
                    laser.back().res->SetLinearVelocity(b2Vec2(0,-10));
                    laser.back().setFillColor(Color(255, 0, 102));

                }
                if ((lasertime/5)==60)
                {
                    laser.push_back(Laser(world,p1.getPosition().x,p1.getPosition().y,5,30));
                    laser.back().res->GetFixtureList()->SetSensor(true);
                    laser.back().res->SetType(b2_dynamicBody);
                    laser.back().res->SetLinearVelocity(b2Vec2(0,-10));
                    laser.back().setFillColor(Color(255, 0, 102));
                    lasertime=0;
                    lasers=false;
                }
            }

            if (Keyboard::isKeyPressed(Keyboard::A) == true)
            {
                p1.setVelocity(Vector2f(-700, 0));
            }

            if (Keyboard::isKeyPressed(Keyboard::D) == true)
            {
                p1.setVelocity(Vector2f(700, 0));
            }

            if (Keyboard::isKeyPressed(Keyboard::A) == false && Keyboard::isKeyPressed(Keyboard::D) == false)
            {
                p1.setVelocity(Vector2f(0, 0));
            }

            if (Keyboard::isKeyPressed(Keyboard::A) == true && Keyboard::isKeyPressed(Keyboard::D) == true)
            {
                p1.setVelocity(Vector2f(0, 0));
            }


            if (Keyboard::isKeyPressed(Keyboard::A) == false && p1.getPosition().x>=xmax)
            {
                p1.setVelocity(Vector2f(0, 0));
            }

            if (Keyboard::isKeyPressed(Keyboard::D) == false && p1.getPosition().x<=xmin)
            {
                p1.setVelocity(Vector2f(0, 0));
            }

            if (ball1.size()>0)
            {
                for (int i = 0; i < bricks.size(); i++)
                {
                    for(int j=0; j<ball1.size(); j++)
                    {
                        if (ball1[j].checkCollision(bricks[i].res) == true)
                        {
                            int powerrangen=rand()%2;
                            if (powerrangen==1)
                            {
                                powerups.push_back(Powerup(world, bricks[i].getPosition().x, bricks[i].getPosition().y, 15.0,15.0));
                                powerups.back().res->GetFixtureList()->SetSensor(true);
                                powerups.back().res->SetLinearVelocity(b2Vec2(0,5));
                                powerups.back().setFillColor(Color(0,255,0));
                            }

                            rpgpoints.push_back(Text("+100",f1,30));
                            rpgpointsy.push_back(bricks[i].getPosition().y);
                            rpgpointsx.push_back(bricks[i].getPosition().x);
                            rpgvisibility.push_back(255);
                            rpglife.push_back(60);

                            bricks[i].removeBody();
                            bricks.erase(bricks.begin() + i);
                            score+=100;
                            if (bricks.size()<=0)
                            {
                                levelup=true;
                                level++;
                            }

                        }
                    }
                }
            }

            for (int i = 0; i < powerups.size(); i++)
            {
                if(p1.checkCollision(powerups[i].res) == true)
                {
                    powerups[i].removeBody();
                    powerups.erase(powerups.begin() + i);
                    int powerrangen2 = rand()%5;

                    if(powerrangen2==4)
                    {
                        if (life<5)
                        {
                            life+=1;
                            if(life<2)
                            {
                                life+=1;
                            }
                        }
                        else
                        {
                            powerrangen2== rand()%5;
                        }
                    }

                    if (powerrangen2==0)
                    {
                        lasers=true;
                    }

                    if (powerrangen2==1)
                    {
                        doubleball=true;
                    }
                    if (powerrangen2==2)
                    {
                        bull=true;
                        bulltime= 100;
                    }

                    if (powerrangen2==3)
                    {
                        longer=true;
                        longertime=300;
                    }
                }
            }

            if (longer==true)
            {
                longertime-=1;
                p1.resetSize(250.0,10.0);
                xmin=125;
                xmax=675;
                if (longertime<1)
                {
                    p1.resetSize(150.0,10.0);
                    xmin=75;
                    xmax=725;
                    longer=false;
                }
            }

            if (laser.size()>0)
            {
                for (int j = 0; j < bricks.size(); j++)
                {
                    for (int i = 0; i < laser.size(); i++)
                    {
                        if(laser[i].checkCollision(bricks[j].res) == true)
                        {
                            laser[i].removeBody();
                            laser.erase(laser.begin() + i);

                            rpgpoints.push_back(Text("+100",f1,30));
                            rpgpointsy.push_back(bricks[j].getPosition().y);
                            rpgpointsx.push_back(bricks[j].getPosition().x);
                            rpgvisibility.push_back(255);
                            rpglife.push_back(60);

                            bricks[j].removeBody();
                            bricks.erase(bricks.begin() + j);
                            score+=100;
                            if (bricks.size()<=0)
                            {
                                levelup=true;
                                level++;
                            }

                        }
                    }
                }
            }
            for (int i=0; i<laser.size(); i++)
            {
                if (laser[i].getPosition().x<20)
                {
                    laser[i].removeBody();
                    laser.erase(laser.begin() + i);
                }
            }

            if (levelup ==true)
            {
                startcreate=true;
            }

            for (int i=0; i<rpgpoints.size(); i++)
            {
                rpgpoints[i].setPosition(rpgpointsx[i]-20,rpgpointsy[i]);
                rpgpoints[i].setFillColor(Color(255,255,255,rpgvisibility[i]));
            }

            for (int i=0; i<rpgpoints.size(); i++)
            {
                rpgpointsy[i]-=1;
                rpglife[i]-=1;
                rpgvisibility[i]-=4.26;
                if(rpgvisibility[i]<1)
                {
                    rpglife.erase(rpglife.begin() + i);
                    rpgpoints.erase(rpgpoints.begin() + i);
                    rpgpointsx.erase(rpgpointsx.begin() + i);
                    rpgpointsy.erase(rpgpointsy.begin() + i);
                    rpgvisibility.erase(rpgvisibility.begin()+i);

                }
            }

            pointsw.setCharacterSize(25);
            pointsw.setPosition(20,558);
            pointsw.setString("Score:");
            pointsw.setFillColor(Color(255, 0, 102));

            pointsn.setCharacterSize(25);
            pointsn.setPosition(125,558);
            pointsn.setString(to_string(score));
            pointsn.setFillColor(Color(255, 0, 102));

            livesw.setCharacterSize(25);
            livesw.setPosition(660,558);
            livesw.setString("Lives:");
            livesw.setFillColor(Color(255, 0, 102));

            livesn.setCharacterSize(25);
            livesn.setPosition(760,558);
            livesn.setString(to_string(life));
            livesn.setFillColor(Color(255, 0, 102));

            leveln.setCharacterSize(25);
            leveln.setPosition(460,558);
            leveln.setString(to_string(level));
            leveln.setFillColor(Color(255, 0, 102));

            levelw.setCharacterSize(25);
            levelw.setPosition(350,558);
            levelw.setString("Level:");
            levelw.setFillColor(Color(255, 0, 102));



            window.clear(); //clears the screen
            world.Step(1.0/60, int32(8), int32(3));
            if (ball1.size()>0)
            {
                for (int i=0; i< ball1.size(); i++)
                {
                    ball1[i].updatePosition();
                }
            }

            if (laser.size()>0)
            {
                for (int i=0; i< laser.size(); i++)
                {
                    laser[i].updatePosition();
                }
            }

            if (powerups.size() > 0)
            {
                for (int i = 0; i < powerups.size(); i++)
                {
                    powerups[i].updatePosition();
                }
            }
            p1.updatePosition();


            window.draw(spaceback);

            for (auto &i : bricks)
                window.draw(i);
            for (auto &i : powerups)
                window.draw(i);
            for (int i=0; i<rpgpoints.size(); i++)
            {
                window.draw(rpgpoints[i]);
            }
            if (ball1.size()>0)
            {
                for (auto &i : ball1)
                    window.draw(i);
            }
            if (laser.size()>0)
            {
                for (auto &i : laser)
                    window.draw(i);
            }
            if (ballshape.size()>0)
            {
                for (auto &i : ballshape)
                    window.draw(i);
            }
            if (startoption==true)
            {
                window.draw(pressspace);
            }
            window.draw(leveln);
            window.draw(levelw);
            window.draw(p1);
            window.draw(pointsn);
            window.draw(pointsw);
            window.draw(livesw);
            window.draw(livesn);

            for (auto &i : walls)
                window.draw(i);

        }

        if (play==false && gameover==false)
        {
            title.setCharacterSize(66);
            title.setFont(f1);
            title.setPosition(115,170);
            title.setString("RETRO BREAKER");

            playw.setCharacterSize(56);
            playw.setFont(f1);
            playw.setPosition(315,290);
            playw.setString("PLAY");

            int mousex=Mouse::getPosition(window).x;
            int mousey=Mouse::getPosition(window).y;

            if (mousex>315 && mousex<490 && mousey>300 && mousey<356)
            {
                playw.setColor(Color::Red);
                if (Mouse::isButtonPressed(Mouse::Left))
                {
                    startcreate=true;
                    play=true;
                }
            }
            else
            {
                playw.setColor(Color::White);
            }

            sf::Sprite spaceback(Startscreen,sf::IntRect(xstart,ystart,740,416));
            xstart+=740;
            if(ystart<1664)
            {
                if(xstart >= 2960)
                {
                    xstart=0;
                    ystart+=416;
                }
            }
            else if(xstart>=1480)
            {
                ystart=0;
                xstart=0;
            }
            spaceback.setScale(1.4444,1.4444);
            spaceback.setPosition(-140,0);

            window.clear(); //clears the screen
            world.Step(1.0/60, int32(8), int32(3));
            window.draw(spaceback);
            window.draw(title);
            window.draw(playw);
        }

        if (gameover==true)
        {
            p1.setVelocity(Vector2f(0.0,0.0));

            gameoverw.setCharacterSize(86);
            gameoverw.setFont(f1);
            gameoverw.setPosition(144,100);
            gameoverw.setString("GAME OVER");

            retryw.setCharacterSize(66);
            retryw.setFont(f1);
            retryw.setPosition(255,420);
            retryw.setString("RETRY?");

            gameoverscore.setCharacterSize(66);
            gameoverscore.setFont(f1);
            gameoverscore.setPosition(210,250);
            gameoverscore.setString("Score:");

            gameoverscoren.setCharacterSize(66);
            gameoverscoren.setFont(f1);
            gameoverscoren.setPosition(490,250);
            gameoverscoren.setString(to_string(score));

            gameoverleveln.setCharacterSize(66);
            gameoverleveln.setFont(f1);
            gameoverleveln.setPosition(530,330);
            gameoverleveln.setString(to_string(level));

            gameoverlevelw.setCharacterSize(66);
            gameoverlevelw.setFont(f1);
            gameoverlevelw.setPosition(250,330);
            gameoverlevelw.setString("Level:");

            int mousex=Mouse::getPosition(window).x;
            int mousey=Mouse::getPosition(window).y;

            if (mousex>255 && mousex<545 && mousey>440 && mousey<485)
            {
                retryw.setColor(Color::Red);
                if (Mouse::isButtonPressed(Mouse::Left))
                {
                    play=true;
                    startcreate=true;
                    gameover=false;
                    score=0;
                    level=1;
                    life=5;

                }
            }
            else
            {
                retryw.setColor(Color::White);
            }

            sf::Sprite endback(gameoverback,sf::IntRect(xover,yover,1100,619));
            xover+=1100;
            if (xover>=2200)
            {
                xover=0;
                yover+=619;
            }
            if (yover>1850)
            {
                yover=0;
            }
            endback.setPosition(-150,0);



            window.clear(); //clears the screen
            world.Step(1.0/60, int32(8), int32(3));
            window.draw(endback);
            window.draw(gameoverw);
            window.draw(retryw);
            window.draw(gameoverscore);
            window.draw(gameoverscoren);
            window.draw(gameoverlevelw);
            window.draw(gameoverleveln);
        }


        window.display();   //displays everything on the video card to the monitor
    }   //ends the game loop

    return 0;
}
