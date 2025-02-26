#include "Scanner.hpp"

const std::unordered_map<std::string, TokenType> My::Scanner::keywords =
{
    {"and",    TokenType::AND},
    {"class",  TokenType::CLASS},
    {"else",   TokenType::ELSE},
    {"false",  TokenType::MY_FALSE},
    {"for",    TokenType::FOR},
    {"fun",    TokenType::FUN},
    {"if",     TokenType::IF},
    {"nil",    TokenType::NIL},
    {"or",     TokenType::OR},
    {"print",  TokenType::PRINT},
    {"return", TokenType::RETURN},
    {"super",  TokenType::SUPER},
    {"this",   TokenType::THIS},
    {"true",   TokenType::MY_TRUE},
    {"var",    TokenType::VAR},
    {"while",  TokenType::WHILE}
};

My::Scanner::Scanner(const std::string& source)
    : source(source)
{

}

std::vector<My::Token> My::Scanner::scanTokens()
{
    while (!isAtEnd())
    {
        start = current;
        scanToken();
    }

    tokens.emplace_back(Token(TokenType::MY_EOF, "", nullptr, line));
    return tokens;
}

bool My::Scanner::isAtEnd()
{
    return current >= source.size();
}

bool My::Scanner::isAlpha(char c)
{
    bool condition = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
    return condition;
}

bool My::Scanner::isDigit(char c)
{
    return c >= '0' && c <= '9';
}

bool My::Scanner::isAlphaNumeric(char c)
{
    return isAlpha(c) || isDigit(c);
}

bool My::Scanner::match(char expected)
{
    if(isAtEnd() || source.at(current) != expected)
    {
        return false;
    }
    else
    {
        current++;
        return true;
    }
}

void My::Scanner::scanToken()
{
    char c = advance();
    switch (c)
    {
        case '(':
        {
            addToken(TokenType::LEFT_PAREN);
            break;
        }
        case ')':
        {
            addToken(TokenType::RIGHT_PAREN);
            break; 
        }
        case '{':
        {
            addToken(TokenType::LEFT_BRACE);
            break;
        }
        case '}':
        {
            addToken(TokenType::RIGHT_BRACE);
            break;
        }
        case ',':
        {
            addToken(TokenType::COMMA);
            break;
        }
        case '.':
        { 
            addToken(TokenType::DOT);
            break;
        }
        case '-':
        {
            addToken(TokenType::MINUS);
            break;
        }
        case '+':
        {
            addToken(TokenType::PLUS);
            break;
        }
        case ';':
        {
            addToken(TokenType::SEMICOLON);
            break;
        }
        case '*':
        {
            addToken(TokenType::STAR);
            break;
        }
        case '[':
        {
            addToken(TokenType::LEFT_BRACKET);
            break;
        }
        case ']':
        {
            addToken(TokenType::RIGHT_BRACKET);
            break;
        }
        case '!':
        { 
            addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
            break; 
        }
        case '=':
        {
            addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
            break; 
        }
        case '<':
        {
            addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
            break;
        }
        case '>':
        {
            addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
            break;
        }
        case '/':
        {
            if(match('/'))
            {
                while(peek() != '\n' && !isAtEnd())
                {
                    advance();
                }
            }
            else
            {
                addToken(TokenType::SLASH);
            }
            break; 
        }
        case ' ':
        case '\r':
        case '\t':
        {
            break;
        }
        case '\n':
        { 
            break;
        }
        case '"': 
        { 
            break; 
        }
        default:
        {
            if(isDigit(c))
            {
                number();
            }
            else if(isAlpha(c))
            {
                identifier();
            }
            else
            {
                Debug::error(line, "Unexpected character.");
            }
            break;
        }
    }
}

char My::Scanner::advance()
{
    current++;
    return source.at(current - 1);
}

void My::Scanner::addToken(TokenType type)
{
    addToken(type, nullptr);
}

void My::Scanner::addToken(TokenType type, std::any literal)
{
    std::string text = source.substr(start, current - start);
    tokens.emplace_back(Token(type, text, literal, line));
}

char My::Scanner::peek()
{
    if (isAtEnd())
    {
        return '\0';
    }
    else
    {
        return source.at(current);
    }
    
}

char My::Scanner::peekNext()
{
    if (current + 1 >= source.length())
    {
        return '\0';
    }

    return source.at(current + 1);
}

void My::Scanner::string()
{
    while(peek() != '"' && !isAtEnd())
    {
        if(peek() == '\n')
        {
            line++;
        }
        advance();
    }

    if(isAtEnd())
    {
        Debug::error(line, "Unterminated string.");
        return;
    }

    advance();

    std::string value = source.substr(start + 1, current - start + 1);
    addToken(TokenType::STRING, value);
}

void My::Scanner::number()
{
    while(isDigit(peek()))
    {
        advance();
    }
    if(peek() == '.' && isDigit(peekNext()))
    {
        advance();
        while(isDigit(peek()))
        {
            advance();
        }
    }

    std::string value(source.substr(start, current - start));
    addToken(TokenType::NUMBER, value);
}

void My::Scanner::identifier()
{
    while(isAlphaNumeric(peek()))
    {
        advance();
    }
    std::string text = source.substr(start, current - start);
    auto keyword = keywords.find(text);
    if (keyword != keywords.end())
    {
        addToken(keyword->second);
    }
    else
    {
        addToken(TokenType::IDENTIFIER);
    }
}