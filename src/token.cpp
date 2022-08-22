#include "token.h"

#define ASCII_NUMBER(c) ((c)>='0'&&(c)<='9')

bool FindToken(FILE* file, token* Token, token_type Type)
{
    while(Token->Type != Type)
    {
        char c = getc(file);
        if(c == tokens[Type])
        {
            Token->Type = Type;
            Token->Val = c;
            return true;
        }
        
        if(c == EOF)
        {
            rewind(file);
            return false;
        }
    }
    
    return false;
}

// TODO(Oscar): Bad name, it's not peeking any more
int PeekLineToken(FILE* file, token_type Type)
{
    int Result = 0;
    FILE* fileRunner = file;
    
    char c = getc(fileRunner);
    
    while(c != tokens[Type])
    {
        c = getc(fileRunner);
        if(c=='\n' || c==EOF)
        {
            fseek(file, -(Result+1), SEEK_CUR);
            return -1;
        }
        Result += ASCII_NUMBER(c)*1;
    }
    fseek(file, -(Result+1), SEEK_CUR);
    return Result;
}

int PeekToken(FILE* file, token_type Type)
{
    int Result = 0;
    FILE* fileRunner = file;
    
    char c = getc(fileRunner);
    
    while(c != tokens[Type])
    {
        c = getc(fileRunner);
        if(c==EOF)
        {
            fseek(file, -(Result+1), SEEK_CUR);
            return -1;
        }
        Result += ASCII_NUMBER(c)*1;
    }
    fseek(file, -(Result+1), SEEK_CUR);
    return Result;
}

int OffsetToCharacter(FILE* file, char Character)
{
    int Result = 0;
    while(true)
    {
        char c = getc(file);
        if(c==EOF)
        {
            fseek(file, -(Result+1), SEEK_CUR);
            return -1;
        }
        if(c==Character)
        {
            int breakpoint = fseek(file, -(Result+1), SEEK_CUR);
            return Result;
        }
        
        Result += ASCII_NUMBER(c)*1;
    }
}

bool FindIdentifier(FILE* file, identifier* Ident, identifier_type Type, token_type TokenType)
{
    int OffsetToken = PeekToken(file, TokenType);
    
    if(OffsetToken != -1)
    {
        char* String;
        PushScrapStringByRef(String, OffsetToken + 1);
        for(int i = 0; i< OffsetToken; ++i)
        {
            String[i] = getc(file);
        }
        
        // TODO(Oscar): Compare case? meh...
        if(CompareStringIgnoreCase(String, identifiers[Type]))
        {
            PushScrapStringByRef(Ident->Identifier, OffsetToken + 1);
            CopyString(Ident->Identifier, String, OffsetToken);
            Ident->Type = Type;
            return true;
        }
    }
    return false;
}

bool FindNextRow(FILE* file)
{
    bool Result = false;
    
    token Token = {0};
    if(FindToken(file, &Token, OPEN_SQUARE_BRACE))
    {
        identifier Ident  = {0};
        if(FindIdentifier(file, &Ident, TABLE_START, CLOSE_SQUARE_BRACE))
        {
            Result = true;
        }
    }
    
    return Result;
}

void NextLine(FILE* file)
{
    while(getc(file) != '\n');
}

int ExtractValueInt(FILE* file)
{
    int offset = OffsetToCharacter(file, '\n');
    char* String;
    PushScrapStringByRef(String, offset + 1);
    for(int i = 0; i< offset; ++i)
    {
        String[i] = getc(file);
    }
    return StoInt(String, offset);
}

v2 ExtractValueV2(FILE* file)
{
    int offset = OffsetToCharacter(file, ',');
    char* String;
    PushScrapStringByRef(String, offset + 1);
    for(int i = 0; i< offset; ++i)
    {
        String[i] = getc(file);
    }
    float X = (float)StoInt(String, offset);
    
    offset = OffsetToCharacter(file, '\n');
    for(int i = 0; i< offset; ++i)
    {
        String[i] = getc(file);
    }
    float Y = StoInt(String, offset);
    
    return V2(X,Y);
}