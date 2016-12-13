#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "string.h"
#include "vector_string.h"
#include "array_vector_string.h"
#include "boolean.h"
#include "binary_search_tree.h"
#include "node.h"

#define DEBUG

int get_word_len();
int get_num_of_guesses();
char get_guess(STRING);
void print_guesses(STRING);
void play_hangman(int, int);
Boolean will_keep_playing();
void clear_keyboard_buffer();
void get_word_key_value(STRING, STRING, STRING, char);
void insert_word_into_tree(BST, STRING, STRING);
void user_win(STRING);
void user_lose(VECTOR_STRING);


int main(void)
{
	Boolean playing = TRUE;

	while(playing)
	{
		printf("\n\n\n  Not So Nice Hangman\n    by Zachary Buffone\n\n");

		printf("What is the length of the word you want to guess?\n");
		int word_len = get_word_len();
		printf("\nHow many guesses do you want?\n");
		int num_of_guesses = get_num_of_guesses();

		printf("\nLets start!");
		play_hangman(word_len, num_of_guesses);

		printf("Do you want to play again? (Y/N)\n");
		if(!(will_keep_playing()))
		{
			printf("Thanks for playing!!!\n");
			playing = FALSE;
		}

	}


}

void play_hangman(int word_len, int num_of_guesses)
{
	STRING guesses = string_initDefault();
	VECTOR_STRING* dict = array_vector_string_init();
	VECTOR_STRING word_vec = vector_string_shallow_copy(dict[word_len]);
	STRING current_word_family = string_initDefault();

	//blank word family
	int i;
	for(i = 0; i < word_len; i++)
		string_pushBack(current_word_family, '-');

	while(num_of_guesses > 0)
	{
		string_print(current_word_family);

		printf("You have %d guesses left.\nGuesses so far: ", num_of_guesses);
		print_guesses(guesses);

		char guess = get_guess(guesses);
		string_pushBack(guesses, guess);

		BST tree = bst_init_default();
		STRING word;
		STRING new_key;
		for(i = 0; i < vector_string_get_size(word_vec); i++)
		{
			new_key = string_initDefault();

			word = *(vector_string_at(word_vec, i));
			get_word_key_value(word, current_word_family, new_key, guess);

			insert_word_into_tree(tree, new_key, word);
		}

		Node* largest_node = bst_at_largest_key(tree);

		#ifdef DEBUG
		bst_traverse(tree);
		printf("Largest key: ");
		string_insertion(largest_node->key, stdout);
		printf("\n");
		#endif
		string_destroy(&current_word_family);
		current_word_family = string_copy(largest_node->key);
		vector_string_shallow_destroy(&word_vec);
		word_vec = vector_string_shallow_copy(largest_node->value);

		///win condition
		if(((Node*)tree)->right == NULL && ((Node*)tree)->left == NULL
			&& vector_string_get_size(((Node*)tree)->value) == 1) //bad
		{
			user_win(largest_node->key);
			bst_destroy(&tree);
			break;
		}

		bst_destroy(&tree);
		num_of_guesses--;
	}

	//lose condition
	if(num_of_guesses == 0)
		user_lose(word_vec);

	vector_string_shallow_destroy(&word_vec);
	array_vector_string_destroy(&dict);
	string_destroy(&guesses);
	string_destroy(&current_word_family);
	return;
}

void get_word_key_value(STRING word, STRING current_word_family, STRING new_key, char guess)
{
	int i;

	//ptrs to chars in strings word, cur_word_fam
	char* wp;
	char* fp;
	for(i = 0; i < string_getSize(word); i++)
	{
		wp = string_at(word, i);
		fp = string_at(current_word_family, i);

		if(*fp != '-')
			string_pushBack(new_key, *fp);
		else if(*wp == guess)
			string_pushBack(new_key, guess);
		else
			string_pushBack(new_key, '-');
	}

	return;
}

void insert_word_into_tree(BST tree, STRING key, STRING word)
{
	Node* node = bst_at_key(tree, key);

	//if node doesn't exist, create node and insert word
	if(!node)
	{
		#ifdef DEBUG
		printf("Creating new node ");
		string_insertion(key, stdout);
		printf(".\n");
		#endif
		node = bst_insert_key(tree, key);
	}
	else
		string_destroy(&key);

	vector_string_push_back(node->value, word);
	return;
}

void print_guesses(STRING guesses)
{
	int i;
	for(i = 0; i < string_getSize(guesses); i++)
		printf(" %c ", *(string_at(guesses, i)));
	printf("\n");

	return;
}

void user_win(STRING word)
{
	printf("What? You won? Cheater...\nThe word was ");
	string_insertion(word, stdout);
	printf(".\n\n");
	return;
}

void user_lose(VECTOR_STRING vec)
{
	int index = rand() % (vector_string_get_size(vec) - 1);
	printf("You lose!\nThe word was ");
	string_insertion(*(vector_string_at(vec, index)), stdout);
	printf(".\n");
	return;
}

//user input functions -----
int get_word_len()
{
	int len = 0;
	int convert = scanf("%d", &len);
	while(!convert || len < 2 || len == 26 || len == 27 || len > 29)
	{
		printf("Enter a integer that is not\n\t26 or 27\n\tless than 2\n\tgreater than 29\n");
		clear_keyboard_buffer();
		convert = scanf("%d", &len);
	}
	clear_keyboard_buffer();
	return len;
}

int get_num_of_guesses()
{
	int len;
	int convert = scanf("%d", &len);
	while(!convert || len < 1)
	{
		printf("Enter a positive integer\n");
		clear_keyboard_buffer();
		convert = scanf("%d", &len);
	}
	clear_keyboard_buffer();
	return len;
}

char get_guess(STRING guesses)
{
	char g;
	printf("Enter your guess: ");
	scanf("%c", &g);

	while(string_contains(guesses, g) || !isalpha(g))
	{
		printf("You have already guesses that letter.\nEnter a letter you have not guessed: ");
		clear_keyboard_buffer();
		scanf("%c", &g);
	}

	printf("\n");
	clear_keyboard_buffer();
	return tolower(g);

}

Boolean will_keep_playing()
{
	char c;
	int convert = scanf("%c", &c);
	c = tolower(c);

	while(!convert || (c != 'y' && c != 'n'))
	{
		printf("Please enter \'y\' or \'n\': ");
		clear_keyboard_buffer();
		convert = scanf("%c", &c);
	}
	clear_keyboard_buffer();
	return ( (c == 'y') ? TRUE : FALSE );
}

void clear_keyboard_buffer()
{
	char c;
	do
		scanf("%c", &c);
	while(c != '\n');
	return;
}
