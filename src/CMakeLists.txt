
add_executable(slam main.cpp Camera.cpp ../include/Config.h Config.cpp ../include/frame.h frame.cpp ../include/map.h map.cpp ../include/mappoint.h mappoint.cpp)

target_link_libraries(slam ${THIRD_PARTY_LIBS})

