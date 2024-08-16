#include "FieldPlayerMLP.h"

AverageValueMeter* FieldPlayerMLP::meter;

FieldPlayerMLP::FieldPlayerMLP() {

	// Model definition - 2-layer Perceptron with ReLU activation
	model.add(Linear(nInputCount, 100));
	model.add(ReLU());
	model.add(Linear(100, nOutputCount));

	// MSE loss
	loss = MeanSquaredError();

	// Optimizer definition
	sgd = new SGDOptimizer(model.params(), learningRate, momentum);


}

Action FieldPlayerMLP::Process(Observation observation, bool backpropagate, Action target)
{
	Tensor observation_tensor = Tensor::fromVector(observation.toVector());
	Tensor decision = Tensor::fromVector(target.toVector());
	//std::cout << "observation_tensor : " << observation_tensor << std::endl;
	//std::cout << "decision : " << decision << std::endl;

	sgd->zeroGrad();

	// Forward propagation
	auto result = model(input(observation_tensor));
	//std::cout << "result : " << result.tensor() << std::endl;

	if (backpropagate) {
		// Calculate loss
		auto l = loss(result, noGrad(decision));

		// Backward propagation
		l.backward();

		// Update parameters
		sgd->step();

		//std::cout << "l.scalar<float>() : " << l.scalar<float>() << std::endl;
		meter->add(l.scalar<float>());
	}

	return Action::toAction(result.tensor());
}
