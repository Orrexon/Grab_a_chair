/* date = August 16th 2022 11:36 pm */

#ifndef APP_DATA_ACCESS_H

#include "ztring.h"
#include <stdio.h>
#include "token.cpp"
#include "book.h"


char* DateTimeString(time_detail Time)
{
    ztring Result = {0};
    PushScrapStringByRef(Result.String, 16);
    // NOTE(Oscar): just placeholding to have something compiling. fixing it later
    Append(&Result, "2022");//IntToS(Time.tm_year + 1900));
    Append(&Result, "-");
    Append(&Result, IntToS(Time.tm_mon + 1));
    Append(&Result, "-");
    Append(&Result, IntToS(Time.tm_mday));
    Append(&Result, "-");
    Append(&Result, weekdays[Time.tm_wday]);
    Append(&Result, "-");
    Append(&Result, IntToS(Time.tm_hour));
    Append(&Result, "-");
    Append(&Result, IntToS(Time.tm_min));
    
    return Result.String;
}

void SerializeBookInfo(ztring* String, book_info* BookInfo)
{
    Append    (String,"[");
    Append    (String, identifiers[BOOK_START]);
    AppendLine(String,"]");
    Append    (String, "ID:");
    AppendLine(String, IntToS(BookInfo->ID));
    Append    (String, "TableID:");
    AppendLine(String, IntToS(BookInfo->TableID));
    Append    (String, "DateTime:");
    AppendLine(String, DateTimeString(BookInfo->Time));
    Append    (String,"[");
    Append    (String, identifiers[BOOK_END]);
    AppendLine(String,"]");
}

void SerializeTable(ztring* String, table* Table)
{
    v2i Pi = V2i(Table->P);
    Append    (String,"[");
    Append    (String, identifiers[TABLE_START]);
    AppendLine(String,"]");
    Append    (String, "ID:");
    AppendLine(String, IntToS(Table->ID));
    Append    (String, "W:");
    AppendLine(String, IntToS(Table->W));
    Append    (String, "H:");
    AppendLine(String, IntToS(Table->H));
    Append    (String, "CHAIRS:");
    AppendLine(String, IntToS(Table->Chairs));
    Append    (String, "POS:");
    Append    (String, IntToS(Pi.x));
    Append    (String, ",");
    AppendLine(String, IntToS(Pi.y));
    Append    (String,"[");
    Append    (String, identifiers[TABLE_END]);
    AppendLine(String,"]");
}

void Deserialize(FILE* file, table* Tables, int TableCount)
{
    for(int Index = 0; Index<TableCount; ++Index)
    {
        if(FindNextRow(file))
        {
            identifier Ident = {0};
            NextLine(file);
            if(FindIdentifier(file, &Ident, TABLE_ID, COLON))
            {
                Tables[Index].ID = ExtractValueInt(file);
            }
            if(FindIdentifier(file, &Ident, TABLE_WIDTH, COLON))
            {
                Tables[Index].W = ExtractValueInt(file);
            }
            if(FindIdentifier(file, &Ident, TABLE_HEIGHT, COLON))
            {
                Tables[Index].H = ExtractValueInt(file);
            }
            if(FindIdentifier(file, &Ident, TABLE_CHAIRS, COLON))
            {
                Tables[Index].Chairs = ExtractValueInt(file);
            }
            if(FindIdentifier(file, &Ident, TABLE_POSITION, COLON))
            {
                Tables[Index].P = ExtractValueV2(file);
            }
        }
    }
}

bool SaveTablePositions(app_state* State)
{
    FILE* file = fopen("./../data/table_positions.txt", "w+b");
    if(file)
    {
        ztring String = {0};
        int SizeBytes = 128;
        PushScrapStringByRef(String.String, SizeBytes*State->TableCount);
        for(int tableIndex = 0; tableIndex<State->TableCount; ++tableIndex)
        {
            table tbl = State->Tables[tableIndex];
            SerializeTable(&String, &tbl);
        }
        
        if(!fwrite(String.String, sizeof(char), String.Count, file))
        {
            IM_ASSERT(!"Wth happened dude-man? ");
        }
        fclose(file);
        ResetStringArena();
        return true;
    }
    return false;
}

time_detail SetTime(int Row, int Col)
{
    time_t rawtime;
    time_detail* Result = {0};
    time( &rawtime );
    Result = localtime( &rawtime );
    
    // TODO(Oscar): This is of course not gonna work, it's just prototyping
    Result->tm_wday = (Result->tm_wday + Row) % 7;
    Result->tm_hour = (Result->tm_hour + (Col + 9))%24;
    
    return *Result;
}

void BookTable(app_state* State, table BookedTable, int Row, int Col, char* Name)
{
    FILE* file = fopen("./../data/bookings.txt", "w+b");
    if(file)
    {
        book_info Info = {0};
        Info.ID = State->BookCount++;
        Info.TableID = BookedTable.ID;
        Info.Time = SetTime(Row, Col);
        int size = CountString(Name);
        PushScrapStringByRef(Info.Name, size+1);
        RealCopy(Info.Name,Name, size, char);
        ztring String = {0};
        PushScrapStringByRef(String.String, 128);
        SerializeBookInfo(&String, &Info);
        
        fputs(String.String, file);
        
        fclose(file);
        ResetStringArena();
    }
}

bool LoadTablePositions(app_state* State)
{
    FILE* file = fopen("./../data/table_positions.txt", "rb");
    if(file)
    {
        Deserialize(file, State->Tables, State->TableCount);
        
        fclose(file);
        return true;
    }
    return false;
}

#define APP_DATA_ACCESS_H

#endif //APP_DATA_ACCESS_H
