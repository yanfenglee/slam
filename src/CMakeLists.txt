
add_library(slam SHARED
        Camera.cpp
        Config.cpp
        frame.cpp
        map.cpp
        mappoint.cpp
        vo.cpp g2o_types.cpp)

target_link_libraries(slam ${THIRD_PARTY_LIBS})

