#include "Password.h"
using CSC2110::ListArrayIterator;



#include <iostream>
using namespace std;

Password::Password()
{
	ListArray<String>* all_words = new ListArray;
	ListArray<String>* viable_words = new ListArray;
	//uses constructor from ListArray class to initialize pointers
	all_words->ListArray();	//JC 2.2.17
	viable_words->ListArray();	//JC 2.2.17
}

Password::~Password()
{
	//call removeAll func to delete contents of arrays
	all_words->removeAll();	//JC 2.2.17
	viable_words->removeAll();	//JC 2.2.17
	
	//calls destructor from ListArray class
	all_words->~ListArray();	//JC 2.2.17
	viable_words->~ListArray();		//JC2.2.17
	
	delete all_words;	//JC 2.2.17
	delete viable_words;	//JC 2.2.17
}

void Password::addWord(String* word)
{
	//populates both arrays with original list of words
	all_words->add(word);	//JC 2.2.17
	viable_words->add(word);	//JC 2.2.17
}

void Password::guess(int try_password, int num_matches)
{
	String* word = getOriginalWord(try_password);
	ListArray<String>* temp = new ListArray;
	int sz = viable_words->size();	
	
	for (int i = 0; i < sz; i++)	
	{
		
		if (word.compare(viable_words[i]) <= num_matches)
		{
			temp->add(viable_words[i]);
		}
	}
	
	viable_word = temp;
}

int Password::getNumberOfPasswordsLeft()
{
	int num = viable_words->size();	//Finds number of possible passwords and returns int
	
	return num;
}

void Password::displayViableWords()
{
	int sz = viable_words->size();	//get current size of array JC 2.2.17
	
	for (int i = 0; i < sz; i++)	//cycle through array and print contents JC 2.2.17
	{
		cout << endl << viable_words[i];
	}
}

String* Password::getOriginalWord(int index)	//JC 2.2.17
{
	String* original_word = all_words->get(index);
	
	return original_word;
}

int Password::bestGuess()
{
   int best_guess_index = -1;
   int best_num_eliminated = -1;
   int num_viable_passwords = getNumberOfPasswordsLeft();

   //loop over ALL words, even if they have been eliminated as the password
   int count = 1;
   ListArrayIterator<String>* all_iter = all_words->iterator();
   while(all_iter->hasNext())
   {
      String* original_word = all_iter->next();

      //loop over only those words that could still be the password
      //count up the number of matches between a possible password and a word in the original list
      int* count_num_matches = new int[len + 1];

      for (int i = 0; i < len; i++) 
      {
         count_num_matches[i] = 0;
      }

      ListArrayIterator<String>* viable_iter = viable_words->iterator();
      while(viable_iter->hasNext())
      {
         String* viable_word = viable_iter->next();
         int num_matches = getNumMatches(viable_word, original_word);
         count_num_matches[num_matches]++;
      }
      delete viable_iter;

      //find the largest number in the count_num_matches array
      //the largest number indicates the guess that will generate the most eliminations
      int most_num_matches = 0;
      for (int j = 0; j < len; j++) 
      {
         int curr_num_matches = count_num_matches[j];
         if (curr_num_matches > most_num_matches)
         {
            most_num_matches = curr_num_matches;
         }
      }

      //compute the fewest that can possibly be eliminated by guessing the current word (original list)
      int num_eliminated = num_viable_passwords - most_num_matches;

      //select the word to guess that maximizes the minimum number of eliminations (minimax)
      if (num_eliminated > best_num_eliminated)
      {
         best_num_eliminated = num_eliminated;
         best_guess_index = count;
      }
      
      count++;
      delete[] count_num_matches;
   }

   delete all_iter;
   return best_guess_index;  //return a 1-based index into the all_words list of words (careful)
}
