// 
// 
// 

#include "Game.h"

void Game::playTune()
{
	tone(22, 32, 500);
	delayMicroseconds(100);
	tone(22, 32, 500);
}

void Game::printCraneData()
{
	Serial.println("    Crane data:");
	Serial.print("        state: ");
	Serial.print(crane.currState);
	Serial.print("        xpos: ");
	Serial.print(crane.getXPos());
	Serial.print("        ypos: ");
	Serial.println(crane.getYPos());
	
	Serial.print("        xLastVel: ");
	Serial.print((int)crane.lastXVelocity);
	Serial.print("        yLastVel: ");
	Serial.println((int)crane.lastYVelocity);
	
	Serial.print("        xCurrVel: ") ;
	Serial.print((int)crane.currXVelocity) ;
	Serial.print("        yCurrVel: ") ;
	Serial.println((int)crane.currYVelocity);
}

Game::Game() : slide(PIN_HAS_PRIZE_SLIDE_E, PIN_HAS_PRIZE_SLIDE_T, PIN_DOOR), crane(A0, A1, PIN_HAS_PRIZE_CRANE)
{
	pinMode(PIN_BUZZER, OUTPUT);
}

bool Game::tryStart()
{
	if(currState != S_GAME_OVER)
		return false;
	
	crane.setState(Crane::S_PLAYING);
	currState = S_PLAYING;
	ledMatrix.clear();
	playTune();
	return true;
}

byte Game::update(bool _catch, bool drop)
{
	Serial.print("game state: ");//debug
	switch (currState)
	{
		case S_GAME_OVER:
			Serial.println("GAME_OVER");//debug
			if(lastResult == R_WON){//LO MANDA A ACTUALIZAR EN LA PANTALLA MAS VECES DE LAS NECESARIAS
				//Para hacer el blinkeo
				if(blinkToggle){
					ledMatrix.paintDot(lastXBeforeCatch, lastYBeforeCatch);
				}else{
					ledMatrix.clearDot(lastXBeforeCatch, lastYBeforeCatch);
				}
				
				if(millis() - lastUpdateBlinked > BLINK_PERIOD){
					blinkToggle = !blinkToggle;
					lastUpdateBlinked = millis();
				}
			}
		return R_NONE;
		case S_PLAYING:
			Serial.println("PLAYING");//debug
			Serial.print("    crane state: ");
			switch (crane.getState())
			{
				case Crane::S_PLAYING:
					Serial.println("PLAYING");//debug
					crane.update();
					ledMatrix.paintDot(crane.getXPos(), crane.getYPos());
					if(_catch){
						crane.setState(Crane::S_CATCHING_PRIZE);
						lastXBeforeCatch = crane.getXPos();
						lastYBeforeCatch = crane.getYPos();
					}
				break;
				case Crane::S_CATCHING_PRIZE:
					Serial.println("CATCHING PRIZE");//debug
					if(crane.update()){
						bool hasPrize = crane.hasPrize();
						Serial.print("************HAS PRIZE: ");
						Serial.println(hasPrize);
						if (crane.hasPrize()){
							currState = S_PLAYING_W_PRIZE;
							crane.setState(Crane::S_PLAYING);
						}
						else{
							currState = S_LOSER_RETRIEVING;
							crane.setState(Crane::S_RETRIEVING);
						} 
					}
				break;
			}
			printCraneData();
		return R_PLAYING;
		case S_PLAYING_W_PRIZE:
			Serial.println("PLAYING_WITH_PRICE");//debug
			crane.update();
			if(crane.hasPrize() == false){
				currState = S_WAIT_FOR_PRIZE;
				stateStartTime = 0xffffffff;
				crane.setState(Crane::S_RESTING);
			}
			if(drop){
				currState = S_DROPPING;
				crane.setState(Crane::S_DROPING_PRIZE);
			}
			printCraneData();
		return R_PLAYING;
		case S_LOSER_RETRIEVING:
			Serial.println("LOSER_RETRIEVING");//debug
			if(crane.update()){
				currState =  S_GAME_OVER;
				ledMatrix.paintSadFace();
				lastResult = R_LOST;
				return R_LOST;
			}
			printCraneData();
		return R_NONE;
		break;
		case S_WINNER_RETRIEVING:
			Serial.println("WINNER_RETRIEVING");//debug
			if(crane.update()){
				currState =  S_GAME_OVER;
				lastResult = R_WON;
				return R_WON;
			}
		break;
		case S_DROPPING:
			Serial.println("DROPING");//debug
			if (crane.update())
			{
				currState = S_WAIT_FOR_PRIZE;
				stateStartTime = 0xffffffff;
				crane.setState(Crane::S_RESTING);
			}
			printCraneData();
		return R_NONE;
		case S_WAIT_FOR_PRIZE:
			Serial.println("WAIT_FOR_PRIZE: ");//debug
			if(stateStartTime == 0xffffffff){
				stateStartTime = millis();
			}
			slide.update();
			if (!slide.getHadPrize() && slide.getHasPrize()){
				Serial.println("Opening slide");
				slide.open();
			}
			//Revisar el flujo con los return NONE; talvez hay una manera mas facil hacer el flujo
			if(slide.getHadPrize() && !slide.getHasPrize() && slide.isDoorOpen()){
				slide.close();
				crane.setState(Crane::S_RETRIEVING);
				currState = S_WINNER_RETRIEVING;
				return R_NONE;
			}
			if(millis() - stateStartTime > PRIZE_WAIT_PERIOD && !slide.isDoorOpen()){
				crane.setState(Crane::S_RETRIEVING);
				currState = S_LOSER_RETRIEVING;
				return R_NONE;
			}
		return R_NONE;
	}
	//slide.updateServo();//Chapus horrible para el servo
}

Game::setup()
{
	slide.setup();
}

