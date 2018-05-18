@CD ..

@IF NOT EXIST build (
    @MKDIR build
)

@CD build

@cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -G "MinGW Makefiles"
@make
