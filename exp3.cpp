#include <iostream>
#include <string>
#include <cctype>
#include <vector>
using namespace std;

enum class TokenType {
    ILLEGAL, END, IDENT, ASSIGN, PLUS, MINUS, MULTIPLY, DIVIDE, AND, OR, LPAREN, RPAREN, LESS_THAN, GREATER_THAN
};

const string tokenStrings[] = {
    "ILLEGAL", "END", "IDENT", "ASSIGN", "PLUS", "MINUS", "MULTIPLY", "DIVIDE", "AND", "OR", "LPAREN", "RPAREN", "LESS_THAN", "GREATER_THAN"
};

struct Token {
    TokenType type;
    string literal;
};

class Lexer {
public:
    Lexer(string input) : input(input), size(input.size()), position(0), next_pos(0), current(0) {
        advance();
    }
    Token next_token();

private:
    string input;
    size_t size, position, next_pos;
    char current;

    void advance();
    Token create_token(TokenType type, char value);
    Token parse_identifier();
    void skip_whitespace();
};

void Lexer::advance() {
    current = (next_pos >= size) ? 0 : input[next_pos];
    position = next_pos++;
}

Token Lexer::create_token(TokenType type, char value) {
    return {type, string(1, value)};
}

Token Lexer::parse_identifier() {
    string identifier = "";
    while (isalpha(current)) {
        identifier += current;
        advance();
    }
    return {TokenType::IDENT, identifier};
}

void Lexer::skip_whitespace() {
    while (isspace(current)) {
        advance();
    }
}

Token Lexer::next_token() {
    skip_whitespace();
    Token token;

    switch (current) {
        case '=': token = create_token(TokenType::ASSIGN, current); break;
        case '+': token = create_token(TokenType::PLUS, current); break;
        case '-': token = create_token(TokenType::MINUS, current); break;
        case '*': token = create_token(TokenType::MULTIPLY, current); break;
        case '/': token = create_token(TokenType::DIVIDE, current); break;
        case '&': token = create_token(TokenType::AND, current); break;
        case '|': token = create_token(TokenType::OR, current); break;
        case '(': token = create_token(TokenType::LPAREN, current); break;
        case ')': token = create_token(TokenType::RPAREN, current); break;
        case '<': token = create_token(TokenType::LESS_THAN, current); break;
        case '>': token = create_token(TokenType::GREATER_THAN, current); break;
        case 0:   token = {TokenType::END, ""}; break;
        default:
            if (isalpha(current)) {
                return parse_identifier();
            } else {
                token = create_token(TokenType::ILLEGAL, current);
            }
            break;
    }

    advance();
    return token;
}

vector<string> tokenize(string input) {
    Lexer lexer(input);
    vector<string> tokens;
    Token currentToken;

    do {
        currentToken = lexer.next_token();
        if (currentToken.type != TokenType::END && currentToken.type != TokenType::ILLEGAL) {
            tokens.push_back(tokenStrings[static_cast<int>(currentToken.type)]);
        }
    } while (currentToken.type != TokenType::END);

    return tokens;
}

bool is_valid_expression(const vector<string>& tokens) {
    bool expect_identifier = true;

    for (const string& type : tokens) {
        if (expect_identifier) {
            if (type == "IDENT") {
                expect_identifier = false;
            } else {
                return false;
            }
        } else {
            if (type == "PLUS" || type == "MINUS" || type == "MULTIPLY" || 
                type == "DIVIDE" || type == "ASSIGN") {
                expect_identifier = true;
            } else {
                return false;
            }
        }
    }
    return !expect_identifier;
}

int main() {
    string input;
    cout << "Enter an expression: ";
    getline(cin, input);
    
    vector<string> tokens = tokenize(input);

    if (is_valid_expression(tokens)) {
        cout << "The expression is valid" << endl;
    } else {
        cout << "The expression is invalid" << endl;
    }

    return 0;
}

// int main() {
//     FILE *file;
//     char expression[MAX_EXPR_LEN];

//     // Step 1: Open the file for reading
//     file = fopen("expression.txt", "r");
//     if (file == NULL) {
//         printf("Error: Could not open file\n");
//         return 1;
//     }

//     // Step 2: Read the expression from the file
//     fgets(expression, MAX_EXPR_LEN, file);
//     fclose(file);

//     // Step 3: Generate the three-address code
//     printf("Three Address Code:\n");
//     generate_three_address_code(expression);

//     return 0;
// }