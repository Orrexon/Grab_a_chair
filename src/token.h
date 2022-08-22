/* date = August 16th 2022 11:43 pm */

#ifndef TOKEN_H

// TODO(Oscar): look up formal names etc
enum identifier_type
{
    UNKNOWN_IDENTIFIER,
    TABLE_START,//row start
    TABLE_END,//row end really IG
    TABLE_ID,
    TABLE_POSITION,
    TABLE_WIDTH,
    TABLE_HEIGHT,
    TABLE_CHAIRS,
    BOOK_START,
    BOOK_ID,
    BOOK_TABLE_ID,
    BOOK_DATE_TIME,
    BOOK_END
        
};

char* identifiers[]
{
    "_",
    "START",
    "END",
    "ID",
    "POS",
    "W",
    "H",
    "CHAIRS",
    "START",
    "ID",
    "TableID",
    "DateTime",
    "END"
};

struct identifier
{
    identifier_type Type;
    char* Identifier;
};

enum token_type
{
    UNKNOWN_TOKEN,
    FAILED,
    OPEN_SQUARE_BRACE,
    CLOSE_SQUARE_BRACE,
    COLON
};

char tokens[]
{
    '_',
    '\0',
    '[',
    ']',
    ':'
};


struct token
{
    token_type Type;
    char Val;
};

token TokenFailed()
{
    return token{FAILED};
}


#define TOKEN_H

#endif //TOKEN_H
