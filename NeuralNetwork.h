#pragma once
#include <cstdint>
#include <memory>
#include <vector>
#include <random>

struct FGenerator {
  // [0; to]
  float get(float to) {
    return std::uniform_real_distribution<float>(0, to)(m_generator);
  }
private:
  std::mt19937 m_generator = std::mt19937(std::random_device()());
};

class Neuron {
public:
  Neuron() = delete;
  Neuron(uint16_t inputCnt, FGenerator& generator);
public:
  float calc(const std::shared_ptr<float[]>& inputs);
private:
  uint16_t m_inputCnt;
  std::unique_ptr<float[]> m_weights;
};

class Layer {
public:
  Layer() = delete;
  Layer(uint16_t inputCnt, uint16_t neuronCnt, FGenerator& generator);
public:
  std::shared_ptr<float[]> calc(const std::shared_ptr<float[]>& inputs);
private:
  std::vector<Neuron> m_neurons;
};

class NeuralNetwork {
public:
  NeuralNetwork(uint16_t inputCnt, uint16_t neuronLayer0Cnt, FGenerator& generator);
public:
  float calc(const std::shared_ptr<float[]>& inputs);
private:
  Layer m_layer0;
  Neuron m_output;
};

