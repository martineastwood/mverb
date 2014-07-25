//	Editor.h - Declaration of the editor class.
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

#ifndef EDITOR_H_
#define EDITOR_H_

#include "aeffguieditor.h"
#include "ctooltipsupport.h"

///	Declaration of the editor class.
class Editor : public AEffGUIEditor,
			   public CControlListener
{
  public:
	///	Constructor.
	//Editor(AudioEffect* effect);
	  Editor (void*);
	///	Destructor.
	~Editor();

	///	Called when the editor should be opened.
	bool open(void *systemPointer);
	///	Called when the editor should be closed.
	void close();

	///	Called from the plugin to set a parameter.
	void setParameter(VstInt32 index, float value);
	///	Called from controls when their value changes.
	//void valueChanged(CDrawContext *context, CControl *control);
	void valueChanged (CControl* pControl);
	//do idle stuff
	void idle ();
  private:
	///	Enum keeping track of the image IDs.
	enum
	{
		BackgroundImage = 127,
		ShapeImage,
		FeedbackImage,
		SourceImage,
		LightImage,
		FootswitchImage,
		AboutImage
	};
 
	///	Shape knob.
	CAnimKnob *mixknob;
	///	Feedback knob.
	CAnimKnob *delayknob;
	///	Feedback knob.
	CAnimKnob *earlymixknob;
	///	Feedback knob.
	CAnimKnob *sizeknob;
	///	Feedback knob.
	CAnimKnob *densityknob;
	///	Feedback knob.
	CAnimKnob *bandknob;
	///	Feedback knob.
	CAnimKnob *decayknob;
	///	Feedback knob.
	CAnimKnob *dampknob;
	///	Feedback knob.
	CAnimKnob *gainknob;

	CParamDisplay     *mixdisplay;
	CParamDisplay     *delaydisplay;
	CParamDisplay     *earlymixdisplay;
	CParamDisplay     *sizedisplay;
	CParamDisplay     *densitydisplay;
	CParamDisplay     *banddisplay;
	CParamDisplay     *decaydisplay;
	CParamDisplay     *dampdisplay;
	CParamDisplay     *gaindisplay;


	//CTooltipSupport* tooltipSupport;

	///	Bitmap for the background image.
	CBitmap *backgroundImage;
	///	Bitmap for the shape knob.
	CBitmap *shapeImage;
	///	Bitmap for the feedback knob.
	CBitmap *feedbackImage;
	///	Bitmap for the source switch.
	CBitmap *sourceImage;
	///	Bitmap for the footswitch light.
	CBitmap *lightImage;
	///	Bitmap for the footswitch.
	CBitmap *footswitchImage;
	///	Bitmap for the about page.
	CBitmap *aboutImage;
};

#endif
