#include<stdio.h>
#include<string.h>

int main()
{
	// Declare variables
	char reg[20]; // Regular expression input
	int q[20][3]; // Transition table
	int i=0, j=1, len, a, b; // Loop and index variables

	// Prompt for regular expression input
	printf("Enter the regular expression: ");

	// Initialize the transition table with zeros
	for (a = 0; a < 20; a++)
		for (b = 0; b < 3; b++)
			q[a][b] = 0;

	// Read the regular expression input
	scanf("%s", reg);

	// Print the given regular expression
	printf("Given regular expression: %s\n", reg);

	// Calculate the length of the regular expression
	len = strlen(reg);

	// Parsing the regular expression character by character
	while(i < len)
	{
		// Check for 'a' followed by a non-'|' and non-'*' character
		if(reg[i] == 'a' && reg[i+1] != '|' && reg[i+1] != '*') {
			q[j][0] = j+1; // Assign next state for 'a'
			j++;
		}

		// Check for 'b' followed by a non-'|' and non-'*' character
		if(reg[i] == 'b' && reg[i+1] != '|' && reg[i+1] != '*') {
			q[j][1] = j+1; // Assign next state for 'b'
			j++;
		}

		// Check for 'e' (epsilon) followed by a non-'|' and non-'*' character
		if(reg[i] == 'e' && reg[i+1] != '|' && reg[i+1] != '*') {
			q[j][2] = j+1; // Assign next state for 'e'
			j++;
		}

		// Check for 'a' followed by '|' and 'b'
		if(reg[i] == 'a' && reg[i+1] == '|' && reg[i+2] == 'b') {
			q[j][2] = ((j+1)*10) + (j+3); // Concatenation of 'a' and 'b'
			j++;
			q[j][0] = j+1; // Assign next state for 'a'
			j++;
			q[j][2] = j+3; // Assign next state for 'b'
			j++;
			q[j][1] = j+1; // Assign next state for 'b' after '|'
			j++;
			q[j][2] = j+1; // Assign next state for 'e' after '|'
			j++;
			i = i+2; // Skip the '|' and 'b'
		}

		// Check for 'b' followed by '|' and 'a'
		if(reg[i] == 'b' && reg[i+1] == '|' && reg[i+2] == 'a') {
			q[j][2] = ((j+1)*10) + (j+3); // Concatenation of 'b' and 'a'
			j++;
			q[j][1] = j+1; // Assign next state for 'b'
			j++;
			q[j][2] = j+3; // Assign next state for 'a'
			j++;
			q[j][0] = j+1; // Assign next state for 'a' after '|'
			j++;
      			q[j][2] = j+1; // Assign next state for 'e' after '|'
			j++;
			i = i+2; // Skip the '|' and 'a'
		}

		// Check for 'a' followed by '*'
		if(reg[i] == 'a' && reg[i+1] == '*') {
			q[j][2] = ((j+1)*10) + (j+3); // Kleene closure of 'a'
			j++;
			q[j][0] = j+1; // Assign next state for 'a'
			j++;
			q[j][2] = ((j+1)*10) + (j-1); // Loop back to the previous 'a'
			j++;
		}

		// Check for 'b' followed by '*'
		if(reg[i] == 'b' && reg[i+1] == '*') {
			q[j][2] = ((j+1)*10) + (j+3); // Kleene closure of 'b'
			j++;
			q[j][1] = j+1; // Assign next state for 'b'
			j++;
			q[j][2] = ((j+1)*10) + (j-1); // Loop back to the previous 'b'
			j++;
		}

		// Check for ')' followed by '*'
		if(reg[i] == ')' && reg[i+1] == '*') {
			q[0][2] = ((j+1)*10) + 1; // Closure of the entire regular expression
			q[j][2] = ((j+1)*10) + 1;
			j++;
		}

		i++; // Move to the next character in the regular expression
	}

	// Print the transition table
	printf("\n\tTransition Table \n");
	printf("_____________________________________\n");
	printf("Current State |\tInput |\tNext State");
	printf("\n_____________________________________\n");

	// Iterate over the transition table and print the states and inputs
	for(i=0; i<=j; i++) {
		if(q[i][0] != 0)
			printf("\n  q[%d]\t      |   a   |  q[%d]", i, q[i][0]);
		if(q[i][1] != 0)
			printf("\n  q[%d]\t      |   b   |  q[%d]", i, q[i][1]);
		if(q[i][2] != 0) {
			if(q[i][2] < 10)
				printf("\n  q[%d]\t      |   e   |  q[%d]", i, q[i][2]);
			else
				printf("\n  q[%d]\t      |   e   |  q[%d] , q[%d]", i, q[i][2]/10, q[i][2]%10);
		}
	}

	printf("\n_____________________________________\n");
	return 0;
}

// Input 

// (a|b)*abb
