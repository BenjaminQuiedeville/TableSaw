/* ------------------------------------------------------------
author: "Benjamin Quiedeville"
name: "TableSaw"
version: "0.0.1"
Code generated with Faust 2.60.3 (https://faust.grame.fr)
Compilation options: -a minimal-effect.cpp -lang cpp -nvi -ct 1 -es 1 -mcd 16 -single -ftz 0
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
	FAUSTFLOAT fHslider2;
	float fVec0[2];
	float fConst14;
	float fConst15;
	float fConst17;
	float fConst18;
	float fRec5[2];
	float fVec1[2];
	float fConst20;
	float fConst21;
	float fRec4[2];
	float fRec3[2];
	float fRec2[3];
	float fRec1[3];
	float fRec0[3];
	FAUSTFLOAT fHslider3;
	float fVec2[2];
	float fRec11[2];
	float fVec3[2];
	float fRec10[2];
	float fRec9[2];
	float fRec8[3];
	float fRec7[3];
	float fRec6[3];
	
 public:
	mydsp() {}

	void metadata(Meta* m) { 
		m->declare("author", "Benjamin Quiedeville");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/tabulateNd", "Copyright (C) 2023 Bart Brouns <bart@magnetophon.nl>");
		m->declare("basics.lib/version", "1.10.0");
		m->declare("compile_options", "-a minimal-effect.cpp -lang cpp -nvi -ct 1 -es 1 -mcd 16 -single -ftz 0");
		m->declare("description", "Boss HM2 Emulation");
		m->declare("filename", "tablesaw.dsp");
		m->declare("filter.lib/author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("filter.lib/copyright", "Julius O. Smith III");
		m->declare("filter.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.");
		m->declare("filter.lib/license", "STK-4.3");
		m->declare("filter.lib/name", "Faust Filter Library");
		m->declare("filter.lib/reference", "https://ccrma.stanford.edu/~jos/filters/");
		m->declare("filter.lib/version", "1.29");
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
		m->declare("maths.lib/version", "2.6.0");
		m->declare("music.lib/author", "GRAME");
		m->declare("music.lib/copyright", "GRAME");
		m->declare("music.lib/deprecated", "This library is deprecated and is not maintained anymore. It will be removed in August 2017.");
		m->declare("music.lib/license", "LGPL with exception");
		m->declare("music.lib/name", "Music Library");
		m->declare("music.lib/version", "1.0");
		m->declare("name", "TableSaw");
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
		fConst1 = 7853.9814f / (fConst0 * std::sin(6283.1855f / fConst0));
		float fConst2 = std::tan(3141.5928f / fConst0);
		fConst3 = 1.0f / fConst2;
		fConst4 = 2.0f * (1.0f - 1.0f / mydsp_faustpower2_f(fConst2));
		fConst5 = 11780.973f / (fConst0 * std::sin(9424.778f / fConst0));
		float fConst6 = std::tan(4712.389f / fConst0);
		fConst7 = 1.0f / fConst6;
		fConst8 = 2.0f * (1.0f - 1.0f / mydsp_faustpower2_f(fConst6));
		fConst9 = 628.31854f / (fConst0 * std::sin(502.65482f / fConst0));
		float fConst10 = std::tan(251.32741f / fConst0);
		fConst11 = 1.0f / fConst10;
		fConst12 = 2.0f * (1.0f - 1.0f / mydsp_faustpower2_f(fConst10));
		float fConst13 = std::tan(31.415926f / fConst0);
		fConst14 = 1.0f / fConst13;
		fConst15 = 1.0f - fConst14;
		float fConst16 = fConst14 + 1.0f;
		fConst17 = 1.0f / fConst16;
		fConst18 = 0.0f - 1.0f / (fConst13 * fConst16);
		float fConst19 = 1.0f / std::tan(31415.926f / fConst0);
		fConst20 = 1.0f - fConst19;
		fConst21 = 1.0f / (fConst19 + 1.0f);
	}
	
	void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(0.5f);
		fHslider1 = FAUSTFLOAT(0.5f);
		fHslider2 = FAUSTFLOAT(0.5f);
		fHslider3 = FAUSTFLOAT(0.5f);
	}
	
	void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fVec0[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec5[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fVec1[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec4[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fRec3[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 3; l5 = l5 + 1) {
			fRec2[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 3; l6 = l6 + 1) {
			fRec1[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 3; l7 = l7 + 1) {
			fRec0[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			fVec2[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 2; l9 = l9 + 1) {
			fRec11[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 2; l10 = l10 + 1) {
			fVec3[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 2; l11 = l11 + 1) {
			fRec10[l11] = 0.0f;
		}
		for (int l12 = 0; l12 < 2; l12 = l12 + 1) {
			fRec9[l12] = 0.0f;
		}
		for (int l13 = 0; l13 < 3; l13 = l13 + 1) {
			fRec8[l13] = 0.0f;
		}
		for (int l14 = 0; l14 < 3; l14 = l14 + 1) {
			fRec7[l14] = 0.0f;
		}
		for (int l15 = 0; l15 < 3; l15 = l15 + 1) {
			fRec6[l15] = 0.0f;
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
		float fSlow0 = 1e+01f * float(fHslider0);
		int iSlow1 = fSlow0 > 0.0f;
		float fSlow2 = std::pow(1e+01f, 0.05f * std::fabs(fSlow0));
		float fSlow3 = fConst1 * fSlow2;
		float fSlow4 = ((iSlow1) ? fConst1 : fSlow3);
		float fSlow5 = fConst3 * (fConst3 + fSlow4) + 1.0f;
		float fSlow6 = ((iSlow1) ? fSlow3 : fConst1);
		float fSlow7 = fConst3 * (fConst3 - fSlow6) + 1.0f;
		float fSlow8 = fConst3 * (fConst3 - fSlow4) + 1.0f;
		float fSlow9 = fConst5 * fSlow2;
		float fSlow10 = ((iSlow1) ? fConst5 : fSlow9);
		float fSlow11 = fConst7 * (fConst7 + fSlow10) + 1.0f;
		float fSlow12 = ((iSlow1) ? fSlow9 : fConst5);
		float fSlow13 = fConst7 * (fConst7 - fSlow12) + 1.0f;
		float fSlow14 = 1.0f - fConst7 * (fSlow10 - fConst7);
		float fSlow15 = 2e+01f * float(fHslider1);
		int iSlow16 = fSlow15 > 0.0f;
		float fSlow17 = fConst9 * std::pow(1e+01f, 0.05f * std::fabs(fSlow15));
		float fSlow18 = ((iSlow16) ? fConst9 : fSlow17);
		float fSlow19 = fConst11 * (fConst11 + fSlow18) + 1.0f;
		float fSlow20 = ((iSlow16) ? fSlow17 : fConst9);
		float fSlow21 = fConst11 * (fConst11 - fSlow20) + 1.0f;
		float fSlow22 = 1.0f - fConst11 * (fSlow18 - fConst11);
		float fSlow23 = std::pow(1e+01f, 1.5f * float(fHslider2));
		float fSlow24 = fConst11 * (fConst11 + fSlow20) + 1.0f;
		float fSlow25 = fConst7 * (fConst7 + fSlow12) + 1.0f;
		float fSlow26 = fConst3 * (fConst3 + fSlow6) + 1.0f;
		float fSlow27 = float(fHslider3);
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			float fTemp0 = fConst4 * fRec0[1];
			float fTemp1 = fConst8 * fRec1[1];
			float fTemp2 = fConst12 * fRec2[1];
			float fTemp3 = fSlow23 * float(input0[i0]);
			float fTemp4 = tanhf(std::min<float>(0.0f, fTemp3)) + std::max<float>(0.0f, std::min<float>(1.0f, fTemp3)) + tanhf(std::max<float>(1.0f, fTemp3) + -1.0f);
			fVec0[0] = fTemp4;
			fRec5[0] = fConst18 * fVec0[1] - fConst17 * (fConst15 * fRec5[1] - fConst14 * fTemp4);
			float fTemp5 = std::max<float>(-1.0f, std::min<float>(1.0f, std::max<float>(0.3f, fRec5[0]) + std::min<float>(-0.3f, fRec5[0])));
			fVec1[0] = fTemp5;
			fRec4[0] = 0.0f - fConst21 * (fConst20 * fRec4[1] - (fTemp5 + fVec1[1]));
			fRec3[0] = fConst18 * fRec4[1] - fConst17 * (fConst15 * fRec3[1] - fConst14 * fRec4[0]);
			fRec2[0] = fRec3[0] - (fRec2[2] * fSlow22 + fTemp2) / fSlow19;
			fRec1[0] = (fTemp2 + fRec2[0] * fSlow24 + fRec2[2] * fSlow21) / fSlow19 - (fRec1[2] * fSlow14 + fTemp1) / fSlow11;
			fRec0[0] = (fTemp1 + fRec1[0] * fSlow25 + fRec1[2] * fSlow13) / fSlow11 - (fRec0[2] * fSlow8 + fTemp0) / fSlow5;
			output0[i0] = FAUSTFLOAT(fSlow27 * ((fTemp0 + fRec0[0] * fSlow26 + fRec0[2] * fSlow7) / fSlow5));
			float fTemp6 = fConst4 * fRec6[1];
			float fTemp7 = fConst8 * fRec7[1];
			float fTemp8 = fConst12 * fRec8[1];
			float fTemp9 = fSlow23 * float(input1[i0]);
			float fTemp10 = tanhf(std::min<float>(0.0f, fTemp9)) + std::max<float>(0.0f, std::min<float>(1.0f, fTemp9)) + tanhf(std::max<float>(1.0f, fTemp9) + -1.0f);
			fVec2[0] = fTemp10;
			fRec11[0] = fConst18 * fVec2[1] + fConst17 * (fConst14 * fTemp10 - fConst15 * fRec11[1]);
			float fTemp11 = std::max<float>(-1.0f, std::min<float>(1.0f, std::max<float>(0.3f, fRec11[0]) + std::min<float>(-0.3f, fRec11[0])));
			fVec3[0] = fTemp11;
			fRec10[0] = 0.0f - fConst21 * (fConst20 * fRec10[1] - (fTemp11 + fVec3[1]));
			fRec9[0] = fConst18 * fRec10[1] - fConst17 * (fConst15 * fRec9[1] - fConst14 * fRec10[0]);
			fRec8[0] = fRec9[0] - (fSlow22 * fRec8[2] + fTemp8) / fSlow19;
			fRec7[0] = (fTemp8 + fRec8[0] * fSlow24 + fSlow21 * fRec8[2]) / fSlow19 - (fSlow14 * fRec7[2] + fTemp7) / fSlow11;
			fRec6[0] = (fTemp7 + fRec7[0] * fSlow25 + fSlow13 * fRec7[2]) / fSlow11 - (fSlow8 * fRec6[2] + fTemp6) / fSlow5;
			output1[i0] = FAUSTFLOAT(fSlow27 * ((fTemp6 + fRec6[0] * fSlow26 + fSlow7 * fRec6[2]) / fSlow5));
			fVec0[1] = fVec0[0];
			fRec5[1] = fRec5[0];
			fVec1[1] = fVec1[0];
			fRec4[1] = fRec4[0];
			fRec3[1] = fRec3[0];
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
			fVec2[1] = fVec2[0];
			fRec11[1] = fRec11[0];
			fVec3[1] = fVec3[0];
			fRec10[1] = fRec10[0];
			fRec9[1] = fRec9[0];
			fRec8[2] = fRec8[1];
			fRec8[1] = fRec8[0];
			fRec7[2] = fRec7[1];
			fRec7[1] = fRec7[0];
			fRec6[2] = fRec6[1];
			fRec6[1] = fRec6[0];
		}
	}

};

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/

// Factory API
dsp* createmydsp() { return new mydsp(); }

/******************* END minimal-effect.cpp ****************/

#endif
