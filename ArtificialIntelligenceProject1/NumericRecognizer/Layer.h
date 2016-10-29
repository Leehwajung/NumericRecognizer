#pragma once
#include "Object.h"
#include "Neuron.h"


class Layer : public Object
{
public:
	/* Constructor / Destructor */

	// Constructor
	Layer();

	// Destructor
	~Layer();


private:
	/* Attributes */
	Neuron *m_neurons;
};

