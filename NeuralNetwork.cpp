#include "NeuralNetwork.h"
#include <iostream>


Neuron::Neuron(uint16_t inputCnt, Generator& generator)
  : m_inputCnt(inputCnt)
  , m_weights(new float[inputCnt]) {

  float *ptr = m_weights.get();
  for (uint16_t i=0; i!=m_inputCnt; ++i) {
    ptr[i] = generator.getf(1.0f);
  }
}

void Neuron::cloneFrom(Neuron &parent, Generator &generator) {
  float *ptr = m_weights.get();
  float *parentPtr = parent.m_weights.get();
  for (uint16_t i=0; i!=m_inputCnt; ++i) {
    if (generator.get(10) == 0) {
      ptr[i] = generator.getf(1.0f);
    } else {
      ptr[i] = parentPtr[i];
    }
  }
}

float Neuron::calc(const std::shared_ptr<float[]>& inputs) {
  float *inputsPtr = inputs.get();
  float *weightsPtr = m_weights.get();

  float out = 0.0f;
  for (uint16_t i=0; i!=m_inputCnt; ++i) {
    out += (inputsPtr[i] * weightsPtr[i]);
  }

  float result = (1.0f / (exp(-out) + 1.0f));
//  std::cout << result << std::endl;
  return result;
//  return out / (1 + abs(out));
}

Layer::Layer(uint16_t inputCnt, uint16_t neuronCnt, Generator& generator) {
  for (uint16_t i=0; i!=neuronCnt; ++i) {
    m_neurons.emplace_back(inputCnt, generator);
  }
}

void Layer::cloneFrom(Layer& parent, Generator &generator) {
  for (size_t i=0; i!=m_neurons.size(); ++i) {
    m_neurons[i].cloneFrom(parent.m_neurons[i], generator);
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

NeuralNetwork::NeuralNetwork(uint16_t inputCnt, uint16_t neuronLayer0Cnt, uint16_t neuronLayer1Cnt, Generator& generator)
  : m_layer0(inputCnt, neuronLayer0Cnt, generator)
  , m_layer1(neuronLayer0Cnt, neuronLayer1Cnt, generator) {

}

void NeuralNetwork::cloneFrom(NeuralNetwork &parent, Generator &generator) {
  m_layer0.cloneFrom(parent.m_layer0, generator);
}

const std::shared_ptr<float[]> NeuralNetwork::calc(const std::shared_ptr<float[]> &inputs) {
//  return m_layer1.calc(m_layer0.calc(inputs));
  return inputs;
}
