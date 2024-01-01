/*                                                                                                                         
                                                                                                                             
PPPPPPPPPPPPPPPPP   DDDDDDDDDDDDD              &&&&&&&&&&    DDDDDDDDDDDDD        TTTTTTTTTTTTTTTTTTTTTTTPPPPPPPPPPPPPPPPP   
P::::::::::::::::P  D::::::::::::DDD          &::::::::::&   D::::::::::::DDD     T:::::::::::::::::::::TP::::::::::::::::P  
P::::::PPPPPP:::::P D:::::::::::::::DD       &::::&&&:::::&  D:::::::::::::::DD   T:::::::::::::::::::::TP::::::PPPPPP:::::P 
PP:::::P     P:::::PDDD:::::DDDDD:::::D     &::::&   &::::&  DDD:::::DDDDD:::::D  T:::::TT:::::::TT:::::TPP:::::P     P:::::P
  P::::P     P:::::P  D:::::D    D:::::D    &::::&   &::::&    D:::::D    D:::::D TTTTTT  T:::::T  TTTTTT  P::::P     P:::::P
  P::::P     P:::::P  D:::::D     D:::::D    &::::&&&::::&     D:::::D     D:::::D        T:::::T          P::::P     P:::::P
  P::::PPPPPP:::::P   D:::::D     D:::::D    &::::::::::&      D:::::D     D:::::D        T:::::T          P::::PPPPPP:::::P 
  P:::::::::::::PP    D:::::D     D:::::D     &:::::::&&       D:::::D     D:::::D        T:::::T          P:::::::::::::PP  
  P::::PPPPPPPPP      D:::::D     D:::::D   &::::::::&   &&&&  D:::::D     D:::::D        T:::::T          P::::PPPPPPPPP    
  P::::P              D:::::D     D:::::D  &:::::&&::&  &:::&  D:::::D     D:::::D        T:::::T          P::::P            
  P::::P              D:::::D     D:::::D &:::::&  &::&&:::&&  D:::::D     D:::::D        T:::::T          P::::P            
  P::::P              D:::::D    D:::::D  &:::::&   &:::::&    D:::::D    D:::::D         T:::::T          P::::P            
PP::::::PP          DDD:::::DDDDD:::::D   &:::::&    &::::&  DDD:::::DDDDD:::::D        TT:::::::TT      PP::::::PP          
P::::::::P          D:::::::::::::::DD    &::::::&&&&::::::&&D:::::::::::::::DD         T:::::::::T      P::::::::P          
P::::::::P          D::::::::::::DDD       &&::::::::&&&::::&D::::::::::::DDD           T:::::::::T      P::::::::P          
PPPPPPPPPP          DDDDDDDDDDDDD            &&&&&&&&   &&&&&DDDDDDDDDDDDD              TTTTTTTTTTT      PPPPPPPPPP          
                                                                                                                             
Physics Demostration and Display Testing Program (v1.1 Experimental)
by Eco_Man_CZ (Matt)
powered by the u8g2 library by olikraus

--You can use this code in your own projects, but when making the project public remeber to credit, me thank you :)--
--Вы можете использовать этот код в своих собственных проектах, но, делая проект общедоступным, не забудьте поблагодарить меня :)--

|______                   _     _             __                                    _               
||  __ \                 | |   | |           / _|                                  (_)              
|| /_/ /  ___   __ _   __| |   | |__    ___ | |_   ___   _ __   ___     _   _  ___  _  _ __    __ _ 
||    /  / _ \ / _` | / _` |   | '_ \  / _ \|  _| / _ \ | '__| / _ \   | | | |/ __|| || '_ \  / _` |
|| |\ \ |  __/| (_| || (_| |   | |_) ||  __/| |  | (_) || |   |  __/   | |_| |\__ \| || | | || (_| |
|\_| \_| \___| \__,_| \__,_|   |_.__/  \___||_|   \___/ |_|    \___|    \__,_||___/|_||_| |_| \__, |
|                                                                                              __/ |
|                                                                                             |___/ 
Hello! its me Matt, i'm the creator of this program.This program was created for testing my new 128x64 lcd display
i got for christmas and because i'm a sucker for physics, programing challenges and logical thinking i decided to
create this little program for fun and for me to learn something new! Now the only things you should change to use
your own display is the dw variable, dh variable and the display driver on line 48 BUT! i have included more 
variables to play around with the physics simulations! i have also tried my best to comment on everything,
So i guess you can start doing stuff!

Also if have any issues dm me on reddit username: Eco_Man_Redditer

*/
#include <Arduino.h>
#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C disp(U8G2_R0, /* reset=*/U8X8_PIN_NONE, 22, 21);  //!!edit this to your own controller!!

