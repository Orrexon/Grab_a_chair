#include "app.h"
#include "app_data_access.h"
//#include "book.h"

table* AddTable(memory_arena* arena, int Width, int Height, int Chairs, int Id)
{
    table* Result = PushStruct(arena, table);
    
    Result->W = Width;
    Result->H = Height;
    Result->Chairs = Chairs;
    Result->ID = Id;
    
    return Result;
}

room InitRoom(memory_arena* Arena)
{
    room* Result = PushStruct(Arena, room);
    
    Result->CurrentTable = 0;
    // NOTE(Oscar): copy for now doesn't matter in this stage
    return *Result;
}

app_state InitRestaurant()
{
    app_state Result = {0};
    Result.AppMem = CreateArena();
    
    restaurant rest = {0};
    rest.CurrentRoom = 0;
    Result.Restaurant = rest;
    
    Result.Rooms[0] = InitRoom(&Result.AppMem);
    Result.RoomCount++;
    Result.Tables = PushArray(&Result.AppMem, 10, table);
    // TODO(Oscar): Add table could take the tables pointer instead maybe..
    Result.Tables[Result.TableCount] = *AddTable(&Result.AppMem, 1, 1, 4, Result.TableCount++);
    Result.Tables[Result.TableCount] = *AddTable(&Result.AppMem, 2, 1, 6, Result.TableCount++);
    
    return Result;
}

void SetTables(app_state* State)
{
    for(int roomIndex = 0; roomIndex<State->RoomCount; ++roomIndex)
    {
        for(int tableIndex = 0; tableIndex<State->TableCount; ++tableIndex)
        {
            table* Table = &State->Tables[tableIndex];
            Table->P = V2(tableIndex + 5,tableIndex + 3);
        }
    }
}

v2 GetCurrentTableMinPointInMeter(app_state* State)
{
    v2 p = State->Tables[State->Rooms[State->Restaurant.CurrentRoom].CurrentTable].P;
    int w = State->Tables[State->Rooms[State->Restaurant.CurrentRoom].CurrentTable].W;
    int h = State->Tables[State->Rooms[State->Restaurant.CurrentRoom].CurrentTable].H;
    
    return V2(p.x - w/2.f, p.y - h/2.f)*METER;
    
}

v2 GetCurrentTableMinPointInMeter(table* Table)
{
    v2 p = Table->P;
    int w = Table->W;
    int h = Table->H;
    
    return V2(p.x - w/2.f, p.y - h/2.f)*METER;
    
}

v2 GetCurrentTableSecondPointInMeter(app_state* State)
{
    v2 p = State->Tables[State->Rooms[State->Restaurant.CurrentRoom].CurrentTable].P;
    int w = State->Tables[State->Rooms[State->Restaurant.CurrentRoom].CurrentTable].W;
    int h = State->Tables[State->Rooms[State->Restaurant.CurrentRoom].CurrentTable].H;
    
    return V2(p.x + w/2.f, p.y - h/2.f)*METER;
}

v2 GetCurrentTableSecondPointInMeter(table* Table)
{
    v2 p = Table->P;
    int w = Table->W;
    int h = Table->H;
    
    return V2(p.x + w/2.f, p.y - h/2.f)*METER;
}


v2 GetCurrentTableThirdPointInMeter(app_state* State)
{
    v2 p = State->Tables[State->Rooms[State->Restaurant.CurrentRoom].CurrentTable].P;
    int w = State->Tables[State->Rooms[State->Restaurant.CurrentRoom].CurrentTable].W;
    int h = State->Tables[State->Rooms[State->Restaurant.CurrentRoom].CurrentTable].H;
    
    return V2(p.x - w/2.f, p.y + h/2.f)*METER;
}

v2 GetCurrentTableThirdPointInMeter(table* Table)
{
    v2 p = Table->P;
    int w = Table->W;
    int h = Table->H;
    
    return V2(p.x - w/2.f, p.y + h/2.f)*METER;
}

v2 GetCurrentTableMaxPointInMeter(app_state* State)
{
    v2 p = State->Tables[State->Rooms[State->Restaurant.CurrentRoom].CurrentTable].P;
    int w = State->Tables[State->Rooms[State->Restaurant.CurrentRoom].CurrentTable].W;
    int h = State->Tables[State->Rooms[State->Restaurant.CurrentRoom].CurrentTable].H;
    
    return V2(p.x + w/2.f, p.y + h/2.f)*METER;
}

v2 GetCurrentTableMaxPointInMeter(table* Table)
{
    v2 p = Table->P;
    int w = Table->W;
    int h = Table->H;
    
    return V2(p.x + w/2.f, p.y + h/2.f)*METER;
}

