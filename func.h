
#include "vars.h"


void resetGame() {
  player.score = 0;
  oppo.score = 0;
  player.y = HEIGHT / 2 - player.height;
  ball.x = 64;
  ball.right = false;
}
template<typename T>
//This animaton function takes a sprite and runs through all its frames, then starts over at frame 0
void animateSprite(T& structObj, uint8_t T::*cframe, uint8_t T::*framec, int T::*counter, uint8_t T::*wait) {
  if (structObj.*counter % (FRAME(structObj.*wait)) == 0) {
    if (structObj.*cframe < structObj.*framec) {
      structObj.*cframe += 1;
    } else {
      structObj.*cframe = 0;
    }
  }
  structObj.*counter += 1;
}


template<typename T>
//This animation function takes a sprite and runs trough all its frames in incremental order, then when reaching the final frame, in decremental order back to zero, ad infinitum
void animateFWB(T& structObj, uint8_t T::*cframe, uint8_t T::*framec, int T::*counter, uint8_t T::*wait, bool T::*inc) {
  if (structObj.*counter % (FRAME(structObj.*wait)) == 0) {
    if (structObj.*cframe == structObj.*framec) {
      structObj.*inc = false;
    }
    if (structObj.*cframe == 0) {
      structObj.*inc = true;
    }
    if (structObj.*inc) {
      if (structObj.*cframe < structObj.*framec) {
        structObj.*cframe += 1;
      }
    } else {
      if (structObj.*cframe > 0) {
        structObj.*cframe -= 1;
      }
    }
  }
  structObj.*counter += 1;
}

void playerInput() {


  if (arduboy.pressed(LEFT_BUTTON)) {


  } else if (arduboy.pressed(DOWN_BUTTON)) {

  } else if (arduboy.pressed(RIGHT_BUTTON)) {

  } else if (arduboy.pressed(UP_BUTTON)) {

  } else {
  }
}


void updatePlayerSprite() {
  if (!arduboy.pressed(UP_BUTTON) || !arduboy.pressed(DOWN_BUTTON)) {
    player.sprite = MonkeyIdleEast;
    //player.currentframe = 0;
    player.framecount = 2;
  } else {
    player.sprite = MonkeyWalkEast;
    //player.currentframe = 0;
    player.framecount = 3;
  }
}


void update() {
  if (ball.right) {
    ball.x++;
  } else {
    ball.x--;
  }
  if (ball.down) {
    ball.y++;
  }
  if (ball.up) {
    ball.y--;
  }
  if (ball.y == 0) {
    ball.down = true;
    ball.up = false;
    /*if (random(0,3)==1){
          ball.right=true;
        } else {ball.right=false;}*/
  }
  if (ball.y == HEIGHT - ball.size) {
    ball.down = false;
    ball.up = true;
    /*if (random(0,3)==1){
          ball.right=true;
        }
        else {ball.right=false;}*/
  }
  switch (screen) {
    case Screen::Splash:
      if (startcounter != 0) {
        startcounter--;
      } else {
        screen = Screen::Title;
      }
      break;
    case Screen::Title:
      animateSprite(Abutton, &Sprite::currentframe, &Sprite::framecount, &Sprite::counter, &Sprite::framewait);
      animateSprite(Bbutton, &Sprite::currentframe, &Sprite::framecount, &Sprite::counter, &Sprite::framewait);

      if (ball.x == 0) {
        ball.right = true;
      }
      if (ball.x == WIDTH - ball.size) {
        ball.right = false;
      }
      if (arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON)) {
        screen = Screen::Game;
      }



      break;

    case Screen::Game:

      // animateSprite(sprite, &Sprite::currentframe, &Sprite::framecount, &Sprite::counter, &Sprite::framewait);
      //animateFWB(heart, &Heart::currentframe, &Heart::framecount, &Heart::counter, &Heart::framewait, &Heart::inc);
      //animateSprite(player, &Player::currentframe, &Player::framecount, &Player::counter, &Player::framewait);

      //updatePlayerSprite();
      //playerInput();


      //-----player bounds-----------|
      if (player.y > HEIGHT - player.height) {  //|
        player.y = HEIGHT - player.height;      //|
      }                                         //|
      if (player.y < 0) {                       //|
        player.y = 0;                           //|
      }                                         //|
      //---------------------------//|
      if (player.y > 0 && (arduboy.pressed(UP_BUTTON))) --player.y;
      if (player.y < 64 && (arduboy.pressed(DOWN_BUTTON))) ++player.y;
      //-------paddle physics/bounds--------|
      if (ball.x == player.x + player.width && player.y < ball.y + ball.size && player.y + player.height > ball.y) {

        if (player.y + player.height / 2 == ball.y + ball.size / 2) {  //if player hits dead center
          ball.down = false;
          ball.up = false;
        }
        if (player.y + player.height / 2 > ball.y + ball.size / 2) {
          ball.down = false;
          ball.up = true;
        }
        if (player.y + player.height / 2 < ball.y + ball.size / 2) {
          ball.up = false;
          ball.down = true;
        }

        ball.right = true;

      }  //if player paddle touches the ball, change directions



      if (ball.x + ball.size == oppo.x + 3 && oppo.y < ball.y + ball.size && oppo.y + oppo.height > ball.y) {


        if (oppo.y + oppo.height / 2 == ball.y + ball.size / 2) {
          ball.down = false;
          ball.up = false;
        }
        if (oppo.y + oppo.height / 2 > ball.y + ball.size / 2) {
          ball.down = false;
          ball.up = true;
        }
        if (oppo.y + oppo.height / 2 < ball.y + ball.size / 2) {
          ball.down = true;
          ball.up = false;
        }

        ball.right = false;



      }  //if oppo touches the ball, change directions

      if (ball.x + ball.size <= 0) {
        oppo.score++;
        ball.x = WIDTH / 2 - ball.size;
      }
      if (ball.x >= WIDTH - ball.size) {
        player.score++;
        ball.x = WIDTH / 2 - ball.size;
      }
      if (oppo.score == 11) {
        face.sprite = monkeymad;

        screen = Screen::Gameover;
      }
      if (player.score == 11) {

        face.sprite = monkeywin;
        screen = Screen::Win;
      }
      //-------------------------------------------------|
      if (ball.y > 64){
        ball.y=64;
        ball.up=true;
        ball.down=false;
      }
      if (ball.y < 0){
        ball.y=0;
        ball.up=false;
        ball.down=true;
      }

      //-----------oppo "AI" --------------------|
      if (ball.x > 100 || random(0, 5) == 1) {
        if (ball.y < oppo.y || random(0, 3) == 3 && oppo.y > 1) {
          oppo.y--;

        } else if (ball.y + ball.size > oppo.y + oppo.height && oppo.y < HEIGHT - oppo.height || random(0, 3) == 2 && oppo.y < HEIGHT - oppo.height) {
          oppo.y++;

        } else {
        }
      }
      //---------------------------------------------|
      

      player.spritey = player.y - 5;
      oppo.spritey = oppo.y - 5;
      updatePlayerSprite();
      animateSprite(player, &Paddle::currentframe, &Paddle::framecount, &Paddle::counter, &Paddle::framewait);
      animateSprite(oppo, &Paddle::currentframe, &Paddle::framecount, &Paddle::counter, &Paddle::framewait);
      animateSprite(ball, &Ball::currentframe, &Ball::framecount, &Ball::counter, &Ball::framewait);
      break;




    case Screen::Gameover:
      if (ball.x == 0) {
        ball.right = true;
      }
      if (ball.x == WIDTH - ball.size) {
        ball.right = false;
      }
      if (arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON)) {
        resetGame();
        screen = Screen::Title;
      }
      break;

    case Screen::Win:
      animateSprite(face, &Sprite::currentframe, &Sprite::framecount, &Sprite::counter, &Sprite::framewait);
      face.x = 64-16;
      if (arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON)) {
        resetGame();
        screen = Screen::Title;
      }
      break;
  }
}


