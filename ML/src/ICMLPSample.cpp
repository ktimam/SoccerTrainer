#include "ICMLPSample.h"

#include <sstream>
#include <string>

#include "flashlight/fl/tensor/TensorBase.h"
#include "flashlight/fl/tensor/Index.h"
#include "flashlight/fl/tensor/Init.h"
#include "flashlight/fl/dataset/datasets.h"
#include "flashlight/fl/meter/meters.h"
#include "flashlight/fl/nn/nn.h"
//#include "flashlight/fl/optim/optim.h"
#include "flashlight/fl/optim/SGDOptimizer.h"
#include "flashlight/fl/tensor/Random.h"

#define IC_API_INCL
//#define STD_IO

#ifdef IC_API_INCL
#include "ic_api.h"
#elif defined(STD_IO)
#include <stdio.h>
#include <stdlib.h>
#endif

//#include <json/json.hpp>

//#include <iostream>

using namespace fl;

/* ---------------------------------------------------------
  Respond with a 'std::string' wrapped in a CandidTypeText
*/
void train() {
    fl::init();

    // Create dataset
    const int nSamples = 5;// 10000;
    const int nFeat = 3;// 10;
    auto X = fl::rand({ nFeat, nSamples }) + 1; // X elements in [1, 2]
    auto Y = /* signal */ fl::transpose(fl::sum(fl::power(X, 3), { 0 })) +
        /* noise */ fl::sin(2 * (float)M_PI * fl::rand({ nSamples }));


    /* signal */
    //auto Y = fl::power(X, 3);
    //std::cout << "Tensor Y : " << Y << std::endl;
    //Y = fl::sum(Y, { 0 });
    //std::cout << "Tensor Y : " << Y << std::endl;
    //std::cout << "Y shape : " << Y.shape() << std::endl;
    //Y = fl::transpose(Y);

    // Create Dataset to simplify the code for iterating over samples
    TensorDataset data({ X, Y });
    auto first = data.get(0);
    const int inputIdx = 0, targetIdx = 1;

    // Model definition - 2-layer Perceptron with ReLU activation
    Sequential model;
    model.add(Linear(nFeat, 100));
    model.add(ReLU());
    model.add(Linear(100, 1));
    // MSE loss
    auto loss = MeanSquaredError();

    // Optimizer definition
    const float learningRate = 0.0001;
    const float momentum = 0.9;
    auto sgd = SGDOptimizer(model.params(), learningRate, momentum);

    // Meter definition
    AverageValueMeter meter;

    // Start training

    //std::cout << "[Multi-layer Perceptron] Started..." << std::endl;

    const int nEpochs = 100;

    // Create a msg, to be passed back as Candid over the wire
    std::string msg{ "" };
#ifdef IC_API_INCL
    IC_API ic_api(CanisterQuery{ std::string(__func__) }, false);
    CandidTypePrincipal caller = ic_api.get_caller();
    msg.append("Your principal is: " + caller.get_text() + "!\n");
#endif
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
        /*std::cout << "Epoch: " << e << " Mean Squared Error: " << meter.value()[0]
            << std::endl;*/

        std::stringstream ss;
        ss << "Epoch: " << e << " Mean Squared Error: " << meter.value()[0] << "!\n";
        msg.append(ss.str());

    }
    //std::cout << "[Multi-layer Perceptron] Done!" << std::endl;
    msg.append("[Multi-layer Perceptron] Done!\n");
#ifdef NATIVE_BUILD
    std::cout << msg << std::endl;
#endif

#ifdef IC_API_INCL
    ic_api.to_wire(CandidTypeText{msg});
#elif defined(STD_IO)
    printf("msg.c_str()");
#endif
}