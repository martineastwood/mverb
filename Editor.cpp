//	Editor.cpp - Declaration of the editor class.
//	---------------------------------------------------------------------------
//	Copyright (c) 2006 Niall Moody
//
//	Permission is hereby granted, free of charge, to any person obtaining a
//	copy of this software and associated documentation files (the "Software"),
//	to deal in the Software without restriction, including without limitation
//	the rights to use, copy, modify, merge, publish, distribute, sublicense,
//	and/or sell copies of the Software, and to permit persons to whom the
//	Software is furnished to do so, subject to the following conditions:
//
//	The above copyright notice and this permission notice shall be included in
//	all copies or substantial portions of the Software.
//
//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
//	THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//	DEALINGS IN THE SOFTWARE.
//	---------------------------------------------------------------------------

#include "Editor.h"
#include "VstPlugin.h"

AEffGUIEditor* createEditor (AudioEffectX* effect)
{
	return new Editor (effect);
}
//-----------------------------------------------------------------------------

Editor::Editor (void* ptr)
: AEffGUIEditor (ptr)
{
	backgroundImage = new CBitmap(BackgroundImage);

	rect.left   = 0;
	rect.top    = 0;
	rect.right  = static_cast<short>(backgroundImage->getWidth());
	rect.bottom = static_cast<short>(backgroundImage->getHeight());
}

//-----------------------------------------------------------------------------
Editor::~Editor()
{
	backgroundImage->forget();
}