void render() {
  uint16_t currentPlane = arduboy.currentPlane();

  switch (screen) {

    case Screen::Splash:
      SpritesU::drawPlusMaskFX(0, 0, punklogooutlined, FRAME(0));
      break;

    case Screen::Title:


      if (currentPlane <= 0) {  //dark gray
      }

      if (currentPlane <= 1) {  //gray
//arduboy.setCursor(0, 0);
//arduboy.println(mapy);
#ifndef OLED_SH1106
        arduboy.fillScreen(WHITE);
#endif
      }

      if (currentPlane <= 2) {  //white
        //arduboy.setCursor(0, 0);
        //arduboy.print("Banana Pong press start or a or b or blah blah blah");
      }
      SpritesU::drawPlusMaskFX(0, 0, titlecard, FRAME(0));
      SpritesU::drawPlusMaskFX(Abutton.x, Abutton.y, Abutton.sprite, FRAME(Abutton.currentframe));
      SpritesU::drawPlusMaskFX(Bbutton.x, Bbutton.y, Bbutton.sprite, FRAME(Bbutton.currentframe));
      break;

    case Screen::Game:


      if (currentPlane <= 0) {  //dark gray
      }

      if (currentPlane <= 1) {  //gray
        arduboy.fillScreen(WHITE);
      }

      if (currentPlane <= 2) {  //white
        arduboy.setCursor(0, 0);
        arduboy.print("M1:");
        arduboy.print(player.score);
        arduboy.setCursor(100, 0);
        arduboy.print("CPU:");
        arduboy.print(oppo.score);
      }
      SpritesU::drawPlusMaskFX(ball.x, ball.y, ball.sprite, FRAME(ball.currentframe));
      SpritesU::drawPlusMaskFX(player.x, player.y, player.sprite, FRAME(player.currentframe));
      SpritesU::drawPlusMaskFX(oppo.x, oppo.y, oppo.sprite, FRAME(oppo.currentframe));

      break;


    case Screen::Gameover:
      if (currentPlane <= 0) {  //dark gray
        
      }

      if (currentPlane <= 1) {  //gray
       // arduboy.fillScreen(WHITE);
      }

      if (currentPlane <= 2) {  //white
                                //   arduboy.setCursor(0, 0);
                                // arduboy.println(mapx);
                                // arduboy.println(mapy);
                                
        arduboy.setCursor(0, 0);
        arduboy.print("You play like human: \nSlow, clumsy,  \nbanana-less!");
      }

      
      offsetX = random(-2, 3) * intensity;
      offsetY = random(-2, 3) * intensity;
      SpritesU::drawPlusMaskFX(face.x+offsetX, face.y+offsetY, face.sprite, FRAME(face.currentframe));
      break;
      
    case Screen::Win:
      if (currentPlane <= 0) {  //dark gray
      }

      if (currentPlane <= 1) {  //gray
        arduboy.fillScreen(WHITE);
      }

      if (currentPlane <= 2) {  //white
        arduboy.setCursor(0, 0);
        arduboy.println("AYYY you win!!!");
        // arduboy.println(mapy);
      }
      SpritesU::drawPlusMaskFX(face.x, face.y, face.sprite, FRAME(face.currentframe));
      break;
  }
}