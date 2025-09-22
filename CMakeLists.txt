cmake_minimum_required(VERSION 3.10)
project(calczp C)

# Füge hier alle deine Quelldateien hinzu
add_executable(calczp
        Programm.c
        einfacheBerechnungen.c
        localizedString.c
        binaryFunction.c


        ZeLib/ZcBase.c
        ZeLib/ZThreading.c
        ZeLib/WindowManager.c
)