uint8_t currx = 0;        //*used for properly spacing text using the dprint function
uint8_t curry = 7;        //*this code was ripped from another of my codes
uint8_t ballacc = 0;      //ball acceleration for the bouncing ball demo
const uint8_t g = 10;     //gravitational acceleration (earth rounded)
uint8_t balltracervar = 0;//variable for the ball tracing in the ball example
uint8_t sd = 0;           //smallest display dimesion, in a 128x64 display its gonna be 64, in a 320x240 its going to be 240 etc...

float velx = 1;           //horizontal velocity used in the bouncing pixel demo
float vely = 1;           //vertical velocity used in the bouncing pixel demo
float demox = 2;          //horizontal position used in the bouncing pixel demo
float demoy = 2;          //vertical position used in the bouncing pixel demo
float focallen = 10;      //Focal length, used to calculate the weak perspective projection used in the 3d cube demo
const float startballvelx = 1.6;            //start horizontal ball velocity used in the bouncing ball demo
const float startballvely = 0;              //start vertical ball velocity used in the bouncing ball demo
const float startballx = 2;                 //start horizontal ball position used in the bouncing ball demo
const float startbally = 2;                 //start vertical ball position used in the bouncing ball demo
const float ballbounciness = 0.67;          //determines how much velocity gets kept when the ball hits the floor (1 = 100% / 0.5 = 50% / 0 = 0%)
const float ballweight = 0.44;              //ball weight determines the gravitational force of the ball
const float pendweight = 1.2;               //weight of pendulum bob
const float pendanglestart = 45;            //starting angle of the pendulum arm realtive to the y axis
const float pendarmlen = 45;                //length of pendulum arm
const float penddamp = 0.008;               //dampening factor of the pendulum(friction and other losses)
const float springarmlen = 32;              //length of the spring in the spring demo
const float springbobweight = 20;           //weight of the bob attached to the string in the spring demo
const float springconstant = 35;            //spring constant (string strenght) used in the spring demo
const float springdampening = 0.008;        //spring dampening factor(really small friction anad other losses)


struct vector3{float x,y,z;};               //vector3 a variable type for 3d points
struct vector2{float x,y;};                 //vector2 a variable type for 2d points

vector3 cube3d[8] = {                       //points of the 3d cube
  {-1,-1,-1},
  {-1,-1,1},
  {1,-1,-1},
  {1,-1,1},
  {-1,1,-1},
  {-1,1,1},
  {1,1,-1},
  {1,1,1}
};

vector2 point2d[8];                         //projected points of the 3d cube

vector2 traces[100];                        //trace points in the bouncing ball demo

const vector2 edges[14] = {                 //contains what points of the 3d cube should be connected with a line
  {0,1},
  {0,2},
  {1,3},
  {3,2},
  {0,4},
  {1,5},
  {2,6},
  {3,7},
  {4,6},
  {4,5},
  {5,7},
  {6,7},
  {0,7},
  {0,3}
};

#define fovangle 80                         //fov angle for the 3d cube demo
#define fontdef u8g2_font_4x6_tf            //font, pretty self explanitory
#define fontstep 7                          //max font height + 1 used for the dprint function
#define dw 128                              //display width !!edit this for your own display!!
#define dh 64                               //display height  !!edit this for your own display!!

