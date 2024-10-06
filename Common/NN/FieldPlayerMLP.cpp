#include "FieldPlayerMLP.h"

AverageValueMeter* FieldPlayerMLP::meter;

FieldPlayerMLP::FieldPlayerMLP() {
	// Model definition - 2-layer Perceptron with ReLU activation
	model = std::make_shared <Sequential>();
	model->add(Linear(nInputCount, 512));
	model->add(ReLU());
	/*model->add(Linear(1024, 512));
	model->add(ReLU());*/
	model->add(Linear(512, 128));
	model->add(ReLU());
	/*model->add(Linear(256, 256));
	model->add(ReLU());
	model->add(Linear(256, 128));
	model->add(ReLU());
	model->add(Linear(128, 128));
	model->add(ReLU());*/
	model->add(Linear(128, nOutputCount));
	// Optimizer definition
	//optimizer = std::make_shared < SGDOptimizer>(model->params(), learningRate, momentum);
	optimizer = std::make_shared < AdagradOptimizer>(model->params(), learningRate);

	// MSE loss
	loss = MeanSquaredError();

}

Action FieldPlayerMLP::Process(Observation observation, Action target)
{
	return Process(observation.toVector(), target.toVector());
}
Action FieldPlayerMLP::Process(vector<float> observation_vec, vector<float> target_vec)
{
	std::cout << "FieldPlayerMLP::Process....." << std::endl;
	Tensor observation_tensor = Tensor::fromVector(observation_vec);
	std::cout << "Tensor decision....." << std::endl;
	Tensor decision = Tensor::fromVector(target_vec);
	//std::cout << "observation_tensor : " << observation_tensor << std::endl;
	//std::cout << "decision : " << decision << std::endl;

	std::cout << "optimizer->zeroGrad()....." << std::endl;
	optimizer->zeroGrad();

	// Forward propagation
	//std::cout << "model->forward....." << std::endl;
	auto result = model->forward(input(observation_tensor));
	//std::cout << "result : " << result.tensor() << std::endl;

	if (trainingOn) {
		// Calculate loss
		auto l = loss(result, noGrad(decision));

		// Backward propagation
		l.backward();

		// Update parameters
		optimizer->step();

		//std::cout << "l.scalar<float>() : " << l.scalar<float>() << std::endl;
		meter->add(l.scalar<float>());
	}

	//std::cout << "Action::toAction....." << std::endl;
	return Action::toAction(result.tensor());
}

bool FieldPlayerMLP::Save(string aFileName)
{
	fl::save(aFileName, model);
	return true;
}

bool FieldPlayerMLP::Load(string aFileName)
{
	if (std::filesystem::exists(aFileName)) {
		model = std::make_shared <Sequential>();
		fl::load(aFileName, model);
		//optimizer = std::make_shared < SGDOptimizer>(model->params(), learningRate, momentum);
		optimizer = std::make_shared < AdagradOptimizer>(model->params(), learningRate);
		return true;
	}
	return false;
}
