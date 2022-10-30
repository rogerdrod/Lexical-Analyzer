
#include <stdio.h>
#include <ctype.h>


/* Global declarations */
/* Variables */
int charClass; 
char* Token;
char lexeme [100];
char nextChar;
char currentChar;
int lexLen; 
int token;
int nextToken;
FILE *in_fp, *fopen();

/* Function declarations */
void addChar();
void getChar();
void getNonBlank();
char* lex();

/* Character classes left here from previous code in case I need it for future use but is not used in this program*/

#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99
//Token codes 
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
#define LESSER_OP 27
#define GREATER_OP 28
#define EQUAL_OP 29
#define NEQUAL_OP 30
#define LEQUAL_OP 31
#define GEQUAL_OP 32
#define SEMICOLON 33
#define MOD_OP 34
#define LEFT_CBRACE 35
#define RIGHT_CBRACE 36
#define KEY_READ 37 
#define KEY_PRINT 38 
#define KEY_WHILE 39
#define KEY_DO 40 


/* Character classes with an underscore and defining them as words that are used for the display*/
#define LETTER_ "LETTER"
#define DIGIT_ "DIGIT"
#define UNKNOWN_ "UNKNOWN"
/* Token codes */
#define INT_LIT_ "INT_LIT"
#define IDENT_ "IDENT"
#define ASSIGN_OP_ "ASSIGN_OP"
#define ADD_OP_ "ADD_OP"
#define SUB_OP_ "SUB_OP"
#define MULT_OP_ "MULT_OP"
#define DIV_OP_ "DIV_OP"
#define LEFT_PAREN_ "LEFT_PAREN"
#define RIGHT_PAREN_ "RIGHT_PAREN"
#define LESSER_OP_ "LESSER_OP"
#define GREATER_OP_ "GREATER_OP"
#define EQUAL_OP_ "EQUAL_OP"
#define NEQUAL_OP_ "NEQUAL_OP"
#define LEQUAL_OP_ "LEQUAL_OP"
#define GEQUAL_OP_ "GEQUAL_OP"
#define SEMICOLON_ "SEMICOLON"
#define MOD_OP_ "MOD_OP"
#define LEFT_CBRACE_ "LEFT_CBRACE"
#define RIGHT_CBRACE_ "RIGHT_CBRACE"
#define KEY_READ_ "KEY_READ"
#define KEY_PRINT_ "KEY_PRINT"
#define KEY_WHILE_ "KEY_WHILE"
#define KEY_DO_ "KEY_DO"


/* main driver */
int main(int argc, char** argv[]){ 
/* Open the input data file and process its contents */
printf("DanC Analyzer :: R11697479\n\n");
if ((in_fp = fopen(argv[1], "r")) == NULL) 
printf("ERROR - cannot open file \n");
else {
getChar();

do {
lex();
} while (nextToken != EOF); 

}
return 0;
}

/* lookup - a function to lookup operators and parentheses as well as handling unknown characters. The return is the token name */