//Display Interface ==================================================================================
void dprint(String string = "def_string",uint8_t x = 0,uint8_t y = fontstep,bool setcursor = false){  //dprint same as the u8g2.drawStr but it atomaticly fills in the x,y position
    if (setcursor){disp.setCursor(x,y);currx = x;curry = y;}  //if the user wants to set x,y position then set it
    else{curry += fontstep; disp.setCursor(currx,curry);}     //if not then set the x,y position acording to currx and curry variables also increment curry by fontstep
    disp.println(string);                                     //print the string
    disp.sendBuffer();                                        //copy the memory buffer to the display buffer
}

void dpp(uint8_t x = 0,uint8_t y = 0){      //short for the disp.drawPixel function just for conviniece
  disp.drawPixel(x,y);
}

void dcls(){                                //short function for clearing the screen
    disp.clear();                           //clear the screen
    disp.setCursor(0,fontstep);             //set the cursor position to 0,fontstep
    currx = 0;                              //set currx to 0
    curry = 0;                              //set curry to 0
}

//Math Functions =====================================================================================
vector3 otocitx (float angle,vector3 point){                //function for rotating a point around the x axis
  vector3 returnval;                                        //define a return value (vector3)
  returnval.x = point.x;                                    //x value is the same
  returnval.y = cos(angle) * point.y - sin(angle) * point.z;//calculate the y value of the point after rotating
  returnval.z = sin(angle) * point.y + cos(angle) * point.z;//calculate the z value of the point after rotating
  return returnval;                                         //returning the calculated point position after rotating
}

vector3 otocity (float angle,vector3 point){                //function for rotating a point around the y axis
  vector3 returnval;                                        //define a return value (vector3)
  returnval.x = cos(angle) * point.x + sin(angle) * point.z;//calculate the x value of the point after rotating
  returnval.y = point.y;                                    //y value is the same
  returnval.z = cos(angle) * point.z - sin(angle) * point.x;//calculate the z value of the point after rotating
  return returnval;                                         //returning the calculated point position after rotating
}

vector3 otocitz (float angle,vector3 point){                //function for rotating a point around the z axis
  vector3 returnval;                                        //define a return value (vector3)
  returnval.x = cos(angle) * point.x - sin(angle) * point.y;//calculate the x value of the point after rotating
  returnval.y = sin(angle) * point.x + cos(angle) * point.y;//calculate the y value of the point after rotating
  returnval.z = point.z;                                    //z value is the same
  return returnval;                                         //returning the calculated point position after rotating
}

vector2 projectionxy(float fov,vector3 point){              //easy way to convert 3d to 2d is using wweak perspective projection
  return vector2{(dw/2) + (fov * point.x)/(fov + point.z) * 16,(dh/2) + (fov * point.y)/(fov + point.z) * 16};//formula used to calculate the x,y position on the screen using the
}                                                                                                             //x,y,z position of the point to project