bool IsPointInsideTable(table* tabl, ImVec2 MP)
{
    v2 M = V2(MP.x, MP.y);
    
    v2 A = GetCurrentTableMinPointInMeter(tabl);
    v2 B = GetCurrentTableSecondPointInMeter(tabl);
    v2 C = GetCurrentTableThirdPointInMeter(tabl);
    v2 D = GetCurrentTableMaxPointInMeter(tabl);
    
    v2 AM = M - A;
    v2 BM = M - B;
    v2 CM = M - C;
    v2 DM = M - D;
    
    v2 AB = B - A;
    v2 CA = A - C;
    v2 BD = D - B;
    v2 DC = C - D;
    
    float TOP = Inner(AM, AB) - Inner(AB, AB);
    float RIGHT = Inner(BM, BD) - Inner(BD, BD);
    float BOTTOM = Inner(DM, DC) - Inner(DC, DC);
    float LEFT = Inner(CM, CA) - Inner(CA, CA);
    
    if(TOP    < 0 &&
       RIGHT  < 0 &&
       BOTTOM < 0 &&
       LEFT   < 0)
    {
        return true;
    }
    return false;
}

RESTAURANT_EVENT(PopupBookTableEvent)
{
    static char menuPopupBuffer[128] = {0};
    if(ImGui::BeginPopup("Book menu"))
    {
        OxGui::InputTextHintLabel(55, menuPopupBuffer, "Name", 5, 128);
        ImGui::NewLine();
        if(ImGui::BeginTable("Calendar", 7, ImGuiTableFlags_Borders))
        {
            for(int row = 0; row < 7; ++row)
            {
                ImGui::TableNextRow();
                for(int column = 0; column < 7; ++column)
                {
                    ImGui::TableSetColumnIndex(column);
                    ImGui::Text("%s %d",weekdays[row], column);
                    if(ImGui::IsItemHovered())
                    {
                        ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, 0x77DD4422, column);
                        if(ImGui::IsItemClicked(ImGuiMouseButton_Left))
                        {
                            // NOTE(Oscar): For now, Previous table is used because Selected table is set to null on IsMouseReleased(left). This event is fired the following frame
                            BookTable(Restaurant, *Restaurant->PreviousTable, row, column, menuPopupBuffer);
                        }
                    }
                }
            }
            ImGui::EndTable();
        }
        ImGui::EndPopup();
    }
    else
    {
        ImGui::OpenPopup("Book menu");
        Restaurant->PopupBookMenu = false;
    }
}

void AddEventToEventQueue(int EventType)
{
    switch(EventType)
    {
        case RESTAURANT_EVENT_QUEUE_POPUP_BOOKING_WINDOW:
        {
            Events[EventCount++] = PopupBookTableEvent;
        }break;
        default:
        {}break;
    }
}

void ResturantEventDeQueue(app_state* State)
{
    while(EventCount)
    {
        --EventCount;
        Events[EventCount](State);
    }
}

void Update(app_state* State)
{
    // TODO(Oscar): Input, drawbuffer, events? etc
    
    // NOTE(Oscar): Get mouse position and check if inside
    static bool DragTable = false;
    ImVec2 MP = ImGui::GetMousePos();
    int tblCount = State->TableCount;
    ImU32 color = 0xFFFF00FF;
    for(int tblIndex = 0; tblIndex<tblCount; ++tblIndex)
    {
        table* tabl = &State->Tables[tblIndex];
        if(IsPointInsideTable(tabl, MP))
        {
            color = 0xFF0000FF;
            if(ImGui::IsMouseDown(ImGuiMouseButton_Left))
            {
                State->SelectedTable = tabl;
                DragTable = true;
            }
            if(ImGui::IsMouseDown(ImGuiMouseButton_Right))
            {
                State->SelectedTable = tabl;
                State->PopupBookMenu = true;
            }
        }
    }
    
    if(State->SelectedTable && DragTable)
    {
        v2 MDelta = V2(ImGui::GetIO().MouseDelta.x, ImGui::GetIO().MouseDelta.y);
        State->SelectedTable->P += MDelta*ImGui::GetIO().DeltaTime;
    }
    if(ImGui::IsMouseReleased(ImGuiMouseButton_Left))
    {
        State->PreviousTable = State->SelectedTable;
        State->SelectedTable = 0;
        DragTable = false;
    }
    
    
    //// NOTE(Oscar): Render stuffz:
    
    // TODO(Oscar): A render layer that takes the custom v2 and v3 and calls the ImGui and set them to meters.
    // The render layer will sort the drawing order as well. 
    for(int renderTable = 0; renderTable<State->TableCount; ++renderTable)
    {
        table tbl = State->Tables[renderTable];
        v2 p1 = GetCurrentTableMinPointInMeter(&tbl);
        v2 p2 = GetCurrentTableMaxPointInMeter(&tbl);
        ImGui::GetBackgroundDrawList()->AddRect(ImVec2(p1.x, p1.y), ImVec2(p2.x, p2.y),color, 0, 0, 4);
    }
    
    static bool saveloadwindow = true;
    switch(OxGui::SavePositionsWindow("Button window", &saveloadwindow))
    {
        case SAVE_BUTTON:{SaveTablePositions(State);}break;
        case LOAD_BUTTON:{LoadTablePositions(State);}break;
        //case ADD_TABLE_BUTTON:{AddTable()}break;
        default:break;
    }
}