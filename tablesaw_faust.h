/* ------------------------------------------------------------
author: "Benjamin Quiedeville"
name: "TableSaw"
version: "0.0.1"
Code generated with Faust 2.54.9 (https://faust.grame.fr)
Compilation options: -a minimal-effect.cpp -lang cpp -es 1 -mcd 16 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__

/************************************************************************
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each section
 is governed by its own copyright and license. Please check individually
 each section for license and copyright information.
 *************************************************************************/

/******************* BEGIN minimal-effect.cpp ****************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2019 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 
 ************************************************************************
 ************************************************************************/
 
#include <algorithm>

#include "faust/gui/UI.h"
#include "faust/gui/meta.h"
#include "faust/dsp/dsp.h"

#if defined(SOUNDFILE)
#include "faust/gui/SoundUI.h"
#endif

using std::max;
using std::min;

/******************************************************************************
 *******************************************************************************
 
 VECTOR INTRINSICS
 
 *******************************************************************************
 *******************************************************************************/


/********************END ARCHITECTURE SECTION (part 1/2)****************/

/**************************BEGIN USER SECTION **************************/

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

/* link with : "" */
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

#if defined(_WIN32)
#define RESTRICT __restrict
#else
#define RESTRICT __restrict__
#endif

static float mydsp_faustpower2_f(float value) {
	return value * value;
}

class mydsp final : public dsp {
	
 private:
	
