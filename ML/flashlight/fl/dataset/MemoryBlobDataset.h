/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include "flashlight/fl/dataset/BlobDataset.h"

#include <fstream>
#ifndef MULTITHREADING_DISABLED
#include <mutex>
#endif // MULTITHREADING_DISABLED


namespace fl {

/**
 * A BlobDataset in (CPU) memory.
 *
 * As the arrays are stored on disk, sequential access will be the most
 * efficient.
 *
 */
class FL_API MemoryBlobDataset : public BlobDataset {
 public:
  /**
   * Creates a `MemoryBlobDataset`, specifying a blob file name.
   */
  MemoryBlobDataset();

  virtual ~MemoryBlobDataset() override = default;

 protected:
  int64_t writeData(int64_t offset, const char* data, int64_t size)
      const override;
  int64_t readData(int64_t offset, char* data, int64_t size) const override;
  void flushData() override;
  bool isEmptyData() const override;

 private:
#ifndef MULTITHREADING_DISABLED
  mutable std::mutex writeMutex_;
#endif // MULTITHREADING_DISABLED

  mutable std::vector<char> data_;
};

} // namespace fl
