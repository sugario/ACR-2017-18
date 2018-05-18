@CALL clean.bat
@CD ../.vscode
@CALL build.bat
@CD ..
cppcheck --enable=all --project=build/compile_commands.json
