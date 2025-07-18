/*
 * SPDX-FileCopyrightText: (C) 2025 DeliteAI Authors
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <future>

#include "base_job.hpp"
#include "data_variable.hpp"
#include "ne_fwd.hpp"
#include "nlohmann/json.hpp"

/**
 @brief Wraps a future of OpReturnType so it is transparent in the Python workflow

 This class is used for exposing the result of a Job to the Python script. It forwards the functions
 called on it to the DataVariable returned by the future and throws if the future has not been
 satisfied. Similarly, forwards get_int_subscript.

 It also stores the Job from which this future has been produced
*/
class FutureDataVariable : public DataVariable {
  int get_containerType() const override { return CONTAINERTYPE::SINGLE; }

  bool get_bool() override { return true; }

  int get_dataType_enum() const override { return DATATYPE::NONE; }

  std::string print() override { return ne::fmt("Future[%s]", _name.c_str()).str; }

  nlohmann::json to_json() const override { return ne::fmt("Future[%s]", _name.c_str()).str; }

 private:
  std::future<OpReturnType> _future; /**< The wrapped future containing the operation result */
  std::string _name;                 /**< Name identifier for this future variable */
  OpReturnType _val;                 /**< Cached value once future is resolved */
  std::shared_ptr<BaseJob> _dependentJob; /**< Job that produced this future */
  bool _savedToTask = false;         /**< Flag indicating if this future has been saved to a task */

 public:
  FutureDataVariable(std::future<OpReturnType>&& future, const std::string& name,
                     std::shared_ptr<BaseJob> dependentJob, bool isTaskInitializing);

  std::shared_ptr<BaseJob> get_job();
  bool is_available();
  OpReturnType get();
  OpReturnType get_int_subscript(int index) override;
  void save_to_task(Task& task);

 private:
  OpReturnType call_function(int memberFuncIndex, const std::vector<OpReturnType>& arguments,
                             CallStack& stack) override;
};