char* lookup(char ch) {
switch (ch) {
case '(':
addChar();
nextToken = LEFT_PAREN;
Token = LEFT_PAREN_;
break;
  
case ')':
addChar();
nextToken = RIGHT_PAREN;
Token = RIGHT_PAREN_;
break;
  
case '+':
addChar();
nextToken = ADD_OP;
Token = ADD_OP_;
break;
  
case '-':
addChar();
nextToken = SUB_OP;
Token = SUB_OP_;
break;

case '*':
addChar();
nextToken = MULT_OP;
Token = MULT_OP_;
break;

case '/':
addChar();
nextToken = DIV_OP;
Token = DIV_OP_;  
break;


case '=':
currentChar = nextChar;//used to track the current character so that I can use getChar() to check for a second '='
addChar();
getChar();
if(currentChar == nextChar){
    nextToken = EQUAL_OP;
    Token = EQUAL_OP_;
    addChar();
    break;
}
else if (currentChar != nextChar){
ungetc(nextChar, in_fp); //used to go back from the get char if the current character is not another equals sign
nextToken = ASSIGN_OP;
Token = ASSIGN_OP_;
break;
}

case '<':
addChar();
getChar();
if(nextChar == '='){
    nextToken = LEQUAL_OP;
    Token = LEQUAL_OP_;
    addChar();
    break;
}
else if (nextChar == '>'){
    nextToken = NEQUAL_OP;
    Token = NEQUAL_OP_;
    addChar();
    break;
}
else{
ungetc(nextChar, in_fp);//same concept as above
nextToken = LESSER_OP;
Token = LESSER_OP_;
break;
}

case '>':
addChar();
getChar();
if(nextChar == '='){
    nextToken = GEQUAL_OP;
    Token = GEQUAL_OP_;
    addChar();
    break;
}
else{
ungetc(nextChar, in_fp); //same concept as above
nextToken = GREATER_OP;
Token = GREATER_OP_;
break;
}

case ';':
addChar();
nextToken = SEMICOLON;
Token = SEMICOLON_;
break;

case '%':
addChar();
nextToken = MOD_OP;
Token = MOD_OP_;
break;

case '{':
addChar();
nextToken = LEFT_CBRACE;
Token = LEFT_CBRACE_;
break;

case '}':
addChar();
nextToken = RIGHT_CBRACE;
Token = RIGHT_CBRACE_;
break;

default: //case for unknown character
addChar();
nextToken = UNKNOWN;
Token = UNKNOWN_;
break;
} 

  return Token;
}

/* addChar - a function to add nextChar to lexeme */
void addChar() {
if (lexLen <= 98) {

lexeme[lexLen++] = nextChar;

lexeme[lexLen] = 0;
}
else
printf("Error - lexeme is too long \n");
}

/* getChar - a function to get the next character of input and determine its character class */
void getChar() {
if ((nextChar = getc(in_fp)) != EOF) {
if (isalpha(nextChar))
charClass = LETTER;

else if (isdigit(nextChar))
charClass = DIGIT;
else charClass = UNKNOWN;
}

else
charClass = EOF;
}

/* getNonBlank - a function to call getChar until it returns a non-whitespace character */
void getNonBlank() {

  while (isspace(nextChar))
      getChar();

  }


/* lex - a lexical analyzer for
expressions */
char* lex() {
lexLen = 0;

getNonBlank();

switch (charClass) {
/* Parse identifiers and keywords*/

case LETTER:
addChar();
getChar();
while (charClass == LETTER || charClass == DIGIT) {
addChar();
getChar();
}
//this keyword solution works for now but I will have to adjust this for Assignment 4
if(lexeme[0] == 'd' && lexeme[1] == 'o'){
    nextToken = KEY_DO;
    Token = KEY_DO_;
    break;
}
if(lexeme[0] == 'r' && lexeme[1] == 'e' && lexeme[2] == 'a' && lexeme[3] == 'd'){ 
    nextToken = KEY_READ;
    Token = KEY_READ_;
    break;
}
if(lexeme[0] == 'w' && lexeme[1] == 'h' && lexeme[2] == 'i' && lexeme[3] == 'l' && lexeme[4] == 'e'){
    nextToken = KEY_WHILE;
    Token = KEY_WHILE_;
    break;
}
if(lexeme[0] == 'p' && lexeme[1] == 'r' && lexeme[2] == 'i' && lexeme[3] == 'n' && lexeme[4] == 't'){
    nextToken = KEY_PRINT;
    Token = KEY_PRINT_;
    break;
}

nextToken = IDENT;
Token = IDENT_;
break;


/* Parse integer literals */
case DIGIT:
addChar();
getChar();
while (charClass == DIGIT) {
addChar();
getChar();
}
nextToken = INT_LIT;
Token = INT_LIT_;
break;
  
/* Parse Parentheses, operators and unknown characters */

case UNKNOWN:
  lookup(nextChar);
  getChar();
break;

/* EOF  end of file*/

case EOF:
nextToken = EOF;
Token = "EOF";
break;


} /* End of switch statement*/
if(nextToken != EOF){
printf("%s\t\t%s\n",lexeme, Token);
  }
  //return Token;
return Token;
} /* End of function lex */