@CD ..

@IF EXIST build (
    @CD build
    @DEL compile_commands.json
    @make clean
) ELSE (
    @MKDIR build
    @CD build
)
