cmake_minimum_required(VERSION 3.25)
project(rpg_simulator)

set(CMAKE_CXX_STANDARD 17)

add_executable(rpg_simulator src/main.cpp include/json.hpp src/model/Move.h src/model/Item.h src/model/Inventory.h src/model/Entity.h src/model/Move.cpp src/model/Item.cpp src/model/Entity.cpp src/view/View.cpp src/view/View.h src/controller/Controller.cpp src/controller/Controller.h src/model/Model.cpp src/model/Model.h src/model/Inventory.cpp)
target_link_libraries(rpg_simulator curses)
