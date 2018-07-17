#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "./math/taylor.h"

//DONE: Allocate an array of neurons
//TODO: Calculate outputs of neurons
//TODO: Backpropagation

typedef struct Neuron{
	float **weights;
	float **biases;
	float output;
} Neuron;

float squish(float input){
	return 1 / (1 + t_exp(input));
}

/* Description: Allocates an array (or layer) of Neurons, and then allocates and initializes each Neuron's weights and biases.
 * size: the size of the layer currently being build
 * previous_layer_size: the size of the preceding layer in the network (can be 0).
 *
 */
Neuron** create_layer(size_t size, size_t previous_layer_size){
	//Allocate every neuron in the layer
	Neuron** layer = (Neuron**)malloc(size*sizeof(Neuron*));
	for(int i = 0; i < size; i++){
		layer[i] = (Neuron*)malloc(size*sizeof(Neuron));
		
		//Allocate weights and biases
		for(int j = 0; j < size; j++){
			float **weights = (float**)malloc(previous_layer_size*sizeof(float*));
			float **biases = (float**)malloc(previous_layer_size*sizeof(float*));
			for(int k = 0; k < previous_layer_size; k++){
				weights[k] = (float*)malloc(previous_layer_size*sizeof(float));
			  biases[k] = (float*)malloc(previous_layer_size*sizeof(float));
				
				//Initialize weights and biases
				for(int l = 0; l < previous_layer_size; l++){
					weights[k][l] = ((float)(rand()%700))/100;
					biases[k][l] = ((float)(rand()&700))/100;	
				}
			}
			layer[i][j].weights = weights;
			layer[i][j].biases = biases;
		}
	}
	return layer;
}

/* Description: Sets the outputs of a layer manually, instead of calculating them. 
 *              The purpose of this function is to set the outputs of the input layer.
 * layer: The layer whose outputs will be set.
 * outputs: The array of outputs which will be assigned to the layer
 * important: dimensions of outputs and layer must both be size*size
 */
void setOutputs(Neuron** layer, float** outputs, size_t size){
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			layer[i][j].output = outputs[i][j];
 		}
	} 	
}

/* Description: Calculates the outputs of each neuron in a layer based on the outputs & weights of the neurons in the preceding layer
 * layer1: the layer with existing outputs
 * layer2: the layer whose outputs will be calculated
 * important: dimensions of weights of layer2 must match dimensions of neurons of layer1
 */
void calculateOutputs(Neuron** layer1, size_t layer_one_size, Neuron** layer2, size_t layer_two_size){
	for(int i = 0; i < layer_two_size; i++){
		for(int j = 0; j < layer_two_size; j++){
			float sum = 0;
			Neuron *current = &layer2[i][j];
			for(int k = 0; k < layer_one_size; k++){
				for(int l = 0; l < layer_one_size; l++){
						sum += layer1[k][l].output * layer2[i][j].weights[k][l];
						printf("%f + ", layer1[k][l].output);
				}
			}
			printf("= %f\n", sum);
			current->output = sum;	
		}
	}
}

void printOutputs(Neuron** layer, size_t size){
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			printf("%f, ", layer[i][j].output);
		}
		printf("\n");
	}
}

const int RANGE = 7;
int main(){
	srand(time(NULL));
	size_t input_layer_size = 28;
	size_t hidden_layer_size = 16;
	size_t output_layer_size = 10;

	Neuron** input_layer = create_layer(input_layer_size, 0);
	Neuron** hidden_layer = create_layer(hidden_layer_size, input_layer_size);
	Neuron** hidden_layer2 = create_layer(hidden_layer_size, input_layer_size);
	Neuron** output_layer = create_layer(output_layer_size, hidden_layer_size);

	float **inputs = (float**)malloc(input_layer_size*sizeof(float*));
	for(int k = 0; k < input_layer_size; k++){
		inputs[k] = (float*)malloc(input_layer_size*sizeof(float));
		for(int l = 0; l < input_layer_size; l++){
			inputs[k][l] = ((float)(rand()%RANGE)-(RANGE)/2.0)/100;
		}
	}

	setOutputs(input_layer, inputs, input_layer_size);

	calculateOutputs(input_layer, input_layer_size, hidden_layer, hidden_layer_size);	
	printOutputs(hidden_layer, hidden_layer_size);
}	




