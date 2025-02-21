// Copyright (c) 2023 PaddlePaddle Authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include "paddle/ir/builtin_attribute.h"
#include "paddle/ir/op_info.h"
#include "paddle/ir/type.h"
#include "paddle/ir/value_impl.h"

namespace ir {

using AttributeMap = std::unordered_map<std::string, Attribute>;

//===----------------------------------------------------------------------===//
// OperationArgument
//===----------------------------------------------------------------------===//

// This represents an operation arguments in an combined form, suitable for use
// with the builder APIs.
struct OperationArgument {
  OpInfo info_;
  std::vector<OpResult> inputs_;
  std::vector<Type> output_types_;
  AttributeMap attribute_;

 public:
  OperationArgument(IrContext* ir_context, std::string name);
  explicit OperationArgument(OpInfo info) : info_(info) {}
  OperationArgument(OpInfo info,
                    const std::vector<OpResult>& operands,
                    const std::vector<Type>& types,
                    const AttributeMap& named_attr = {});

  template <class InputIt>
  void addOperands(InputIt first, InputIt last);

  template <class InputIt>
  void addTypes(InputIt first, InputIt last);

  /// Add an attribute with the specified name.
  void addAttribute(const std::string& name, Attribute attr) {
    attribute_[name] = attr;
  }
  /// Add an array of named attributes.
  template <class InputIt>
  void addAttributes(InputIt first, InputIt last);
  /// Get the context held by this operation state.
  IrContext* getContext() const { return info_.ir_context(); }
};

template <class InputIt>
void OperationArgument::addOperands(InputIt first, InputIt last) {
  while (first != last) {
    inputs_.emplace_back(*first++);
  }
}
template <class InputIt>
void OperationArgument::addTypes(InputIt first, InputIt last) {
  while (first != last) {
    output_types_.emplace_back(*first++);
  }
}
template <class InputIt>
void OperationArgument::addAttributes(InputIt first, InputIt last) {
  while (first != last) {
    attribute_[first->first] = first->second;
    ++first;
  }
}

}  // namespace ir
