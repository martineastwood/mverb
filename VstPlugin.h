//	Copyright (c) 2010 Martin Eastwood
//  This code is distributed under the terms of the GNU General Public License

//  MVerb is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  at your option) any later version.
//
//  MVerb is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this MVerb.  If not, see <http://www.gnu.org/licenses/>.

#ifndef VSTPLUGIN_H_
#define VSTPLUGIN_H_

#include <string>
#include <stdio.h>
#include "audioeffectx.h"
#include "MVerb.h"

struct PluginProgram;

class VstPlugin : public AudioEffectX
{
public:
	VstPlugin(audioMasterCallback audioMaster);
	~VstPlugin();

	void process(float **inputs, float **outputs, VstInt32 sampleFrames);
	void processReplacing(float **inputs, float **outputs, VstInt32 sampleFrames);
	VstInt32 processEvents(VstEvents* events);
	void resume();
	void suspend();

	void setProgram(VstInt32 program);
	void setProgramName(char *name);
	void getProgramName(char *name);
	bool getProgramNameIndexed(VstInt32 category, VstInt32 index, char* text);
	bool copyProgram(VstInt32 destination);

	void setParameter(VstInt32 index, float value);
	float getParameter(VstInt32 index);
	void getParameterLabel(VstInt32 index, char *label);
	void getParameterDisplay(VstInt32 index, char *text);
	void getParameterName(VstInt32 index, char *text);

	VstInt32 canDo(char* text);
	bool getEffectName(char* name);
	bool getVendorString(char* text);
	bool getProductString(char* text);
	VstInt32 getVendorVersion();
	VstPlugCategory getPlugCategory();
	bool getInputProperties(VstInt32 index, VstPinProperties* properties);
	bool getOutputProperties(VstInt32 index, VstPinProperties* properties);


  private:
	enum
	{
		numPrograms = 5,
		versionNumber = 100
	};

    PluginProgram *programs;
	float samplerate;
	float parameters[MVerb<float>::NUM_PARAMS];
	VstInt32 frames;

	std::string effectName;
    std::string vendorName;

	MVerb<float> em_verb;
};

//---------------------------------------------------------------------------
struct PluginProgram
{
  public:
	PluginProgram():
	name("empty")
	{
		for(VstInt32 i=0;i<MVerb<float>::NUM_PARAMS;++i)
			parameters[i] = 0.0f;
	};
	float parameters[MVerb<float>::NUM_PARAMS];
	std::string name;
};

#endif
