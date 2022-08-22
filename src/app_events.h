/* date = August 17th 2022 11:13 pm */

#ifndef APP_EVENTS_H
struct app_state;
enum event_type
{
    RESTAURANT_EVENT_QUEUE_POPUP_BOOKING_WINDOW
};

#define RESTAURANT_EVENT(name) void name(app_state* Restaurant)
typedef RESTAURANT_EVENT(restaurant_event);


static restaurant_event* Events[5] = {0};
static int EventCount = 0;

#define APP_EVENTS_H

#endif //APP_EVENTS_H