	FAUSTFLOAT fHslider0;
	int fSampleRate;
	float fConst1;
	float fConst3;
	float fConst4;
	float fConst5;
	float fConst7;
	float fConst8;
	FAUSTFLOAT fHslider1;
	float fConst9;
	float fConst11;
	float fConst12;
	float fConst16;
	float fRec9[3];
	float fRec8[3];
	FAUSTFLOAT fHslider2;
	float fVec0[2];
	float fConst17;
	float fConst18;
	float fRec7[2];
	float fVec1[2];
	float fConst20;
	float fConst21;
	float fRec6[2];
	float fConst23;
	float fConst24;
	float fConst26;
	float fConst27;
	float fRec5[2];
	float fRec4[3];
	float fRec3[3];
	float fRec2[3];
	FAUSTFLOAT fHslider3;
	float fRec1[3];
	float fRec0[3];
	float fRec19[3];
	float fRec18[3];
	float fVec2[2];
	float fRec17[2];
	float fVec3[2];
	float fRec16[2];
	float fRec15[2];
	float fRec14[3];
	float fRec13[3];
	float fRec12[3];
	float fRec11[3];
	float fRec10[3];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("author", "Benjamin Quiedeville");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.9");
		m->declare("compile_options", "-a minimal-effect.cpp -lang cpp -es 1 -mcd 16 -single -ftz 0");
		m->declare("description", "Boss HM2 Emulation");
		m->declare("filename", "tablesaw.dsp");
		m->declare("filter.lib/author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("filter.lib/copyright", "Julius O. Smith III");
		m->declare("filter.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.");
		m->declare("filter.lib/license", "STK-4.3");
		m->declare("filter.lib/name", "Faust Filter Library");
		m->declare("filter.lib/reference", "https://ccrma.stanford.edu/~jos/filters/");
		m->declare("filter.lib/version", "1.29");
		m->declare("filters.lib/fir:author", "Julius O. Smith III");
		m->declare("filters.lib/fir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/fir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/iir:author", "Julius O. Smith III");
		m->declare("filters.lib/iir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/lowpass0_highpass1:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/lowpass:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/tf2:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2s:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2s:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2s:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/version", "0.3");
		m->declare("math.lib/author", "GRAME");
		m->declare("math.lib/copyright", "GRAME");
		m->declare("math.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.");
		m->declare("math.lib/license", "LGPL with exception");
		m->declare("math.lib/name", "Math Library");
		m->declare("math.lib/version", "1.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.5");
		m->declare("music.lib/author", "GRAME");
		m->declare("music.lib/copyright", "GRAME");
		m->declare("music.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.");
		m->declare("music.lib/license", "LGPL with exception");
		m->declare("music.lib/name", "Music Library");
		m->declare("music.lib/version", "1.0");
		m->declare("name", "TableSaw");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "0.3");
		m->declare("version", "0.0.1");
	}

	static constexpr int getStaticNumInputs() {
		return 2;
	}
	static constexpr int getStaticNumOutputs() {
		return 2;
	}
	int getNumInputs() {
		return 2;
	}
	int getNumOutputs() {
		return 2;
	}
	
	static void classInit(int sample_rate) {
	}
	
	void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		float fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = 6283.1855f / (fConst0 * std::sin(6283.1855f / fConst0));
		float fConst2 = std::tan(3141.5928f / fConst0);
		fConst3 = 1.0f / fConst2;
		fConst4 = 2.0f * (1.0f - 1.0f / mydsp_faustpower2_f(fConst2));
		fConst5 = 9424.778f / (fConst0 * std::sin(9424.778f / fConst0));
		float fConst6 = std::tan(4712.389f / fConst0);
		fConst7 = 1.0f / fConst6;
		fConst8 = 2.0f * (1.0f - 1.0f / mydsp_faustpower2_f(fConst6));
		fConst9 = 502.65482f / (fConst0 * std::sin(502.65482f / fConst0));
		float fConst10 = std::tan(251.32741f / fConst0);
		fConst11 = 1.0f / fConst10;
		fConst12 = 2.0f * (1.0f - 1.0f / mydsp_faustpower2_f(fConst10));
		float fConst13 = std::tan(31.415926f / fConst0);
		float fConst14 = 1.0f / fConst13;
		float fConst15 = fConst14 + 1.0f;
		fConst16 = (1.0f - fConst14) / fConst15;
		fConst17 = 1.0f / (fConst13 * fConst15);
		fConst18 = 0.0f - fConst17;
		float fConst19 = 1.0f / std::tan(37699.113f / fConst0);
		fConst20 = 1.0f - fConst19;
		fConst21 = 1.0f / (fConst19 + 1.0f);
		float fConst22 = std::tan(94.24778f / fConst0);
		fConst23 = 1.0f / fConst22;
		fConst24 = 1.0f - fConst23;
		float fConst25 = fConst23 + 1.0f;
		fConst26 = 1.0f / fConst25;
		fConst27 = 0.0f - 1.0f / (fConst22 * fConst25);
	}
	
	void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(0.5f);
		fHslider1 = FAUSTFLOAT(0.5f);
		fHslider2 = FAUSTFLOAT(0.5f);
		fHslider3 = FAUSTFLOAT(0.5f);
	}
	
	void instanceClear() {
		for (int l0 = 0; l0 < 3; l0 = l0 + 1) {
			fRec9[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 3; l1 = l1 + 1) {
			fRec8[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fVec0[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec7[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fVec1[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec6[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			fRec5[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 3; l7 = l7 + 1) {
			fRec4[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 3; l8 = l8 + 1) {
			fRec3[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 3; l9 = l9 + 1) {
			fRec2[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 3; l10 = l10 + 1) {
			fRec1[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 3; l11 = l11 + 1) {
			fRec0[l11] = 0.0f;
		}
		for (int l12 = 0; l12 < 3; l12 = l12 + 1) {
			fRec19[l12] = 0.0f;
		}
		for (int l13 = 0; l13 < 3; l13 = l13 + 1) {
			fRec18[l13] = 0.0f;
		}
		for (int l14 = 0; l14 < 2; l14 = l14 + 1) {
			fVec2[l14] = 0.0f;
		}
		for (int l15 = 0; l15 < 2; l15 = l15 + 1) {
			fRec17[l15] = 0.0f;
		}
		for (int l16 = 0; l16 < 2; l16 = l16 + 1) {
			fVec3[l16] = 0.0f;
		}
		for (int l17 = 0; l17 < 2; l17 = l17 + 1) {
			fRec16[l17] = 0.0f;
		}
		for (int l18 = 0; l18 < 2; l18 = l18 + 1) {
			fRec15[l18] = 0.0f;
		}
		for (int l19 = 0; l19 < 3; l19 = l19 + 1) {
			fRec14[l19] = 0.0f;
		}
		for (int l20 = 0; l20 < 3; l20 = l20 + 1) {
			fRec13[l20] = 0.0f;
		}
		for (int l21 = 0; l21 < 3; l21 = l21 + 1) {
			fRec12[l21] = 0.0f;
		}
		for (int l22 = 0; l22 < 3; l22 = l22 + 1) {
			fRec11[l22] = 0.0f;
		}
		for (int l23 = 0; l23 < 3; l23 = l23 + 1) {
			fRec10[l23] = 0.0f;
		}
	}
	
	void init(int sample_rate) {
		classInit(sample_rate);
		instanceInit(sample_rate);
	}
	void instanceInit(int sample_rate) {
		instanceConstants(sample_rate);
		instanceResetUserInterface();
		instanceClear();
	}
	
	mydsp* clone() {
		return new mydsp();
	}
	
	int getSampleRate() {
		return fSampleRate;
	}
	
	void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("TableSaw");
		ui_interface->addHorizontalSlider("gain", &fHslider2, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.1f));
		ui_interface->addHorizontalSlider("high", &fHslider0, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.1f));
		ui_interface->addHorizontalSlider("low", &fHslider1, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.1f));
		ui_interface->addHorizontalSlider("vol", &fHslider3, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
	}
	
	void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = 2e+01f * float(fHslider0);
		int iSlow1 = fSlow0 > 0.0f;
		float fSlow2 = std::pow(1e+01f, 0.05f * std::fabs(fSlow0));
		float fSlow3 = fConst1 * fSlow2;
		float fSlow4 = ((iSlow1) ? fConst1 : fSlow3);
		float fSlow5 = fConst3 * (fConst3 + fSlow4) + 1.0f;
		float fSlow6 = ((iSlow1) ? fSlow3 : fConst1);
		float fSlow7 = fConst3 * (fConst3 - fSlow6) + 1.0f;
		float fSlow8 = 1.0f - fConst3 * (fSlow4 - fConst3);
		float fSlow9 = fConst5 * fSlow2;
		float fSlow10 = ((iSlow1) ? fConst5 : fSlow9);
		float fSlow11 = fConst7 * (fConst7 + fSlow10) + 1.0f;
		float fSlow12 = ((iSlow1) ? fSlow9 : fConst5);
		float fSlow13 = fConst7 * (fConst7 - fSlow12) + 1.0f;
		float fSlow14 = fConst7 * (fConst7 - fSlow10) + 1.0f;
		float fSlow15 = 2e+01f * float(fHslider1);
		int iSlow16 = fSlow15 > 0.0f;
		float fSlow17 = fConst9 * std::pow(1e+01f, 0.05f * std::fabs(fSlow15));
		float fSlow18 = ((iSlow16) ? fConst9 : fSlow17);
		float fSlow19 = fConst11 * (fConst11 + fSlow18) + 1.0f;
		float fSlow20 = ((iSlow16) ? fSlow17 : fConst9);
		float fSlow21 = fConst11 * (fConst11 - fSlow20) + 1.0f;
		float fSlow22 = fConst11 * (fConst11 - fSlow18) + 1.0f;
		float fSlow23 = 0.6666667f * std::pow(1e+01f, 3.0f * float(fHslider2));
		float fSlow24 = fConst11 * (fConst11 + fSlow20) + 1.0f;
		float fSlow25 = fConst7 * (fConst7 + fSlow12) + 1.0f;
		float fSlow26 = fConst3 * (fConst3 + fSlow6) + 1.0f;
		float fSlow27 = 0.1f * float(fHslider3);
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			float fTemp0 = fConst4 * fRec2[1];
			float fTemp1 = fConst8 * fRec3[1];
			float fTemp2 = fConst12 * fRec4[1];
			fRec9[0] = float(input0[i0]) + 0.9505005f * fRec9[1] - 0.2499908f * fRec9[2];
			fRec8[0] = 0.14974517f * fRec9[1] + 0.07487258f * (fRec9[0] + fRec9[2]) + 1.2180791f * fRec8[1] - 0.60187995f * fRec8[2];
			float fTemp3 = fSlow23 * (0.19190045f * fRec8[1] + 0.09595022f * (fRec8[0] + fRec8[2]));
			float fTemp4 = tanhf(std::min<float>(0.0f, fTemp3)) + std::max<float>(0.0f, std::min<float>(1.0f, fTemp3)) + tanhf(std::max<float>(1.0f, fTemp3) + -1.0f);
			fVec0[0] = fTemp4;
			fRec7[0] = 1.5f * (fConst17 * fTemp4 + fConst18 * fVec0[1]) - fConst16 * fRec7[1];
			float fTemp5 = std::max<float>(-0.7f, std::min<float>(0.7f, std::max<float>(0.1f, fRec7[0]) + std::min<float>(-0.1f, fRec7[0])));
			fVec1[0] = fTemp5;
			fRec6[0] = 0.0f - fConst21 * (fConst20 * fRec6[1] - (fTemp5 + fVec1[1]));
			fRec5[0] = fConst27 * fRec6[1] - fConst26 * (fConst24 * fRec5[1] - fConst23 * fRec6[0]);
			fRec4[0] = fRec5[0] - (fRec4[2] * fSlow22 + fTemp2) / fSlow19;
			fRec3[0] = (fTemp2 + fRec4[0] * fSlow24 + fRec4[2] * fSlow21) / fSlow19 - (fRec3[2] * fSlow14 + fTemp1) / fSlow11;
			fRec2[0] = (fTemp1 + fRec3[0] * fSlow25 + fRec3[2] * fSlow13) / fSlow11 - (fRec2[2] * fSlow8 + fTemp0) / fSlow5;
			fRec1[0] = fSlow27 * ((fTemp0 + fRec2[0] * fSlow26 + fRec2[2] * fSlow7) / fSlow5) + 0.9505005f * fRec1[1] - 0.2499908f * fRec1[2];
			fRec0[0] = 0.14974517f * fRec1[1] + 0.07487258f * (fRec1[0] + fRec1[2]) + 1.2180791f * fRec0[1] - 0.60187995f * fRec0[2];
			output0[i0] = FAUSTFLOAT(0.19190045f * fRec0[1] + 0.09595022f * (fRec0[0] + fRec0[2]));
			float fTemp6 = fConst4 * fRec12[1];
			float fTemp7 = fConst8 * fRec13[1];
			float fTemp8 = fConst12 * fRec14[1];
			fRec19[0] = float(input1[i0]) + 0.9505005f * fRec19[1] - 0.2499908f * fRec19[2];
			fRec18[0] = 0.14974517f * fRec19[1] + 0.07487258f * (fRec19[0] + fRec19[2]) + 1.2180791f * fRec18[1] - 0.60187995f * fRec18[2];
			float fTemp9 = fSlow23 * (0.19190045f * fRec18[1] + 0.09595022f * (fRec18[0] + fRec18[2]));
			float fTemp10 = std::max<float>(0.0f, std::min<float>(1.0f, fTemp9)) + tanhf(std::min<float>(0.0f, fTemp9)) + tanhf(std::max<float>(1.0f, fTemp9) + -1.0f);
			fVec2[0] = fTemp10;
			fRec17[0] = 1.5f * (fConst17 * fTemp10 + fConst18 * fVec2[1]) - fConst16 * fRec17[1];
			float fTemp11 = std::max<float>(-0.7f, std::min<float>(0.7f, std::max<float>(0.1f, fRec17[0]) + std::min<float>(-0.1f, fRec17[0])));
			fVec3[0] = fTemp11;
			fRec16[0] = fConst21 * (fTemp11 + fVec3[1] - fConst20 * fRec16[1]);
			fRec15[0] = fConst27 * fRec16[1] + fConst26 * (fConst23 * fRec16[0] - fConst24 * fRec15[1]);
			fRec14[0] = fRec15[0] - (fSlow22 * fRec14[2] + fTemp8) / fSlow19;
			fRec13[0] = (fTemp8 + fRec14[0] * fSlow24 + fSlow21 * fRec14[2]) / fSlow19 - (fSlow14 * fRec13[2] + fTemp7) / fSlow11;
			fRec12[0] = (fTemp7 + fRec13[0] * fSlow25 + fSlow13 * fRec13[2]) / fSlow11 - (fSlow8 * fRec12[2] + fTemp6) / fSlow5;
			fRec11[0] = fSlow27 * ((fTemp6 + fRec12[0] * fSlow26 + fSlow7 * fRec12[2]) / fSlow5) + 0.9505005f * fRec11[1] - 0.2499908f * fRec11[2];
			fRec10[0] = 0.14974517f * fRec11[1] + 0.07487258f * (fRec11[0] + fRec11[2]) + 1.2180791f * fRec10[1] - 0.60187995f * fRec10[2];
			output1[i0] = FAUSTFLOAT(0.19190045f * fRec10[1] + 0.09595022f * (fRec10[0] + fRec10[2]));
			fRec9[2] = fRec9[1];
			fRec9[1] = fRec9[0];
			fRec8[2] = fRec8[1];
			fRec8[1] = fRec8[0];
			fVec0[1] = fVec0[0];
			fRec7[1] = fRec7[0];
			fVec1[1] = fVec1[0];
			fRec6[1] = fRec6[0];
			fRec5[1] = fRec5[0];
			fRec4[2] = fRec4[1];
			fRec4[1] = fRec4[0];
			fRec3[2] = fRec3[1];
			fRec3[1] = fRec3[0];
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
			fRec19[2] = fRec19[1];
			fRec19[1] = fRec19[0];
			fRec18[2] = fRec18[1];
			fRec18[1] = fRec18[0];
			fVec2[1] = fVec2[0];
			fRec17[1] = fRec17[0];
			fVec3[1] = fVec3[0];
			fRec16[1] = fRec16[0];
			fRec15[1] = fRec15[0];
			fRec14[2] = fRec14[1];
			fRec14[1] = fRec14[0];
			fRec13[2] = fRec13[1];
			fRec13[1] = fRec13[0];
			fRec12[2] = fRec12[1];
			fRec12[1] = fRec12[0];
			fRec11[2] = fRec11[1];
			fRec11[1] = fRec11[0];
			fRec10[2] = fRec10[1];
			fRec10[1] = fRec10[0];
		}
	}

};

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/

// Factory API
dsp* createmydsp() { return new mydsp(); }

/******************* END minimal-effect.cpp ****************/

#endif
