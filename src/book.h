/* date = August 17th 2022 0:04 am */

#ifndef BOOK_H

#include "orrex_widgets.h"
//#include "app.h"

char* weekdays[]
{
    "Sunday",
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday"
};

struct book_info
{
    char* Name;
    int ID;
    int TableID;
    time_detail Time;
};

#define BOOK_H

#endif //BOOK_H
