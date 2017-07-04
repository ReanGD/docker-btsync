#include "NeuralNetwork.h"


Neuron::Neuron(uint16_t inputCnt, Generator& generator)
  : m_inputCnt(inputCnt)
  , m_weights(new float[inputCnt]) {

  float *ptr = m_weights.get();
  for (uint16_t i=0; i!=inputCnt; ++i) {
    ptr[i] = generator.getf(1.0f);
  }
}

float Neuron::calc(const std::shared_ptr<float[]>& inputs) {
  float *inputsPtr = inputs.get();
  float *weightsPtr = m_weights.get();

  float out = 0.0f;
  for (uint16_t i=0; i!=m_inputCnt; ++i) {
    out += (inputsPtr[i] * weightsPtr[i]);
  }

  return out / (1 + abs(out));
}

Layer::Layer(uint16_t inputCnt, uint16_t neuronCnt, Generator& generator) {
  for (uint16_t i=0; i!=neuronCnt; ++i) {
    m_neurons.emplace_back(inputCnt, generator);
  }
}

std::shared_ptr<float[]> Layer::calc(const std::shared_ptr<float[]> &inputs) {
  auto output = std::shared_ptr<float[]>(new float[m_neurons.size()]);
  uint16_t i=0;
  for(Neuron& neuron :m_neurons) {
    output[i++] = neuron.calc(inputs);
  }
  return output;
}

NeuralNetwork::NeuralNetwork(uint16_t inputCnt, uint16_t neuronLayer0Cnt, Generator& generator)
  : m_layer0(inputCnt, neuronLayer0Cnt, generator)
  , m_output(neuronLayer0Cnt, generator) {

}

float NeuralNetwork::calc(const std::shared_ptr<float[]> &inputs) {
  return m_output.calc(m_layer0.calc(inputs));
}
