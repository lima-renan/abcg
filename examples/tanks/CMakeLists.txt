project(tanks)

add_executable(${PROJECT_NAME} main.cpp openglwindow.cpp enemies.cpp
                               shots.cpp player.cpp)

enable_abcg(${PROJECT_NAME})