void setup() {

  bool dispdone = disp.begin();             //if the display init was sucessful = 1 else = 0
  disp.clear();                             //clear the screen
  disp.enableUTF8Print();                   //enable utf8 printing
	disp.setFont(fontdef);                    //set the font to fontdef
	disp.setFontDirection(0);                 //set font direction to 0
  dprint("Display init. done...",0,fontstep,true);//print that the display init is done

	Serial.begin(115200);                     //begin the serial communication
  Serial.print("disp init.");               // *
  if(dispdone){ Serial.println("done...");} // *write to the serial monitor if the display library init. was sucessful
  else{Serial.println("fail");}             // *

  Serial.println("Serial init. done...");   //write to serial that serial init is done
  dprint("Serial init. done...");           //print on the display that serial init is done

  if(dw <= dh){sd = dw;}else{sd = dh;}      //find the smallest dimension
  focallen = tan((fovangle/2)*PI/180) * dw/2;//calculate the focal length from the fov and screen width

  delay(1000);                              //wait for a second
  dcls();                                   //clear the display
}
void loop() {

  for(int i = 0;i <= 500;i++){              //loop the below code for 500 iterations
    disp.clearBuffer();                       //clear the memory buffer
    disp.drawStr(0,6,"Bouncing Pixel:");      //draw the title in the upper right corner
    dpp(demox,demoy);                         //print a dot at demox and demoy
    if (demox > dw){demox = dw;}              // *
    if (demoy > dh){demoy = dh;}              // *clip the pixel if it goes out of bounds
    if (demox < 0){demox = 0;}                // *
    if (demoy < 0){demoy = 0;}                // *
    if (demox > dw-1 || demox < 1){velx *= -1;}//if the pixel hits a wall reverse its x velocity
    if (demoy > dh-1 || demoy < 1){vely *= -1;}//if the pixel hits the floor or ceiling reverse its y velocity
    demox += velx / 8;                        //add the x velocity to the x position
    demoy += vely / 8;                        //add the y velocity to the y position
    velx += (-1,1);                           //change the x velocity by random for more fun
    vely += (-1,1);                           //change the y velocity by random for more fun
    disp.sendBuffer();                        //send the memory buffer to the display buffer
  }
  
  for(int i = 0;i <=(360*4);i += 5){        //loop the below code for 4 full rotations 
    disp.clearBuffer();                       //clear the memory buffer
    disp.drawStr(0,6,"Sin + Cos:");           //draw the title in the upper right corner
    dpp(dw/2,sd/2*sin(i*PI/180)+dh/2);        //calculate the sin of the current angle and show it with a pixel
    dpp(sd/2*cos(i*PI/180)+dw/2,dh/2);        //calculate the cos of the current angle and show it with a pixel
    dpp(sd/2*cos(i*PI/180)+dw/2,sd/2*sin(i*PI/180)+dh/2);//calculate the sin and cos and show it wwith a pixel
    disp.sendBuffer();                        //send the memory buffer to the display buffer
  }

  for(int i = 0;i <=(360*4);i += 5){        //loop the below code for 4 full rotations 
    disp.clearBuffer();                       //clear the memory buffer
    disp.drawStr(0,6,"Rotating Line:");       //draw the title in the upper right corner
    disp.drawLine(sd/2*cos(i*PI/180)+dw/2,sd/2*sin(i*PI/180)+dh/2,sd/2*cos((i+180)*PI/180)+dw/2,sd/2*sin((i+180)*PI/180)+dh/2);
    // /\
    //calculate the sin and cos + the sin and cos with the angle shifted by PI and show it in a line
    disp.sendBuffer();                        //send the memory buffer to the display buffer
  }

  for(int i = 0;i <=(360*4);i += 5){        //loop the below code for 4 full rotations 
    disp.clearBuffer();                       //clear the memory buffer
    disp.drawStr(0,6,"Rotating triangle:");   //draw the title in the upper right corner
    disp.drawTriangle(sd/2*cos(i*PI/180)+dw/2,sd/2*sin(i*PI/180)+dh/2,sd/2*cos((i+(360/3))*PI/180)+dw/2,sd/2*sin((i+(360/3))*PI/180)+dh/2,sd/2*cos((i+(360/3*2))*PI/180)+dw/2,sd/2*sin((i+(360/3*2))*PI/180)+dh/2);
    // /\
    //calculate the sin and cos + the sin and cos shifted by 1/3 of the pi + the sin and cos shifted by 2/3 of the pi
    disp.sendBuffer();                        //send the memory buffer to the display buffer
  }

  for(int i = 0;i <= 10;i++){               //repeat the code below 10 times
    uint8_t rnd = random(0,3);
    for(uint8_t t = 0;t <= 40;t++){           //repeat the codee below 40 times
      disp.clearBuffer();                       //clear the memory buffer
      for(uint8_t x = 0;x < (sizeof(cube3d)/sizeof(cube3d[0]));x++){//repeat the below code for the number of points in the cube
        switch (rnd){                                //pick a random number from 0 to 2
        case 0:                                      //if the number is 0 then:
          disp.drawStr(0,6,"Rotating 3D Cube(X):");    //draw the title in the upper right corner
          cube3d[x] = otocitx(PI/180,cube3d[x]);       //rotate the point in the cube by one degree
        break;
        case 1:                                      //if the number is 1 then:
          disp.drawStr(0,6,"Rotating 3D Cube(Y):");    //draw the title in the upper right corner
          cube3d[x] = otocity(PI/180,cube3d[x]);       //rotate the point in the cube by one degree
        break;
        case 2:                                      //if the number is 2 then:
          disp.drawStr(0,6,"Rotating 3D Cube(Z):");    //draw the title in the upper right corner
          cube3d[x] = otocitz(PI/180,cube3d[x]);       //rotate the point in the cube by one degree
        break;
        }
        point2d[x] = projectionxy(focallen,cube3d[x]);//project the point
        if(point2d[x].x > dw){point2d[x].x = dw;} // *
        if(point2d[x].y > dh){point2d[x].y = dh;} // *clip the 2d point if it gets out of bounds
        if(point2d[x].x < 0){point2d[x].x = 0;}   // *
        if(point2d[x].y < 0){point2d[x].y = 0;}   // *
      }
      for(int z = 0;z < (sizeof(edges)/sizeof(edges[0]));z++){//repeat the below code for the number of egdes in the cube
        disp.drawLine(point2d[(int)edges[z].x].x,point2d[(int)edges[z].x].y,point2d[(int)edges[z].y].x,point2d[(int)edges[z].y].y);
        // /\
        //draw a line between the two points
      }
      disp.sendBuffer();                        //send the memory buffer to the display buffer
    }
  }

  float ballvelx = startballvelx;           // *
  float ballvely = startballvely;           // *define the ball variables
  float ballx = startballx;                 // *and reset the variables back to default
  float bally = startbally;                 // *
  for(uint8_t i = 0;i <= 100;i++){          //repeat the below code 100 times
    int f;                                    //define a force variable
    if(bally <= dh - 2){f = ballweight * g;}  //if the ball is in the air then apply a gravitational force based on weight and gravitational acceleration
    else{f = 0;}                              //if the ball is on the floor then the Normal Force cancels out the gravitational force and the resulting force is 0 Newtons
    ballacc = f / ballweight;                 //calculate the ball acceleration from the formula: a = f/m wich is a modifed form of f = ma
    ballvely += ballacc;                      //apply the acceleration to the velocity of the ball
    ballx += ballvelx;                        //apply the x velocity to the x position of the ball
    bally += (ballvely/10);                   //apply the y velocity to the y position of the ball
    if(bally > dh - 2 && ballvely > 0){ballvely *= -ballbounciness;ballacc = 0;ballvelx -= 0.03;}
    // /\
    //when on floor then: reverse the y velocity, and multiply the ball velocity by the ball bounciness,ball acceleration set to 0 
    //(ball is no longer accelerating towards the ground) and reduce the ball x velocity by its losses (lets say about 0.03 for example)
    if(ballx > dw - 2){ballvelx *= -1;}       //when the ball hits the left wall then: reverse the x velocity
    disp.clearBuffer();                       //clear the memory buffer
    disp.drawStr(0,6,"Bouncing Ball:");       //draw the title in the upper right corner
    //Serial.println("Velocity y:" + String(ballvely));    // *diagnostic info sent to serial monitor
    //Serial.println("Ball x:" + String(ballx));           // *
    //Serial.println("Ball y:" + String(bally));           // *
    //Serial.println("Force:" + String(ballweight * g));   // *
    //Serial.println("Acc:" + String(f / ballweight));     // *
    traces[balltracervar] = {ballx,bally};    //log the current position to the traces variable
    if(balltracervar >= (sizeof(traces)/sizeof(traces[0])) - 1){balltracervar = 0;}//if the ball trace variable is equal to or higer than the size of the traces variable se it to 0
    balltracervar++;                          //count up the ball trace variable
    for(uint8_t f = 0;f < (sizeof(traces)/sizeof(traces[0]));f++){//repeat the below code for the size of the traces variables
      dpp(traces[f].x,traces[f].y);             //print all the points in the traces variable
    }
    dpp(ballx,bally);                         //print a pixel on the current position
    disp.drawCircle(ballx,bally,1);           //print a circle on the current position
    disp.sendBuffer();                        //send the memory buffer to the display buffer
  }
  for(uint8_t f = 0;f < (sizeof(traces)/sizeof(traces[0]));f++){//repeat the below code for the size of the traces variables
    traces[f] = {0,0};                          //reset it to 0
  }

  float AngularV = 0;                       //define an angular velocity variable
  float AngularA = 0;                       //define an angular acceleration variable
  float force = 0;                          //define an force variable
  float pendangle = pendanglestart;         //define an pendulum angle and set it to the starting angle defined at line 68
  for(uint16_t i = 0;i <= 500;i++){         //repeat the code below 500 times:
    force = sin(pendangle * PI/180) * pendweight * g;//calculate the angular force using trigometry
    AngularA = -1 * force / pendarmlen;       //the longer the arm the smaller the angular acceleration otherwise it looks and behaves weirdly

    AngularV *= 1 - penddamp;                 //damp the the current velocity

    AngularV += AngularA;                     //apply the angular acceleration to the angular velocity
    pendangle += AngularV;                    //apply the angular velocity to the angle

    disp.clearBuffer();                       //clear the memory buffer
    disp.drawStr(0,6,"Simulated Pendulum:");  //draw the title in the upper right corner
    disp.drawLine(dw/2,6,pendarmlen*sin((pendangle)*PI/180)+dw/2,pendarmlen*cos((pendangle)*PI/180));//draw a line between the bob and the orgin
    disp.drawCircle(pendarmlen*sin((pendangle)*PI/180)+dw/2,pendarmlen*cos((pendangle)*PI/180),6);//draw a circle on the position of the bob
    disp.sendBuffer();                        //send the memory buffer to the display buffer
  }

  float armdiff = 0;                        //define an delta of the spring length
  float Fk = 0;                             //define an Spring force
  float Fg = 0;                             //define an Gravitational Force
  float a = 0;                              //define an bob y acceleration
  float v = 0;                              //define an bob y velocity
  for(uint16_t i = 0;i <= 500;i++){         //repeat the code below 500 times:
    Fg = springbobweight * g;                 //calculate the gravitational force using Fg = m * g
    Fk = armdiff * -springconstant;           //calculate the spring force using Fk = Δl * k
    a = (Fg+Fk) / springbobweight;            //calculate the acceleration using a = F / m
    v += a / 10;                              //apply the bob acceleration to the bob velocity
    armdiff += v;                             //apply the bob velocity to the Δl of the spring
    armdiff  *= (1 - springdampening);        //dampen the spring so it doesnt resonate forever
    disp.clearBuffer();                       //clear the memory buffer
    disp.drawStr(0,6,"Simulated Spring:");    //draw the title in the upper right corner
    disp.drawLine(dw/2,6,dw/2,springarmlen+armdiff);//draw a line between the bob and the orgin
    disp.drawCircle(dw/2,springarmlen+armdiff,6);//draw a circle on the position of the bob
    /*Serial.println("Velocity y:" + String(v));        // *diagnostic info sent to serial monitor
    Serial.println("Acceleration:" + String(a));        // *
    Serial.println("Force k:" + String(Fk));            // *
    Serial.println("Force g:" + String(Fg));            // *
    Serial.println("Arm diffrencee:" + String(armdiff));// */
    disp.sendBuffer();                        //send the memory buffer to the display buffer
  }
}

//did you read through it? if yes then thank you because commenting took way longer than it should have. :D