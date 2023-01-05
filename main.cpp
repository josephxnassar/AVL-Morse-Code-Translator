#include "AVL.h"

int main(int argc, char *argv[])
{
	char* morse = argv[1];
	char* input = argv[2];
	char* output = argv[3];

	AVL tree(morse); //Initializes ballanced tree via characters from MorseTable.txt

	//tree.print(); //Prints contents of tree

	//tree.print2D();

	tree.convert(input, output); //Converts contents from Convert.txt to morse code

	tree.printStats();

	tree.destroyTree(); //Destroys that futile tree

	return 0;
}