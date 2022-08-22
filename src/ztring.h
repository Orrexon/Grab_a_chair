/* date = August 16th 2022 11:39 pm */

#ifndef ZTRING_H
#include "app_memory.h"

struct ztring
{
    char* String;
    size_t Count;
    size_t Current;
};

int CountString(char* string)
{
    int Result = 0;
    for (int i = 0; i < string[i] != 0; i += 1)
    {
        ++Result;
    }
    
    return Result;
}

int CountString(ztring String)
{
    String.Count = CountString(String.String);
    
    return String.Count;
}

void CopyString(char* dest, char* source, size_t count)
{
    for(int index = 0; index < count; ++index)
    {
        dest[index] = source[index];
    }
}

//TODO Oscar: varargs
void Concat(char* dest, char* source1, char* source2, char seperator = 0)
{
    while(*source1 != '\0')
    {
        *dest++ = *source1++;
    }
    if(seperator)
    {
        *dest++ = seperator;
    }
    while(*source2 != '\0')
    {
        *dest++ = *source2++;
    }
}

void Concat(ztring* dest, char* source1, char* source2, char seperator = 0)
{
    while(*source1 != '\0')
    {
        *dest->String++ = *source1++;
        dest->Count++;
    }
    if(seperator)
    {
        *dest->String++ = seperator;
        dest->Count++;
    }
    while(*source2 != '\0')
    {
        *dest->String++ = *source2++;
        dest->Count++;
    }
}

void Append(ztring* Dest, char* Source)
{
    char* destRunner = (Dest->String + Dest->Current);
    while(*Source != '\0')
    {
        *destRunner++ = *Source++;
        Dest->Count++;
    }
    Dest->Current = Dest->Count;
}

void AppendLine(ztring* Dest, char* Source)
{
    Append(Dest, Source);
    Append(Dest, "\n");
}

#define RealCopy(dest, source, count, type) RealCopy_(dest, source, (sizeof(type) * count))
void RealCopy_(void* dest, void* source, int bytes)
{
    char* DestRunner = (char*)dest;
    char *SourceRunner = (char*)source;
    
    while(bytes--)
    {
        *DestRunner++ = *SourceRunner++;
    }
    
}

int StoInt(char* string, size_t size)
{
    
    int Result = 0;
    int multiplier = 1;
    for(int i=0; i<size-1;++i)
    {
        multiplier *= 10;
    }
    
    for(int i = 0; i<size; ++i)
    {
        Result += (string[i] - '0') * multiplier;
        multiplier /= 10;
    }
    
    return Result;
}

// TODO(Oscar): to be continued :) 
// TODO(Oscar): I know I can probably google this or use stdlib or whatever
// TODO(Oscar): but no, I am too stubborn : )Just need to figure out the missing 
// TODO(Oscar): stuff from this algorithm. 
void ItoStr(int value)
{
    char Result[16] = {0};
    int divisor = 1;
    for(; value/divisor >= 10 ;)
    {
        divisor *= 10;
    }
    for(int i = 0; value/divisor <= 10; ++i)
    {
        Result[i] = value/divisor + '0';
        value/=10;
        divisor/=10;
    }
}

// TODO(Oscar): broken will replace with another, above... 
int MakeIntString(unsigned char* String, int Count)
{
    int Result = 0;
    for(int i = 0; i<Count; ++i)
    {
        if(String[i+Result] >= 10)
        {
            int div = String[i+Result]/10;
            if(div>=10)
            {
                int FirstDigit = div/10;
                int SecondDigit = div%10;
                int LastDigit = String[i+Result]%10;
                String[i+Result] = FirstDigit + '0';
                String[i+Result+1] = SecondDigit + '0';
                String[i+Result+2] = LastDigit + '0';
                Result = 2;
            }
            else
            {
                int FirstDigit = div;
                int LastDigit = String[i+Result]%10;
                String[i+Result] = FirstDigit + '0';
                String[i+Result+1] = LastDigit + '0';
                Result = 1;
            }
            
        }
        else
        {
            String[i+Result] += '0';
            Result = 0;
        }
    }
    
    return Result;
}

char* IntToS(int Number)
{
    char* Result;
    PushScrapStringByRef(Result, 16);
    if(Number > 0xFF)
    {
        // TODO(Oscar): broken for more digits making a new one
        int bytes = 0;
        int shift = 0;
        while(Number & (0xFF << shift))
        {
            shift += 8;
        }
        bytes = shift/8;
        
        int Count = 0;
        while(Count < bytes)
        {
            Result[Count] = ((Number >> (((bytes-1)-Count))*8) & 0xFF);
            Count++;
        }
        
        int offset = 0;
        for(int idx = 0; idx<Count; ++idx)
        {
            offset += MakeIntString((unsigned char* )&Result[offset], 0);
        }
    }
    else
    {
        Result[0] = (Number)&0xFF;
        MakeIntString((unsigned char* )Result, 1);
    }
    return Result;
}

bool
CompareStringIgnoreCase(char* A , char* B)
{
    char* ARunner = A;
    char* BRunner = B;
    while(*ARunner && *BRunner)
    {
        if(!((*ARunner++ | 1<<5) == (*BRunner++ | 1<<5)))
            return false;
    }
    
    return true;
}


#define ZTRING_H

#endif //ZTRING_H
