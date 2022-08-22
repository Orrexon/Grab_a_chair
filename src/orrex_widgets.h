/* date = August 18th 2022 0:19 am */

#ifndef ORREX_WIDGETS_H

#include "time.h"
typedef tm time_detail;
struct app_state;
namespace OxGui
{
    time_detail* DateTimeInputText();
    bool InputTextSize(char* text_label, char* read_only_text, size_t maxSize, size_t boxWidth, ImGuiInputTextFlags flags=0, ImGuiInputTextCallback callback=0, void* user_data=0);
    bool InputTextHintLabel(int id_seed, char* out_buffer, const char* hint, size_t hintSize, size_t maxSize,ImGuiInputTextFlags flags=0,ImGuiInputTextCallback callback=0, void* user_data=0);
    int SavePositionsWindow(char* text_label, bool* open);
}


#define ORREX_WIDGETS_H

#endif //ORREX_WIDGETS_H