//-----------------------------------------------------------------------------
bool Editor::open(void *systemPointer)
{
	CPoint offset;

	AEffEditor::open(systemPointer);

	//Initialise the frame.
	CRect size(0,
			   0,
			   backgroundImage->getWidth(),
			   backgroundImage->getHeight());
	frame = new CFrame(size, systemPointer, this);
	frame->setBackground(backgroundImage);

	//Create bitmaps.
	shapeImage = new CBitmap(ShapeImage);

	//Create shape knob.
	size.x = 56;
	size.y = 40;
	size.setHeight(shapeImage->getHeight()/129);
	size.setWidth(shapeImage->getWidth());
	offset.x = size.x;
	offset.y = size.y;
	mixknob = new CAnimKnob(size, this, MVerb<float>::MIX, 129, shapeImage->getHeight()/129, shapeImage, 0);
	frame->addView(mixknob);
	mixknob->setValue(effect->getParameter(MVerb<float>::MIX));

	//Create shape knob.
	size.x = 96;
	size.y = 40;
	size.setHeight(shapeImage->getHeight()/129);
	size.setWidth(shapeImage->getWidth());
	offset.x = size.x;
	offset.y = size.y;
	delayknob = new CAnimKnob(size, this, MVerb<float>::PREDELAY, 129, shapeImage->getHeight()/129, shapeImage, 0);
	frame->addView(delayknob);
	delayknob->setValue(effect->getParameter(MVerb<float>::PREDELAY));

	//Create shape knob.
	size.x = 136;
	size.y = 40;
	size.setHeight(shapeImage->getHeight()/129);
	size.setWidth(shapeImage->getWidth());
	offset.x = size.x;
	offset.y = size.y;
	earlymixknob = new CAnimKnob(size, this, MVerb<float>::EARLYMIX, 129, shapeImage->getHeight()/129, shapeImage, 0);
	frame->addView(earlymixknob);
	earlymixknob->setValue(effect->getParameter(MVerb<float>::EARLYMIX));

	//Create shape knob.
	size.x = 176;
	size.y = 40;
	size.setHeight(shapeImage->getHeight()/129);
	size.setWidth(shapeImage->getWidth());
	offset.x = size.x;
	offset.y = size.y;
	sizeknob = new CAnimKnob(size, this, MVerb<float>::SIZE, 129, shapeImage->getHeight()/129, shapeImage, 0);
	frame->addView(sizeknob);
	sizeknob->setValue(effect->getParameter(MVerb<float>::SIZE));

	//Create shape knob.
	size.x = 216;
	size.y = 40;
	size.setHeight(shapeImage->getHeight()/129);
	size.setWidth(shapeImage->getWidth());
	offset.x = size.x;
	offset.y = size.y;
	densityknob = new CAnimKnob(size, this, MVerb<float>::DENSITY, 129, shapeImage->getHeight()/129, shapeImage, 0);
	frame->addView(densityknob);
	densityknob->setValue(effect->getParameter(MVerb<float>::DENSITY));

	//Create shape knob.
	size.x = 256;
	size.y = 40;
	size.setHeight(shapeImage->getHeight()/129);
	size.setWidth(shapeImage->getWidth());
	offset.x = size.x;
	offset.y = size.y;
	bandknob = new CAnimKnob(size, this, MVerb<float>::BANDWIDTHFREQ, 129, shapeImage->getHeight()/129, shapeImage, 0);
	frame->addView(bandknob);
	bandknob->setValue(effect->getParameter(MVerb<float>::BANDWIDTHFREQ));

	//Create shape knob.
	size.x = 296;
	size.y = 40;
	size.setHeight(shapeImage->getHeight()/129);
	size.setWidth(shapeImage->getWidth());
	offset.x = size.x;
	offset.y = size.y;
	decayknob = new CAnimKnob(size, this, MVerb<float>::DECAY, 129, shapeImage->getHeight()/129, shapeImage, 0);
	frame->addView(decayknob);
	decayknob->setValue(effect->getParameter(MVerb<float>::DECAY));

	//Create shape knob.
	size.x = 336;
	size.y = 40;
	size.setHeight(shapeImage->getHeight()/129);
	size.setWidth(shapeImage->getWidth());
	offset.x = size.x;
	offset.y = size.y;
	dampknob = new CAnimKnob(size, this, MVerb<float>::DAMPINGFREQ, 129, shapeImage->getHeight()/129, shapeImage, 0);
	frame->addView(dampknob);
	dampknob->setValue(effect->getParameter(MVerb<float>::DAMPINGFREQ));

	//Create shape knob.
	size.x = 376;
	size.y = 40;
	size.setHeight(shapeImage->getHeight()/129);
	size.setWidth(shapeImage->getWidth());
	offset.x = size.x;
	offset.y = size.y;
	gainknob = new CAnimKnob(size, this, MVerb<float>::GAIN, 129, shapeImage->getHeight()/129, shapeImage, 0);
	frame->addView(gainknob);
	gainknob->setValue(effect->getParameter(MVerb<float>::GAIN));

	size.x = 60;
	size.y = 77;
	size.setHeight(10);
	size.setWidth(25);
	offset.x = size.x;
	offset.y = size.y;
	mixdisplay = new CParamDisplay (size);
	mixdisplay->setFont (kNormalFont);
	mixdisplay->setFontColor (kWhiteCColor);
	mixdisplay->setBackColor (kBlackCColor);
	mixdisplay->setFrameColor(kWhiteCColor);
	mixdisplay->setTransparency(true);
	mixdisplay->setValue ( (effect->getParameter(MVerb<float>::MIX))); 
	frame->addView (mixdisplay);

	size.x = 95;
	size.y = 77;
	size.setHeight(10);
	size.setWidth(35);
	offset.x = size.x;
	offset.y = size.y;
	delaydisplay = new CParamDisplay (size);
	delaydisplay->setFont (kNormalFont);
	delaydisplay->setFontColor (kWhiteCColor);
	delaydisplay->setBackColor (kBlackCColor);
	delaydisplay->setFrameColor(kWhiteCColor);
	delaydisplay->setTransparency(true);
	delaydisplay->setValue (effect->getParameter(MVerb<float>::PREDELAY)*100.f);
	frame->addView (delaydisplay);

	size.x = 135;
	size.y = 77;
	size.setHeight(10);
	size.setWidth(35);
	offset.x = size.x;
	offset.y = size.y;
	earlymixdisplay = new CParamDisplay (size);
	earlymixdisplay->setFont (kNormalFont);
	earlymixdisplay->setFontColor (kWhiteCColor);
	earlymixdisplay->setBackColor (kBlackCColor);
	earlymixdisplay->setFrameColor(kWhiteCColor);
	earlymixdisplay->setTransparency(true);
	earlymixdisplay->setValue ( (effect->getParameter (MVerb<float>::EARLYMIX ))); 
	frame->addView (earlymixdisplay);

	size.x = 175;
	size.y = 77;
	size.setHeight(10);
	size.setWidth(35);
	offset.x = size.x;
	offset.y = size.y;
	sizedisplay = new CParamDisplay (size);
	sizedisplay->setFont (kNormalFont);
	sizedisplay->setFontColor (kWhiteCColor);
	sizedisplay->setBackColor (kBlackCColor);
	sizedisplay->setFrameColor(kWhiteCColor);
	sizedisplay->setTransparency(true);
	sizedisplay->setValue (((0.95 * effect->getParameter(MVerb<float>::SIZE) + 0.05)) * 100.); 
	frame->addView (sizedisplay);

	size.x = 215;
	size.y = 77;
	size.setHeight(10);
	size.setWidth(35);
	offset.x = size.x;
	offset.y = size.y;
	densitydisplay = new CParamDisplay (size);
	densitydisplay->setFont (kNormalFont);
	densitydisplay->setFontColor (kWhiteCColor);
	densitydisplay->setBackColor (kBlackCColor);
	densitydisplay->setFrameColor(kWhiteCColor);
	densitydisplay->setTransparency(true);
	densitydisplay->setValue (effect->getParameter(MVerb<float>::DENSITY)*100.f);
	frame->addView (densitydisplay);

	size.x = 255;
	size.y = 77;
	size.setHeight(10);
	size.setWidth(35);
	offset.x = size.x;
	offset.y = size.y;
	banddisplay = new CParamDisplay (size);
	banddisplay->setFont (kNormalFont);
	banddisplay->setFontColor (kWhiteCColor);
	banddisplay->setBackColor (kBlackCColor);
	banddisplay->setFrameColor(kWhiteCColor);
	banddisplay->setTransparency(true);
	banddisplay->setValue (effect->getParameter (MVerb<float>::BANDWIDTHFREQ)*100.); 
	frame->addView (banddisplay);

	size.x = 295;
	size.y = 77;
	size.setHeight(10);
	size.setWidth(35);
	offset.x = size.x;
	offset.y = size.y;
	decaydisplay = new CParamDisplay (size);
	decaydisplay->setFont (kNormalFont);
	decaydisplay->setFontColor (kWhiteCColor);
	decaydisplay->setBackColor (kBlackCColor);
	decaydisplay->setFrameColor(kWhiteCColor);
	decaydisplay->setTransparency(true);
	decaydisplay->setValue (effect->getParameter (MVerb<float>::DECAY)*100.); 
	frame->addView (decaydisplay);

	size.x = 335;
	size.y = 77;
	size.setHeight(10);
	size.setWidth(35);
	offset.x = size.x;
	offset.y = size.y;
	dampdisplay = new CParamDisplay (size);
	dampdisplay->setFont (kNormalFont);
	dampdisplay->setFontColor (kWhiteCColor);
	dampdisplay->setBackColor (kBlackCColor);
	dampdisplay->setFrameColor(kWhiteCColor);
	dampdisplay->setTransparency(true);
	dampdisplay->setValue (effect->getParameter (MVerb<float>::DAMPINGFREQ)*100.); 
	frame->addView (dampdisplay);

	size.x = 375;
	size.y = 77;
	size.setHeight(10);
	size.setWidth(35);
	offset.x = size.x;
	offset.y = size.y;
	gaindisplay = new CParamDisplay (size);
	gaindisplay->setFont (kNormalFont);
	gaindisplay->setFontColor (kWhiteCColor);
	gaindisplay->setBackColor (kBlackCColor);
	gaindisplay->setFrameColor(kWhiteCColor);
	gaindisplay->setTransparency(true);
	gaindisplay->setValue (effect->getParameter (MVerb<float>::GAIN)*100.); 
	frame->addView (gaindisplay);

	setKnobMode(kLinearMode);
	shapeImage->forget();

	return true;
}

