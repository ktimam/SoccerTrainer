#include "FieldPlayerMLP.h"

AverageValueMeter* FieldPlayerMLP::meter;

FieldPlayerMLP::FieldPlayerMLP() {
	// Model definition - 2-layer Perceptron with ReLU activation
	model = std::make_shared <Sequential>();
	model->add(Linear(nInputCount, 1024));
	model->add(ReLU());
	model->add(Linear(1024, 512));
	model->add(ReLU());
	model->add(Linear(512, 256));
	model->add(ReLU());
	model->add(Linear(256, 256));
	model->add(ReLU());
	model->add(Linear(256, 128));
	model->add(ReLU());
	model->add(Linear(128, 128));
	model->add(ReLU());
	model->add(Linear(128, nOutputCount));
	// Optimizer definition
	//optimizer = new SGDOptimizer(model->params(), learningRate, momentum);
	optimizer = std::make_shared < AdagradOptimizer>(model->params(), learningRate);

	// MSE loss
	loss = MeanSquaredError();

}

Action FieldPlayerMLP::Process(Observation observation, bool backpropagate, Action target)
{
	Tensor observation_tensor = Tensor::fromVector(observation.toVector());
	Tensor decision = Tensor::fromVector(target.toVector());
	//std::cout << "observation_tensor : " << observation_tensor << std::endl;
	//std::cout << "decision : " << decision << std::endl;

	optimizer->zeroGrad();

	// Forward propagation
	auto result = model->forward(input(observation_tensor));
	//std::cout << "result : " << result.tensor() << std::endl;

	if (backpropagate) {
		// Calculate loss
		auto l = loss(result, noGrad(decision));

		// Backward propagation
		l.backward();

		// Update parameters
		optimizer->step();

		//std::cout << "l.scalar<float>() : " << l.scalar<float>() << std::endl;
		meter->add(l.scalar<float>());
	}

	return Action::toAction(result.tensor());
}

bool FieldPlayerMLP::Save(string aFileName)
{
	fl::save(aFileName, model);
	return true;
}

bool FieldPlayerMLP::Load(string aFileName)
{
	model = std::make_shared <Sequential>();
	fl::load(aFileName, model);
	optimizer = std::make_shared < AdagradOptimizer>(model->params(), learningRate);
	return true;
}
