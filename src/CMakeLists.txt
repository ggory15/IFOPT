SET(LIBRARY_NAME ${PROJECT_NAME})

SET(${LIBRARY_NAME}_SOURCES
    ifopt_core/problem.cc
    ifopt_core/composite.cc
    ifopt_core/leaves.cc
	
    ifopt_ipopt/ipopt_adapter.cc
    ifopt_ipopt/ipopt_solver.cc
)

ADD_LIBRARY(${LIBRARY_NAME}
  SHARED
  ${${LIBRARY_NAME}_SOURCES}
  )

TARGET_LINK_LIBRARIES (${LIBRARY_NAME} ${Boost_LIBRARIES} ${EIGEN_LIBRARIES})
INSTALL(TARGETS ${LIBRARY_NAME} DESTINATION lib)

