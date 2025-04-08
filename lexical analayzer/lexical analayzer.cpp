// Function to add the current character to the lexeme.
void addChar() {
    lexeme += nextChar;  // Adds the character to the lexeme string.
}

// Function to get the next character from the input file.
void getChar() {
    if (in_fp.get(nextChar)) {  // Reads the next character from the file.
        if (isalpha(nextChar))  // Checks if the character is a letter.
            charClass = LETTER;  // Sets the character class to LETTER if it's a letter.
        else if (isdigit(nextChar))  // Checks if the character is a digit.
            charClass = DIGIT;  // Sets the character class to DIGIT if it's a digit.
        else
            charClass = UNKNOWN;  // Sets the character class to UNKNOWN for other characters.
    }
    else {
        charClass = END_OF_FILE;  // Sets the character class to END_OF_FILE if the end of file is reached.
    }
}

// Function to skip any whitespace characters (spaces, tabs, newlines) in the input.
void getNonBlank() {
    while (isspace(nextChar))  // Loops until a non-whitespace character is found.
        getChar();  // Calls getChar() to get the next character.
}

// Function to process special characters and operators and assign the corresponding token type.
int lookup(char ch) {
    // Checks for specific characters (operators, parentheses, and assignment operator) and assigns the corresponding token type.
    switch (ch) {
    case '(':
        addChar();
        nextToken = LEFT_PAREN;  // Token for left parenthesis.
        break;
    case ')':
        addChar();
        nextToken = RIGHT_PAREN;  // Token for right parenthesis.
        break;
    case '+':
        addChar();
        nextToken = ADD_OP;  // Token for addition operator.
        break;
    case '-':
        addChar();
        nextToken = SUB_OP;  // Token for subtraction operator.
        break;
    case '*':
        addChar();
        nextToken = MULT_OP;  // Token for multiplication operator.
        break;
    case '/':
        addChar();
        nextToken = DIV_OP;  // Token for division operator.
        break;
    case '=':
        addChar();
        nextToken = ASSIGN_OP;  // Token for assignment operator.
        break;
    default:
        addChar();
        nextToken = END_OF_FILE;  // If no matching case, mark it as end of file (EOF).
        break;
    }
    return nextToken;  // Return the token type corresponding to the character.
}

// Function to analyze the next lexeme (token) in the input stream and assign it a token type.
int lex() {
    lexeme = "";  // Clear the lexeme string.
    getNonBlank();  // Skip any leading whitespace characters.

    switch (charClass) {
    case LETTER:
        addChar();  // Add the current character to the lexeme if it's a letter.
        getChar();  // Get the next character.
        while (charClass == LETTER || charClass == DIGIT) {  // Continue while the character is a letter or a digit.
            addChar();  // Add the character to the lexeme.
            getChar();  // Get the next character.
        }
        nextToken = IDENT;  // Set the token type to IDENT (identifier) for a string of letters/digits.
        break;

    case DIGIT:
        addChar();  // Add the current character to the lexeme if it's a digit.
        getChar();  // Get the next character.
        while (charClass == DIGIT) {  // Continue while the character is a digit.
            addChar();  // Add the character to the lexeme.
            getChar();  // Get the next character.
        }
        nextToken = INT_LIT;  // Set the token type to INT_LIT (integer literal) for digits.
        break;

    case UNKNOWN:
        lookup(nextChar);  // Process unknown characters and assign a token type.
        getChar();  // Get the next character.
        break;

    case END_OF_FILE:
        nextToken = END_OF_FILE;  // Mark the token as EOF if the end of file is reached.
        lexeme = "EOF";  // Set the lexeme to "EOF".
        break;
    }

    // Output the current token and lexeme for debugging purposes.
    cout << "Next token is: " << nextToken << ", Next lexeme is " << lexeme << endl;

    return nextToken;  // Return the token type.
}

// Main function to process the input file and generate tokens.
int main() {
    in_fp.open("front.in");  // Open the input file "front.in".

    if (!in_fp) {  // If the file cannot be opened, print an error and return 1.
        cerr << "ERROR - cannot open front.in" << endl;
        return 1;
    }

    getChar();  // Get the first character from the file.

    // Continuously process the input file until the end of the file (EOF) is reached.
    do {
        lex();  // Call the lex function to process the next token.
    } while (nextToken != END_OF_FILE);  // Repeat until the EOF token is encountered.

    in_fp.close();  // Close the input file after processing.
    return 0;  
}
