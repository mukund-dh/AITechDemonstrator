// Fill out your copyright notice in the Description page of Project Settings.


#include "Attributes/AITDPsychAttrs.h"

UAITDPsychAttrs::UAITDPsychAttrs()
	: AttrVal(100.0f)
{
	bias = 0.0f;
	AttrValBeforeChange = 0.0f;
}

void UAITDPsychAttrs::AddInputForCompute(const FTraitInputBase& LayerInput)
{
	if (Inputs.Num() == 0)
	{
		Inputs.Add(LayerInput);
		return;
	}

	bool bFound = false;
	for (FTraitInputBase Trait : Inputs)
	{
		if (Trait.BaseAttribute.AttributeName == LayerInput.BaseAttribute.AttributeName)
		{
			bFound = true;
			break;
		}
	}

	if (!bFound)
	{
		Inputs.Add(LayerInput);
	}
}

void UAITDPsychAttrs::SetAttributeBias(float NewBias)
{
	bias = NewBias;
}

float UAITDPsychAttrs::GetAttributeBias() const
{
	return bias;
}
