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

#include "VstPlugin.h"
#include "Editor.h"

#include <cmath>

using namespace std;

//-------------------------------------------------------------------------------------------------------
AudioEffect *createEffectInstance(audioMasterCallback audioMaster)
{
	return new VstPlugin(audioMaster);
}
//----------------------------------------------------------------------------
VstPlugin::VstPlugin(audioMasterCallback audioMaster):
AudioEffectX(audioMaster, numPrograms, MVerb<float>::NUM_PARAMS),
programs(0),
samplerate(44100.0f),
frames(0),
effectName("MVerb"),
vendorName("Martin Eastwood")
{
	for(int i=0;i<MVerb<float>::NUM_PARAMS;++i)
		parameters[i] = 0.5f;

	programs = new PluginProgram[numPrograms];
	setProgram(4);
	setProgramName((char*)"Subtle");
	setParameter(MVerb<float>::DAMPINGFREQ, 0.);
	setParameter(MVerb<float>::DENSITY, 0.5);
	setParameter(MVerb<float>::BANDWIDTHFREQ, 1.);
	setParameter(MVerb<float>::DECAY, 0.5);
	setParameter(MVerb<float>::PREDELAY, 0.);
	setParameter(MVerb<float>::SIZE, 0.5);
    setParameter(MVerb<float>::GAIN, 1.);
	setParameter(MVerb<float>::MIX, 0.15);
	setParameter(MVerb<float>::EARLYMIX, 0.75);
	
	setProgram(3);
	setProgramName((char*)"Stadium");
	setParameter(MVerb<float>::DAMPINGFREQ, 0.);
	setParameter(MVerb<float>::DENSITY, 0.5);
	setParameter(MVerb<float>::BANDWIDTHFREQ, 1.);
	setParameter(MVerb<float>::DECAY, 0.5);
	setParameter(MVerb<float>::PREDELAY, 0.);
	setParameter(MVerb<float>::SIZE, 1.);
    setParameter(MVerb<float>::GAIN, 1.);
	setParameter(MVerb<float>::MIX, 0.35);
	setParameter(MVerb<float>::EARLYMIX, 0.75);
	
	setProgram(2);
	setProgramName((char*)"Cupboard");
	setParameter(MVerb<float>::DAMPINGFREQ, 0.);
	setParameter(MVerb<float>::DENSITY, 0.5);
	setParameter(MVerb<float>::BANDWIDTHFREQ, 1.);
	setParameter(MVerb<float>::DECAY, 0.5);
	setParameter(MVerb<float>::PREDELAY, 0.);
	setParameter(MVerb<float>::SIZE, 0.25);
    setParameter(MVerb<float>::GAIN, 1.);
	setParameter(MVerb<float>::MIX, 0.35);
	setParameter(MVerb<float>::EARLYMIX, 0.75);
	
	setProgram(1);
	setProgramName((char*)"Dark");
	setParameter(MVerb<float>::DAMPINGFREQ, 0.9);
	setParameter(MVerb<float>::DENSITY, 0.5);
	setParameter(MVerb<float>::BANDWIDTHFREQ, 0.1);
	setParameter(MVerb<float>::DECAY, 0.5);
	setParameter(MVerb<float>::PREDELAY, 0.);
	setParameter(MVerb<float>::SIZE, 0.5);
    setParameter(MVerb<float>::GAIN, 1.);
	setParameter(MVerb<float>::MIX, 0.5);
	setParameter(MVerb<float>::EARLYMIX, 0.75);

	setProgram(0);
	setProgramName((char*)"Halves");
	setParameter(MVerb<float>::DAMPINGFREQ, 0.5);
	setParameter(MVerb<float>::DENSITY, 0.5);
	setParameter(MVerb<float>::BANDWIDTHFREQ, 0.5);
	setParameter(MVerb<float>::DECAY, 0.5);
	setParameter(MVerb<float>::PREDELAY, 0.5);
    setParameter(MVerb<float>::GAIN, 1.);
	setParameter(MVerb<float>::MIX, 0.5);
	setParameter(MVerb<float>::EARLYMIX, 0.5);
	setParameter(MVerb<float>::SIZE, 0.75);
	
    setNumInputs(2);
    setNumOutputs(2);
    canProcessReplacing(true);
    isSynth(false);
    setUniqueID('emVB');
	editor = new Editor(this);
}

//----------------------------------------------------------------------------
VstPlugin::~VstPlugin()
{
	if(programs)
		delete [] programs;
}

