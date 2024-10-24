/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */
#define WIN32_LEAN_AND_MEAN      // Exclude rarely-used stuff from Windows headers

#if defined(OS_WIN)
#include <windows.h>
#endif

#include <iostream>

#include "flashlight/fl/tensor/Init.h"
#include "flashlight/fl/dataset/datasets.h"
#include "flashlight/fl/meter/meters.h"
#include "flashlight/fl/nn/nn.h"
//#include "flashlight/fl/optim/optim.h"
#include "flashlight/fl/optim/SGDOptimizer.h"
#include "flashlight/fl/tensor/Random.h"
#include "flashlight/fl/tensor/TensorBase.h"

using namespace fl;

int main() {
    fl::init();

    // Create dataset
    const int nSamples = 5;// 10000;
    const int nFeat = 3;// 10;
    auto X = fl::rand({ nFeat, nSamples }) + 1; // X elements in [1, 2]
    auto Y = /* signal */ fl::transpose(fl::sum(fl::power(X, 3), { 0 })) +
        /* noise */ fl::sin(2.0f * (float)M_PI * fl::rand({ nSamples }));


    /* signal */
    //auto Y = fl::power(X, 3);
    //std::cout << "Tensor Y : " << Y << std::endl;
    //Y = fl::sum(Y, { 0 });
    //std::cout << "Tensor Y : " << Y << std::endl;
    //std::cout << "Y shape : " << Y.shape() << std::endl;
    //Y = fl::transpose(Y);

    //Tensor Z = Tensor(Y);// .copy();
    //std::cout << "Z : " << Z << std::endl;
    //std::cout << "Z shape : " << Z.shape() << std::endl;
    //TensorDataset ds({ Y });
    //std::cout << "ds.get(0)[0] : " << ds.get(0)[0] << std::endl;
    //std::cout << "ds shape : " << ds.get(0)[0].shape() << std::endl;
    //auto dsd = ds.get(0);

    // Create Dataset to simplify the code for iterating over samples
    TensorDataset data({ X, Y });
    auto first = data.get(0);
    const int inputIdx = 0, targetIdx = 1;

    // Model definition - 2-layer Perceptron with ReLU activation
    Sequential model;
    /*model.add(Linear(nFeat, 100));
    model.add(ReLU());
    model.add(Linear(100, 1));*/
    fl::load("Models/mlpmodel", model);
    // MSE loss
    auto loss = MeanSquaredError();

    // Optimizer definition
    const float learningRate = 0.0001;
    const float momentum = 0.9;
    auto sgd = SGDOptimizer(model.params(), learningRate, momentum);

    // Meter definition
    AverageValueMeter meter;

    // Start training

    std::cout << "[Multi-layer Perceptron] Started..." << std::endl;

    const int nEpochs = 100;
    for (int e = 1; e <= nEpochs; ++e) {
        meter.reset();
        for (auto& sample : data) {
            sgd.zeroGrad();

            // Forward propagation
            auto result = model(input(sample[inputIdx]));

            // Calculate loss
            auto l = loss(result, noGrad(sample[targetIdx]));

            // Backward propagation
            l.backward();

            // Update parameters
            sgd.step();

            meter.add(l.scalar<float>());
        }
        std::cout << "Epoch: " << e << " Mean Squared Error: " << meter.value()[0]
            << std::endl;
    }
    fl::save("Models/mlpmodel", model);
    std::cout << "[Multi-layer Perceptron] Done!" << std::endl;
    return 0;
}
