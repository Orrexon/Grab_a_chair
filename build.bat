@echo off
if not exist build mkdir build
pushd build

copy ..\libs\SDL2.dll .\

rem ~~~ build SDL2/DearImGui/OpenGL3 template
cl /nologo /Zi /I..\src\ ../src/grab_a_chair.cpp ../src/third_party/dear_imgui/imgui*.cpp /link ..\libs\SDL2.lib ..\libs\SDL2main.lib opengl32.lib shell32.lib

popd
