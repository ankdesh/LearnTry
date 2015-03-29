
add_executable(openDB openDB.cpp)
target_link_libraries (openDB sqlite3)

add_executable(createTable createTable.cpp)
target_link_libraries (createTable sqlite3)

add_executable(insertOperation insertOperation.cpp)
target_link_libraries (insertOperation sqlite3)

add_executable(selectQuery selectQuery.cpp)
target_link_libraries (selectQuery sqlite3)
