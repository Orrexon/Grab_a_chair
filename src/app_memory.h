/* date = August 15th 2022 3:46 pm */

#ifndef APP_MEMORY_H

#define DefaultSize 1024*1000 //1 MB
#define DefaultStringArenaSize DefaultSize*1000 //1 GB
#define DefaultScrapHeapSize DefaultStringArenaSize
#define Assert(condition) if((!(condition))){int* i = 0; *i = 0;}

struct memory_arena
{
    void* Base;
    size_t Used;
    size_t Max;
};

memory_arena CreateArena()
{
    memory_arena Result = {};
    Result.Base = VirtualAlloc(0, DefaultSize, MEM_COMMIT|MEM_RESERVE, PAGE_READWRITE);
    Result.Max = DefaultSize;
    
    return Result;
}

memory_arena CreateArena(size_t size)
{
    memory_arena Result = {};
    Result.Base = VirtualAlloc(0, size, MEM_COMMIT|MEM_RESERVE, PAGE_READWRITE);
    Result.Max = size;
    
    return Result;
}


memory_arena CreateStringArena()
{
    memory_arena Result = {};
    Result.Base = VirtualAlloc(0, DefaultStringArenaSize, MEM_COMMIT|MEM_RESERVE, PAGE_READWRITE);
    Result.Max = DefaultStringArenaSize;
    
    return Result;
}

memory_arena CreateScrapHeap()
{
    memory_arena Result = {};
    Result.Base = VirtualAlloc(0, DefaultScrapHeapSize, MEM_COMMIT|MEM_RESERVE, PAGE_READWRITE);
    Result.Max = DefaultScrapHeapSize;
    
    return Result;
}


static memory_arena ScrapHeap = {};
static memory_arena StringArena = {};

#define PushStructScrapHeap(type, count)                         \
if(ScrapHeap.Base)                                           \
{                                                            \
type = (char*)PushSize_(&ScrapHeap, sizeof(char)*count); \
}                                                            \
else                                                         \
{                                                            \
ScrapHeap = CreateScrapHeap();                           \
type = (char*)PushSize_(&ScrapHeap, sizeof(char)*count); \
}

#define PushScrapStringByRef(string, count)                               \
if(StringArena.Base)                                             \
{                                                                \
string = (char*)PushSize_(&StringArena, sizeof(char)*count); \
}                                                                \
else                                                             \
{                                                                \
StringArena = CreateStringArena();                           \
string = (char*)PushSize_(&StringArena, sizeof(char)*count); \
}

#define PushStructOnScrap(instance, type)                       \
if(ScrapHeap.Base)                                           \
{                                                            \
instance = PushStruct(&ScrapHeap, type);             \
}\
else                                                         \
{                                                            \
ScrapHeap = CreateScrapHeap();                           \
instance= PushStruct(&ScrapHeap, type);             \
}

#define PushString(arena, count) PushArray(arena, (count), char)
#define PushArray(arena, count, type) (type* )PushSize_(arena, (sizeof(type)*(count)))
#define PushStruct(arena, type) (type*)PushSize_(arena, sizeof(type))
void* PushSize_(memory_arena* arena, size_t size)
{
    size_t NewMemPos = (size_t)((char*)arena->Base + arena->Used + size);
    size_t MaxMemPos = (size_t)((char*)arena->Base + arena->Max);
    void* Result = 0;
    if(NewMemPos < MaxMemPos)
    {
        Result = (void*)((char*)arena->Base + arena->Used);
        arena->Used += size;
    }
    
    Assert(Result);
    
    return Result;
}

void ResetArena(memory_arena* arena)
{
    arena->Used = 0;
}

void ResetStringArena()
{
    StringArena.Used = 0;
}

void ResetScrapHeap()
{
    ScrapHeap.Used = 0;
}


#define APP_MEMORY_H

#endif //APP_MEMORY_H
