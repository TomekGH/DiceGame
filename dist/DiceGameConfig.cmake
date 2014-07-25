# This file is used when other components needs to use something provided by this DCL. 
# Provide any include paths and lib directories. Use /home/tomek/Pulpit/DCL/DiceGame/dist
# to point to 'dist' directory of current DCL, it'll be substituted during installation. 

# directory containing header files
SET(DiceGame_INCLUDE_DIR /home/tomek/Pulpit/DCL/DiceGame/dist/include)
INCLUDE_DIRECTORIES(${DiceGame_INCLUDE_DIR})

# directory containing libraries
SET(DiceGame_LIB_DIR /home/tomek/Pulpit/DCL/DiceGame/dist/lib)
LINK_DIRECTORIES(${DiceGame_LIB_DIR})

# list of libraries to link against when using features of DiceGame
# add all additional libraries built by this dcl (NOT components)
# SET(DiceGame_LIBS lib_1 lib_2)
# SET(ADDITIONAL_LIB_DIRS /home/tomek/Pulpit/DCL/DiceGame/dist/lib ${ADDITIONAL_LIB_DIRS})
