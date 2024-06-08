/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "flashlight/fl/tensor/TensorBackend.h"

namespace fl {
namespace detail {

bool areBackendsEqual(const Tensor& a, const Tensor& b) {
  return a.backendType() == b.backendType();
}

} // namespace detail

bool TensorBackend::isDataTypeSupported(const fl::dtype& dtype) const {
  bool supported = this->supportsDataType(dtype);
  for (auto& p : extensions_) {
    supported &= p.second->isDataTypeSupported(dtype);
  }
  return supported;
}

Tensor TensorBackend::clip(
    const Tensor& tensor,
    const Tensor& low,
    const float& high) {
  return clip(
      tensor, low, full(tensor.shape(), high, dtype_traits<float>::ctype));
}

Tensor TensorBackend::clip(
    const Tensor& tensor,
    const float& low,
    const Tensor& high) {
  return clip(
      tensor, full(tensor.shape(), low, dtype_traits<float>::ctype), high);
}

Tensor TensorBackend::clip(
    const Tensor& tensor,
    const float& low,
    const float& high) {
  return clip(
      tensor,
      full(tensor.shape(), low, dtype_traits<float>::ctype),
      full(tensor.shape(), high, dtype_traits<float>::ctype));
}

Tensor TensorBackend::where(
    const Tensor& condition,
    const Tensor& x,
    const float& y) {
  return where(condition, x, full(condition.shape(), y, x.type()));
}

Tensor TensorBackend::where(
    const Tensor& condition,
    const float& x,
    const Tensor& y) {
  return where(condition, full(condition.shape(), x, y.type()), y);
}

Tensor TensorBackend::minimum(const Tensor& lhs, const float& rhs) {
  return minimum(lhs, full(lhs.shape(), rhs, dtype_traits<float>::ctype));
}

Tensor TensorBackend::minimum(const float& lhs, const Tensor& rhs) {
  return minimum(full(rhs.shape(), lhs, dtype_traits<float>::ctype), rhs);
}

Tensor TensorBackend::maximum(const Tensor& lhs, const float& rhs) {
  return maximum(lhs, full(lhs.shape(), rhs, dtype_traits<float>::ctype));
}

Tensor TensorBackend::maximum(const float& lhs, const Tensor& rhs) {
  return maximum(full(rhs.shape(), lhs, dtype_traits<float>::ctype), rhs);
}

Tensor TensorBackend::power(const Tensor& lhs, const float& rhs) {
  return power(lhs, full(lhs.shape(), rhs, dtype_traits<float>::ctype));
}

Tensor TensorBackend::power(const float& lhs, const Tensor& rhs) {
  return power(full(rhs.shape(), lhs, dtype_traits<float>::ctype), rhs);
}

} // namespace fl