//-----------------------------------------------------------------------------
void Editor::close()
{
	delete frame;
	frame = 0;
}

//-----------------------------------------------------------------------------
void Editor::setParameter(VstInt32 index, float value)
{
	if(!frame)
		return;

	switch(index)
	{
		case MVerb<float>::MIX:
			mixknob->setValue(value);
			mixdisplay->setValue (value); 
			break;
		case MVerb<float>::SIZE:
			sizeknob->setValue(value);
			sizedisplay->setValue (((0.95 * value) + 0.05)*100.); 
			break;
		case MVerb<float>::PREDELAY:
			delayknob->setValue(value);
			delaydisplay->setValue (value * 100.); 
			break;
		case MVerb<float>::EARLYMIX:
			earlymixknob->setValue(value);
			earlymixdisplay->setValue (value ); 
			break;
		case MVerb<float>::DENSITY:
			densityknob->setValue(value);
			densitydisplay->setValue (value * 100 ); 
			break;
		case MVerb<float>::BANDWIDTHFREQ:
			bandknob->setValue(value);
			banddisplay->setValue (value * 100); 
			break;
		case MVerb<float>::DECAY:
			decayknob->setValue(value);
			decaydisplay->setValue (value * 100); 
			break;
		case MVerb<float>::DAMPINGFREQ:
			dampknob->setValue(value );
			dampdisplay->setValue (value * 100); 
			break;
		case MVerb<float>::GAIN:
			gainknob->setValue(value);
			gaindisplay->setValue (value * 100); 
			break;
	}
}
void Editor::valueChanged (CControl* pControl)
{
 if(pControl->getTag() < MVerb<float>::NUM_PARAMS)
		effect->setParameterAutomated(pControl->getTag(), pControl->getValue());
}

void Editor::idle ()
{
	AEffGUIEditor::idle();
}