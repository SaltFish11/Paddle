cc_library(
  custom_operator_node
  SRCS custom_operator_node.cc
  DEPS phi grad_node_info custom_operator)
