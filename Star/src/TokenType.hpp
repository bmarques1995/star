#pragma once

namespace Star
{
    enum class TokenType
    {
        // Tokens de Caracteres Únicos
        LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
        COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

        // Tokens de um ou dois Caracteres
        BANG, BANG_EQUAL,
        EQUAL, EQUAL_EQUAL,
        GREATER, GREATER_EQUAL,
        LESS, LESS_EQUAL,

        // Tokens literais
        IDENTIFIER, STRING, NUMBER,

        // Palavras-chave
        AND, CLASS, ELSE, ST_FALSE, FUN, FOR, IF, NIL, OR,
        PRINT, RETURN, SUPER, THIS, ST_TRUE, VAR, WHILE,

        // Token para final de declaração
        ST_EOF 
    };
}