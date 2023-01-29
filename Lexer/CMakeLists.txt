cmake_minimum_required(VERSION 3.20)
project(Lexer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(
        Lexer main.cpp
        src/Token/TokenType.h
        src/Token/Token.cpp
        src/Token/Token.h
        src/Common/Position.h
        src/Lexer/Lexer.cpp
        src/Lexer/Lexer.h
        src/Lexem/Lexem.h
        src/Lexem/Lexem.cpp
        src/utils/LexerDialog/LexerDialog.cpp
        src/utils/LexerDialog/LexerDialog.h
)

add_executable(
        test test/test.cpp
        src/Token/TokenType.h
        src/Token/Token.cpp
        src/Token/Token.h
        src/Common/Position.h
        src/Lexer/Lexer.cpp
        src/Lexer/Lexer.h
        src/Lexem/Lexem.h
        src/Lexem/Lexem.cpp
        src/utils/LexerDialog/LexerDialog.cpp
        src/utils/LexerDialog/LexerDialog.h
)