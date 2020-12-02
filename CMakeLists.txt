cmake_minimum_required(VERSION 3.8)
project(FP_Base C)

set(CMAKE_C_STANDARD 90)

add_executable(FP_Base main.c docente.c docente.h login.c login.h carte.c carte.h territori.c territori.h combattimenti.c combattimenti.h spostamento.c spostamento.h game.c game.h rinforzi.c rinforzi.h salvataggio.c salvataggio.h)