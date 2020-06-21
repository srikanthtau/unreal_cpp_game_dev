#pragma once
#include <string>

using FString = std::string;
using int32 = int;

//never use namespace in the header file

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	INAVLID,
	OK,
	NOT_ISO,
	WRONG_LEN,
	NOT_LOWERCASE
};

enum class EResetStatus
{
	NO_HIDDEN_WORD,
	OK
};

class FBullsNCows {
public:
	FBullsNCows();

	int32 GetMaxTries() const;	
	int32 GetCurrentTry() const;
	bool IsGameWon() const;
	int32 GetHiddenLen() const;
	bool bGameIsWon;

	void Reset();
	EGuessStatus CheckGuessValidity(FString Guess) const;
	// counts bulls and cows
	FBullCowCount SubmitValidGuess(FString Guess);

private:
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool IsIsogram(FString) const; 
	bool IsLowerCase(FString) const;
};