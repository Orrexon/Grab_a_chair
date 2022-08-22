/* date = August 15th 2022 3:20 pm */

#ifndef APP_H


typedef unsigned int     uint32;
typedef unsigned         uint32;
typedef int              int32;
typedef int32            i32;
typedef uint32           u32;
typedef i32              bool32;
typedef bool32           b32;
typedef __int64          int64;
typedef unsigned __int64 uint64;
typedef int64            i64;
typedef uint64           u64;
typedef char             i8;
typedef unsigned char    u8;
typedef float            r32;
typedef double           r64;


#include "book.h"
#include "orrex_widgets.cpp"
#include "app_memory.h"
#include "app_math.h"
#include "app_events.h"

// NOTE(Oscar): Arbitrary, need to find some better way to find a good nr of pixels to represent meters
#define METER 60;
#define PIXEL 1/METER;

struct table
{
    // TODO(Oscar): Need axis when rotating to get the corner points correctly
    // NOTE(Oscar): I don't really know the best way, quarternions, rotation matrises etc...
    // NOTE(Oscar): But I'll really only need one axis since it's easy to perpendicularize it....
    // NOTE(Oscar): or just current angle maybe? We'll see
    v2 P;
    int W,H;
    int Chairs;
    int ID;
};

struct room
{
    int CurrentTable;
};

struct restaurant
{
    int CurrentRoom;
};

struct calendar
{
    
};

struct app_state
{
    // TODO(Oscar): rooms and tables go here, restaurant and rooms keep indices to them
    memory_arena AppMem;
    
    // TODO(Oscar): This may be a bit redundant, we'll see
    restaurant Restaurant;
    
    room Rooms[5];
    int RoomCount;
    
    table* Tables;
    int TableCount;
    table* SelectedTable;
    table* PreviousTable;
    
    book_info* Bookings;
    int BookCount;
    
    bool PopupBookMenu;
    restaurant_event* PopupEvent;
};


#define APP_H

#endif //APP_H