//----------------------------------------------------------------------------
void VstPlugin::process(float **inputs, float **outputs, VstInt32 sampleFrames)
{
	em_verb.process(inputs, outputs, sampleFrames);
}

//----------------------------------------------------------------------------
void VstPlugin::processReplacing(float **inputs,
								 float **outputs,
								 VstInt32 sampleFrames)
{
	em_verb.process(inputs, outputs, sampleFrames);
}

//----------------------------------------------------------------------------
VstInt32 VstPlugin::processEvents(VstEvents *events)
{
	return 1;
}

//----------------------------------------------------------------------------
void VstPlugin::resume()
{
	em_verb.setSampleRate(getSampleRate());
	AudioEffectX::resume();
}

//----------------------------------------------------------------------------
void VstPlugin::suspend()
{
    
}

//----------------------------------------------------------------------------
void VstPlugin::setProgram(VstInt32 program)
{
	 int i;
	curProgram = program;
	for(i=0;i<MVerb<float>::NUM_PARAMS;++i)
		setParameter(i, programs[curProgram].parameters[i]);
}

//----------------------------------------------------------------------------
void VstPlugin::setProgramName(char *name)
{
	programs[curProgram].name = name;
}


//----------------------------------------------------------------------------
void VstPlugin::getProgramName(char *name)
{
	strcpy(name, programs[curProgram].name.c_str());
}

//----------------------------------------------------------------------------
bool VstPlugin::getProgramNameIndexed(VstInt32 category, VstInt32 index, char* text)
{
	bool retval = false;

    if(index < numPrograms)
    {
		strcpy(text, programs[index].name.c_str());
		retval = true;
    }

	return retval;
}

//----------------------------------------------------------------------------
bool VstPlugin::copyProgram(VstInt32 destination)
{
	bool retval = false;

    if(destination < numPrograms)
    {
		programs[destination] = programs[curProgram];
        retval = true;
    }

    return retval;
}

//----------------------------------------------------------------------------
void VstPlugin::setParameter(VstInt32 index, float value)
{
	if (index < MVerb<float>::NUM_PARAMS && value <= 1. && value >= 0. )
    {
            parameters[index] = value;
            em_verb.setParameter(index, parameters[index]);
            programs[curProgram].parameters[index] = parameters[index];
    }

	if(editor)
	{
		((AEffGUIEditor *)editor)->setParameter(index, value);
	}
}

//----------------------------------------------------------------------------
float VstPlugin::getParameter(VstInt32 index)
{
	 if (index < MVerb<float>::NUM_PARAMS)
        return parameters[index];
    else return 0.;
}

//----------------------------------------------------------------------------
void VstPlugin::getParameterLabel(VstInt32 index, char *label)
{
	if (index < MVerb<float>::NUM_PARAMS)
    {
        char tempch[8];
        sprintf(tempch, "p%d", static_cast<int>(index));
        strcpy(label, tempch);

        switch(index){
                case MVerb<float>::DAMPINGFREQ:
                        strcpy(label, "%");
                        break;
                case MVerb<float>::DENSITY:
                        strcpy(label, "%");
                        break;
                case MVerb<float>::BANDWIDTHFREQ:
                        strcpy(label, "%");
                        break;
                case MVerb<float>::PREDELAY:
                        strcpy(label, "%");
                        break;
                case MVerb<float>::DECAY:
                        strcpy(label, "%");;
                        break;
                case MVerb<float>::SIZE:
                        strcpy(label, "%");;
                        break;
                case MVerb<float>::GAIN:
                        strcpy(label, "%");
                        break;
                case MVerb<float>::MIX:
                        strcpy(label, "%");
                        break;
                case MVerb<float>::EARLYMIX:
                        strcpy(label, "%");
                        break;
                default: strcpy(label, "%");
                    break;
        }
    }
    else strcpy(label, "Nil");
}

//----------------------------------------------------------------------------
void VstPlugin::getParameterDisplay(VstInt32 index, char *text)
{
		if (index < MVerb<float>::NUM_PARAMS)
        float2string(em_verb.getParameter(index), text, 5);
    else
        float2string(0., text, 5);
}

