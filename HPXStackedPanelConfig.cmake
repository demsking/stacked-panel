set(HPXStackedPanel_INCLUDE_DIRS ${PREFIX}/include/hpx/stacked-panel)
set(HPXStackedPanel_LIBRARY ${PREFIX}/lib/libHPXStackedPanel.so)
add_library(${PROJECT_NAME} ALIAS HPX::${PROJECT_NAME})
