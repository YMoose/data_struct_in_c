set(Unity_SEARCH_PATH_LIST
    /home/yzh/Unity/src
    ${Unity_ROOT}
    $ENV{Unity_ROOT}
)

find_path(Unity_SRC_DIR 
    NAMES unity.h
    HINTS ${Unity_SEARCH_PATH_LIST}
    DOC "Find the unity includes"
)

set(Unity_SRC_FILE ${Unity_SRC_DIR}/unity.c)
set(Unity_SRC_FILE ${Unity_SRC_DIR}/unity.c)