#include "Scanner.hpp"

Star::Scanner::Scanner(const std::string &source) :
    source(source)
{
    keywords = {
        {"and",    TokenType::AND},
        {"class",  TokenType::CLASS},
        {"else",   TokenType::ELSE},
        {"false",  TokenType::ST_FALSE},
        {"for",    TokenType::FOR},
        {"fun",    TokenType::FUN},
        {"if",     TokenType::IF},
        {"nil",    TokenType::NIL},
        {"or",     TokenType::OR},
        {"print",  TokenType::PRINT},
        {"return", TokenType::RETURN},
        {"super",  TokenType::SUPER},
        {"this",   TokenType::THIS},
        {"true",   TokenType::ST_TRUE},
        {"var",    TokenType::VAR},
        {"while",  TokenType::WHILE}
    };
}

std::vector<Star::Token> Star::Scanner::ScanTokens()
{
    while (!IsAtEnd())
    {
        start = current;
        ScanToken();
    }
    
    tokens.emplace_back(TokenType::ST_EOF, "", nullptr, line);
    return tokens;
}

bool Star::Scanner::IsAtEnd()
{
    return current >= source.length();
}

bool Star::Scanner::IsAlpha(char c)
{
    return (c >= 'a' && c <= 'z') ||
        (c >= 'A' && c <= 'Z') ||
        (c == '_');
}

bool Star::Scanner::IsDigit(char c)
{
    return (c >= '0' && c <= '9');
}

bool Star::Scanner::IsAlphaNumeric(char c)
{
    return IsAlpha(c) || IsDigit(c);
}

bool Star::Scanner::Match(char expected)
{
    if(IsAtEnd() || source.at(current) != expected) return false;
    current++;
    return true;
}

void Star::Scanner::ScanToken()
{
    char c = Advance();
    switch (c) {
        case '(': AddToken(TokenType::LEFT_PAREN); break;
        case ')': AddToken(TokenType::RIGHT_PAREN); break;
        case '{': AddToken(TokenType::LEFT_BRACE); break;
        case '}': AddToken(TokenType::RIGHT_BRACE); break;
        case ',': AddToken(TokenType::COMMA); break;
        case '.':
        {
            if (IsDigit(PeekNext()))
                Number();
            else
                AddToken(TokenType::DOT); 
            break; 
        }
        case '-': AddToken(TokenType::MINUS); break;
        case '+': AddToken(TokenType::PLUS); break;
        case ';': AddToken(TokenType::SEMICOLON); break;
        case '*': AddToken(TokenType::STAR); break;
        case '[': AddToken(TokenType::LEFT_BRACKET); break;
        case ']': AddToken(TokenType::RIGHT_BRACKET); break;
        case '!':
            AddToken(Match('=') ? TokenType::BANG_EQUAL : TokenType::BANG); break;
        case '=':
            AddToken(Match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL); break;
        case '<':
            AddToken(Match('=') ? TokenType::LESS_EQUAL : TokenType::LESS); break;
        case '>':
            AddToken(Match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
            break;
        case '/':
        {
            if (Match('/'))
                while (Peek() != '\n' && !IsAtEnd())
                    Advance();
            else
                AddToken(TokenType::SLASH);
            break;
        }    
        case ' ':
        case '\r':
        case '\t':
            break;
        case '\n':
            break;
        case '"':
            break;
        default:
            if (IsDigit(c))
                Number();
            else if (IsAlpha(c))
                Identifier();
            else
                Debug::Error(line, "Unexpected character");
            break;
    }
}

char Star::Scanner::Advance()
{
    return source.at(current++);
}

void Star::Scanner::AddToken(TokenType type)
{
    AddToken(type, nullptr);
}

void Star::Scanner::AddToken(TokenType type, std::any literal)
{
    std::string text = source.substr(start, current - start);
    tokens.emplace_back(type, text, literal, line);
}

char Star::Scanner::Peek()
{
    if(IsAtEnd())
        return '\0';
    return source.at(current);
}

char Star::Scanner::PeekNext()
{
    if ((current + 1) > source.length())
        return '\0';
    return source.at(current + 1);
}

void Star::Scanner::String()
{
    char c = Peek();
    while (c != '\"' && !IsAtEnd())
    {
        if (c == '\\')
        {
            if (PeekNext() == '\"')
            {
                Advance();
                Advance();
            }
        }
        if (c == '\n')
        {
            line++;
        }
        Advance();
        c = Peek();
    }
}

void Star::Scanner::Number()
{
    GetNumberBody();
    GetNumberExponent();
    GetNumberSuffix();
    std::string numberToken = source.substr(start, current - start);
    AddToken(TokenType::NUMBER);
}

void Star::Scanner::Identifier()
{
    while(IsAlphaNumeric(Peek()))
        Advance();
    std::string text = source.substr(start, current - start);
    auto keyword = keywords.find(text);
    TokenType type = keyword != keywords.end() ? keyword->second : TokenType::IDENTIFIER;
    AddToken(type);
}

void Star::Scanner::GetNumberBody()
{
    bool isDecimal = false;
    char c = Peek();
    if(c == '.')
    {
        Advance();
        c = Peek();
        isDecimal = true;
        if(!IsDigit(c))
        {
            Debug::Error(line, "Expected digit after decimal point.");
            return;
        }
    }
    if(IsDigit(c))
    {
        Advance();
        c = Peek();
    }
    while(IsDigit(c) || c == '.')
    {
        Advance();
        c = Peek();
        if(c == '.')
        {
            if(isDecimal)
            {
                Debug::Error(line, "Multiple decimal points in number.");
                return;
            }
            isDecimal = true;
        }
    }
}

void Star::Scanner::GetNumberExponent()
{
    char c = Peek();
    if(c == 'e' || c == 'E')
    {
        Advance();
        c = Peek();
        if(c == '+' || c == '-')
            Advance();
        c = Peek();
        if(!IsDigit(c))
        {
            // Report error: expected digit after exponent
            Debug::Error(line, "Expected digit after exponent.");
            return;
        }
        while(IsDigit(c))
        {
            Advance();
            c = Peek();
        }
    }
}

void Star::Scanner::GetNumberSuffix()
{
    char c = Peek();
    if(c == 'f')
    {
        Advance();
        return; // float
    }
    if(c == 'i' || c == 'u')
    {
        Advance();
        c = Peek();
        while (IsDigit(c))
        {
            Advance();
            c = Peek();
        }
    }
}

/*
void Star::Scanner::ScanNumberType(const std::string &suffixStr, bool isDecimal, std::type_index *literalType)
{
    static const std::unordered_map<std::string, std::type_index> intSuffixTypeMap = {
        {"i8", typeid(int8_t)}, {"u8", typeid(uint8_t)},
        {"i16", typeid(int16_t)}, {"u16", typeid(uint16_t)},
        {"i32", typeid(int32_t)}, {"u32", typeid(uint32_t)},
        {"i64", typeid(int64_t)}, {"u64", typeid(uint64_t)}
    };
    if(isDecimal)
    {
        if((suffixStr.compare("f") == 0))
            *literalType = typeid(float);
        else
            Debug::Error(line, "Invalid type, float numbers can only be assigned with f or empty, for double");
        return;
    }
    auto it = intSuffixTypeMap.find(suffixStr);
    if(it != intSuffixTypeMap.end())
        *literalType = it->second;
    else
        Debug::Error(line, "Invalid type, integers must be assigned as (i|u)(8|16|32|64)");
}
*/