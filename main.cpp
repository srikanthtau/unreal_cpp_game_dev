#include <iostream>
#include <string>
#include "FBullsNCows.h"

#pragma once

// Unreal convention 
using FText = std::string;
using int32 = int;

void PrintIntro();
FText GetValidGuess();
void PlayGame();
bool AskToPlayAgain();
void PrintGameSummary();

FBullsNCows BCGame;

int main()
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} 
	while (bPlayAgain);
	
	return 0;
}

void PrintIntro()
{
	std::cout << "Hello fucking VS 2019" << std::endl;
	std::cout << "can you guess the " << BCGame.GetHiddenLen() << " letter isogram..." << std::endl;
	return;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess();
		// submit valid guess to the game 
		FBullCowCount bullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << bullCowCount.Bulls << "; Cows = " << bullCowCount.Cows << std::endl;
		std::cout << "You have guessed : " << Guess << std::endl;
		std::cout << std::endl;
	}
	// TODO Summarize the game 


}


bool AskToPlayAgain()
{
	std::cout << "Do want to play again with the same hidden word?";
	FText Response = "";
	std::cin >> Response;

	return (Response[0] == 'y' || Response[0] == 'Y');
}

void PrintGameSummary() {
	if (BCGame.IsGameWon()) 
	{
		std::cout << "WELL Done" << std::endl;

	}
	else {
		std::cout << "Better Luck next time" << std::endl;
	}
}

FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::INAVLID;
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();

		
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetCurrentTry() << ". Enter your guess :";
		// cin >> Guess;
		std::getline(std::cin, Guess);
 
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::WRONG_LEN:
			std::cout << "Please enter a  " << BCGame.GetHiddenLen() << " letter word" << std::endl;
			break;
		case EGuessStatus::NOT_ISO:
			std::cout << "Please enter a word woth out rpeating letters" << std::endl;
			break;
		case EGuessStatus::NOT_LOWERCASE:
			std::cout << "Please enter a lower case word" << std::endl;
			break;
		default:
			// Guess is valid 
			break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK); //loop through there are no errors
	return Guess;
}

