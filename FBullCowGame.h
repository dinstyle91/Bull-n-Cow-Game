/*
Rhe game logic (no view code or direct user interaction)
The game is a simple guess the word based on Mastermind
*/
#pragma once
#include <string>
#include <iostream>

using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EWordStatus
{
	Invalid,
	Ok,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase

};

class FBullCowGame {
public:	
	FBullCowGame(); // constructor

	int32 GetMaxTries() const;
	FString GetDesiredWord(FString) ;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength()const;
	void SetCurrentTry(int32 x);
	bool IsGameWon(int32 x) const;
	EWordStatus CheckGuessValidity(FString)const;

	FString ChooseWordLength()const;
	void Reset();
	void Reset1();
	
	FBullCowCount SubmitValidGuess(FString);
	FString GetNumber();


private:
	bool IsIsogram(FString)const;
	bool IsLowercase(FString) const;
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	

};