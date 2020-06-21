#include "FBullsNCows.h"
#include <map>
#define TMap std::map


FBullsNCows::FBullsNCows()
{
	Reset();

}

void FBullsNCows::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	MyCurrentTry = 1;
	MyMaxTries = MAX_TRIES;
	const FString HIDDEN_WORD = "planet";
	MyHiddenWord = HIDDEN_WORD;
	bGameIsWon = false;
	return;
}

int FBullsNCows::GetMaxTries() const
{
	TMap<int32, int32> WordLenToMaxTries{ {3, 5}, {4,5}, {5,5}, {6,5} };
	return WordLenToMaxTries[MyHiddenWord.length()];
}

int FBullsNCows::GetCurrentTry() const
{
	return MyCurrentTry;
}

bool FBullsNCows::IsGameWon() const
{
	return bGameIsWon; 
}

int32 FBullsNCows::GetHiddenLen() const
{	
	return  MyHiddenWord.length();
}

EGuessStatus FBullsNCows::CheckGuessValidity(FString Guess) const
{
	// return fasle if it is not an isogram or a lower case or if len is less 
	if (!IsIsogram(Guess)) {
		return EGuessStatus::NOT_ISO;
	}
	else if (!IsLowerCase(Guess)) {
		return EGuessStatus::NOT_LOWERCASE;
	}
	else if (Guess.length() != GetHiddenLen()) {
		return EGuessStatus::WRONG_LEN;
	}
	else {
		return EGuessStatus::OK;
	}
}

// received a VALID guess, increamets the try and returns count
FBullCowCount FBullsNCows::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	// setupo a retrun value
	FBullCowCount bullCowCount;

	// compare the letters 
	int32 HiddenWordLen = MyHiddenWord.length();
	for (int32 myHidChar = 0; myHidChar < HiddenWordLen; myHidChar++) {
		for (int32 GuessChar = 0; GuessChar < HiddenWordLen; GuessChar++) {
			if ( Guess[GuessChar] == MyHiddenWord[myHidChar] ) {
				if (myHidChar == GuessChar) {
					bullCowCount.Bulls++;
				}
				else {

					bullCowCount.Cows++; // must be a cow
				}
			}
		}
	}

	if (bullCowCount.Bulls == HiddenWordLen) {
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return bullCowCount;
}

bool FBullsNCows::IsIsogram(FString Word) const
{
	// 0 and 1 letter word is a isogram
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LettersSeen;
	for(auto Letter : Word){ //For all letters of the word
		Letter = tolower(Letter);
		if(LettersSeen[Letter]){
			return false;
		}
		else {
			LettersSeen[Letter] = true;
		}
	} 

	return true;
}

bool FBullsNCows::IsLowerCase(FString Word) const
{
	for (auto Letter : Word) {
		if (!islower(Letter) {
			return false;
		}
	}
	return true;
}
