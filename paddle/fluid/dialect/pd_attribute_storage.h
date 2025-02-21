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

#include "paddle/ir/attribute.h"
#include "paddle/ir/utils.h"
#include "paddle/phi/common/data_type.h"
#include "paddle/phi/common/int_array.h"
#include "paddle/phi/common/layout.h"
#include "paddle/phi/common/place.h"
#include "paddle/phi/common/scalar.h"

namespace paddle {
namespace dialect {
struct IntArrayAttributeStorage : public ir::AttributeStorage {
  using ParamKey = phi::IntArray;

  explicit IntArrayAttributeStorage(const ParamKey &key) { data_ = key; }

  static IntArrayAttributeStorage *Construct(ParamKey key) {
    return new IntArrayAttributeStorage(key);
  }

  static std::size_t HashValue(const ParamKey &key) {
    size_t hash_value = 0;
    hash_value =
        ir::hash_combine(hash_value, std::hash<bool>()(key.FromTensor()));
    for (auto value : key.GetData()) {
      hash_value = ir::hash_combine(hash_value, std::hash<int64_t>()(value));
    }
    return hash_value;
  }

  bool operator==(const ParamKey &key) const {
    return (data_.GetData() == key.GetData()) &&
           (data_.FromTensor() == key.FromTensor());
  }

  ParamKey GetAsKey() const { return ParamKey(data_); }

 private:
  phi::IntArray data_;
};

struct ScalarAttributeStorage : public ir::AttributeStorage {
  using ParamKey = phi::Scalar;

  explicit ScalarAttributeStorage(const ParamKey &key) { data_ = key; }

  static ScalarAttributeStorage *Construct(ParamKey key) {
    return new ScalarAttributeStorage(key);
  }

  static std::size_t HashValue(const ParamKey &key) {
    return ir::hash_combine(std::hash<std::string>()(key.ToString()),
                            std::hash<bool>()(key.FromTensor()));
  }

  bool operator==(const ParamKey &key) const { return data_ == key; }

  ParamKey GetAsKey() const { return ParamKey(data_); }

 private:
  phi::Scalar data_;
};

struct DataTypeAttributeStorage : public ir::AttributeStorage {
  using ParamKey = phi::DataType;

  explicit DataTypeAttributeStorage(const ParamKey &key) { data_ = key; }

  static DataTypeAttributeStorage *Construct(ParamKey key) {
    return new DataTypeAttributeStorage(key);
  }

  static std::size_t HashValue(const ParamKey &key) {
    return std::hash<phi::DataType>()(key);
  }

  bool operator==(const ParamKey &key) const { return data_ == key; }

  ParamKey GetAsKey() const { return data_; }

 private:
  phi::DataType data_;
};

struct PlaceAttributeStorage : public ir::AttributeStorage {
  using ParamKey = phi::Place;

  explicit PlaceAttributeStorage(const ParamKey &key) { data_ = key; }

  static PlaceAttributeStorage *Construct(ParamKey key) {
    return new PlaceAttributeStorage(key);
  }

  static std::size_t HashValue(const ParamKey &key) { return key.HashValue(); }

  bool operator==(const ParamKey &key) const { return data_ == key; }

  ParamKey GetAsKey() const { return data_; }

 private:
  phi::Place data_;
};

struct DataLayoutAttributeStorage : public ir::AttributeStorage {
  using ParamKey = phi::DataLayout;

  explicit DataLayoutAttributeStorage(const ParamKey &key) { data_ = key; }

  static DataLayoutAttributeStorage *Construct(ParamKey key) {
    return new DataLayoutAttributeStorage(key);
  }

  static std::size_t HashValue(const ParamKey &key) {
    return std::hash<phi::DataLayout>()(key);
  }

  bool operator==(const ParamKey &key) const { return data_ == key; }

  ParamKey GetAsKey() const { return data_; }

 private:
  phi::DataLayout data_;
};

}  // namespace dialect
}  // namespace paddle
