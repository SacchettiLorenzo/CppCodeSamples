// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com


#include <iostream>
#include <vector>

using namespace std;

struct Neuron;

template <typename Self>
	struct SomeNeurons {
		template<typename T> void connect_to(T& other) {
			for (Neuron& from : *static_cast<Self*>(this)) {
				for (Neuron& to : other) {
					from.out.push_back(&to);
					to.in.push_back(&from);
				}
			}
		}
	};

struct Neuron : SomeNeurons<Neuron>{
	
	vector<Neuron*> in, out;
	unsigned int id;

	Neuron() {
		static int id = 1; 
		this->id = id++;
	}

	Neuron* begin() { return this; }
	Neuron* end() { return this + 1; }
	
};

struct NeuronLayer : vector<Neuron> , SomeNeurons<NeuronLayer> {
	NeuronLayer(int count) {
		while (count-- > 0) {
			emplace_back(Neuron{});
		}
	}
};



int main() {
	Neuron n1, n2;

	NeuronLayer l1(1), l2(1);

	n1.connect_to(n2);

	n1.connect_to(l1);

	l1.connect_to(n1);

	l1.connect_to(l2);

}