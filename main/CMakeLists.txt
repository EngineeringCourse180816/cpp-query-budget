set(Main_SRCS main.cpp BudgetQuery.cpp BudgetDao.cpp BudgetDao.h BudgetQuery.h date.h Period.cpp Period.h)

add_library(core ${Main_SRCS})
add_executable(${CMAKE_PROJECT_NAME} main.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} core)
