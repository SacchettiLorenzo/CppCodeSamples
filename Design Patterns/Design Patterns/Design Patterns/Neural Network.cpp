// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com


#include <iostream>
#include <vector>

using namespace std;

struct Neuron;

/*this sample use self-inheritance to create groups of neurons*/

/*SomeNeurons is a generic group of neurons. could be 1 or more neuron. it can connect neurons in 1to1 - 1toN - Nto1 - NtoN way*/
template <typename Self>
	struct SomeNeurons {
		template<typename T> //the template enable use of the same class for connecting sigle neuron and layers in the same way
		void connect_to(T& other) {
			for (Neuron& from : *static_cast<Self*>(this)) { //"this" could be a single neuron or a layer
				for (Neuron& to : other) { //the neuron or layer to be connected to
					//each neuron is connected with each other neuron in both ways
					from.out.push_back(&to);
					to.in.push_back(&from);
				}
			}
		}
	};

//single neuron as subclass of a genric group of neurons
//this class hold the connection with the other neurons
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

//list of neurons as subclass of generic group of neurons. treted as a vector
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