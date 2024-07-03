########################################
#
# Find MyStructInC library and includes
# This module sets:
#  MyStructInC_FOUND:          True if Libcheck was found
#  MyStructInC_INCLUDE_DIR:    The Libcheck include dir
#  todo:MyStructInC_LIBRARY:        The Libcheck library
#

set(MyStructInC_SEARCH_PATH_LIST
    /home/yzh/data_struct_in_c
    ${MyStructInC_ROOT}
    $ENV{MyStructInC_ROOT}
)

find_path(MyStructInC_INCLUDE_DIR mem.h
    HINTS ${MyStructInC_SEARCH_PATH_LIST}
    DOC "Find the check includes"
)

