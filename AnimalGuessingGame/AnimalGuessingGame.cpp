#include <iostream>
#include <string>
#include <stdio.h>
#include <conio.h>
using namespace std;

//Globals
string UserAnimalInput; //Stores the animal the user was thinking of
string UserQuestionInput; //Stores the users differentiating question
string UserQuestionAnswer; //Stores the answer (yes or no) to the user's differentiating question
bool ContinuePlaying = true;

//Structs
struct GuessNode {
	string question;
	string guess;
	GuessNode* yesNode;
	GuessNode* noNode;
};

//Global Structs
GuessNode* CurrentNode = new GuessNode;
GuessNode* RootNode = new GuessNode;

//Functions
void InitializeGame() { //Initial configuration of the root node. This will only run at startup
	RootNode->question = "";
	RootNode->guess = "lizard";
	RootNode->noNode = nullptr;
	RootNode->yesNode = nullptr;
}//InitializeGame

void GenerateChildNodes() { //Runs every time the program fails to guess an animal. This generates new leaf nodes that are children of the current node
	CurrentNode->yesNode = new GuessNode;
	CurrentNode->noNode = new GuessNode;
	CurrentNode->yesNode->yesNode = nullptr;
	CurrentNode->yesNode->noNode = nullptr;
	CurrentNode->noNode->yesNode = nullptr;
	CurrentNode->noNode->noNode = nullptr;
}//GenerateChildNodes

bool PromptUser() { //Input validation for all user input except for CollectUserQuestionAnswer() below
	switch (_getch()) {
	case 'Y':
	case 'y':
		return (true);
		break;
	case 'N':
	case 'n':
		return (false);
		break;
	default:
		cout << "\nInvalid Entry! Please enter Y/N.\n";
		PromptUser();
	}
}//PromptUser

void PopulateChildNodes() { //Populates the newly created child nodes of the current node based on the user input
	if (UserQuestionAnswer == "N") {
		CurrentNode->noNode->guess = UserAnimalInput;
		CurrentNode->noNode->question = "";
		CurrentNode->yesNode->guess = CurrentNode->guess;
		CurrentNode->yesNode->question = "";
	}
	else {
		CurrentNode->yesNode->guess = UserAnimalInput;
		CurrentNode->yesNode->question = "";
		CurrentNode->noNode->guess = CurrentNode->guess;
		CurrentNode->noNode->question = "";
	}
}//PopulateChildNodes

void CollectUserQuestionAnswer() { //Input validation routine for specifying if the answer to their provided question will be yes or no for their provided animal
	switch (_getch()) {
	case 'Y':
	case 'y':
		UserQuestionAnswer = "Y";
		break;
	case 'N':
	case 'n':
		UserQuestionAnswer = "N";
		break;
	default:
		cout << "\nInvalid Entry! Please enter Y/N.\n";
		PromptUser();
	}
}//CollectUserQuestionAnswer

void CreateNewGuessNodes() {
	cout << "You stumped me!" << endl;
	cout << "Enter the animal you were thinking of: ";
	getline(cin, UserAnimalInput);
	cout << "Give me a question I can use to differentiate between " << UserAnimalInput << " and " << CurrentNode->guess << ": ";
	getline(cin, UserQuestionInput);
	cout << "For a " << UserAnimalInput << " what is the answer to this question? (Enter Y or N): \n";
	CollectUserQuestionAnswer();
	GenerateChildNodes();
	PopulateChildNodes();
	CurrentNode->question = UserQuestionInput;
	CurrentNode->guess = "";
}//CreateNewGuessNodes

void MakeGuess() { //Runs when the program encounters a leaf node
	cout << "Is your animal a(n) " << CurrentNode->guess << "? (Enter Y or N): " << endl;
	if (PromptUser() == true) { //If the program guesses the correct animal the game will end, and the program prompts the user to play again in main()
		cout << "I win! Let's play again" << endl;
	}
	else { //If the user is thinking of an animal not in the database, the program collects necessary information to generate a new node with their animal
		CreateNewGuessNodes();
	}
}//MakeGuess

void TraverseTree() {
	if (CurrentNode->yesNode == nullptr && CurrentNode->noNode == nullptr) { //When the program reaches a leaf node it will attempt to guess the animal
		MakeGuess();
	}
	else { //At each branch the program will ask the question present at that node, and move to the appropriate next node
		string UserInput;
		cout << CurrentNode->question << " (Y or N): ";
		if (PromptUser() == true) {
			cout << "\n";
			CurrentNode = CurrentNode->yesNode;
			TraverseTree();
		}
		else {
			cout << "\n";
			CurrentNode = CurrentNode->noNode;
			TraverseTree();
		}
	}
}//TraverseTree

int main()
{
	InitializeGame();
	do { //Continues playing the game as long as the user continues to agree to play again upon game over
		CurrentNode = RootNode;
		cout << "Please think of an animal and ";
		system("pause");
		TraverseTree();
		cout << "Do you want to play again?: (Y or N): \n";
		if (PromptUser() == false) {
			ContinuePlaying = false;
		}
	} while (ContinuePlaying == true);
}

