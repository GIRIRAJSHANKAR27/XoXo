#include <iostream>
#include <string>
#include <vector>
#include <cctype>

enum class TokenType {
    KEYWORD,
    IDENTIFIER,
    NUMBER,
    SYMBOL,
    UNKNOWN
};

struct Token {
    TokenType type;
    std::string value;
};

bool isKeyword(const std::string& word) {
    return word == "if" || word == "else" || word == "while" || word == "return" || word == "int" || word == "float" || word == "void";
}

std::vector<Token> lexicalAnalyzer(const std::string& code) {
    std::vector<Token> tokens;
    std::string currentToken;
    
    for (char ch : code) {
        if (std::isspace(ch)) {
            if (!currentToken.empty()) {
                // Check if the current token is a keyword, identifier, or number
                TokenType type;
                if (isKeyword(currentToken)) {
                    type = TokenType::KEYWORD;
                } else if (std::isdigit(currentToken[0])) {
                    type = TokenType::NUMBER;
                } else {
                    type = TokenType::IDENTIFIER;
                }
                tokens.push_back({type, currentToken});
                currentToken.clear();
            }
        } else if (std::isalpha(ch) || ch == '_') {
            currentToken += ch; // Build identifier or keyword
        } else if (std::isdigit(ch)) {
            currentToken += ch; // Build number
        } else {
            if (!currentToken.empty()) {
                // Handle the previous token
                TokenType type;
                if (isKeyword(currentToken)) {
                    type = TokenType::KEYWORD;
                } else if (std::isdigit(currentToken[0])) {
                    type = TokenType::NUMBER;
                } else {
                    type = TokenType::IDENTIFIER;
                }
                tokens.push_back({type, currentToken});
                currentToken.clear();
            }
            // Handle symbols directly
            tokens.push_back({TokenType::SYMBOL, std::string(1, ch)});
        }
    }

    // Handle any remaining token
    if (!currentToken.empty()) {
        TokenType type;
        if (isKeyword(currentToken)) {
            type = TokenType::KEYWORD;
        } else if (std::isdigit(currentToken[0])) {
            type = TokenType::NUMBER;
        } else {
            type = TokenType::IDENTIFIER;
        }
        tokens.push_back({type, currentToken});
    }

    return tokens;
}

void printTokens(const std::vector<Token>& tokens) {
    for (const auto& token : tokens) {
        std::string typeName;
        switch (token.type) {
            case TokenType::KEYWORD: typeName = "KEYWORD"; break;
            case TokenType::IDENTIFIER: typeName = "IDENTIFIER"; break;
            case TokenType::NUMBER: typeName = "NUMBER"; break;
            case TokenType::SYMBOL: typeName = "SYMBOL"; break;
            case TokenType::UNKNOWN: typeName = "UNKNOWN"; break;
        }
        std::cout << typeName << ": " << token.value << std::endl;
    }
}

int main() {
    std::string sampleCode = "int main() { if (x == 10) return 1; }";
    auto tokens = lexicalAnalyzer(sampleCode);
    printTokens(tokens);
    return 0;
}