//----------------------------------------------------------------------------
void VstPlugin::getParameterName(VstInt32 index, char *label)
{
	 if (index < MVerb<float>::NUM_PARAMS)
    {
        char tempch[8];

        sprintf(tempch, "p%d", static_cast<int>(index));
        strcpy(label, tempch);

        switch(index){
                case MVerb<float>::DAMPINGFREQ:
                        strcpy(label, "Damping");
                        break;
                case MVerb<float>::DENSITY:
                        strcpy(label, "Density");
                        break;
                case MVerb<float>::BANDWIDTHFREQ:
                        strcpy(label, "Bandwidth");
                        break;
                case MVerb<float>::PREDELAY:
                        strcpy(label, "Predelay");
                        break;
                case MVerb<float>::SIZE:
                        strcpy(label, "Size");
                        break;
                case MVerb<float>::DECAY:
                        strcpy(label, "Decay");;
                        break;
                case MVerb<float>::GAIN:
                        strcpy(label, "Gain");
                        break;
                case MVerb<float>::MIX:
                        strcpy(label, "Mix");
                        break;
                case MVerb<float>::EARLYMIX:
                        strcpy(label, "Early/Late Mix");
                        break;
                default: strcpy(label, " ");
                    break;
            }
    }
    else strcpy(label, "Nil");
}

//----------------------------------------------------------------------------
VstInt32 VstPlugin::canDo(char *text)
{
	if(!strcmp(text, "sendVstEvents")) return 1;
	if(!strcmp(text, "sendVstMidiEvent")) return 1;
	if(!strcmp(text, "sendVstTimeInfo")) return -1;
	if(!strcmp(text, "receiveVstEvents")) return 1;
	if(!strcmp(text, "receiveVstMidiEvent")) return 1;
	if(!strcmp(text, "receiveVstTimeInfo")) return 1;
	if(!strcmp(text, "offline")) return -1;
	if(!strcmp(text, "plugAsChannelInsert")) return -1;
	if(!strcmp(text, "plugAsSend")) return -1;
	if(!strcmp(text, "mixDryWet")) return -1;
	if(!strcmp(text, "noRealTime")) return -1;
	if(!strcmp(text, "multipass")) return -1;
	if(!strcmp(text, "metapass")) return -1;
	if(!strcmp(text, "1in1out")) return -1;
	if(!strcmp(text, "1in2out")) return -1;
	if(!strcmp(text, "2in1out")) return -1;
	if(!strcmp(text, "2in2out")) return -1;
	if(!strcmp(text, "2in4out")) return -1;
	if(!strcmp(text, "4in2out")) return -1;
	if(!strcmp(text, "4in4out")) return -1;
	if(!strcmp(text, "4in8out")) return -1;
	if(!strcmp(text, "8in4out")) return -1;
	if(!strcmp(text, "8in8out")) return -1;
	if(!strcmp(text, "midiProgramNames")) return -1;
	if(!strcmp(text, "conformsToWindowRules") ) return -1;
	if(!strcmp(text, "bypass")) return -1;

	return -1;
}

//----------------------------------------------------------------------------
bool VstPlugin::getEffectName(char* name)
{
    strcpy(name, effectName.c_str());

    return true;
}

//----------------------------------------------------------------------------
bool VstPlugin::getVendorString(char* text)
{
    strcpy(text, vendorName.c_str());

    return true;
}

//----------------------------------------------------------------------------
bool VstPlugin::getProductString(char* text)
{
    strcpy(text, effectName.c_str());

    return true;
}

//----------------------------------------------------------------------------
VstInt32 VstPlugin::getVendorVersion()
{
    return versionNumber;
}

//----------------------------------------------------------------------------
VstPlugCategory VstPlugin::getPlugCategory()
{
    return(kPlugCategEffect);
}

//----------------------------------------------------------------------------
bool VstPlugin::getInputProperties(VstInt32 index, VstPinProperties* properties)
{
	bool retval = false;

	if (index == 0 || index == 1 || index == 2 || index == 3)
	{
		properties->flags = kVstPinIsActive | kVstPinIsStereo;
	}
	if (index == 0)
	{
		strcpy(properties->label,	   "Left input");
		strcpy(properties->shortLabel, "L in");
		return true;
	}
	else if (index == 1)
	{
		strcpy(properties->label,	   "Right input");
		strcpy(properties->shortLabel, "R in");
		return true;
	}

	return false;
}

//----------------------------------------------------------------------------
bool VstPlugin::getOutputProperties(VstInt32 index, VstPinProperties* properties)
{
	if (index == 0 || index == 1)
	{
		properties->flags = kVstPinIsActive | kVstPinIsStereo;
	}
	if (index == 0)
	{
		strcpy(properties->label,	   "Left output");
		strcpy(properties->shortLabel, "L out");
		return true;
	}
	else if (index == 1)
	{
		strcpy(properties->label,	   "Right output");
		strcpy(properties->shortLabel, "R out");
		return true;
	}
	return false;
}