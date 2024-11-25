#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <cctype>
using namespace std;

enum class TokenType {
	ILLEGAL, END, IDENT, INT, ASSIGN, PLUS, MINUS, LPAREN, RPAREN, LESS_THAN, GREATER_THAN, 
	MULTIPLY, DIVISION, AUTO, BREAK, CASE, CHAR, CONST, CONTINUE, DEFAULT, DO, DOUBLE, ELSE,
	ENUM, EXTERN, FLOAT, FOR, GOTO, IF, INLINE, INT_KW, LONG, REGISTER, RESTRICT, RETURN, 
	SHORT, SIGNED, SIZEOF, STATIC, STRUCT, SWITCH, TYPEDEF, UNION, UNSIGNED, VOID, VOLATILE, WHILE
};

unordered_map<string, TokenType> keywords = {
	{"auto", TokenType::AUTO}, {"break", TokenType::BREAK}, {"case", TokenType::CASE}, {"char", TokenType::CHAR},
	{"const", TokenType::CONST}, {"continue", TokenType::CONTINUE}, {"default", TokenType::DEFAULT}, {"do", TokenType::DO},
	{"double", TokenType::DOUBLE}, {"else", TokenType::ELSE}, {"enum", TokenType::ENUM}, {"extern", TokenType::EXTERN},
	{"float", TokenType::FLOAT}, {"for", TokenType::FOR}, {"goto", TokenType::GOTO}, {"if", TokenType::IF},
	{"inline", TokenType::INLINE}, {"int", TokenType::INT_KW}, {"long", TokenType::LONG}, {"register", TokenType::REGISTER},
	{"restrict", TokenType::RESTRICT}, {"return", TokenType::RETURN}, {"short", TokenType::SHORT}, {"signed", TokenType::SIGNED},
	{"sizeof", TokenType::SIZEOF}, {"static", TokenType::STATIC}, {"struct", TokenType::STRUCT}, {"switch", TokenType::SWITCH},
	{"typedef", TokenType::TYPEDEF}, {"union", TokenType::UNION}, {"unsigned", TokenType::UNSIGNED}, {"void", TokenType::VOID},
	{"volatile", TokenType::VOLATILE}, {"while", TokenType::WHILE}
};

const string token_names[] = {
	"ILLEGAL", "END", "IDENT", "INT", "ASSIGN", "PLUS", "MINUS", "LPAREN", "RPAREN", 
	"LESS_THAN", "GREATER_THAN", "MULTIPLY", "DIVISION", 
	"AUTO", "BREAK", "CASE", "CHAR", "CONST", "CONTINUE", "DEFAULT", "DO", "DOUBLE", "ELSE",
	"ENUM", "EXTERN", "FLOAT", "FOR", "GOTO", "IF", "INLINE", "INT_KW", "LONG", "REGISTER",
	"RESTRICT", "RETURN", "SHORT", "SIGNED", "SIZEOF", "STATIC", "STRUCT", "SWITCH",
	"TYPEDEF", "UNION", "UNSIGNED", "VOID", "VOLATILE", "WHILE"
};

struct Token {
	TokenType type;
	string literal;
	size_t row;
	size_t col;
};

class Lexer {
public:
	Lexer(string filename) : position(0), read_position(0), row(1), col(0) {
		ifstream file(filename);
		if (file.is_open()) {
			input = string((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
			file.close();
		}
		size = input.size();
		read_char();
	}

	Token next_token();

private:
	string input;
	size_t size;
	size_t position;
	size_t read_position;
	size_t row, col;
	char ch;

	void read_char();
	void skip_whitespace();
	Token read_identifier();
	Token read_number();
	TokenType lookup_identifier(const string& ident);
};

void Lexer::read_char() {
	if (read_position >= size)
		ch = 0;
	else
		ch = input[read_position];

	if (ch == '\n') {
		row++;
		col = 0;
	} else {
		col++;
	}

	position = read_position++;
}

void Lexer::skip_whitespace() {
	while (isspace(ch)) {
		read_char();
	}
}

TokenType Lexer::lookup_identifier(const string& ident) {
	if (keywords.find(ident) != keywords.end()) {
		return keywords[ident];
	}
	return TokenType::IDENT;
}

Token Lexer::read_identifier() {
	string ident;
	size_t start_col = col;
	while (isalpha(ch)) {
		ident += ch;
		read_char();
	}
	return {lookup_identifier(ident), ident, row, start_col};
}

Token Lexer::read_number() {
	string num;
	size_t start_col = col;
	while (isdigit(ch)) {
		num += ch;
		read_char();
	}
	return {TokenType::INT, num, row, start_col};
}

Token Lexer::next_token() {
	skip_whitespace();

	Token tok;

	size_t start_col = col;
	switch (ch) {
		case '=': tok = {TokenType::ASSIGN, string(1, ch), row, col}; break;
		case '+': tok = {TokenType::PLUS, string(1, ch), row, col}; break;
		case '-': tok = {TokenType::MINUS, string(1, ch), row, col}; break;
		case '(': tok = {TokenType::LPAREN, string(1, ch), row, col}; break;
		case ')': tok = {TokenType::RPAREN, string(1, ch), row, col}; break;
		case '<': tok = {TokenType::LESS_THAN, string(1, ch), row, col}; break;
		case '>': tok = {TokenType::GREATER_THAN, string(1, ch), row, col}; break;
		case '*': tok = {TokenType::MULTIPLY, string(1, ch), row, col}; break;
		case '/': tok = {TokenType::DIVISION, string(1, ch), row, col}; break;
		case 0: tok = {TokenType::END, "", row, col}; break;
		default:
			if (isalpha(ch)) return read_identifier();
			if (isdigit(ch)) return read_number();
			tok = {TokenType::ILLEGAL, string(1, ch), row, col};
	}

	read_char();
	return tok;
}

int main(int argc, char** argv) {
	string filename = argv[1];
	Lexer lexer(filename);
	Token token;
	unordered_map<string, int> tokens_count;

	do {
		token = lexer.next_token();
		tokens_count[token_names[static_cast<int>(token.type)]]++;
		cout << token.literal << "\t" << token_names[static_cast<int>(token.type)]
		     << "\t(Row: " << token.row << ", Col: " << token.col << ")" << endl;
	} while (token.type != TokenType::END);

	for(auto tokens:tokens_count)
		cout << tokens.first << " --> " << tokens.second << endl;

	return 0;
}
