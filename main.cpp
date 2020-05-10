/*
Console executable, it create a BullCowClass
*/


#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

//to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
void PrintBack(FText);
bool AskToPlayAgain();
void PrintGameSummary(int32 x);

//instanciate a game, which uses across game
FBullCowGame BCGame;

int main(void)
{
	PrintIntro();
	do
	{
				
		PlayGame();
	} while (AskToPlayAgain() == true);
	return 0;
}

//introduce the game
void PrintIntro()
{

	int32 WORD_LENGTH = BCGame.GetHiddenWordLength();
	std::cout << "\nWelcome to Bulls and Cows, a fun word game!\n";

	std::cout << "                                        /;    ;\\ \n";
	std::cout << "                                    __  \\\\____// \n";
	std::cout << "                                   /{_\\_/   `'\\____ \n";
	std::cout << "                                   \\___   (o)  (o  } \n";
	std::cout << "        _____________________________/          :--'    \n";
	std::cout << "    ,-,'`@@@@@@@@       @@@@@@         \\_    `__\\ \n";
	std::cout << "   ;:(  @@@@@@@@@        @@@             \\___(o'o) \n";
	std::cout << "   :: )  @@@@          @@@@@@        ,'@@(  `===='         \n";
	std::cout << "   :: : @@@@@:          @@@@         `@@@: \n";
	std::cout << "   :: \\  @@@@@:       @@@@@@@)    (  '@@@' \n";
	std::cout << "   ;; /\\      /`,    @@@@@@@@@\\   :@@@@@)                    \n";
	std::cout << "   ::/  )    {_----------------:  :~`,~~; \n";
	std::cout << "  ;;'`; :   )                  :  / `; ; \n";
	std::cout << " ;;;; : :   ;                  :  ;  ; :                          \n";
	std::cout << " `'`' / :  :                   :  :  : : \n";
	std::cout << "     )_ \\__;       ;           :_ ;  \\_\\       `,',' \n";
	std::cout << "     :__\\  \\    * `,'*         \\  \\  :  \\   *  8`;'*  * \n";
	std::cout << "         `^'     \\ :/           `^'  `-^-'   \\v/ :  \\/   -Bill Ames- \n";

	return;
}

//play a single game to completion
//Game Loop
void PlayGame()
{	
	
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	int32 CurrentTry = 0;
	int x = 0;
	while (BCGame.GetCurrentTry()<= MaxTries && !BCGame.IsGameWon(x))
	{
		CurrentTry = BCGame.GetCurrentTry();		
		FText Guess=GetValidGuess(); 

		//Submit valid guess to game
		//Print number of bulls and cows
		FBullCowCount BullCowCount= BCGame.SubmitValidGuess(Guess);
		PrintBack(Guess);	
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << " \n\n";	
		BCGame.SetCurrentTry(CurrentTry + 1); //I am increasing the current try here
		x = BullCowCount.Bulls;
	}
	PrintGameSummary(x);
	return;
}

//loop until the player puts a valid guess
FText GetValidGuess() 
{
	EWordStatus Status = EWordStatus::Invalid;
	FText Guess = "";
	do {
		//get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		
		std::cout << "You still have " << BCGame.GetMaxTries()- (BCGame.GetCurrentTry()-1) << " tries\n";
		std::cout << "Try " << CurrentTry << " Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EWordStatus::Wrong_Length:
			std::cout << "please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EWordStatus::Not_Isogram:
			std::cout << "please enter an isogram (a word without repeating letters)\n\n";
			break;
		case EWordStatus::Not_Lowercase:
			std::cout << "please use lowercase letters\n\n";
			break;
		default: 
			break;
		}
	} while (Status != EWordStatus::Ok); //keep looping until we get no errors

	return Guess;
}

void PrintBack(FText X)
{
	std::cout << "Your guess was '" << X << "'\n";
	return;
}

bool AskToPlayAgain()
{
	bool bAnswer;
	std::cout << "Do you want to play again? (y/n)\n";
	FText Response = "";
	std::getline(std::cin, Response);
	if (Response[0] == 'y' || Response[0]== 'Y')
	{
		bAnswer = true;		
	}
	else
		bAnswer = false;
	return bAnswer;
}

void PrintGameSummary(int32 x)
{

	if (x == BCGame.GetHiddenWordLength())
	{
		std::cout << "Congrats, you won! ";
	}
	else std::cout << "Bad luck... Maybe next time! ";

}
