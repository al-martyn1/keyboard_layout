@call :DEL_FILE kbd_layout_gen.exe
@call :DEL_FILE kbd_layout_gen.obj
@call :DEL_FILE *.log
@if exist kbd_layout_gen rmdir /Q /S kbd_layout_gen
@exit /b

:DEL_FILE
@if exist %1 del /Q %1
@exit /b