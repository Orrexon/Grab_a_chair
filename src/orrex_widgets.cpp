#include "orrex_widgets.h"
#include "ztring.h"


/*
----------------------------------------------------------------------------------------------
Custom widgets
----------------------------------------------------------------------------------------------
*/

inline time_detail* 
OxGui::DateTimeInputText()
{
    // TODO(Oscar): improve the string format returned from time.h. (perhaps roll your own :P) 
    time_t currentTime;
    currentTime = time(&currentTime);
    time_detail* Result = localtime(&currentTime);
    
    ImGui::PushItemWidth(200);
    static char DTBuffer[256] = {0};
    if(ImGui::InputText("DateTime box", DTBuffer, IM_ARRAYSIZE(DTBuffer),ImGuiInputTextFlags_EnterReturnsTrue))
    {
        if(CompareStringIgnoreCase("now", DTBuffer))
        {
            strcpy(DTBuffer, ctime(&currentTime));
            return Result;
        }
        
        int date_index = 0;
        char DateString[IM_ARRAYSIZE(DTBuffer)] = {0};
        for(int i=0; 
            i<IM_ARRAYSIZE(DTBuffer) && DTBuffer[i];
            ++i)
        {
            char c = DTBuffer[i];
            if(c>='0' && c<='9')
            {
                DateString[date_index++] = c;
            }
        }
        if(date_index == 8)
        {
            Result->tm_year = (StoInt(&DateString[0], 4) - 1900);
            Result->tm_mon  = (StoInt(&DateString[4], 2) - 1); IM_ASSERT(Result->tm_mon < 12 && Result->tm_mon >= 0);
            Result->tm_mday = (StoInt(&DateString[6], 2));
            strcpy(DTBuffer, asctime(Result));
            return Result;
        }
    }
    ImGui::PopItemWidth();
    
    return 0;
}


inline bool
OxGui::InputTextSize(char* text_label, char* read_only_text, 
                     size_t maxSize, size_t boxWidth, 
                     ImGuiInputTextFlags flags, ImGuiInputTextCallback callback, void* user_data)
{
    //// TODO(Oscar): Probably doesn't need to be hinted.. but could be useful maybe
    bool Result = false;
    ImGui::BeginGroup();
    ImGui::PushItemWidth(boxWidth);
    //static char text_label[16] = {0};
    ImGui::Text(text_label);
    if(ImGui::InputTextWithHint("##UniqueNumber","Number",read_only_text, maxSize, ImGuiInputTextFlags_ReadOnly))
    {
        Result = true;
    }
    ImGui::PopItemWidth();
    ImGui::EndGroup();
    
    return Result;
}

inline bool
OxGui::InputTextHintLabel(int id_seed, char* out_buffer, const char* hint, size_t hintSize, size_t maxSize,ImGuiInputTextFlags flags,ImGuiInputTextCallback callback, void* user_data)
{
    bool Result = false;
    ImGui::BeginGroup();
    {
        ImGui::PushID(id_seed);
        char* NoteBuffer = out_buffer;
        char text_label[16] = {0};
        if(NoteBuffer[0])
            strncpy(text_label, hint, hintSize);
        ImGui::Text(text_label);
        if(ImGui::InputTextWithHint("##hintlabelbox", hint, NoteBuffer, maxSize, flags, callback, user_data))
        {
            Result = true;
        }
        strcpy(out_buffer, NoteBuffer);
    }
    ImGui::PopID();
    ImGui::EndGroup();
    
    return Result;
}

enum
{
    NO_BUTTON,
    SAVE_BUTTON,
    LOAD_BUTTON
};
int OxGui::SavePositionsWindow(char* name, bool* open)
{
    int Result = NO_BUTTON;
    if(ImGui::Begin(name, open))
    {
        if(ImGui::Button("Save table positions"))
        {
            Result = SAVE_BUTTON;
        }
        if(ImGui::Button("Load table positions"))
        {
            Result = LOAD_BUTTON;
        }
        ImGui::End();
    }
    
    return Result;
}