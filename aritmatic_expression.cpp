#include <iostream>
#include <string>
#include <cctype>
#include <vector>
using namespace std;

enum class TokenType {
    ILLEGAL, END, IDENT, ASSIGN, PLUS, MINUS, MULTIPLY, DIVIDE, AND, OR, LPAREN, RPAREN, LESS_THAN, GREATER_THAN
};

const string enum_vals[] = {
    "ILLEGAL", "END", "IDENT", "ASSIGN", "PLUS", "MINUS", "MULTIPLY", "DIVIDE", "AND", "OR", "LPAREN", "RPAREN", "LESS_THAN", "GREATER_THAN"
};

struct token {
    TokenType type;
    string literal;
};

class Lexer {
public:
    Lexer(string input) : input(input), size(input.size()), position(0), read_position(0), ch(0) {
        readchar();
    }
    struct token next_token();

private:
    string input;
    size_t size;
    size_t position;
    size_t read_position;
    char ch;

    void readchar();
    int skip_white_spaces();
    struct token new_token(TokenType type, char ch);
    struct token read_identifier();
    struct token read_number();
};

void Lexer::readchar() {
    if (read_position >= size)
        ch = 0;
    else
        ch = input[read_position];
    position = read_position++;
}

struct token Lexer::new_token(TokenType type, char ch) {
    return {type, string(1, ch)};
}

struct token Lexer::read_identifier() {
    string ident = "";
    while (isalpha(ch)) {
        ident += ch;
        readchar();
    }
    return {TokenType::IDENT, ident};
}

int Lexer::skip_white_spaces(){
    if(ch == ' ' || ch == '\n' || ch == '\t')
        readchar();
    if(ch == ' ' || ch == '\n' || ch == '\t')
        return 1;
    return 0;
}

struct token Lexer::next_token() {
    while(skip_white_spaces());
    struct token this_token;

    switch (ch) {
        case '=':
            this_token = new_token(TokenType::ASSIGN, ch);break;
        case '+':
            this_token = new_token(TokenType::PLUS, ch);break;
        case '-':
            this_token = new_token(TokenType::MINUS, ch);break;
        case '*':
            this_token = new_token(TokenType::MULTIPLY, ch);break;
        case '/':
            this_token = new_token(TokenType::DIVIDE, ch);break;
        case '&':
            this_token = new_token(TokenType::AND, ch);break;
        case '|':
            this_token = new_token(TokenType::OR, ch);break;
        case '(':
            this_token = new_token(TokenType::LPAREN, ch);break;
        case ')':
            this_token = new_token(TokenType::RPAREN, ch);break;
        case '<':
            this_token = new_token(TokenType::LESS_THAN, ch);break;
        case '>':
            this_token = new_token(TokenType::GREATER_THAN, ch);break;
        case 0:
            this_token = {TokenType::END, ""};break;
        default:
            if (isalpha(ch))
                return read_identifier();
            else
                this_token = new_token(TokenType::ILLEGAL, ch);
            break;
    }

    readchar();
    return this_token;
}

vector<string> get_tokens(string input) {
    Lexer lexer(input);
    vector<string> tokens;

    struct token curr_token;

    do {
        curr_token = lexer.next_token();

        if (curr_token.type != TokenType::END && curr_token.type != TokenType::ILLEGAL) {
            tokens.push_back(enum_vals[static_cast<int>(curr_token.type)]);
        }

    } while (curr_token.type != TokenType::END);

    return tokens;
}

bool check_expression(const vector<string>& tokens) {
    bool expect_operand = true; 
    bool valid_expression = true;

    for (const string& token_type : tokens) {
        if (expect_operand) {
            if (token_type == "IDENT") {
                expect_operand = false; 
            } else {
                valid_expression = false;
                break;
            }
        } else {
            if (token_type == "PLUS" || token_type == "MINUS" || 
                token_type == "MULTIPLY" || token_type == "DIVIDE" || 
                token_type == "ASSIGN") {
                expect_operand = true; 
            } else {
                valid_expression = false; 
                break;
            }
        }
    }

    return valid_expression && !expect_operand;
}

int main(int argc, char** argv) {
    string input = "a = b + c";
    if(argc == 2){
        input = argv[1];
    }
    vector<string> tokens = get_tokens(input);
    bool ans = check_expression(tokens);
    if(ans)
        cout << "the expression " << input <<" is valid" << endl;
    else
        cout << "the expression " << input <<" is invalid" << endl;
    return 0;
}
