if(WITH_XPU)
  cc_library(
    beam_search_xpu
    SRCS beam_search_xpu.cc
    DEPS xpu_op_list)
endif()

# please add new math_library in alphabetical order
math_library(concat_and_split DEPS phi)
math_library(context_project DEPS phi)
math_library(cos_sim_functor)
math_library(depthwise_conv)
math_library(sample_prob)
math_library(sampler DEPS phi)

if(WITH_XPU)
  math_library(beam_search DEPS phi beam_search_xpu)
else()
  math_library(beam_search DEPS phi)
endif()

math_library(unpooling)
math_library(prelu)
math_library(bert_encoder_functor)
math_library(tree2col DEPS phi)
