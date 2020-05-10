#pragma once
#include "FBullCowGame.h"
#include <iostream>
#include <string>
#include <map>
#define TMap std::map

FBullCowGame::FBullCowGame()
{
	
}

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const {return MyHiddenWord.length();}

int32 FBullCowGame::GetMaxTries() const 
{
	TMap<int32, int32>WordLengthToMaxTries{ {3,4}, {4,5}, {5,6} ,{6,10} ,{7,16}, {8,20}, {9,25} };
	return WordLengthToMaxTries[MyHiddenWord.length()]; //this would be the 1st number in the curly braces, which would return the second number in the curly braces.
}

FString FBullCowGame::GetDesiredWord(FString No)  
{
	//the words have to be isograms!
	TMap<FString, FString> WordlengthToDesireWord{ { "3","ale" },{ "4","apes" },{ "5","plane" } ,{ "6","knight" } ,{ "7","hybrids" } };
	return WordlengthToDesireWord[No]; //this would be the 1st number in the curly braces, which would return the second number in the curly braces.
}

bool FBullCowGame::IsIsogram(FString Guess) const
{
	//treat 0 and 1 letter words as isograms
	if (Guess.length() <= 1) { return true; }
	
	//set up the map
	TMap<char, bool> LetterSeen;
	for (auto Letter : Guess) // for all letters in the guess
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) { return false; }//if letter has been seen before (it's already in the map), we don't have an isogram
		else 
		{
			LetterSeen[Letter] = true; //add letter to the map
		}
	}
	return true;
}

bool FBullCowGame::IsLowercase(FString Guess) const
{	
	
	for (auto Letter : Guess) // for all letters in the guess
	{		
		if (islower(Letter)) 
		{ 
			
		}
		else
		{
			return false;
		}
	}
	return true;
}

FString FBullCowGame::GetNumber()
{
	std::cout << "Can you guess one of the isograms I am thinking?\n" << "Please chose the length of the word you would like to guess\n";
	std::cout << "(From 3 to 9 characters)";
	FString letters="";
	std::getline(std::cin, letters);
	return letters;
}


void FBullCowGame::Reset()
{ 
	std::cout << "Can you guess one of the isograms I am thinking?\n" << "Please chose the length of the word you would like to guess\n";
	std::cout << "(From 3 to 9 characters)\n";
	FString letters = "";
	std::getline(std::cin, letters);
	const FString HIDDEN_WORD = GetDesiredWord(letters);
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;	
	return;
}

void FBullCowGame::Reset1()
{
	const FString HIDDEN_WORD="knight";
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	return;
}



void FBullCowGame::SetCurrentTry(int32 x)
{
	MyCurrentTry = x;
}

bool FBullCowGame::IsGameWon(int32 x) const
{
	if (x == GetHiddenWordLength())
		return true;
	else
		return false;
}

EWordStatus FBullCowGame::CheckGuessValidity(FString Guess)const
{
	if (IsIsogram(Guess)!=true) return EWordStatus::Not_Isogram; 

	else if (IsLowercase(Guess) != true) return EWordStatus::Not_Lowercase; 

	else if (Guess.length()!= GetHiddenWordLength())
		return EWordStatus::Wrong_Length;
	
	else  return EWordStatus::Ok; 
}

//receives a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); //assuming same length as guess

	//loop through all letters in the hidden word	
	for (int32 HiddenWordChar = 0; HiddenWordChar < WordLength; HiddenWordChar++) {
		// compare letters against the guess
		for (int32 GuessChar = 0; GuessChar< WordLength; GuessChar++) {
			if (Guess[GuessChar] == MyHiddenWord[HiddenWordChar])
			{
				if (HiddenWordChar == GuessChar) {
					BullCowCount.Bulls++;
				}
				else{
					BullCowCount.Cows++;
				}				
			}				
		}
	}
	return BullCowCount;
}

FString FBullCowGame::ChooseWordLength(void) const
{
	std::cout << "Hello! inorder to continue, please choos how many letters the hidden word should have (from 3 to 7)\n";
	FString letters = "";
	std::getline(std::cin, letters);
	return letters;
}

