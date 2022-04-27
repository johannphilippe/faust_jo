/* ------------------------------------------------------------
author: "Johann Philippe"
copyright: "(c) Johann Philippe 2022"
license: "MIT"
name: "polyphonic_detection"
version: "1.0"
Code generated with Faust 2.39.10 (https://faust.grame.fr)
Compilation options: -a /usr/local/share/faust/juce/juce-plugin.cpp -lang cpp -i -scn base_dsp -es 1 -mcd 16 -uim -single -ftz 0
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2016 GRAME, Centre National de Creation Musicale
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
#include <assert.h>

#if JUCE_WINDOWS
#define JUCE_CORE_INCLUDE_NATIVE_HEADERS 1
#endif

#include "JuceLibraryCode/JuceHeader.h"

/************************** BEGIN MapUI.h ******************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ***********************************************************************/

#ifndef FAUST_MAPUI_H
#define FAUST_MAPUI_H

#include <vector>
#include <map>
#include <string>
#include <stdio.h>

/************************** BEGIN UI.h *****************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ********************************************************************/

#ifndef __UI_H__
#define __UI_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

/*******************************************************************************
 * UI : Faust DSP User Interface
 * User Interface as expected by the buildUserInterface() method of a DSP.
 * This abstract class contains only the method that the Faust compiler can
 * generate to describe a DSP user interface.
 ******************************************************************************/

struct Soundfile;

template <typename REAL>
struct UIReal
{
    UIReal() {}
    virtual ~UIReal() {}
    
    // -- widget's layouts
    
    virtual void openTabBox(const char* label) = 0;
    virtual void openHorizontalBox(const char* label) = 0;
    virtual void openVerticalBox(const char* label) = 0;
    virtual void closeBox() = 0;
    
    // -- active widgets
    
    virtual void addButton(const char* label, REAL* zone) = 0;
    virtual void addCheckButton(const char* label, REAL* zone) = 0;
    virtual void addVerticalSlider(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step) = 0;
    virtual void addHorizontalSlider(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step) = 0;
    virtual void addNumEntry(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step) = 0;
    
    // -- passive widgets
    
    virtual void addHorizontalBargraph(const char* label, REAL* zone, REAL min, REAL max) = 0;
    virtual void addVerticalBargraph(const char* label, REAL* zone, REAL min, REAL max) = 0;
    
    // -- soundfiles
    
    virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) = 0;
    
    // -- metadata declarations
    
    virtual void declare(REAL* zone, const char* key, const char* val) {}
    
    // To be used by LLVM client
    virtual int sizeOfFAUSTFLOAT() { return sizeof(FAUSTFLOAT); }
};

struct UI : public UIReal<FAUSTFLOAT>
{
    UI() {}
    virtual ~UI() {}
};

#endif
/**************************  END  UI.h **************************/
/************************** BEGIN PathBuilder.h **************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef FAUST_PATHBUILDER_H
#define FAUST_PATHBUILDER_H

#include <vector>
#include <string>
#include <algorithm>

/*******************************************************************************
 * PathBuilder : Faust User Interface
 * Helper class to build complete hierarchical path for UI items.
 ******************************************************************************/

class PathBuilder
{

    protected:
    
        std::vector<std::string> fControlsLevel;
       
    public:
    
        PathBuilder() {}
        virtual ~PathBuilder() {}
    
        std::string replaceCharList(std::string str, const std::vector<char>& ch1, char ch2)
        {
            std::vector<char>::const_iterator beg = ch1.begin();
            std::vector<char>::const_iterator end = ch1.end();
            for (size_t i = 0; i < str.length(); ++i) {
                if (std::find(beg, end, str[i]) != end) {
                    str[i] = ch2;
                }
            }
            return str;
        }
    
        std::string buildPath(const std::string& label) 
        {
            std::string res = "/";
            for (size_t i = 0; i < fControlsLevel.size(); i++) {
                res += fControlsLevel[i];
                res += "/";
            }
            res += label;
            std::vector<char> rep = {' ', '#', '*', ',', '/', '?', '[', ']', '{', '}', '(', ')'};
            replaceCharList(res, rep, '_');
            return res;
        }
    
        void pushLabel(const std::string& label) { fControlsLevel.push_back(label); }
        void popLabel() { fControlsLevel.pop_back(); }
    
};

#endif  // FAUST_PATHBUILDER_H
/**************************  END  PathBuilder.h **************************/

/*******************************************************************************
 * MapUI : Faust User Interface.
 *
 * This class creates:
 * - a map of 'labels' and zones for each UI item.
 * - a map of complete hierarchical 'paths' and zones for each UI item.
 *
 * Simple 'labels' and complete 'paths' (to fully discriminate between possible same
 * 'labels' at different location in the UI hierachy) can be used to access a given parameter.
 ******************************************************************************/

class MapUI : public UI, public PathBuilder
{
    
    protected:
    
        // Complete path map
        std::map<std::string, FAUSTFLOAT*> fPathZoneMap;
    
        // Label zone map
        std::map<std::string, FAUSTFLOAT*> fLabelZoneMap;
    
    public:
        
        MapUI() {}
        virtual ~MapUI() {}
        
        // -- widget's layouts
        void openTabBox(const char* label)
        {
            pushLabel(label);
        }
        void openHorizontalBox(const char* label)
        {
            pushLabel(label);
        }
        void openVerticalBox(const char* label)
        {
            pushLabel(label);
        }
        void closeBox()
        {
            popLabel();
        }
        
        // -- active widgets
        void addButton(const char* label, FAUSTFLOAT* zone)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        
        // -- passive widgets
        void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
    
        // -- soundfiles
        virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) {}
        
        // -- metadata declarations
        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {}
        
        // setParamValue/getParamValue
        void setParamValue(const std::string& path, FAUSTFLOAT value)
        {
            if (fPathZoneMap.find(path) != fPathZoneMap.end()) {
                *fPathZoneMap[path] = value;
            } else if (fLabelZoneMap.find(path) != fLabelZoneMap.end()) {
                *fLabelZoneMap[path] = value;
            } else {
                fprintf(stderr, "ERROR : setParamValue '%s' not found\n", path.c_str());
            }
        }
        
        FAUSTFLOAT getParamValue(const std::string& path)
        {
            if (fPathZoneMap.find(path) != fPathZoneMap.end()) {
                return *fPathZoneMap[path];
            } else if (fLabelZoneMap.find(path) != fLabelZoneMap.end()) {
                return *fLabelZoneMap[path];
            } else {
                fprintf(stderr, "ERROR : getParamValue '%s' not found\n", path.c_str());
                return 0;
            }
        }
    
        // map access 
        std::map<std::string, FAUSTFLOAT*>& getMap() { return fPathZoneMap; }
        
        int getParamsCount() { return int(fPathZoneMap.size()); }
        
        std::string getParamAddress(int index)
        {
            if (index < 0 || index > int(fPathZoneMap.size())) {
                return "";
            } else {
                auto it = fPathZoneMap.begin();
                while (index-- > 0 && it++ != fPathZoneMap.end()) {}
                return it->first;
            }
        }
        
        const char* getParamAddress1(int index)
        {
            if (index < 0 || index > int(fPathZoneMap.size())) {
                return nullptr;
            } else {
                auto it = fPathZoneMap.begin();
                while (index-- > 0 && it++ != fPathZoneMap.end()) {}
                return it->first.c_str();
            }
        }
    
        std::string getParamAddress(FAUSTFLOAT* zone)
        {
            for (const auto& it : fPathZoneMap) {
                if (it.second == zone) return it.first;
            }
            return "";
        }
    
        FAUSTFLOAT* getParamZone(const std::string& str)
        {
            if (fPathZoneMap.find(str) != fPathZoneMap.end()) {
                return fPathZoneMap[str];
            } else if (fLabelZoneMap.find(str) != fLabelZoneMap.end()) {
                return fLabelZoneMap[str];
            }
            return nullptr;
        }
    
        FAUSTFLOAT* getParamZone(int index)
        {
            if (index < 0 || index > int(fPathZoneMap.size())) {
                return nullptr;
            } else {
                auto it = fPathZoneMap.begin();
                while (index-- > 0 && it++ != fPathZoneMap.end()) {}
                return it->second;
            }
        }
    
        static bool endsWith(const std::string& str, const std::string& end)
        {
            size_t l1 = str.length();
            size_t l2 = end.length();
            return (l1 >= l2) && (0 == str.compare(l1 - l2, l2, end));
        }
};

#endif // FAUST_MAPUI_H
/**************************  END  MapUI.h **************************/
/************************** BEGIN base_dsp-adapter.h *************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __dsp_adapter__
#define __dsp_adapter__

#ifndef _WIN32
#include <alloca.h>
#endif
#include <string.h>
#include <cmath>
#include <assert.h>
#include <stdio.h>

/************************** BEGIN base_dsp.h ********************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __dsp__
#define __dsp__

#include <string>
#include <vector>

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

struct UI;
struct Meta;

/**
 * DSP memory manager.
 */

struct dsp_memory_manager {
    
    virtual ~dsp_memory_manager() {}
    
    /**
     * Inform the Memory Manager with the number of expected memory zones.
     * @param count - the number of expected memory zones
     */
    virtual void begin(size_t count) {}
    
    /**
     * Give the Memory Manager information on a given memory zone.
     * @param size - the size in bytes of the memory zone
     * @param reads - the number of Read access to the zone used to compute one frame
     * @param writes - the number of Write access to the zone used to compute one frame
     */
    virtual void info(size_t size, size_t reads, size_t writes) {}
    
    /**
     * Inform the Memory Manager that all memory zones have been described,
     * to possibly start a 'compute the best allocation strategy' step.
     */
    virtual void end() {}
    
    /**
     * Allocate a memory zone.
     * @param size - the memory zone size in bytes
     */
    virtual void* allocate(size_t size) = 0;
    
    /**
     * Destroy a memory zone.
     * @param ptr - the memory zone pointer to be deallocated
     */
    virtual void destroy(void* ptr) = 0;
    
};

/**
* Signal processor definition.
*/

class base_dsp {

    public:

        base_dsp() {}
        virtual ~base_dsp() {}

        /* Return instance number of audio inputs */
        virtual int getNumInputs() = 0;
    
        /* Return instance number of audio outputs */
        virtual int getNumOutputs() = 0;
    
        /**
         * Trigger the ui_interface parameter with instance specific calls
         * to 'openTabBox', 'addButton', 'addVerticalSlider'... in order to build the UI.
         *
         * @param ui_interface - the user interface builder
         */
        virtual void buildUserInterface(UI* ui_interface) = 0;
    
        /* Return the sample rate currently used by the instance */
        virtual int getSampleRate() = 0;
    
        /**
         * Global init, calls the following methods:
         * - static class 'classInit': static tables initialization
         * - 'instanceInit': constants and instance state initialization
         *
         * @param sample_rate - the sampling rate in Hz
         */
        virtual void init(int sample_rate) = 0;

        /**
         * Init instance state
         *
         * @param sample_rate - the sampling rate in Hz
         */
        virtual void instanceInit(int sample_rate) = 0;
    
        /**
         * Init instance constant state
         *
         * @param sample_rate - the sampling rate in Hz
         */
        virtual void instanceConstants(int sample_rate) = 0;
    
        /* Init default control parameters values */
        virtual void instanceResetUserInterface() = 0;
    
        /* Init instance state (like delay lines...) but keep the control parameter values */
        virtual void instanceClear() = 0;
 
        /**
         * Return a clone of the instance.
         *
         * @return a copy of the instance on success, otherwise a null pointer.
         */
        virtual base_dsp* clone() = 0;
    
        /**
         * Trigger the Meta* parameter with instance specific calls to 'declare' (key, value) metadata.
         *
         * @param m - the Meta* meta user
         */
        virtual void metadata(Meta* m) = 0;
    
        /**
         * DSP instance computation, to be called with successive in/out audio buffers.
         *
         * @param count - the number of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, double or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, double or quad)
         *
         */
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) = 0;
    
        /**
         * DSP instance computation: alternative method to be used by subclasses.
         *
         * @param date_usec - the timestamp in microsec given by audio driver.
         * @param count - the number of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (either float, double or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (either float, double or quad)
         *
         */
        virtual void compute(double /*date_usec*/, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }
       
};

/**
 * Generic DSP decorator.
 */

class decorator_dsp : public base_dsp {

    protected:

        base_dsp* fDSP;

    public:

        decorator_dsp(base_dsp* base_dsp = nullptr):fDSP(base_dsp) {}
        virtual ~decorator_dsp() { delete fDSP; }

        virtual int getNumInputs() { return fDSP->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP->getNumOutputs(); }
        virtual void buildUserInterface(UI* ui_interface) { fDSP->buildUserInterface(ui_interface); }
        virtual int getSampleRate() { return fDSP->getSampleRate(); }
        virtual void init(int sample_rate) { fDSP->init(sample_rate); }
        virtual void instanceInit(int sample_rate) { fDSP->instanceInit(sample_rate); }
        virtual void instanceConstants(int sample_rate) { fDSP->instanceConstants(sample_rate); }
        virtual void instanceResetUserInterface() { fDSP->instanceResetUserInterface(); }
        virtual void instanceClear() { fDSP->instanceClear(); }
        virtual decorator_dsp* clone() { return new decorator_dsp(fDSP->clone()); }
        virtual void metadata(Meta* m) { fDSP->metadata(m); }
        // Beware: subclasses usually have to overload the two 'compute' methods
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(count, inputs, outputs); }
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(date_usec, count, inputs, outputs); }
    
};

/**
 * DSP factory class, used with LLVM and Interpreter backends
 * to create DSP instances from a compiled DSP program.
 */

class dsp_factory {
    
    protected:
    
        // So that to force sub-classes to use deleteDSPFactory(dsp_factory* factory);
        virtual ~dsp_factory() {}
    
    public:
    
        virtual std::string getName() = 0;
        virtual std::string getSHAKey() = 0;
        virtual std::string getDSPCode() = 0;
        virtual std::string getCompileOptions() = 0;
        virtual std::vector<std::string> getLibraryList() = 0;
        virtual std::vector<std::string> getIncludePathnames() = 0;
    
        virtual base_dsp* createDSPInstance() = 0;
    
        virtual void setMemoryManager(dsp_memory_manager* manager) = 0;
        virtual dsp_memory_manager* getMemoryManager() = 0;
    
};

// Denormal handling

#if defined (__SSE__)
#include <xmmintrin.h>
#endif

class ScopedNoDenormals
{
    private:
    
        intptr_t fpsr;
        
        void setFpStatusRegister(intptr_t fpsr_aux) noexcept
        {
        #if defined (__arm64__) || defined (__aarch64__)
           asm volatile("msr fpcr, %0" : : "ri" (fpsr_aux));
        #elif defined (__SSE__)
            _mm_setcsr(static_cast<uint32_t>(fpsr_aux));
        #endif
        }
        
        void getFpStatusRegister() noexcept
        {
        #if defined (__arm64__) || defined (__aarch64__)
            asm volatile("mrs %0, fpcr" : "=r" (fpsr));
        #elif defined ( __SSE__)
            fpsr = static_cast<intptr_t>(_mm_getcsr());
        #endif
        }
    
    public:
    
        ScopedNoDenormals() noexcept
        {
        #if defined (__arm64__) || defined (__aarch64__)
            intptr_t mask = (1 << 24 /* FZ */);
        #else
            #if defined(__SSE__)
            #if defined(__SSE2__)
                intptr_t mask = 0x8040;
            #else
                intptr_t mask = 0x8000;
            #endif
            #else
                intptr_t mask = 0x0000;
            #endif
        #endif
            getFpStatusRegister();
            setFpStatusRegister(fpsr | mask);
        }
        
        ~ScopedNoDenormals() noexcept
        {
            setFpStatusRegister(fpsr);
        }

};

#define AVOIDDENORMALS ScopedNoDenormals();

#endif

/************************** END base_dsp.h **************************/

// Adapts a DSP for a different number of inputs/outputs
class dsp_adapter : public decorator_dsp {
    
    private:
    
        FAUSTFLOAT** fAdaptedInputs;
        FAUSTFLOAT** fAdaptedOutputs;
        int fHWInputs;
        int fHWOutputs;
        int fBufferSize;
    
        void adaptBuffers(FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            for (int i = 0; i < fHWInputs; i++) {
                fAdaptedInputs[i] = inputs[i];
            }
            for (int i = 0; i < fHWOutputs; i++) {
                fAdaptedOutputs[i] = outputs[i];
            }
        }
    
    public:
    
        dsp_adapter(base_dsp* base_dsp, int hw_inputs, int hw_outputs, int buffer_size):decorator_dsp(base_dsp)
        {
            fHWInputs = hw_inputs;
            fHWOutputs = hw_outputs;
            fBufferSize = buffer_size;
            
            fAdaptedInputs = new FAUSTFLOAT*[base_dsp->getNumInputs()];
            for (int i = 0; i < base_dsp->getNumInputs() - fHWInputs; i++) {
                fAdaptedInputs[i + fHWInputs] = new FAUSTFLOAT[buffer_size];
                memset(fAdaptedInputs[i + fHWInputs], 0, sizeof(FAUSTFLOAT) * buffer_size);
            }
            
            fAdaptedOutputs = new FAUSTFLOAT*[base_dsp->getNumOutputs()];
            for (int i = 0; i < base_dsp->getNumOutputs() - fHWOutputs; i++) {
                fAdaptedOutputs[i + fHWOutputs] = new FAUSTFLOAT[buffer_size];
                memset(fAdaptedOutputs[i + fHWOutputs], 0, sizeof(FAUSTFLOAT) * buffer_size);
            }
        }
    
        virtual ~dsp_adapter()
        {
            for (int i = 0; i < fDSP->getNumInputs() - fHWInputs; i++) {
                delete [] fAdaptedInputs[i + fHWInputs];
            }
            delete [] fAdaptedInputs;
            
            for (int i = 0; i < fDSP->getNumOutputs() - fHWOutputs; i++) {
                delete [] fAdaptedOutputs[i + fHWOutputs];
            }
            delete [] fAdaptedOutputs;
        }
    
        virtual int getNumInputs() { return fHWInputs; }
        virtual int getNumOutputs() { return fHWOutputs; }
    
        virtual dsp_adapter* clone() { return new dsp_adapter(fDSP->clone(), fHWInputs, fHWOutputs, fBufferSize); }
    
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            adaptBuffers(inputs, outputs);
            fDSP->compute(date_usec, count, fAdaptedInputs, fAdaptedOutputs);
        }
    
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            adaptBuffers(inputs, outputs);
            fDSP->compute(count, fAdaptedInputs, fAdaptedOutputs);
        }
};

// Adapts a DSP for a different sample size
template <typename REAL_INT, typename REAL_EXT>
class dsp_sample_adapter : public decorator_dsp {
    
    private:
    
        REAL_INT** fAdaptedInputs;
        REAL_INT** fAdaptedOutputs;
    
        void adaptInputBuffers(int count, FAUSTFLOAT** inputs)
        {
            for (int chan = 0; chan < fDSP->getNumInputs(); chan++) {
                for (int frame = 0; frame < count; frame++) {
                    fAdaptedInputs[chan][frame] = REAL_INT(reinterpret_cast<REAL_EXT**>(inputs)[chan][frame]);
                }
            }
        }
    
        void adaptOutputsBuffers(int count, FAUSTFLOAT** outputs)
        {
            for (int chan = 0; chan < fDSP->getNumOutputs(); chan++) {
                for (int frame = 0; frame < count; frame++) {
                    reinterpret_cast<REAL_EXT**>(outputs)[chan][frame] = REAL_EXT(fAdaptedOutputs[chan][frame]);
                }
            }
        }
    
    public:
    
        dsp_sample_adapter(base_dsp* base_dsp):decorator_dsp(base_dsp)
        {
            fAdaptedInputs = new REAL_INT*[base_dsp->getNumInputs()];
            for (int i = 0; i < base_dsp->getNumInputs(); i++) {
                fAdaptedInputs[i] = new REAL_INT[4096];
            }
            
            fAdaptedOutputs = new REAL_INT*[base_dsp->getNumOutputs()];
            for (int i = 0; i < base_dsp->getNumOutputs(); i++) {
                fAdaptedOutputs[i] = new REAL_INT[4096];
            }
        }
    
        virtual ~dsp_sample_adapter()
        {
            for (int i = 0; i < fDSP->getNumInputs(); i++) {
                delete [] fAdaptedInputs[i];
            }
            delete [] fAdaptedInputs;
            
            for (int i = 0; i < fDSP->getNumOutputs(); i++) {
                delete [] fAdaptedOutputs[i];
            }
            delete [] fAdaptedOutputs;
        }
    
        virtual dsp_sample_adapter* clone() { return new dsp_sample_adapter(fDSP->clone()); }
    
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            assert(count <= 4096);
            adaptInputBuffers(count, inputs);
            // DSP base class uses FAUSTFLOAT** type, so reinterpret_cast has to be used even if the real DSP uses REAL_INT
            fDSP->compute(count, reinterpret_cast<FAUSTFLOAT**>(fAdaptedInputs), reinterpret_cast<FAUSTFLOAT**>(fAdaptedOutputs));
            adaptOutputsBuffers(count, outputs);
        }
    
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            assert(count <= 4096);
            adaptInputBuffers(count, inputs);
            // DSP base class uses FAUSTFLOAT** type, so reinterpret_cast has to be used even if the real DSP uses REAL_INT
            fDSP->compute(date_usec, count, reinterpret_cast<FAUSTFLOAT**>(fAdaptedInputs), reinterpret_cast<FAUSTFLOAT**>(fAdaptedOutputs));
            adaptOutputsBuffers(count, outputs);
        }
};

// Template used to specialize double parameters expressed as NUM/DENOM
template <int NUM, int DENOM>
struct Double {
    static constexpr double value() { return double(NUM)/double(DENOM); }
};

// Base class for filters
template <class fVslider0, int fVslider1>
struct Filter {
    inline int getFactor() { return fVslider1; }
};

// Identity filter: copy input to output
template <class fVslider0, int fVslider1>
struct Identity : public Filter<fVslider0, fVslider1> {
    inline int getFactor() { return fVslider1; }
    
    inline void compute(int count, FAUSTFLOAT* input0, FAUSTFLOAT* output0)
    {
        memcpy(output0, input0, count * sizeof(FAUSTFLOAT));
    }
};

// Generated with process = fi.lowpass(3, ma.SR*hslider("FCFactor", 0.4, 0.4, 0.5, 0.01)/hslider("Factor", 2, 2, 8, 1));
template <class fVslider0, int fVslider1, typename REAL>
struct LowPass3 : public Filter<fVslider0, fVslider1> {
    
    REAL fVec0[2];
    REAL fRec1[2];
    REAL fRec0[3];
    
    inline REAL LowPass3_faustpower2_f(REAL value)
    {
        return (value * value);
    }
    
    LowPass3()
    {
        for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
            fVec0[l0] = 0.0;
        }
        for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
            fRec1[l1] = 0.0;
        }
        for (int l2 = 0; (l2 < 3); l2 = (l2 + 1)) {
            fRec0[l2] = 0.0;
        }
    }
    
    inline void compute(int count, FAUSTFLOAT* input0, FAUSTFLOAT* output0)
    {
        // Computed at template specialization time
        REAL fSlow0 = std::tan((3.1415926535897931 * (REAL(fVslider0::value()) / REAL(fVslider1))));
        REAL fSlow1 = (1.0 / fSlow0);
        REAL fSlow2 = (1.0 / (((fSlow1 + 1.0000000000000002) / fSlow0) + 1.0));
        REAL fSlow3 = (1.0 / (fSlow1 + 1.0));
        REAL fSlow4 = (1.0 - fSlow1);
        REAL fSlow5 = (((fSlow1 + -1.0000000000000002) / fSlow0) + 1.0);
        REAL fSlow6 = (2.0 * (1.0 - (1.0 / LowPass3_faustpower2_f(fSlow0))));
        // Computed at runtime
        for (int i = 0; (i < count); i = (i + 1)) {
            REAL fTemp0 = REAL(input0[i]);
            fVec0[0] = fTemp0;
            fRec1[0] = (0.0 - (fSlow3 * ((fSlow4 * fRec1[1]) - (fTemp0 + fVec0[1]))));
            fRec0[0] = (fRec1[0] - (fSlow2 * ((fSlow5 * fRec0[2]) + (fSlow6 * fRec0[1]))));
            output0[i] = FAUSTFLOAT((fSlow2 * (fRec0[2] + (fRec0[0] + (2.0 * fRec0[1])))));
            fVec0[1] = fVec0[0];
            fRec1[1] = fRec1[0];
            fRec0[2] = fRec0[1];
            fRec0[1] = fRec0[0];
        }
    }
};

// Generated with process = fi.lowpass(4, ma.SR*hslider("FCFactor", 0.4, 0.4, 0.5, 0.01)/hslider("Factor", 2, 2, 8, 1));
template <class fVslider0, int fVslider1, typename REAL>
struct LowPass4 : public Filter<fVslider0, fVslider1> {
    
    REAL fRec1[3];
    REAL fRec0[3];
    
    inline REAL LowPass4_faustpower2_f(REAL value)
    {
        return (value * value);
    }
    
    LowPass4()
    {
        for (int l0 = 0; (l0 < 3); l0 = (l0 + 1)) {
            fRec1[l0] = 0.0f;
        }
        for (int l1 = 0; (l1 < 3); l1 = (l1 + 1)) {
            fRec0[l1] = 0.0f;
        }
    }
    
    inline void compute(int count, FAUSTFLOAT* input0, FAUSTFLOAT* output0)
    {
        // Computed at template specialization time
        REAL fSlow0 = std::tan((3.1415926535897931 * (REAL(fVslider0::value()) / REAL(fVslider1))));
        REAL fSlow1 = (1.0 / fSlow0);
        REAL fSlow2 = (1.0 / (((fSlow1 + 0.76536686473017945) / fSlow0) + 1.0));
        REAL fSlow3 = (1.0 / (((fSlow1 + 1.8477590650225735) / fSlow0) + 1.0));
        REAL fSlow4 = (((fSlow1 + -1.8477590650225735) / fSlow0) + 1.0);
        REAL fSlow5 = (2.0 * (1.0 - (1.0 / LowPass4_faustpower2_f(fSlow0))));
        REAL fSlow6 = (((fSlow1 + -0.76536686473017945) / fSlow0) + 1.0);
        // Computed at runtime
        for (int i = 0; (i < count); i = (i + 1)) {
            fRec1[0] = (REAL(input0[i]) - (fSlow3 * ((fSlow4 * fRec1[2]) + (fSlow5 * fRec1[1]))));
            fRec0[0] = ((fSlow3 * (fRec1[2] + (fRec1[0] + (2.0 * fRec1[1])))) - (fSlow2 * ((fSlow6 * fRec0[2]) + (fSlow5 * fRec0[1]))));
            output0[i] = FAUSTFLOAT((fSlow2 * (fRec0[2] + (fRec0[0] + (2.0 * fRec0[1])))));
            fRec1[2] = fRec1[1];
            fRec1[1] = fRec1[0];
            fRec0[2] = fRec0[1];
            fRec0[1] = fRec0[0];
        }
    }
};

// Generated with process = fi.lowpass3e(ma.SR*hslider("FCFactor", 0.4, 0.4, 0.5, 0.01)/hslider("Factor", 2, 2, 8, 1));
template <class fVslider0, int fVslider1, typename REAL>
struct LowPass3e : public Filter<fVslider0, fVslider1> {
    
    REAL fRec1[3];
    REAL fVec0[2];
    REAL fRec0[2];
    
    inline REAL LowPass3e_faustpower2_f(REAL value)
    {
        return (value * value);
    }
    
    LowPass3e()
    {
        for (int l0 = 0; (l0 < 3); l0 = (l0 + 1)) {
            fRec1[l0] = 0.0;
        }
        for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
            fVec0[l1] = 0.0;
        }
        for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
            fRec0[l2] = 0.0;
        }
    }
    
    inline void compute(int count, FAUSTFLOAT* input0, FAUSTFLOAT* output0)
    {
        // Computed at template specialization time
        REAL fSlow0 = std::tan((3.1415926535897931 * (REAL(fVslider0::value()) / REAL(fVslider1))));
        REAL fSlow1 = (1.0 / fSlow0);
        REAL fSlow2 = (1.0 / (fSlow1 + 0.82244590899881598));
        REAL fSlow3 = (0.82244590899881598 - fSlow1);
        REAL fSlow4 = (1.0 / (((fSlow1 + 0.80263676416103003) / fSlow0) + 1.4122708937742039));
        REAL fSlow5 = LowPass3e_faustpower2_f(fSlow0);
        REAL fSlow6 = (0.019809144837788999 / fSlow5);
        REAL fSlow7 = (fSlow6 + 1.1615164189826961);
        REAL fSlow8 = (((fSlow1 + -0.80263676416103003) / fSlow0) + 1.4122708937742039);
        REAL fSlow9 = (2.0 * (1.4122708937742039 - (1.0 / fSlow5)));
        REAL fSlow10 = (2.0 * (1.1615164189826961 - fSlow6));
        // Computed at runtime
        for (int i = 0; (i < count); i = (i + 1)) {
            fRec1[0] = (REAL(input0[i]) - (fSlow4 * ((fSlow8 * fRec1[2]) + (fSlow9 * fRec1[1]))));
            REAL fTemp0 = (fSlow4 * (((fSlow7 * fRec1[0]) + (fSlow10 * fRec1[1])) + (fSlow7 * fRec1[2])));
            fVec0[0] = fTemp0;
            fRec0[0] = (0.0 - (fSlow2 * ((fSlow3 * fRec0[1]) - (fTemp0 + fVec0[1]))));
            output0[i] = FAUSTFLOAT(fRec0[0]);
            fRec1[2] = fRec1[1];
            fRec1[1] = fRec1[0];
            fVec0[1] = fVec0[0];
            fRec0[1] = fRec0[0];
        }
    }
};

// Generated with process = fi.lowpass6e(ma.SR*hslider("FCFactor", 0.4, 0.4, 0.5, 0.01)/hslider("Factor", 2, 2, 8, 1));
template <class fVslider0, int fVslider1, typename REAL>
struct LowPass6e : public Filter<fVslider0, fVslider1> {
    
    REAL fRec2[3];
    REAL fRec1[3];
    REAL fRec0[3];
    
    inline REAL LowPass6e_faustpower2_f(REAL value)
    {
        return (value * value);
    }
    
    LowPass6e()
    {
        for (int l0 = 0; (l0 < 3); l0 = (l0 + 1)) {
            fRec2[l0] = 0.0;
        }
        for (int l1 = 0; (l1 < 3); l1 = (l1 + 1)) {
            fRec1[l1] = 0.0;
        }
        for (int l2 = 0; (l2 < 3); l2 = (l2 + 1)) {
            fRec0[l2] = 0.0;
        }
    }
    
    inline void compute(int count, FAUSTFLOAT* input0, FAUSTFLOAT* output0)
    {
        // Computed at template specialization time
        REAL fSlow0 = std::tan((3.1415926535897931 * (REAL(fVslider0::value()) / REAL(fVslider1))));
        REAL fSlow1 = (1.0 / fSlow0);
        REAL fSlow2 = (1.0 / (((fSlow1 + 0.16840487111358901) / fSlow0) + 1.0693584077073119));
        REAL fSlow3 = LowPass6e_faustpower2_f(fSlow0);
        REAL fSlow4 = (1.0 / fSlow3);
        REAL fSlow5 = (fSlow4 + 53.536152954556727);
        REAL fSlow6 = (1.0 / (((fSlow1 + 0.51247864188914105) / fSlow0) + 0.68962136448467504));
        REAL fSlow7 = (fSlow4 + 7.6217312988706034);
        REAL fSlow8 = (1.0 / (((fSlow1 + 0.78241304682164503) / fSlow0) + 0.24529150870616001));
        REAL fSlow9 = (9.9999997054999994e-05 / fSlow3);
        REAL fSlow10 = (fSlow9 + 0.00043322720055500002);
        REAL fSlow11 = (((fSlow1 + -0.78241304682164503) / fSlow0) + 0.24529150870616001);
        REAL fSlow12 = (2.0 * (0.24529150870616001 - fSlow4));
        REAL fSlow13 = (2.0 * (0.00043322720055500002 - fSlow9));
        REAL fSlow14 = (((fSlow1 + -0.51247864188914105) / fSlow0) + 0.68962136448467504);
        REAL fSlow15 = (2.0 * (0.68962136448467504 - fSlow4));
        REAL fSlow16 = (2.0 * (7.6217312988706034 - fSlow4));
        REAL fSlow17 = (((fSlow1 + -0.16840487111358901) / fSlow0) + 1.0693584077073119);
        REAL fSlow18 = (2.0 * (1.0693584077073119 - fSlow4));
        REAL fSlow19 = (2.0 * (53.536152954556727 - fSlow4));
        // Computed at runtime
        for (int i = 0; (i < count); i = (i + 1)) {
            fRec2[0] = (REAL(input0[i]) - (fSlow8 * ((fSlow11 * fRec2[2]) + (fSlow12 * fRec2[1]))));
            fRec1[0] = ((fSlow8 * (((fSlow10 * fRec2[0]) + (fSlow13 * fRec2[1])) + (fSlow10 * fRec2[2]))) - (fSlow6 * ((fSlow14 * fRec1[2]) + (fSlow15 * fRec1[1]))));
            fRec0[0] = ((fSlow6 * (((fSlow7 * fRec1[0]) + (fSlow16 * fRec1[1])) + (fSlow7 * fRec1[2]))) - (fSlow2 * ((fSlow17 * fRec0[2]) + (fSlow18 * fRec0[1]))));
            output0[i] = FAUSTFLOAT((fSlow2 * (((fSlow5 * fRec0[0]) + (fSlow19 * fRec0[1])) + (fSlow5 * fRec0[2]))));
            fRec2[2] = fRec2[1];
            fRec2[1] = fRec2[0];
            fRec1[2] = fRec1[1];
            fRec1[1] = fRec1[0];
            fRec0[2] = fRec0[1];
            fRec0[1] = fRec0[0];
        }
    }
};

// A "si.bus(N)" like hard-coded class
struct dsp_bus : public base_dsp {
    
    int fChannels;
    int fSampleRate;
    
    dsp_bus(int channels):fChannels(channels), fSampleRate(-1)
    {}
    
    virtual int getNumInputs() { return fChannels; }
    virtual int getNumOutputs() { return fChannels; }
    
    virtual int getSampleRate() { return fSampleRate; }
    
    virtual void buildUserInterface(UI* ui_interface) {}
    virtual void init(int sample_rate)
    {
        //classInit(sample_rate);
        instanceInit(sample_rate);
    }
    
    virtual void instanceInit(int sample_rate)
    {
        fSampleRate = sample_rate;
        instanceConstants(sample_rate);
        instanceResetUserInterface();
        instanceClear();
    }
    
    virtual void instanceConstants(int sample_rate) {}
    virtual void instanceResetUserInterface() {}
    virtual void instanceClear() {}
    
    virtual base_dsp* clone() { return new dsp_bus(fChannels); }
    
    virtual void metadata(Meta* m) {}
    
    virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
    {
        for (int chan = 0; chan < fChannels; chan++) {
            memcpy(outputs[chan], inputs[chan], sizeof(FAUSTFLOAT) * count);
        }
    }
    
    virtual void compute(double /*date_usec*/, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
    {
        compute(count, inputs, outputs);
    }
    
};

// Base class for sample-rate adapter
template <typename FILTER>
class sr_sampler : public decorator_dsp {
    
    protected:
    
        std::vector<FILTER> fInputLowPass;
        std::vector<FILTER> fOutputLowPass;
    
        inline int getFactor() { return this->fOutputLowPass[0].getFactor(); }
    
    public:
    
        sr_sampler(base_dsp* base_dsp):decorator_dsp(base_dsp)
        {
            for (int chan = 0; chan < fDSP->getNumInputs(); chan++) {
                fInputLowPass.push_back(FILTER());
            }
            for (int chan = 0; chan < fDSP->getNumOutputs(); chan++) {
                fOutputLowPass.push_back(FILTER());
            }
        }
};

// Down sample-rate adapter
template <typename FILTER>
class dsp_down_sampler : public sr_sampler<FILTER> {
    
    public:
    
        dsp_down_sampler(base_dsp* base_dsp):sr_sampler<FILTER>(base_dsp)
        {}
    
        virtual void init(int sample_rate)
        {
            this->fDSP->init(sample_rate / this->getFactor());
        }
    
        virtual void instanceInit(int sample_rate)
        {
            this->fDSP->instanceInit(sample_rate / this->getFactor());
        }
    
        virtual void instanceConstants(int sample_rate)
        {
            this->fDSP->instanceConstants(sample_rate / this->getFactor());
        }
    
        virtual dsp_down_sampler* clone() { return new dsp_down_sampler(decorator_dsp::clone()); }
    
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            int real_count = count / this->getFactor();
            
            // Adapt inputs
            FAUSTFLOAT** fInputs = (FAUSTFLOAT**)alloca(this->fDSP->getNumInputs() * sizeof(FAUSTFLOAT*));
            for (int chan = 0; chan < this->fDSP->getNumInputs(); chan++) {
                // Lowpass filtering in place on 'inputs'
                this->fInputLowPass[chan].compute(count, inputs[chan], inputs[chan]);
                // Allocate fInputs with 'real_count' frames
                fInputs[chan] = (FAUSTFLOAT*)alloca(sizeof(FAUSTFLOAT) * real_count);
                // Decimate
                for (int frame = 0; frame < real_count; frame++) {
                    fInputs[chan][frame] = inputs[chan][frame * this->getFactor()];
                }
            }
            
            // Allocate fOutputs with 'real_count' frames
            FAUSTFLOAT** fOutputs = (FAUSTFLOAT**)alloca(this->fDSP->getNumOutputs() * sizeof(FAUSTFLOAT*));
            for (int chan = 0; chan < this->fDSP->getNumOutputs(); chan++) {
                fOutputs[chan] = (FAUSTFLOAT*)alloca(sizeof(FAUSTFLOAT) * real_count);
            }
            
            // Compute at lower rate
            this->fDSP->compute(real_count, fInputs, fOutputs);
            
            // Adapt outputs
            for (int chan = 0; chan < this->fDSP->getNumOutputs(); chan++) {
                // Puts zeros
                memset(outputs[chan], 0, sizeof(FAUSTFLOAT) * count);
                for (int frame = 0; frame < real_count; frame++) {
                    // Copy one sample every 'DownFactor'
                    // Apply volume
                    //outputs[chan][frame * this->getFactor()] = fOutputs[chan][frame] * this->getFactor();
                    outputs[chan][frame * this->getFactor()] = fOutputs[chan][frame];
                }
                // Lowpass filtering in place on 'outputs'
                this->fOutputLowPass[chan].compute(count, outputs[chan], outputs[chan]);
            }
        }
    
        virtual void compute(double /*date_usec*/, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }
};

// Up sample-rate adapter
template <typename FILTER>
class dsp_up_sampler : public sr_sampler<FILTER> {
    
    public:
    
        dsp_up_sampler(base_dsp* base_dsp):sr_sampler<FILTER>(base_dsp)
        {}
    
        virtual void init(int sample_rate)
        {
            this->fDSP->init(sample_rate * this->getFactor());
        }
    
        virtual void instanceInit(int sample_rate)
        {
            this->fDSP->instanceInit(sample_rate * this->getFactor());
        }
    
        virtual void instanceConstants(int sample_rate)
        {
            this->fDSP->instanceConstants(sample_rate * this->getFactor());
        }
    
        virtual dsp_up_sampler* clone() { return new dsp_up_sampler(decorator_dsp::clone()); }
    
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            int real_count = count * this->getFactor();
            
            // Adapt inputs
            FAUSTFLOAT** fInputs = (FAUSTFLOAT**)alloca(this->fDSP->getNumInputs() * sizeof(FAUSTFLOAT*));
            
            for (int chan = 0; chan < this->fDSP->getNumInputs(); chan++) {
                // Allocate fInputs with 'real_count' frames
                fInputs[chan] = (FAUSTFLOAT*)alloca(sizeof(FAUSTFLOAT) * real_count);
                // Puts zeros
                memset(fInputs[chan], 0, sizeof(FAUSTFLOAT) * real_count);
                for (int frame = 0; frame < count; frame++) {
                    // Copy one sample every 'UpFactor'
                    fInputs[chan][frame * this->getFactor()] = inputs[chan][frame];
                }
                // Lowpass filtering in place on 'fInputs'
                this->fInputLowPass[chan].compute(real_count, fInputs[chan], fInputs[chan]);
            }
            
            // Allocate fOutputs with 'real_count' frames
            FAUSTFLOAT** fOutputs = (FAUSTFLOAT**)alloca(this->fDSP->getNumOutputs() * sizeof(FAUSTFLOAT*));
            
            for (int chan = 0; chan < this->fDSP->getNumOutputs(); chan++) {
                fOutputs[chan] = (FAUSTFLOAT*)alloca(sizeof(FAUSTFLOAT) * real_count);
            }
            
            // Compute at upper rate
            this->fDSP->compute(real_count, fInputs, fOutputs);
            
            // Adapt outputs
            for (int chan = 0; chan < this->fDSP->getNumOutputs(); chan++) {
                // Lowpass filtering in place on 'fOutputs'
                this->fOutputLowPass[chan].compute(real_count, fOutputs[chan], fOutputs[chan]);
                // Decimate
                for (int frame = 0; frame < count; frame++) {
                    // Apply volume
                    //outputs[chan][frame] = fOutputs[chan][frame * this->getFactor()] * this->getFactor();
                    outputs[chan][frame] = fOutputs[chan][frame * this->getFactor()];
                }
            }
        }
    
        virtual void compute(double /*date_usec*/, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }
};

// Create a UP/DS + Filter adapted DSP
template <typename REAL>
base_dsp* createSRAdapter(base_dsp* DSP, int ds = 0, int us = 0, int filter = 0)
{
    if (ds > 0) {
        switch (filter) {
            case 0:
                if (ds == 2) {
                    return new dsp_down_sampler<Identity<Double<1,1>, 2>>(DSP);
                } else if (ds == 3) {
                    return new dsp_down_sampler<Identity<Double<1,1>, 3>>(DSP);
                } else if (ds == 4) {
                    return new dsp_down_sampler<Identity<Double<1,1>, 4>>(DSP);
                } else if (ds == 8) {
                    return new dsp_down_sampler<Identity<Double<1,1>, 8>>(DSP);
                } else if (ds == 16) {
                    return new dsp_down_sampler<Identity<Double<1,1>, 16>>(DSP);
                } else if (ds == 32) {
                    return new dsp_down_sampler<Identity<Double<1,1>, 32>>(DSP);
                } else {
                    fprintf(stderr, "ERROR : ds factor type must be in [2..32] range\n");
                    assert(false);
                    return nullptr;
                }
            case 1:
                if (ds == 2) {
                    return new dsp_down_sampler<LowPass3<Double<45,100>, 2, REAL>>(DSP);
                } else if (ds == 3) {
                    return new dsp_down_sampler<LowPass3<Double<45,100>, 3, REAL>>(DSP);
                } else if (ds == 4) {
                    return new dsp_down_sampler<LowPass3<Double<45,100>, 4, REAL>>(DSP);
                } else if (ds == 8) {
                    return new dsp_down_sampler<LowPass3<Double<45,100>, 8, REAL>>(DSP);
                } else if (ds == 16) {
                    return new dsp_down_sampler<LowPass3<Double<45,100>, 16, REAL>>(DSP);
                } else if (ds == 32) {
                    return new dsp_down_sampler<LowPass3<Double<45,100>, 32, REAL>>(DSP);
                } else {
                    fprintf(stderr, "ERROR : ds factor type must be in [2..32] range\n");
                    assert(false);
                    return nullptr;
                }
            case 2:
                if (ds == 2) {
                    return new dsp_down_sampler<LowPass4<Double<45,100>, 2, REAL>>(DSP);
                } else if (ds == 3) {
                    return new dsp_down_sampler<LowPass4<Double<45,100>, 3, REAL>>(DSP);
                } else if (ds == 4) {
                    return new dsp_down_sampler<LowPass4<Double<45,100>, 4, REAL>>(DSP);
                } else if (ds == 8) {
                    return new dsp_down_sampler<LowPass4<Double<45,100>, 8, REAL>>(DSP);
                } else if (ds == 16) {
                    return new dsp_down_sampler<LowPass4<Double<45,100>, 16, REAL>>(DSP);
                } else if (ds == 32) {
                    return new dsp_down_sampler<LowPass4<Double<45,100>, 32, REAL>>(DSP);
                } else {
                    fprintf(stderr, "ERROR : ds factor type must be in [2..32] range\n");
                    assert(false);
                    return nullptr;
                }
            case 3:
                if (ds == 2) {
                    return new dsp_down_sampler<LowPass3e<Double<45,100>, 2, REAL>>(DSP);
                } else if (ds == 3) {
                    return new dsp_down_sampler<LowPass3e<Double<45,100>, 3, REAL>>(DSP);
                } else if (ds == 4) {
                    return new dsp_down_sampler<LowPass3e<Double<45,100>, 4, REAL>>(DSP);
                } else if (ds == 8) {
                    return new dsp_down_sampler<LowPass3e<Double<45,100>, 8, REAL>>(DSP);
                } else if (ds == 16) {
                    return new dsp_down_sampler<LowPass3e<Double<45,100>, 16, REAL>>(DSP);
                } else if (ds == 32) {
                    return new dsp_down_sampler<LowPass3e<Double<45,100>, 32, REAL>>(DSP);
                } else {
                    fprintf(stderr, "ERROR : ds factor type must be in [2..32] range\n");
                    assert(false);
                    return nullptr;
                }
            case 4:
                if (ds == 2) {
                    return new dsp_down_sampler<LowPass6e<Double<45,100>, 2, REAL>>(DSP);
                } else if (ds == 3) {
                    return new dsp_down_sampler<LowPass6e<Double<45,100>, 3, REAL>>(DSP);
                } else if (ds == 4) {
                    return new dsp_down_sampler<LowPass6e<Double<45,100>, 4, REAL>>(DSP);
                } else if (ds == 8) {
                    return new dsp_down_sampler<LowPass6e<Double<45,100>, 8, REAL>>(DSP);
                } else if (ds == 16) {
                    return new dsp_down_sampler<LowPass6e<Double<45,100>, 16, REAL>>(DSP);
                } else if (ds == 32) {
                    return new dsp_down_sampler<LowPass6e<Double<45,100>, 32, REAL>>(DSP);
                } else {
                    fprintf(stderr, "ERROR : ds factor type must be in [2..32] range\n");
                    assert(false);
                    return nullptr;
                }
            default:
                fprintf(stderr, "ERROR : filter type must be in [0..4] range\n");
                assert(false);
                return nullptr;
        }
    } else if (us > 0) {
        
        switch (filter) {
            case 0:
                if (us == 2) {
                    return new dsp_up_sampler<Identity<Double<1,1>, 2>>(DSP);
                } else if (us == 3) {
                    return new dsp_up_sampler<Identity<Double<1,1>, 3>>(DSP);
                } else if (us == 4) {
                    return new dsp_up_sampler<Identity<Double<1,1>, 4>>(DSP);
                } else if (us == 8) {
                    return new dsp_up_sampler<Identity<Double<1,1>, 8>>(DSP);
                } else if (us == 16) {
                    return new dsp_up_sampler<Identity<Double<1,1>, 16>>(DSP);
                } else if (us == 32) {
                    return new dsp_up_sampler<Identity<Double<1,1>, 32>>(DSP);
                } else {
                    fprintf(stderr, "ERROR : us factor type must be in [2..32] range\n");
                    assert(false);
                    return nullptr;
                }
            case 1:
                if (us == 2) {
                    return new dsp_up_sampler<LowPass3<Double<45,100>, 2, REAL>>(DSP);
                } else if (us == 3) {
                    return new dsp_up_sampler<LowPass3<Double<45,100>, 3, REAL>>(DSP);
                } else if (us == 4) {
                    return new dsp_up_sampler<LowPass3<Double<45,100>, 4, REAL>>(DSP);
                } else if (us == 8) {
                    return new dsp_up_sampler<LowPass3<Double<45,100>, 8, REAL>>(DSP);
                } else if (us == 16) {
                    return new dsp_up_sampler<LowPass3<Double<45,100>, 16, REAL>>(DSP);
                } else if (us == 32) {
                    return new dsp_up_sampler<LowPass3<Double<45,100>, 32, REAL>>(DSP);
                } else {
                    fprintf(stderr, "ERROR : us factor type must be in [2..32] range\n");
                    assert(false);
                    return nullptr;
                }
            case 2:
                if (us == 2) {
                    return new dsp_up_sampler<LowPass4<Double<45,100>, 2, REAL>>(DSP);
                } else if (us == 3) {
                    return new dsp_up_sampler<LowPass4<Double<45,100>, 3, REAL>>(DSP);
                } else if (us == 4) {
                    return new dsp_up_sampler<LowPass4<Double<45,100>, 4, REAL>>(DSP);
                } else if (us == 8) {
                    return new dsp_up_sampler<LowPass4<Double<45,100>, 8, REAL>>(DSP);
                } else if (us == 16) {
                    return new dsp_up_sampler<LowPass4<Double<45,100>, 16, REAL>>(DSP);
                } else if (us == 32) {
                    return new dsp_up_sampler<LowPass4<Double<45,100>, 32, REAL>>(DSP);
                } else {
                    fprintf(stderr, "ERROR : us factor type must be in [2..32] range\n");
                    assert(false);
                    return nullptr;
                }
            case 3:
                if (us == 2) {
                    return new dsp_up_sampler<LowPass3e<Double<45,100>, 2, REAL>>(DSP);
                } else if (us == 3) {
                    return new dsp_up_sampler<LowPass3e<Double<45,100>, 3, REAL>>(DSP);
                } else if (us == 4) {
                    return new dsp_up_sampler<LowPass3e<Double<45,100>, 4, REAL>>(DSP);
                } else if (us == 8) {
                    return new dsp_up_sampler<LowPass3e<Double<45,100>, 8, REAL>>(DSP);
                } else if (us == 16) {
                    return new dsp_up_sampler<LowPass3e<Double<45,100>, 16, REAL>>(DSP);
                } else if (us == 32) {
                    return new dsp_up_sampler<LowPass3e<Double<45,100>, 32, REAL>>(DSP);
                } else {
                    fprintf(stderr, "ERROR : us factor type must be in [2..32] range\n");
                    assert(false);
                    return nullptr;
                }
            case 4:
                if (us == 2) {
                    return new dsp_up_sampler<LowPass6e<Double<45,100>, 2, REAL>>(DSP);
                } else if (us == 3) {
                    return new dsp_up_sampler<LowPass6e<Double<45,100>, 3, REAL>>(DSP);
                } else if (us == 4) {
                    return new dsp_up_sampler<LowPass6e<Double<45,100>, 4, REAL>>(DSP);
                } else if (us == 8) {
                    return new dsp_up_sampler<LowPass6e<Double<45,100>, 8, REAL>>(DSP);
                } else if (us == 16) {
                    return new dsp_up_sampler<LowPass6e<Double<45,100>, 16, REAL>>(DSP);
                } else if (us == 32) {
                    return new dsp_up_sampler<LowPass6e<Double<45,100>, 32, REAL>>(DSP);
                } else {
                    fprintf(stderr, "ERROR : us factor type must be in [2..32] range\n");
                    assert(false);
                    return nullptr;
                }
            default:
                fprintf(stderr, "ERROR : filter type must be in [0..4] range\n");
                assert(false);
                return nullptr;
        }
    } else {
        return DSP;
    }
}
    
#endif
/************************** END base_dsp-adapter.h **************************/
/************************** BEGIN MidiUI.h ****************************
FAUST Architecture File
Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
---------------------------------------------------------------------
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

EXCEPTION : As a special exception, you may create a larger work
that contains this FAUST architecture section and distribute
that work under terms of your choice, so long as this FAUST
architecture section is not modified.
************************************************************************/

#ifndef FAUST_MIDIUI_H
#define FAUST_MIDIUI_H

#include <vector>
#include <string>
#include <utility>
#include <cstdlib>
#include <cmath>

/************************** BEGIN meta.h *******************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __meta__
#define __meta__

/**
 The base class of Meta handler to be used in base_dsp::metadata(Meta* m) method to retrieve (key, value) metadata.
 */
struct Meta
{
    virtual ~Meta() {}
    virtual void declare(const char* key, const char* value) = 0;
};

#endif
/**************************  END  meta.h **************************/
/************************** BEGIN GUI.h **********************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 *************************************************************************/

#ifndef __GUI_H__
#define __GUI_H__

#include <list>
#include <map>
#include <vector>
#include <assert.h>

#ifdef _WIN32
# pragma warning (disable: 4100)
#else
# pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

/************************** BEGIN ValueConverter.h ********************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ********************************************************************/

#ifndef __ValueConverter__
#define __ValueConverter__

/***************************************************************************************
 ValueConverter.h
 (GRAME, Copyright 2015-2019)
 
 Set of conversion objects used to map user interface values (for example a gui slider
 delivering values between 0 and 1) to faust values (for example a vslider between
 20 and 20000) using a log scale.
 
 -- Utilities
 
 Range(lo,hi) : clip a value x between lo and hi
 Interpolator(lo,hi,v1,v2) : Maps a value x between lo and hi to a value y between v1 and v2
 Interpolator3pt(lo,mi,hi,v1,vm,v2) : Map values between lo mid hi to values between v1 vm v2
 
 -- Value Converters
 
 ValueConverter::ui2faust(x)
 ValueConverter::faust2ui(x)
 
 -- ValueConverters used for sliders depending of the scale
 
 LinearValueConverter(umin, umax, fmin, fmax)
 LinearValueConverter2(lo, mi, hi, v1, vm, v2) using 2 segments
 LogValueConverter(umin, umax, fmin, fmax)
 ExpValueConverter(umin, umax, fmin, fmax)
 
 -- ValueConverters used for accelerometers based on 3 points
 
 AccUpConverter(amin, amid, amax, fmin, fmid, fmax)        -- curve 0
 AccDownConverter(amin, amid, amax, fmin, fmid, fmax)      -- curve 1
 AccUpDownConverter(amin, amid, amax, fmin, fmid, fmax)    -- curve 2
 AccDownUpConverter(amin, amid, amax, fmin, fmid, fmax)    -- curve 3
 
 -- lists of ZoneControl are used to implement accelerometers metadata for each axes
 
 ZoneControl(zone, valueConverter) : a zone with an accelerometer data converter
 
 -- ZoneReader are used to implement screencolor metadata
 
 ZoneReader(zone, valueConverter) : a zone with a data converter

****************************************************************************************/

#include <float.h>
#include <algorithm>    // std::max
#include <cmath>
#include <vector>
#include <assert.h>

//--------------------------------------------------------------------------------------
// Interpolator(lo,hi,v1,v2)
// Maps a value x between lo and hi to a value y between v1 and v2
// y = v1 + (x-lo)/(hi-lo)*(v2-v1)
// y = v1 + (x-lo) * coef           with coef = (v2-v1)/(hi-lo)
// y = v1 + x*coef - lo*coef
// y = v1 - lo*coef + x*coef
// y = offset + x*coef              with offset = v1 - lo*coef
//--------------------------------------------------------------------------------------
class Interpolator
{
    private:

        //--------------------------------------------------------------------------------------
        // Range(lo,hi) clip a value between lo and hi
        //--------------------------------------------------------------------------------------
        struct Range
        {
            double fLo;
            double fHi;

            Range(double x, double y) : fLo(std::min<double>(x,y)), fHi(std::max<double>(x,y)) {}
            double operator()(double x) { return (x<fLo) ? fLo : (x>fHi) ? fHi : x; }
        };


        Range fRange;
        double fCoef;
        double fOffset;

    public:

        Interpolator(double lo, double hi, double v1, double v2) : fRange(lo,hi)
        {
            if (hi != lo) {
                // regular case
                fCoef = (v2-v1)/(hi-lo);
                fOffset = v1 - lo*fCoef;
            } else {
                // degenerate case, avoids division by zero
                fCoef = 0;
                fOffset = (v1+v2)/2;
            }
        }
        double operator()(double v)
        {
            double x = fRange(v);
            return  fOffset + x*fCoef;
        }

        void getLowHigh(double& amin, double& amax)
        {
            amin = fRange.fLo;
            amax = fRange.fHi;
        }
};

//--------------------------------------------------------------------------------------
// Interpolator3pt(lo,mi,hi,v1,vm,v2)
// Map values between lo mid hi to values between v1 vm v2
//--------------------------------------------------------------------------------------
class Interpolator3pt
{

    private:

        Interpolator fSegment1;
        Interpolator fSegment2;
        double fMid;

    public:

        Interpolator3pt(double lo, double mi, double hi, double v1, double vm, double v2) :
            fSegment1(lo, mi, v1, vm),
            fSegment2(mi, hi, vm, v2),
            fMid(mi) {}
        double operator()(double x) { return  (x < fMid) ? fSegment1(x) : fSegment2(x); }

        void getMappingValues(double& amin, double& amid, double& amax)
        {
            fSegment1.getLowHigh(amin, amid);
            fSegment2.getLowHigh(amid, amax);
        }
};

//--------------------------------------------------------------------------------------
// Abstract ValueConverter class. Converts values between UI and Faust representations
//--------------------------------------------------------------------------------------
class ValueConverter // Identity by default
{

    public:

        virtual ~ValueConverter() {}
        virtual double ui2faust(double x) { return x; };
        virtual double faust2ui(double x) { return x; };
};

//--------------------------------------------------------------------------------------
// A converter than can be updated
//--------------------------------------------------------------------------------------

class UpdatableValueConverter : public ValueConverter {
    
    protected:
        
        bool fActive;
        
    public:
        
        UpdatableValueConverter():fActive(true)
        {}
        virtual ~UpdatableValueConverter()
        {}
        
        virtual void setMappingValues(double amin, double amid, double amax, double min, double init, double max) = 0;
        virtual void getMappingValues(double& amin, double& amid, double& amax) = 0;
        
        void setActive(bool on_off) { fActive = on_off; }
        bool getActive() { return fActive; }
    
};

//--------------------------------------------------------------------------------------
// Linear conversion between ui and Faust values
//--------------------------------------------------------------------------------------
class LinearValueConverter : public ValueConverter
{
    
    private:
        
        Interpolator fUI2F;
        Interpolator fF2UI;
        
    public:
        
        LinearValueConverter(double umin, double umax, double fmin, double fmax) :
            fUI2F(umin,umax,fmin,fmax), fF2UI(fmin,fmax,umin,umax)
        {}
        
        LinearValueConverter() : fUI2F(0.,0.,0.,0.), fF2UI(0.,0.,0.,0.)
        {}
        virtual double ui2faust(double x) { return fUI2F(x); }
        virtual double faust2ui(double x) { return fF2UI(x); }
    
};

//--------------------------------------------------------------------------------------
// Two segments linear conversion between ui and Faust values
//--------------------------------------------------------------------------------------
class LinearValueConverter2 : public UpdatableValueConverter
{
    
    private:
    
        Interpolator3pt fUI2F;
        Interpolator3pt fF2UI;
        
    public:
    
        LinearValueConverter2(double amin, double amid, double amax, double min, double init, double max) :
            fUI2F(amin, amid, amax, min, init, max), fF2UI(min, init, max, amin, amid, amax)
        {}
        
        LinearValueConverter2() : fUI2F(0.,0.,0.,0.,0.,0.), fF2UI(0.,0.,0.,0.,0.,0.)
        {}
    
        virtual double ui2faust(double x) { return fUI2F(x); }
        virtual double faust2ui(double x) { return fF2UI(x); }
    
        virtual void setMappingValues(double amin, double amid, double amax, double min, double init, double max)
        {
            fUI2F = Interpolator3pt(amin, amid, amax, min, init, max);
            fF2UI = Interpolator3pt(min, init, max, amin, amid, amax);
        }

        virtual void getMappingValues(double& amin, double& amid, double& amax)
        {
            fUI2F.getMappingValues(amin, amid, amax);
        }
    
};

//--------------------------------------------------------------------------------------
// Logarithmic conversion between ui and Faust values
//--------------------------------------------------------------------------------------
class LogValueConverter : public LinearValueConverter
{

    public:

        LogValueConverter(double umin, double umax, double fmin, double fmax) :
            LinearValueConverter(umin, umax, std::log(std::max<double>(DBL_MIN, fmin)), std::log(std::max<double>(DBL_MIN, fmax)))
        {}

        virtual double ui2faust(double x) { return std::exp(LinearValueConverter::ui2faust(x)); }
        virtual double faust2ui(double x) { return LinearValueConverter::faust2ui(std::log(std::max<double>(x, DBL_MIN))); }

};

//--------------------------------------------------------------------------------------
// Exponential conversion between ui and Faust values
//--------------------------------------------------------------------------------------
class ExpValueConverter : public LinearValueConverter
{

    public:

        ExpValueConverter(double umin, double umax, double fmin, double fmax) :
            LinearValueConverter(umin, umax, std::min<double>(DBL_MAX, std::exp(fmin)), std::min<double>(DBL_MAX, std::exp(fmax)))
        {}

        virtual double ui2faust(double x) { return std::log(LinearValueConverter::ui2faust(x)); }
        virtual double faust2ui(double x) { return LinearValueConverter::faust2ui(std::min<double>(DBL_MAX, std::exp(x))); }

};

//--------------------------------------------------------------------------------------
// Convert accelerometer or gyroscope values to Faust values
// Using an Up curve (curve 0)
//--------------------------------------------------------------------------------------
class AccUpConverter : public UpdatableValueConverter
{

    private:

        Interpolator3pt fA2F;
        Interpolator3pt fF2A;

    public:

        AccUpConverter(double amin, double amid, double amax, double fmin, double fmid, double fmax) :
            fA2F(amin,amid,amax,fmin,fmid,fmax),
            fF2A(fmin,fmid,fmax,amin,amid,amax)
        {}

        virtual double ui2faust(double x) { return fA2F(x); }
        virtual double faust2ui(double x) { return fF2A(x); }

        virtual void setMappingValues(double amin, double amid, double amax, double fmin, double fmid, double fmax)
        {
            //__android_log_print(ANDROID_LOG_ERROR, "Faust", "AccUpConverter update %f %f %f %f %f %f", amin,amid,amax,fmin,fmid,fmax);
            fA2F = Interpolator3pt(amin, amid, amax, fmin, fmid, fmax);
            fF2A = Interpolator3pt(fmin, fmid, fmax, amin, amid, amax);
        }

        virtual void getMappingValues(double& amin, double& amid, double& amax)
        {
            fA2F.getMappingValues(amin, amid, amax);
        }

};

//--------------------------------------------------------------------------------------
// Convert accelerometer or gyroscope values to Faust values
// Using a Down curve (curve 1)
//--------------------------------------------------------------------------------------
class AccDownConverter : public UpdatableValueConverter
{

    private:

        Interpolator3pt	fA2F;
        Interpolator3pt	fF2A;

    public:

        AccDownConverter(double amin, double amid, double amax, double fmin, double fmid, double fmax) :
            fA2F(amin,amid,amax,fmax,fmid,fmin),
            fF2A(fmin,fmid,fmax,amax,amid,amin)
        {}

        virtual double ui2faust(double x) { return fA2F(x); }
        virtual double faust2ui(double x) { return fF2A(x); }

        virtual void setMappingValues(double amin, double amid, double amax, double fmin, double fmid, double fmax)
        {
             //__android_log_print(ANDROID_LOG_ERROR, "Faust", "AccDownConverter update %f %f %f %f %f %f", amin,amid,amax,fmin,fmid,fmax);
            fA2F = Interpolator3pt(amin, amid, amax, fmax, fmid, fmin);
            fF2A = Interpolator3pt(fmin, fmid, fmax, amax, amid, amin);
        }

        virtual void getMappingValues(double& amin, double& amid, double& amax)
        {
            fA2F.getMappingValues(amin, amid, amax);
        }
};

//--------------------------------------------------------------------------------------
// Convert accelerometer or gyroscope values to Faust values
// Using an Up-Down curve (curve 2)
//--------------------------------------------------------------------------------------
class AccUpDownConverter : public UpdatableValueConverter
{

    private:

        Interpolator3pt	fA2F;
        Interpolator fF2A;

    public:

        AccUpDownConverter(double amin, double amid, double amax, double fmin, double fmid, double fmax) :
            fA2F(amin,amid,amax,fmin,fmax,fmin),
            fF2A(fmin,fmax,amin,amax)				// Special, pseudo inverse of a non monotonic function
        {}

        virtual double ui2faust(double x) { return fA2F(x); }
        virtual double faust2ui(double x) { return fF2A(x); }

        virtual void setMappingValues(double amin, double amid, double amax, double fmin, double fmid, double fmax)
        {
            //__android_log_print(ANDROID_LOG_ERROR, "Faust", "AccUpDownConverter update %f %f %f %f %f %f", amin,amid,amax,fmin,fmid,fmax);
            fA2F = Interpolator3pt(amin, amid, amax, fmin, fmax, fmin);
            fF2A = Interpolator(fmin, fmax, amin, amax);
        }

        virtual void getMappingValues(double& amin, double& amid, double& amax)
        {
            fA2F.getMappingValues(amin, amid, amax);
        }
};

//--------------------------------------------------------------------------------------
// Convert accelerometer or gyroscope values to Faust values
// Using a Down-Up curve (curve 3)
//--------------------------------------------------------------------------------------
class AccDownUpConverter : public UpdatableValueConverter
{

    private:

        Interpolator3pt	fA2F;
        Interpolator fF2A;

    public:

        AccDownUpConverter(double amin, double amid, double amax, double fmin, double fmid, double fmax) :
            fA2F(amin,amid,amax,fmax,fmin,fmax),
            fF2A(fmin,fmax,amin,amax)				// Special, pseudo inverse of a non monotonic function
        {}

        virtual double ui2faust(double x) { return fA2F(x); }
        virtual double faust2ui(double x) { return fF2A(x); }

        virtual void setMappingValues(double amin, double amid, double amax, double fmin, double fmid, double fmax)
        {
            //__android_log_print(ANDROID_LOG_ERROR, "Faust", "AccDownUpConverter update %f %f %f %f %f %f", amin,amid,amax,fmin,fmid,fmax);
            fA2F = Interpolator3pt(amin, amid, amax, fmax, fmin, fmax);
            fF2A = Interpolator(fmin, fmax, amin, amax);
        }

        virtual void getMappingValues(double& amin, double& amid, double& amax)
        {
            fA2F.getMappingValues(amin, amid, amax);
        }
};

//--------------------------------------------------------------------------------------
// Base class for ZoneControl
//--------------------------------------------------------------------------------------
class ZoneControl
{

    protected:

        FAUSTFLOAT*	fZone;

    public:

        ZoneControl(FAUSTFLOAT* zone) : fZone(zone) {}
        virtual ~ZoneControl() {}

        virtual void update(double v) const {}

        virtual void setMappingValues(int curve, double amin, double amid, double amax, double min, double init, double max) {}
        virtual void getMappingValues(double& amin, double& amid, double& amax) {}

        FAUSTFLOAT* getZone() { return fZone; }

        virtual void setActive(bool on_off) {}
        virtual bool getActive() { return false; }

        virtual int getCurve() { return -1; }

};

//--------------------------------------------------------------------------------------
//  Useful to implement accelerometers metadata as a list of ZoneControl for each axes
//--------------------------------------------------------------------------------------
class ConverterZoneControl : public ZoneControl
{

    protected:

        ValueConverter* fValueConverter;

    public:

        ConverterZoneControl(FAUSTFLOAT* zone, ValueConverter* converter) : ZoneControl(zone), fValueConverter(converter) {}
        virtual ~ConverterZoneControl() { delete fValueConverter; } // Assuming fValueConverter is not kept elsewhere...

        virtual void update(double v) const { *fZone = FAUSTFLOAT(fValueConverter->ui2faust(v)); }

        ValueConverter* getConverter() { return fValueConverter; }

};

//--------------------------------------------------------------------------------------
// Association of a zone and a four value converter, each one for each possible curve.
// Useful to implement accelerometers metadata as a list of ZoneControl for each axes
//--------------------------------------------------------------------------------------
class CurveZoneControl : public ZoneControl
{

    private:

        std::vector<UpdatableValueConverter*> fValueConverters;
        int fCurve;

    public:

        CurveZoneControl(FAUSTFLOAT* zone, int curve, double amin, double amid, double amax, double min, double init, double max) : ZoneControl(zone), fCurve(0)
        {
            assert(curve >= 0 && curve <= 3);
            fValueConverters.push_back(new AccUpConverter(amin, amid, amax, min, init, max));
            fValueConverters.push_back(new AccDownConverter(amin, amid, amax, min, init, max));
            fValueConverters.push_back(new AccUpDownConverter(amin, amid, amax, min, init, max));
            fValueConverters.push_back(new AccDownUpConverter(amin, amid, amax, min, init, max));
            fCurve = curve;
        }
        virtual ~CurveZoneControl()
        {
            for (const auto& it : fValueConverters) { delete it; }
        }
        void update(double v) const { if (fValueConverters[fCurve]->getActive()) *fZone = FAUSTFLOAT(fValueConverters[fCurve]->ui2faust(v)); }

        void setMappingValues(int curve, double amin, double amid, double amax, double min, double init, double max)
        {
            fValueConverters[curve]->setMappingValues(amin, amid, amax, min, init, max);
            fCurve = curve;
        }

        void getMappingValues(double& amin, double& amid, double& amax)
        {
            fValueConverters[fCurve]->getMappingValues(amin, amid, amax);
        }

        void setActive(bool on_off)
        {
            for (const auto& it : fValueConverters) { it->setActive(on_off); }
        }

        int getCurve() { return fCurve; }
};

class ZoneReader
{

    private:

        FAUSTFLOAT* fZone;
        Interpolator fInterpolator;

    public:

        ZoneReader(FAUSTFLOAT* zone, double lo, double hi) : fZone(zone), fInterpolator(lo, hi, 0, 255) {}

        virtual ~ZoneReader() {}

        int getValue()
        {
            return (fZone != nullptr) ? int(fInterpolator(*fZone)) : 127;
        }

};

#endif
/**************************  END  ValueConverter.h **************************/
/************************** BEGIN MetaDataUI.h **************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef MetaData_UI_H
#define MetaData_UI_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include <map>
#include <set>
#include <string>
#include <string.h>
#include <assert.h>
#include <stdio.h> // We use the lighter fprintf code

/************************** BEGIN SimpleParser.h *********************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ********************************************************************/

#ifndef SIMPLEPARSER_H
#define SIMPLEPARSER_H

// ---------------------------------------------------------------------
//                          Simple Parser
// A parser returns true if it was able to parse what it is
// supposed to parse and advance the pointer. Otherwise it returns false
// and the pointer is not advanced so that another parser can be tried.
// ---------------------------------------------------------------------

#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <fstream>
#include <sstream>
#include <stdio.h> // We use the lighter fprintf code
#include <ctype.h>

#ifndef _WIN32
# pragma GCC diagnostic ignored "-Wunused-function"
#endif

struct itemInfo {
    std::string type;
    std::string label;
    std::string url;
    std::string address;
    int index;
    double init;
    double fmin;
    double fmax;
    double step;
    std::vector<std::pair<std::string, std::string> > meta;
    
    itemInfo():index(0), init(0.), fmin(0.), fmax(0.), step(0.)
    {}
};

// ---------------------------------------------------------------------
//                          Elementary parsers
// ---------------------------------------------------------------------

// Report a parsing error
static bool parseError(const char*& p, const char* errmsg)
{
    fprintf(stderr, "Parse error : %s here : %s\n", errmsg, p);
    return true;
}

/**
 * @brief skipBlank : advance pointer p to the first non blank character
 * @param p the string to parse, then the remaining string
 */
static void skipBlank(const char*& p)
{
    while (isspace(*p)) { p++; }
}

// Parse character x, but don't report error if fails
static bool tryChar(const char*& p, char x)
{
    skipBlank(p);
    if (x == *p) {
        p++;
        return true;
    } else {
        return false;
    }
}

/**
 * @brief parseChar : parse a specific character x
 * @param p the string to parse, then the remaining string
 * @param x the character to recognize
 * @return true if x was found at the begin of p
 */
static bool parseChar(const char*& p, char x)
{
    skipBlank(p);
    if (x == *p) {
        p++;
        return true;
    } else {
        return false;
    }
}

/**
 * @brief parseWord : parse a specific string w
 * @param p the string to parse, then the remaining string
 * @param w the string to recognize
 * @return true if string w was found at the begin of p
 */
static bool parseWord(const char*& p, const char* w)
{
    skipBlank(p);
    const char* saved = p;  // to restore position if we fail
    while ((*w == *p) && (*w)) {++w; ++p;}
    if (*w) {
        p = saved;
        return false;
    } else {
        return true;
    }
}

/**
 * @brief parseDouble : parse number [s]dddd[.dddd] or [s]d[.dddd][E|e][s][dddd] and store the result in x
 * @param p the string to parse, then the remaining string
 * @param x the float number found if any
 * @return true if a float number was found at the begin of p
 */
static bool parseDouble(const char*& p, double& x)
{
    double sign = 1.0;     // sign of the number
    double ipart = 0;      // integral part of the number
    double dpart = 0;      // decimal part of the number before division
    double dcoef = 1.0;    // division factor for the decimal part
    double expsign = 1.0;  // sign of the E|e part
    double expcoef = 0.0;  // multiplication factor of E|e part
    
    bool valid = false;    // true if the number contains at least one digit
    
    skipBlank(p);
    const char* saved = p;  // to restore position if we fail
    
    // Sign
    if (parseChar(p, '+')) {
        sign = 1.0;
    } else if (parseChar(p, '-')) {
        sign = -1.0;
    }
    
    // Integral part
    while (isdigit(*p)) {
        valid = true;
        ipart = ipart*10 + (*p - '0');
        p++;
    }
    
    // Possible decimal part
    if (parseChar(p, '.')) {
        while (isdigit(*p)) {
            valid = true;
            dpart = dpart*10 + (*p - '0');
            dcoef *= 10.0;
            p++;
        }
    }
    
    // Possible E|e part
    if (parseChar(p, 'E') || parseChar(p, 'e')) {
        if (parseChar(p, '+')) {
            expsign = 1.0;
        } else if (parseChar(p, '-')) {
            expsign = -1.0;
        }
        while (isdigit(*p)) {
            expcoef = expcoef*10 + (*p - '0');
            p++;
        }
    }
    
    if (valid)  {
        x = (sign*(ipart + dpart/dcoef)) * std::pow(10.0, expcoef*expsign);
    } else {
        p = saved;
    }
    return valid;
}

/**
 * @brief parseString, parse an arbitrary quoted string q...q and store the result in s
 * @param p the string to parse, then the remaining string
 * @param quote the character used to quote the string
 * @param s the (unquoted) string found if any
 * @return true if a string was found at the begin of p
 */
static bool parseString(const char*& p, char quote, std::string& s)
{
    std::string str;
    skipBlank(p);
    
    const char* saved = p;  // to restore position if we fail
    if (*p++ == quote) {
        while ((*p != 0) && (*p != quote)) {
            str += *p++;
        }
        if (*p++ == quote) {
            s = str;
            return true;
        }
    }
    p = saved;
    return false;
}

/**
 * @brief parseSQString, parse a single quoted string '...' and store the result in s
 * @param p the string to parse, then the remaining string
 * @param s the (unquoted) string found if any
 * @return true if a string was found at the begin of p
 */
static bool parseSQString(const char*& p, std::string& s)
{
    return parseString(p, '\'', s);
}

/**
 * @brief parseDQString, parse a double quoted string "..." and store the result in s
 * @param p the string to parse, then the remaining string
 * @param s the (unquoted) string found if any
 * @return true if a string was found at the begin of p
 */
static bool parseDQString(const char*& p, std::string& s)
{
    return parseString(p, '"', s);
}

// ---------------------------------------------------------------------
//
//                          IMPLEMENTATION
// 
// ---------------------------------------------------------------------

/**
 * @brief parseMenuItem, parse a menu item ...'low':440.0...
 * @param p the string to parse, then the remaining string
 * @param name the name found
 * @param value the value found
 * @return true if a nemu item was found
 */
static bool parseMenuItem(const char*& p, std::string& name, double& value)
{
    const char* saved = p;  // to restore position if we fail
    if (parseSQString(p, name) && parseChar(p, ':') && parseDouble(p, value)) {
        return true;
    } else {
        p = saved;
        return false;
    }
}

static bool parseMenuItem2(const char*& p, std::string& name)
{
    const char* saved = p;  // to restore position if we fail
    // single quoted
    if (parseSQString(p, name)) {
        return true;
    } else {
        p = saved;
        return false;
    }
}

/**
 * @brief parseMenuList, parse a menu list {'low' : 440.0; 'mid' : 880.0; 'hi' : 1760.0}...
 * @param p the string to parse, then the remaining string
 * @param names the vector of names found
 * @param values the vector of values found
 * @return true if a menu list was found
 */
static bool parseMenuList(const char*& p, std::vector<std::string>& names, std::vector<double>& values)
{
    std::vector<std::string> tmpnames;
    std::vector<double> tmpvalues;
    const char* saved = p; // to restore position if we fail

    if (parseChar(p, '{')) {
        do {
            std::string n;
            double v;
            if (parseMenuItem(p, n, v)) {
                tmpnames.push_back(n);
                tmpvalues.push_back(v);
            } else {
                p = saved;
                return false;
            }
        } while (parseChar(p, ';'));
        if (parseChar(p, '}')) {
            // we suceeded
            names = tmpnames;
            values = tmpvalues;
            return true;
        }
    }
    p = saved;
    return false;
}

static bool parseMenuList2(const char*& p, std::vector<std::string>& names, bool debug)
{
    std::vector<std::string> tmpnames;
    const char* saved = p;  // to restore position if we fail
    
    if (parseChar(p, '{')) {
        do {
            std::string n;
            if (parseMenuItem2(p, n)) {
                tmpnames.push_back(n);
            } else {
                goto error;
            }
        } while (parseChar(p, ';'));
        if (parseChar(p, '}')) {
            // we suceeded
            names = tmpnames;
            return true;
        }
    }
    
error:
    if (debug) { fprintf(stderr, "parseMenuList2 : (%s) is not a valid list !\n", p); }
    p = saved;
    return false;
}

/// ---------------------------------------------------------------------
// Parse list of strings
/// ---------------------------------------------------------------------
static bool parseList(const char*& p, std::vector<std::string>& items)
{
    const char* saved = p;  // to restore position if we fail
    if (parseChar(p, '[')) {
        do {
            std::string item;
            if (!parseDQString(p, item)) {
                p = saved;
                return false;
            }
            items.push_back(item);
        } while (tryChar(p, ','));
        return parseChar(p, ']');
    } else {
        p = saved;
        return false;
    }
}

static bool parseMetaData(const char*& p, std::map<std::string, std::string>& metadatas)
{
    const char* saved = p; // to restore position if we fail
    std::string metaKey, metaValue;
    if (parseChar(p, ':') && parseChar(p, '[')) {
        do { 
            if (parseChar(p, '{') && parseDQString(p, metaKey) && parseChar(p, ':') && parseDQString(p, metaValue) && parseChar(p, '}')) {
                metadatas[metaKey] = metaValue;
            }
        } while (tryChar(p, ','));
        return parseChar(p, ']');
    } else {
        p = saved;
        return false;
    }
}

static bool parseItemMetaData(const char*& p, std::vector<std::pair<std::string, std::string> >& metadatas)
{
    const char* saved = p; // to restore position if we fail
    std::string metaKey, metaValue;
    if (parseChar(p, ':') && parseChar(p, '[')) {
        do { 
            if (parseChar(p, '{') && parseDQString(p, metaKey) && parseChar(p, ':') && parseDQString(p, metaValue) && parseChar(p, '}')) {
                metadatas.push_back(std::make_pair(metaKey, metaValue));
            }
        } while (tryChar(p, ','));
        return parseChar(p, ']');
    } else {
        p = saved;
        return false;
    }
}

// ---------------------------------------------------------------------
// Parse metadatas of the interface:
// "name" : "...", "inputs" : "...", "outputs" : "...", ...
// and store the result as key/value
/// ---------------------------------------------------------------------
static bool parseGlobalMetaData(const char*& p, std::string& key, std::string& value, double& dbl, std::map<std::string, std::string>& metadatas, std::vector<std::string>& items)
{
    const char* saved = p; // to restore position if we fail
    if (parseDQString(p, key)) {
        if (key == "meta") {
            return parseMetaData(p, metadatas);
        } else {
            return parseChar(p, ':') && (parseDQString(p, value) || parseList(p, items) || parseDouble(p, dbl));
        }
    } else {
        p = saved;
        return false;
    }
}

// ---------------------------------------------------------------------
// Parse gui:
// "type" : "...", "label" : "...", "address" : "...", ...
// and store the result in uiItems Vector
/// ---------------------------------------------------------------------
static bool parseUI(const char*& p, std::vector<itemInfo>& uiItems, int& numItems)
{
    const char* saved = p; // to restore position if we fail
    if (parseChar(p, '{')) {
   
        std::string label;
        std::string value;
        double dbl = 0;
        
        do {
            if (parseDQString(p, label)) {
                if (label == "type") {
                    if (uiItems.size() != 0) {
                        numItems++;
                    }
                    if (parseChar(p, ':') && parseDQString(p, value)) {   
                        itemInfo item;
                        item.type = value;
                        uiItems.push_back(item);
                    }
                }
                
                else if (label == "label") {
                    if (parseChar(p, ':') && parseDQString(p, value)) {
                        uiItems[numItems].label = value;
                    }
                }
                
                else if (label == "url") {
                    if (parseChar(p, ':') && parseDQString(p, value)) {
                        uiItems[numItems].url = value;
                    }
                }
                
                else if (label == "address") {
                    if (parseChar(p, ':') && parseDQString(p, value)) {
                        uiItems[numItems].address = value;
                    }
                }
                
                else if (label == "index") {
                    if (parseChar(p, ':') && parseDouble(p, dbl)) {
                        uiItems[numItems].index = int(dbl);
                    }
                }
                
                else if (label == "meta") {
                    if (!parseItemMetaData(p, uiItems[numItems].meta)) {
                        return false;
                    }
                }
                
                else if (label == "init") {
                    if (parseChar(p, ':') && parseDouble(p, dbl)) {
                        uiItems[numItems].init = dbl;
                    }
                }
                
                else if (label == "min") {
                    if (parseChar(p, ':') && parseDouble(p, dbl)) {
                        uiItems[numItems].fmin = dbl;
                    }
                }
                
                else if (label == "max") {
                    if (parseChar(p, ':') && parseDouble(p, dbl)) {
                        uiItems[numItems].fmax = dbl;
                    }
                }
                
                else if (label == "step") {
                    if (parseChar(p, ':') && parseDouble(p, dbl)) {
                        uiItems[numItems].step = dbl;
                    }
                }
                
                else if (label == "items") {
                    if (parseChar(p, ':') && parseChar(p, '[')) {
                        do {
                            if (!parseUI(p, uiItems, numItems)) {
                                p = saved;
                                return false;
                            }
                        } while (tryChar(p, ','));
                        if (parseChar(p, ']')) {
                            itemInfo item;
                            item.type = "close";
                            uiItems.push_back(item);
                            numItems++;
                        }
                    }
                }
            } else {
                p = saved;
                return false;
            }
            
        } while (tryChar(p, ','));
    
        return parseChar(p, '}');
    } else {
        return true; // "items": [] is valid
    }
}

// ---------------------------------------------------------------------
// Parse full JSON record describing a JSON/Faust interface :
// {"metadatas": "...", "ui": [{ "type": "...", "label": "...", "items": [...], "address": "...","init": "...", "min": "...", "max": "...","step": "..."}]}
//
// and store the result in map Metadatas and vector containing the items of the interface. Returns true if parsing was successfull.
/// ---------------------------------------------------------------------
static bool parseJson(const char*& p,
                      std::map<std::string, std::pair<std::string, double> >& metaDatas0,
                      std::map<std::string, std::string>& metaDatas1,
                      std::map<std::string, std::vector<std::string> >& metaDatas2,
                      std::vector<itemInfo>& uiItems)
{
    parseChar(p, '{');
    
    do {
        std::string key;
        std::string value;
        double dbl = 0;
        std::vector<std::string> items;
        if (parseGlobalMetaData(p, key, value, dbl, metaDatas1, items)) {
            if (key != "meta") {
                // keep "name", "inputs", "outputs" key/value pairs
                if (items.size() > 0) {
                    metaDatas2[key] = items;
                    items.clear();
                } else if (value != "") {
                    metaDatas0[key].first = value;
                } else {
                    metaDatas0[key].second = dbl;
                }
            }
        } else if (key == "ui") {
            int numItems = 0;
            parseChar(p, '[') && parseUI(p, uiItems, numItems);
        }
    } while (tryChar(p, ','));
    
    return parseChar(p, '}');
}

#endif // SIMPLEPARSER_H
/**************************  END  SimpleParser.h **************************/

static bool startWith(const std::string& str, const std::string& prefix)
{
    return (str.substr(0, prefix.size()) == prefix);
}

/**
 * Convert a dB value into a scale between 0 and 1 (following IEC standard ?)
 */
static FAUSTFLOAT dB2Scale(FAUSTFLOAT dB)
{
    FAUSTFLOAT scale = FAUSTFLOAT(1.0);
    
    /*if (dB < -70.0f)
     scale = 0.0f;
     else*/
    if (dB < FAUSTFLOAT(-60.0))
        scale = (dB + FAUSTFLOAT(70.0)) * FAUSTFLOAT(0.0025);
    else if (dB < FAUSTFLOAT(-50.0))
        scale = (dB + FAUSTFLOAT(60.0)) * FAUSTFLOAT(0.005) + FAUSTFLOAT(0.025);
    else if (dB < FAUSTFLOAT(-40.0))
        scale = (dB + FAUSTFLOAT(50.0)) * FAUSTFLOAT(0.0075) + FAUSTFLOAT(0.075);
    else if (dB < FAUSTFLOAT(-30.0))
        scale = (dB + FAUSTFLOAT(40.0)) * FAUSTFLOAT(0.015) + FAUSTFLOAT(0.15);
    else if (dB < FAUSTFLOAT(-20.0))
        scale = (dB + FAUSTFLOAT(30.0)) * FAUSTFLOAT(0.02) + FAUSTFLOAT(0.3);
    else if (dB < FAUSTFLOAT(-0.001) || dB > FAUSTFLOAT(0.001))  /* if (dB < 0.0) */
        scale = (dB + FAUSTFLOAT(20.0)) * FAUSTFLOAT(0.025) + FAUSTFLOAT(0.5);
    
    return scale;
}

/*******************************************************************************
 * MetaDataUI : Common class for MetaData handling
 ******************************************************************************/

//============================= BEGIN GROUP LABEL METADATA===========================
// Unlike widget's label, metadata inside group's label are not extracted directly by
// the Faust compiler. Therefore they must be extracted within the architecture file
//-----------------------------------------------------------------------------------

class MetaDataUI {
    
    protected:
        
        std::string                         fGroupTooltip;
        std::map<FAUSTFLOAT*, FAUSTFLOAT>   fGuiSize;            // map widget zone with widget size coef
        std::map<FAUSTFLOAT*, std::string>  fTooltip;            // map widget zone with tooltip strings
        std::map<FAUSTFLOAT*, std::string>  fUnit;               // map widget zone to unit string (i.e. "dB")
        std::map<FAUSTFLOAT*, std::string>  fRadioDescription;   // map zone to {'low':440; ...; 'hi':1000.0}
        std::map<FAUSTFLOAT*, std::string>  fMenuDescription;    // map zone to {'low':440; ...; 'hi':1000.0}
        std::set<FAUSTFLOAT*>               fKnobSet;            // set of widget zone to be knobs
        std::set<FAUSTFLOAT*>               fLedSet;             // set of widget zone to be LEDs
        std::set<FAUSTFLOAT*>               fNumSet;             // set of widget zone to be numerical bargraphs
        std::set<FAUSTFLOAT*>               fLogSet;             // set of widget zone having a log UI scale
        std::set<FAUSTFLOAT*>               fExpSet;             // set of widget zone having an exp UI scale
        std::set<FAUSTFLOAT*>               fHiddenSet;          // set of hidden widget zone
        
        void clearMetadata()
        {
            fGuiSize.clear();
            fTooltip.clear();
            fUnit.clear();
            fRadioDescription.clear();
            fMenuDescription.clear();
            fKnobSet.clear();
            fLedSet.clear();
            fNumSet.clear();
            fLogSet.clear();
            fExpSet.clear();
            fHiddenSet.clear();
            fGroupTooltip = "";
        }
        
        /**
         * rmWhiteSpaces(): Remove the leading and trailing white spaces of a string
         * (but not those in the middle of the string)
         */
        static std::string rmWhiteSpaces(const std::string& s)
        {
            size_t i = s.find_first_not_of(" \t");
            size_t j = s.find_last_not_of(" \t");
            if ((i != std::string::npos) && (j != std::string::npos)) {
                return s.substr(i, 1+j-i);
            } else {
                return "";
            }
        }
        
        /**
         * Format tooltip string by replacing some white spaces by
         * return characters so that line width doesn't exceed n.
         * Limitation : long words exceeding n are not cut.
         */
        std::string formatTooltip(int n, const std::string& tt)
        {
            std::string ss = tt;  // ss string we are going to format
            int lws = 0;          // last white space encountered
            int lri = 0;          // last return inserted
            for (int i = 0; i < (int)tt.size(); i++) {
                if (tt[i] == ' ') lws = i;
                if (((i-lri) >= n) && (lws > lri)) {
                    // insert return here
                    ss[lws] = '\n';
                    lri = lws;
                }
            }
            return ss;
        }
        
    public:
        
        virtual ~MetaDataUI()
        {}
        
        enum Scale {
            kLin,
            kLog,
            kExp
        };
        
        Scale getScale(FAUSTFLOAT* zone)
        {
            if (fLogSet.count(zone) > 0) return kLog;
            if (fExpSet.count(zone) > 0) return kExp;
            return kLin;
        }
        
        bool isKnob(FAUSTFLOAT* zone)
        {
            return fKnobSet.count(zone) > 0;
        }
        
        bool isRadio(FAUSTFLOAT* zone)
        {
            return fRadioDescription.count(zone) > 0;
        }
        
        bool isMenu(FAUSTFLOAT* zone)
        {
            return fMenuDescription.count(zone) > 0;
        }
        
        bool isLed(FAUSTFLOAT* zone)
        {
            return fLedSet.count(zone) > 0;
        }
        
        bool isNumerical(FAUSTFLOAT* zone)
        {
            return fNumSet.count(zone) > 0;
        }
        
        bool isHidden(FAUSTFLOAT* zone)
        {
            return fHiddenSet.count(zone) > 0;
        }
        
        /**
         * Extracts metadata from a label : 'vol [unit: dB]' -> 'vol' + metadata(unit=dB)
         */
        static void extractMetadata(const std::string& fulllabel, std::string& label, std::map<std::string, std::string>& metadata)
        {
            enum {kLabel, kEscape1, kEscape2, kEscape3, kKey, kValue};
            int state = kLabel; int deep = 0;
            std::string key, value;
            
            for (unsigned int i = 0; i < fulllabel.size(); i++) {
                char c = fulllabel[i];
                switch (state) {
                    case kLabel :
                        assert(deep == 0);
                        switch (c) {
                            case '\\' : state = kEscape1; break;
                            case '[' : state = kKey; deep++; break;
                            default : label += c;
                        }
                        break;
                        
                    case kEscape1:
                        label += c;
                        state = kLabel;
                        break;
                        
                    case kEscape2:
                        key += c;
                        state = kKey;
                        break;
                        
                    case kEscape3:
                        value += c;
                        state = kValue;
                        break;
                        
                    case kKey:
                        assert(deep > 0);
                        switch (c) {
                            case '\\':
                                state = kEscape2;
                                break;
                                
                            case '[':
                                deep++;
                                key += c;
                                break;
                                
                            case ':':
                                if (deep == 1) {
                                    state = kValue;
                                } else {
                                    key += c;
                                }
                                break;
                            case ']':
                                deep--;
                                if (deep < 1) {
                                    metadata[rmWhiteSpaces(key)] = "";
                                    state = kLabel;
                                    key = "";
                                    value = "";
                                } else {
                                    key += c;
                                }
                                break;
                            default : key += c;
                        }
                        break;
                        
                    case kValue:
                        assert(deep > 0);
                        switch (c) {
                            case '\\':
                                state = kEscape3;
                                break;
                                
                            case '[':
                                deep++;
                                value += c;
                                break;
                                
                            case ']':
                                deep--;
                                if (deep < 1) {
                                    metadata[rmWhiteSpaces(key)] = rmWhiteSpaces(value);
                                    state = kLabel;
                                    key = "";
                                    value = "";
                                } else {
                                    value += c;
                                }
                                break;
                            default : value += c;
                        }
                        break;
                        
                    default:
                        fprintf(stderr, "ERROR unrecognized state %d\n", state);
                }
            }
            label = rmWhiteSpaces(label);
        }
        
        /**
         * Analyses the widget zone metadata declarations and takes appropriate actions.
         */
        void declare(FAUSTFLOAT* zone, const char* key, const char* value)
        {
            if (zone == 0) {
                // special zone 0 means group metadata
                if (strcmp(key, "tooltip") == 0) {
                    // only group tooltip are currently implemented
                    fGroupTooltip = formatTooltip(30, value);
                } else if (strcmp(key, "hidden") == 0) {
                    fHiddenSet.insert(zone);
                }
            } else {
                if (strcmp(key, "size") == 0) {
                    fGuiSize[zone] = atof(value);
                }
                else if (strcmp(key, "tooltip") == 0) {
                    fTooltip[zone] = formatTooltip(30, value);
                }
                else if (strcmp(key, "unit") == 0) {
                    fUnit[zone] = value;
                }
                else if (strcmp(key, "hidden") == 0) {
                    fHiddenSet.insert(zone);
                }
                else if (strcmp(key, "scale") == 0) {
                    if (strcmp(value, "log") == 0) {
                        fLogSet.insert(zone);
                    } else if (strcmp(value, "exp") == 0) {
                        fExpSet.insert(zone);
                    }
                }
                else if (strcmp(key, "style") == 0) {
                    if (strcmp(value, "knob") == 0) {
                        fKnobSet.insert(zone);
                    } else if (strcmp(value, "led") == 0) {
                        fLedSet.insert(zone);
                    } else if (strcmp(value, "numerical") == 0) {
                        fNumSet.insert(zone);
                    } else {
                        const char* p = value;
                        if (parseWord(p, "radio")) {
                            fRadioDescription[zone] = std::string(p);
                        } else if (parseWord(p, "menu")) {
                            fMenuDescription[zone] = std::string(p);
                        }
                    }
                }
            }
        }
    
};

#endif
/**************************  END  MetaDataUI.h **************************/
/************************** BEGIN ring-buffer.h **************************/
/*
  Copyright (C) 2000 Paul Davis
  Copyright (C) 2003 Rohan Drape
  Copyright (C) 2016 GRAME (renaming for internal use)

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation; either version 2.1 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

  ISO/POSIX C version of Paul Davis's lock free ringbuffer C++ code.
  This is safe for the case of one read thread and one write thread.
*/

#ifndef __ring_buffer__
#define __ring_buffer__

#include <stdlib.h>
#include <string.h>

#ifdef WIN32
# pragma warning (disable: 4334)
#else
# pragma GCC diagnostic ignored "-Wunused-function"
#endif

typedef struct {
    char *buf;
    size_t len;
}
ringbuffer_data_t;

typedef struct {
    char *buf;
    volatile size_t write_ptr;
    volatile size_t read_ptr;
    size_t	size;
    size_t	size_mask;
    int	mlocked;
}
ringbuffer_t;

static ringbuffer_t *ringbuffer_create(size_t sz);
static void ringbuffer_free(ringbuffer_t *rb);
static void ringbuffer_get_read_vector(const ringbuffer_t *rb,
                                         ringbuffer_data_t *vec);
static void ringbuffer_get_write_vector(const ringbuffer_t *rb,
                                          ringbuffer_data_t *vec);
static size_t ringbuffer_read(ringbuffer_t *rb, char *dest, size_t cnt);
static size_t ringbuffer_peek(ringbuffer_t *rb, char *dest, size_t cnt);
static void ringbuffer_read_advance(ringbuffer_t *rb, size_t cnt);
static size_t ringbuffer_read_space(const ringbuffer_t *rb);
static int ringbuffer_mlock(ringbuffer_t *rb);
static void ringbuffer_reset(ringbuffer_t *rb);
static void ringbuffer_reset_size (ringbuffer_t * rb, size_t sz);
static size_t ringbuffer_write(ringbuffer_t *rb, const char *src,
                                 size_t cnt);
static void ringbuffer_write_advance(ringbuffer_t *rb, size_t cnt);
static size_t ringbuffer_write_space(const ringbuffer_t *rb);

/* Create a new ringbuffer to hold at least `sz' bytes of data. The
   actual buffer size is rounded up to the next power of two. */

static ringbuffer_t *
ringbuffer_create (size_t sz)
{
	size_t power_of_two;
	ringbuffer_t *rb;

	if ((rb = (ringbuffer_t *) malloc (sizeof (ringbuffer_t))) == NULL) {
		return NULL;
	}

	for (power_of_two = 1u; 1u << power_of_two < sz; power_of_two++);

	rb->size = 1u << power_of_two;
	rb->size_mask = rb->size;
	rb->size_mask -= 1;
	rb->write_ptr = 0;
	rb->read_ptr = 0;
	if ((rb->buf = (char *) malloc (rb->size)) == NULL) {
		free (rb);
		return NULL;
	}
	rb->mlocked = 0;

	return rb;
}

/* Free all data associated with the ringbuffer `rb'. */

static void
ringbuffer_free (ringbuffer_t * rb)
{
#ifdef USE_MLOCK
	if (rb->mlocked) {
		munlock (rb->buf, rb->size);
	}
#endif /* USE_MLOCK */
	free (rb->buf);
	free (rb);
}

/* Lock the data block of `rb' using the system call 'mlock'.  */

static int
ringbuffer_mlock (ringbuffer_t * rb)
{
#ifdef USE_MLOCK
	if (mlock (rb->buf, rb->size)) {
		return -1;
	}
#endif /* USE_MLOCK */
	rb->mlocked = 1;
	return 0;
}

/* Reset the read and write pointers to zero. This is not thread
   safe. */

static void
ringbuffer_reset (ringbuffer_t * rb)
{
	rb->read_ptr = 0;
	rb->write_ptr = 0;
    memset(rb->buf, 0, rb->size);
}

/* Reset the read and write pointers to zero. This is not thread
   safe. */

static void
ringbuffer_reset_size (ringbuffer_t * rb, size_t sz)
{
    rb->size = sz;
    rb->size_mask = rb->size;
    rb->size_mask -= 1;
    rb->read_ptr = 0;
    rb->write_ptr = 0;
}

/* Return the number of bytes available for reading. This is the
   number of bytes in front of the read pointer and behind the write
   pointer.  */

static size_t
ringbuffer_read_space (const ringbuffer_t * rb)
{
	size_t w, r;

	w = rb->write_ptr;
	r = rb->read_ptr;

	if (w > r) {
		return w - r;
	} else {
		return (w - r + rb->size) & rb->size_mask;
	}
}

/* Return the number of bytes available for writing. This is the
   number of bytes in front of the write pointer and behind the read
   pointer.  */

static size_t
ringbuffer_write_space (const ringbuffer_t * rb)
{
	size_t w, r;

	w = rb->write_ptr;
	r = rb->read_ptr;

	if (w > r) {
		return ((r - w + rb->size) & rb->size_mask) - 1;
	} else if (w < r) {
		return (r - w) - 1;
	} else {
		return rb->size - 1;
	}
}

/* The copying data reader. Copy at most `cnt' bytes from `rb' to
   `dest'.  Returns the actual number of bytes copied. */

static size_t
ringbuffer_read (ringbuffer_t * rb, char *dest, size_t cnt)
{
	size_t free_cnt;
	size_t cnt2;
	size_t to_read;
	size_t n1, n2;

	if ((free_cnt = ringbuffer_read_space (rb)) == 0) {
		return 0;
	}

	to_read = cnt > free_cnt ? free_cnt : cnt;

	cnt2 = rb->read_ptr + to_read;

	if (cnt2 > rb->size) {
		n1 = rb->size - rb->read_ptr;
		n2 = cnt2 & rb->size_mask;
	} else {
		n1 = to_read;
		n2 = 0;
	}

	memcpy (dest, &(rb->buf[rb->read_ptr]), n1);
	rb->read_ptr = (rb->read_ptr + n1) & rb->size_mask;

	if (n2) {
		memcpy (dest + n1, &(rb->buf[rb->read_ptr]), n2);
		rb->read_ptr = (rb->read_ptr + n2) & rb->size_mask;
	}

	return to_read;
}

/* The copying data reader w/o read pointer advance. Copy at most
   `cnt' bytes from `rb' to `dest'.  Returns the actual number of bytes
   copied. */

static size_t
ringbuffer_peek (ringbuffer_t * rb, char *dest, size_t cnt)
{
	size_t free_cnt;
	size_t cnt2;
	size_t to_read;
	size_t n1, n2;
	size_t tmp_read_ptr;

	tmp_read_ptr = rb->read_ptr;

	if ((free_cnt = ringbuffer_read_space (rb)) == 0) {
		return 0;
	}

	to_read = cnt > free_cnt ? free_cnt : cnt;

	cnt2 = tmp_read_ptr + to_read;

	if (cnt2 > rb->size) {
		n1 = rb->size - tmp_read_ptr;
		n2 = cnt2 & rb->size_mask;
	} else {
		n1 = to_read;
		n2 = 0;
	}

	memcpy (dest, &(rb->buf[tmp_read_ptr]), n1);
	tmp_read_ptr = (tmp_read_ptr + n1) & rb->size_mask;

	if (n2) {
		memcpy (dest + n1, &(rb->buf[tmp_read_ptr]), n2);
	}

	return to_read;
}

/* The copying data writer. Copy at most `cnt' bytes to `rb' from
   `src'.  Returns the actual number of bytes copied. */

static size_t
ringbuffer_write (ringbuffer_t * rb, const char *src, size_t cnt)
{
	size_t free_cnt;
	size_t cnt2;
	size_t to_write;
	size_t n1, n2;

	if ((free_cnt = ringbuffer_write_space (rb)) == 0) {
		return 0;
	}

	to_write = cnt > free_cnt ? free_cnt : cnt;

	cnt2 = rb->write_ptr + to_write;

	if (cnt2 > rb->size) {
		n1 = rb->size - rb->write_ptr;
		n2 = cnt2 & rb->size_mask;
	} else {
		n1 = to_write;
		n2 = 0;
	}

	memcpy (&(rb->buf[rb->write_ptr]), src, n1);
	rb->write_ptr = (rb->write_ptr + n1) & rb->size_mask;

	if (n2) {
		memcpy (&(rb->buf[rb->write_ptr]), src + n1, n2);
		rb->write_ptr = (rb->write_ptr + n2) & rb->size_mask;
	}

	return to_write;
}

/* Advance the read pointer `cnt' places. */

static void
ringbuffer_read_advance (ringbuffer_t * rb, size_t cnt)
{
	size_t tmp = (rb->read_ptr + cnt) & rb->size_mask;
	rb->read_ptr = tmp;
}

/* Advance the write pointer `cnt' places. */

static void
ringbuffer_write_advance (ringbuffer_t * rb, size_t cnt)
{
	size_t tmp = (rb->write_ptr + cnt) & rb->size_mask;
	rb->write_ptr = tmp;
}

/* The non-copying data reader. `vec' is an array of two places. Set
   the values at `vec' to hold the current readable data at `rb'. If
   the readable data is in one segment the second segment has zero
   length. */

static void
ringbuffer_get_read_vector (const ringbuffer_t * rb,
				 ringbuffer_data_t * vec)
{
	size_t free_cnt;
	size_t cnt2;
	size_t w, r;

	w = rb->write_ptr;
	r = rb->read_ptr;

	if (w > r) {
		free_cnt = w - r;
	} else {
		free_cnt = (w - r + rb->size) & rb->size_mask;
	}

	cnt2 = r + free_cnt;

	if (cnt2 > rb->size) {

		/* Two part vector: the rest of the buffer after the current write
		   ptr, plus some from the start of the buffer. */

		vec[0].buf = &(rb->buf[r]);
		vec[0].len = rb->size - r;
		vec[1].buf = rb->buf;
		vec[1].len = cnt2 & rb->size_mask;

	} else {

		/* Single part vector: just the rest of the buffer */

		vec[0].buf = &(rb->buf[r]);
		vec[0].len = free_cnt;
		vec[1].len = 0;
	}
}

/* The non-copying data writer. `vec' is an array of two places. Set
   the values at `vec' to hold the current writeable data at `rb'. If
   the writeable data is in one segment the second segment has zero
   length. */

static void
ringbuffer_get_write_vector (const ringbuffer_t * rb,
				  ringbuffer_data_t * vec)
{
	size_t free_cnt;
	size_t cnt2;
	size_t w, r;

	w = rb->write_ptr;
	r = rb->read_ptr;

	if (w > r) {
		free_cnt = ((r - w + rb->size) & rb->size_mask) - 1;
	} else if (w < r) {
		free_cnt = (r - w) - 1;
	} else {
		free_cnt = rb->size - 1;
	}

	cnt2 = w + free_cnt;

	if (cnt2 > rb->size) {

		/* Two part vector: the rest of the buffer after the current write
		   ptr, plus some from the start of the buffer. */

		vec[0].buf = &(rb->buf[w]);
		vec[0].len = rb->size - w;
		vec[1].buf = rb->buf;
		vec[1].len = cnt2 & rb->size_mask;
	} else {
		vec[0].buf = &(rb->buf[w]);
		vec[0].len = free_cnt;
		vec[1].len = 0;
	}
}

#endif // __ring_buffer__
/**************************  END  ring-buffer.h **************************/

/*******************************************************************************
 * GUI : Abstract Graphic User Interface
 * Provides additional mechanisms to synchronize widgets and zones. Widgets
 * should both reflect the value of a zone and allow to change this value.
 ******************************************************************************/

class uiItem;
class GUI;
struct clist;

typedef void (*uiCallback)(FAUSTFLOAT val, void* data);

/**
 * Base class for uiTypedItem: memory zones that can be grouped and synchronized, using an internal cache.
 */
struct uiItemBase
{
    
    uiItemBase(GUI* ui, FAUSTFLOAT* zone)
    {
        assert(ui);
        assert(zone);
    }
    
    virtual ~uiItemBase()
    {}
    
    /**
     * This method will be called when the value changes externally,
     * and will signal the new value to all linked uItem
     * when the value is different from the cached one.
     *
     * @param v - the new value
     */
    virtual void modifyZone(FAUSTFLOAT v) = 0;
    
    /**
     * This method will be called when the value changes externally,
     * and will signal the new value to all linked uItem
     * when the value is different from the cached one.
     *
     * @param date - the timestamp of the received value in usec
     * @param v - the new value
     */
    virtual void modifyZone(double date, FAUSTFLOAT v) {}
    
    /**
     * This method is called by the synchronisation mecanism and is expected
     * to 'reflect' the new value, by changing the Widget layout for instance,
     * or sending a message (OSC, MIDI...)
     */
    virtual void reflectZone() = 0;
    
    /**
     * Return the cached value.
     *
     * @return - the cached value
     */
    virtual double cache() = 0;
    
};

// Declared as 'static' to avoid code duplication at link time
static void deleteClist(clist* cl);

/**
 * A list containing all groupe uiItemBase objects.
 */
struct clist : public std::list<uiItemBase*>
{
    
    virtual ~clist()
    {
        deleteClist(this);
    }
        
};

static void createUiCallbackItem(GUI* ui, FAUSTFLOAT* zone, uiCallback foo, void* data);

typedef std::map<FAUSTFLOAT*, clist*> zmap;

typedef std::map<FAUSTFLOAT*, ringbuffer_t*> ztimedmap;

class GUI : public UI
{
		
    private:
     
        static std::list<GUI*> fGuiList;
        zmap fZoneMap;
        bool fStopped;
    
     public:
            
        GUI():fStopped(false)
        {	
            fGuiList.push_back(this);
        }
        
        virtual ~GUI() 
        {   
            // delete all items
            for (const auto& it : fZoneMap) {
                delete it.second;
            }
            // suppress 'this' in static fGuiList
            fGuiList.remove(this);
        }

        // -- registerZone(z,c) : zone management
        
        void registerZone(FAUSTFLOAT* z, uiItemBase* c)
        {
            if (fZoneMap.find(z) == fZoneMap.end()) fZoneMap[z] = new clist();
            fZoneMap[z]->push_back(c);
        }
    
        void updateZone(FAUSTFLOAT* z)
        {
            FAUSTFLOAT v = *z;
            clist* cl = fZoneMap[z];
            for (const auto& c : *cl) {
                if (c->cache() != v) c->reflectZone();
            }
        }
    
        void updateAllZones()
        {
            for (const auto& m : fZoneMap) {
                updateZone(m.first);
            }
        }
    
        static void updateAllGuis()
        {
            for (const auto& g : fGuiList) {
                g->updateAllZones();
            }
        }
    
        void addCallback(FAUSTFLOAT* zone, uiCallback foo, void* data)
        {
            createUiCallbackItem(this, zone, foo, data);
        }

        // Start event or message processing
        virtual bool run() { return false; };
        // Stop event or message processing
        virtual void stop() { fStopped = true; }
        bool stopped() { return fStopped; }
    
        // -- widget's layouts
        
        virtual void openTabBox(const char* label) {}
        virtual void openHorizontalBox(const char* label) {}
        virtual void openVerticalBox(const char* label) {}
        virtual void closeBox() {}
        
        // -- active widgets
        
        virtual void addButton(const char* label, FAUSTFLOAT* zone) {}
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone) {}
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {}
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {}
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {}
    
        // -- passive widgets
        
        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) {}
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) {}
    
        // -- soundfiles
    
        virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) {}
    
        // -- metadata declarations

        virtual void declare(FAUSTFLOAT*, const char*, const char*) {}
    
        // Static global for timed zones, shared between all UI that will set timed values
        static ztimedmap gTimedZoneMap;

};

/**
 * User Interface Item: abstract definition.
 */
template <typename REAL>
class uiTypedItemReal : public uiItemBase
{
    protected:
        
        GUI* fGUI;
        REAL* fZone;
        REAL fCache;
        
        uiTypedItemReal(GUI* ui, REAL* zone):uiItemBase(ui, static_cast<FAUSTFLOAT*>(zone)),
        fGUI(ui), fZone(zone), fCache(REAL(-123456.654321))
        {
            ui->registerZone(zone, this);
        }
        
    public:
        
        virtual ~uiTypedItemReal()
        {}
    
        void modifyZone(REAL v)
        {
            fCache = v;
            if (*fZone != v) {
                *fZone = v;
                fGUI->updateZone(fZone);
            }
        }
    
        double cache() { return fCache; }
    
};

class uiItem : public uiTypedItemReal<FAUSTFLOAT> {
    
    protected:
    
        uiItem(GUI* ui, FAUSTFLOAT* zone):uiTypedItemReal<FAUSTFLOAT>(ui, zone)
        {}

    public:

        virtual ~uiItem() 
        {}

		void modifyZone(FAUSTFLOAT v)
		{
			fCache = v;
			if (*fZone != v) {
				*fZone = v;
				fGUI->updateZone(fZone);
			}
		}

};

/**
 * Base class for items with a value converter.
 */
struct uiConverter {
    
    ValueConverter* fConverter;
    
    uiConverter(MetaDataUI::Scale scale, FAUSTFLOAT umin, FAUSTFLOAT umax, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
    {
        // Select appropriate converter according to scale mode
        if (scale == MetaDataUI::kLog) {
            fConverter = new LogValueConverter(umin, umax, fmin, fmax);
        } else if (scale == MetaDataUI::kExp) {
            fConverter = new ExpValueConverter(umin, umax, fmin, fmax);
        } else {
            fConverter = new LinearValueConverter(umin, umax, fmin, fmax);
        }
    }
    
    virtual ~uiConverter()
    {
        delete fConverter;
    }
};

/**
 * User Interface item owned (and so deleted) by external code.
 */
class uiOwnedItem : public uiItem {
    
    protected:
    
        uiOwnedItem(GUI* ui, FAUSTFLOAT* zone):uiItem(ui, zone)
        {}
    
     public:
    
        virtual ~uiOwnedItem()
        {}
    
        virtual void reflectZone() {}
};

/**
 * Callback Item.
 */
class uiCallbackItem : public uiItem {
    
    protected:
    
        uiCallback fCallback;
        void* fData;
    
    public:
    
        uiCallbackItem(GUI* ui, FAUSTFLOAT* zone, uiCallback foo, void* data)
        : uiItem(ui, zone), fCallback(foo), fData(data) {}
        
        virtual void reflectZone() 
        {		
            FAUSTFLOAT v = *fZone;
            fCache = v; 
            fCallback(v, fData);	
        }
};

/**
 *  For timestamped control.
 */
struct DatedControl {
    
    double fDate;
    FAUSTFLOAT fValue;
    
    DatedControl(double d = 0., FAUSTFLOAT v = FAUSTFLOAT(0)):fDate(d), fValue(v) {}
    
};

/**
 * Base class for timed items.
 */
class uiTimedItem : public uiItem
{
    
    protected:
        
        bool fDelete;
        
    public:
    
        using uiItem::modifyZone;
        
        uiTimedItem(GUI* ui, FAUSTFLOAT* zone):uiItem(ui, zone)
        {
            if (GUI::gTimedZoneMap.find(fZone) == GUI::gTimedZoneMap.end()) {
                GUI::gTimedZoneMap[fZone] = ringbuffer_create(8192);
                fDelete = true;
            } else {
                fDelete = false;
            }
        }
        
        virtual ~uiTimedItem()
        {
            ztimedmap::iterator it;
            if (fDelete && ((it = GUI::gTimedZoneMap.find(fZone)) != GUI::gTimedZoneMap.end())) {
                ringbuffer_free((*it).second);
                GUI::gTimedZoneMap.erase(it);
            }
        }
        
        virtual void modifyZone(double date, FAUSTFLOAT v)
        {
            size_t res;
            DatedControl dated_val(date, v);
            if ((res = ringbuffer_write(GUI::gTimedZoneMap[fZone], (const char*)&dated_val, sizeof(DatedControl))) != sizeof(DatedControl)) {
                fprintf(stderr, "ringbuffer_write error DatedControl\n");
            }
        }
    
};

/**
 * Allows to group a set of zones.
 */
class uiGroupItem : public uiItem
{
    protected:
    
        std::vector<FAUSTFLOAT*> fZoneMap;

    public:
    
        uiGroupItem(GUI* ui, FAUSTFLOAT* zone):uiItem(ui, zone)
        {}
        virtual ~uiGroupItem() 
        {}
        
        virtual void reflectZone() 
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            
            // Update all zones of the same group
            for (const auto& it : fZoneMap) {
                *it = v;
            }
        }
        
        void addZone(FAUSTFLOAT* zone) { fZoneMap.push_back(zone); }

};

// Cannot be defined as method in the classes.

static void createUiCallbackItem(GUI* ui, FAUSTFLOAT* zone, uiCallback foo, void* data)
{
    new uiCallbackItem(ui, zone, foo, data);
}

static void deleteClist(clist* cl)
{
    for (const auto& it : *cl) {
        // This specific code is only used in JUCE context. TODO: use proper 'shared_ptr' based memory management.
    #if defined(JUCE_32BIT) || defined(JUCE_64BIT)
        uiOwnedItem* owned = dynamic_cast<uiOwnedItem*>(it);
        // owned items are deleted by external code
        if (!owned) {
            delete it;
        }
    #else
        delete it;
    #endif
    }
}

#endif
/**************************  END  GUI.h **************************/
/************************** BEGIN JSONUI.h *****************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef FAUST_JSONUI_H
#define FAUST_JSONUI_H

#include <vector>
#include <map>
#include <string>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <limits>


/*******************************************************************************
 * JSONUI : Faust User Interface
 * This class produce a complete JSON decription of the DSP instance.
 ******************************************************************************/

typedef std::vector<std::tuple<std::string, int, int, int, int, int>> MemoryLayoutType;
typedef std::map<std::string, int> PathTableType;

template <typename REAL>
class JSONUIReal : public PathBuilder, public Meta, public UIReal<REAL>
{

    protected:
    
        std::stringstream fUI;
        std::stringstream fMeta;
        std::vector<std::pair <std::string, std::string> > fMetaAux;
        std::string fVersion;           // Compiler version
        std::string fCompileOptions;    // Compilation options
        std::vector<std::string> fLibraryList;
        std::vector<std::string> fIncludePathnames;
        std::string fName;
        std::string fFileName;
        std::string fExpandedCode;
        std::string fSHAKey;
        int fDSPSize;                   // In bytes
        PathTableType fPathTable;
        MemoryLayoutType fMemoryLayout;
        bool fExtended;
    
        char fCloseUIPar;
        char fCloseMetaPar;
        int fTab;
    
        int fInputs, fOutputs, fSRIndex;
         
        void tab(int n, std::ostream& fout)
        {
            fout << '\n';
            while (n-- > 0) {
                fout << '\t';
            }
        }
    
        std::string flatten(const std::string& src)
        {
            std::string dst;
            for (size_t i = 0; i < src.size(); i++) {
                switch (src[i]) {
                    case '\n':
                    case '\t':
                        break;
                    default:
                        dst += src[i];
                        break;
                }
            }
            return dst;
        }
    
        void addMeta(int tab_val, bool quote = true)
        {
            if (fMetaAux.size() > 0) {
                tab(tab_val, fUI); fUI << "\"meta\": [";
                std::string sep = "";
                for (size_t i = 0; i < fMetaAux.size(); i++) {
                    fUI << sep;
                    tab(tab_val + 1, fUI); fUI << "{ \"" << fMetaAux[i].first << "\": \"" << fMetaAux[i].second << "\" }";
                    sep = ",";
                }
                tab(tab_val, fUI); fUI << ((quote) ? "],": "]");
                fMetaAux.clear();
            }
        }
    
        int getAddressIndex(const std::string& path)
        {
            return (fPathTable.find(path) != fPathTable.end()) ? fPathTable[path] : -1;
        }
      
     public:
     
        JSONUIReal(const std::string& name,
                  const std::string& filename,
                  int inputs,
                  int outputs,
                  int sr_index,
                  const std::string& sha_key,
                  const std::string& dsp_code,
                  const std::string& version,
                  const std::string& compile_options,
                  const std::vector<std::string>& library_list,
                  const std::vector<std::string>& include_pathnames,
                  int size,
                  const PathTableType& path_table,
                  MemoryLayoutType memory_layout)
        {
            init(name, filename, inputs, outputs, sr_index, sha_key, dsp_code, version, compile_options, library_list, include_pathnames, size, path_table, memory_layout);
        }

        JSONUIReal(const std::string& name, const std::string& filename, int inputs, int outputs)
        {
            init(name, filename, inputs, outputs, -1, "", "", "", "", std::vector<std::string>(), std::vector<std::string>(), -1, PathTableType(), MemoryLayoutType());
        }

        JSONUIReal(int inputs, int outputs)
        {
            init("", "", inputs, outputs, -1, "", "","", "", std::vector<std::string>(), std::vector<std::string>(), -1, PathTableType(), MemoryLayoutType());
        }
        
        JSONUIReal()
        {
            init("", "", -1, -1, -1, "", "", "", "", std::vector<std::string>(), std::vector<std::string>(), -1, PathTableType(), MemoryLayoutType());
        }
 
        virtual ~JSONUIReal() {}
        
        void setInputs(int inputs) { fInputs = inputs; }
        void setOutputs(int outputs) { fOutputs = outputs; }
    
        void setSRIndex(int sr_index) { fSRIndex = sr_index; }
    
        // Init may be called multiple times so fMeta and fUI are reinitialized
        void init(const std::string& name,
                  const std::string& filename,
                  int inputs,
                  int outputs,
                  int sr_index,
                  const std::string& sha_key,
                  const std::string& dsp_code,
                  const std::string& version,
                  const std::string& compile_options,
                  const std::vector<std::string>& library_list,
                  const std::vector<std::string>& include_pathnames,
                  int size,
                  const PathTableType& path_table,
                  MemoryLayoutType memory_layout,
                  bool extended = false)
        {
            fTab = 1;
            fExtended = extended;
            if (fExtended) {
                fUI << std::setprecision(std::numeric_limits<REAL>::max_digits10);
                fMeta << std::setprecision(std::numeric_limits<REAL>::max_digits10);
            }
            
            // Start Meta generation
            fMeta.str("");
            tab(fTab, fMeta); fMeta << "\"meta\": [";
            fCloseMetaPar = ' ';
            
            // Start UI generation
            fUI.str("");
            tab(fTab, fUI); fUI << "\"ui\": [";
            fCloseUIPar = ' ';
            fTab += 1;
            
            fName = name;
            fFileName = filename;
            fInputs = inputs;
            fOutputs = outputs;
            fSRIndex = sr_index;
            fExpandedCode = dsp_code;
            fSHAKey = sha_key;
            fDSPSize = size;
            fPathTable = path_table;
            fVersion = version;
            fCompileOptions = compile_options;
            fLibraryList = library_list;
            fIncludePathnames = include_pathnames;
            fMemoryLayout = memory_layout;
        }
   
        // -- widget's layouts
    
        virtual void openGenericGroup(const char* label, const char* name)
        {
            pushLabel(label);
            fUI << fCloseUIPar;
            tab(fTab, fUI); fUI << "{";
            fTab += 1;
            tab(fTab, fUI); fUI << "\"type\": \"" << name << "\",";
            tab(fTab, fUI); fUI << "\"label\": \"" << label << "\",";
            addMeta(fTab);
            tab(fTab, fUI); fUI << "\"items\": [";
            fCloseUIPar = ' ';
            fTab += 1;
        }

        virtual void openTabBox(const char* label)
        {
            openGenericGroup(label, "tgroup");
        }
    
        virtual void openHorizontalBox(const char* label)
        {
            openGenericGroup(label, "hgroup");
        }
    
        virtual void openVerticalBox(const char* label)
        {
            openGenericGroup(label, "vgroup");
        }
    
        virtual void closeBox()
        {
            popLabel();
            fTab -= 1;
            tab(fTab, fUI); fUI << "]";
            fTab -= 1;
            tab(fTab, fUI); fUI << "}";
            fCloseUIPar = ',';
        }
    
        // -- active widgets
  
        virtual void addGenericButton(const char* label, const char* name)
        {
            std::string path = buildPath(label);
            
            fUI << fCloseUIPar;
            tab(fTab, fUI); fUI << "{";
            fTab += 1;
            tab(fTab, fUI); fUI << "\"type\": \"" << name << "\",";
            tab(fTab, fUI); fUI << "\"label\": \"" << label << "\",";
            if (fPathTable.size() > 0) {
                tab(fTab, fUI); fUI << "\"address\": \"" << path << "\",";
                tab(fTab, fUI); fUI << "\"index\": " << getAddressIndex(path) << ((fMetaAux.size() > 0) ? "," : "");
            } else {
                tab(fTab, fUI); fUI << "\"address\": \"" << path << "\"" << ((fMetaAux.size() > 0) ? "," : "");
            }
            addMeta(fTab, false);
            fTab -= 1;
            tab(fTab, fUI); fUI << "}";
            fCloseUIPar = ',';
        }

        virtual void addButton(const char* label, REAL* zone)
        {
            addGenericButton(label, "button");
        }
    
        virtual void addCheckButton(const char* label, REAL* zone)
        {
            addGenericButton(label, "checkbox");
        }

        virtual void addGenericEntry(const char* label, const char* name, REAL init, REAL min, REAL max, REAL step)
        {
            std::string path = buildPath(label);
            
            fUI << fCloseUIPar;
            tab(fTab, fUI); fUI << "{";
            fTab += 1;
            tab(fTab, fUI); fUI << "\"type\": \"" << name << "\",";
            tab(fTab, fUI); fUI << "\"label\": \"" << label << "\",";
            tab(fTab, fUI); fUI << "\"address\": \"" << path << "\",";
            if (fPathTable.size() > 0) {
                tab(fTab, fUI); fUI << "\"index\": " << getAddressIndex(path) << ",";
            }
            addMeta(fTab);
            tab(fTab, fUI); fUI << "\"init\": " << init << ",";
            tab(fTab, fUI); fUI << "\"min\": " << min << ",";
            tab(fTab, fUI); fUI << "\"max\": " << max << ",";
            tab(fTab, fUI); fUI << "\"step\": " << step;
            fTab -= 1;
            tab(fTab, fUI); fUI << "}";
            fCloseUIPar = ',';
        }
    
        virtual void addVerticalSlider(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step)
        {
            addGenericEntry(label, "vslider", init, min, max, step);
        }
    
        virtual void addHorizontalSlider(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step)
        {
            addGenericEntry(label, "hslider", init, min, max, step);
        }
    
        virtual void addNumEntry(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step)
        {
            addGenericEntry(label, "nentry", init, min, max, step);
        }

        // -- passive widgets
    
        virtual void addGenericBargraph(const char* label, const char* name, REAL min, REAL max) 
        {
            std::string path = buildPath(label);
            
            fUI << fCloseUIPar;
            tab(fTab, fUI); fUI << "{";
            fTab += 1;
            tab(fTab, fUI); fUI << "\"type\": \"" << name << "\",";
            tab(fTab, fUI); fUI << "\"label\": \"" << label << "\",";
            tab(fTab, fUI); fUI << "\"address\": \"" << path << "\",";
            if (fPathTable.size() > 0) {
                tab(fTab, fUI); fUI << "\"index\": " << getAddressIndex(path) << ",";
            }
            addMeta(fTab);
            tab(fTab, fUI); fUI << "\"min\": " << min << ",";
            tab(fTab, fUI); fUI << "\"max\": " << max;
            fTab -= 1;
            tab(fTab, fUI); fUI << "}";
            fCloseUIPar = ',';
        }

        virtual void addHorizontalBargraph(const char* label, REAL* zone, REAL min, REAL max) 
        {
            addGenericBargraph(label, "hbargraph", min, max);
        }
    
        virtual void addVerticalBargraph(const char* label, REAL* zone, REAL min, REAL max)
        {
            addGenericBargraph(label, "vbargraph", min, max);
        }
    
        virtual void addSoundfile(const char* label, const char* url, Soundfile** zone)
        {
            std::string path = buildPath(label);
            
            fUI << fCloseUIPar;
            tab(fTab, fUI); fUI << "{";
            fTab += 1;
            tab(fTab, fUI); fUI << "\"type\": \"" << "soundfile" << "\",";
            tab(fTab, fUI); fUI << "\"label\": \"" << label << "\"" << ",";
            tab(fTab, fUI); fUI << "\"url\": \"" << url << "\"" << ",";
            tab(fTab, fUI); fUI << "\"address\": \"" << path << "\"" << ((fPathTable.size() > 0) ? "," : "");
            if (fPathTable.size() > 0) {
                tab(fTab, fUI); fUI << "\"index\": " << getAddressIndex(path);
            }
            fTab -= 1;
            tab(fTab, fUI); fUI << "}";
            fCloseUIPar = ',';
        }

        // -- metadata declarations

        virtual void declare(REAL* zone, const char* key, const char* val)
        {
            fMetaAux.push_back(std::make_pair(key, val));
        }
    
        // Meta interface
        virtual void declare(const char* key, const char* value)
        {
            fMeta << fCloseMetaPar;
            // fName found in metadata
            if ((strcmp(key, "name") == 0) && (fName == "")) fName = value;
            // fFileName found in metadata
            if ((strcmp(key, "filename") == 0) && (fFileName == "")) fFileName = value;
            tab(fTab, fMeta); fMeta << "{ " << "\"" << key << "\"" << ": " << "\"" << value << "\" }";
            fCloseMetaPar = ',';
        }
    
        std::string JSON(bool flat = false)
        {
            fTab = 0;
            std::stringstream JSON;
            if (fExtended) {
                JSON << std::setprecision(std::numeric_limits<REAL>::max_digits10);
            }
            JSON << "{";
            fTab += 1;
            tab(fTab, JSON); JSON << "\"name\": \"" << fName << "\",";
            tab(fTab, JSON); JSON << "\"filename\": \"" << fFileName << "\",";
            if (fVersion != "") { tab(fTab, JSON); JSON << "\"version\": \"" << fVersion << "\","; }
            if (fCompileOptions != "") { tab(fTab, JSON); JSON << "\"compile_options\": \"" <<  fCompileOptions << "\","; }
            if (fLibraryList.size() > 0) {
                tab(fTab, JSON);
                JSON << "\"library_list\": [";
                for (size_t i = 0; i < fLibraryList.size(); i++) {
                    JSON << "\"" << fLibraryList[i] << "\"";
                    if (i < (fLibraryList.size() - 1)) JSON << ",";
                }
                JSON << "],";
            }
            if (fIncludePathnames.size() > 0) {
                tab(fTab, JSON);
                JSON << "\"include_pathnames\": [";
                for (size_t i = 0; i < fIncludePathnames.size(); i++) {
                    JSON << "\"" << fIncludePathnames[i] << "\"";
                    if (i < (fIncludePathnames.size() - 1)) JSON << ",";
                }
                JSON << "],";
            }
            if (fMemoryLayout.size() > 0) {
                tab(fTab, JSON);
                JSON << "\"memory_layout\": [";
                for (size_t i = 0; i < fMemoryLayout.size(); i++) {
                    // DSP or field name, type, size, sizeBytes, reads, writes
                    std::tuple<std::string, int, int, int, int, int> item = fMemoryLayout[i];
                    tab(fTab + 1, JSON);
                    JSON << "{\"size\": " << std::get<3>(item) << ", ";
                    JSON << "\"reads\": " << std::get<4>(item) << ", ";
                    JSON << "\"writes\": " << std::get<5>(item) << "}";
                    if (i < (fMemoryLayout.size() - 1)) JSON << ",";
                }
                tab(fTab, JSON);
                JSON << "],";
            }
            if (fDSPSize != -1) { tab(fTab, JSON); JSON << "\"size\": " << fDSPSize << ","; }
            if (fSHAKey != "") { tab(fTab, JSON); JSON << "\"sha_key\": \"" << fSHAKey << "\","; }
            if (fExpandedCode != "") { tab(fTab, JSON); JSON << "\"code\": \"" << fExpandedCode << "\","; }
            tab(fTab, JSON); JSON << "\"inputs\": " << fInputs << ",";
            tab(fTab, JSON); JSON << "\"outputs\": " << fOutputs << ",";
            if (fSRIndex != -1) { tab(fTab, JSON); JSON << "\"sr_index\": " << fSRIndex << ","; }
            tab(fTab, fMeta); fMeta << "],";
            tab(fTab, fUI); fUI << "]";
            fTab -= 1;
            if (fCloseMetaPar == ',') { // If "declare" has been called, fCloseMetaPar state is now ','
                JSON << fMeta.str() << fUI.str();
            } else {
                JSON << fUI.str();
            }
            tab(fTab, JSON); JSON << "}";
            return (flat) ? flatten(JSON.str()) : JSON.str();
        }
    
};

// Externally available class using FAUSTFLOAT

struct JSONUI : public JSONUIReal<FAUSTFLOAT>, public UI
{
    
    JSONUI(const std::string& name,
           const std::string& filename,
           int inputs,
           int outputs,
           int sr_index,
           const std::string& sha_key,
           const std::string& dsp_code,
           const std::string& version,
           const std::string& compile_options,
           const std::vector<std::string>& library_list,
           const std::vector<std::string>& include_pathnames,
           int size,
           const PathTableType& path_table,
           MemoryLayoutType memory_layout):
    JSONUIReal<FAUSTFLOAT>(name, filename,
                          inputs, outputs,
                          sr_index,
                          sha_key, dsp_code,
                          version, compile_options,
                          library_list, include_pathnames,
                          size, path_table, memory_layout)
    {}
    
    JSONUI(const std::string& name, const std::string& filename, int inputs, int outputs):
    JSONUIReal<FAUSTFLOAT>(name, filename, inputs, outputs)
    {}
    
    JSONUI(int inputs, int outputs):JSONUIReal<FAUSTFLOAT>(inputs, outputs)
    {}
    
    JSONUI():JSONUIReal<FAUSTFLOAT>()
    {}

    virtual void openTabBox(const char* label)
    {
        JSONUIReal<FAUSTFLOAT>::openTabBox(label);
    }
    virtual void openHorizontalBox(const char* label)
    {
        JSONUIReal<FAUSTFLOAT>::openHorizontalBox(label);
    }
    virtual void openVerticalBox(const char* label)
    {
        JSONUIReal<FAUSTFLOAT>::openVerticalBox(label);
    }
    virtual void closeBox()
    {
        JSONUIReal<FAUSTFLOAT>::closeBox();
    }
    
    // -- active widgets
    
    virtual void addButton(const char* label, FAUSTFLOAT* zone)
    {
        JSONUIReal<FAUSTFLOAT>::addButton(label, zone);
    }
    virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)
    {
        JSONUIReal<FAUSTFLOAT>::addCheckButton(label, zone);
    }
    virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        JSONUIReal<FAUSTFLOAT>::addVerticalSlider(label, zone, init, min, max, step);
    }
    virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        JSONUIReal<FAUSTFLOAT>::addHorizontalSlider(label, zone, init, min, max, step);
    }
    virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        JSONUIReal<FAUSTFLOAT>::addNumEntry(label, zone, init, min, max, step);
    }
    
    // -- passive widgets
    
    virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
    {
        JSONUIReal<FAUSTFLOAT>::addHorizontalBargraph(label, zone, min, max);
    }
    virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
    {
        JSONUIReal<FAUSTFLOAT>::addVerticalBargraph(label, zone, min, max);
    }
    
    // -- soundfiles
    
    virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone)
    {
        JSONUIReal<FAUSTFLOAT>::addSoundfile(label, filename, sf_zone);
    }
    
    // -- metadata declarations
    
    virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val)
    {
        JSONUIReal<FAUSTFLOAT>::declare(zone, key, val);
    }

    virtual void declare(const char* key, const char* val)
    {
        JSONUIReal<FAUSTFLOAT>::declare(key, val);
    }

    virtual ~JSONUI() {}
    
};

#endif // FAUST_JSONUI_H
/**************************  END  JSONUI.h **************************/
/************************** BEGIN midi.h *******************************
FAUST Architecture File
Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
---------------------------------------------------------------------
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

EXCEPTION : As a special exception, you may create a larger work
that contains this FAUST architecture section and distribute
that work under terms of your choice, so long as this FAUST
architecture section is not modified.
************************************************************************/

#ifndef __midi__
#define __midi__

#include <vector>
#include <string>
#include <algorithm>
#include <assert.h>

class MapUI;

/**
 * A timestamped short MIDI message used with SOUL.
 */

// Force contiguous memory layout
#pragma pack (push, 1)
struct MIDIMessage
{
    uint32_t frameIndex;
    uint8_t byte0, byte1, byte2;
};
#pragma pack (pop)

/**
 * For timestamped MIDI messages.
 */
struct DatedMessage {
    
    double fDate;
    unsigned char fBuffer[3];
    size_t fSize;
    
    DatedMessage(double date, unsigned char* buffer, size_t size)
    :fDate(date), fSize(size)
    {
        assert(size <= 3);
        memcpy(fBuffer, buffer, size);
    }
    
    DatedMessage():fDate(0.0), fSize(0)
    {}
    
};

/**
 * MIDI processor definition.
 *
 * MIDI input or output handling classes will implement this interface,
 * so the same method names (keyOn, keyOff, ctrlChange...) will be used either
 * when decoding MIDI input or encoding MIDI output events.
 * MIDI channel is numbered in [0..15] in this layer.
 */
class midi {

    public:

        midi() {}
        virtual ~midi() {}

        // Additional time-stamped API for MIDI input
        virtual MapUI* keyOn(double, int channel, int pitch, int velocity)
        {
            return keyOn(channel, pitch, velocity);
        }
        
        virtual void keyOff(double, int channel, int pitch, int velocity = 0)
        {
            keyOff(channel, pitch, velocity);
        }
    
        virtual void keyPress(double, int channel, int pitch, int press)
        {
            keyPress(channel, pitch, press);
        }
        
        virtual void chanPress(double date, int channel, int press)
        {
            chanPress(channel, press);
        }
    
        virtual void pitchWheel(double, int channel, int wheel)
        {
            pitchWheel(channel, wheel);
        }
           
        virtual void ctrlChange(double, int channel, int ctrl, int value)
        {
            ctrlChange(channel, ctrl, value);
        }
    
        virtual void ctrlChange14bits(double, int channel, int ctrl, int value)
        {
            ctrlChange14bits(channel, ctrl, value);
        }
    
        virtual void rpn(double, int channel, int ctrl, int value)
        {
            rpn(channel, ctrl, value);
        }

        virtual void progChange(double, int channel, int pgm)
        {
            progChange(channel, pgm);
        }
    
        virtual void sysEx(double, std::vector<unsigned char>& message)
        {
            sysEx(message);
        }

        // MIDI sync
        virtual void startSync(double date)  {}
        virtual void stopSync(double date)   {}
        virtual void clock(double date)  {}

        // Standard MIDI API
        virtual MapUI* keyOn(int channel, int pitch, int velocity)      { return nullptr; }
        virtual void keyOff(int channel, int pitch, int velocity)       {}
        virtual void keyPress(int channel, int pitch, int press)        {}
        virtual void chanPress(int channel, int press)                  {}
        virtual void ctrlChange(int channel, int ctrl, int value)       {}
        virtual void ctrlChange14bits(int channel, int ctrl, int value) {}
        virtual void rpn(int channel, int ctrl, int value)              {}
        virtual void pitchWheel(int channel, int wheel)                 {}
        virtual void progChange(int channel, int pgm)                   {}
        virtual void sysEx(std::vector<unsigned char>& message)         {}

        enum MidiStatus {
            // channel voice messages
            MIDI_NOTE_OFF = 0x80,
            MIDI_NOTE_ON = 0x90,
            MIDI_CONTROL_CHANGE = 0xB0,
            MIDI_PROGRAM_CHANGE = 0xC0,
            MIDI_PITCH_BEND = 0xE0,
            MIDI_AFTERTOUCH = 0xD0,         // aka channel pressure
            MIDI_POLY_AFTERTOUCH = 0xA0,    // aka key pressure
            MIDI_CLOCK = 0xF8,
            MIDI_START = 0xFA,
            MIDI_CONT = 0xFB,
            MIDI_STOP = 0xFC,
            MIDI_SYSEX_START = 0xF0,
            MIDI_SYSEX_STOP = 0xF7
        };

        enum MidiCtrl {
            ALL_NOTES_OFF = 123,
            ALL_SOUND_OFF = 120
        };
    
        enum MidiNPN {
            PITCH_BEND_RANGE = 0
        };

};

/**
 * A class to decode NRPN and RPN messages, adapted from JUCE forum message:
 * https://forum.juce.com/t/14bit-midi-controller-support/11517
 */
class MidiNRPN {
    
    private:
    
        bool ctrlnew;
        int ctrlnum;
        int ctrlval;
        
        int nrpn_lsb, nrpn_msb;
        int data_lsb, data_msb;
        
        enum
        {
            midi_nrpn_lsb = 98,
            midi_nrpn_msb = 99,
            midi_rpn_lsb  = 100,
            midi_rpn_msb  = 101,
            midi_data_lsb = 38,
            midi_data_msb = 6
        };
    
    public:
        
        MidiNRPN(): ctrlnew(false), nrpn_lsb(-1), nrpn_msb(-1), data_lsb(-1), data_msb(-1)
        {}
        
        // return true if the message has been filtered
        bool process(int data1, int data2)
        {
            switch (data1)
            {
                case midi_nrpn_lsb: nrpn_lsb = data2; return true;
                case midi_nrpn_msb: nrpn_msb = data2; return true;
                case midi_rpn_lsb: {
                    if (data2 == 127) {
                        nrpn_lsb = data_lsb = -1;
                    } else {
                        nrpn_lsb = 0;
                        data_lsb = -1;
                    }
                    return true;
                }
                case midi_rpn_msb: {
                    if (data2 == 127) {
                        nrpn_msb = data_msb = -1;
                    } else {
                        nrpn_msb = 0;
                        data_msb = -1;
                    }
                    return true;
                }
                case midi_data_lsb:
                case midi_data_msb:
                {
                    if (data1 == midi_data_msb) {
                        if (nrpn_msb < 0) {
                            return false;
                        }
                        data_msb = data2;
                    } else { // midi_data_lsb
                        if (nrpn_lsb < 0) {
                            return false;
                        }
                        data_lsb = data2;
                    }
                    if (data_lsb >= 0 && data_msb >= 0) {
                        ctrlnum = (nrpn_msb << 7) | nrpn_lsb;
                        ctrlval = (data_msb << 7) | data_lsb;
                        data_lsb = data_msb = -1;
                        nrpn_msb = nrpn_lsb = -1;
                        ctrlnew = true;
                    }
                    return true;
                }
                default: return false;
            };
        }
        
        bool hasNewNRPN() { bool res = ctrlnew; ctrlnew = false; return res; }
        
        // results in [0, 16383]
        int getCtrl() const { return ctrlnum; }
        int getVal() const { return ctrlval; }
    
};

/**
 * A pure interface for MIDI handlers that can send/receive MIDI messages to/from 'midi' objects.
 */
struct midi_interface {
    virtual void addMidiIn(midi* midi_dsp)      = 0;
    virtual void removeMidiIn(midi* midi_dsp)   = 0;
    virtual ~midi_interface() {}
};

/****************************************************
 * Base class for MIDI input handling.
 *
 * Shared common code used for input handling:
 * - decoding Real-Time messages: handleSync
 * - decoding one data byte messages: handleData1
 * - decoding two data byte messages: handleData2
 * - getting ready messages in polling mode
 ****************************************************/
class midi_handler : public midi, public midi_interface {

    protected:

        std::vector<midi*> fMidiInputs;
        std::string fName;
        MidiNRPN fNRPN;
    
        int range(int min, int max, int val) { return (val < min) ? min : ((val >= max) ? max : val); }
  
    public:

        midi_handler(const std::string& name = "MIDIHandler"):midi_interface(), fName(name) {}
        virtual ~midi_handler() {}

        void addMidiIn(midi* midi_dsp) { if (midi_dsp) fMidiInputs.push_back(midi_dsp); }
        void removeMidiIn(midi* midi_dsp)
        {
            std::vector<midi*>::iterator it = std::find(fMidiInputs.begin(), fMidiInputs.end(), midi_dsp);
            if (it != fMidiInputs.end()) {
                fMidiInputs.erase(it);
            }
        }

        // Those 2 methods have to be implemented by subclasses
        virtual bool startMidi() { return true; }
        virtual void stopMidi() {}
    
        void setName(const std::string& name) { fName = name; }
        std::string getName() { return fName; }
    
        // To be used in polling mode
        virtual int recvMessages(std::vector<MIDIMessage>* message) { return 0; }
        virtual void sendMessages(std::vector<MIDIMessage>* message, int count) {}
    
        // MIDI Real-Time
        void handleClock(double time)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->clock(time);
            }
        }
        
        void handleStart(double time)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->startSync(time);
            }
        }
        
        void handleStop(double time)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->stopSync(time);
            }
        }
    
        void handleSync(double time, int type)
        {
            if (type == MIDI_CLOCK) {
                handleClock(time);
            // We can consider start and continue as identical messages
            } else if ((type == MIDI_START) || (type == MIDI_CONT)) {
                handleStart(time);
            } else if (type == MIDI_STOP) {
                handleStop(time);
            }
        }
    
        // MIDI 1 data
        void handleProgChange(double time, int channel, int data1)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->progChange(time, channel, data1);
            }
        }
    
        void handleAfterTouch(double time, int channel, int data1)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->chanPress(time, channel, data1);
            }
        }

        void handleData1(double time, int type, int channel, int data1)
        {
            if (type == MIDI_PROGRAM_CHANGE) {
                handleProgChange(time, channel, data1);
            } else if (type == MIDI_AFTERTOUCH) {
                handleAfterTouch(time, channel, data1);
            }
        }
    
        // MIDI 2 datas
        void handleKeyOff(double time, int channel, int data1, int data2)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->keyOff(time, channel, data1, data2);
            }
        }
        
        void handleKeyOn(double time, int channel, int data1, int data2)
        {
            if (data2 == 0) {
                handleKeyOff(time, channel, data1, data2);
            } else {
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    fMidiInputs[i]->keyOn(time, channel, data1, data2);
                }
            }
        }
    
        void handleCtrlChange(double time, int channel, int data1, int data2)
        {
            // Special processing for NRPN and RPN
            if (fNRPN.process(data1, data2)) {
                if (fNRPN.hasNewNRPN()) {
                    for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                        fMidiInputs[i]->rpn(time, channel, fNRPN.getCtrl(), fNRPN.getVal());
                    }
                }
            } else {
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    fMidiInputs[i]->ctrlChange(time, channel, data1, data2);
                }
            }
        }
        
        void handlePitchWheel(double time, int channel, int data1, int data2)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->pitchWheel(time, channel, (data2 << 7) + data1);
            }
        }
    
        void handlePitchWheel(double time, int channel, int bend)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->pitchWheel(time, channel, bend);
            }
        }
        
        void handlePolyAfterTouch(double time, int channel, int data1, int data2)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->keyPress(time, channel, data1, data2);
            }
        }
  
        void handleData2(double time, int type, int channel, int data1, int data2)
        {
            if (type == MIDI_NOTE_OFF) {
                handleKeyOff(time, channel,  data1, data2);
            } else if (type == MIDI_NOTE_ON) {
                handleKeyOn(time, channel, data1, data2);
            } else if (type == MIDI_CONTROL_CHANGE) {
                handleCtrlChange(time, channel, data1, data2);
            } else if (type == MIDI_PITCH_BEND) {
                handlePitchWheel(time, channel, data1, data2);
            } else if (type == MIDI_POLY_AFTERTOUCH) {
                handlePolyAfterTouch(time, channel, data1, data2);
            }
        }
    
        // SysEx
        void handleSysex(double time, std::vector<unsigned char>& message)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->sysEx(time, message);
            }
        }
    
        void handleMessage(double time, int type, std::vector<unsigned char>& message)
        {
            if (type == MIDI_SYSEX_START) {
                handleSysex(time, message);
            }
        }
  
};

#endif // __midi__
/**************************  END  midi.h **************************/

#ifdef _MSC_VER
#define gsscanf sscanf_s
#else
#define gsscanf sscanf
#endif

/**
 * Helper code for MIDI meta and polyphonic 'nvoices' parsing.
 */
struct MidiMeta : public Meta, public std::map<std::string, std::string> {
    
    void declare(const char* key, const char* value)
    {
        (*this)[key] = value;
    }
    
    const std::string get(const char* key, const char* def)
    {
        return (this->find(key) != this->end()) ? (*this)[key] : def;
    }
    
    static void analyse(base_dsp* mono_dsp, bool& midi_sync, int& nvoices)
    {
        JSONUI jsonui;
        mono_dsp->buildUserInterface(&jsonui);
        std::string json = jsonui.JSON();
        midi_sync = ((json.find("midi") != std::string::npos) &&
                     ((json.find("start") != std::string::npos) ||
                      (json.find("stop") != std::string::npos) ||
                      (json.find("clock") != std::string::npos) ||
                      (json.find("timestamp") != std::string::npos)));
    
    #if defined(NVOICES) && NVOICES!=NUM_VOICES
        nvoices = NVOICES;
    #else
        MidiMeta meta;
        mono_dsp->metadata(&meta);
        bool found_voices = false;
        // If "options" metadata is used
        std::string options = meta.get("options", "");
        if (options != "") {
            std::map<std::string, std::string> metadata;
            std::string res;
            MetaDataUI::extractMetadata(options, res, metadata);
            if (metadata.find("nvoices") != metadata.end()) {
                nvoices = std::atoi(metadata["nvoices"].c_str());
                found_voices = true;
            }
        }
        // Otherwise test for "nvoices" metadata
        if (!found_voices) {
            std::string numVoices = meta.get("nvoices", "0");
            nvoices = std::atoi(numVoices.c_str());
        }
        nvoices = std::max<int>(0, nvoices);
    #endif
    }
    
    static bool checkPolyphony(base_dsp* mono_dsp)
    {
        MapUI map_ui;
        mono_dsp->buildUserInterface(&map_ui);
        bool has_freq = false;
        bool has_gate = false;
        bool has_gain = false;
        for (int i = 0; i < map_ui.getParamsCount(); i++) {
            std::string path = map_ui.getParamAddress(i);
            has_freq |= MapUI::endsWith(path, "/freq");
            has_gate |= MapUI::endsWith(path, "/gate");
            has_gain |= MapUI::endsWith(path, "/gain");
        }
        return (has_freq && has_gate && has_gain);
    }
    
};

/**
 * uiMidi : Faust User Interface
 * This class decodes MIDI meta data and maps incoming MIDI messages to them.
 * Currently ctrlChange, keyOn/keyOff, keyPress, progChange, chanPress, pitchWheel/pitchBend
 * start/stop/clock meta data is handled.
 * MIDI channel is numbered in [1..16] in this layer.
 * Channel 0 means "all channels" when receiving or sending.
 */
class uiMidi {
    
    friend class MidiUI;
    
    protected:
        
        midi* fMidiOut;
        bool fInputCtrl;
        int fChan;
    
        bool inRange(FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT v) { return (min <= v && v <= max); }
    
    public:
        
        uiMidi(midi* midi_out, bool input, int chan = 0):fMidiOut(midi_out), fInputCtrl(input), fChan(chan)
        {}
        virtual ~uiMidi()
        {}

};

/**
 * Base class for MIDI aware UI items.
 */
class uiMidiItem : public uiMidi, public uiItem {
    
    public:
        
        uiMidiItem(midi* midi_out, GUI* ui, FAUSTFLOAT* zone, bool input = true, int chan = 0)
            :uiMidi(midi_out, input, chan), uiItem(ui, zone)
        {}
        virtual ~uiMidiItem()
        {}
    
        virtual void reflectZone() {}
    
};

/**
 * Base class for MIDI aware UI items with timestamp support.
 */
class uiMidiTimedItem : public uiMidi, public uiTimedItem {
    
    public:
        
        uiMidiTimedItem(midi* midi_out, GUI* ui, FAUSTFLOAT* zone, bool input = true, int chan = 0)
            :uiMidi(midi_out, input, chan), uiTimedItem(ui, zone)
        {}
        virtual ~uiMidiTimedItem()
        {}
    
        virtual void reflectZone() {}
    
};

/**
 * MIDI sync.
 */
class uiMidiStart : public uiMidiTimedItem
{
  
    public:
    
        uiMidiStart(midi* midi_out, GUI* ui, FAUSTFLOAT* zone, bool input = true)
            :uiMidiTimedItem(midi_out, ui, zone, input)
        {}
        virtual ~uiMidiStart()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (v != FAUSTFLOAT(0)) {
                fMidiOut->startSync(0);
            }
        }
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(v));
            }
        }
        
};

class uiMidiStop : public uiMidiTimedItem {
  
    public:
    
        uiMidiStop(midi* midi_out, GUI* ui, FAUSTFLOAT* zone, bool input = true)
            :uiMidiTimedItem(midi_out, ui, zone, input)
        {}
        virtual ~uiMidiStop()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (v != FAUSTFLOAT(1)) {
                fMidiOut->stopSync(0);
            }
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(v));
            }
        }
};

class uiMidiClock : public uiMidiTimedItem {

    private:
        
        bool fState;
  
    public:
    
        uiMidiClock(midi* midi_out, GUI* ui, FAUSTFLOAT* zone, bool input = true)
            :uiMidiTimedItem(midi_out, ui, zone, input), fState(false)
        {}
        virtual ~uiMidiClock()
        {}
    
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            fMidiOut->clock(0);
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                fState = !fState;
                uiMidiTimedItem::modifyZone(date, FAUSTFLOAT(fState));
            }
        }

};

/**
 * Standard MIDI events.
 */

/**
 * uiMidiProgChange uses the [min...max] range.
 */
class uiMidiProgChange : public uiMidiTimedItem {
    
    public:
    
        FAUSTFLOAT fMin, fMax;
    
        uiMidiProgChange(midi* midi_out, GUI* ui, FAUSTFLOAT* zone,
                         FAUSTFLOAT min, FAUSTFLOAT max,
                         bool input = true, int chan = 0)
            :uiMidiTimedItem(midi_out, ui, zone, input, chan), fMin(min), fMax(max)
        {}
        virtual ~uiMidiProgChange()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (inRange(fMin, fMax, v)) {
                if (fChan == 0) {
                    // Send on [0..15] channels on the MIDI layer
                    for (int chan = 0; chan < 16; chan++) {
                        fMidiOut->progChange(chan, v);
                    }
                } else {
                    fMidiOut->progChange(fChan - 1, v);
                }
            }
        }
    
        void modifyZone(FAUSTFLOAT v)
        {
            if (fInputCtrl && inRange(fMin, fMax, v)) {
                uiItem::modifyZone(v);
            }
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl && inRange(fMin, fMax, v)) {
                uiMidiTimedItem::modifyZone(date, v);
            }
        }
        
};

/**
 * uiMidiChanPress.
 */
class uiMidiChanPress : public uiMidiTimedItem, public uiConverter {
    
    public:
    
        uiMidiChanPress(midi* midi_out, GUI* ui,
                        FAUSTFLOAT* zone,
                        FAUSTFLOAT min, FAUSTFLOAT max,
                        bool input = true,
                        MetaDataUI::Scale scale = MetaDataUI::kLin,
                        int chan = 0)
            :uiMidiTimedItem(midi_out, ui, zone, input, chan), uiConverter(scale, 0., 127., min, max)
        {}
        virtual ~uiMidiChanPress()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (fChan == 0) {
                // Send on [0..15] channels on the MIDI layer
                for (int chan = 0; chan < 16; chan++) {
                    fMidiOut->chanPress(chan, fConverter->faust2ui(v));
                }
            } else {
                fMidiOut->chanPress(fChan - 1, fConverter->faust2ui(v));
            }
        }
    
        void modifyZone(FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiMidiTimedItem::modifyZone(date, FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
        
};

/**
 * uiMidiCtrlChange does scale (kLin/kLog/kExp) mapping.
 */
class uiMidiCtrlChange : public uiMidiTimedItem, public uiConverter {
    
    private:
    
        int fCtrl;
 
    public:

        uiMidiCtrlChange(midi* midi_out, int ctrl, GUI* ui,
                     FAUSTFLOAT* zone,
                     FAUSTFLOAT min, FAUSTFLOAT max,
                     bool input = true,
                     MetaDataUI::Scale scale = MetaDataUI::kLin,
                     int chan = 0)
            :uiMidiTimedItem(midi_out, ui, zone, input, chan), uiConverter(scale, 0., 127., min, max), fCtrl(ctrl)
        {}
        virtual ~uiMidiCtrlChange()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (fChan == 0) {
                // Send on [0..15] channels on the MIDI layer
                for (int chan = 0; chan < 16; chan++) {
                    fMidiOut->ctrlChange(chan, fCtrl, fConverter->faust2ui(v));
                }
            } else {
                fMidiOut->ctrlChange(fChan - 1, fCtrl, fConverter->faust2ui(v));
            }
        }
        
        void modifyZone(FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiMidiTimedItem::modifyZone(date, FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
};

class uiMidiPitchWheel : public uiMidiTimedItem {

    private:
    
        LinearValueConverter2 fConverter;
    
    public:
    
        uiMidiPitchWheel(midi* midi_out, GUI* ui, FAUSTFLOAT* zone,
                         FAUSTFLOAT min, FAUSTFLOAT max,
                         bool input = true, int chan = 0)
            :uiMidiTimedItem(midi_out, ui, zone, input, chan)
        {
            if (min <= 0 && max >= 0) {
                fConverter = LinearValueConverter2(0., 8191., 16383., double(min), 0., double(max));
            } else {
                // Degenerated case...
                fConverter = LinearValueConverter2(0., 8191., 16383., double(min),double(min + (max - min)/FAUSTFLOAT(2)), double(max));
            }
        }
    
        virtual ~uiMidiPitchWheel()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (fChan == 0) {
                // Send on [0..15] channels on the MIDI layer
                for (int chan = 0; chan < 16; chan++) {
                    fMidiOut->pitchWheel(chan, fConverter.faust2ui(v));
                }
            } else {
                fMidiOut->pitchWheel(fChan - 1, fConverter.faust2ui(v));
            }
        }
        
        void modifyZone(FAUSTFLOAT v)
        { 
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(fConverter.ui2faust(v)));
            }
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiMidiTimedItem::modifyZone(FAUSTFLOAT(fConverter.ui2faust(v)));
            }
        }
    
        void setRange(int val)
        {
            double semi = (val / 128) + ((val % 128) / 100.);
            fConverter.setMappingValues(0., 8191., 16383., -semi, 0., semi);
        }
 
};

/**
 * uiMidiKeyOn does scale (kLin/kLog/kExp) mapping for velocity.
 */
class uiMidiKeyOn : public uiMidiTimedItem, public uiConverter {

    private:
        
        int fKeyOn;
  
    public:
    
        uiMidiKeyOn(midi* midi_out, int key, GUI* ui,
                    FAUSTFLOAT* zone,
                    FAUSTFLOAT min, FAUSTFLOAT max,
                    bool input = true,
                    MetaDataUI::Scale scale = MetaDataUI::kLin,
                    int chan = 0)
            :uiMidiTimedItem(midi_out, ui, zone, input, chan), uiConverter(scale, 0., 127., min, max), fKeyOn(key)
        {}
        virtual ~uiMidiKeyOn()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (fChan == 0) {
                // Send on [0..15] channels on the MIDI layer
                for (int chan = 0; chan < 16; chan++) {
                    fMidiOut->keyOn(chan, fKeyOn, fConverter->faust2ui(v));
                }
            } else {
                fMidiOut->keyOn(fChan - 1, fKeyOn, fConverter->faust2ui(v));
            }
        }
        
        void modifyZone(FAUSTFLOAT v)
        { 
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiMidiTimedItem::modifyZone(date, FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
    
};

/**
 * uiMidiKeyOff does scale (kLin/kLog/kExp) mapping for velocity.
 */
class uiMidiKeyOff : public uiMidiTimedItem, public uiConverter {

    private:
        
        int fKeyOff;
  
    public:
    
        uiMidiKeyOff(midi* midi_out, int key, GUI* ui,
                     FAUSTFLOAT* zone,
                     FAUSTFLOAT min, FAUSTFLOAT max,
                     bool input = true,
                     MetaDataUI::Scale scale = MetaDataUI::kLin,
                     int chan = 0)
            :uiMidiTimedItem(midi_out, ui, zone, input, chan), uiConverter(scale, 0., 127., min, max), fKeyOff(key)
        {}
        virtual ~uiMidiKeyOff()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (fChan == 0) {
                // Send on [0..15] channels on the MIDI layer
                for (int chan = 0; chan < 16; chan++) {
                    fMidiOut->keyOn(chan, fKeyOff, fConverter->faust2ui(v));
                }
            } else {
                fMidiOut->keyOn(fChan - 1, fKeyOff, fConverter->faust2ui(v));
            }
        }
        
        void modifyZone(FAUSTFLOAT v)
        { 
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiMidiTimedItem::modifyZone(date, FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
    
};

/**
 * uiMidiKeyPress does scale (kLin/kLog/kExp) mapping for velocity.
 */
class uiMidiKeyPress : public uiMidiTimedItem, public uiConverter {

    private:
    
        int fKey;
  
    public:
    
        uiMidiKeyPress(midi* midi_out, int key, GUI* ui,
                       FAUSTFLOAT* zone,
                       FAUSTFLOAT min, FAUSTFLOAT max,
                       bool input = true,
                       MetaDataUI::Scale scale = MetaDataUI::kLin,
                       int chan = 0)
            :uiMidiTimedItem(midi_out, ui, zone, input, chan), uiConverter(scale, 0., 127., min, max), fKey(key)
        {}
        virtual ~uiMidiKeyPress()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (fChan == 0) {
                // Send on [0..15] channels on the MIDI layer
                for (int chan = 0; chan < 16; chan++) {
                    fMidiOut->keyOn(chan, fKey, fConverter->faust2ui(v));
                }
            } else {
                fMidiOut->keyOn(fChan - 1, fKey, fConverter->faust2ui(v));
            }
        }
        
        void modifyZone(FAUSTFLOAT v)
        { 
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiMidiTimedItem::modifyZone(date, FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
    
};

/******************************************************************************************
 * MidiUI : Faust User Interface
 * This class decodes MIDI metadata and maps incoming MIDI messages to them.
 * Currently ctrlChange, keyOn/keyOff, keyPress, progChange, chanPress, pitchWheel/pitchBend
 * start/stop/clock meta data are handled.
 *
 * Maps associating MIDI event ID (like each ctrl number) with all MIDI aware UI items
 * are defined and progressively filled when decoding MIDI related metadata.
 * MIDI aware UI items are used in both directions:
 *  - modifying their internal state when receving MIDI input events
 *  - sending their internal state as MIDI output events
 *******************************************************************************************/

class MidiUI : public GUI, public midi, public midi_interface, public MetaDataUI {

    // Add uiItem subclasses objects are deallocated by the inherited GUI class
    typedef std::map <int, std::vector<uiMidiCtrlChange*> > TCtrlChangeTable;
    typedef std::vector<uiMidiProgChange*>                  TProgChangeTable;
    typedef std::vector<uiMidiChanPress*>                   TChanPressTable;
    typedef std::map <int, std::vector<uiMidiKeyOn*> >      TKeyOnTable;
    typedef std::map <int, std::vector<uiMidiKeyOff*> >     TKeyOffTable;
    typedef std::map <int, std::vector<uiMidiKeyPress*> >   TKeyPressTable;
    typedef std::vector<uiMidiPitchWheel*>                  TPitchWheelTable;
    
    protected:
    
        TCtrlChangeTable fCtrlChangeTable;
        TProgChangeTable fProgChangeTable;
        TChanPressTable  fChanPressTable;
        TKeyOnTable      fKeyOnTable;
        TKeyOffTable     fKeyOffTable;
        TKeyOnTable      fKeyTable;
        TKeyPressTable   fKeyPressTable;
        TPitchWheelTable fPitchWheelTable;
        
        std::vector<uiMidiStart*> fStartTable;
        std::vector<uiMidiStop*>  fStopTable;
        std::vector<uiMidiClock*> fClockTable;
        
        std::vector<std::pair <std::string, std::string> > fMetaAux;
        
        midi_handler* fMidiHandler;
        bool fDelete;
        bool fTimeStamp;
    
        void addGenericZone(FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max, bool input = true)
        {
            if (fMetaAux.size() > 0) {
                for (size_t i = 0; i < fMetaAux.size(); i++) {
                    unsigned num;
                    unsigned chan;
                    if (fMetaAux[i].first == "midi") {
                        if (gsscanf(fMetaAux[i].second.c_str(), "ctrl %u %u", &num, &chan) == 2) {
                            fCtrlChangeTable[num].push_back(new uiMidiCtrlChange(fMidiHandler, num, this, zone, min, max, input, getScale(zone), chan));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "ctrl %u", &num) == 1) {
                            fCtrlChangeTable[num].push_back(new uiMidiCtrlChange(fMidiHandler, num, this, zone, min, max, input, getScale(zone)));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "keyon %u %u", &num, &chan) == 2) {
                            fKeyOnTable[num].push_back(new uiMidiKeyOn(fMidiHandler, num, this, zone, min, max, input, getScale(zone), chan));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "keyon %u", &num) == 1) {
                            fKeyOnTable[num].push_back(new uiMidiKeyOn(fMidiHandler, num, this, zone, min, max, input, getScale(zone)));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "keyoff %u %u", &num, &chan) == 2) {
                            fKeyOffTable[num].push_back(new uiMidiKeyOff(fMidiHandler, num, this, zone, min, max, input, getScale(zone), chan));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "keyoff %u", &num) == 1) {
                            fKeyOffTable[num].push_back(new uiMidiKeyOff(fMidiHandler, num, this, zone, min, max, input, getScale(zone)));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "key %u %u", &num, &chan) == 2) {
                            fKeyTable[num].push_back(new uiMidiKeyOn(fMidiHandler, num, this, zone, min, max, input, getScale(zone), chan));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "key %u", &num) == 1) {
                            fKeyTable[num].push_back(new uiMidiKeyOn(fMidiHandler, num, this, zone, min, max, input, getScale(zone)));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "keypress %u %u", &num, &chan) == 2) {
                            fKeyPressTable[num].push_back(new uiMidiKeyPress(fMidiHandler, num, this, zone, min, max, input, getScale(zone), chan));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "keypress %u", &num) == 1) {
                            fKeyPressTable[num].push_back(new uiMidiKeyPress(fMidiHandler, num, this, zone, min, max, input, getScale(zone)));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "pgm %u", &chan) == 1) {
                            fProgChangeTable.push_back(new uiMidiProgChange(fMidiHandler, this, zone, min, max, input, chan));
                        } else if (strcmp(fMetaAux[i].second.c_str(), "pgm") == 0) {
                            fProgChangeTable.push_back(new uiMidiProgChange(fMidiHandler, this, zone, min, max, input));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "chanpress %u", &chan) == 1) {
                            fChanPressTable.push_back(new uiMidiChanPress(fMidiHandler, this, zone, min, max, input, getScale(zone), chan));
                        } else if ((fMetaAux[i].second == "chanpress")) {
                            fChanPressTable.push_back(new uiMidiChanPress(fMidiHandler, this, zone, min, max, input, getScale(zone)));
                        } else if ((gsscanf(fMetaAux[i].second.c_str(), "pitchwheel %u", &chan) == 1) || (gsscanf(fMetaAux[i].second.c_str(), "pitchbend %u", &chan) == 1)) {
                            fPitchWheelTable.push_back(new uiMidiPitchWheel(fMidiHandler, this, zone, min, max, input, chan));
                        } else if ((fMetaAux[i].second == "pitchwheel") || (fMetaAux[i].second == "pitchbend")) {
                            fPitchWheelTable.push_back(new uiMidiPitchWheel(fMidiHandler, this, zone, min, max, input));
                        // MIDI sync
                        } else if (fMetaAux[i].second == "start") {
                            fStartTable.push_back(new uiMidiStart(fMidiHandler, this, zone, input));
                        } else if (fMetaAux[i].second == "stop") {
                            fStopTable.push_back(new uiMidiStop(fMidiHandler, this, zone, input));
                        } else if (fMetaAux[i].second == "clock") {
                            fClockTable.push_back(new uiMidiClock(fMidiHandler, this, zone, input));
                        // Explicit metadata to activate 'timestamp' mode
                        } else if (fMetaAux[i].second == "timestamp") {
                            fTimeStamp = true;
                        }
                    }
                }
            }
            fMetaAux.clear();
        }
    
        template <typename TABLE>
        void updateTable1(TABLE& table, double date, int channel, int val1)
        {
            for (size_t i = 0; i < table.size(); i++) {
                int channel_aux = table[i]->fChan;
                // channel_aux == 0 means "all channels"
                if (channel_aux == 0 || channel == channel_aux - 1) {
                    if (fTimeStamp) {
                        table[i]->modifyZone(date, FAUSTFLOAT(val1));
                    } else {
                        table[i]->modifyZone(FAUSTFLOAT(val1));
                    }
                }
            }
        }
        
        template <typename TABLE>
        void updateTable2(TABLE& table, double date, int channel, int val1, int val2)
        {
            if (table.find(val1) != table.end()) {
                for (size_t i = 0; i < table[val1].size(); i++) {
                    int channel_aux = table[val1][i]->fChan;
                    // channel_aux == 0 means "all channels"
                    if (channel_aux == 0 || channel == channel_aux - 1) {
                        if (fTimeStamp) {
                            table[val1][i]->modifyZone(date, FAUSTFLOAT(val2));
                        } else {
                            table[val1][i]->modifyZone(FAUSTFLOAT(val2));
                        }
                    }
                }
            }
        }
    
    public:
    
        MidiUI(midi_handler* midi_handler, bool delete_handler = false)
        {
            fMidiHandler = midi_handler;
            fMidiHandler->addMidiIn(this);
            // TODO: use shared_ptr based implementation
            fDelete = delete_handler;
            fTimeStamp = false;
        }
 
        virtual ~MidiUI() 
        {
            // Remove from fMidiHandler
            fMidiHandler->removeMidiIn(this);
            // TODO: use shared_ptr based implementation
            if (fDelete) delete fMidiHandler;
        }
    
        bool run() { return fMidiHandler->startMidi(); }
        void stop() { fMidiHandler->stopMidi(); }
        
        void addMidiIn(midi* midi_dsp) { fMidiHandler->addMidiIn(midi_dsp); }
        void removeMidiIn(midi* midi_dsp) { fMidiHandler->removeMidiIn(midi_dsp); }
      
        // -- active widgets
        
        virtual void addButton(const char* label, FAUSTFLOAT* zone)
        {
            addGenericZone(zone, FAUSTFLOAT(0), FAUSTFLOAT(1));
        }
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            addGenericZone(zone, FAUSTFLOAT(0), FAUSTFLOAT(1));
        }
        
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addGenericZone(zone, min, max);
        }
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addGenericZone(zone, min, max);
        }
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addGenericZone(zone, min, max);
        }

        // -- passive widgets

        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) 
        {
            addGenericZone(zone, min, max, false);
        }
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            addGenericZone(zone, min, max, false);
        }

        // -- metadata declarations

        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {
            MetaDataUI::declare(zone, key, val);
            fMetaAux.push_back(std::make_pair(key, val));
        }
        
        // -- MIDI API
    
        void key(double date, int channel, int note, int velocity)
        {
            updateTable2<TKeyOnTable>(fKeyTable, date, channel, note, velocity);
        }
    
        MapUI* keyOn(double date, int channel, int note, int velocity)
        {
            updateTable2<TKeyOnTable>(fKeyOnTable, date, channel, note, velocity);
            // If note is in fKeyTable, handle it as a keyOn
            key(date, channel, note, velocity);
            return nullptr;
        }
        
        void keyOff(double date, int channel, int note, int velocity)
        {
            updateTable2<TKeyOffTable>(fKeyOffTable, date, channel, note, velocity);
            // If note is in fKeyTable, handle it as a keyOff with a 0 velocity
            key(date, channel, note, 0);
        }
        
        void ctrlChange(double date, int channel, int ctrl, int value)
        {
            updateTable2<TCtrlChangeTable>(fCtrlChangeTable, date, channel, ctrl, value);
        }
    
        void rpn(double date, int channel, int ctrl, int value)
        {
            if (ctrl == midi::PITCH_BEND_RANGE) {
                for (size_t i = 0; i < fPitchWheelTable.size(); i++) {
                    // channel_aux == 0 means "all channels"
                    int channel_aux = fPitchWheelTable[i]->fChan;
                    if (channel_aux == 0 || channel == channel_aux - 1) {
                        fPitchWheelTable[i]->setRange(value);
                    }
                }
            }
        }
    
        void progChange(double date, int channel, int pgm)
        {
            updateTable1<TProgChangeTable>(fProgChangeTable, date, channel, pgm);
        }
        
        void pitchWheel(double date, int channel, int wheel) 
        {
            updateTable1<TPitchWheelTable>(fPitchWheelTable, date, channel, wheel);
        }
        
        void keyPress(double date, int channel, int pitch, int press) 
        {
            updateTable2<TKeyPressTable>(fKeyPressTable, date, channel, pitch, press);
        }
        
        void chanPress(double date, int channel, int press)
        {
            updateTable1<TChanPressTable>(fChanPressTable, date, channel, press);
        }
        
        void ctrlChange14bits(double date, int channel, int ctrl, int value) {}
        
        // MIDI sync
        
        void startSync(double date)
        {
            for (size_t i = 0; i < fStartTable.size(); i++) {
                fStartTable[i]->modifyZone(date, FAUSTFLOAT(1));
            }
        }
        
        void stopSync(double date)
        {
            for (size_t i = 0; i < fStopTable.size(); i++) {
                fStopTable[i]->modifyZone(date, FAUSTFLOAT(0));
            }
        }
        
        void clock(double date)
        {
            for (size_t i = 0; i < fClockTable.size(); i++) {
                fClockTable[i]->modifyZone(date, FAUSTFLOAT(1));
            }
        }
};

#endif // FAUST_MIDIUI_H
/**************************  END  MidiUI.h **************************/
/************************** BEGIN poly-base_dsp.h *************************
FAUST Architecture File
Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
---------------------------------------------------------------------
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

EXCEPTION : As a special exception, you may create a larger work
that contains this FAUST architecture section and distribute
that work under terms of your choice, so long as this FAUST
architecture section is not modified.
*********************************************************************/

#ifndef __poly_dsp__
#define __poly_dsp__

#include <stdio.h>
#include <string>
#include <cmath>
#include <algorithm>
#include <functional>
#include <ostream>
#include <sstream>
#include <vector>
#include <limits.h>
#include <float.h>
#include <assert.h>

/************************** BEGIN base_dsp-combiner.h **************************
FAUST Architecture File
Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
---------------------------------------------------------------------
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

EXCEPTION : As a special exception, you may create a larger work
that contains this FAUST architecture section and distribute
that work under terms of your choice, so long as this FAUST
architecture section is not modified.
************************************************************************/

#ifndef __dsp_combiner__
#define __dsp_combiner__

#include <string.h>
#include <string>
#include <assert.h>
#include <sstream>


// Base class and common code for binary combiners

enum Layout { kVerticalGroup, kHorizontalGroup, kTabGroup };

class dsp_binary_combiner : public base_dsp {

    protected:

        base_dsp* fDSP1;
        base_dsp* fDSP2;
        int fBufferSize;
        Layout fLayout;
        std::string fLabel;

        void buildUserInterfaceAux(UI* ui_interface)
        {
            switch (fLayout) {
                case kHorizontalGroup:
                    ui_interface->openHorizontalBox(fLabel.c_str());
                    fDSP1->buildUserInterface(ui_interface);
                    fDSP2->buildUserInterface(ui_interface);
                    ui_interface->closeBox();
                    break;
                case kVerticalGroup:
                    ui_interface->openVerticalBox(fLabel.c_str());
                    fDSP1->buildUserInterface(ui_interface);
                    fDSP2->buildUserInterface(ui_interface);
                    ui_interface->closeBox();
                    break;
                case kTabGroup:
                    ui_interface->openTabBox(fLabel.c_str());
                    ui_interface->openVerticalBox("DSP1");
                    fDSP1->buildUserInterface(ui_interface);
                    ui_interface->closeBox();
                    ui_interface->openVerticalBox("DSP2");
                    fDSP2->buildUserInterface(ui_interface);
                    ui_interface->closeBox();
                    ui_interface->closeBox();
                    break;
            }
        }

        FAUSTFLOAT** allocateChannels(int num)
        {
            FAUSTFLOAT** channels = new FAUSTFLOAT*[num];
            for (int chan = 0; chan < num; chan++) {
                channels[chan] = new FAUSTFLOAT[fBufferSize];
                memset(channels[chan], 0, sizeof(FAUSTFLOAT) * fBufferSize);
            }
            return channels;
        }

        void deleteChannels(FAUSTFLOAT** channels, int num)
        {
            for (int chan = 0; chan < num; chan++) {
                delete [] channels[chan];
            }
            delete [] channels;
        }

     public:

        dsp_binary_combiner(base_dsp* dsp1, base_dsp* dsp2, int buffer_size, Layout layout, const std::string& label)
        :fDSP1(dsp1), fDSP2(dsp2), fBufferSize(buffer_size), fLayout(layout), fLabel(label)
        {}

        virtual ~dsp_binary_combiner()
        {
            delete fDSP1;
            delete fDSP2;
        }

        virtual int getSampleRate()
        {
            return fDSP1->getSampleRate();
        }
        virtual void init(int sample_rate)
        {
            fDSP1->init(sample_rate);
            fDSP2->init(sample_rate);
        }
        virtual void instanceInit(int sample_rate)
        {
            fDSP1->instanceInit(sample_rate);
            fDSP2->instanceInit(sample_rate);
        }
        virtual void instanceConstants(int sample_rate)
        {
            fDSP1->instanceConstants(sample_rate);
            fDSP2->instanceConstants(sample_rate);
        }

        virtual void instanceResetUserInterface()
        {
            fDSP1->instanceResetUserInterface();
            fDSP2->instanceResetUserInterface();
        }

        virtual void instanceClear()
        {
            fDSP1->instanceClear();
            fDSP2->instanceClear();
        }

        virtual void metadata(Meta* m)
        {
            fDSP1->metadata(m);
            fDSP2->metadata(m);
        }

};

// Combine two 'compatible' DSP in sequence

class dsp_sequencer : public dsp_binary_combiner {

    private:

        FAUSTFLOAT** fDSP1Outputs;

    public:

        dsp_sequencer(base_dsp* dsp1, base_dsp* dsp2,
                      int buffer_size = 4096,
                      Layout layout = Layout::kTabGroup,
                      const std::string& label = "Sequencer")
        :dsp_binary_combiner(dsp1, dsp2, buffer_size, layout, label)
        {
            fDSP1Outputs = allocateChannels(fDSP1->getNumOutputs());
        }

        virtual ~dsp_sequencer()
        {
            deleteChannels(fDSP1Outputs, fDSP1->getNumOutputs());
        }

        virtual int getNumInputs() { return fDSP1->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP2->getNumOutputs(); }

        virtual void buildUserInterface(UI* ui_interface)
        {
            buildUserInterfaceAux(ui_interface);
        }

        virtual base_dsp* clone()
        {
            return new dsp_sequencer(fDSP1->clone(), fDSP2->clone(), fBufferSize, fLayout, fLabel);
        }

        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            fDSP1->compute(count, inputs, fDSP1Outputs);
            fDSP2->compute(count, fDSP1Outputs, outputs);
        }

        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }

};

// Combine two DSP in parallel

class dsp_parallelizer : public dsp_binary_combiner {

    private:

        FAUSTFLOAT** fDSP2Inputs;
        FAUSTFLOAT** fDSP2Outputs;

    public:

        dsp_parallelizer(base_dsp* dsp1, base_dsp* dsp2,
                     int buffer_size = 4096,
                     Layout layout = Layout::kTabGroup,
                     const std::string& label = "Parallelizer")
        :dsp_binary_combiner(dsp1, dsp2, buffer_size, layout, label)
        {
            fDSP2Inputs = new FAUSTFLOAT*[fDSP2->getNumInputs()];
            fDSP2Outputs = new FAUSTFLOAT*[fDSP2->getNumOutputs()];
        }

        virtual ~dsp_parallelizer()
        {
            delete [] fDSP2Inputs;
            delete [] fDSP2Outputs;
        }

        virtual int getNumInputs() { return fDSP1->getNumInputs() + fDSP2->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP1->getNumOutputs() + fDSP2->getNumOutputs(); }

        virtual void buildUserInterface(UI* ui_interface)
        {
            buildUserInterfaceAux(ui_interface);
        }

        virtual base_dsp* clone()
        {
            return new dsp_parallelizer(fDSP1->clone(), fDSP2->clone(), fBufferSize, fLayout, fLabel);
        }

        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            fDSP1->compute(count, inputs, outputs);

            // Shift inputs/outputs channels for fDSP2
            for (int chan = 0; chan < fDSP2->getNumInputs(); chan++) {
                fDSP2Inputs[chan] = inputs[fDSP1->getNumInputs() + chan];
            }
            for (int chan = 0; chan < fDSP2->getNumOutputs(); chan++) {
                fDSP2Outputs[chan] = outputs[fDSP1->getNumOutputs() + chan];
            }

            fDSP2->compute(count, fDSP2Inputs, fDSP2Outputs);
        }

        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }

};

// Combine two 'compatible' DSP in splitter

class dsp_splitter : public dsp_binary_combiner {

    private:

        FAUSTFLOAT** fDSP1Outputs;
        FAUSTFLOAT** fDSP2Inputs;

    public:

        dsp_splitter(base_dsp* dsp1, base_dsp* dsp2,
                     int buffer_size = 4096,
                     Layout layout = Layout::kTabGroup,
                     const std::string& label = "Splitter")
        :dsp_binary_combiner(dsp1, dsp2, buffer_size, layout, label)
        {
            fDSP1Outputs = allocateChannels(fDSP1->getNumOutputs());
            fDSP2Inputs = new FAUSTFLOAT*[fDSP2->getNumInputs()];
        }

        virtual ~dsp_splitter()
        {
            deleteChannels(fDSP1Outputs, fDSP1->getNumOutputs());
            delete [] fDSP2Inputs;
        }

        virtual int getNumInputs() { return fDSP1->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP2->getNumOutputs(); }

        virtual void buildUserInterface(UI* ui_interface)
        {
            buildUserInterfaceAux(ui_interface);
        }

        virtual base_dsp* clone()
        {
            return new dsp_splitter(fDSP1->clone(), fDSP2->clone(), fBufferSize, fLayout, fLabel);
        }

        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            fDSP1->compute(count, inputs, fDSP1Outputs);

            for (int chan = 0; chan < fDSP2->getNumInputs(); chan++) {
                 fDSP2Inputs[chan] = fDSP1Outputs[chan % fDSP1->getNumOutputs()];
            }

            fDSP2->compute(count, fDSP2Inputs, outputs);
        }
};

// Combine two 'compatible' DSP in merger

class dsp_merger : public dsp_binary_combiner {

    private:

        FAUSTFLOAT** fDSP1Inputs;
        FAUSTFLOAT** fDSP1Outputs;
        FAUSTFLOAT** fDSP2Inputs;

        void mix(int count, FAUSTFLOAT* dst, FAUSTFLOAT* src)
        {
            for (int frame = 0; frame < count; frame++) {
                dst[frame] += src[frame];
            }
        }

    public:

        dsp_merger(base_dsp* dsp1, base_dsp* dsp2,
                   int buffer_size = 4096,
                   Layout layout = Layout::kTabGroup,
                   const std::string& label = "Merger")
        :dsp_binary_combiner(dsp1, dsp2, buffer_size, layout, label)
        {
            fDSP1Inputs = allocateChannels(fDSP1->getNumInputs());
            fDSP1Outputs = allocateChannels(fDSP1->getNumOutputs());
            fDSP2Inputs = new FAUSTFLOAT*[fDSP2->getNumInputs()];
        }

        virtual ~dsp_merger()
        {
            deleteChannels(fDSP1Inputs, fDSP1->getNumInputs());
            deleteChannels(fDSP1Outputs, fDSP1->getNumOutputs());
            delete [] fDSP2Inputs;
        }

        virtual int getNumInputs() { return fDSP1->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP2->getNumOutputs(); }

        virtual void buildUserInterface(UI* ui_interface)
        {
            buildUserInterfaceAux(ui_interface);
        }

        virtual base_dsp* clone()
        {
            return new dsp_merger(fDSP1->clone(), fDSP2->clone(), fBufferSize, fLayout, fLabel);
        }

        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            fDSP1->compute(count, fDSP1Inputs, fDSP1Outputs);

            memset(fDSP2Inputs, 0, sizeof(FAUSTFLOAT*) * fDSP2->getNumInputs());

            for (int chan = 0; chan < fDSP1->getNumOutputs(); chan++) {
                int mchan = chan % fDSP2->getNumInputs();
                if (fDSP2Inputs[mchan]) {
                    mix(count, fDSP2Inputs[mchan], fDSP1Outputs[chan]);
                } else {
                    fDSP2Inputs[mchan] = fDSP1Outputs[chan];
                }
            }

            fDSP2->compute(count, fDSP2Inputs, outputs);
        }
};

// Combine two 'compatible' DSP in a recursive way

class dsp_recursiver : public dsp_binary_combiner {

    private:

        FAUSTFLOAT** fDSP1Inputs;
        FAUSTFLOAT** fDSP1Outputs;

        FAUSTFLOAT** fDSP2Inputs;
        FAUSTFLOAT** fDSP2Outputs;

    public:

        dsp_recursiver(base_dsp* dsp1, base_dsp* dsp2,
                       Layout layout = Layout::kTabGroup,
                       const std::string& label = "Recursiver")
        :dsp_binary_combiner(dsp1, dsp2, 1, layout, label)
        {
            fDSP1Inputs = allocateChannels(fDSP1->getNumInputs());
            fDSP1Outputs = allocateChannels(fDSP1->getNumOutputs());
            fDSP2Inputs = allocateChannels(fDSP2->getNumInputs());
            fDSP2Outputs = allocateChannels(fDSP2->getNumOutputs());
        }

        virtual ~dsp_recursiver()
        {
            deleteChannels(fDSP1Inputs, fDSP1->getNumInputs());
            deleteChannels(fDSP1Outputs, fDSP1->getNumOutputs());
            deleteChannels(fDSP2Inputs, fDSP2->getNumInputs());
            deleteChannels(fDSP2Outputs, fDSP2->getNumOutputs());
        }

        virtual int getNumInputs() { return fDSP1->getNumInputs() - fDSP2->getNumOutputs(); }
        virtual int getNumOutputs() { return fDSP1->getNumOutputs(); }

        virtual void buildUserInterface(UI* ui_interface)
        {
            buildUserInterfaceAux(ui_interface);
        }

        virtual base_dsp* clone()
        {
            return new dsp_recursiver(fDSP1->clone(), fDSP2->clone(), fLayout, fLabel);
        }

        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            for (int frame = 0; (frame < count); frame++) {

                for (int chan = 0; chan < fDSP2->getNumOutputs(); chan++) {
                    fDSP1Inputs[chan][0] = fDSP2Outputs[chan][0];
                }

                for (int chan = 0; chan < fDSP1->getNumInputs() - fDSP2->getNumOutputs(); chan++) {
                    fDSP1Inputs[chan + fDSP2->getNumOutputs()][0] = inputs[chan][frame];
                }

                fDSP1->compute(1, fDSP1Inputs, fDSP1Outputs);

                for (int chan = 0; chan < fDSP1->getNumOutputs(); chan++) {
                    outputs[chan][frame] = fDSP1Outputs[chan][0];
                }

                for (int chan = 0; chan < fDSP2->getNumInputs(); chan++) {
                    fDSP2Inputs[chan][0] = fDSP1Outputs[chan][0];
                }

                fDSP2->compute(1, fDSP2Inputs, fDSP2Outputs);
            }
        }

        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }

};

/*
 Crossfade between two DSP.
 When fCrossfade = 1, the first DSP only is computed, when fCrossfade = 0,
 the second DSP only is computed, otherwise both DSPs are computed and mixed.
*/

class dsp_crossfader: public dsp_binary_combiner {

    private:
    
        FAUSTFLOAT fCrossfade;
        FAUSTFLOAT** fDSPOutputs1;
        FAUSTFLOAT** fDSPOutputs2;
    
    public:
    
        dsp_crossfader(base_dsp* dsp1, base_dsp* dsp2,
                       Layout layout = Layout::kTabGroup,
                       const std::string& label = "Crossfade")
        :dsp_binary_combiner(dsp1, dsp2, 4096, layout, label),fCrossfade(FAUSTFLOAT(0.5))
        {
            fDSPOutputs1 = allocateChannels(fDSP1->getNumOutputs());
            fDSPOutputs2 = allocateChannels(fDSP1->getNumOutputs());
        }
    
        virtual ~dsp_crossfader()
        {
            deleteChannels(fDSPOutputs1, fDSP1->getNumInputs());
            deleteChannels(fDSPOutputs2, fDSP1->getNumOutputs());
        }
    
        virtual int getNumInputs() { return fDSP1->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP1->getNumOutputs(); }

        void buildUserInterface(UI* ui_interface)
        {
            switch (fLayout) {
                case kHorizontalGroup:
                    ui_interface->openHorizontalBox(fLabel.c_str());
                    ui_interface->addHorizontalSlider("Crossfade", &fCrossfade, FAUSTFLOAT(0.5), FAUSTFLOAT(0), FAUSTFLOAT(1), FAUSTFLOAT(0.01));
                    fDSP1->buildUserInterface(ui_interface);
                    fDSP2->buildUserInterface(ui_interface);
                    ui_interface->closeBox();
                    break;
                case kVerticalGroup:
                    ui_interface->openVerticalBox(fLabel.c_str());
                    ui_interface->addHorizontalSlider("Crossfade", &fCrossfade, FAUSTFLOAT(0.5), FAUSTFLOAT(0), FAUSTFLOAT(1), FAUSTFLOAT(0.01));
                    fDSP1->buildUserInterface(ui_interface);
                    fDSP2->buildUserInterface(ui_interface);
                    ui_interface->closeBox();
                    break;
                case kTabGroup:
                    ui_interface->openTabBox(fLabel.c_str());
                    ui_interface->openVerticalBox("Crossfade");
                    ui_interface->addHorizontalSlider("Crossfade", &fCrossfade, FAUSTFLOAT(0.5), FAUSTFLOAT(0), FAUSTFLOAT(1), FAUSTFLOAT(0.01));
                    ui_interface->closeBox();
                    ui_interface->openVerticalBox("DSP1");
                    fDSP1->buildUserInterface(ui_interface);
                    ui_interface->closeBox();
                    ui_interface->openVerticalBox("DSP2");
                    fDSP2->buildUserInterface(ui_interface);
                    ui_interface->closeBox();
                    ui_interface->closeBox();
                    break;
            }
        }
    
        virtual base_dsp* clone()
        {
            return new dsp_crossfader(fDSP1->clone(), fDSP2->clone(), fLayout, fLabel);
        }
    
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            if (fCrossfade == FAUSTFLOAT(1)) {
                fDSP1->compute(count, inputs, outputs);
            } else if (fCrossfade == FAUSTFLOAT(0)) {
                fDSP2->compute(count, inputs, outputs);
            } else {
                // Compute each effect
                fDSP1->compute(count, inputs, fDSPOutputs1);
                fDSP2->compute(count, inputs, fDSPOutputs2);
                // Mix between the two effects
                FAUSTFLOAT gain1 = fCrossfade;
                FAUSTFLOAT gain2 = FAUSTFLOAT(1) - gain1;
                for (int frame = 0; (frame < count); frame++) {
                    for (int chan = 0; chan < fDSP1->getNumOutputs(); chan++) {
                        outputs[chan][frame] = fDSPOutputs1[chan][frame] * gain1 + fDSPOutputs2[chan][frame] * gain2;
                    }
                }
            }
        }
    
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }
};

#ifndef __dsp_algebra_api__
#define __dsp_algebra_api__

// DSP algebra API
/*
 Each operation takes two DSP and a optional Layout and Label parameters, returns the combined DSPs, or null if failure with an error message.
 */

static base_dsp* createDSPSequencer(base_dsp* dsp1, base_dsp* dsp2,
                               std::string& error,
                               Layout layout = Layout::kTabGroup,
                               const std::string& label = "Sequencer")
{
    if (dsp1->getNumOutputs() != dsp2->getNumInputs()) {
        std::stringstream error_aux;
        error_aux << "Connection error in dsp_sequencer : the number of outputs ("
                  << dsp1->getNumOutputs() << ") of A "
                  << "must be equal to the number of inputs (" << dsp2->getNumInputs() << ") of B" << std::endl;
        error = error_aux.str();
        return nullptr;
    } else {
        return new dsp_sequencer(dsp1, dsp2, 4096, layout, label);
    }
}

static base_dsp* createDSPParallelizer(base_dsp* dsp1, base_dsp* dsp2,
                                  std::string& error,
                                  Layout layout = Layout::kTabGroup,
                                  const std::string& label = "Parallelizer")
{
    return new dsp_parallelizer(dsp1, dsp2, 4096, layout, label);
}

static base_dsp* createDSPSplitter(base_dsp* dsp1, base_dsp* dsp2, std::string& error, Layout layout = Layout::kTabGroup, const std::string& label = "Splitter")
{
    if (dsp1->getNumOutputs() == 0) {
        error = "Connection error in dsp_splitter : the first expression has no outputs\n";
        return nullptr;
    } else if (dsp2->getNumInputs() == 0) {
        error = "Connection error in dsp_splitter : the second expression has no inputs\n";
        return nullptr;
    } else if (dsp2->getNumInputs() % dsp1->getNumOutputs() != 0) {
        std::stringstream error_aux;
        error_aux << "Connection error in dsp_splitter : the number of outputs (" << dsp1->getNumOutputs()
                  << ") of the first expression should be a divisor of the number of inputs ("
                  << dsp2->getNumInputs()
                  << ") of the second expression" << std::endl;
        error = error_aux.str();
        return nullptr;
    } else if (dsp2->getNumInputs() == dsp1->getNumOutputs()) {
        return new dsp_sequencer(dsp1, dsp2, 4096, layout, label);
    } else {
        return new dsp_splitter(dsp1, dsp2, 4096, layout, label);
    }
}

static base_dsp* createDSPMerger(base_dsp* dsp1, base_dsp* dsp2,
                            std::string& error,
                            Layout layout = Layout::kTabGroup,
                            const std::string& label = "Merger")
{
    if (dsp1->getNumOutputs() == 0) {
        error = "Connection error in dsp_merger : the first expression has no outputs\n";
        return nullptr;
    } else if (dsp2->getNumInputs() == 0) {
        error = "Connection error in dsp_merger : the second expression has no inputs\n";
        return nullptr;
    } else if (dsp1->getNumOutputs() % dsp2->getNumInputs() != 0) {
        std::stringstream error_aux;
        error_aux << "Connection error in dsp_merger : the number of outputs (" << dsp1->getNumOutputs()
                  << ") of the first expression should be a multiple of the number of inputs ("
                  << dsp2->getNumInputs()
                  << ") of the second expression" << std::endl;
        error = error_aux.str();
        return nullptr;
    } else if (dsp2->getNumInputs() == dsp1->getNumOutputs()) {
        return new dsp_sequencer(dsp1, dsp2, 4096, layout, label);
    } else {
        return new dsp_merger(dsp1, dsp2, 4096, layout, label);
    }
}

static base_dsp* createDSPRecursiver(base_dsp* dsp1, base_dsp* dsp2,
                                std::string& error,
                                Layout layout = Layout::kTabGroup,
                                const std::string& label = "Recursiver")
{
    if ((dsp2->getNumInputs() > dsp1->getNumOutputs()) || (dsp2->getNumOutputs() > dsp1->getNumInputs())) {
        std::stringstream error_aux;
        error_aux << "Connection error in : dsp_recursiver" << std::endl;
        if (dsp2->getNumInputs() > dsp1->getNumOutputs()) {
            error_aux << "The number of outputs " << dsp1->getNumOutputs()
                      << " of the first expression should be greater or equal to the number of inputs ("
                      << dsp2->getNumInputs()
                      << ") of the second expression" << std::endl;
        }
        if (dsp2->getNumOutputs() > dsp1->getNumInputs()) {
            error_aux << "The number of inputs " << dsp1->getNumInputs()
                      << " of the first expression should be greater or equal to the number of outputs ("
                      << dsp2->getNumOutputs()
                      << ") of the second expression" << std::endl;
        }
        error = error_aux.str();
        return nullptr;
    } else {
        return new dsp_recursiver(dsp1, dsp2, layout, label);
    }
}

static base_dsp* createDSPCrossfader(base_dsp* dsp1, base_dsp* dsp2,
                                 std::string& error,
                                 Layout layout = Layout::kTabGroup,
                                 const std::string& label = "Crossfade")
{
    if (dsp1->getNumInputs() != dsp2->getNumInputs()) {
        std::stringstream error_aux;
        error_aux << "Connection error in dsp_crossfader : the number of inputs ("
        << dsp1->getNumInputs() << ") of A "
        << "must be equal to the number of inputs (" << dsp2->getNumInputs() << ") of B" << std::endl;
        error = error_aux.str();
        return nullptr;
    } else if (dsp1->getNumOutputs() != dsp2->getNumOutputs()) {
        std::stringstream error_aux;
        error_aux << "Connection error in dsp_crossfader : the number of outputs ("
        << dsp1->getNumOutputs() << ") of A "
        << "must be equal to the number of outputs (" << dsp2->getNumOutputs() << ") of B" << std::endl;
        error = error_aux.str();
        return nullptr;
    } else {
        return new dsp_crossfader(dsp1, dsp2, layout, label);
    }
}

#endif

#endif
/************************** END base_dsp-combiner.h **************************/
/************************** BEGIN proxy-base_dsp.h ***************************
FAUST Architecture File
Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
---------------------------------------------------------------------
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

EXCEPTION : As a special exception, you may create a larger work
that contains this FAUST architecture section and distribute
that work under terms of your choice, so long as this FAUST
architecture section is not modified.
***************************************************************************/

#ifndef __proxy_dsp__
#define __proxy_dsp__

#include <vector>
#include <map>

/************************** BEGIN JSONUIDecoder.h **************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 *************************************************************************/

#ifndef __JSONUIDecoder__
#define __JSONUIDecoder__

#include <vector>
#include <map>
#include <utility>
#include <cstdlib>
#include <sstream>
#include <functional>

/************************** BEGIN CGlue.h *****************************
FAUST Architecture File
Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
---------------------------------------------------------------------
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

EXCEPTION : As a special exception, you may create a larger work
that contains this FAUST architecture section and distribute
that work under terms of your choice, so long as this FAUST
architecture section is not modified.
*************************************************************************/

#ifndef CGLUE_H
#define CGLUE_H

/************************** BEGIN CInterface.h **************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 *************************************************************************/


#ifndef CINTERFACE_H
#define CINTERFACE_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif
    
struct Soundfile;

/*******************************************************************************
 * UI, Meta and MemoryManager structures for C code.
 ******************************************************************************/

// -- widget's layouts

typedef void (* openTabBoxFun) (void* ui_interface, const char* label);
typedef void (* openHorizontalBoxFun) (void* ui_interface, const char* label);
typedef void (* openVerticalBoxFun) (void* ui_interface, const char* label);
typedef void (* closeBoxFun) (void* ui_interface);

// -- active widgets

typedef void (* addButtonFun) (void* ui_interface, const char* label, FAUSTFLOAT* zone);
typedef void (* addCheckButtonFun) (void* ui_interface, const char* label, FAUSTFLOAT* zone);
typedef void (* addVerticalSliderFun) (void* ui_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step);
typedef void (* addHorizontalSliderFun) (void* ui_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step);
typedef void (* addNumEntryFun) (void* ui_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step);

// -- passive widgets

typedef void (* addHorizontalBargraphFun) (void* ui_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max);
typedef void (* addVerticalBargraphFun) (void* ui_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max);

// -- soundfiles
    
typedef void (* addSoundfileFun) (void* ui_interface, const char* label, const char* url, struct Soundfile** sf_zone);

typedef void (* declareFun) (void* ui_interface, FAUSTFLOAT* zone, const char* key, const char* value);

typedef struct {

    void* uiInterface;

    openTabBoxFun openTabBox;
    openHorizontalBoxFun openHorizontalBox;
    openVerticalBoxFun openVerticalBox;
    closeBoxFun closeBox;
    addButtonFun addButton;
    addCheckButtonFun addCheckButton;
    addVerticalSliderFun addVerticalSlider;
    addHorizontalSliderFun addHorizontalSlider;
    addNumEntryFun addNumEntry;
    addHorizontalBargraphFun addHorizontalBargraph;
    addVerticalBargraphFun addVerticalBargraph;
    addSoundfileFun addSoundfile;
    declareFun declare;

} UIGlue;

typedef void (* metaDeclareFun) (void* ui_interface, const char* key, const char* value);

typedef struct {

    void* metaInterface;
    
    metaDeclareFun declare;

} MetaGlue;

/***************************************
 *  Interface for the DSP object
 ***************************************/

typedef char dsp_imp;
    
typedef dsp_imp* (* newDspFun) ();
typedef void (* destroyDspFun) (dsp_imp* base_dsp);
typedef int (* getNumInputsFun) (dsp_imp* base_dsp);
typedef int (* getNumOutputsFun) (dsp_imp* base_dsp);
typedef void (* buildUserInterfaceFun) (dsp_imp* base_dsp, UIGlue* ui);
typedef int (* getSampleRateFun) (dsp_imp* base_dsp);
typedef void (* initFun) (dsp_imp* base_dsp, int sample_rate);
typedef void (* classInitFun) (int sample_rate);
typedef void (* instanceInitFun) (dsp_imp* base_dsp, int sample_rate);
typedef void (* instanceConstantsFun) (dsp_imp* base_dsp, int sample_rate);
typedef void (* instanceResetUserInterfaceFun) (dsp_imp* base_dsp);
typedef void (* instanceClearFun) (dsp_imp* base_dsp);
typedef void (* computeFun) (dsp_imp* base_dsp, int len, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs);
typedef void (* metadataFun) (MetaGlue* meta);
    
/***************************************
 * DSP memory manager functions
 ***************************************/

typedef void* (* allocateFun) (void* manager_interface, size_t size);
typedef void (* destroyFun) (void* manager_interface, void* ptr);

typedef struct {
    
    void* managerInterface;
    
    allocateFun allocate;
    destroyFun destroy;
    
} MemoryManagerGlue;

#ifdef __cplusplus
}
#endif

#endif
/**************************  END  CInterface.h **************************/

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * UI glue code
 ******************************************************************************/
 
class UIFloat
{

    public:

        UIFloat() {}

        virtual ~UIFloat() {}

        // -- widget's layouts

        virtual void openTabBox(const char* label) = 0;
        virtual void openHorizontalBox(const char* label) = 0;
        virtual void openVerticalBox(const char* label) = 0;
        virtual void closeBox() = 0;

        // -- active widgets

        virtual void addButton(const char* label, float* zone) = 0;
        virtual void addCheckButton(const char* label, float* zone) = 0;
        virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step) = 0;
        virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step) = 0;
        virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step) = 0;

        // -- passive widgets

        virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max) = 0;
        virtual void addVerticalBargraph(const char* label, float* zone, float min, float max) = 0;
    
        // -- soundfiles
    
        virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) = 0;

        // -- metadata declarations

        virtual void declare(float* zone, const char* key, const char* val) {}
};

static void openTabBoxGlueFloat(void* cpp_interface, const char* label)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->openTabBox(label);
}

static void openHorizontalBoxGlueFloat(void* cpp_interface, const char* label)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->openHorizontalBox(label);
}

static void openVerticalBoxGlueFloat(void* cpp_interface, const char* label)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->openVerticalBox(label);
}

static void closeBoxGlueFloat(void* cpp_interface)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->closeBox();
}

static void addButtonGlueFloat(void* cpp_interface, const char* label, float* zone)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->addButton(label, zone);
}

static void addCheckButtonGlueFloat(void* cpp_interface, const char* label, float* zone)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->addCheckButton(label, zone);
}

static void addVerticalSliderGlueFloat(void* cpp_interface, const char* label, float* zone, float init, float min, float max, float step)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->addVerticalSlider(label, zone, init, min, max, step);
}

static void addHorizontalSliderGlueFloat(void* cpp_interface, const char* label, float* zone, float init, float min, float max, float step)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->addHorizontalSlider(label, zone, init, min, max, step);
}

static void addNumEntryGlueFloat(void* cpp_interface, const char* label, float* zone, float init, float min, float max, float step)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->addNumEntry(label, zone, init, min, max, step);
}

static void addHorizontalBargraphGlueFloat(void* cpp_interface, const char* label, float* zone, float min, float max)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->addHorizontalBargraph(label, zone, min, max);
}

static void addVerticalBargraphGlueFloat(void* cpp_interface, const char* label, float* zone, float min, float max)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->addVerticalBargraph(label, zone, min, max);
}
    
static void addSoundfileGlueFloat(void* cpp_interface, const char* label, const char* url, Soundfile** sf_zone)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->addSoundfile(label, url, sf_zone);
}

static void declareGlueFloat(void* cpp_interface, float* zone, const char* key, const char* value)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->declare(zone, key, value);
}

class UIDouble
{

    public:

        UIDouble() {}

        virtual ~UIDouble() {}

        // -- widget's layouts

        virtual void openTabBox(const char* label) = 0;
        virtual void openHorizontalBox(const char* label) = 0;
        virtual void openVerticalBox(const char* label) = 0;
        virtual void closeBox() = 0;

        // -- active widgets

        virtual void addButton(const char* label, double* zone) = 0;
        virtual void addCheckButton(const char* label, double* zone) = 0;
        virtual void addVerticalSlider(const char* label, double* zone, double init, double min, double max, double step) = 0;
        virtual void addHorizontalSlider(const char* label, double* zone, double init, double min, double max, double step) = 0;
        virtual void addNumEntry(const char* label, double* zone, double init, double min, double max, double step) = 0;

        // -- passive widgets

        virtual void addHorizontalBargraph(const char* label, double* zone, double min, double max) = 0;
        virtual void addVerticalBargraph(const char* label, double* zone, double min, double max) = 0;
    
        // -- soundfiles
    
        virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) = 0;

        // -- metadata declarations

        virtual void declare(double* zone, const char* key, const char* val) {}
};

static void openTabBoxGlueDouble(void* cpp_interface, const char* label)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->openTabBox(label);
}

static void openHorizontalBoxGlueDouble(void* cpp_interface, const char* label)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->openHorizontalBox(label);
}

static void openVerticalBoxGlueDouble(void* cpp_interface, const char* label)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->openVerticalBox(label);
}

static void closeBoxGlueDouble(void* cpp_interface)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->closeBox();
}

static void addButtonGlueDouble(void* cpp_interface, const char* label, double* zone)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->addButton(label, zone);
}

static void addCheckButtonGlueDouble(void* cpp_interface, const char* label, double* zone)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->addCheckButton(label, zone);
}

static void addVerticalSliderGlueDouble(void* cpp_interface, const char* label, double* zone, double init, double min, double max, double step)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->addVerticalSlider(label, zone, init, min, max, step);
}

static void addHorizontalSliderGlueDouble(void* cpp_interface, const char* label, double* zone, double init, double min, double max, double step)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->addHorizontalSlider(label, zone, init, min, max, step);
}

static void addNumEntryGlueDouble(void* cpp_interface, const char* label, double* zone, double init, double min, double max, double step)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->addNumEntry(label, zone, init, min, max, step);
}

static void addHorizontalBargraphGlueDouble(void* cpp_interface, const char* label, double* zone, double min, double max)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->addHorizontalBargraph(label, zone, min, max);
}

static void addVerticalBargraphGlueDouble(void* cpp_interface, const char* label, double* zone, double min, double max)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->addVerticalBargraph(label, zone, min, max);
}
    
static void addSoundfileGlueDouble(void* cpp_interface, const char* label, const char* url, Soundfile** sf_zone)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->addSoundfile(label, url, sf_zone);
}

static void declareGlueDouble(void* cpp_interface, double* zone, const char* key, const char* value)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->declare(zone, key, value);
}

static void buildUIGlue(UIGlue* glue, UI* ui_interface, bool is_double)
{
    glue->uiInterface = ui_interface;
    
    if (is_double) {
        glue->openTabBox = reinterpret_cast<openTabBoxFun>(openTabBoxGlueDouble);
        glue->openHorizontalBox = reinterpret_cast<openHorizontalBoxFun>(openHorizontalBoxGlueDouble);
        glue->openVerticalBox = reinterpret_cast<openVerticalBoxFun>(openVerticalBoxGlueDouble);
        glue->closeBox = reinterpret_cast<closeBoxFun>(closeBoxGlueDouble);
        glue->addButton = reinterpret_cast<addButtonFun>(addButtonGlueDouble);
        glue->addCheckButton = reinterpret_cast<addCheckButtonFun>(addCheckButtonGlueDouble);
        glue->addVerticalSlider = reinterpret_cast<addVerticalSliderFun>(addVerticalSliderGlueDouble);
        glue->addHorizontalSlider = reinterpret_cast<addHorizontalSliderFun>(addHorizontalSliderGlueDouble);
        glue->addNumEntry = reinterpret_cast<addNumEntryFun>(addNumEntryGlueDouble);
        glue->addHorizontalBargraph = reinterpret_cast<addHorizontalBargraphFun>(addHorizontalBargraphGlueDouble);
        glue->addVerticalBargraph = reinterpret_cast<addVerticalBargraphFun>(addVerticalBargraphGlueDouble);
        glue->addSoundfile = reinterpret_cast<addSoundfileFun>(addSoundfileGlueDouble);
        glue->declare = reinterpret_cast<declareFun>(declareGlueDouble);
    } else {
        glue->openTabBox = reinterpret_cast<openTabBoxFun>(openTabBoxGlueFloat);
        glue->openHorizontalBox = reinterpret_cast<openHorizontalBoxFun>(openHorizontalBoxGlueFloat);
        glue->openVerticalBox = reinterpret_cast<openVerticalBoxFun>(openVerticalBoxGlueFloat);
        glue->closeBox = reinterpret_cast<closeBoxFun>(closeBoxGlueFloat);
        glue->addButton = reinterpret_cast<addButtonFun>(addButtonGlueFloat);
        glue->addCheckButton = reinterpret_cast<addCheckButtonFun>(addCheckButtonGlueFloat);
        glue->addVerticalSlider = reinterpret_cast<addVerticalSliderFun>(addVerticalSliderGlueFloat);
        glue->addHorizontalSlider = reinterpret_cast<addHorizontalSliderFun>(addHorizontalSliderGlueFloat);
        glue->addNumEntry = reinterpret_cast<addNumEntryFun>(addNumEntryGlueFloat);
        glue->addHorizontalBargraph = reinterpret_cast<addHorizontalBargraphFun>(addHorizontalBargraphGlueFloat);
        glue->addVerticalBargraph = reinterpret_cast<addVerticalBargraphFun>(addVerticalBargraphGlueFloat);
        glue->addSoundfile = reinterpret_cast<addSoundfileFun>(addSoundfileGlueFloat);
        glue->declare = reinterpret_cast<declareFun>(declareGlueFloat);
    }
}
    
struct UITemplate
{
    
    void* fCPPInterface;

    UITemplate(void* cpp_interface):fCPPInterface(cpp_interface)
    {}
    
    virtual ~UITemplate() {}
    
    // -- widget's layouts
    
    virtual void openTabBox(const char* label)
    {
        openTabBoxGlueFloat(fCPPInterface, label);
    }
    virtual void openHorizontalBox(const char* label)
    {
        openHorizontalBoxGlueFloat(fCPPInterface, label);
    }
    virtual void openVerticalBox(const char* label)
    {
        openVerticalBoxGlueFloat(fCPPInterface, label);
    }
    virtual void closeBox()
    {
        closeBoxGlueFloat(fCPPInterface);
    }
    
    // float version
    
    // -- active widgets
    
    virtual void addButton(const char* label, float* zone)
    {
        addButtonGlueFloat(fCPPInterface, label, zone);
    }
    virtual void addCheckButton(const char* label, float* zone)
    {
        addCheckButtonGlueFloat(fCPPInterface, label, zone);
    }
    
    virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step)
    {
        addVerticalSliderGlueFloat(fCPPInterface, label, zone, init, min, max, step);
    }
    
    virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step)
    {
        addHorizontalSliderGlueFloat(fCPPInterface, label, zone, init, min, max, step);
    }
    
    virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step)
    {
        addNumEntryGlueFloat(fCPPInterface, label, zone, init, min, max, step);
    }
    
    // -- passive widgets
    
    virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max)
    {
        addHorizontalBargraphGlueFloat(fCPPInterface, label, zone, min, max);
    }
    
    virtual void addVerticalBargraph(const char* label, float* zone, float min, float max)
    {
        addVerticalBargraphGlueFloat(fCPPInterface, label, zone, min, max);
    }

    // -- metadata declarations
    
    virtual void declare(float* zone, const char* key, const char* val)
    {
        declareGlueFloat(fCPPInterface, zone, key, val);
    }
    
    // double version
    
    virtual void addButton(const char* label, double* zone)
    {
        addButtonGlueDouble(fCPPInterface, label, zone);
    }
    virtual void addCheckButton(const char* label, double* zone)
    {
        addCheckButtonGlueDouble(fCPPInterface, label, zone);
    }
    
    virtual void addVerticalSlider(const char* label, double* zone, double init, double min, double max, double step)
    {
        addVerticalSliderGlueDouble(fCPPInterface, label, zone, init, min, max, step);
    }
    
    virtual void addHorizontalSlider(const char* label, double* zone, double init, double min, double max, double step)
    {
        addHorizontalSliderGlueDouble(fCPPInterface, label, zone, init, min, max, step);
    }
    
    virtual void addNumEntry(const char* label, double* zone, double init, double min, double max, double step)
    {
        addNumEntryGlueDouble(fCPPInterface, label, zone, init, min, max, step);
    }

    // -- soundfiles
    
    virtual void addSoundfile(const char* label, const char* url, Soundfile** sf_zone)
    {
        addSoundfileGlueFloat(fCPPInterface, label, url, sf_zone);
    }

    // -- passive widgets
    
    virtual void addHorizontalBargraph(const char* label, double* zone, double min, double max)
    {
        addHorizontalBargraphGlueDouble(fCPPInterface, label, zone, min, max);
    }
    
    virtual void addVerticalBargraph(const char* label, double* zone, double min, double max)
    {
        addVerticalBargraphGlueDouble(fCPPInterface, label, zone, min, max);
    }

    // -- metadata declarations
    
    virtual void declare(double* zone, const char* key, const char* val)
    {
        declareGlueDouble(fCPPInterface, zone, key, val);
    }

};

/*******************************************************************************
 * Meta glue code
 ******************************************************************************/

static void declareMetaGlue(void* cpp_interface, const char* key, const char* value)
{
    Meta* meta_interface = static_cast<Meta*>(cpp_interface);
    meta_interface->declare(key, value);
}

static void buildMetaGlue(MetaGlue* glue, Meta* meta)
{
    glue->metaInterface = meta;
    glue->declare = declareMetaGlue;
}
    
/*******************************************************************************
 * Memory manager glue code
 ******************************************************************************/

static void* allocateMemoryManagerGlue(void* cpp_interface, size_t size)
{
    dsp_memory_manager* manager_interface = static_cast<dsp_memory_manager*>(cpp_interface);
    return manager_interface->allocate(size);
}
    
static void destroyMemoryManagerGlue(void* cpp_interface, void* ptr)
{
    dsp_memory_manager* manager_interface = static_cast<dsp_memory_manager*>(cpp_interface);
    manager_interface->destroy(ptr);
}

static void buildManagerGlue(MemoryManagerGlue* glue, dsp_memory_manager* manager)
{
    glue->managerInterface = manager;
    glue->allocate = allocateMemoryManagerGlue;
    glue->destroy = destroyMemoryManagerGlue;
}

#ifdef __cplusplus
}
#endif

#endif
/**************************  END  CGlue.h **************************/

#ifdef _WIN32
#include <windows.h>
#define snprintf _snprintf
#endif

//------------------------------------------------------------------------------------------
//  Decode a base_dsp JSON description and implement 'buildUserInterface' and 'metadata' methods
//------------------------------------------------------------------------------------------

#define REAL_UI(ui_interface) reinterpret_cast<UIReal<REAL>*>(ui_interface)
#define REAL_ADR(index)      reinterpret_cast<REAL*>(&memory_block[index])
#define REAL_EXT_ADR(index)  reinterpret_cast<FAUSTFLOAT*>(&memory_block[index])
#define SOUNDFILE_ADR(index) reinterpret_cast<Soundfile**>(&memory_block[index])

typedef std::function<void(FAUSTFLOAT)> ReflectFunction;
typedef std::function<FAUSTFLOAT()> ModifyFunction;

struct ExtZoneParam {

    virtual void reflectZone() = 0;
    virtual void modifyZone() = 0;
    
    virtual void setReflectZoneFun(ReflectFunction reflect) = 0;
    virtual void setModifyZoneFun(ModifyFunction modify) = 0;
    
    virtual ~ExtZoneParam()
    {}
    
};

// Templated decoder

struct JSONUIDecoderBase
{
    virtual ~JSONUIDecoderBase()
    {}
    
    virtual void metadata(Meta* m) = 0;
    virtual void metadata(MetaGlue* glue) = 0;
    virtual int getDSPSize() = 0;
    virtual std::string getName() = 0;
    virtual std::string getLibVersion() = 0;
    virtual std::string getCompileOptions() = 0;
    virtual std::vector<std::string> getLibraryList() = 0;
    virtual std::vector<std::string> getIncludePathnames() = 0;
    virtual int getNumInputs() = 0;
    virtual int getNumOutputs() = 0;
    virtual int getSampleRate(char* memory_block) = 0;
    virtual void setReflectZoneFun(int index, ReflectFunction fun) = 0;
    virtual void setModifyZoneFun(int index, ModifyFunction fun) = 0;
    virtual void setupDSPProxy(UI* ui_interface, char* memory_block) = 0;
    virtual bool hasDSPProxy() = 0;
    virtual std::vector<ExtZoneParam*>& getInputControls() = 0;
    virtual std::vector<ExtZoneParam*>& getOutputControls() = 0;
    virtual void resetUserInterface() = 0;
    virtual void resetUserInterface(char* memory_block, Soundfile* defaultsound = nullptr) = 0;
    virtual void buildUserInterface(UI* ui_interface) = 0;
    virtual void buildUserInterface(UI* ui_interface, char* memory_block) = 0;
    virtual void buildUserInterface(UIGlue* ui_interface, char* memory_block) = 0;
    virtual bool hasCompileOption(const std::string& option) = 0;
};

template <typename REAL>
struct JSONUIDecoderReal : public JSONUIDecoderBase {
    
    struct ZoneParam : public ExtZoneParam {
        
        FAUSTFLOAT fZone;
        ReflectFunction fReflect;
        ModifyFunction fModify;
        
    #if defined(TARGET_OS_IPHONE) || defined(WIN32)
        ZoneParam(ReflectFunction reflect = nullptr, ModifyFunction modify = nullptr)
        :fReflect(reflect), fModify(modify)
        {}
        void reflectZone() { if (fReflect) fReflect(fZone); }
        void modifyZone() { if (fModify) fZone = fModify(); }
    #else
        ZoneParam(ReflectFunction reflect = [](FAUSTFLOAT value) {}, ModifyFunction modify = []() { return FAUSTFLOAT(-1); })
        :fReflect(reflect), fModify(modify)
        {}
        void reflectZone() { fReflect(fZone); }
        void modifyZone() { fZone = fModify(); }
    #endif
        
        void setReflectZoneFun(ReflectFunction reflect) { fReflect = reflect; }
        void setModifyZoneFun(ModifyFunction modify) { fModify = modify; }
        
    };
    
    typedef std::vector<ExtZoneParam*> controlMap;
  
    std::string fName;
    std::string fFileName;
    std::string fJSON;
    std::string fVersion;
    std::string fCompileOptions;
    
    std::map<std::string, std::string> fMetadata;
    std::vector<itemInfo> fUiItems;
    
    std::vector<std::string> fLibraryList;
    std::vector<std::string> fIncludePathnames;
    
    int fNumInputs, fNumOutputs, fSRIndex;
    int fDSPSize;
    bool fDSPProxy;
    
    controlMap fPathInputTable;     // [path, ZoneParam]
    controlMap fPathOutputTable;    // [path, ZoneParam]
    
    bool startWith(const std::string& str, const std::string& prefix)
    {
        return (str.substr(0, prefix.size()) == prefix);
    }

    bool isInput(const std::string& type)
    {
        return (type == "vslider" || type == "hslider" || type == "nentry" || type == "button" || type == "checkbox");
    }
    bool isOutput(const std::string& type) { return (type == "hbargraph" || type == "vbargraph"); }
    bool isSoundfile(const std::string& type) { return (type == "soundfile"); }
    
    std::string getString(std::map<std::string, std::pair<std::string, double> >& map, const std::string& key)
    {
        return (map.find(key) != map.end()) ? map[key].first : "";
    }
    
    int getInt(std::map<std::string, std::pair<std::string, double> >& map, const std::string& key)
    {
        return (map.find(key) != map.end()) ? int(map[key].second) : -1;
    }
    
    void setReflectZoneFun(int index, ReflectFunction fun)
    {
        fPathInputTable[index]->setReflectZoneFun(fun);
    }
    
    void setModifyZoneFun(int index, ModifyFunction fun)
    {
        fPathOutputTable[index]->setModifyZoneFun(fun);
    }

    JSONUIDecoderReal(const std::string& json)
    {
        fJSON = json;
        const char* p = fJSON.c_str();
        std::map<std::string, std::pair<std::string, double> > meta_data1;
        std::map<std::string, std::vector<std::string> > meta_data2;
        parseJson(p, meta_data1, fMetadata, meta_data2, fUiItems);
        
        // meta_data1 contains <name : val>, <inputs : val>, <ouputs : val> pairs etc...
        fName = getString(meta_data1, "name");
        fFileName = getString(meta_data1, "filename");
        fVersion = getString(meta_data1, "version");
        fCompileOptions = getString(meta_data1, "compile_options");
        
        if (meta_data2.find("library_list") != meta_data2.end()) {
            fLibraryList = meta_data2["library_list"];
        } else {
            // 'library_list' is coded as successive 'library_pathN' metadata
            for (const auto& it : fMetadata) {
                if (startWith(it.first, "library_path")) {
                    fLibraryList.push_back(it.second);
                }
            }
        }
        if (meta_data2.find("include_pathnames") != meta_data2.end()) {
            fIncludePathnames = meta_data2["include_pathnames"];
        }
        
        fDSPSize = getInt(meta_data1, "size");
        fNumInputs = getInt(meta_data1, "inputs");
        fNumOutputs = getInt(meta_data1, "outputs");
        fSRIndex = getInt(meta_data1, "sr_index");
        fDSPProxy = false;
        
        // Prepare the fPathTable and init zone
        for (const auto& it : fUiItems) {
            std::string type = it.type;
            // Meta data declaration for input items
            if (isInput(type)) {
                ZoneParam* param = new ZoneParam();
                fPathInputTable.push_back(param);
                param->fZone = it.init;
            }
            // Meta data declaration for output items
            else if (isOutput(type)) {
                ZoneParam* param = new ZoneParam();
                fPathOutputTable.push_back(param);
                param->fZone = REAL(0);
            }
        }
    }
    
    virtual ~JSONUIDecoderReal()
    {
        for (const auto& it : fPathInputTable) {
            delete it;
        }
        for (const auto& it : fPathOutputTable) {
            delete it;
        }
    }
    
    void metadata(Meta* m)
    {
        for (const auto& it : fMetadata) {
            m->declare(it.first.c_str(), it.second.c_str());
        }
    }
    
    void metadata(MetaGlue* m)
    {
        for (const auto& it : fMetadata) {
            m->declare(m->metaInterface, it.first.c_str(), it.second.c_str());
        }
    }
    
    void resetUserInterface()
    {
        int item = 0;
        for (const auto& it : fUiItems) {
            if (isInput(it.type)) {
                static_cast<ZoneParam*>(fPathInputTable[item++])->fZone = it.init;
            }
        }
    }
    
    void resetUserInterface(char* memory_block, Soundfile* defaultsound = nullptr)
    {
        for (const auto& it : fUiItems) {
            int index = it.index;
            if (isInput(it.type)) {
                *REAL_ADR(index) = it.init;
            } else if (isSoundfile(it.type)) {
                if (*SOUNDFILE_ADR(index) == nullptr) {
                    *SOUNDFILE_ADR(index) = defaultsound;
                }
            }
        }
    }
    
    int getSampleRate(char* memory_block)
    {
        return *reinterpret_cast<int*>(&memory_block[fSRIndex]);
    }
    
    void setupDSPProxy(UI* ui_interface, char* memory_block)
    {
        if (!fDSPProxy) {
            fDSPProxy = true;
            int countIn = 0;
            int countOut = 0;
            for (const auto& it : fUiItems) {
                std::string type = it.type;
                int index = it.index;
                if (isInput(type)) {
                    fPathInputTable[countIn++]->setReflectZoneFun([=](FAUSTFLOAT value) { *REAL_ADR(index) = REAL(value); });
                } else if (isOutput(type)) {
                    fPathOutputTable[countOut++]->setModifyZoneFun([=]() { return FAUSTFLOAT(*REAL_ADR(index)); });
                }
            }
        }
        
        // Setup soundfile in any case
        for (const auto& it : fUiItems) {
            if (isSoundfile(it.type)) {
                ui_interface->addSoundfile(it.label.c_str(), it.url.c_str(), SOUNDFILE_ADR(it.index));
            }
        }
    }
    
    bool hasDSPProxy() { return fDSPProxy; }
  
    void buildUserInterface(UI* ui_interface)
    {
        // MANDATORY: to be sure floats or double are correctly parsed
        char* tmp_local = setlocale(LC_ALL, nullptr);
        if (tmp_local != NULL) {
            tmp_local = strdup(tmp_local);
        }
        setlocale(LC_ALL, "C");
        
        int countIn = 0;
        int countOut = 0;
        int countSound = 0;
        
        for (const auto& it : fUiItems) {
            
            std::string type = it.type;
            REAL init = REAL(it.init);
            REAL min = REAL(it.fmin);
            REAL max = REAL(it.fmax);
            REAL step = REAL(it.step);
            
            // Meta data declaration for input items
            if (isInput(type)) {
                for (size_t i = 0; i < it.meta.size(); i++) {
                    ui_interface->declare(&static_cast<ZoneParam*>(fPathInputTable[countIn])->fZone, it.meta[i].first.c_str(), it.meta[i].second.c_str());
                }
            }
            // Meta data declaration for output items
            else if (isOutput(type)) {
                for (size_t i = 0; i < it.meta.size(); i++) {
                    ui_interface->declare(&static_cast<ZoneParam*>(fPathOutputTable[countOut])->fZone, it.meta[i].first.c_str(), it.meta[i].second.c_str());
                }
            }
            // Meta data declaration for group opening or closing
            else {
                for (size_t i = 0; i < it.meta.size(); i++) {
                    ui_interface->declare(0, it.meta[i].first.c_str(), it.meta[i].second.c_str());
                }
            }
            
            if (type == "hgroup") {
                ui_interface->openHorizontalBox(it.label.c_str());
            } else if (type == "vgroup") {
                ui_interface->openVerticalBox(it.label.c_str());
            } else if (type == "tgroup") {
                ui_interface->openTabBox(it.label.c_str());
            } else if (type == "vslider") {
                ui_interface->addVerticalSlider(it.label.c_str(), &static_cast<ZoneParam*>(fPathInputTable[countIn])->fZone, init, min, max, step);
            } else if (type == "hslider") {
                ui_interface->addHorizontalSlider(it.label.c_str(), &static_cast<ZoneParam*>(fPathInputTable[countIn])->fZone, init, min, max, step);
            } else if (type == "checkbox") {
                ui_interface->addCheckButton(it.label.c_str(), &static_cast<ZoneParam*>(fPathInputTable[countIn])->fZone);
            } else if (type == "soundfile") {
                // Nothing
            } else if (type == "hbargraph") {
                ui_interface->addHorizontalBargraph(it.label.c_str(), &static_cast<ZoneParam*>(fPathOutputTable[countOut])->fZone, min, max);
            } else if (type == "vbargraph") {
                ui_interface->addVerticalBargraph(it.label.c_str(), &static_cast<ZoneParam*>(fPathOutputTable[countOut])->fZone, min, max);
            } else if (type == "nentry") {
                ui_interface->addNumEntry(it.label.c_str(), &static_cast<ZoneParam*>(fPathInputTable[countIn])->fZone, init, min, max, step);
            } else if (type == "button") {
                ui_interface->addButton(it.label.c_str(), &static_cast<ZoneParam*>(fPathInputTable[countIn])->fZone);
            } else if (type == "close") {
                ui_interface->closeBox();
            }
            
            if (isInput(type)) {
                countIn++;
            } else if (isOutput(type)) {
                countOut++;
            } else if (isSoundfile(type)) {
                countSound++;
            }
        }
        
        if (tmp_local != NULL) {
            setlocale(LC_ALL, tmp_local);
            free(tmp_local);
        }
    }
    
    void buildUserInterface(UI* ui_interface, char* memory_block)
    {
        // MANDATORY: to be sure floats or double are correctly parsed
        char* tmp_local = setlocale(LC_ALL, nullptr);
        if (tmp_local != NULL) {
            tmp_local = strdup(tmp_local);
        }
        setlocale(LC_ALL, "C");
        
        for (const auto& it : fUiItems) {
            
            std::string type = it.type;
            int index = it.index;
            REAL init = REAL(it.init);
            REAL min = REAL(it.fmin);
            REAL max = REAL(it.fmax);
            REAL step = REAL(it.step);
            
            // Meta data declaration for input items
            if (isInput(type)) {
                for (size_t i = 0; i < it.meta.size(); i++) {
                    REAL_UI(ui_interface)->declare(REAL_ADR(index), it.meta[i].first.c_str(), it.meta[i].second.c_str());
                }
            }
            // Meta data declaration for output items
            else if (isOutput(type)) {
                for (size_t i = 0; i < it.meta.size(); i++) {
                    REAL_UI(ui_interface)->declare(REAL_ADR(index), it.meta[i].first.c_str(), it.meta[i].second.c_str());
                }
            }
            // Meta data declaration for group opening or closing
            else {
                for (size_t i = 0; i < it.meta.size(); i++) {
                    REAL_UI(ui_interface)->declare(0, it.meta[i].first.c_str(), it.meta[i].second.c_str());
                }
            }
            
            if (type == "hgroup") {
                REAL_UI(ui_interface)->openHorizontalBox(it.label.c_str());
            } else if (type == "vgroup") {
                REAL_UI(ui_interface)->openVerticalBox(it.label.c_str());
            } else if (type == "tgroup") {
                REAL_UI(ui_interface)->openTabBox(it.label.c_str());
            } else if (type == "vslider") {
                REAL_UI(ui_interface)->addVerticalSlider(it.label.c_str(), REAL_ADR(index), init, min, max, step);
            } else if (type == "hslider") {
                REAL_UI(ui_interface)->addHorizontalSlider(it.label.c_str(), REAL_ADR(index), init, min, max, step);
            } else if (type == "checkbox") {
                REAL_UI(ui_interface)->addCheckButton(it.label.c_str(), REAL_ADR(index));
            } else if (type == "soundfile") {
                REAL_UI(ui_interface)->addSoundfile(it.label.c_str(), it.url.c_str(), SOUNDFILE_ADR(index));
            } else if (type == "hbargraph") {
                REAL_UI(ui_interface)->addHorizontalBargraph(it.label.c_str(), REAL_ADR(index), min, max);
            } else if (type == "vbargraph") {
                REAL_UI(ui_interface)->addVerticalBargraph(it.label.c_str(), REAL_ADR(index), min, max);
            } else if (type == "nentry") {
                REAL_UI(ui_interface)->addNumEntry(it.label.c_str(), REAL_ADR(index), init, min, max, step);
            } else if (type == "button") {
                REAL_UI(ui_interface)->addButton(it.label.c_str(), REAL_ADR(index));
            } else if (type == "close") {
                REAL_UI(ui_interface)->closeBox();
            }
        }
        
        if (tmp_local != NULL) {
            setlocale(LC_ALL, tmp_local);
            free(tmp_local);
        }
    }
    
    void buildUserInterface(UIGlue* ui_interface, char* memory_block)
    {
        // MANDATORY: to be sure floats or double are correctly parsed
        char* tmp_local = setlocale(LC_ALL, nullptr);
        if (tmp_local != NULL) {
            tmp_local = strdup(tmp_local);
        }
        setlocale(LC_ALL, "C");
        
        for (const auto& it : fUiItems) {
            
            std::string type = it.type;
            int index = it.index;
            REAL init = REAL(it.init);
            REAL min = REAL(it.fmin);
            REAL max = REAL(it.fmax);
            REAL step = REAL(it.step);
            
            // Meta data declaration for input items
            if (isInput(type)) {
                for (size_t i = 0; i < it.meta.size(); i++) {
                    ui_interface->declare(ui_interface->uiInterface, REAL_EXT_ADR(index), it.meta[i].first.c_str(), it.meta[i].second.c_str());
                }
            }
            // Meta data declaration for output items
            else if (isOutput(type)) {
                for (size_t i = 0; i < it.meta.size(); i++) {
                    ui_interface->declare(ui_interface->uiInterface, REAL_EXT_ADR(index), it.meta[i].first.c_str(), it.meta[i].second.c_str());
                }
            }
            // Meta data declaration for group opening or closing
            else {
                for (size_t i = 0; i < it.meta.size(); i++) {
                    ui_interface->declare(ui_interface->uiInterface, 0, it.meta[i].first.c_str(), it.meta[i].second.c_str());
                }
            }
            
            if (type == "hgroup") {
                ui_interface->openHorizontalBox(ui_interface->uiInterface, it.label.c_str());
            } else if (type == "vgroup") {
                ui_interface->openVerticalBox(ui_interface->uiInterface, it.label.c_str());
            } else if (type == "tgroup") {
                ui_interface->openTabBox(ui_interface->uiInterface, it.label.c_str());
            } else if (type == "vslider") {
                ui_interface->addVerticalSlider(ui_interface->uiInterface, it.label.c_str(), REAL_EXT_ADR(index), init, min, max, step);
            } else if (type == "hslider") {
                ui_interface->addHorizontalSlider(ui_interface->uiInterface, it.label.c_str(), REAL_EXT_ADR(index), init, min, max, step);
            } else if (type == "checkbox") {
                ui_interface->addCheckButton(ui_interface->uiInterface, it.label.c_str(), REAL_EXT_ADR(index));
            } else if (type == "soundfile") {
                ui_interface->addSoundfile(ui_interface->uiInterface, it.label.c_str(), it.url.c_str(), SOUNDFILE_ADR(index));
            } else if (type == "hbargraph") {
                ui_interface->addHorizontalBargraph(ui_interface->uiInterface, it.label.c_str(), REAL_EXT_ADR(index), min, max);
            } else if (type == "vbargraph") {
                ui_interface->addVerticalBargraph(ui_interface->uiInterface, it.label.c_str(), REAL_EXT_ADR(index), min, max);
            } else if (type == "nentry") {
                ui_interface->addNumEntry(ui_interface->uiInterface, it.label.c_str(), REAL_EXT_ADR(index), init, min, max, step);
            } else if (type == "button") {
                ui_interface->addButton(ui_interface->uiInterface, it.label.c_str(), REAL_EXT_ADR(index));
            } else if (type == "close") {
                ui_interface->closeBox(ui_interface->uiInterface);
            }
        }
        
        if (tmp_local != NULL) {
            setlocale(LC_ALL, tmp_local);
            free(tmp_local);
        }
    }
    
    bool hasCompileOption(const std::string& option)
    {
        std::istringstream iss(fCompileOptions);
        std::string token;
        while (std::getline(iss, token, ' ')) {
            if (token == option) return true;
        }
        return false;
    }
    
    int getDSPSize() { return fDSPSize; }
    std::string getName() { return fName; }
    std::string getLibVersion() { return fVersion; }
    std::string getCompileOptions() { return fCompileOptions; }
    std::vector<std::string> getLibraryList() { return fLibraryList; }
    std::vector<std::string> getIncludePathnames() { return fIncludePathnames; }
    int getNumInputs() { return fNumInputs; }
    int getNumOutputs() { return fNumOutputs; }
    
    std::vector<ExtZoneParam*>& getInputControls()
    {
        return fPathInputTable;
    }
    std::vector<ExtZoneParam*>& getOutputControls()
    {
        return fPathOutputTable;
    }
    
};

// FAUSTFLOAT templated decoder

struct JSONUIDecoder : public JSONUIDecoderReal<FAUSTFLOAT>
{
    JSONUIDecoder(const std::string& json):JSONUIDecoderReal<FAUSTFLOAT>(json)
    {}
};

// Generic factory

static JSONUIDecoderBase* createJSONUIDecoder(const std::string& json)
{
    JSONUIDecoder decoder(json);
    if (decoder.hasCompileOption("-double")) {
        return new JSONUIDecoderReal<double>(json);
    } else {
        return new JSONUIDecoderReal<float>(json);
    }
}

#endif
/**************************  END  JSONUIDecoder.h **************************/

/**
 * Proxy base_dsp definition created from the DSP JSON description.
 * This class allows a 'proxy' base_dsp to control a real base_dsp
 * possibly running somewhere else.
 */
class proxy_dsp : public base_dsp {

    protected:
    
        JSONUIDecoder* fDecoder;
        int fSampleRate;
    
        void init(const std::string& json)
        {
            fDecoder = new JSONUIDecoder(json);
            fSampleRate = -1;
        }
        
    public:
    
        proxy_dsp():fDecoder(nullptr), fSampleRate(-1)
        {}
    
        proxy_dsp(const std::string& json)
        {
            init(json);
        }
          
        proxy_dsp(base_dsp* base_dsp)
        {
            JSONUI builder(base_dsp->getNumInputs(), base_dsp->getNumOutputs());
            base_dsp->metadata(&builder);
            base_dsp->buildUserInterface(&builder);
            fSampleRate = base_dsp->getSampleRate();
            fDecoder = new JSONUIDecoder(builder.JSON());
        }
      
        virtual ~proxy_dsp()
        {
            delete fDecoder;
        }
    
        virtual int getNumInputs() { return fDecoder->fNumInputs; }
        virtual int getNumOutputs() { return fDecoder->fNumOutputs; }
        
        virtual void buildUserInterface(UI* ui) { fDecoder->buildUserInterface(ui); }
        
        // To possibly implement in a concrete proxy base_dsp 
        virtual void init(int sample_rate)
        {
            instanceInit(sample_rate);
        }
        virtual void instanceInit(int sample_rate)
        {
            instanceConstants(sample_rate);
            instanceResetUserInterface();
            instanceClear();
        }
        virtual void instanceConstants(int sample_rate) { fSampleRate = sample_rate; }
        virtual void instanceResetUserInterface() { fDecoder->resetUserInterface(); }
        virtual void instanceClear() {}
    
        virtual int getSampleRate() { return fSampleRate; }
    
        virtual proxy_dsp* clone() { return new proxy_dsp(fDecoder->fJSON); }
        virtual void metadata(Meta* m) { fDecoder->metadata(m); }
    
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {}
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {} 
        
};

#endif
/************************** END proxy-base_dsp.h **************************/

/************************** BEGIN DecoratorUI.h **************************
 FAUST Architecture File
Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
---------------------------------------------------------------------
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

EXCEPTION : As a special exception, you may create a larger work
that contains this FAUST architecture section and distribute
that work under terms of your choice, so long as this FAUST
architecture section is not modified.
*************************************************************************/

#ifndef Decorator_UI_H
#define Decorator_UI_H


//----------------------------------------------------------------
//  Generic UI empty implementation
//----------------------------------------------------------------

class GenericUI : public UI
{
    
    public:
        
        GenericUI() {}
        virtual ~GenericUI() {}
        
        // -- widget's layouts
        virtual void openTabBox(const char* label) {}
        virtual void openHorizontalBox(const char* label) {}
        virtual void openVerticalBox(const char* label) {}
        virtual void closeBox() {}
        
        // -- active widgets
        virtual void addButton(const char* label, FAUSTFLOAT* zone) {}
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone) {}
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {}
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {}
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {}
    
        // -- passive widgets
        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) {}
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) {}
    
        // -- soundfiles
        virtual void addSoundfile(const char* label, const char* soundpath, Soundfile** sf_zone) {}
    
        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val) {}
    
};

//----------------------------------------------------------------
//  Generic UI decorator
//----------------------------------------------------------------

class DecoratorUI : public UI
{
    
    protected:
        
        UI* fUI;
        
    public:
        
        DecoratorUI(UI* ui = 0):fUI(ui) {}
        virtual ~DecoratorUI() { delete fUI; }
        
        // -- widget's layouts
        virtual void openTabBox(const char* label)          { fUI->openTabBox(label); }
        virtual void openHorizontalBox(const char* label)   { fUI->openHorizontalBox(label); }
        virtual void openVerticalBox(const char* label)     { fUI->openVerticalBox(label); }
        virtual void closeBox()                             { fUI->closeBox(); }
        
        // -- active widgets
        virtual void addButton(const char* label, FAUSTFLOAT* zone)         { fUI->addButton(label, zone); }
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)    { fUI->addCheckButton(label, zone); }
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        { fUI->addVerticalSlider(label, zone, init, min, max, step); }
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        { fUI->addHorizontalSlider(label, zone, init, min, max, step); }
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        { fUI->addNumEntry(label, zone, init, min, max, step); }
        
        // -- passive widgets
        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        { fUI->addHorizontalBargraph(label, zone, min, max); }
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        { fUI->addVerticalBargraph(label, zone, min, max); }
    
        // -- soundfiles
        virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) { fUI->addSoundfile(label, filename, sf_zone); }
    
        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val) { fUI->declare(zone, key, val); }
    
};

// Defined here to simplify header #include inclusion 
class SoundUIInterface : public GenericUI {};

#endif
/**************************  END  DecoratorUI.h **************************/
/************************** BEGIN JSONControl.h **************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 *************************************************************************/

#ifndef __JSON_CONTROL__
#define __JSON_CONTROL__

#include <string>

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

struct JSONControl {
    
    virtual std::string getJSON() { return ""; }

    virtual void setParamValue(const std::string& path, FAUSTFLOAT value) {}

    virtual FAUSTFLOAT getParamValue(const std::string& path) { return 0; }
    
    virtual ~JSONControl()
    {}
    
};

#endif
/**************************  END  JSONControl.h **************************/

#define kActiveVoice    0
#define kFreeVoice     -1
#define kReleaseVoice  -2
#define kLegatoVoice   -3
#define kNoVoice       -4

#define VOICE_STOP_LEVEL  0.0005    // -70 db
#define MIX_BUFFER_SIZE   4096

/**
 * Allows to control zones in a grouped manner.
 */
class GroupUI : public GUI, public PathBuilder {

    private:

        std::map<std::string, uiGroupItem*> fLabelZoneMap;

        void insertMap(std::string label, FAUSTFLOAT* zone)
        {
            if (!MapUI::endsWith(label, "/gate")
                && !MapUI::endsWith(label, "/freq")
                && !MapUI::endsWith(label, "/key")
                && !MapUI::endsWith(label, "/gain")
                && !MapUI::endsWith(label, "/vel")
                && !MapUI::endsWith(label, "/velocity")) {

                // Groups all controllers except 'freq/key', 'gate', and 'gain/vel|velocity'
                if (fLabelZoneMap.find(label) != fLabelZoneMap.end()) {
                    fLabelZoneMap[label]->addZone(zone);
                } else {
                    fLabelZoneMap[label] = new uiGroupItem(this, zone);
                }
            }
        }

        uiCallbackItem* fPanic;

    public:

        GroupUI(FAUSTFLOAT* zone, uiCallback cb, void* arg)
        {
            fPanic = new uiCallbackItem(this, zone, cb, arg);
        }
    
        virtual ~GroupUI()
        {
            // 'fPanic' is kept and deleted in GUI, so do not delete here
        }

        // -- widget's layouts
        void openTabBox(const char* label)
        {
            pushLabel(label);
        }
        void openHorizontalBox(const char* label)
        {
            pushLabel(label);
        }
        void openVerticalBox(const char* label)
        {
            pushLabel(label);
        }
        void closeBox()
        {
            popLabel();
        }

        // -- active widgets
        void addButton(const char* label, FAUSTFLOAT* zone)
        {
            insertMap(buildPath(label), zone);
        }
        void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            insertMap(buildPath(label), zone);
        }
        void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            insertMap(buildPath(label), zone);
        }
        void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            insertMap(buildPath(label), zone);
        }
        void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            insertMap(buildPath(label), zone);
        }

        // -- passive widgets
        void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            insertMap(buildPath(label), zone);
        }
        void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            insertMap(buildPath(label), zone);
        }

};

/**
 * One voice of polyphony.
 */
struct dsp_voice : public MapUI, public decorator_dsp {
    
    typedef std::function<double(int)> TransformFunction;
  
    static double midiToFreq(double note)
    {
        return 440.0 * std::pow(2.0, (note-69.0)/12.0);
    }
    
    int fCurNote;                       // Playing note pitch
    int fNextNote;                      // In kLegatoVoice state, next note to play
    int fNextVel;                       // In kLegatoVoice state, next velocity to play
    int fDate;                          // KeyOn date
    int fRelease;                       // Current number of samples used in release mode to detect end of note
    FAUSTFLOAT fLevel;                  // Last audio block level
    double fReleaseLengthSec;           // Maximum release length in seconds (estimated time to silence after note release)
    std::vector<std::string> fGatePath; // Paths of 'gate' control
    std::vector<std::string> fGainPath; // Paths of 'gain/vel|velocity' control
    std::vector<std::string> fFreqPath; // Paths of 'freq/key' control
    TransformFunction        fKeyFun;   // MIDI key to freq conversion function
    TransformFunction        fVelFun;   // MIDI velocity to gain conversion function
    
    FAUSTFLOAT** fInputsSlice;
    FAUSTFLOAT** fOutputsSlice;
 
    dsp_voice(base_dsp* base_dsp):decorator_dsp(base_dsp)
    {
        // Default versions
        fVelFun = [](int velocity) { return double(velocity)/127.0; };
        fKeyFun = [](int pitch) { return midiToFreq(pitch); };
        base_dsp->buildUserInterface(this);
        fCurNote = kFreeVoice;
        fNextNote = fNextVel = -1;
        fLevel = FAUSTFLOAT(0);
        fDate = fRelease = 0;
        fReleaseLengthSec = 0.5;  // A half second is a reasonable default maximum release length.
        extractPaths(fGatePath, fFreqPath, fGainPath);
    }
    virtual ~dsp_voice()
    {}
    
    void computeSlice(int offset, int slice, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
    {
        FAUSTFLOAT** inputsSlice = static_cast<FAUSTFLOAT**>(alloca(sizeof(FAUSTFLOAT*) * getNumInputs()));
        for (int chan = 0; chan < getNumInputs(); chan++) {
            inputsSlice[chan] = &(inputs[chan][offset]);
        }
        FAUSTFLOAT** outputsSlice = static_cast<FAUSTFLOAT**>(alloca(sizeof(FAUSTFLOAT*) * getNumOutputs()));
        for (int chan = 0; chan < getNumOutputs(); chan++) {
            outputsSlice[chan] = &(outputs[chan][offset]);
        }
        compute(slice, inputsSlice, outputsSlice);
    }
    
    void computeLegato(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
    {
        int slice = count/2;
        
        // Reset envelops
        for (size_t i = 0; i < fGatePath.size(); i++) {
            setParamValue(fGatePath[i], FAUSTFLOAT(0));
        }
        
        // Compute current voice on half buffer
        computeSlice(0, slice, inputs, outputs);
         
        // Start next keyOn
        keyOn(fNextNote, fNextVel);
        
        // Compute on second half buffer
        computeSlice(slice, slice, inputs, outputs);
    }

    void extractPaths(std::vector<std::string>& gate, std::vector<std::string>& freq, std::vector<std::string>& gain)
    {
        // Keep gain/vel|velocity, freq/key and gate labels
        for (const auto& it : getMap()) {
            std::string path = it.first;
            if (endsWith(path, "/gate")) {
                gate.push_back(path);
            } else if (endsWith(path, "/freq")) {
                fKeyFun = [](int pitch) { return midiToFreq(pitch); };
                freq.push_back(path);
            } else if (endsWith(path, "/key")) {
                fKeyFun = [](int pitch) { return pitch; };
                freq.push_back(path);
            } else if (endsWith(path, "/gain")) {
                fVelFun = [](int velocity) { return double(velocity)/127.0; };
                gain.push_back(path);
            } else if (endsWith(path, "/vel") || endsWith(path, "/velocity")) {
                fVelFun = [](int velocity) { return double(velocity); };
                gain.push_back(path);
            }
        }
    }
    
    void reset()
    {
        init(getSampleRate());
    }
 
    void instanceClear()
    {
        decorator_dsp::instanceClear();
        fCurNote = kFreeVoice;
        fNextNote = fNextVel = -1;
        fLevel = FAUSTFLOAT(0);
        fDate = fRelease = 0;
    }
    
    // Keep 'pitch' and 'velocity' to fadeOut the current voice and start next one in the next buffer
    void keyOn(int pitch, int velocity, bool legato = false)
    {
        if (legato) {
            fNextNote = pitch;
            fNextVel = velocity;
        } else {
            keyOn(pitch, fVelFun(velocity));
        }
    }

    // Normalized MIDI velocity [0..1]
    void keyOn(int pitch, double velocity)
    {
        for (size_t i = 0; i < fFreqPath.size(); i++) {
            setParamValue(fFreqPath[i], fKeyFun(pitch));
        }
        for (size_t i = 0; i < fGatePath.size(); i++) {
            setParamValue(fGatePath[i], FAUSTFLOAT(1));
        }
        for (size_t i = 0; i < fGainPath.size(); i++) {
            setParamValue(fGainPath[i], velocity);
        }
        
        fCurNote = pitch;
    }

    void keyOff(bool hard = false)
    {
        // No use of velocity for now...
        for (size_t i = 0; i < fGatePath.size(); i++) {
            setParamValue(fGatePath[i], FAUSTFLOAT(0));
        }
        
        if (hard) {
            // Immediately stop voice
            fCurNote = kFreeVoice;
        } else {
            // Release voice
            fRelease = fReleaseLengthSec * fDSP->getSampleRate();
            fCurNote = kReleaseVoice;
        }
    }
 
    // Change the voice release
    void setReleaseLength(double sec)
    {
        fReleaseLengthSec = sec;
    }

};

/**
 * A group of voices.
 */
struct dsp_voice_group {

    GroupUI fGroups;

    std::vector<dsp_voice*> fVoiceTable; // Individual voices
    base_dsp* fVoiceGroup;                    // Voices group to be used for GUI grouped control

    FAUSTFLOAT fPanic;

    bool fVoiceControl;
    bool fGroupControl;

    dsp_voice_group(uiCallback cb, void* arg, bool control, bool group)
        :fGroups(&fPanic, cb, arg),
        fVoiceGroup(0), fPanic(FAUSTFLOAT(0)),
        fVoiceControl(control), fGroupControl(group)
    {}

    virtual ~dsp_voice_group()
    {
        for (size_t i = 0; i < fVoiceTable.size(); i++) {
            delete fVoiceTable[i];
        }
        delete fVoiceGroup;
    }

    void addVoice(dsp_voice* voice)
    {
        fVoiceTable.push_back(voice);
    }

    void clearVoices()
    {
        fVoiceTable.clear();
    }

    void init()
    {
        // Groups all uiItem for a given path
        fVoiceGroup = new proxy_dsp(fVoiceTable[0]);
        fVoiceGroup->buildUserInterface(&fGroups);
        for (size_t i = 0; i < fVoiceTable.size(); i++) {
            fVoiceTable[i]->buildUserInterface(&fGroups);
        }
    }
    
    void instanceResetUserInterface()
    {
        for (size_t i = 0; i < fVoiceTable.size(); i++) {
            fVoiceTable[i]->instanceResetUserInterface();
        }
    }

    void buildUserInterface(UI* ui_interface)
    {
        if (fVoiceTable.size() > 1) {
            ui_interface->openTabBox("Polyphonic");

            // Grouped voices UI
            ui_interface->openVerticalBox("Voices");
            ui_interface->addButton("Panic", &fPanic);
            fVoiceGroup->buildUserInterface(ui_interface);
            ui_interface->closeBox();

            // If not grouped, also add individual voices UI
            if (!fGroupControl || dynamic_cast<SoundUIInterface*>(ui_interface)) {
                for (size_t i = 0; i < fVoiceTable.size(); i++) {
                    char buffer[32];
                    snprintf(buffer, 32, ((fVoiceTable.size() < 8) ? "Voice%ld" : "V%ld"), long(i+1));
                    ui_interface->openHorizontalBox(buffer);
                    fVoiceTable[i]->buildUserInterface(ui_interface);
                    ui_interface->closeBox();
                }
            }

            ui_interface->closeBox();
        } else {
            fVoiceTable[0]->buildUserInterface(ui_interface);
        }
    }

};

/**
 * Base class for MIDI controllable polyphonic DSP.
 */
#ifdef EMCC
#endif

class dsp_poly : public decorator_dsp, public midi, public JSONControl {

    protected:
    
    #ifdef EMCC
        MapUI fMapUI;
        std::string fJSON;
        midi_handler fMidiHandler;
        MidiUI fMIDIUI;
    #endif
    
    public:
    
    #ifdef EMCC
        dsp_poly(base_dsp* base_dsp):decorator_dsp(base_dsp), fMIDIUI(&fMidiHandler)
        {
            JSONUI jsonui(getNumInputs(), getNumOutputs());
            buildUserInterface(&jsonui);
            fJSON = jsonui.JSON(true);
            buildUserInterface(&fMapUI);
            buildUserInterface(&fMIDIUI);
        }
    #else
        dsp_poly(base_dsp* base_dsp):decorator_dsp(base_dsp)
        {}
    #endif
    
        virtual ~dsp_poly() {}
    
        // Reimplemented for EMCC
    #ifdef EMCC
        virtual int getNumInputs() { return decorator_dsp::getNumInputs(); }
        virtual int getNumOutputs() { return decorator_dsp::getNumOutputs(); }
        virtual void buildUserInterface(UI* ui_interface) { decorator_dsp::buildUserInterface(ui_interface); }
        virtual int getSampleRate() { return decorator_dsp::getSampleRate(); }
        virtual void init(int sample_rate) { decorator_dsp::init(sample_rate); }
        virtual void instanceInit(int sample_rate) { decorator_dsp::instanceInit(sample_rate); }
        virtual void instanceConstants(int sample_rate) { decorator_dsp::instanceConstants(sample_rate); }
        virtual void instanceResetUserInterface() { decorator_dsp::instanceResetUserInterface(); }
        virtual void instanceClear() { decorator_dsp::instanceClear(); }
        virtual dsp_poly* clone() { return new dsp_poly(fDSP->clone()); }
        virtual void metadata(Meta* m) { decorator_dsp::metadata(m); }
    
        // Additional API
        std::string getJSON()
        {
            return fJSON;
        }
    
        virtual void setParamValue(const std::string& path, FAUSTFLOAT value)
        {
            fMapUI.setParamValue(path, value);
            GUI::updateAllGuis();
        }
        
        virtual FAUSTFLOAT getParamValue(const std::string& path) { return fMapUI.getParamValue(path); }

        virtual void computeJS(int count, uintptr_t inputs, uintptr_t outputs)
        {
            decorator_dsp::compute(count, reinterpret_cast<FAUSTFLOAT**>(inputs),reinterpret_cast<FAUSTFLOAT**>(outputs));
        }
    #endif
    
        virtual MapUI* keyOn(int channel, int pitch, int velocity)
        {
            return midi::keyOn(channel, pitch, velocity);
        }
        virtual void keyOff(int channel, int pitch, int velocity)
        {
            midi::keyOff(channel, pitch, velocity);
        }
        virtual void keyPress(int channel, int pitch, int press)
        {
            midi::keyPress(channel, pitch, press);
        }
        virtual void chanPress(int channel, int press)
        {
            midi::chanPress(channel, press);
        }
        virtual void ctrlChange(int channel, int ctrl, int value)
        {
            midi::ctrlChange(channel, ctrl, value);
        }
        virtual void ctrlChange14bits(int channel, int ctrl, int value)
        {
            midi::ctrlChange14bits(channel, ctrl, value);
        }
        virtual void pitchWheel(int channel, int wheel)
        {
        #ifdef EMCC
            fMIDIUI.pitchWheel(0., channel, wheel);
            GUI::updateAllGuis();
        #else
            midi::pitchWheel(channel, wheel);
        #endif
        }
        virtual void progChange(int channel, int pgm)
        {
            midi::progChange(channel, pgm);
        }
    
        // Change the voice release
        virtual void setReleaseLength(double seconds)
        {}
    
};

/**
 * Polyphonic DSP: groups a set of DSP to be played together or triggered by MIDI.
 *
 * All voices are preallocated by cloning the single DSP voice given at creation time.
 * Dynamic voice allocation is done in 'getFreeVoice'
 */
class mydsp_poly : public dsp_voice_group, public dsp_poly {

    private:

        FAUSTFLOAT** fMixBuffer;
        FAUSTFLOAT** fOutBuffer;
        midi_interface* fMidiHandler; // The midi_interface the DSP is connected to
        int fDate;
    
        void fadeOut(int count, FAUSTFLOAT** outBuffer)
        {
            // FadeOut on half buffer
            for (int chan = 0; chan < getNumOutputs(); chan++) {
                double factor = 1., step = 1./double(count);
                for (int frame = 0; frame < count; frame++) {
                    outBuffer[chan][frame] *= factor;
                    factor -= step;
                }
            }
        }
    
        FAUSTFLOAT mixCheckVoice(int count, FAUSTFLOAT** mixBuffer, FAUSTFLOAT** outBuffer)
        {
            FAUSTFLOAT level = 0;
            for (int chan = 0; chan < getNumOutputs(); chan++) {
                FAUSTFLOAT* mixChannel = mixBuffer[chan];
                FAUSTFLOAT* outChannel = outBuffer[chan];
                for (int frame = 0; frame < count; frame++) {
                    level = std::max<FAUSTFLOAT>(level, (FAUSTFLOAT)fabs(mixChannel[frame]));
                    outChannel[frame] += mixChannel[frame];
                }
            }
            return level;
        }
    
        void mixVoice(int count, FAUSTFLOAT** mixBuffer, FAUSTFLOAT** outBuffer)
        {
            for (int chan = 0; chan < getNumOutputs(); chan++) {
                FAUSTFLOAT* mixChannel = mixBuffer[chan];
                FAUSTFLOAT* outChannel = outBuffer[chan];
                for (int frame = 0; frame < count; frame++) {
                    outChannel[frame] += mixChannel[frame];
                }
            }
        }
    
        void copy(int count, FAUSTFLOAT** mixBuffer, FAUSTFLOAT** outBuffer)
        {
            for (int chan = 0; chan < getNumOutputs(); chan++) {
                memcpy(outBuffer[chan], mixBuffer[chan], count * sizeof(FAUSTFLOAT));
            }
        }

        void clear(int count, FAUSTFLOAT** outBuffer)
        {
            for (int chan = 0; chan < getNumOutputs(); chan++) {
                memset(outBuffer[chan], 0, count * sizeof(FAUSTFLOAT));
            }
        }
    
        int getPlayingVoice(int pitch)
        {
            int voice_playing = kNoVoice;
            int oldest_date_playing = INT_MAX;
            
            for (size_t i = 0; i < fVoiceTable.size(); i++) {
                if (fVoiceTable[i]->fCurNote == pitch) {
                    // Keeps oldest playing voice
                    if (fVoiceTable[i]->fDate < oldest_date_playing) {
                        oldest_date_playing = fVoiceTable[i]->fDate;
                        voice_playing = int(i);
                    }
                }
            }
            
            return voice_playing;
        }
    
        int allocVoice(int voice, int type)
        {
            fVoiceTable[voice]->fDate++;
            fVoiceTable[voice]->fCurNote = type;
            return voice;
        }
    
        // Always returns a voice
        int getFreeVoice()
        {
            // Looks for the first available voice
            for (size_t i = 0; i < fVoiceTable.size(); i++) {
                if (fVoiceTable[i]->fCurNote == kFreeVoice) {
                    return allocVoice(i, kActiveVoice);
                }
            }

            // Otherwise steal one
            int voice_release = kNoVoice;
            int voice_playing = kNoVoice;
            int oldest_date_release = INT_MAX;
            int oldest_date_playing = INT_MAX;

            // Scan all voices
            for (size_t i = 0; i < fVoiceTable.size(); i++) {
                if (fVoiceTable[i]->fCurNote == kReleaseVoice) {
                    // Keeps oldest release voice
                    if (fVoiceTable[i]->fDate < oldest_date_release) {
                        oldest_date_release = fVoiceTable[i]->fDate;
                        voice_release = int(i);
                    }
                } else {
                    // Otherwise keeps oldest playing voice
                    if (fVoiceTable[i]->fDate < oldest_date_playing) {
                        oldest_date_playing = fVoiceTable[i]->fDate;
                        voice_playing = int(i);
                    }
                }
            }
        
            // Then decide which one to steal
            if (oldest_date_release != INT_MAX) {
                fprintf(stderr, "Steal release voice : voice_date = %d cur_date = %d voice = %d \n",
                        fVoiceTable[voice_release]->fDate,
                        fDate,
                        voice_release);
                return allocVoice(voice_release, kLegatoVoice);
            } else if (oldest_date_playing != INT_MAX) {
                fprintf(stderr, "Steal playing voice : voice_date = %d cur_date = %d voice = %d \n",
                        fVoiceTable[voice_playing]->fDate,
                        fDate,
                        voice_release);
                return allocVoice(voice_playing, kLegatoVoice);
            } else {
                assert(false);
                return kNoVoice;
            }
        }

        static void panic(FAUSTFLOAT val, void* arg)
        {
            if (val == FAUSTFLOAT(1)) {
                static_cast<mydsp_poly*>(arg)->allNotesOff(true);
            }
        }

        bool checkPolyphony()
        {
            if (fVoiceTable.size() > 0) {
                return true;
            } else {
                fprintf(stderr, "DSP is not polyphonic...\n");
                return false;
            }
        }

    public:
    
        /**
         * Constructor.
         *
         * @param base_dsp - the base_dsp to be used for one voice. Beware: mydsp_poly will use and finally delete the pointer.
         * @param nvoices - number of polyphony voices, should be at least 1
         * @param control - whether voices will be dynamically allocated and controlled (typically by a MIDI controler).
         *                If false all voices are always running.
         * @param group - if true, voices are not individually accessible, a global "Voices" tab will automatically dispatch
         *                a given control on all voices, assuming GUI::updateAllGuis() is called.
         *                If false, all voices can be individually controlled.
         *
         */
        mydsp_poly(base_dsp* base_dsp,
                   int nvoices,
                   bool control = false,
                   bool group = true)
        : dsp_voice_group(panic, this, control, group), dsp_poly(base_dsp) // base_dsp parameter is deallocated by ~dsp_poly
        {
            fDate = 0;
            fMidiHandler = nullptr;

            // Create voices
            assert(nvoices > 0);
            for (int i = 0; i < nvoices; i++) {
                addVoice(new dsp_voice(base_dsp->clone()));
            }

            // Init audio output buffers
            fMixBuffer = new FAUSTFLOAT*[getNumOutputs()];
            fOutBuffer = new FAUSTFLOAT*[getNumOutputs()];
            for (int chan = 0; chan < getNumOutputs(); chan++) {
                fMixBuffer[chan] = new FAUSTFLOAT[MIX_BUFFER_SIZE];
                fOutBuffer[chan] = new FAUSTFLOAT[MIX_BUFFER_SIZE];
            }

            dsp_voice_group::init();
        }

        virtual ~mydsp_poly()
        {
            // Remove from fMidiHandler
            if (fMidiHandler) fMidiHandler->removeMidiIn(this);
            for (int chan = 0; chan < getNumOutputs(); chan++) {
                delete[] fMixBuffer[chan];
                delete[] fOutBuffer[chan];
            }
            delete[] fMixBuffer;
            delete[] fOutBuffer;
            
        }

        // DSP API
        void buildUserInterface(UI* ui_interface)
        {
            // MidiUI ui_interface contains the midi_handler connected to the MIDI driver
            if (dynamic_cast<midi_interface*>(ui_interface)) {
                fMidiHandler = dynamic_cast<midi_interface*>(ui_interface);
                fMidiHandler->addMidiIn(this);
            }
            dsp_voice_group::buildUserInterface(ui_interface);
        }

        void init(int sample_rate)
        {
            decorator_dsp::init(sample_rate);
            fVoiceGroup->init(sample_rate);
            fPanic = FAUSTFLOAT(0);
            
            // Init voices
            for (size_t i = 0; i < fVoiceTable.size(); i++) {
                fVoiceTable[i]->init(sample_rate);
            }
        }
    
        void instanceInit(int samplingFreq)
        {
            instanceConstants(samplingFreq);
            instanceResetUserInterface();
            instanceClear();
        }

        void instanceConstants(int sample_rate)
        {
            decorator_dsp::instanceConstants(sample_rate);
            fVoiceGroup->instanceConstants(sample_rate);
            
            // Init voices
            for (size_t i = 0; i < fVoiceTable.size(); i++) {
                fVoiceTable[i]->instanceConstants(sample_rate);
            }
        }

        void instanceResetUserInterface()
        {
            decorator_dsp::instanceResetUserInterface();
            fVoiceGroup->instanceResetUserInterface();
            fPanic = FAUSTFLOAT(0);
            
            for (size_t i = 0; i < fVoiceTable.size(); i++) {
                fVoiceTable[i]->instanceResetUserInterface();
            }
        }

        void instanceClear()
        {
            decorator_dsp::instanceClear();
            fVoiceGroup->instanceClear();
            
            for (size_t i = 0; i < fVoiceTable.size(); i++) {
                fVoiceTable[i]->instanceClear();
            }
        }

        virtual mydsp_poly* clone()
        {
            return new mydsp_poly(fDSP->clone(), int(fVoiceTable.size()), fVoiceControl, fGroupControl);
        }

        void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            assert(count <= MIX_BUFFER_SIZE);

            // First clear the intermediate fOutBuffer
            clear(count, fOutBuffer);

            if (fVoiceControl) {
                // Mix all playing voices
                for (size_t i = 0; i < fVoiceTable.size(); i++) {
                    dsp_voice* voice = fVoiceTable[i];
                    if (voice->fCurNote == kLegatoVoice) {
                        // Play from current note and next note
                        voice->computeLegato(count, inputs, fMixBuffer);
                        // FadeOut on first half buffer
                        fadeOut(count/2, fMixBuffer);
                        // Mix it in result
                        voice->fLevel = mixCheckVoice(count, fMixBuffer, fOutBuffer);
                    } else if (voice->fCurNote != kFreeVoice) {
                        // Compute current note
                        voice->compute(count, inputs, fMixBuffer);
                        // Mix it in result
                        voice->fLevel = mixCheckVoice(count, fMixBuffer, fOutBuffer);
                        // Check the level to possibly set the voice in kFreeVoice again
                        voice->fRelease -= count;
                        if ((voice->fCurNote == kReleaseVoice)
                            && (voice->fRelease < 0)
                            && (voice->fLevel < VOICE_STOP_LEVEL)) {
                            voice->fCurNote = kFreeVoice;
                        }
                    }
                }
            } else {
                // Mix all voices
                for (size_t i = 0; i < fVoiceTable.size(); i++) {
                    fVoiceTable[i]->compute(count, inputs, fMixBuffer);
                    mixVoice(count, fMixBuffer, fOutBuffer);
                }
            }
            
            // Finally copy intermediate buffer to outputs
            copy(count, fOutBuffer, outputs);
        }

        void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            compute(count, inputs, outputs);
        }
    
        // Terminate all active voices, gently or immediately (depending of 'hard' value)
        void allNotesOff(bool hard = false)
        {
            for (size_t i = 0; i < fVoiceTable.size(); i++) {
                fVoiceTable[i]->keyOff(hard);
            }
        }
 
        // Additional polyphonic API
        MapUI* newVoice()
        {
            return fVoiceTable[getFreeVoice()];
        }

        void deleteVoice(MapUI* voice)
        {
            auto it = find(fVoiceTable.begin(), fVoiceTable.end(), reinterpret_cast<dsp_voice*>(voice));
            if (it != fVoiceTable.end()) {
                dsp_voice* voice = *it;
                voice->keyOff();
                voice->reset();
            } else {
                fprintf(stderr, "Voice not found\n");
            }
        }

        // MIDI API
        MapUI* keyOn(int channel, int pitch, int velocity)
        {
            if (checkPolyphony()) {
                int voice = getFreeVoice();
                fVoiceTable[voice]->keyOn(pitch, velocity, fVoiceTable[voice]->fCurNote == kLegatoVoice);
                return fVoiceTable[voice];
            } else {
                return 0;
            }
        }

        void keyOff(int channel, int pitch, int velocity = 127)
        {
            if (checkPolyphony()) {
                int voice = getPlayingVoice(pitch);
                if (voice != kNoVoice) {
                    fVoiceTable[voice]->keyOff();
                } else {
                    fprintf(stderr, "Playing pitch = %d not found\n", pitch);
                }
            }
        }

        void ctrlChange(int channel, int ctrl, int value)
        {
            if (ctrl == ALL_NOTES_OFF || ctrl == ALL_SOUND_OFF) {
                allNotesOff();
            }
        }

        // Change the voice release
        void setReleaseLength(double seconds)
        {
            for (size_t i = 0; i < fVoiceTable.size(); i++) {
                fVoiceTable[i]->setReleaseLength(seconds);
            }
        }

};

/**
 * Polyphonic DSP with an integrated effect.
 */
class dsp_poly_effect : public dsp_poly {
    
    private:
    
        // fPolyDSP will respond to MIDI messages.
        dsp_poly* fPolyDSP;
        
    public:
        
        dsp_poly_effect(dsp_poly* voice, base_dsp* combined)
        :dsp_poly(combined), fPolyDSP(voice)
        {}
        
        virtual ~dsp_poly_effect()
        {
            // dsp_poly_effect is also a decorator_dsp, which will free fPolyDSP
        }
    
        // MIDI API
        MapUI* keyOn(int channel, int pitch, int velocity)
        {
            return fPolyDSP->keyOn(channel, pitch, velocity);
        }
        void keyOff(int channel, int pitch, int velocity)
        {
            fPolyDSP->keyOff(channel, pitch, velocity);
        }
        void keyPress(int channel, int pitch, int press)
        {
            fPolyDSP->keyPress(channel, pitch, press);
        }
        void chanPress(int channel, int press)
        {
            fPolyDSP->chanPress(channel, press);
        }
        void ctrlChange(int channel, int ctrl, int value)
        {
            fPolyDSP->ctrlChange(channel, ctrl, value);
        }
        void ctrlChange14bits(int channel, int ctrl, int value)
        {
            fPolyDSP->ctrlChange14bits(channel, ctrl, value);
        }
        void pitchWheel(int channel, int wheel)
        {
            fPolyDSP->pitchWheel(channel, wheel);
        }
        void progChange(int channel, int pgm)
        {
            fPolyDSP->progChange(channel, pgm);
        }
    
        // Change the voice release
        void setReleaseLength(double sec)
        {
            fPolyDSP->setReleaseLength(sec);
        }
    
};

/**
 * Polyphonic DSP factory class. Helper code to support polyphonic DSP source with an integrated effect.
 */
struct dsp_poly_factory : public dsp_factory {
    
    dsp_factory* fProcessFactory;
    dsp_factory* fEffectFactory;
    
    base_dsp* adaptDSP(base_dsp* base_dsp, bool is_double)
    {
        return (is_double) ? new dsp_sample_adapter<double, float>(base_dsp) : base_dsp;
    }

    dsp_poly_factory(dsp_factory* process_factory = nullptr,
                     dsp_factory* effect_factory = nullptr):
    fProcessFactory(process_factory)
    ,fEffectFactory(effect_factory)
    {}

    virtual ~dsp_poly_factory()
    {}

    virtual std::string getName() { return fProcessFactory->getName(); }
    virtual std::string getSHAKey() { return fProcessFactory->getSHAKey(); }
    virtual std::string getDSPCode() { return fProcessFactory->getDSPCode(); }
    virtual std::string getCompileOptions() { return fProcessFactory->getCompileOptions(); }
    virtual std::vector<std::string> getLibraryList() { return fProcessFactory->getLibraryList(); }
    virtual std::vector<std::string> getIncludePathnames() { return fProcessFactory->getIncludePathnames(); }

    std::string getEffectCode(const std::string& dsp_content)
    {
        std::stringstream effect_code;
        effect_code << "adapt(1,1) = _; adapt(2,2) = _,_; adapt(1,2) = _ <: _,_; adapt(2,1) = _,_ :> _;";
        effect_code << "adaptor(F,G) = adapt(outputs(F),inputs(G)); dsp_code = environment{ " << dsp_content << " };";
        effect_code << "process = adaptor(dsp_code.process, dsp_code.effect) : dsp_code.effect;";
        return effect_code.str();
    }

    virtual void setMemoryManager(dsp_memory_manager* manager)
    {
        fProcessFactory->setMemoryManager(manager);
        if (fEffectFactory) {
            fEffectFactory->setMemoryManager(manager);
        }
    }
    virtual dsp_memory_manager* getMemoryManager() { return fProcessFactory->getMemoryManager(); }

    /* Create a new polyphonic DSP instance with global effect, to be deleted with C++ 'delete'
     *
     * @param nvoices - number of polyphony voices, should be at least 1
     * @param control - whether voices will be dynamically allocated and controlled (typically by a MIDI controler).
     *                If false all voices are always running.
     * @param group - if true, voices are not individually accessible, a global "Voices" tab will automatically dispatch
     *                a given control on all voices, assuming GUI::updateAllGuis() is called.
     *                If false, all voices can be individually controlled.
     * @param is_double - if true, internally allocated DSPs will be adapted to receive 'double' samples.
     */
    dsp_poly* createPolyDSPInstance(int nvoices, bool control, bool group, bool is_double = false)
    {
        dsp_poly* dsp_poly = new mydsp_poly(adaptDSP(fProcessFactory->createDSPInstance(), is_double), nvoices, control, group);
        if (fEffectFactory) {
            // the 'dsp_poly' object has to be controlled with MIDI, so kept separated from new dsp_sequencer(...) object
            return new dsp_poly_effect(dsp_poly, new dsp_sequencer(dsp_poly, adaptDSP(fEffectFactory->createDSPInstance(), is_double)));
        } else {
            return new dsp_poly_effect(dsp_poly, dsp_poly);
        }
    }

    /* Create a new DSP instance, to be deleted with C++ 'delete' */
    base_dsp* createDSPInstance()
    {
        return fProcessFactory->createDSPInstance();
    }

};

#endif // __poly_dsp__
/************************** END poly-base_dsp.h **************************/
#ifndef PLUGIN_MAGIC
/************************** BEGIN JuceGUI.h *****************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef JUCE_GUI_H
#define JUCE_GUI_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include <stack>

#include "../JuceLibraryCode/JuceHeader.h"


// Definition of the standard size of the different elements

#define kKnobWidth 100
#define kKnobHeight 100

#define kVSliderWidth 80
#define kVSliderHeight 250

#define kHSliderWidth 350
#define kHSliderHeight 50

#define kButtonWidth 100
#define kButtonHeight 50

#define kCheckButtonWidth 60
#define kCheckButtonHeight 40

#define kMenuWidth 100
#define kMenuHeight 50

#define kRadioButtonWidth 100
#define kRadioButtonHeight 55

#define kNumEntryWidth 100
#define kNumEntryHeight 50

#define kNumDisplayWidth 75
#define kNumDisplayHeight 50

#define kVBargraphWidth 60
#define kVBargraphHeight 250

#define kHBargraphWidth 350
#define kHBargraphHeight 50

#define kLedWidth 25
#define kLedHeight 25

#define kNameHeight 14

#define kMargin 4

/**
 * \brief       Custom LookAndFeel class.
 * \details     Define the appearance of all the JUCE widgets.
 */

struct CustomLookAndFeel : public juce::LookAndFeel_V3
{
    void drawRoundThumb (juce::Graphics& g, const float x, const float y,
                         const float diameter, const juce::Colour& colour, float outlineThickness)
    {
        const juce::Rectangle<float> a (x, y, diameter, diameter);
        const float halfThickness = outlineThickness * 0.5f;

        juce::Path p;
        p.addEllipse (x + halfThickness, y + halfThickness, diameter - outlineThickness, diameter - outlineThickness);

        const juce::DropShadow ds (juce::Colours::black, 1, juce::Point<int> (0, 0));
        ds.drawForPath (g, p);

        g.setColour (colour);
        g.fillPath (p);

        g.setColour (colour.brighter());
        g.strokePath (p, juce::PathStrokeType (outlineThickness));
    }

    void drawButtonBackground (juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColour,
                               bool isMouseOverButton, bool isButtonDown) override
    {
        juce::Colour baseColour (backgroundColour.withMultipliedSaturation (button.hasKeyboardFocus (true) ? 1.3f : 0.9f)
                           .withMultipliedAlpha (button.isEnabled() ? 0.9f : 0.5f));

        if (isButtonDown || isMouseOverButton)
            baseColour = baseColour.contrasting (isButtonDown ? 0.2f : 0.1f);

        const bool flatOnLeft   = button.isConnectedOnLeft();
        const bool flatOnRight  = button.isConnectedOnRight();
        const bool flatOnTop    = button.isConnectedOnTop();
        const bool flatOnBottom = button.isConnectedOnBottom();

        const float width  = button.getWidth() - 1.0f;
        const float height = button.getHeight() - 1.0f;

        if (width > 0 && height > 0)
        {
            const float cornerSize = juce::jmin(15.0f, juce::jmin(width, height) * 0.45f);
            const float lineThickness = cornerSize * 0.1f;
            const float halfThickness = lineThickness * 0.5f;

            juce::Path outline;
            outline.addRoundedRectangle (0.5f + halfThickness, 0.5f + halfThickness, width - lineThickness, height - lineThickness,
                                         cornerSize, cornerSize,
                                         ! (flatOnLeft  || flatOnTop),
                                         ! (flatOnRight || flatOnTop),
                                         ! (flatOnLeft  || flatOnBottom),
                                         ! (flatOnRight || flatOnBottom));

            const juce::Colour outlineColour (button.findColour (button.getToggleState() ? juce::TextButton::textColourOnId
                                        : juce::TextButton::textColourOffId));

            g.setColour (baseColour);
            g.fillPath (outline);

            if (! button.getToggleState()) {
                g.setColour (outlineColour);
                g.strokePath (outline, juce::PathStrokeType (lineThickness));
            }
        }
    }

    void drawTickBox (juce::Graphics& g, juce::Component& component,
                      float x, float y, float w, float h,
                      bool ticked,
                      bool isEnabled,
                      bool isMouseOverButton,
                      bool isButtonDown) override
    {
        const float boxSize = w * 0.7f;

        bool isDownOrDragging = component.isEnabled() && (component.isMouseOverOrDragging() || component.isMouseButtonDown());
        const juce::Colour colour (component.findColour (juce::TextButton::buttonColourId).withMultipliedSaturation ((component.hasKeyboardFocus (false) || isDownOrDragging) ? 1.3f : 0.9f)
                             .withMultipliedAlpha (component.isEnabled() ? 1.0f : 0.7f));

        drawRoundThumb (g, x, y + (h - boxSize) * 0.5f, boxSize, colour,
                        isEnabled ? ((isButtonDown || isMouseOverButton) ? 1.1f : 0.5f) : 0.3f);

        if (ticked) {
            const juce::Path tick (juce::LookAndFeel_V2::getTickShape (6.0f));
            g.setColour (isEnabled ? findColour (juce::TextButton::buttonOnColourId) : juce::Colours::grey);

            const float scale = 9.0f;
            const juce::AffineTransform trans (juce::AffineTransform::scale (w / scale, h / scale)
                                         .translated (x - 2.5f, y + 1.0f));
            g.fillPath (tick, trans);
        }
    }

    void drawLinearSliderThumb (juce::Graphics& g, int x, int y, int width, int height,
                                float sliderPos, float minSliderPos, float maxSliderPos,
                                const juce::Slider::SliderStyle style, juce::Slider& slider) override
    {
        const float sliderRadius = (float)(getSliderThumbRadius (slider) - 2);

        bool isDownOrDragging = slider.isEnabled() && (slider.isMouseOverOrDragging() || slider.isMouseButtonDown());
        juce::Colour knobColour (slider.findColour (juce::Slider::thumbColourId).withMultipliedSaturation ((slider.hasKeyboardFocus (false) || isDownOrDragging) ? 1.3f : 0.9f)
                           .withMultipliedAlpha (slider.isEnabled() ? 1.0f : 0.7f));

        if (style == juce::Slider::LinearHorizontal || style == juce::Slider::LinearVertical) {
            float kx, ky;

            if (style == juce::Slider::LinearVertical) {
                kx = x + width * 0.5f;
                ky = sliderPos;
            } else {
                kx = sliderPos;
                ky = y + height * 0.5f;
            }

            const float outlineThickness = slider.isEnabled() ? 0.8f : 0.3f;

            drawRoundThumb (g,
                            kx - sliderRadius,
                            ky - sliderRadius,
                            sliderRadius * 2.0f,
                            knobColour, outlineThickness);
        } else {
            // Just call the base class for the demo
            juce::LookAndFeel_V2::drawLinearSliderThumb (g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
        }
    }

    void drawLinearSlider (juce::Graphics& g, int x, int y, int width, int height,
                           float sliderPos, float minSliderPos, float maxSliderPos,
                           const juce::Slider::SliderStyle style, juce::Slider& slider) override
    {
        g.fillAll (slider.findColour (juce::Slider::backgroundColourId));

        if (style == juce::Slider::LinearBar || style == juce::Slider::LinearBarVertical) {
            const float fx = (float)x, fy = (float)y, fw = (float)width, fh = (float)height;

            juce::Path p;

            if (style == juce::Slider::LinearBarVertical)
                p.addRectangle (fx, sliderPos, fw, 1.0f + fh - sliderPos);
            else
                p.addRectangle (fx, fy, sliderPos - fx, fh);

            juce::Colour baseColour (slider.findColour (juce::Slider::rotarySliderFillColourId)
                               .withMultipliedSaturation (slider.isEnabled() ? 1.0f : 0.5f)
                               .withMultipliedAlpha (0.8f));

            g.setColour (baseColour);
            g.fillPath (p);

            const float lineThickness = juce::jmin(15.0f, juce::jmin(width, height) * 0.45f) * 0.1f;
            g.drawRect (slider.getLocalBounds().toFloat(), lineThickness);
        } else {
            drawLinearSliderBackground (g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
            drawLinearSliderThumb (g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
        }
    }

    void drawLinearSliderBackground (juce::Graphics& g, int x, int y, int width, int height,
                                     float /*sliderPos*/,
                                     float /*minSliderPos*/,
                                     float /*maxSliderPos*/,
                                     const juce::Slider::SliderStyle /*style*/, juce::Slider& slider) override
    {
        const float sliderRadius = getSliderThumbRadius (slider) - 5.0f;
        juce::Path on, off;

        if (slider.isHorizontal()) {
            const float iy = y + height * 0.5f - sliderRadius * 0.5f;
            juce::Rectangle<float> r (x - sliderRadius * 0.5f, iy, width + sliderRadius, sliderRadius);
            const float onW = r.getWidth() * ((float)slider.valueToProportionOfLength (slider.getValue()));

            on.addRectangle (r.removeFromLeft (onW));
            off.addRectangle (r);
        } else {
            const float ix = x + width * 0.5f - sliderRadius * 0.5f;
            juce::Rectangle<float> r (ix, y - sliderRadius * 0.5f, sliderRadius, height + sliderRadius);
            const float onH = r.getHeight() * ((float)slider.valueToProportionOfLength (slider.getValue()));

            on.addRectangle (r.removeFromBottom (onH));
            off.addRectangle (r);
        }

        g.setColour (slider.findColour (juce::Slider::rotarySliderFillColourId));
        g.fillPath (on);

        g.setColour (slider.findColour (juce::Slider::trackColourId));
        g.fillPath (off);
    }

    void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
                           float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider) override
    {
        const float radius = juce::jmin(width / 2, height / 2) - 4.0f;
        const float centreX = x + width * 0.5f;
        const float centreY = y + height * 0.5f;
        const float rx = centreX - radius;
        const float ry = centreY - radius;
        const float rw = radius * 2.0f;
        const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        const bool isMouseOver = slider.isMouseOverOrDragging() && slider.isEnabled();

        //Background
        {
            g.setColour(juce::Colours::lightgrey.withAlpha (isMouseOver ? 1.0f : 0.7f));
            juce::Path intFilledArc;
            intFilledArc.addPieSegment(rx, ry, rw, rw, rotaryStartAngle, rotaryEndAngle, 0.8);
            g.fillPath(intFilledArc);
        }

        if (slider.isEnabled()) {
            g.setColour(slider.findColour (juce::Slider::rotarySliderFillColourId).withAlpha (isMouseOver ? 1.0f : 0.7f));
        } else {
            g.setColour(juce::Colour (0x80808080));
        }

        //Render knob value
        {
            juce::Path pathArc;
            pathArc.addPieSegment(rx, ry, rw, rw, rotaryStartAngle, angle, 0.8);
            g.fillPath(pathArc);

            juce::Path cursor, cursorShadow;
            float rectWidth = radius*0.4;
            float rectHeight = rectWidth/2;
            float rectX = centreX + radius*0.9 - rectHeight/2;
            float rectY = centreY - rectWidth/2;

            cursor.addRectangle(rectX, rectY, rectWidth, rectHeight);
            cursorShadow.addRectangle(rectX-1, rectY-1, rectWidth+2, rectHeight+2);

            juce::AffineTransform t = juce::AffineTransform::translation(-rectWidth + 2, rectHeight/2);
            t = t.rotated((angle - juce::float_Pi/2), centreX, centreY);

            cursor.applyTransform(t);
            cursorShadow.applyTransform(t);

            g.setColour(juce::Colours::black);
            g.fillPath(cursor);

            g.setColour(juce::Colours::black .withAlpha(0.15f));
            g.fillPath(cursorShadow);
        }
    }
};

/**
 * \brief   Different kind of slider available
 * \see     uiSlider
 */
enum SliderType {
    HSlider,    /*!< Horizontal Slider      */
    VSlider,    /*!< Vertical Slider        */
    NumEntry,   /*!< Numerical Entry Box    */
    Knob        /*!< Circular Slider        */
};

/**
 * \brief   Different kind of VU-meter available.
 */
enum VUMeterType {
    HVUMeter,   /*!< Horizontal VU-meter    */
    VVUMeter,   /*!< Vertical VU-meter      */
    Led,        /*!< LED VU-meter           */
    NumDisplay  /*!< TextBox VU-meter       */
};

/**
 * \brief   Intern class for all FAUST widgets.
 * \details Every active, passive or box widgets derive from this class.
 */
class uiBase
{
    
    protected:
        
        int fTotalWidth, fTotalHeight;              // Size with margins included (for a uiBox)
        int fDisplayRectWidth, fDisplayRectHeight;  // Size without margin, just the child dimensions, sum on one dimension, max on the other
        float fHRatio, fVRatio;
        
    public:
        
        /**
         * \brief   Constructor.
         * \details Initialize a uiBase with all its sizes.
         *
         * \param   totWidth    Minimal total width.
         * \param   totHeight   Minimal total Height.
         */
        uiBase(int totWidth = 0, int totHeight = 0):
            fTotalWidth(totWidth), fTotalHeight(totHeight),
            fDisplayRectWidth(0), fDisplayRectHeight(0),
            fHRatio(1), fVRatio(1)
        {}
        
        virtual ~uiBase()
        {}
        
        /** Return the size. */
        juce::Rectangle<int> getSize()
        {
            return juce::Rectangle<int>(0, 0, fTotalWidth, fTotalHeight);
        }
        
        /** Return the total height in pixels. */
        int getTotalHeight()
        {
            return fTotalHeight;
        }
        
        /** Return the total width in pixels. */
        int getTotalWidth()
        {
            return fTotalWidth;
        }
        
        /** Return the horizontal ratio, between 0 and 1. */
        float getHRatio()
        {
            return fHRatio;
        }
        
        /** Return the vertical ratio, between 0 and 1. */
        float getVRatio()
        {
            return fVRatio;
        }
        
        /**
         * \brief   Set the uiBase bounds.
         * \details Convert absolute bounds to relative bounds,
         *          used in JUCE Component mechanics.
         *
         * \param r The absolute bounds.
         *
         */
        void setRelativeSize(juce::Component* comp, const juce::Rectangle<int>& r)
        {
            comp->setBounds(r.getX() - comp->getParentComponent()->getX(),
                            r.getY() - comp->getParentComponent()->getY(),
                            r.getWidth(),
                            r.getHeight());
        }
    
        virtual void init(juce::Component* comp = nullptr)
        {
            /** Initialize both vertical and horizontal ratios. */
            assert(comp);
            uiBase* parentBox = comp->findParentComponentOfClass<uiBase>();
            if (parentBox != nullptr) {
                fHRatio = (float)fTotalWidth / (float)parentBox->fDisplayRectWidth;
                fVRatio = (float)fTotalHeight / (float)parentBox->fDisplayRectHeight;
            }
        }
    
        virtual void setRecommendedSize()
        {}
        
        virtual void add(juce::Component* comp)
        {}
    
};

/**
 * \brief   Intern class for all FAUST active or passive widgets.
 * \details Every activ or passive widgets derive from this class.
 */
class uiComponent : public uiBase, public juce::Component, public uiItem
{

    public:
        /**
         * \brief   Constructor.
         * \details Initialize all uiItem, uiBase and the tooltip variables.
         *
         * \param   gui     Current FAUST GUI.
         * \param   zone    Zone of the widget.
         * \param   w       Width of the widget.
         * \param   h       Height of the widget.
         * \param   name    Name of the widget.
         */
        uiComponent(GUI* gui, FAUSTFLOAT* zone, int w, int h, juce::String name):uiBase(w, h), Component(name), uiItem(gui, zone)
        {}

};

/** 
 * \brief   Intern class for all kind of sliders.
 * \see     SliderType
 */
class uiSlider : public uiComponent, public uiConverter, private juce::Slider::Listener
{
    
    private:
        
        juce::Slider::SliderStyle fStyle;
        juce::Label fLabel;
        SliderType fType;
        juce::Slider fSlider;

    public:
        /**
         * \brief   Constructor.
         * \details Initialize all uiComponent variables, and Slider specific ones.
         *          Initialize juce::Slider parameters.
         *
         * \param   gui, zone, w, h, tooltip, name  uiComponent variables.
         * \param   min                             Minimum value of the slider.
         * \param   max                             Maximum value of the slider.
         * \param   cur                             Initial value of the slider.
         * \param   step                            Step of the slider.
         * \param   unit                            Unit of the slider value.
         * \param   scale                           Scale of the slider, exponential, logarithmic, or linear.
         * \param   type                            Type of slider (see SliderType).
         */
        uiSlider(GUI* gui, FAUSTFLOAT* zone, FAUSTFLOAT w, FAUSTFLOAT h, FAUSTFLOAT cur, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step, juce::String name, juce::String unit, juce::String tooltip, MetaDataUI::Scale scale, SliderType type)
            : uiComponent(gui, zone, w, h, name), uiConverter(scale, min, max, min, max), fType(type)
        {
            // Set the JUCE widget initalization variables.
            switch(fType) {
                case HSlider:
                    fStyle = juce::Slider::SliderStyle::LinearHorizontal;
                    break;
                case VSlider:
                    fStyle = juce::Slider::SliderStyle::LinearVertical;
                    fSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
                    break;
                case NumEntry:
                    fSlider.setIncDecButtonsMode(juce::Slider::incDecButtonsDraggable_AutoDirection);
                    fStyle = juce::Slider::SliderStyle::IncDecButtons;
                    break;
                case Knob:
                    fStyle = juce::Slider::SliderStyle::Rotary;
                    fSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
                    break;
                default:
                    break;
            }
            addAndMakeVisible(fSlider);

            // Slider settings
            fSlider.setRange(min, max, step);
            fSlider.setValue(fConverter->faust2ui(cur));
            fSlider.addListener(this);
            fSlider.setSliderStyle(fStyle);
            fSlider.setTextValueSuffix(" " + unit);
            fSlider.setTooltip(tooltip);
            switch (scale) {
                case MetaDataUI::kLog:
                    fSlider.setSkewFactor(0.25);
                    break;
                case MetaDataUI::kExp:
                    fSlider.setSkewFactor(0.75);
                    break;
                default:
                    break;
            }
      
            // Label settings, only happens for a horizontal of numerical entry slider
            // because the method attachToComponent only give the choice to place the
            // slider name on centered top, which is what we want. It's done manually
            // in the paint method.
            if (fType == HSlider || fType == NumEntry) {
                fLabel.setText(getName(), juce::dontSendNotification);
                fLabel.attachToComponent(&fSlider, true);
                fLabel.setTooltip(tooltip);
                addAndMakeVisible(fLabel);
            }
        }

        /** Draw the name of a vertical or circular slider. */
        virtual void paint(juce::Graphics& g) override
        {
            if (fType == VSlider || fType == Knob) {
                g.setColour(juce::Colours::black);
                g.drawText(getName(), getLocalBounds(), juce::Justification::centredTop);
            }
        }

        /** Allow to control the slider when its value is changed, but not by the user. */
        void reflectZone() override
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            fSlider.setValue(fConverter->faust2ui(v));
        }

        /** JUCE callback for a slider value change, give the value to the FAUST module. */
        void sliderValueChanged(juce::Slider* slider) override
        {
            float v = slider->getValue();
            modifyZone(FAUSTFLOAT(fConverter->ui2faust(v)));
        }

        /** 
         * Set the good coordinates and size for the juce::Slider object depending 
         * on its SliderType, whenever the layout size changes.
         */
        void resized() override
        {
            int x, y, width, height;
            
            switch (fType) {
                    
                case HSlider: {
                    int nameWidth = juce::Font().getStringWidth(getName()) + kMargin * 2;
                    x = nameWidth;
                    y = 0;
                    width = getWidth() - nameWidth;
                    height = getHeight();
                    break;
                }
                    
                case VSlider:
                    x = 0;
                    y = kNameHeight; // kNameHeight pixels for the name
                    height = getHeight() - kNameHeight;
                    width = getWidth();
                    break;

                case NumEntry:
                    width = kNumEntryWidth;
                    height = kNumEntryHeight;
                    // x position is the top left corner horizontal position of the box
                    // and not the top left of the NumEntry label, so we have to do that
                    x = (getWidth() - width)/2 + (juce::Font().getStringWidth(getName()) + kMargin)/2;
                    y = (getHeight() - height)/2;
                    break;
                    
                case Knob:
                    // The knob name needs to be displayed, kNameHeight pixels
                    height = width = juce::jmin(getHeight() - kNameHeight, kKnobHeight);
                    x = (getWidth() - width)/2;
                    // kNameHeight pixels for the knob name still
                    y = juce::jmax((getHeight() - height)/2, kNameHeight);
                    break;
                    
                default:
                    assert(false);
                    break;
            }
            
            fSlider.setBounds(x, y, width, height);
        }
    
};

/** Intern class for button */
class uiButton : public uiComponent, private juce::Button::Listener
{
    
    private:
        
        juce::TextButton fButton;

    public:
        /**
         * \brief   Constructor.
         * \details Initialize all uiComponent variables and juce::TextButton parameters.
         *
         * \param   gui, zone, w, h, tooltip, label uiComponent variable.
         */
        uiButton(GUI* gui, FAUSTFLOAT* zone, FAUSTFLOAT w, FAUSTFLOAT h, juce::String label, juce::String tooltip) :  uiComponent(gui, zone, w, h, label)
        {
            int x = 0;
            int y = (getHeight() - kButtonHeight)/2;

            fButton.setButtonText(label);
            fButton.setBounds(x, y, kButtonWidth, kButtonHeight);
            fButton.addListener(this);
            fButton.setTooltip(tooltip);
            addAndMakeVisible(fButton);
        }

        /** 
         * Has to be defined because its a pure virtual function of juce::Button::Listener, 
         * which uiButton derives from. Control of user actions is done in buttonStateChanged.
         * \see buttonStateChanged
         */
        void buttonClicked (juce::Button* button) override
        {}

        /** Indicate to the FAUST module when the button is pressed and released. */
        void buttonStateChanged (juce::Button* button) override
        {
            if (button->isDown()) {
                modifyZone(FAUSTFLOAT(1));
            } else {
                modifyZone(FAUSTFLOAT(0));
            }
        }
        
        void reflectZone() override
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (v == FAUSTFLOAT(1)) {
                fButton.triggerClick();
            }
        }

        /** Set the good coordinates and size to the juce::TextButton widget whenever the layout size changes. */
        virtual void resized() override
        {
            int x = kMargin;
            int width = getWidth() - 2 * kMargin;
            int height = juce::jmin(getHeight(), kButtonHeight);
            int y = (getHeight()-height)/2;
            fButton.setBounds(x, y, width, height);
        }
    
};

/** Intern class for checkButton */
class uiCheckButton : public uiComponent, private juce::Button::Listener
{
    
    private:
        
        juce::ToggleButton fCheckButton;

    public:
        /**
         * \brief   Constructor.
         * \details Initialize all uiComponent variables and juce::ToggleButton parameters.
         *
         * \param   gui, zone, w, h, label, tooltip  uiComponent variables.
         */
        uiCheckButton(GUI* gui, FAUSTFLOAT* zone, FAUSTFLOAT w, FAUSTFLOAT h, juce::String label, juce::String tooltip) : uiComponent(gui, zone, w, h, label)
        {
            int x = 0;
            int y = (getHeight()-h)/2;
            
            fCheckButton.setButtonText(label);
            fCheckButton.setBounds(x, y, w, h);
            fCheckButton.addListener(this);
            fCheckButton.setTooltip(tooltip);
            addAndMakeVisible(fCheckButton);
        }

        /** Indicate to the FAUST module when the button is toggled or not. */
        void buttonClicked(juce::Button* button) override
        {
            //std::cout << getName() << " : " << button->getToggleState() << std::endl;
            modifyZone(button->getToggleState());
        }

        void reflectZone() override
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            fCheckButton.triggerClick();
        }

        /** Set the good coordinates and size to the juce::ToggleButton widget, whenever the layout size changes. */
        virtual void resized() override
        {
            fCheckButton.setBounds(getLocalBounds());
        }
    
};

/** Intern class for Menu */
class uiMenu : public uiComponent, private juce::ComboBox::Listener
{
    
    private:
        
        juce::ComboBox fComboBox;
        std::vector<double> fValues;

    public:
        /**
         * \brief   Constructor.
         * \details Initialize the uiComponent and Menu specific variables, and the juce::ComboBox parameters.
         *          Menu is considered as a slider in the FAUST logic, with a step of one. The first item
         *          would be 0 on a slider, the second 1, etc. Each "slider value" is associated with a 
         *          string.
         *
         * \param   gui, zone, w, h, tooltip, label     uiComponent variables.
         * \param   cur                                 Current "slider value" associated with the current item selected.
         * \param   low                                 Lowest value possible.
         * \param   hi                                  Highest value possible.
         * \param   mdescr                              Menu description. Contains the names of the items associated with their "value".
         */
        uiMenu(GUI* gui, FAUSTFLOAT* zone, juce::String label, FAUSTFLOAT w, FAUSTFLOAT h, FAUSTFLOAT cur, FAUSTFLOAT lo, FAUSTFLOAT hi, juce::String tooltip, const char* mdescr) : uiComponent(gui, zone, w, h, label)
        {
            //Init ComboBox parameters
            fComboBox.setEditableText(false);
            fComboBox.setJustificationType(juce::Justification::centred);
            fComboBox.addListener(this);
            addAndMakeVisible(fComboBox);

            std::vector<std::string> names;
            std::vector<double> values;

            if (parseMenuList(mdescr, names, values)) {

                int defaultitem = -1;
                double mindelta = FLT_MAX;
                int item = 1;

                // Go through all the Menu's items.
                for (int i = 0; i < names.size(); i++) {
                    double v = values[i];
                    if ((v >= lo) && (v <= hi)) {
                        // It is a valid value : add corresponding menu item
                        // item astrating at 1 because index 0 is reserved for a non-defined item.
                        fComboBox.addItem(juce::String(names[i].c_str()), item++);
                        fValues.push_back(v);

                        // Check if this item is a good candidate to represent the current value
                        double delta = fabs(cur-v);
                        if (delta < mindelta) {
                            mindelta = delta;
                            defaultitem = fComboBox.getNumItems();
                        }
                    }
                }
                // check the best candidate to represent the current value
                if (defaultitem > -1) {
                    fComboBox.setSelectedItemIndex(defaultitem);
                }
            }

            *fZone = cur;
        }

        /** Indicate to the FAUST module when the selected items is changed. */
        void comboBoxChanged (juce::ComboBox* cb) override
        {
            //std::cout << getName( )<< " : " << cb->getSelectedId() - 1 << std::endl;
            // -1 because of the starting item  at 1 at the initialization
            modifyZone(fValues[cb->getSelectedId() - 1]);
        }

        virtual void reflectZone() override
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;

            // search closest value
            int defaultitem = -1;
            double mindelta = FLT_MAX;

            for (unsigned int i = 0; i < fValues.size(); i++) {
                double delta = fabs(fValues[i]-v);
                if (delta < mindelta) {
                    mindelta = delta;
                    defaultitem = i;
                }
            }
            if (defaultitem > -1) {
                fComboBox.setSelectedItemIndex(defaultitem);
            }
        }

        /** Set the good coordinates and size to the juce::ComboBox widget whenever the layout get reiszed */
        virtual void resized() override
        {
            fComboBox.setBounds(0, 0 + kMenuHeight/2, getWidth(), kMenuHeight/2);
        }

        /** Display the name of the Menu */
        virtual void paint(juce::Graphics& g) override
        {
            g.setColour(juce::Colours::black);
            g.drawText(getName(), getLocalBounds().withHeight(getHeight()/2), juce::Justification::centredTop);
        }
    
};

/** Intern class for RadioButton */
class uiRadioButton : public uiComponent, private juce::Button::Listener
{
    
    private:
        
        bool fIsVertical;
        juce::OwnedArray<juce::ToggleButton> fButtons;
        std::vector<double> fValues;

    public:
        /**
         * \brief   Constructor.
         * \details Initialize the uiComponent variables, and the RadioButton specific variables
         *          and parameters. Works in a similar way to the Menu, because it is a special
         *          kind of sliders in the faust logic. 
         * \see     uiMenu
         * 
         * \param   gui, zone, tooltip, label   uiComponent variables.
         * \param   w                           uiComponent variable and width of the RadioButton widget.
         * \param   h                           uiComponent variable and height of the RadioButton widget.
         * \param   cur                         Current "value" associated with the item selected.
         * \param   low                         Lowest "value" possible.
         * \param   hi                          Highest "value" possible.
         * \param   vert                        True if vertical, false if horizontal.
         * \param   names                       Contain the names of the different items.
         * \param   values                      Contain the "values" of the different items.
         * \param   fRadioGroupID               RadioButton being multiple CheckButton in JUCE,
         *                                      we need an ID to know which are linked together.
         */
        uiRadioButton(GUI* gui, FAUSTFLOAT* zone, juce::String label, FAUSTFLOAT w, FAUSTFLOAT h, FAUSTFLOAT cur, FAUSTFLOAT lo, FAUSTFLOAT hi, bool vert, std::vector<std::string>& names, std::vector<double>& values, juce::String tooltip, int radioGroupID) : uiComponent(gui, zone, w, h, label), fIsVertical(vert)
        {
            juce::ToggleButton* defaultbutton = 0;
            double mindelta = FLT_MAX;

            for (int i = 0; i < names.size(); i++) {
                double v = values[i];
                if ((v >= lo) && (v <= hi)) {

                    // It is a valid value included in slider's range
                    juce::ToggleButton* tb = new juce::ToggleButton(names[i]);
                    addAndMakeVisible(tb);
                    tb->setRadioGroupId (radioGroupID);
                    tb->addListener(this);
                    tb->setTooltip(tooltip);
                    fValues.push_back(v);
                    fButtons.add(tb);
      
                    // Check if this item is a good candidate to represent the current value
                    double delta = fabs(cur-v);
                    if (delta < mindelta) {
                        mindelta = delta;
                        defaultbutton = tb;
                    }
                }
            }
            // check the best candidate to represent the current value
            if (defaultbutton) {
                defaultbutton->setToggleState (true, juce::dontSendNotification);
            }
        }
     
        virtual void reflectZone() override
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;

            // select closest value
            int defaultitem = -1;
            double mindelta = FLT_MAX;

            for (unsigned int i = 0; i < fValues.size(); i++) {
                double delta = fabs(fValues[i]-v);
                if (delta < mindelta) {
                    mindelta = delta;
                    defaultitem = i;
                }
            }
            if (defaultitem > -1) {
                fButtons.operator[](defaultitem)->setToggleState (true, juce::dontSendNotification);
            }
        }

        /** Handle the placement of each juce::ToggleButton everytime the layout size is changed. */
        virtual void resized() override
        {
            int width, height;
            fIsVertical ? (height = (getHeight() - kNameHeight) / fButtons.size()) : (width = getWidth() / fButtons.size());

            for (int i = 0; i < fButtons.size(); i++) {
                if (fIsVertical) {
                    fButtons.operator[](i)->setBounds(0, i * height + kNameHeight, getWidth(), height);
                } else {
                    // kNameHeight pixels offset for the title
                    fButtons.operator[](i)->setBounds(i * width, kNameHeight, width, getHeight() - kNameHeight);
                }
            }
        }
        
        /** Display the RadioButton name */
        virtual void paint(juce::Graphics& g) override
        {
            g.setColour(juce::Colours::black);
            g.drawText(getName(), getLocalBounds().withHeight(kNameHeight), juce::Justification::centredTop);
        }

        /** Check which button is checked, and give its "value" to the FAUST module */
    void buttonClicked(juce::Button* button) override
        {
            juce::ToggleButton* checkButton = dynamic_cast<juce::ToggleButton*>(button);
            //std::cout << getName() << " : " << fButtons.indexOf(checkButton) << std::endl;
            modifyZone(fButtons.indexOf(checkButton));
        }
    
};

/**
 * \brief   Intern class for VU-meter
 * \details There is no JUCE widgets for VU-meter, so its fully designed in this class.
 */
class uiVUMeter : public uiComponent, public juce::SettableTooltipClient, public juce::Timer
{
    
    private:
    
        FAUSTFLOAT fLevel;               // Current level of the VU-meter.
        FAUSTFLOAT fMin, fMax;           // Linear range of the VU-meter.
        FAUSTFLOAT fScaleMin, fScaleMax; // Range in dB if needed.
        bool fDB;                        // True if it's a dB VU-meter, false otherwise.
        VUMeterType fStyle;
        juce::String fUnit;
        juce::Label fLabel;               // Name of the VU-meter.
    
        bool isNameDisplayed()
        {
            return (!(getName().startsWith("0x")) && getName().isNotEmpty());
        }
        
        /** Give the right coordinates and size to the text of Label depending on the VU-meter style */
        void setLabelPos()
        {
            if (fStyle == VVUMeter) {
                // -22 on the height because of the text box.
                fLabel.setBounds((getWidth()-50)/2, getHeight()-22, 50, 20);
            } else if (fStyle == HVUMeter) {
                isNameDisplayed() ? fLabel.setBounds(63, (getHeight()-20)/2, 50, 20)
                : fLabel.setBounds(3, (getHeight()-20)/2, 50, 20);
            } else if (fStyle == NumDisplay) {
                fLabel.setBounds((getWidth()-kNumDisplayWidth)/2,
                                 (getHeight()-kNumDisplayHeight/2)/2,
                                 kNumDisplayWidth,
                                 kNumDisplayHeight/2);
            }
        }
        
        /** Contain all the initialization need for our Label */
        void setupLabel(juce::String tooltip)
        {
            setLabelPos();
            fLabel.setEditable(false, false, false);
            fLabel.setJustificationType(juce::Justification::centred);
            fLabel.setText(juce::String((int)*fZone) + " " + fUnit, juce::dontSendNotification);
            fLabel.setTooltip(tooltip);
            addAndMakeVisible(fLabel);
        }
        
        /**
         * \brief   Generic method to draw an horizontal VU-meter.
         * \details Draw the background of the bargraph, and the TextBox box, without taking
         *          care of the actual level of the VU-meter
         * \see     drawHBargraphDB
         * \see     drawHBargraphLin
         *
         * \param   g       JUCE graphics context, used to draw components or images.
         * \param   width   Width of the VU-meter widget.
         * \param   height  Height of the VU-meter widget.
         * \param   level   Current level that needs to be displayed.
         * \param   dB      True if it's a db level, false otherwise.
         */
        void drawHBargraph(juce::Graphics& g, int width, int height)
        {
            float x;
            float y = (float)(getHeight()-height)/2;
            if (isNameDisplayed()) {
                x = 120;
                width -= x;
                // VUMeter Name
                g.setColour(juce::Colours::black);
                g.drawText(getName(), 0, y, 60, height, juce::Justification::centredRight);
            } else {
                x = 60;
                width -= x;
            }
            
            // VUMeter Background
            g.setColour(juce::Colours::lightgrey);
            g.fillRect(x, y, (float)width, (float)height);
            g.setColour(juce::Colours::black);
            g.fillRect(x+1.0f, y+1.0f, (float)width-2, (float)height-2);
            
            // Label Window
            g.setColour(juce::Colours::darkgrey);
            g.fillRect((int)x-58, (getHeight()-22)/2, 52, 22);
            g.setColour(juce::Colours::white.withAlpha(0.8f));
            g.fillRect((int)x-57, (getHeight()-20)/2, 50, 20);
            
            // Call the appropriate drawing method for the level.
            fDB ? drawHBargraphDB (g, y, height) : drawHBargraphLin(g, x, y, width, height);
        }
        
        /**
         * Method in charge of drawing the level of a horizontal dB VU-meter.
         *
         * \param   g       JUCE graphics context, used to draw components or images.
         * \param   y       y coordinate of the VU-meter.
         * \param   height  Height of the VU-meter.
         * \param   level   Current level of the VU-meter, in dB.
         */
        void drawHBargraphDB(juce::Graphics& g, int y, int height)
        {
            // Drawing Scale
            g.setFont(9.0f);
            g.setColour(juce::Colours::white);
            for (int i = -10; i > fMin; i -= 10) {
                paintScale(g, i);
            }
            for (int i = -6; i < fMax; i += 3)  {
                paintScale(g, i);
            }
            
            int alpha = 200;
            FAUSTFLOAT dblevel = dB2Scale(fLevel);
            
            // We need to test here every color changing levels, to avoid to mix colors because of the alpha,
            // and so to start the new color rectangle at the end of the previous one.
            
            // Drawing from the minimal range to the current level, or -10dB.
            g.setColour(juce::Colour((juce::uint8)40, (juce::uint8)160, (juce::uint8)40, (juce::uint8)alpha));
            g.fillRect(dB2x(fMin), y+1.0f, juce::jmin(dB2x(fLevel)-dB2x(fMin), dB2x(-10)-dB2x(fMin)), (float)height-2);
            
            // Drawing from -10dB to the current level, or -6dB.
            if (dblevel > dB2Scale(-10)) {
                g.setColour(juce::Colour((juce::uint8)160, (juce::uint8)220, (juce::uint8)20, (juce::uint8)alpha));
                g.fillRect(dB2x(-10), y+1.0f, juce::jmin(dB2x(fLevel)-dB2x(-10), dB2x(-6)-dB2x(-10)), (float)height-2);
            }
            // Drawing from -6dB to the current level, or -3dB.
            if (dblevel > dB2Scale(-6)) {
                g.setColour(juce::Colour((juce::uint8)220, (juce::uint8)220, (juce::uint8)20, (juce::uint8)alpha));
                g.fillRect(dB2x(-6), y+1.0f, juce::jmin(dB2x(fLevel)-dB2x(-6), dB2x(-3)-dB2x(-6)), (float)height-2);
            }
            // Drawing from -3dB to the current level, or 0dB.
            if (dblevel > dB2Scale(-3)) {
                g.setColour(juce::Colour((juce::uint8)240, (juce::uint8)160, (juce::uint8)20, (juce::uint8)alpha));
                g.fillRect(dB2x(-3), y+1.0f, juce::jmin(dB2x(fLevel)-dB2x(-3), dB2x(0)-dB2x(-3)), (float)height-2);
            }
            // Drawing from 0dB to the current level, or the max range.
            if (dblevel > dB2Scale(0)) {
                g.setColour(juce::Colour((juce::uint8)240, (juce::uint8)0, (juce::uint8)20, (juce::uint8)alpha));
                g.fillRect(dB2x(0), y+1.0f, juce::jmin(dB2x(fLevel)-dB2x(0), dB2x(fMax)-dB2x(0)), (float)height-2);
            }
        }
        
        /**
         * Method in charge of drawing the level of a horizontal linear VU-meter.
         *
         * \param   g       JUCE graphics context, used to draw components or images.
         * \param   x       x coordinate of the VU-meter.
         * \param   y       y coordinate of the VU-meter.
         * \param   height  Height of the VU-meter.
         * \param   width   Width of the VU-meter.
         * \param   level   Current level of the VU-meter, in linear logic.
         */
        void drawHBargraphLin(juce::Graphics& g, int x, int y, int width, int height)
        {
            int alpha = 200;
            juce::Colour c = juce::Colour((juce::uint8)255, (juce::uint8)165, (juce::uint8)0, (juce::uint8)alpha);
            
            // Drawing from the minimal range to the current level, or 20% of the VU-meter
            g.setColour(c.brighter());
            g.fillRect(x+1.0f, y+1.0f, juce::jmin<float>(fLevel*(width-2), 0.2f*(width-2)), (float)height-2);
            // Drawing from 20% of the VU-meter to the current level, or 90% of the VU-meter
            if (fLevel > 0.2f) {
                g.setColour(c);
                g.fillRect(x+1.0f + 0.2f*(width-2), y+1.0f, juce::jmin<float>((fLevel-0.2f) * (width-2), (0.9f-0.2f) * (width-2)), (float)height-2);
            }
            // Drawing from 90% of the VU-meter to the current level, or the maximal range of the VU-meter
            if (fLevel > 0.9f) {
                g.setColour(c.darker());
                g.fillRect(x+1.0f + 0.9f*(width-2), y+1.0f, juce::jmin<float>((fLevel-0.9f) * (width-2), (1.0f-0.9f) * (width-2)), (float)height-2);
            }
        }
        /**
         * \brief   Generic method to draw a vertical VU-meter.
         * \details Draw the background of the bargraph, and the TextBox box, without taking
         *          care of the actual level of the VU-meter
         * \see     drawHBargraphDB
         * \see     drawHBargraphLin
         *
         * \param   g       JUCE graphics context, used to draw components or images.
         * \param   width   Width of the VU-meter widget.
         * \param   height  Height of the VU-meter widget.
         * \param   level   Current level that needs to be displayed.
         * \param   dB      True if it's a db level, false otherwise.
         */
        void drawVBargraph(juce::Graphics& g, int width, int height)
        {
            float x = (float)(getWidth()-width)/2;
            float y;
            if (isNameDisplayed()) {
                y = (float)getHeight()-height+15;
                height -= 40;
                // VUMeter Name
                g.setColour(juce::Colours::black);
                g.drawText(getName(), getLocalBounds(), juce::Justification::centredTop);
            } else {
                y = (float)getHeight()-height;
                height -= 25;
            }
            
            // VUMeter Background
            g.setColour(juce::Colours::lightgrey);
            g.fillRect(x, y, (float)width, (float)height);
            g.setColour(juce::Colours::black);
            g.fillRect(x+1.0f, y+1.0f, (float)width-2, (float)height-2);
            
            // Label window
            g.setColour(juce::Colours::darkgrey);
            g.fillRect(juce::jmax((getWidth()-50)/2, 0), getHeight()-23, juce::jmin(getWidth(), 50), 22);
            g.setColour(juce::Colours::white.withAlpha(0.8f));
            g.fillRect(juce::jmax((getWidth()-48)/2, 1), getHeight()-22, juce::jmin(getWidth()-2, 48), 20);
            
            fDB ? drawVBargraphDB (g, x, width) : drawVBargraphLin(g, x, width);
        }
        
        /**
         * Method in charge of drawing the level of a vertical dB VU-meter.
         *
         * \param   g       JUCE graphics context, used to draw components or images.
         * \param   x       x coordinate of the VU-meter.
         * \param   width   Width of the VU-meter.
         * \param   level   Current level of the VU-meter, in dB.
         */
        void drawVBargraphDB(juce::Graphics& g, int x, int width)
        {
            // Drawing Scale
            g.setFont(9.0f);
            g.setColour(juce::Colours::white);
            for (int i = -10; i > fMin; i -= 10) {
                paintScale(g, i);
            }
            for (int i = -6; i < fMax; i += 3)  {
                paintScale(g, i);
            }
            
            int alpha = 200;
            FAUSTFLOAT dblevel = dB2Scale(fLevel);
            
            // We need to test here every color changing levels, to avoid to mix colors because of the alpha,
            // and so to start the new color rectangle at the end of the previous one.
            
            // Drawing from the minimal range to the current level, or -10dB.
            g.setColour(juce::Colour((juce::uint8)40, (juce::uint8)160, (juce::uint8)40, (juce::uint8)alpha));
            g.fillRect(x+1.0f, juce::jmax(dB2y(fLevel), dB2y(-10)), (float)width-2, dB2y(fMin)-juce::jmax(dB2y(fLevel), dB2y(-10)));
            
            // Drawing from -10dB to the current level, or -6dB.
            if (dblevel > dB2Scale(-10)) {
                g.setColour(juce::Colour((juce::uint8)160, (juce::uint8)220, (juce::uint8)20, (juce::uint8)alpha));
                g.fillRect(x+1.0f, juce::jmax(dB2y(fLevel), dB2y(-6)), (float)width-2, dB2y(-10)-juce::jmax(dB2y(fLevel), dB2y(-6)));
            }
            // Drawing from -6dB to the current level, or -3dB.
            if (dblevel > dB2Scale(-6)) {
                g.setColour(juce::Colour((juce::uint8)220, (juce::uint8)220, (juce::uint8)20, (juce::uint8)alpha));
                g.fillRect(x+1.0f, juce::jmax(dB2y(fLevel), dB2y(-3)), (float)width-2, dB2y(-6)-juce::jmax(dB2y(fLevel), dB2y(-3)));
            }
            // Drawing from -3dB to the current level, or 0dB.
            if (dblevel > dB2Scale(-3)) {
                g.setColour(juce::Colour((juce::uint8)240, (juce::uint8)160, (juce::uint8)20, (juce::uint8)alpha));
                g.fillRect(x+1.0f, juce::jmax(dB2y(fLevel), dB2y(0)), (float)width-2, dB2y(-3)-juce::jmax(dB2y(fLevel), dB2y(0)));
            }
            // Drawing from 0dB to the current level, or the maximum range.
            if (dblevel > dB2Scale(0)) {
                g.setColour(juce::Colour((juce::uint8)240, (juce::uint8)0, (juce::uint8)20, (juce::uint8)alpha));
                g.fillRect(x+1.0f, juce::jmax(dB2y(fLevel), dB2y(fMax)), (float)width-2, dB2y(0)-juce::jmax(dB2y(fLevel), dB2y(fMax)));
            }
        }
        
        /**
         * Method in charge of drawing the level of a vertical linear VU-meter.
         *
         * \param   g       JUCE graphics context, used to draw components or images.
         * \param   x       x coordinate of the VU-meter.
         * \param   width   Width of the VU-meter.
         * \param   level   Current level of the VU-meter, in linear logic.
         */
        void drawVBargraphLin(juce::Graphics& g, int x, int width)
        {
            int alpha = 200;
            juce::Colour c = juce::Colour((juce::uint8)255, (juce::uint8)165, (juce::uint8)0, (juce::uint8)alpha);
            
            // Drawing from the minimal range to the current level, or 20% of the VU-meter.
            g.setColour(c.brighter());
            g.fillRect(x+1.0f, juce::jmax(lin2y(fLevel), lin2y(0.2)), (float)width-2, lin2y(fMin)-juce::jmax(lin2y(fLevel), lin2y(0.2)));
            
            // Drawing from 20% of the VU-meter to the current level, or 90% of the VU-meter.
            if (fLevel > 0.2f) {
                g.setColour(c);
                g.fillRect(x+1.0f, juce::jmax(lin2y(fLevel), lin2y(0.9)), (float)width-2, lin2y(0.2)-juce::jmax(lin2y(fLevel), lin2y(0.9)));
            }
            
            // Drawing from 90% of the VU-meter to the current level, or the maximum range.
            if (fLevel > 0.9f) {
                g.setColour(c.darker());
                g.fillRect(x+1.0f, juce::jmax(lin2y(fLevel), lin2y(fMax)), (float)width-2, lin2y(0.9)-juce::jmax(lin2y(fLevel), lin2y(fMax)));
            }
        }
        
        /**
         * Method in charge of drawing the LED VU-meter, dB or not.
         *
         * \param   g       JUCE graphics context, used to draw components or images.
         * \param   width   Width of the LED.
         * \param   height  Height of the LED.
         * \param   level   Current level of the VU-meter, dB or not.
         */
        void drawLed(juce::Graphics& g, int width, int height)
        {
            float x = (float)(getWidth() - width)/2;
            float y = (float)(getHeight() - height)/2;
            g.setColour(juce::Colours::black);
            g.fillEllipse(x, y, width, height);
            
            if (fDB) {
                int alpha = 200;
                FAUSTFLOAT dblevel = dB2Scale(fLevel);
                
                // Adjust the color depending on the current level
                g.setColour(juce::Colour((juce::uint8)40, (juce::uint8)160, (juce::uint8)40, (juce::uint8)alpha));
                if (dblevel > dB2Scale(-10)) {
                    g.setColour(juce::Colour((juce::uint8)160, (juce::uint8)220, (juce::uint8)20, (juce::uint8)alpha));
                }
                if (dblevel > dB2Scale(-6)) {
                    g.setColour(juce::Colour((juce::uint8)220, (juce::uint8)220, (juce::uint8)20, (juce::uint8)alpha));
                }
                if (dblevel > dB2Scale(-3)) {
                    g.setColour(juce::Colour((juce::uint8)240, (juce::uint8)160, (juce::uint8)20, (juce::uint8)alpha));
                }
                if (dblevel > dB2Scale(0))  {
                    g.setColour(juce::Colour((juce::uint8)240, (juce::uint8)0, (juce::uint8)20, (juce::uint8)alpha));
                }
                
                g.fillEllipse(x+1, y+1, width-2, height-2);
            } else {
                // The alpha depend on the level, from 0 to 1
                g.setColour(juce::Colours::red.withAlpha((float)fLevel));
                g.fillEllipse(x+1, y+1, width-2, height-2);
            }
        }
        
        /**
         * Method in charge of drawing the Numerical Display VU-meter, dB or not.
         *
         * \param   g       JUCE graphics context, used to draw components or images.
         * \param   width   Width of the Numerical Display.
         * \param   height  Height of the Numerical Display.
         * \param   level   Current level of the VU-meter.
         */
        void drawNumDisplay(juce::Graphics& g, int width, int height)
        {
            // Centering it
            int x = (getWidth()-width) / 2;
            int y = (getHeight()-height) / 2;
            
            // Draw box.
            g.setColour(juce::Colours::darkgrey);
            g.fillRect(x, y, width, height);
            g.setColour(juce::Colours::white.withAlpha(0.8f));
            g.fillRect(x+1, y+1, width-2, height-2);
            
            // Text is handled by the setLabelPos() function
        }
        
        /** Convert a dB level to a y coordinate, for easier draw methods. */
        FAUSTFLOAT dB2y(FAUSTFLOAT dB)
        {
            FAUSTFLOAT s0 = fScaleMin;      // Minimal range.
            FAUSTFLOAT s1 = fScaleMax;      // Maximum range.
            FAUSTFLOAT sx = dB2Scale(dB);   // Current level.
            
            int h;
            int treshold;   // Value depend if the name is displayed
            
            if (isNameDisplayed()) {
                h = getHeight()-42; // 15 pixels for the VU-Meter name,
                // 25 for the textBox, 2 pixels margin.
                treshold = 16;      // 15 pixels for the VU-Meter name.
            } else {
                h = getHeight()-27; // 25 for the textBox, 2 pixels margin.
                treshold = 1;       // 1 pixel margin.
            }
            
            return (h - h*(s0-sx)/(s0-s1)) + treshold;
        }
        
        /** Convert a linear level to a y coordinate, for easier draw methods. */
        FAUSTFLOAT lin2y(FAUSTFLOAT level)
        {
            int h;
            int treshold;
            
            if (isNameDisplayed()) {
                h = getHeight()-42; // 15 pixels for the VU-Meter name,
                // 25 for the textBox, 2 pixels margin.
                treshold = 16;      // 15 pixels for the VU-Meter name.
            } else {
                h = getHeight()-27; // 25 for the textBox, 2 pixels margin.
                treshold = 1;       // 1 pixel margin.
            }
            
            return h * (1 - level) + treshold;
        }
        
        /** Convert a dB level to a x coordinate, for easier draw methods. */
        FAUSTFLOAT dB2x(FAUSTFLOAT dB)
        {
            FAUSTFLOAT s0 = fScaleMin;      // Minimal range.
            FAUSTFLOAT s1 = fScaleMax;      // Maximal range.
            FAUSTFLOAT sx = dB2Scale(dB);   // Current level.
            
            int w;
            int treshold;
            
            if (isNameDisplayed()) {
                w = getWidth()-122; // 60 pixels for the VU-Meter name,
                // 60 for the TextBox, 2 pixels margin.
                treshold = 121;     // 60 pixels for the VU-Meter name,
                // 60 for the TextBox, and 1 pixel margin.
            } else {
                w = getWidth()-62;  // 60 pixels for the TextBox, 2 pixels margin.
                treshold = 61;      // 60 pixels for the TextBox, 1 pixel margin.
            }
            
            return treshold + w - w*(s1-sx)/(s1-s0);
        }
        
        /** Write the different level included in the VU-Meter range. */
        void paintScale(juce::Graphics& g, float num)
        {
            juce::Rectangle<int> r;
            
            if (fStyle == VVUMeter) {
                r = juce::Rectangle<int>((getWidth()-(kVBargraphWidth/2))/2 + 1,  // Left side of the VU-Meter.
                                         dB2y(num),                               // Vertically centred with 20 height.
                                         (kVBargraphWidth/2)-2,                   // VU-Meter width with margin.
                                         20);                                     // 20 height.
                g.drawText(juce::String(num), r, juce::Justification::centredRight, false);
            } else {
                r = juce::Rectangle<int>(dB2x(num)-10,                            // Horizontally centred with 20 width.
                                        (getHeight()-kHBargraphHeight/2)/2 + 1,  // Top side of the VU-Meter.
                                        20,                                      // 20 width.
                                        (kHBargraphHeight/2)-2);                 // VU-Meter height with margin
                g.drawText(juce::String(num), r, juce::Justification::centredTop, false);
            }
        }
        
        /** Set the level, keep it in the range of the VU-Meter, and set the TextBox text. */
        void setLevel()
        {
            FAUSTFLOAT rawLevel = *fZone;
        #if JUCE_DEBUG
            if (std::isnan(rawLevel)) {
                std::cerr << "uiVUMeter: NAN\n";
            }
        #endif
            if (fDB) {
                fLevel = range(rawLevel);
            } else {
                fLevel = range((rawLevel-fMin)/(fMax-fMin));
            }
            fLabel.setText(juce::String((int)rawLevel) + " " + fUnit, juce::dontSendNotification);
        }
        
        FAUSTFLOAT range(FAUSTFLOAT level) { return (level > fMax) ? fMax : ((level < fMin) ? fMin : level); }
    
    public:
    
        /**
         * \brief   Constructor.
         * \details Initialize the uiComponent variables and the VU-meter specific ones.
         *
         * \param   gui, zone, w, h, tooltip, label     uiComponent variables.
         * \param   mini                                Minimal value of the VU-meter range.
         * \param   maxi                                Maximal value of the VU-meter range.
         * \param   unit                                Unit of the VU-meter (dB or not).
         * \param   style                               Type of the VU-meter (see VUMeterType).
         * \param   vert                                True if vertical, false if horizontal.
         */
        uiVUMeter (GUI* gui, FAUSTFLOAT* zone, FAUSTFLOAT w, FAUSTFLOAT h, juce::String label, FAUSTFLOAT mini, FAUSTFLOAT maxi, juce::String unit, juce::String tooltip, VUMeterType style, bool vert)
            : uiComponent(gui, zone, w, h, label), fMin(mini), fMax(maxi), fStyle(style)
        {
            fLevel = 0;         // Initialization of the level
            startTimer(50);     // Launch a timer that trigger a callback every 50ms
            this->fUnit = unit;
            fDB = (unit == "dB");
            
            if (fDB) {
                // Conversion in dB of the range
                fScaleMin = dB2Scale(fMin);
                fScaleMax = dB2Scale(fMax);
            }
            setTooltip(tooltip);
            
            // No text editor for LEDs
            if (fStyle != Led) {
                setupLabel(tooltip);
            }
        }
        
        /** Method called by the timer every 50ms, to refresh the VU-meter if it needs to */
        void timerCallback() override
        {
            if (isShowing()) {
                //Force painting at the initialisation
                bool forceRepaint = (fLevel == 0);
                FAUSTFLOAT lastLevel = fLevel;   //t-1
                setLevel(); //t
                
                // Following condition means that we're repainting our VUMeter only if
                // there's one or more changing pixels between last state and this one,
                // and if the curent level is included in the VUMeter range. It improves
                // performances a lot in IDLE. It's the same for the other style of VUMeter
                
                if (fDB) {
                    switch (fStyle) {
                        case VVUMeter:
                            if (((int)dB2y(lastLevel) != (int)dB2y(fLevel) && fLevel >= fMin && fLevel <= fMax) || forceRepaint) {
                                repaint();
                            }
                            break;
                        case HVUMeter:
                            if (((int)dB2x(lastLevel) != (int)dB2x(fLevel) && fLevel >= fMin && fLevel <= fMax) || forceRepaint) {
                                repaint();
                            }
                            break;
                        case NumDisplay:
                            if (((int)lastLevel != (int)fLevel && fLevel >= fMin && fLevel <= fMax) || forceRepaint) {
                                repaint();
                            }
                            break;
                        case Led:
                            if ((dB2Scale(lastLevel) != dB2Scale(fLevel) && fLevel >= fMin && fLevel <= fMax) || forceRepaint) {
                                repaint();
                            }
                            break;
                        default:
                            break;
                    }
                } else {
                    switch (fStyle) {
                        case VVUMeter:
                            if (((int)lin2y(lastLevel) != (int)lin2y(fLevel) && fLevel >= fMin && fLevel <= fMax) || forceRepaint) {
                                repaint();
                            }
                            break;
                        case HVUMeter:
                            if ((std::abs(lastLevel-fLevel) > 0.01 && fLevel >= fMin && fLevel <= fMax) || forceRepaint) {
                                repaint();
                            }
                            break;
                        case NumDisplay:
                            if ((std::abs(lastLevel-fLevel) > 0.01 && fLevel >= fMin && fLevel <= fMax) || forceRepaint) {
                                repaint();
                            }
                            break;
                        case Led:
                            if (((int)lastLevel != (int)fLevel && fLevel >= fMin && fLevel <= fMax) || forceRepaint) {
                                repaint();
                            }
                            break;
                        default:
                            break;
                    }
                }
            } else {
                fLevel = 0;
            }
        }
        
        /**
         * Call the appropriate drawing method according to the VU-meter style
         * \see drawLed
         * \see drawNumDisplay
         * \see drawVBargraph
         * \see drawHBargraph
         */
        void paint(juce::Graphics& g) override
        {
            switch (fStyle) {
                case Led:
                    drawLed(g, kLedWidth, kLedHeight);
                    break;
                case NumDisplay:
                    drawNumDisplay(g, kNumDisplayWidth, kNumDisplayHeight/2);
                    break;
                case VVUMeter:
                    drawVBargraph(g, kVBargraphWidth/2, getHeight());
                    break;
                case HVUMeter:
                    drawHBargraph(g, getWidth(), kHBargraphHeight/2);
                    break;
                default:
                    break;
            }
        }
        
        /** Set the Label position whenever the layout size changes. */
        void resized() override
        {
            setLabelPos();
        }
        
        void reflectZone() override
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
        }
    
};

/** Intern class for tab widget */
class uiTabBox : public uiBase, public juce::TabbedComponent
{
    
public:
    /**
     * \brief   Constructor.
     * \details Initalize the juce::TabbedComponent tabs to be at top, and the uiTabBox size at 0
     */
    uiTabBox():uiBase(),juce::TabbedComponent(juce::TabbedButtonBar::TabsAtTop)
    {}
    
    /**
     * Initialize all his child ratios (1 uiBox per tabs), the LookAndFeel
     * and the uiTabBox size to fit the biggest of its child.
     */
    void init(juce::Component* comp = nullptr) override
    {
        for (int i = 0; i < getNumTabs(); i++) {
            Component* comp = getTabContentComponent(i);
            uiBase* base_comp = dynamic_cast<uiBase*>(comp);
            base_comp->init(comp);
            
            // The TabbedComponent size should be as big as its bigger child's dimension, done here
            fTotalWidth = juce::jmax(fTotalWidth, base_comp->getTotalWidth());
            fTotalHeight = juce::jmax(fTotalHeight, base_comp->getTotalHeight());
        }
        
        fTotalHeight += 30;  // 30 height for the TabBar.
    }
    
    void setRecommendedSize() override
    {
        for (int i = 0; i < getNumTabs(); i++) {
            uiBase* comp = dynamic_cast<uiBase*>(getTabContentComponent(i));
            comp->setRecommendedSize();
            
            // The TabbedComponent size should be as big as its bigger child's dimension, done here
            fTotalWidth = juce::jmax(fTotalWidth, comp->getTotalWidth());
            fTotalHeight = juce::jmax(fTotalHeight, comp->getTotalHeight());
        }
        
        fTotalHeight += 30;  // 30 height for the TabBar
    }
    
    void add(Component* comp) override
    {
        // Name of the component is moved in Tab (so removed from component)
        juce::TabbedComponent::addTab(comp->getName(), juce::Colours::white, comp, true);
        comp->setName("");
    }
    
};

/**
 * \brief   Intern class for box widgets
 * \details That's the class where the whole layout is calculated.
 */
class uiBox : public uiBase, public juce::Component
{
  
    private:
    
        bool fIsVertical;
    
        bool isNameDisplayed()
        {
            return (!(getName().startsWith("0x")) && getName().isNotEmpty());
        }
    
        /**
         * \brief   Return the vertical dimension size for a child to be displayed in.
         *
         */
        int getVSpaceToRemove()
        {
            // Checking if the name is displayed, to give to good amount space for child components
            // kNameHeight pixels is the bix name, kMargin pixel per child components for the margins
            if (isNameDisplayed()) {
                return (getHeight() - kNameHeight - kMargin * getNumChildComponents());
            } else {
                return (getHeight() - kMargin * getNumChildComponents());
            }
        }
    
        /**
         * \brief   Return the vertical dimension size for a child to be displayed in.
         *
         */
        int getHSpaceToRemove()
        {
            // Don't need to check for an horizontal box, as it height doesn't matter
            return (getWidth() - kMargin * getNumChildComponents());
        }
    
    public:
        /**
         * \brief   Constructor.
         * \details Initialize uiBase variables and uiBox specific ones.
         *
         * \param   vert        True if it's a vertical box, false otherwise.
         * \param   boxName     Name of the uiBox.
         */
        uiBox(bool vert, juce::String boxName): uiBase(0,0), juce::Component(boxName), fIsVertical(vert)
        {}
    
        /**
         * \brief   Destructor.
         * \details Delete all uiBox recusively, but not the uiComponent,
         *          because it's handled by the uiItem FAUST objects.
         */
        virtual ~uiBox()
        {
            /*
             Deleting boxes, from leaves to root:
             - leaves (uiComponent) are deleted by the uiItem mechanism
             - containers (uiBox and uiTabBox) have to be explicitly deleted
             */
            for (int i = getNumChildComponents()-1; i >= 0; i--) {
                delete dynamic_cast<uiBox*>(getChildComponent(i));
                delete dynamic_cast<uiTabBox*>(getChildComponent(i));
            }
        }

        /**
         * \brief   Initialization of the DisplayRect and Total size.
         * \details Calculate the correct size for each box, depending on its child sizes.
         */
        void setRecommendedSize() override
        {
            // Initialized each time
            fDisplayRectWidth = fDisplayRectHeight = 0;
            
            // Display rectangle size is the sum of a dimension on a side, and the max of the other one
            // on the other side, depending on its orientation (horizontal/vertical).
            // Using child's totalSize, because the display rectangle size need to be as big as
            // all of its child components with their margins included.
            for (int j = 0; j < getNumChildComponents(); j++) {
                uiBase* base_comp = dynamic_cast<uiBase*>(getChildComponent(j));
                if (fIsVertical) {
                    fDisplayRectWidth = juce::jmax(fDisplayRectWidth, base_comp->getTotalWidth());
                    fDisplayRectHeight += base_comp->getTotalHeight();
                } else {
                    fDisplayRectWidth += base_comp->getTotalWidth();
                    fDisplayRectHeight = juce::jmax(fDisplayRectHeight, base_comp->getTotalHeight());
                }
            }
            
            fTotalHeight = fDisplayRectHeight;
            fTotalWidth = fDisplayRectWidth;
            
            // Adding kMargin pixels of margins per child component on a dimension, and just kMargin on
            // the other one, depending on its orientation
            
            if (fIsVertical) {
                fTotalHeight += kMargin * getNumChildComponents();
                fTotalWidth += kMargin;
            } else {
                fTotalWidth += kMargin * getNumChildComponents();
                fTotalHeight += kMargin;
            }
         
            // Adding kNameHeight pixels on its height to allow the name to be displayed
            if (isNameDisplayed()) {
                fTotalHeight += kNameHeight;
            }
        }

        /** Initiate the current box ratio, and its child's ones recursively. */
        void init(juce::Component* comp = nullptr) override
        {
            uiBase::init(this);
            
            // Going through the Component tree recursively
            for (int i = 0; i < getNumChildComponents(); i++) {
                Component* comp = getChildComponent(i);
                uiBase* base_comp = dynamic_cast<uiBase*>(comp);
                base_comp->init(comp);
            }
        }

        /**
         * \brief   Main layout function.
         * \details Allow to place all uiBase child correctly according to their ratios
         *          and the current box size.
         *
         * \param   displayRect    Absolute raw bounds of the current box (with margins
         *                          and space for the title).
         */
        void resized() override
        {
            juce::Rectangle<int> displayRect = getBounds();
            
            // Deleting space for the box name if it needs to be shown
            if (isNameDisplayed()) {
                displayRect.removeFromTop(kNameHeight);
            }
            
            // Putting the margins
            displayRect.reduce(kMargin/2, kMargin/2);
            
            // Give child components an adapt size depending on its ratio and the current box size
            for (int i = 0; i < getNumChildComponents(); i++) {
                juce::Component* comp = getChildComponent(i);
                uiBase* base_comp = dynamic_cast<uiBase*>(comp);
                
                if (fIsVertical) {
                    int heightToRemove = getVSpaceToRemove() * base_comp->getVRatio();
                    // Remove the space needed from the displayRect, and translate it to show the margins
                    base_comp->setRelativeSize(comp, displayRect.removeFromTop(heightToRemove).translated(0, kMargin * i));
                } else {
                    int widthToRemove = getHSpaceToRemove() * base_comp->getHRatio();
                    // Remove the space needed from the displayRect, and translate it to show the margins
                    base_comp->setRelativeSize(comp, displayRect.removeFromLeft(widthToRemove).translated(kMargin * i, 0));
                }
            }
        }

        /** 
         * Fill the uiBox bounds with a grey color, different shades depending on its order.
         * Write the uiBox name if it needs to.
         */
        void paint(juce::Graphics& g) override
        {
            // Fill the box background in gray shades
            g.setColour(juce::Colours::black.withAlpha(0.05f));
            g.fillRect(getLocalBounds());

            // Display the name if it's needed
            if (isNameDisplayed()) {
                g.setColour(juce::Colours::black);
                g.drawText(getName(), getLocalBounds().withHeight(kNameHeight), juce::Justification::centred);
            }
        }
        
        void add(juce::Component* comp) override
        {
            addAndMakeVisible(comp);
        }
    
};

/** Class in charge of doing the glue between FAUST and JUCE */
class JuceGUI : public GUI, public MetaDataUI, public juce::Component
{
    
    private:
    
        std::stack<uiBase*> fBoxStack;
        uiBase* fCurrentBox = nullptr;   // Current box used in buildUserInterface logic.
        
        int fRadioGroupID;               // In case of radio buttons.
        std::unique_ptr<juce::LookAndFeel> fLaf = std::make_unique<juce::LookAndFeel_V4>();
    
        /** Add generic box to the user interface. */
        void openBox(uiBase* box)
        {
            if (fCurrentBox) {
                fCurrentBox->add(dynamic_cast<juce::Component*>(box));
                fBoxStack.push(fCurrentBox);
            }
            fCurrentBox = box;
        }
     
        /** Add a slider to the user interface. */
        void addSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step, int kWidth, int kHeight, SliderType type)
        {
            if (isKnob(zone)) {
                addKnob(label, zone, *zone, min, max, step);
            } else if (isRadio(zone)) {
                addRadioButtons(label, zone, *zone, min, max, step, fRadioDescription[zone].c_str(), false);
            } else if (isMenu(zone)) {
                addMenu(label, zone, *zone, min, max, step, fMenuDescription[zone].c_str());
            } else {
                fCurrentBox->add(new uiSlider(this, zone, kWidth, kHeight, *zone, min, max, step, juce::String(label), juce::String(fUnit[zone]), juce::String(fTooltip[zone]), getScale(zone), type));
            }
        }
        
        /** Add a radio buttons to the user interface. */
        void addRadioButtons(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step, const char* mdescr, bool vert)
        {
            std::vector<std::string> names;
            std::vector<double> values;
            parseMenuList(mdescr, names, values); // Set names and values vectors
            
            // and not just n checkButtons :
            // TODO : check currently unused checkButtonWidth...
            int checkButtonWidth = 0;
            for (int i = 0; i < names.size(); i++) {
                // Checking the maximum of horizontal space needed to display the radio buttons
                checkButtonWidth = juce::jmax(juce::Font().getStringWidth(juce::String(names[i])) + 15, checkButtonWidth);
            }
            
            if (vert) {
                fCurrentBox->add(new uiRadioButton(this, zone, juce::String(label), kCheckButtonWidth, names.size() * (kRadioButtonHeight - 25) + 25, *zone, min, max, true, names, values, juce::String(fTooltip[zone]), fRadioGroupID++));
            } else {
                fCurrentBox->add(new uiRadioButton(this, zone, juce::String(label), kCheckButtonWidth, kRadioButtonHeight, *zone, min, max, false, names, values, juce::String(fTooltip[zone]), fRadioGroupID++));
            }
        }
        
        /** Add a menu to the user interface. */
        void addMenu(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step, const char* mdescr)
        {
            fCurrentBox->add(new uiMenu(this, zone, juce::String(label), kMenuWidth, kMenuHeight, *zone, min, max, juce::String(fTooltip[zone]), mdescr));
        }
        
        /** Add a ciruclar slider to the user interface. */
        void addKnob(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {
            fCurrentBox->add(new uiSlider(this, zone, kKnobWidth, kKnobHeight, *zone, min, max, step, juce::String(label), juce::String(fUnit[zone]), juce::String(fTooltip[zone]), getScale(zone), Knob));
        }
        
        /** Add a bargraph to the user interface. */
        void addBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max, int kWidth, int kHeight, VUMeterType type)
        {
            if (isLed(zone)) {
                addLed(juce::String(label), zone, min, max);
            } else if (isNumerical(zone)) {
                addNumericalDisplay(juce::String(label), zone, min, max);
            } else {
                fCurrentBox->add(new uiVUMeter (this, zone, kWidth, kHeight, juce::String(label), min, max, juce::String(fUnit[zone]), juce::String(fTooltip[zone]), type, false));
            }
        }
        
    public:
        /**
         * \brief   Constructor, displaying the *current state* of all controller zones.
         * \details Initialize the JuceGUI specific variables. 
         */
        JuceGUI():fRadioGroupID(1) // fRadioGroupID must start at 1
        {
            setLookAndFeel(fLaf.get());
        }
        
        /**
         * \brief   Destructor.
         * \details Delete root box used in buildUserInterface logic.
         */
        virtual ~JuceGUI()
        {
            setLookAndFeel(nullptr);
            delete fCurrentBox;
        }

        /** Return the size of the FAUST program */
        juce::Rectangle<int> getSize()
        {
            // Mininum size in case of empty GUI
            if (fCurrentBox) {
                juce::Rectangle<int> res = fCurrentBox->getSize();
                res.setSize(std::max<int>(1, res.getWidth()), std::max<int>(1, res.getHeight()));
                return res;
            } else {
                return juce::Rectangle<int>(0, 0, 1, 1);
            }
        }

        /** Initialize the uiTabBox component to be visible. */
        virtual void openTabBox(const char* label) override
        {
            openBox(new uiTabBox());
        }
        
        /** Add a new vertical box to the user interface. */
        virtual void openVerticalBox(const char* label) override
        {
            openBox(new uiBox(true, juce::String(label)));
        }

        /** Add a new horizontal box to the user interface. */
        virtual void openHorizontalBox(const char* label) override
        {
            openBox(new uiBox(false, juce::String(label)));
        }

        /** Close the current box. */
        virtual void closeBox() override
        {
            fCurrentBox->setRecommendedSize();
            
            if (fBoxStack.empty()) {
                // Add root box in JuceGUI component
                addAndMakeVisible(dynamic_cast<juce::Component*>(fCurrentBox));
                fCurrentBox->init();
                // Force correct draw
                resized();
            } else {
                fCurrentBox = fBoxStack.top();
                fBoxStack.pop();
            }
        }
     
        /** Add an horizontal slider to the user interface. */
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) override
        {
            addSlider(label, zone, init, min, max, step, kHSliderWidth, kHSliderHeight, HSlider);
        }
        
        /** Add a vertical slider to the user interface. */
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) override
        {
            int newWidth = juce::jmax(juce::Font().getStringWidth(juce::String(label)), kVSliderWidth) + kMargin;
            addSlider(label, zone, init, min, max, step, newWidth, kVSliderHeight, VSlider);
        }
        
        /** Add a button to the user interface. */
        virtual void addButton(const char* label, FAUSTFLOAT* zone) override
        {
            fCurrentBox->add(new uiButton(this, zone, kButtonWidth, kButtonHeight, juce::String(label), juce::String(fTooltip[zone])));
        }
        
        /** Add a check button to the user interface. */
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone) override
        {
            // newWidth is his text size, plus the check box size
            int newWidth = juce::Font().getStringWidth(juce::String(label)) + kCheckButtonWidth;
            fCurrentBox->add(new uiCheckButton(this, zone, newWidth, kCheckButtonHeight, juce::String(label), juce::String(fTooltip[zone])));
        }
        
        /** Add a numerical entry to the user interface. */
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) override
        {
            // kMargin pixels between the slider and his name
            int newWidth = juce::Font().getStringWidth(juce::String(label)) + kNumEntryWidth + kMargin;
            fCurrentBox->add(new uiSlider(this, zone, newWidth, kNumEntryHeight, *zone, min, max, step, juce::String(label), juce::String(fUnit[zone]), juce::String(fTooltip[zone]), getScale(zone), NumEntry));
        }
        
        /** Add a vertical bargraph to the user interface. */
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) override
        {
            addBargraph(label, zone, min, max, kVBargraphWidth, kVBargraphHeight, VVUMeter);
        }
        
        /** Add a vertical bargraph to the user interface. */
        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) override
        {
            addBargraph(label, zone, min, max, kHBargraphWidth, kHBargraphHeight, HVUMeter);
        }
      
        /** Add a LED to the user interface. */
        void addLed(juce::String label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            fCurrentBox->add(new uiVUMeter(this, zone, kLedWidth, kLedHeight, label, min, max, juce::String(fUnit[zone]), juce::String(fTooltip[zone]), Led, false));
        }
        
        /** Add a numerical display to the user interface. */
        void addNumericalDisplay(juce::String label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) {
            fCurrentBox->add(new uiVUMeter(this, zone, kNumDisplayWidth, kNumDisplayHeight, label, min, max, juce::String(fUnit[zone]), juce::String(fTooltip[zone]), NumDisplay, false));
        }
        
        /** Declare a metadata. */
        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* value) override
        {
            MetaDataUI::declare(zone, key, value);
        }

        /** Resize its child to match the new bounds */
        void resized() override
        {
            if (fCurrentBox) {
                dynamic_cast<Component*>(fCurrentBox)->setBounds(getLocalBounds());
            }
        }
    
};

#endif
/**************************  END  JuceGUI.h **************************/
#endif
/************************** BEGIN JuceParameterUI.h *************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef JuceParameterUI_H
#define JuceParameterUI_H

#include "../JuceLibraryCode/JuceHeader.h"


// Link AudioParameterBool with on/off parameter

struct FaustPlugInAudioParameterBool : public juce::AudioParameterBool, public uiOwnedItem {
    
    FaustPlugInAudioParameterBool(GUI* gui, FAUSTFLOAT* zone, const std::string& path, const std::string& label)
    :juce::AudioParameterBool(path, label, false), uiOwnedItem(gui, zone)
    {}
    
    virtual ~FaustPlugInAudioParameterBool() {}
    
    void reflectZone() override
    {
        FAUSTFLOAT v = *fZone;
        fCache = v;
        setValueNotifyingHost(float(v));
    }
    
    virtual void setValue (float newValue) override
    {
        modifyZone(FAUSTFLOAT(newValue));
    }
    
};

// Link AudioParameterFloat with range parameters

struct FaustPlugInAudioParameterFloat : public juce::AudioParameterFloat, public uiOwnedItem {
    
    FaustPlugInAudioParameterFloat(GUI* gui, FAUSTFLOAT* zone, const std::string& path, const std::string& label, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    :juce::AudioParameterFloat(path, label, float(min), float(max), float(init)), uiOwnedItem(gui, zone)
    {}
    
    virtual ~FaustPlugInAudioParameterFloat() {}
    
    void reflectZone() override
    {
        FAUSTFLOAT v = *fZone;
        fCache = v;
        if (v >= range.start && v <= range.end) {
            setValueNotifyingHost(range.convertTo0to1(float(v)));
        }
    }
    
    virtual void setValue (float newValue) override
    {
        modifyZone(FAUSTFLOAT(range.convertFrom0to1(newValue)));
    }
    
};

// A class to create AudioProcessorParameter objects for each zone

class JuceParameterUI : public GUI, public PathBuilder {
    
    private:
        
        juce::AudioProcessor* fProcessor;
        
    public:
        
        JuceParameterUI(juce::AudioProcessor* processor):fProcessor(processor)
        {}
    
        virtual ~JuceParameterUI() {}
        
        // -- widget's layouts
        
        virtual void openTabBox(const char* label)
        {
            pushLabel(label);
        }
        virtual void openHorizontalBox(const char* label)
        {
            pushLabel(label);
        }
        virtual void openVerticalBox(const char* label)
        {
            pushLabel(label);
        }
        virtual void closeBox()
        {
            popLabel();
        }
        
        // -- active widgets
        
        virtual void addButton(const char* label, FAUSTFLOAT* zone)
        {
            fProcessor->addParameter(new FaustPlugInAudioParameterBool(this, zone, buildPath(label), label));
        }
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            fProcessor->addParameter(new FaustPlugInAudioParameterBool(this, zone, buildPath(label), label));
        }
        
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            fProcessor->addParameter(new FaustPlugInAudioParameterFloat(this, zone, buildPath(label), label, init, min, max, step));
        }
        
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            fProcessor->addParameter(new FaustPlugInAudioParameterFloat(this, zone, buildPath(label), label, init, min, max, step));
        }
        
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            fProcessor->addParameter(new FaustPlugInAudioParameterFloat(this, zone, buildPath(label), label, init, min, max, step));
        }
        
        // -- passive widgets
        
        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            fProcessor->addParameter(new FaustPlugInAudioParameterFloat(this, zone, buildPath(label), label, 0, min, max, 0));
        }
        
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            fProcessor->addParameter(new FaustPlugInAudioParameterFloat(this, zone, buildPath(label), label, 0, min, max, 0));
        }
    
};

#endif
/**************************  END  JuceParameterUI.h **************************/
/************************** BEGIN JuceStateUI.h **************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef JuceStateUI_H
#define JuceStateUI_H

#include "../JuceLibraryCode/JuceHeader.h"


// A class to save/restore DSP state using JUCE, which also set default values at construction time.

struct JuceStateUI : public MapUI {
    
    bool fRestored;
    
    JuceStateUI():fRestored(false) {}
    virtual ~JuceStateUI() {}
    
    void getStateInformation (juce::MemoryBlock& destData)
    {
        juce::MemoryOutputStream stream (destData, true);
        
        // Write path and values
        if (sizeof(FAUSTFLOAT) == sizeof(float)) {
            for (const auto& it : fPathZoneMap) {
                stream.writeString(it.first);
                stream.writeFloat(*it.second);
            }
        } else {
            for (const auto& it : fPathZoneMap) {
                stream.writeString(it.first);
                stream.writeDouble(*it.second);
            }
        }
    }
    
    void setStateInformation (const void* data, int sizeInBytes)
    {
        fRestored = true;
        juce::MemoryInputStream stream (data, static_cast<size_t> (sizeInBytes), false);
        std::string path;
        
        // Read path then value and try to restore them
        if (sizeof(FAUSTFLOAT) == sizeof(float)) {
            while ((path = stream.readString().toStdString()) != "") {
                setParamValue(path, stream.readFloat());
            }
        } else {
            while ((path = stream.readString().toStdString()) != "") {
                setParamValue(path, stream.readDouble());
            }
        }
    }
    
    // -- active widgets
    // use MapUI derived methods
    
    // -- passive widgets
    // empty si we don't want to save/restore them
    void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax) {}
    void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax) {}
    
};

#endif
/**************************  END  JuceStateUI.h **************************/

// Always included otherwise -i mode sometimes fails...

#if defined(SOUNDFILE)
/************************** BEGIN SoundUI.h **************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ********************************************************************/
 
#ifndef __SoundUI_H__
#define __SoundUI_H__

#include <map>
#include <vector>
#include <string>
#include <iostream>


#if defined(__APPLE__) && !defined(__VCVRACK__) && !defined(JUCE_32BIT) && !defined(JUCE_64BIT)
#include <CoreFoundation/CFBundle.h>
#endif

// Always included otherwise -i mode later on will not always include it (with the conditional includes)
/************************** BEGIN Soundfile.h **************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ********************************************************************/

#ifndef __Soundfile__
#define __Soundfile__

#include <string.h>
#include <string>
#include <vector>

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#define BUFFER_SIZE 1024
#define SAMPLE_RATE 44100
#define MAX_CHAN 64
#define MAX_SOUNDFILE_PARTS 256

#ifdef _MSC_VER
#define PRE_PACKED_STRUCTURE __pragma(pack(push, 1))
#define POST_PACKED_STRUCTURE \
    ;                         \
    __pragma(pack(pop))
#else
#define PRE_PACKED_STRUCTURE
#define POST_PACKED_STRUCTURE __attribute__((__packed__))
#endif

/*
 The soundfile structure to be used by the DSP code. Soundfile has a MAX_SOUNDFILE_PARTS parts 
 (even a single soundfile or an empty soundfile). 
 The fLength, fOffset and fSR fields are filled accordingly by repeating the actual parts if needed.
 The fBuffers contains MAX_CHAN non-interleaved arrays of samples.
 
 It has to be 'packed' to that the LLVM backend can correctly access it.

 Index computation:
    - p is the current part number [0..MAX_SOUNDFILE_PARTS-1] (must be proved by the type system)
    - i is the current position in the part. It will be constrained between [0..length]
    - idx(p,i) = fOffset[p] + max(0, min(i, fLength[p]));
*/

PRE_PACKED_STRUCTURE
struct Soundfile {
    void* fBuffers; // will correspond to a double** or float** pointer chosen at runtime
    int* fLength;   // length of each part (so fLength[P] contains the length in frames of part P)
    int* fSR;       // sample rate of each part (so fSR[P] contains the SR of part P)
    int* fOffset;   // offset of each part in the global buffer (so fOffset[P] contains the offset in frames of part P)
    int fChannels;  // max number of channels of all concatenated files
    int fParts;     // the total number of loaded parts
    bool fIsDouble; // keep the sample format (float or double)

    Soundfile(int cur_chan, int length, int max_chan, int total_parts, bool is_double)
    {
        fLength   = new int[MAX_SOUNDFILE_PARTS];
        fSR       = new int[MAX_SOUNDFILE_PARTS];
        fOffset   = new int[MAX_SOUNDFILE_PARTS];
        fIsDouble = is_double;
        fChannels = cur_chan;
        fParts    = total_parts;
        if (fIsDouble) {
            fBuffers = allocBufferReal<double>(cur_chan, length, max_chan);
        } else {
            fBuffers = allocBufferReal<float>(cur_chan, length, max_chan);
        }
    }
    
    template <typename REAL>
    void* allocBufferReal(int cur_chan, int length, int max_chan)
    {
        REAL** buffers = new REAL*[max_chan];
        for (int chan = 0; chan < cur_chan; chan++) {
            buffers[chan] = new REAL[length];
            memset(buffers[chan], 0, sizeof(REAL) * length);
        }
        return buffers;
    }
    
    void copyToOut(int size, int channels, int max_channels, int offset, void* buffer)
    {
        if (fIsDouble) {
            copyToOutReal<double>(size, channels, max_channels, offset, buffer);
       } else {
            copyToOutReal<float>(size, channels, max_channels, offset, buffer);
        }
    }
    
    void shareBuffers(int cur_chan, int max_chan)
    {
        // Share the same buffers for all other channels so that we have max_chan channels available
        if (fIsDouble) {
            for (int chan = cur_chan; chan < max_chan; chan++) {
                static_cast<double**>(fBuffers)[chan] = static_cast<double**>(fBuffers)[chan % cur_chan];
            }
        } else {
            for (int chan = cur_chan; chan < max_chan; chan++) {
                static_cast<float**>(fBuffers)[chan] = static_cast<float**>(fBuffers)[chan % cur_chan];
            }
        }
    }
    
    template <typename REAL>
    void copyToOutReal(int size, int channels, int max_channels, int offset, void* buffer)
    {
        for (int sample = 0; sample < size; sample++) {
            for (int chan = 0; chan < channels; chan++) {
                static_cast<REAL**>(fBuffers)[chan][offset + sample] = static_cast<REAL*>(buffer)[sample * max_channels + chan];
            }
        }
    }
    
    template <typename REAL>
    void getBuffersOffsetReal(void* buffers, int offset)
    {
        for (int chan = 0; chan < fChannels; chan++) {
            static_cast<REAL**>(buffers)[chan] = &(static_cast<REAL**>(fBuffers))[chan][offset];
        }
    }
    
    void emptyFile(int part, int& offset)
    {
        fLength[part] = BUFFER_SIZE;
        fSR[part] = SAMPLE_RATE;
        fOffset[part] = offset;
        // Update offset
        offset += fLength[part];
    }
 
    ~Soundfile()
    {
        // Free the real channels only
        if (fIsDouble) {
            for (int chan = 0; chan < fChannels; chan++) {
                delete[] static_cast<double**>(fBuffers)[chan];
            }
            delete[] static_cast<double**>(fBuffers);
        } else {
            for (int chan = 0; chan < fChannels; chan++) {
                delete[] static_cast<float**>(fBuffers)[chan];
            }
            delete[] static_cast<float**>(fBuffers);
        }
        delete[] fLength;
        delete[] fSR;
        delete[] fOffset;
    }

} POST_PACKED_STRUCTURE;

/*
 The generic soundfile reader.
 */

class SoundfileReader {
    
   protected:
    
    int fDriverSR;
   
    // Check if a soundfile exists and return its real path_name
    std::string checkFile(const std::vector<std::string>& sound_directories, const std::string& file_name)
    {
        if (checkFile(file_name)) {
            return file_name;
        } else {
            for (size_t i = 0; i < sound_directories.size(); i++) {
                std::string path_name = sound_directories[i] + "/" + file_name;
                if (checkFile(path_name)) { return path_name; }
            }
            return "";
        }
    }
    
    bool isResampling(int sample_rate) { return (fDriverSR > 0 && fDriverSR != sample_rate); }
 
    // To be implemented by subclasses

    /**
     * Check the availability of a sound resource.
     *
     * @param path_name - the name of the file, or sound resource identified this way
     *
     * @return true if the sound resource is available, false otherwise.
     */
    virtual bool checkFile(const std::string& path_name) = 0;
    
    /**
     * Check the availability of a sound resource.
     *
     * @param buffer - the sound buffer
     * @param size - the sound buffer length
     *
     * @return true if the sound resource is available, false otherwise.
     */

    virtual bool checkFile(unsigned char* buffer, size_t size) { return true; }

    /**
     * Get the channels and length values of the given sound resource.
     *
     * @param path_name - the name of the file, or sound resource identified this way
     * @param channels - the channels value to be filled with the sound resource number of channels
     * @param length - the length value to be filled with the sound resource length in frames
     *
     */
    virtual void getParamsFile(const std::string& path_name, int& channels, int& length) = 0;
    
    /**
     * Get the channels and length values of the given sound resource.
     *
     * @param buffer - the sound buffer
     * @param size - the sound buffer length
     * @param channels - the channels value to be filled with the sound resource number of channels
     * @param length - the length value to be filled with the sound resource length in frames
     *
     */
    virtual void getParamsFile(unsigned char* buffer, size_t size, int& channels, int& length) {}

    /**
     * Read one sound resource and fill the 'soundfile' structure accordingly
     *
     * @param soundfile - the soundfile to be filled
     * @param path_name - the name of the file, or sound resource identified this way
     * @param part - the part number to be filled in the soundfile
     * @param offset - the offset value to be incremented with the actual sound resource length in frames
     * @param max_chan - the maximum number of mono channels to fill
     *
     */
    virtual void readFile(Soundfile* soundfile, const std::string& path_name, int part, int& offset, int max_chan) = 0;
    
    /**
     * Read one sound resource and fill the 'soundfile' structure accordingly
     *
     * @param soundfile - the soundfile to be filled
     * @param buffer - the sound buffer
     * @param size - the sound buffer length
     * @param part - the part number to be filled in the soundfile
     * @param offset - the offset value to be incremented with the actual sound resource length in frames
     * @param max_chan - the maximum number of mono channels to fill
     *
     */
    virtual void readFile(Soundfile* soundfile, unsigned char* buffer, size_t size, int part, int& offset, int max_chan) {}

  public:
    
    virtual ~SoundfileReader() {}
    
    void setSampleRate(int sample_rate) { fDriverSR = sample_rate; }
   
    Soundfile* createSoundfile(const std::vector<std::string>& path_name_list, int max_chan, bool is_double)
    {
        try {
            int cur_chan = 1; // At least one channel
            int total_length = 0;
            
            // Compute total length and channels max of all files
            for (int i = 0; i < int(path_name_list.size()); i++) {
                int chan, length;
                if (path_name_list[i] == "__empty_sound__") {
                    length = BUFFER_SIZE;
                    chan = 1;
                } else {
                    getParamsFile(path_name_list[i], chan, length);
                }
                cur_chan = std::max<int>(cur_chan, chan);
                total_length += length;
            }
           
            // Complete with empty parts
            total_length += (MAX_SOUNDFILE_PARTS - path_name_list.size()) * BUFFER_SIZE;
            
            // Create the soundfile
            Soundfile* soundfile = new Soundfile(cur_chan, total_length, max_chan, path_name_list.size(), is_double);
            
            // Init offset
            int offset = 0;
            
            // Read all files
            for (int i = 0; i < int(path_name_list.size()); i++) {
                if (path_name_list[i] == "__empty_sound__") {
                    soundfile->emptyFile(i, offset);
                } else {
                    readFile(soundfile, path_name_list[i], i, offset, max_chan);
                }
            }
            
            // Complete with empty parts
            for (int i = int(path_name_list.size()); i < MAX_SOUNDFILE_PARTS; i++) {
                soundfile->emptyFile(i, offset);
            }
            
            // Share the same buffers for all other channels so that we have max_chan channels available
            soundfile->shareBuffers(cur_chan, max_chan);
            return soundfile;
            
        } catch (...) {
            return nullptr;
        }
    }

    // Check if all soundfiles exist and return their real path_name
    std::vector<std::string> checkFiles(const std::vector<std::string>& sound_directories,
                                        const std::vector<std::string>& file_name_list)
    {
        std::vector<std::string> path_name_list;
        for (size_t i = 0; i < file_name_list.size(); i++) {
            std::string path_name = checkFile(sound_directories, file_name_list[i]);
            // If 'path_name' is not found, it is replaced by an empty sound (= silence)
            path_name_list.push_back((path_name == "") ? "__empty_sound__" : path_name);
        }
        return path_name_list;
    }

};

#endif
/**************************  END  Soundfile.h **************************/

#if defined(JUCE_32BIT) || defined(JUCE_64BIT)
/************************** BEGIN JuceReader.h **************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __JuceReader__
#define __JuceReader__

#include <assert.h>

#include "../JuceLibraryCode/JuceHeader.h"


struct JuceReader : public SoundfileReader {
    
    juce::AudioFormatManager fFormatManager;
    
    JuceReader() { fFormatManager.registerBasicFormats(); }
    virtual ~JuceReader()
    {}
    
    bool checkFile(const std::string& path_name)
    {
        juce::File file(path_name);
        if (file.existsAsFile()) {
            return true;
        } else {
            std::cerr << "ERROR : cannot open '" << path_name << "'" << std::endl;
            return false;
        }
    }
    
    void getParamsFile(const std::string& path_name, int& channels, int& length)
    {
        std::unique_ptr<juce::AudioFormatReader> formatReader (fFormatManager.createReaderFor (juce::File (path_name)));
        channels = int(formatReader->numChannels);
        length = int(formatReader->lengthInSamples);
    }
    
    void readFile(Soundfile* soundfile, const std::string& path_name, int part, int& offset, int max_chan)
    {
        std::unique_ptr<juce::AudioFormatReader> formatReader (fFormatManager.createReaderFor (juce::File (path_name)));
        
        soundfile->fLength[part] = int(formatReader->lengthInSamples);
        soundfile->fSR[part] = int(formatReader->sampleRate);
        soundfile->fOffset[part] = offset;
        
        void* buffers;
        if (soundfile->fIsDouble) {
            buffers = alloca(soundfile->fChannels * sizeof(double*));
            soundfile->getBuffersOffsetReal<double>(buffers, offset);
        } else {
            buffers = alloca(soundfile->fChannels * sizeof(float*));
            soundfile->getBuffersOffsetReal<float>(buffers, offset);
        }
        
        if (formatReader->read(reinterpret_cast<int *const *>(buffers), int(formatReader->numChannels), 0, int(formatReader->lengthInSamples), false)) {
            
            // Possibly convert samples
            if (!formatReader->usesFloatingPointData) {
                for (int chan = 0; chan < int(formatReader->numChannels); ++chan) {
                    if (soundfile->fIsDouble) {
                        // TODO
                    } else {
                        float* buffer = &(static_cast<float**>(soundfile->fBuffers))[chan][soundfile->fOffset[part]];
                        juce::FloatVectorOperations::convertFixedToFloat(buffer, reinterpret_cast<const int*>(buffer),
                                                                         1.0f/0x7fffffff, int(formatReader->lengthInSamples));
                    }
                }
            }
            
        } else {
            std::cerr << "Error reading the file : " << path_name << std::endl;
        }
            
        // Update offset
        offset += soundfile->fLength[part];
    }
    
};

#endif
/**************************  END  JuceReader.h **************************/
static JuceReader gReader;
#elif defined(ESP32)
/************************** BEGIN Esp32Reader.h **************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 *************************************************************************/

#ifndef FAUST_ESP32READER_H
#define FAUST_ESP32READER_H

#include <stdio.h>
#include "esp_err.h"
#include "esp_log.h"
#include "esp_spi_flash.h"
#include "esp_vfs_fat.h"
#include "driver/sdspi_host.h"
#include "sdmmc_cmd.h"

/************************** BEGIN WaveReader.h **************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ********************************************************************/

#ifndef __WaveReader__
#define __WaveReader__

#include <string.h>
#include <assert.h>
#include <stdio.h>


// WAVE file description
typedef struct {
    
    // The canonical WAVE format starts with the RIFF header
    
    /**
     Variable: chunk_id
     Contains the letters "RIFF" in ASCII form (0x52494646 big-endian form).
     **/
    int chunk_id;
    
    /**
     Variable: chunk_size
     36 + SubChunk2Size, or more precisely: 4 + (8 + SubChunk1Size) + (8 + SubChunk2Size)
     This is the size of the rest of the chunk following this number.
     This is the size of the entire file in bytes minus 8 bytes for the
     two fields not included in this count: ChunkID and ChunkSize.
     **/
    int chunk_size;
    
    /**
     Variable: format
     Contains the letters "WAVE" (0x57415645 big-endian form).
     **/
    int format;
    
    // The "WAVE" format consists of two subchunks: "fmt " and "data":
    // The "fmt " subchunk describes the sound data's format:
    
    /**
     Variable: subchunk_1_id
     Contains the letters "fmt " (0x666d7420 big-endian form).
     **/
    int subchunk_1_id;
    
    /**
     Variable: subchunk_1_size
     16 for PCM. This is the size of the rest of the Subchunk which follows this number.
     **/
    int subchunk_1_size;
    
    /**
     Variable: audio_format
     PCM = 1 (i.e. Linear quantization) Values other than 1 indicate some form of compression.
     **/
    short audio_format;
    
    /**
     Variable: num_channels
     Mono = 1, Stereo = 2, etc.
     **/
    short num_channels;
    
    /**
     Variable: sample_rate
     8000, 44100, etc.
     **/
    int sample_rate;
    
    /**
     Variable: byte_rate
     == SampleRate * NumChannels * BitsPerSample/8
     **/
    int byte_rate;
    
    /**
     Variable: block_align
     == NumChannels * BitsPerSample/8
     The number of bytes for one sample including all channels. I wonder what happens
     when this number isn't an integer?
     **/
    short block_align;
    
    /**
     Variable: bits_per_sample
     8 bits = 8, 16 bits = 16, etc.
     **/
    short bits_per_sample;
    
    /**
     Here should come some extra parameters which i will avoid.
     **/
    
    // The "data" subchunk contains the size of the data and the actual sound:
    
    /**
     Variable: subchunk_2_id
     Contains the letters "data" (0x64617461 big-endian form).
     **/
    int subchunk_2_id;
    
    /**
     Variable: subchunk_2_size
     == NumSamples * NumChannels * BitsPerSample/8
     This is the number of bytes in the data. You can also think of this as the size
     of the read of the subchunk following this number.
     **/
    int subchunk_2_size;
    
    /**
     Variable: data
     The actual sound data.
     **/
    char* data;
    
} wave_t;

// Base reader
struct Reader {
    
    wave_t* fWave;

    inline int is_big_endian()
    {
        int a = 1;
        return !((char*)&a)[0];
    }
    
    inline int convert_to_int(char* buffer, int len)
    {
        int a = 0;
        if (!is_big_endian()) {
            for(int i = 0; i < len; i++) {
                ((char*)&a)[i] = buffer[i];
            }
        } else {
            for(int i = 0; i < len; i++) {
                ((char*)&a)[3-i] = buffer[i];
            }
        }
        return a;
    }
    
    Reader()
    {
        fWave = (wave_t*)calloc(1, sizeof(wave_t));
    }

    virtual ~Reader()
    {
        free(fWave->data);
        free(fWave);
    }

    bool load_wave_header()
    {
        char buffer[4];
        
        read(buffer, 4);
        if (strncmp(buffer, "RIFF", 4) != 0) {
            fprintf(stderr, "This is not valid WAV file!\n");
            return false;
        }
        fWave->chunk_id = convert_to_int(buffer, 4);
        
        read(buffer, 4);
        fWave->chunk_size = convert_to_int(buffer, 4);
        
        read(buffer, 4);
        fWave->format = convert_to_int(buffer, 4);
        
        read(buffer, 4);
        fWave->subchunk_1_id = convert_to_int(buffer, 4);
        
        read(buffer, 4);
        fWave->subchunk_1_size = convert_to_int(buffer, 4);
        
        read(buffer, 2);
        fWave->audio_format = convert_to_int(buffer, 2);
        
        read(buffer, 2);
        fWave->num_channels = convert_to_int(buffer, 2);
        
        read(buffer, 4);
        fWave->sample_rate = convert_to_int(buffer, 4);
        
        read(buffer, 4);
        fWave->byte_rate = convert_to_int(buffer, 4);
        
        read(buffer, 2);
        fWave->block_align = convert_to_int(buffer, 2);
        
        read(buffer, 2);
        fWave->bits_per_sample = convert_to_int(buffer, 2);
        
        read(buffer, 4);
        if (strncmp(buffer, "data", 4) != 0) {
            read(buffer, 4);
            int _extra_size = convert_to_int(buffer, 4);
            char _extra_data[_extra_size];
            read(_extra_data, _extra_size);
            read(buffer, 4);
            fWave->subchunk_2_id = convert_to_int(buffer, 4);
        } else {
            fWave->subchunk_2_id = convert_to_int(buffer, 4);
        }
        
        read(buffer, 4);
        fWave->subchunk_2_size = convert_to_int(buffer, 4);
        return true;
    }
    
    void load_wave()
    {
        // Read sound data
        fWave->data = (char*)malloc(fWave->subchunk_2_size);
        read(fWave->data, fWave->subchunk_2_size);
    }

    virtual void read(char* buffer, unsigned int size) = 0;
   
};

struct FileReader : public Reader {
    
    FILE* fFile;
    
    FileReader(const std::string& file_path)
    {
        fFile = fopen(file_path.c_str(), "rb");
        if (!fFile) {
            fprintf(stderr, "FileReader : cannot open file!\n");
            throw -1;
        }
        if (!load_wave_header()) {
            fprintf(stderr, "FileReader : not a WAV file!\n");
            throw -1;
        }
    }
    
    virtual ~FileReader()
    {
        fclose(fFile);
    }
    
    void read(char* buffer, unsigned int size)
    {
        fread(buffer, 1, size, fFile);
    }
    
};

extern const uint8_t file_start[] asm("_binary_FILE_start");
extern const uint8_t file_end[]   asm("_binary_FILE_end");

struct MemoryReader : public Reader {
    
    int fPos;
    const uint8_t* fStart;
    const uint8_t* fEnd;
    
    MemoryReader(const uint8_t* start, const uint8_t* end):fPos(0)
    {
        fStart = start;
        fEnd = end;
        if (!load_wave_header()) {
            fprintf(stderr, "MemoryReader : not a WAV file!\n");
            throw -1;
        }
    }
    
    virtual ~MemoryReader()
    {}
    
    void read(char* buffer, unsigned int size)
    {
        memcpy(buffer, fStart + fPos, size);
        fPos += size;
    }
    
};

// Using a FileReader to implement SoundfileReader

struct WaveReader : public SoundfileReader {
    
    WaveReader() {}
    virtual ~WaveReader() {}
    
    virtual bool checkFile(const std::string& path_name)
    {
        try {
            FileReader reader(path_name);
            return true;
        } catch (...)  {
            return false;
        }
    }
    
    virtual void getParamsFile(const std::string& path_name, int& channels, int& length)
    {
        FileReader reader(path_name);
        channels = reader.fWave->num_channels;
        length = (reader.fWave->subchunk_2_size * 8) / (reader.fWave->num_channels * reader.fWave->bits_per_sample);
    }
    
    virtual void readFile(Soundfile* soundfile, const std::string& path_name, int part, int& offset, int max_chan)
    {
        FileReader reader(path_name);
        reader.load_wave();
        
        soundfile->fLength[part] = (reader.fWave->subchunk_2_size * 8) / (reader.fWave->num_channels * reader.fWave->bits_per_sample);
        soundfile->fSR[part] = reader.fWave->sample_rate;
        soundfile->fOffset[part] = offset;
        
        // Audio frames have to be written for each chan
        if (reader.fWave->bits_per_sample == 16) {
            float factor = 1.f/32767.f;
            for (int sample = 0; sample < soundfile->fLength[part]; sample++) {
                short* frame = (short*)&reader.fWave->data[reader.fWave->block_align * sample];
                for (int chan = 0; chan < reader.fWave->num_channels; chan++) {
                    soundfile->fBuffers[chan][offset + sample] = frame[chan] * factor;
                }
            }
        } else if (reader.fWave->bits_per_sample == 32) {
            fprintf(stderr, "readFile : not implemented\n");
        }
        
        // Update offset
        offset += soundfile->fLength[part];
    }
};

#endif
/**************************  END  WaveReader.h **************************/

#define TAG "Esp32Reader"

#define SD_PIN_NUM_MISO GPIO_NUM_2
#define SD_PIN_NUM_MOSI GPIO_NUM_15
#define SD_PIN_NUM_CLK  GPIO_NUM_14
#define SD_PIN_NUM_CS   GPIO_NUM_13

struct Esp32Reader : public WaveReader {
    
    void sdcard_init()
    {
        ESP_LOGI(TAG, "Initializing SD card");
        ESP_LOGI(TAG, "Using SPI peripheral");
        
        sdmmc_host_t host = SDSPI_HOST_DEFAULT();
        sdspi_slot_config_t slot_config = SDSPI_SLOT_CONFIG_DEFAULT();
        slot_config.gpio_miso = SD_PIN_NUM_MISO;
        slot_config.gpio_mosi = SD_PIN_NUM_MOSI;
        slot_config.gpio_sck  = SD_PIN_NUM_CLK;
        slot_config.gpio_cs   = SD_PIN_NUM_CS;
        // This initializes the slot without card detect (CD) and write protect (WP) signals.
        // Modify slot_config.gpio_cd and slot_config.gpio_wp if your board has these signals.
        
        // Options for mounting the filesystem.
        // If format_if_mount_failed is set to true, SD card will be partitioned and
        // formatted in case when mounting fails.
        esp_vfs_fat_sdmmc_mount_config_t mount_config = {
            .format_if_mount_failed = false,
            .max_files = 5,
            .allocation_unit_size = 16 * 1024
        };
        
        // Use settings defined above to initialize SD card and mount FAT filesystem.
        // Note: esp_vfs_fat_sdmmc_mount is an all-in-one convenience function.
        // Please check its source code and implement error recovery when developing
        // production applications.
        sdmmc_card_t* card;
        esp_err_t ret = esp_vfs_fat_sdmmc_mount("/sdcard", &host, &slot_config, &mount_config, &card);
        
        if (ret != ESP_OK) {
            if (ret == ESP_FAIL) {
                ESP_LOGE(TAG, "Failed to mount filesystem. "
                         "If you want the card to be formatted, set format_if_mount_failed = true.");
            } else {
                ESP_LOGE(TAG, "Failed to initialize the card (%s). "
                         "Make sure SD card lines have pull-up resistors in place.", esp_err_to_name(ret));
            }
            return;
        }
        
        // Card has been initialized, print its properties
        sdmmc_card_print_info(stdout, card);
        ESP_LOGI(TAG, "SD card initialized");
    }
    
    Esp32Reader()
    {
        sdcard_init();
    }
   
    // Access methods inherited from WaveReader
};

#endif // FAUST_ESP32READER_H
/**************************  END  Esp32Reader.h **************************/
static Esp32Reader gReader;
#elif defined(DAISY)
static WaveReader gReader;
#elif defined(MEMORY_READER)
/************************** BEGIN MemoryReader.h ************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __MemoryReader__
#define __MemoryReader__


/*
 A 'MemoryReader' object can be used to prepare a set of sound resources in memory, to be used by SoundUI::addSoundfile.
 
 A Soundfile* object will have to be filled with a list of sound resources: the fLength, fOffset, fSampleRate and fBuffers fields 
 have to be completed with the appropriate values, and will be accessed in the DSP object while running.
 *
 */

// To adapt for a real case use

#define SOUND_CHAN      2
#define SOUND_LENGTH    4096
#define SOUND_SR        44100

struct MemoryReader : public SoundfileReader {
    
    MemoryReader()
    {}
    
    /**
     * Check the availability of a sound resource.
     *
     * @param path_name - the name of the file, or sound resource identified this way
     *
     * @return true if the sound resource is available, false otherwise.
     */
    virtual bool checkFile(const std::string& path_name) { return true; }
    
    /**
     * Get the channels and length values of the given sound resource.
     *
     * @param path_name - the name of the file, or sound resource identified this way
     * @param channels - the channels value to be filled with the sound resource number of channels
     * @param length - the length value to be filled with the sound resource length in frames
     *
     */
    virtual void getParamsFile(const std::string& path_name, int& channels, int& length)
    {
        channels = SOUND_CHAN;
        length = SOUND_LENGTH;
    }
    
    /**
     * Read one sound resource and fill the 'soundfile' structure accordingly
     *
     * @param path_name - the name of the file, or sound resource identified this way
     * @param part - the part number to be filled in the soundfile
     * @param offset - the offset value to be incremented with the actual sound resource length in frames
     * @param max_chan - the maximum number of mono channels to fill
     *
     */
    virtual void readFile(Soundfile* soundfile, const std::string& path_name, int part, int& offset, int max_chan)
    {
        soundfile->fLength[part] = SOUND_LENGTH;
        soundfile->fSR[part] = SOUND_SR;
        soundfile->fOffset[part] = offset;
        
        // Audio frames have to be written for each chan
        if (soundfile->fIsDouble) {
            for (int sample = 0; sample < SOUND_LENGTH; sample++) {
                for (int chan = 0; chan < SOUND_CHAN; chan++) {
                    static_cast<double**>(soundfile->fBuffers)[chan][offset + sample] = 0.f;
                }
            }
        } else {
            for (int sample = 0; sample < SOUND_LENGTH; sample++) {
                for (int chan = 0; chan < SOUND_CHAN; chan++) {
                    static_cast<float**>(soundfile->fBuffers)[chan][offset + sample] = 0.f;
                }
            }
        }
        
        // Update offset
        offset += SOUND_LENGTH;
    }
    
};

#endif
/**************************  END  MemoryReader.h **************************/
static MemoryReader gReader;
#else
/************************** BEGIN LibsndfileReader.h *********************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __LibsndfileReader__
#define __LibsndfileReader__

#ifdef SAMPLERATE
#include <samplerate.h>
#endif
#include <sndfile.h>
#include <string.h>
#include <assert.h>
#include <iostream>


struct VFLibsndfile {
    
    #define SIGNED_SIZEOF(x) ((int)sizeof(x))
    
    unsigned char* fBuffer;
    size_t fLength;
    size_t fOffset;
    SF_VIRTUAL_IO fVIO;
    
    VFLibsndfile(unsigned char* buffer, size_t length):fBuffer(buffer), fLength(length), fOffset(0)
    {
        fVIO.get_filelen = vfget_filelen;
        fVIO.seek = vfseek;
        fVIO.read = vfread;
        fVIO.write = vfwrite;
        fVIO.tell = vftell;
    }
    
    static sf_count_t vfget_filelen(void* user_data)
    {
        VFLibsndfile* vf = static_cast<VFLibsndfile*>(user_data);
        return vf->fLength;
    }
  
    static sf_count_t vfseek(sf_count_t offset, int whence, void* user_data)
    {
        VFLibsndfile* vf = static_cast<VFLibsndfile*>(user_data);
        switch (whence) {
            case SEEK_SET:
                vf->fOffset = offset;
                break;
                
            case SEEK_CUR:
                vf->fOffset = vf->fOffset + offset;
                break;
                
            case SEEK_END:
                vf->fOffset = vf->fLength + offset;
                break;
                
            default:
                break;
        };
        
        return vf->fOffset;
    }
    
    static sf_count_t vfread(void* ptr, sf_count_t count, void* user_data)
    {
        VFLibsndfile* vf = static_cast<VFLibsndfile*>(user_data);
        
        /*
         **	This will break badly for files over 2Gig in length, but
         **	is sufficient for testing.
         */
        if (vf->fOffset + count > vf->fLength) {
            count = vf->fLength - vf->fOffset;
        }
        
        memcpy(ptr, vf->fBuffer + vf->fOffset, count);
        vf->fOffset += count;
        
        return count;
    }
    
    static sf_count_t vfwrite(const void* ptr, sf_count_t count, void* user_data)
    {
        VFLibsndfile* vf = static_cast<VFLibsndfile*>(user_data);
        
        /*
         **	This will break badly for files over 2Gig in length, but
         **	is sufficient for testing.
         */
        if (vf->fOffset >= SIGNED_SIZEOF(vf->fBuffer)) {
            return 0;
        }
        
        if (vf->fOffset + count > SIGNED_SIZEOF(vf->fBuffer)) {
            count = sizeof (vf->fBuffer) - vf->fOffset;
        }
        
        memcpy(vf->fBuffer + vf->fOffset, ptr, (size_t)count);
        vf->fOffset += count;
        
        if (vf->fOffset > vf->fLength) {
            vf->fLength = vf->fOffset;
        }
        
        return count;
    }
    
    static sf_count_t vftell(void* user_data)
    {
        VFLibsndfile* vf = static_cast<VFLibsndfile*>(user_data);
        return vf->fOffset;
    }
 
};

struct LibsndfileReader : public SoundfileReader {
	
    LibsndfileReader() {}
	
    typedef sf_count_t (* sample_read)(SNDFILE* sndfile, void* buffer, sf_count_t frames);
	
    // Check file
    bool checkFile(const std::string& path_name)
    {
        SF_INFO snd_info;
        snd_info.format = 0;
        SNDFILE* snd_file = sf_open(path_name.c_str(), SFM_READ, &snd_info);
        return checkFileAux(snd_file, path_name);
    }
    
    bool checkFile(unsigned char* buffer, size_t length)
    {
        SF_INFO snd_info;
        snd_info.format = 0;
        VFLibsndfile vio(buffer, length);
        SNDFILE* snd_file = sf_open_virtual(&vio.fVIO, SFM_READ, &snd_info, &vio);
        return checkFileAux(snd_file, "virtual file");
    }
    
    bool checkFileAux(SNDFILE* snd_file, const std::string& path_name)
    {
        if (snd_file) {
            sf_close(snd_file);
            return true;
        } else {
            std::cerr << "ERROR : cannot open '" << path_name << "' (" << sf_strerror(NULL) << ")" << std::endl;
            return false;
        }
    }

    // Open the file and returns its length and channels
    void getParamsFile(const std::string& path_name, int& channels, int& length)
    {
        SF_INFO	snd_info;
        snd_info.format = 0;
        SNDFILE* snd_file = sf_open(path_name.c_str(), SFM_READ, &snd_info);
        getParamsFileAux(snd_file, snd_info, channels, length);
    }
    
    void getParamsFile(unsigned char* buffer, size_t size, int& channels, int& length)
    {
        SF_INFO	snd_info;
        snd_info.format = 0;
        VFLibsndfile vio(buffer, size);
        SNDFILE* snd_file = sf_open_virtual(&vio.fVIO, SFM_READ, &snd_info, &vio);
        getParamsFileAux(snd_file, snd_info, channels, length);
    }
    
    void getParamsFileAux(SNDFILE* snd_file, const SF_INFO& snd_info, int& channels, int& length)
    {
        assert(snd_file);
        channels = int(snd_info.channels);
    #ifdef SAMPLERATE
        length = (isResampling(snd_info.samplerate)) ? ((double(snd_info.frames) * double(fDriverSR) / double(snd_info.samplerate)) + BUFFER_SIZE) : int(snd_info.frames);
    #else
        length = int(snd_info.frames);
    #endif
        sf_close(snd_file);
    }
    
    // Read the file
    void readFile(Soundfile* soundfile, const std::string& path_name, int part, int& offset, int max_chan)
    {
        SF_INFO	snd_info;
        snd_info.format = 0;
        SNDFILE* snd_file = sf_open(path_name.c_str(), SFM_READ, &snd_info);
        readFileAux(soundfile, snd_file, snd_info, part, offset, max_chan);
    }
    
    void readFile(Soundfile* soundfile, unsigned char* buffer, size_t length, int part, int& offset, int max_chan)
    {
        SF_INFO	snd_info;
        snd_info.format = 0;
        VFLibsndfile vio(buffer, length);
        SNDFILE* snd_file = sf_open_virtual(&vio.fVIO, SFM_READ, &snd_info, &vio);
        readFileAux(soundfile, snd_file, snd_info, part, offset, max_chan);
    }
	
    // Will be called to fill all parts from 0 to MAX_SOUNDFILE_PARTS-1
    void readFileAux(Soundfile* soundfile, SNDFILE* snd_file, const SF_INFO& snd_info, int part, int& offset, int max_chan)
    {
        assert(snd_file);
        int channels = std::min<int>(max_chan, snd_info.channels);
    #ifdef SAMPLERATE
        if (isResampling(snd_info.samplerate)) {
            soundfile->fLength[part] = int(double(snd_info.frames) * double(fDriverSR) / double(snd_info.samplerate));
            soundfile->fSR[part] = fDriverSR;
        } else {
            soundfile->fLength[part] = int(snd_info.frames);
            soundfile->fSR[part] = snd_info.samplerate;
        }
    #else
        soundfile->fLength[part] = int(snd_info.frames);
        soundfile->fSR[part] = snd_info.samplerate;
    #endif
        soundfile->fOffset[part] = offset;
		
        // Read and fill snd_info.channels number of channels
        sf_count_t nbf;
        
        sample_read reader;
        void* buffer_in = nullptr;
        if (soundfile->fIsDouble) {
            buffer_in = static_cast<double*>(alloca(BUFFER_SIZE * sizeof(double) * snd_info.channels));
            reader = reinterpret_cast<sample_read>(sf_readf_double);
        } else {
            buffer_in = static_cast<float*>(alloca(BUFFER_SIZE * sizeof(float) * snd_info.channels));
            reader = reinterpret_cast<sample_read>(sf_readf_float);
        }
        
    #ifdef SAMPLERATE
        // Resampling
        SRC_STATE* resampler = nullptr;
        float* src_buffer_out = nullptr;
        float* src_buffer_in = nullptr;
        void* buffer_out = nullptr;
        if  (isResampling(snd_info.samplerate)) {
            int error;
            resampler = src_new(SRC_SINC_FASTEST, channels, &error);
            if (error != 0) {
                std::cerr << "ERROR : src_new " << src_strerror(error) << std::endl;
                throw -1;
            }
            if (soundfile->fIsDouble) {
                // Additional buffers for SRC resampling
                src_buffer_in = static_cast<float*>(alloca(BUFFER_SIZE * sizeof(float) * snd_info.channels));
                src_buffer_out = static_cast<float*>(alloca(BUFFER_SIZE * sizeof(float) * snd_info.channels));
                buffer_out = static_cast<double*>(alloca(BUFFER_SIZE * sizeof(double) * snd_info.channels));
            } else {
                buffer_out = static_cast<float*>(alloca(BUFFER_SIZE * sizeof(float) * snd_info.channels));
            }
        }
    #endif
        
        do {
            nbf = reader(snd_file, buffer_in, BUFFER_SIZE);
        #ifdef SAMPLERATE
            // Resampling
            if  (isResampling(snd_info.samplerate)) {
                int in_offset = 0;
                SRC_DATA src_data;
                src_data.src_ratio = double(fDriverSR)/double(snd_info.samplerate);
                if (soundfile->fIsDouble) {
                    for (int frame = 0; frame < (BUFFER_SIZE * snd_info.channels); frame++) {
                        src_buffer_in[frame] = float(static_cast<float*>(buffer_in)[frame]);
                    }
                }
                do {
                    if (soundfile->fIsDouble) {
                        src_data.data_in = src_buffer_in;
                        src_data.data_out = src_buffer_out;
                    } else {
                        src_data.data_in = static_cast<const float*>(buffer_in);
                        src_data.data_out = static_cast<float*>(buffer_out);
                    }
                    src_data.input_frames = nbf - in_offset;
                    src_data.output_frames = BUFFER_SIZE;
                    src_data.end_of_input = (nbf < BUFFER_SIZE);
                    int res = src_process(resampler, &src_data);
                    if (res != 0) {
                        std::cerr << "ERROR : src_process " << src_strerror(res) << std::endl;
                        throw -1;
                    }
                    if (soundfile->fIsDouble) {
                        for (int frame = 0; frame < (BUFFER_SIZE * snd_info.channels); frame++) {
                            static_cast<double*>(buffer_out)[frame] = double(src_buffer_out[frame]);
                        }
                    }
                    soundfile->copyToOut(src_data.output_frames_gen, channels, snd_info.channels, offset, buffer_out);
                    in_offset += src_data.input_frames_used;
                    // Update offset
                    offset += src_data.output_frames_gen;
                } while (in_offset < nbf);
            } else {
                soundfile->copyToOut(nbf, channels, snd_info.channels, offset, buffer_in);
                // Update offset
                offset += nbf;
            }
        #else
            soundfile->copyToOut(nbf, channels, snd_info.channels, offset, buffer_in);
            // Update offset
            offset += nbf;
        #endif
        } while (nbf == BUFFER_SIZE);
		
        sf_close(snd_file);
    #ifdef SAMPLERATE
        if (resampler) src_delete(resampler);
    #endif
    }

};

#endif
/**************************  END  LibsndfileReader.h **************************/
static LibsndfileReader gReader;
#endif

// To be used by DSP code if no SoundUI is used
static std::vector<std::string> path_name_list;
static Soundfile* defaultsound = nullptr;

class SoundUI : public SoundUIInterface
{
		
    protected:
    
        std::vector<std::string> fSoundfileDir;             // The soundfile directories
        std::map<std::string, Soundfile*> fSoundfileMap;    // Map to share loaded soundfiles
        SoundfileReader* fSoundReader;
        bool fIsDouble;

     public:
    
        /**
         * Create a soundfile loader which will typically use a concrete SoundfileReader like LibsndfileReader or JuceReader to load soundfiles.
         *
         * @param sound_directory - the base directory to look for files, which paths will be relative to this one
         * @param sample_rate - the audio driver SR which may be different from the file SR, to possibly resample files
         * @param reader - an alternative soundfile reader
         * @param is_double - whether Faust code has been compiled in -double mode and soundfile buffers have to be in double
         *
         * @return the soundfile loader.
         */
        SoundUI(const std::string& sound_directory = "", int sample_rate = -1, SoundfileReader* reader = nullptr, bool is_double = false)
        {
            fSoundfileDir.push_back(sound_directory);
            fSoundReader = (reader) ? reader : &gReader;
            fSoundReader->setSampleRate(sample_rate);
            fIsDouble = is_double;
            if (!defaultsound) defaultsound = gReader.createSoundfile(path_name_list, MAX_CHAN, is_double);
        }
    
        /**
         * Create a soundfile loader which will typically use a concrete SoundfileReader like LibsndfileReader or JuceReader to load soundfiles.
         *
         * @param sound_directories - a vector of base directories to look for files, which paths will be relative to these ones
         * @param sample_rate - the audio driver SR which may be different from the file SR, to possibly resample files
         * @param reader - an alternative soundfile reader
         * @param is_double - whether Faust code has been compiled in -double mode and soundfile buffers have to be in double
         *
         * @return the soundfile loader.
         */
        SoundUI(const std::vector<std::string>& sound_directories, int sample_rate = -1, SoundfileReader* reader = nullptr, bool is_double = false)
        :fSoundfileDir(sound_directories)
        {
            fSoundReader = (reader) ? reader : &gReader;
            fSoundReader->setSampleRate(sample_rate);
            fIsDouble = is_double;
            if (!defaultsound) defaultsound = gReader.createSoundfile(path_name_list, MAX_CHAN, is_double);
        }
    
        virtual ~SoundUI()
        {   
            // Delete all soundfiles
            for (const auto& it : fSoundfileMap) {
                delete it.second;
            }
        }

        // -- soundfiles
        virtual void addSoundfile(const char* label, const char* url, Soundfile** sf_zone)
        {
            const char* saved_url = url; // 'url' is consumed by parseMenuList2
            std::vector<std::string> file_name_list;
            
            bool menu = parseMenuList2(url, file_name_list, true);
            // If not a list, we have as single file
            if (!menu) { file_name_list.push_back(saved_url); }
            
            // Parse the possible list
            std::string saved_url_real = std::string(saved_url) + "_" + std::to_string(fIsDouble); // fIsDouble is used in the key
            if (fSoundfileMap.find(saved_url_real) == fSoundfileMap.end()) {
                // Check all files and get their complete path
                std::vector<std::string> path_name_list = fSoundReader->checkFiles(fSoundfileDir, file_name_list);
                // Read them and create the Soundfile
                Soundfile* sound_file = fSoundReader->createSoundfile(path_name_list, MAX_CHAN, fIsDouble);
                if (sound_file) {
                    fSoundfileMap[saved_url_real] = sound_file;
                } else {
                    // If failure, use 'defaultsound'
                    std::cerr << "addSoundfile : soundfile for " << saved_url << " cannot be created !" << std::endl;
                    *sf_zone = defaultsound;
                    return;
                }
            }
            
            // Get the soundfile
            *sf_zone = fSoundfileMap[saved_url_real];
        }
    
        /**
         * An OS dependant function to get the path of the running executable or plugin.
         * This will typically be used when creating a SoundUI soundfile loader, like new SoundUI(SoundUI::getBinaryPath());
         *
         * @return the running executable or plugin path.
         */
        static std::string getBinaryPath()
        {
            std::string bundle_path_str;
        #if defined(__APPLE__) && !defined(__VCVRACK__) && !defined(JUCE_32BIT) && !defined(JUCE_64BIT)
            CFURLRef bundle_ref = CFBundleCopyBundleURL(CFBundleGetMainBundle());
            if (!bundle_ref) { std::cerr << "getBinaryPath CFBundleCopyBundleURL error\n"; return ""; }
      
            UInt8 bundle_path[1024];
            if (CFURLGetFileSystemRepresentation(bundle_ref, true, bundle_path, 1024)) {
                bundle_path_str = std::string((char*)bundle_path);
            } else {
                std::cerr << "getBinaryPath CFURLGetFileSystemRepresentation error\n";
            }
        #endif
        #ifdef ANDROID_DRIVER
            bundle_path_str = "/data/data/__CURRENT_ANDROID_PACKAGE__/files";
        #endif
            return bundle_path_str;
        }
    
        /**
         * An OS dependant function to get the path of the running executable or plugin.
         * This will typically be used when creating a SoundUI soundfile loader, like new SoundUI(SoundUI::getBinaryPathFrom());
         *
         * @param path - entry point to start getting the path of the running executable or plugin.
         *
         * @return the running executable or plugin path.
         */
        static std::string getBinaryPathFrom(const std::string& path)
        {
            std::string bundle_path_str;
        #if defined(__APPLE__) && !defined(__VCVRACK__) && !defined(JUCE_32BIT) && !defined(JUCE_64BIT)
            CFBundleRef bundle = CFBundleGetBundleWithIdentifier(CFStringCreateWithCString(kCFAllocatorDefault, path.c_str(), CFStringGetSystemEncoding()));
            if (!bundle) { std::cerr << "getBinaryPathFrom CFBundleGetBundleWithIdentifier error '" << path << "'" << std::endl; return ""; }
         
            CFURLRef bundle_ref = CFBundleCopyBundleURL(bundle);
            if (!bundle_ref) { std::cerr << "getBinaryPathFrom CFBundleCopyBundleURL error\n"; return ""; }
            
            UInt8 bundle_path[1024];
            if (CFURLGetFileSystemRepresentation(bundle_ref, true, bundle_path, 1024)) {
                bundle_path_str = std::string((char*)bundle_path);
            } else {
                std::cerr << "getBinaryPathFrom CFURLGetFileSystemRepresentation error\n";
            }
        #endif
        #ifdef ANDROID_DRIVER
            bundle_path_str = "/data/data/__CURRENT_ANDROID_PACKAGE__/files";
        #endif
            return bundle_path_str;
        }
};

#endif
/**************************  END  SoundUI.h **************************/
#endif

#if defined(OSCCTRL)
/************************** BEGIN JuceOSCUI.h **************************
 FAUST Architecture File
 Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/
 
#ifndef __juce_osc__
#define __juce_osc__
 
#include "../JuceLibraryCode/JuceHeader.h"

/************************** BEGIN APIUI.h *****************************
FAUST Architecture File
Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
---------------------------------------------------------------------
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

EXCEPTION : As a special exception, you may create a larger work
that contains this FAUST architecture section and distribute
that work under terms of your choice, so long as this FAUST
architecture section is not modified.
************************************************************************/

#ifndef API_UI_H
#define API_UI_H

#include <sstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <map>


typedef unsigned int uint;

class APIUI : public PathBuilder, public Meta, public UI
{
    public:
        enum ItemType { kButton = 0, kCheckButton, kVSlider, kHSlider, kNumEntry, kHBargraph, kVBargraph };
        enum Type { kAcc = 0, kGyr = 1, kNoType };

    protected:

        enum Mapping { kLin = 0, kLog = 1, kExp = 2 };

        struct Item {
            std::string fPath;
            std::string fLabel;
            ValueConverter* fConversion;
            FAUSTFLOAT* fZone;
            FAUSTFLOAT fInit;
            FAUSTFLOAT fMin;
            FAUSTFLOAT fMax;
            FAUSTFLOAT fStep;
            ItemType fItemType;
        };
        std::vector<Item> fItems;

        std::vector<std::map<std::string, std::string> > fMetaData;
        std::vector<ZoneControl*> fAcc[3];
        std::vector<ZoneControl*> fGyr[3];

        // Screen color control
        // "...[screencolor:red]..." etc.
        bool fHasScreenControl;      // true if control screen color metadata
        ZoneReader* fRedReader;
        ZoneReader* fGreenReader;
        ZoneReader* fBlueReader;

        // Current values controlled by metadata
        std::string fCurrentUnit;
        int fCurrentScale;
        std::string fCurrentAcc;
        std::string fCurrentGyr;
        std::string fCurrentColor;
        std::string fCurrentTooltip;
        std::map<std::string, std::string> fCurrentMetadata;

        // Add a generic parameter
        virtual void addParameter(const char* label,
                                  FAUSTFLOAT* zone,
                                  FAUSTFLOAT init,
                                  FAUSTFLOAT min,
                                  FAUSTFLOAT max,
                                  FAUSTFLOAT step,
                                  ItemType type)
        {
            std::string path = buildPath(label);

            // handle scale metadata
            ValueConverter* converter = nullptr;
            switch (fCurrentScale) {
                case kLin:
                    converter = new LinearValueConverter(0, 1, min, max);
                    break;
                case kLog:
                    converter = new LogValueConverter(0, 1, min, max);
                    break;
                case kExp:
                    converter = new ExpValueConverter(0, 1, min, max);
                    break;
            }
            fCurrentScale = kLin;

            fItems.push_back({path, label, converter, zone, init, min, max, step, type });
       
            if (fCurrentAcc.size() > 0 && fCurrentGyr.size() > 0) {
                fprintf(stderr, "warning : 'acc' and 'gyr' metadata used for the same %s parameter !!\n", label);
            }

            // handle acc metadata "...[acc : <axe> <curve> <amin> <amid> <amax>]..."
            if (fCurrentAcc.size() > 0) {
                std::istringstream iss(fCurrentAcc);
                int axe, curve;
                double amin, amid, amax;
                iss >> axe >> curve >> amin >> amid >> amax;

                if ((0 <= axe) && (axe < 3) &&
                    (0 <= curve) && (curve < 4) &&
                    (amin < amax) && (amin <= amid) && (amid <= amax))
                {
                    fAcc[axe].push_back(new CurveZoneControl(zone, curve, amin, amid, amax, min, init, max));
                } else {
                    fprintf(stderr, "incorrect acc metadata : %s \n", fCurrentAcc.c_str());
                }
                fCurrentAcc = "";
            }

            // handle gyr metadata "...[gyr : <axe> <curve> <amin> <amid> <amax>]..."
            if (fCurrentGyr.size() > 0) {
                std::istringstream iss(fCurrentGyr);
                int axe, curve;
                double amin, amid, amax;
                iss >> axe >> curve >> amin >> amid >> amax;

                if ((0 <= axe) && (axe < 3) &&
                    (0 <= curve) && (curve < 4) &&
                    (amin < amax) && (amin <= amid) && (amid <= amax))
                {
                    fGyr[axe].push_back(new CurveZoneControl(zone, curve, amin, amid, amax, min, init, max));
                } else {
                    fprintf(stderr, "incorrect gyr metadata : %s \n", fCurrentGyr.c_str());
                }
                fCurrentGyr = "";
            }

            // handle screencolor metadata "...[screencolor:red|green|blue|white]..."
            if (fCurrentColor.size() > 0) {
                if ((fCurrentColor == "red") && (fRedReader == nullptr)) {
                    fRedReader = new ZoneReader(zone, min, max);
                    fHasScreenControl = true;
                } else if ((fCurrentColor == "green") && (fGreenReader == nullptr)) {
                    fGreenReader = new ZoneReader(zone, min, max);
                    fHasScreenControl = true;
                } else if ((fCurrentColor == "blue") && (fBlueReader == nullptr)) {
                    fBlueReader = new ZoneReader(zone, min, max);
                    fHasScreenControl = true;
                } else if ((fCurrentColor == "white") && (fRedReader == nullptr) && (fGreenReader == nullptr) && (fBlueReader == nullptr)) {
                    fRedReader = new ZoneReader(zone, min, max);
                    fGreenReader = new ZoneReader(zone, min, max);
                    fBlueReader = new ZoneReader(zone, min, max);
                    fHasScreenControl = true;
                } else {
                    fprintf(stderr, "incorrect screencolor metadata : %s \n", fCurrentColor.c_str());
                }
            }
            fCurrentColor = "";

            fMetaData.push_back(fCurrentMetadata);
            fCurrentMetadata.clear();
        }

        int getZoneIndex(std::vector<ZoneControl*>* table, int p, int val)
        {
            FAUSTFLOAT* zone = fItems[uint(p)].fZone;
            for (size_t i = 0; i < table[val].size(); i++) {
                if (zone == table[val][i]->getZone()) return int(i);
            }
            return -1;
        }

        void setConverter(std::vector<ZoneControl*>* table, int p, int val, int curve, double amin, double amid, double amax)
        {
            int id1 = getZoneIndex(table, p, 0);
            int id2 = getZoneIndex(table, p, 1);
            int id3 = getZoneIndex(table, p, 2);

            // Deactivates everywhere..
            if (id1 != -1) table[0][uint(id1)]->setActive(false);
            if (id2 != -1) table[1][uint(id2)]->setActive(false);
            if (id3 != -1) table[2][uint(id3)]->setActive(false);

            if (val == -1) { // Means: no more mapping...
                // So stay all deactivated...
            } else {
                int id4 = getZoneIndex(table, p, val);
                if (id4 != -1) {
                    // Reactivate the one we edit...
                  table[val][uint(id4)]->setMappingValues(curve, amin, amid, amax, fItems[uint(p)].fMin, fItems[uint(p)].fInit, fItems[uint(p)].fMax);
                  table[val][uint(id4)]->setActive(true);
                } else {
                    // Allocate a new CurveZoneControl which is 'active' by default
                    FAUSTFLOAT* zone = fItems[uint(p)].fZone;
                    table[val].push_back(new CurveZoneControl(zone, curve, amin, amid, amax, fItems[uint(p)].fMin, fItems[uint(p)].fInit, fItems[uint(p)].fMax));
                }
            }
        }

        void getConverter(std::vector<ZoneControl*>* table, int p, int& val, int& curve, double& amin, double& amid, double& amax)
        {
            int id1 = getZoneIndex(table, p, 0);
            int id2 = getZoneIndex(table, p, 1);
            int id3 = getZoneIndex(table, p, 2);

            if (id1 != -1) {
                val = 0;
                curve = table[val][uint(id1)]->getCurve();
                table[val][uint(id1)]->getMappingValues(amin, amid, amax);
            } else if (id2 != -1) {
                val = 1;
                curve = table[val][uint(id2)]->getCurve();
                table[val][uint(id2)]->getMappingValues(amin, amid, amax);
            } else if (id3 != -1) {
                val = 2;
                curve = table[val][uint(id3)]->getCurve();
                table[val][uint(id3)]->getMappingValues(amin, amid, amax);
            } else {
                val = -1; // No mapping
                curve = 0;
                amin = -100.;
                amid = 0.;
                amax = 100.;
            }
        }

    public:

        APIUI() : fHasScreenControl(false), fRedReader(nullptr), fGreenReader(nullptr), fBlueReader(nullptr), fCurrentScale(kLin)
        {}

        virtual ~APIUI()
        {
            for (const auto& it : fItems) delete it.fConversion;
            for (int i = 0; i < 3; i++) {
                for (const auto& it : fAcc[i]) delete it;
                for (const auto& it : fGyr[i]) delete it;
            }
            delete fRedReader;
            delete fGreenReader;
            delete fBlueReader;
        }

        // -- widget's layouts

        virtual void openTabBox(const char* label) { pushLabel(label); }
        virtual void openHorizontalBox(const char* label) { pushLabel(label); }
        virtual void openVerticalBox(const char* label) { pushLabel(label); }
        virtual void closeBox() { popLabel(); }

        // -- active widgets

        virtual void addButton(const char* label, FAUSTFLOAT* zone)
        {
            addParameter(label, zone, 0, 0, 1, 1, kButton);
        }

        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            addParameter(label, zone, 0, 0, 1, 1, kCheckButton);
        }

        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addParameter(label, zone, init, min, max, step, kVSlider);
        }

        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addParameter(label, zone, init, min, max, step, kHSlider);
        }

        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addParameter(label, zone, init, min, max, step, kNumEntry);
        }

        // -- passive widgets

        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            addParameter(label, zone, min, min, max, (max-min)/1000.0f, kHBargraph);
        }

        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            addParameter(label, zone, min, min, max, (max-min)/1000.0f, kVBargraph);
        }

        // -- soundfiles

        virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) {}

        // -- metadata declarations

        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {
            // Keep metadata
            fCurrentMetadata[key] = val;

            if (strcmp(key, "scale") == 0) {
                if (strcmp(val, "log") == 0) {
                    fCurrentScale = kLog;
                } else if (strcmp(val, "exp") == 0) {
                    fCurrentScale = kExp;
                } else {
                    fCurrentScale = kLin;
                }
            } else if (strcmp(key, "unit") == 0) {
                fCurrentUnit = val;
            } else if (strcmp(key, "acc") == 0) {
                fCurrentAcc = val;
            } else if (strcmp(key, "gyr") == 0) {
                fCurrentGyr = val;
            } else if (strcmp(key, "screencolor") == 0) {
                fCurrentColor = val; // val = "red", "green", "blue" or "white"
            } else if (strcmp(key, "tooltip") == 0) {
                fCurrentTooltip = val;
            }
        }

        virtual void declare(const char* key, const char* val)
        {}

        //-------------------------------------------------------------------------------
        // Simple API part
        //-------------------------------------------------------------------------------
        int getParamsCount() { return int(fItems.size()); }

        int getParamIndex(const char* path)
        {
            auto it1 = find_if(fItems.begin(), fItems.end(), [=](const Item& it) { return it.fPath == std::string(path); });
            if (it1 != fItems.end()) {
                return int(it1 - fItems.begin());
            }

            auto it2 = find_if(fItems.begin(), fItems.end(), [=](const Item& it) { return it.fLabel == std::string(path); });
            if (it2 != fItems.end()) {
                return int(it2 - fItems.begin());
            }

            return -1;
        }
        const char* getParamAddress(int p) { return fItems[uint(p)].fPath.c_str(); }
        const char* getParamLabel(int p) { return fItems[uint(p)].fLabel.c_str(); }
        std::map<const char*, const char*> getMetadata(int p)
        {
            std::map<const char*, const char*> res;
            std::map<std::string, std::string> metadata = fMetaData[uint(p)];
            for (const auto& it : metadata) {
                res[it.first.c_str()] = it.second.c_str();
            }
            return res;
        }

        const char* getMetadata(int p, const char* key)
        {
            return (fMetaData[uint(p)].find(key) != fMetaData[uint(p)].end()) ? fMetaData[uint(p)][key].c_str() : "";
        }
        FAUSTFLOAT getParamMin(int p) { return fItems[uint(p)].fMin; }
        FAUSTFLOAT getParamMax(int p) { return fItems[uint(p)].fMax; }
        FAUSTFLOAT getParamStep(int p) { return fItems[uint(p)].fStep; }
        FAUSTFLOAT getParamInit(int p) { return fItems[uint(p)].fInit; }

        FAUSTFLOAT* getParamZone(int p) { return fItems[uint(p)].fZone; }

        FAUSTFLOAT getParamValue(int p) { return *fItems[uint(p)].fZone; }
        FAUSTFLOAT getParamValue(const char* path)
        {
            int index = getParamIndex(path);
            return (index >= 0) ? getParamValue(index) : FAUSTFLOAT(0);
        }

        void setParamValue(int p, FAUSTFLOAT v) { *fItems[uint(p)].fZone = v; }
        void setParamValue(const char* path, FAUSTFLOAT v)
        {
            int index = getParamIndex(path);
            if (index >= 0) {
                setParamValue(index, v);
            } else {
                fprintf(stderr, "setParamValue : '%s' not found\n", (path == nullptr ? "NULL" : path));
            }
        }

        double getParamRatio(int p) { return fItems[uint(p)].fConversion->faust2ui(*fItems[uint(p)].fZone); }
        void setParamRatio(int p, double r) { *fItems[uint(p)].fZone = FAUSTFLOAT(fItems[uint(p)].fConversion->ui2faust(r)); }

        double value2ratio(int p, double r)    { return fItems[uint(p)].fConversion->faust2ui(r); }
        double ratio2value(int p, double r)    { return fItems[uint(p)].fConversion->ui2faust(r); }

        /**
         * Return the control type (kAcc, kGyr, or -1) for a given parameter.
         *
         * @param p - the UI parameter index
         *
         * @return the type
         */
        Type getParamType(int p)
        {
            if (p >= 0) {
                if (getZoneIndex(fAcc, p, 0) != -1
                    || getZoneIndex(fAcc, p, 1) != -1
                    || getZoneIndex(fAcc, p, 2) != -1) {
                    return kAcc;
                } else if (getZoneIndex(fGyr, p, 0) != -1
                           || getZoneIndex(fGyr, p, 1) != -1
                           || getZoneIndex(fGyr, p, 2) != -1) {
                    return kGyr;
                }
            }
            return kNoType;
        }

        /**
         * Return the Item type (kButton = 0, kCheckButton, kVSlider, kHSlider, kNumEntry, kHBargraph, kVBargraph) for a given parameter.
         *
         * @param p - the UI parameter index
         *
         * @return the Item type
         */
        ItemType getParamItemType(int p)
        {
            return fItems[uint(p)].fItemType;
        }

        /**
         * Set a new value coming from an accelerometer, propagate it to all relevant FAUSTFLOAT* zones.
         *
         * @param acc - 0 for X accelerometer, 1 for Y accelerometer, 2 for Z accelerometer
         * @param value - the new value
         *
         */
        void propagateAcc(int acc, double value)
        {
            for (size_t i = 0; i < fAcc[acc].size(); i++) {
                fAcc[acc][i]->update(value);
            }
        }

        /**
         * Used to edit accelerometer curves and mapping. Set curve and related mapping for a given UI parameter.
         *
         * @param p - the UI parameter index
         * @param acc - 0 for X accelerometer, 1 for Y accelerometer, 2 for Z accelerometer (-1 means "no mapping")
         * @param curve - between 0 and 3
         * @param amin - mapping 'min' point
         * @param amid - mapping 'middle' point
         * @param amax - mapping 'max' point
         *
         */
        void setAccConverter(int p, int acc, int curve, double amin, double amid, double amax)
        {
            setConverter(fAcc, p, acc, curve, amin, amid, amax);
        }

        /**
         * Used to edit gyroscope curves and mapping. Set curve and related mapping for a given UI parameter.
         *
         * @param p - the UI parameter index
         * @param acc - 0 for X gyroscope, 1 for Y gyroscope, 2 for Z gyroscope (-1 means "no mapping")
         * @param curve - between 0 and 3
         * @param amin - mapping 'min' point
         * @param amid - mapping 'middle' point
         * @param amax - mapping 'max' point
         *
         */
        void setGyrConverter(int p, int gyr, int curve, double amin, double amid, double amax)
        {
            setConverter(fGyr, p, gyr, curve, amin, amid, amax);
        }

        /**
         * Used to edit accelerometer curves and mapping. Get curve and related mapping for a given UI parameter.
         *
         * @param p - the UI parameter index
         * @param acc - the acc value to be retrieved (-1 means "no mapping")
         * @param curve - the curve value to be retrieved
         * @param amin - the amin value to be retrieved
         * @param amid - the amid value to be retrieved
         * @param amax - the amax value to be retrieved
         *
         */
        void getAccConverter(int p, int& acc, int& curve, double& amin, double& amid, double& amax)
        {
            getConverter(fAcc, p, acc, curve, amin, amid, amax);
        }

        /**
         * Used to edit gyroscope curves and mapping. Get curve and related mapping for a given UI parameter.
         *
         * @param p - the UI parameter index
         * @param gyr - the gyr value to be retrieved (-1 means "no mapping")
         * @param curve - the curve value to be retrieved
         * @param amin - the amin value to be retrieved
         * @param amid - the amid value to be retrieved
         * @param amax - the amax value to be retrieved
         *
         */
        void getGyrConverter(int p, int& gyr, int& curve, double& amin, double& amid, double& amax)
        {
            getConverter(fGyr, p, gyr, curve, amin, amid, amax);
        }

        /**
         * Set a new value coming from an gyroscope, propagate it to all relevant FAUSTFLOAT* zones.
         *
         * @param gyr - 0 for X gyroscope, 1 for Y gyroscope, 2 for Z gyroscope
         * @param value - the new value
         *
         */
        void propagateGyr(int gyr, double value)
        {
            for (size_t i = 0; i < fGyr[gyr].size(); i++) {
                fGyr[gyr][i]->update(value);
            }
        }

        /**
         * Get the number of FAUSTFLOAT* zones controlled with the accelerometer.
         *
         * @param acc - 0 for X accelerometer, 1 for Y accelerometer, 2 for Z accelerometer
         * @return the number of zones
         *
         */
        int getAccCount(int acc)
        {
            return (acc >= 0 && acc < 3) ? int(fAcc[acc].size()) : 0;
        }

        /**
         * Get the number of FAUSTFLOAT* zones controlled with the gyroscope.
         *
         * @param gyr - 0 for X gyroscope, 1 for Y gyroscope, 2 for Z gyroscope
         * @param the number of zones
         *
         */
        int getGyrCount(int gyr)
        {
            return (gyr >= 0 && gyr < 3) ? int(fGyr[gyr].size()) : 0;
        }

        // getScreenColor() : -1 means no screen color control (no screencolor metadata found)
        // otherwise return 0x00RRGGBB a ready to use color
        int getScreenColor()
        {
            if (fHasScreenControl) {
                int r = (fRedReader) ? fRedReader->getValue() : 0;
                int g = (fGreenReader) ? fGreenReader->getValue() : 0;
                int b = (fBlueReader) ? fBlueReader->getValue() : 0;
                return (r<<16) | (g<<8) | b;
            } else {
                return -1;
            }
        }

};

#endif
/**************************  END  APIUI.h **************************/

class oscItem : public uiItem {
    
    protected:
        
        juce::OSCSender* fSender;
        juce::String fPath;
        
    public:
        
        oscItem(juce::OSCSender* sender, GUI* ui, const juce::String& path, FAUSTFLOAT* zone)
        :uiItem(ui, zone), fSender(sender), fPath(path) {}
        virtual ~oscItem()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            fSender->send(fPath, float(v));
        }
    
};

class JuceOSCUI : private juce::OSCReceiver, private juce::OSCReceiver::Listener<juce::OSCReceiver::RealtimeCallback>, public GUI {
    
    private:
        
        juce::OSCSender fSender;
        juce::String fIP;
        int fInputPort, fOutputPort;
        APIUI fAPIUI;
        juce::Array<oscItem*> fOSCItems;  // Pointers are kept and desallocated by the GUI class
        
    public:
        
        JuceOSCUI(const std::string& ip, int in_port, int out_port)
        :fIP(ip), fInputPort(in_port), fOutputPort(out_port)
        {}
        
        virtual ~JuceOSCUI()
        {}
        
        void oscMessageReceived(const juce::OSCMessage& message) override
        {
            juce::String address = message.getAddressPattern().toString();
            
            for (int i = 0; i < message.size(); ++i) {
                if (message[i].isFloat32()) {
                    fAPIUI.setParamValue(fAPIUI.getParamIndex(address.toStdString().c_str()), FAUSTFLOAT(message[i].getFloat32()));
                    // "get" message with correct address
                } else if (message[i].isString()
                           && message[i].getString().equalsIgnoreCase("get")
                           && juce::String(fAPIUI.getParamAddress(0)).startsWith(address)) {
                    for (int p = 0; p < fAPIUI.getParamsCount(); ++p) {
                        fSender.send(fAPIUI.getParamAddress(p), float(fAPIUI.getParamValue(p)), float(fAPIUI.getParamMin(p)), float(fAPIUI.getParamMax(p)));
                    }
                    // "hello" message
                } else if (message[i].isString()
                           && address.equalsIgnoreCase("/*")
                           && message[i].getString().equalsIgnoreCase("hello")) {
                    juce::String path = fAPIUI.getParamAddress(0);
                    int pos1 = path.indexOfChar('/');
                    int pos2 = path.indexOfChar(pos1 + 1, '/');
                    fSender.send(path.substring(pos1, pos2), fIP, fInputPort, fOutputPort);
                }
            }
        }
        
        bool run() override
        {
            // Keep all zones for update when OSC messages are received
            if (fOSCItems.size() == 0) {
                for (int p = 0; p < fAPIUI.getParamsCount(); ++p) {
                    fOSCItems.add(new oscItem(&fSender, this, fAPIUI.getParamAddress(p), fAPIUI.getParamZone(p)));
                }
            }
            
            if (!fSender.connect(fIP, fOutputPort)) {
                std::cerr << "Error: could not connect to UDP port " << fInputPort << std::endl;
                return false;
            }
            
            if (!connect(fInputPort)) {
                std::cerr << "Error: could not connect to UDP port " << fOutputPort << std::endl;
                return false;
            }
            addListener(this);
            return true;
        }
        
        void stop() override
        {
            fSender.disconnect();
            disconnect();
            removeListener(this);
        }
        
        // -- widget's layouts
        
        void openTabBox(const char* label) override { fAPIUI.openTabBox(label); }
        void openHorizontalBox(const char* label) override { fAPIUI.openHorizontalBox(label); }
        void openVerticalBox(const char* label) override { fAPIUI.openVerticalBox(label); }
        void closeBox() override { fAPIUI.closeBox(); }
        
        // -- active widgets
        
        void addButton(const char* label, FAUSTFLOAT* zone) override { fAPIUI.addButton(label, zone); }
        void addCheckButton(const char* label, FAUSTFLOAT* zone) override { fAPIUI.addCheckButton(label, zone); }
        void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) override
        { fAPIUI.addVerticalSlider(label, zone, init, min, max, step); }
        void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) override
        { fAPIUI.addHorizontalSlider(label, zone, init, min, max, step); }
        void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) override
        { fAPIUI.addNumEntry(label, zone, init, min, max, step); }
        
        // -- passive widgets
        
        void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) override
        { fAPIUI.addHorizontalBargraph(label, zone, min, max); }
        void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) override
        { fAPIUI.addVerticalBargraph(label, zone, min, max); }
        
        // -- metadata declarations
        
        void declare(FAUSTFLOAT* zone, const char* key, const char* val) override { fAPIUI.declare(zone, key, val); }
    
};

#endif // __juce_osc__

/**************************  END  JuceOSCUI.h **************************/
#endif

#if defined(MIDICTRL)
/************************** BEGIN juce-midi.h ****************************
FAUST Architecture File
Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
---------------------------------------------------------------------
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

EXCEPTION : As a special exception, you may create a larger work
that contains this FAUST architecture section and distribute
that work under terms of your choice, so long as this FAUST
architecture section is not modified.
***************************************************************************/

#ifndef __juce_midi__
#define __juce_midi__
 

class MapUI;

/**
 *  MIDI input/output handling using JUCE framework: https://juce.com
 */
class juce_midi_handler : public midi_handler {
    
    protected:
    
        juce::MidiBuffer fOutputBuffer;
        juce::CriticalSection fMutex;
    
        void decodeMessage(const juce::MidiMessage& message)
        {
            const juce::uint8* data = message.getRawData();
            int channel = message.getChannel() - 1; // which MIDI channel, 0-15
            double time = message.getTimeStamp();
            
            if (message.isNoteOff()) {
                handleKeyOff(time, channel, data[1], data[2]);
            } else if (message.isNoteOn()) {
                handleKeyOn(time, channel, data[1], data[2]);
            } else if (message.isAftertouch()) {
                handlePolyAfterTouch(time, channel, data[1], data[2]);
            } else if (message.isController()) {
                handleCtrlChange(time, channel, data[1], data[2]);
            } else if (message.isProgramChange()) {
                handleProgChange(time, channel, data[1]);
            } else if (message.isChannelPressure()) {
                handleAfterTouch(time, channel, data[1]);
            } else if (message.isPitchWheel()) {
                handlePitchWheel(time, channel, data[1], data[2]);
            } else if (message.isMidiClock()) {
                handleClock(time);
            // We can consider start and continue as identical messages.
            } else if (message.isMidiStart() || message.isMidiContinue()) {
                handleStart(time);
            } else if (message.isMidiStop()) {
                handleStop(time);
            } else if (message.isSysEx()) {
                std::vector<unsigned char> sysex(data, data + message.getRawDataSize());
                handleSysex(time, sysex);
            } else {
                std::cerr << "Unused MIDI message" << std::endl;
            }
        }
    
    public:
    
        juce_midi_handler():midi_handler("JUCE")
        {}
    
        virtual ~juce_midi_handler() {}
    
        // Used with MidiBuffer (containing several messages)
        void encodeBuffer(juce::MidiBuffer& buffer)
        {
            const juce::ScopedTryLock lock(fMutex);
            if (lock.isLocked()) {
                buffer.swapWith(fOutputBuffer);
                fOutputBuffer.clear();
            } else {
                std::cerr << "encodeBuffer fails..." << std::endl;
            }
        }
        
        void decodeBuffer(juce::MidiBuffer& buffer)
        {
            juce::MidiMessage msg;
            int ignore;
            for (juce::MidiBuffer::Iterator it(buffer); it.getNextEvent(msg, ignore);) {
                decodeMessage(msg);
            }
            buffer.clear();
        }
    
        // MIDI output API
        MapUI* keyOn(int channel, int pitch, int velocity)
        {
            fOutputBuffer.addEvent(juce::MidiMessage::noteOn(channel + 1, pitch, juce::uint8(velocity)), 0);
            return nullptr;
        }
        
        void keyOff(int channel, int pitch, int velocity)
        {
            fOutputBuffer.addEvent(juce::MidiMessage::noteOff(channel + 1, pitch, juce::uint8(velocity)), 0);
        }
        
        void ctrlChange(int channel, int ctrl, int val)
        {
            fOutputBuffer.addEvent(juce::MidiMessage::controllerEvent(channel + 1, ctrl, juce::uint8(val)), 0);
        }
        
        void chanPress(int channel, int press)
        {
            fOutputBuffer.addEvent(juce::MidiMessage::channelPressureChange(channel + 1, press), 0);
        }
        
        void progChange(int channel, int pgm)
        {
            fOutputBuffer.addEvent(juce::MidiMessage::programChange(channel + 1, pgm), 0);
        }
        
        void keyPress(int channel, int pitch, int press)
        {
            fOutputBuffer.addEvent(juce::MidiMessage::aftertouchChange(channel + 1, pitch, press), 0);
        }
        
        void pitchWheel(int channel, int wheel)
        {
            fOutputBuffer.addEvent(juce::MidiMessage::pitchWheel(channel + 1, range(0, 16383, wheel)), 0);
        }
        
        void ctrlChange14bits(int channel, int ctrl, int value)
        {
            // TODO
        }
        
        void startSync(double date)
        {
            fOutputBuffer.addEvent(juce::MidiMessage::midiStart(), 0);
        }
        
        void stopSync(double date)
        {
            fOutputBuffer.addEvent(juce::MidiMessage::midiStop(), 0);
        }
        
        void clock(double date)
        {
            fOutputBuffer.addEvent(juce::MidiMessage::midiClock(), 0);
        }
    
        void sysEx(double date, std::vector<unsigned char>& message)
        {
            fOutputBuffer.addEvent(juce::MidiMessage(message.data(), (int)message.size()), 0);
        }

};

class juce_midi : public juce_midi_handler, public juce::MidiInputCallback {

    private:
    
        std::unique_ptr<juce::MidiInput> fMidiIn;
        std::unique_ptr<juce::MidiOutput> fMidiOut;
    
        void handleIncomingMidiMessage(juce::MidiInput*, const juce::MidiMessage& message)
        {
            decodeMessage(message);
        }
    
    public:
    
        juce_midi():juce_midi_handler()
        {}
    
        virtual ~juce_midi()
        {
            stopMidi();
        }
        
        bool startMidi()
        {
            if ((fMidiIn = juce::MidiInput::openDevice(juce::MidiInput::getDefaultDeviceIndex(), this)) == nullptr) {
                return false;
            }
            if ((fMidiOut = juce::MidiOutput::openDevice(juce::MidiOutput::getDefaultDeviceIndex())) == nullptr) {
                return false;
            }
            fMidiIn->start();
            return true;
        }
        
        void stopMidi()
        { 
            fMidiIn->stop();
        }
    
        // MIDI output API
        MapUI* keyOn(int channel, int pitch, int velocity)
        {
            fMidiOut->sendMessageNow(juce::MidiMessage::noteOn(channel + 1, pitch, juce::uint8(velocity)));
            return nullptr;
        }
        
        void keyOff(int channel, int pitch, int velocity) 
        {
            fMidiOut->sendMessageNow(juce::MidiMessage::noteOff(channel + 1, pitch, juce::uint8(velocity)));
        }
        
        void ctrlChange(int channel, int ctrl, int val) 
        {
            fMidiOut->sendMessageNow(juce::MidiMessage::controllerEvent(channel + 1, ctrl, juce::uint8(val)));
        }
        
        void chanPress(int channel, int press) 
        {
            fMidiOut->sendMessageNow(juce::MidiMessage::channelPressureChange(channel + 1, press));
        }
        
        void progChange(int channel, int pgm) 
        {
            fMidiOut->sendMessageNow(juce::MidiMessage::programChange(channel + 1, pgm));
        }
          
        void keyPress(int channel, int pitch, int press) 
        {
            fMidiOut->sendMessageNow(juce::MidiMessage::aftertouchChange(channel + 1, pitch, press));
        }
   
        void pitchWheel(int channel, int wheel) 
        {
            fMidiOut->sendMessageNow(juce::MidiMessage::pitchWheel(channel + 1, range(0, 16383, wheel)));
        }
        
        void ctrlChange14bits(int channel, int ctrl, int value)
        {
            // TODO
        }
    
        void startSync(double date) 
        {
            fMidiOut->sendMessageNow(juce::MidiMessage::midiStart());
        }
       
        void stopSync(double date) 
        {
            fMidiOut->sendMessageNow(juce::MidiMessage::midiStop());
        }
        
        void clock(double date) 
        {
            fMidiOut->sendMessageNow(juce::MidiMessage::midiClock());
        }
    
        void sysEx(double date, std::vector<unsigned char>& message)
        {
            fMidiOut->sendMessageNow(juce::MidiMessage(message.data(), (int)message.size()));
        }
    
};

#endif // __juce_midi__

/**************************  END  juce-midi.h **************************/
/************************** BEGIN timed-base_dsp.h *****************************
FAUST Architecture File
Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
---------------------------------------------------------------------
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

EXCEPTION : As a special exception, you may create a larger work
that contains this FAUST architecture section and distribute
that work under terms of your choice, so long as this FAUST
architecture section is not modified.
***************************************************************************/

#ifndef __timed_dsp__
#define __timed_dsp__

#include <set>
#include <float.h>
#include <assert.h>


namespace {
    
#if __APPLE__
#if TARGET_OS_IPHONE
    //inline double GetCurrentTimeInUsec() { return double(CAHostTimeBase::GetCurrentTimeInNanos()) / 1000.; }
    // TODO
    inline double GetCurrentTimeInUsec() { return 0.0; }
#else
    #include <CoreAudio/HostTime.h>
    inline double GetCurrentTimeInUsec() { return double(AudioConvertHostTimeToNanos(AudioGetCurrentHostTime())) / 1000.; }
#endif
#endif

#if __linux__
#include <sys/time.h>
inline double GetCurrentTimeInUsec() 
{
    struct timeval tv;
    (void)gettimeofday(&tv, (struct timezone *)NULL);
    return double((tv.tv_sec * 1000000) + tv.tv_usec);
}
#endif

#if _WIN32
#include <windows.h>
inline double GetCurrentTimeInUsec(void)
{
    LARGE_INTEGER time;
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&time);
    return double(time.QuadPart) / double(frequency.QuadPart) * 1000000.0;
}
#endif
    
}

/**
 * ZoneUI : this class collect zones in a set.
 */

struct ZoneUI : public GenericUI
{
    
    std::set<FAUSTFLOAT*> fZoneSet;
    
    ZoneUI():GenericUI() {}
    virtual ~ZoneUI() {}
    
    void insertZone(FAUSTFLOAT* zone) 
    { 
        if (GUI::gTimedZoneMap.find(zone) != GUI::gTimedZoneMap.end()) {
            fZoneSet.insert(zone);
        } 
    }
    
    // -- active widgets
    void addButton(const char* label, FAUSTFLOAT* zone)
    {
        insertZone(zone);
    }
    void addCheckButton(const char* label, FAUSTFLOAT* zone)
    {
        insertZone(zone);
    }
    void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
    {
        insertZone(zone);
    }
    void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
    {
        insertZone(zone);
    }
    void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
    {
        insertZone(zone);
    }
    
    // -- passive widgets
    void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
    {
        insertZone(zone);
    }
    void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
    {
        insertZone(zone);
    }
  
};

/**
 * Timed signal processor that allows to handle the decorated DSP by 'slices'
 * that is, calling the 'compute' method several times and changing control
 * parameters between slices.
 */

class timed_dsp : public decorator_dsp {

    protected:
        
        double fDateUsec;       // Compute call date in usec
        double fOffsetUsec;     // Compute call offset in usec
        bool fFirstCallback;
        ZoneUI fZoneUI;
    
        FAUSTFLOAT** fInputsSlice;
        FAUSTFLOAT** fOutputsSlice;
    
        void computeSlice(int offset, int slice, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) 
        {
            if (slice > 0) {
                for (int chan = 0; chan < fDSP->getNumInputs(); chan++) {
                    fInputsSlice[chan] = &(inputs[chan][offset]);
                }
                for (int chan = 0; chan < fDSP->getNumOutputs(); chan++) {
                    fOutputsSlice[chan] = &(outputs[chan][offset]);
                }
                fDSP->compute(slice, fInputsSlice, fOutputsSlice);
            } 
        }
        
        double convertUsecToSample(double usec)
        {
            return std::max<double>(0., (double(getSampleRate()) * (usec - fDateUsec)) / 1000000.);
        }
        
        ztimedmap::iterator getNextControl(DatedControl& res)
        {
            DatedControl date1(DBL_MAX, 0);
            ztimedmap::iterator it1, it2 = GUI::gTimedZoneMap.end();
            std::set<FAUSTFLOAT*>::iterator it3;
              
            // Find date of next audio slice to compute
            for (it3 = fZoneUI.fZoneSet.begin(); it3 != fZoneUI.fZoneSet.end(); it3++) {
                // If value list is not empty, get the date and keep the minimal one
                it1 = GUI::gTimedZoneMap.find(*it3);
                if (it1 != GUI::gTimedZoneMap.end()) { // Check if zone still in global GUI::gTimedZoneMap (since MidiUI may have been desallocated)
                    DatedControl date2;
                    if (ringbuffer_peek((*it1).second, (char*)&date2, sizeof(DatedControl)) == sizeof(DatedControl) 
                        && date2.fDate < date1.fDate) {
                        it2 = it1;
                        date1 = date2;
                    }
                }
            }
            
            res = date1;
            return it2;
        }
        
        virtual void computeAux(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs, bool convert_ts)
        {
            int slice, offset = 0;
            ztimedmap::iterator it;
            DatedControl next_control;
             
            // Do audio computation "slice" by "slice"
            while ((it = getNextControl(next_control)) != GUI::gTimedZoneMap.end()) {
                
                // If needed, convert next_control in samples from begining of the buffer, possible moving to 0 (if negative)
                if (convert_ts) {
                    next_control.fDate = convertUsecToSample(next_control.fDate);
                }
                     
                // Compute audio slice
                slice = int(next_control.fDate) - offset;
                computeSlice(offset, slice, inputs, outputs);
                offset += slice;
               
                // Update control
                ringbuffer_t* control_values = (*it).second;
                *((*it).first) = next_control.fValue;
                
                // Move ringbuffer pointer
                ringbuffer_read_advance(control_values, sizeof(DatedControl));
            } 
            
            // Compute last audio slice
            slice = count - offset;
            computeSlice(offset, slice, inputs, outputs);
        }

    public:

        timed_dsp(base_dsp* base_dsp):decorator_dsp(base_dsp), fDateUsec(0), fOffsetUsec(0), fFirstCallback(true)
        {
            fInputsSlice = new FAUSTFLOAT*[base_dsp->getNumInputs()];
            fOutputsSlice = new FAUSTFLOAT*[base_dsp->getNumOutputs()];
        }
        virtual ~timed_dsp() 
        {
            delete [] fInputsSlice;
            delete [] fOutputsSlice;
        }
        
        virtual void init(int sample_rate)
        {
            fDSP->init(sample_rate);
        }
        
        virtual void buildUserInterface(UI* ui_interface)   
        { 
            fDSP->buildUserInterface(ui_interface); 
            // Only keep zones that are in GUI::gTimedZoneMap
            fDSP->buildUserInterface(&fZoneUI);
        }
    
        virtual timed_dsp* clone()
        {
            return new timed_dsp(fDSP->clone());
        }
    
        // Default method take a timestamp at 'compute' call time
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            compute(::GetCurrentTimeInUsec(), count, inputs, outputs);
        }    
        
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            if (date_usec == -1) {
                // Timestamp is expressed in frames
                computeAux(count, inputs, outputs, false);
            } else {
                // Save the timestamp offset in the first callback
                if (fFirstCallback) {
                    fFirstCallback = false;
                    double current_date_usec = ::GetCurrentTimeInUsec();
                    fDateUsec = current_date_usec;
                    fOffsetUsec = current_date_usec - date_usec;
                }
                
                // RtMidi mode: timestamp must be converted in frames
                computeAux(count, inputs, outputs, true);
                
                // Keep call date 
                fDateUsec = date_usec + fOffsetUsec;
            }
        }
        
};

#endif
/************************** END timed-base_dsp.h **************************/
#endif

#if defined(POLY2)
#include "effect.h"
#endif 

// we require macro declarations
#define FAUST_UIMACROS

// but we will ignore most of them
#define FAUST_ADDBUTTON(l,f)
#define FAUST_ADDCHECKBOX(l,f)
#define FAUST_ADDSOUNDFILE(l,s)
#define FAUST_ADDVERTICALSLIDER(l,f,i,a,b,s)
#define FAUST_ADDHORIZONTALSLIDER(l,f,i,a,b,s)
#define FAUST_ADDNUMENTRY(l,f,i,a,b,s)
#define FAUST_ADDVERTICALBARGRAPH(l,f,a,b)
#define FAUST_ADDHORIZONTALBARGRAPH(l,f,a,b)


#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

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

class mydsp : public base_dsp {
	
 public:
	
	int fSampleRate;
	float fConst0;
	FAUSTFLOAT fHslider0;
	int IOTA0;
	float fConst6;
	float fConst9;
	float fConst11;
	float fConst12;
	float fConst13;
	float fConst14;
	float fConst15;
	float fRec6[3];
	float fRec5[3];
	float fRec4[3];
	float fRec3[3];
	float fVec0[2];
	float fRec2[2];
	float fRec1[32768];
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	float fRec0[2];
	float fConst16;
	float fRec7[2];
	float fConst17;
	float fConst23;
	float fConst25;
	float fConst26;
	float fConst27;
	float fConst28;
	float fConst29;
	float fRec15[3];
	float fRec14[3];
	float fRec13[3];
	float fRec12[3];
	float fVec1[2];
	float fRec11[2];
	float fRec10[32768];
	float fRec9[2];
	float fConst30;
	float fRec16[2];
	float fConst31;
	float fConst37;
	float fConst39;
	float fConst40;
	float fConst41;
	float fConst42;
	float fConst43;
	float fRec24[3];
	float fRec23[3];
	float fRec22[3];
	float fRec21[3];
	float fVec2[2];
	float fRec20[2];
	float fRec19[32768];
	float fRec18[2];
	float fConst44;
	float fRec25[2];
	float fConst45;
	float fConst51;
	float fConst53;
	float fConst54;
	float fConst55;
	float fConst56;
	float fConst57;
	float fRec33[3];
	float fRec32[3];
	float fRec31[3];
	float fRec30[3];
	float fVec3[2];
	float fRec29[2];
	float fRec28[32768];
	float fRec27[2];
	float fConst58;
	float fRec34[2];
	float fConst59;
	float fConst65;
	float fConst67;
	float fConst68;
	float fConst69;
	float fConst70;
	float fConst71;
	float fRec42[3];
	float fRec41[3];
	float fRec40[3];
	float fRec39[3];
	float fVec4[2];
	float fRec38[2];
	float fRec37[32768];
	float fRec36[2];
	float fConst72;
	float fRec43[2];
	float fConst73;
	float fConst79;
	float fConst81;
	float fConst82;
	float fConst83;
	float fConst84;
	float fConst85;
	float fRec51[3];
	float fRec50[3];
	float fRec49[3];
	float fRec48[3];
	float fVec5[2];
	float fRec47[2];
	float fRec46[32768];
	float fRec45[2];
	float fConst86;
	float fRec52[2];
	float fConst87;
	float fConst93;
	float fConst95;
	float fConst96;
	float fConst97;
	float fConst98;
	float fConst99;
	float fRec60[3];
	float fRec59[3];
	float fRec58[3];
	float fRec57[3];
	float fVec6[2];
	float fRec56[2];
	float fRec55[32768];
	float fRec54[2];
	float fConst100;
	float fRec61[2];
	float fConst101;
	float fConst107;
	float fConst109;
	float fConst110;
	float fConst111;
	float fConst112;
	float fConst113;
	float fRec69[3];
	float fRec68[3];
	float fRec67[3];
	float fRec66[3];
	float fVec7[2];
	float fRec65[2];
	float fRec64[32768];
	float fRec63[2];
	float fConst114;
	float fRec70[2];
	float fConst115;
	float fConst121;
	float fConst123;
	float fConst124;
	float fConst125;
	float fConst126;
	float fConst127;
	float fRec78[3];
	float fRec77[3];
	float fRec76[3];
	float fRec75[3];
	float fVec8[2];
	float fRec74[2];
	float fRec73[32768];
	float fRec72[2];
	float fConst128;
	float fRec79[2];
	float fConst129;
	float fConst135;
	float fConst137;
	float fConst138;
	float fConst139;
	float fConst140;
	float fConst141;
	float fRec87[3];
	float fRec86[3];
	float fRec85[3];
	float fRec84[3];
	float fVec9[2];
	float fRec83[2];
	float fRec82[32768];
	float fRec81[2];
	float fConst142;
	float fRec88[2];
	float fConst143;
	float fConst149;
	float fConst151;
	float fConst152;
	float fConst153;
	float fConst154;
	float fConst155;
	float fRec96[3];
	float fRec95[3];
	float fRec94[3];
	float fRec93[3];
	float fVec10[2];
	float fRec92[2];
	float fRec91[32768];
	float fRec90[2];
	float fConst156;
	float fRec97[2];
	float fConst157;
	float fConst163;
	float fConst165;
	float fConst166;
	float fConst167;
	float fConst168;
	float fConst169;
	float fRec105[3];
	float fRec104[3];
	float fRec103[3];
	float fRec102[3];
	float fVec11[2];
	float fRec101[2];
	float fRec100[32768];
	float fRec99[2];
	float fConst170;
	float fRec106[2];
	float fConst171;
	float fConst177;
	float fConst179;
	float fConst180;
	float fConst181;
	float fConst182;
	float fConst183;
	float fRec114[3];
	float fRec113[3];
	float fRec112[3];
	float fRec111[3];
	float fVec12[2];
	float fRec110[2];
	float fRec109[32768];
	float fRec108[2];
	float fConst184;
	float fRec115[2];
	float fConst185;
	float fConst191;
	float fConst193;
	float fConst194;
	float fConst195;
	float fConst196;
	float fConst197;
	float fRec123[3];
	float fRec122[3];
	float fRec121[3];
	float fRec120[3];
	float fVec13[2];
	float fRec119[2];
	float fRec118[32768];
	float fRec117[2];
	float fConst198;
	float fRec124[2];
	float fConst199;
	float fConst205;
	float fConst207;
	float fConst208;
	float fConst209;
	float fConst210;
	float fConst211;
	float fRec132[3];
	float fRec131[3];
	float fRec130[3];
	float fRec129[3];
	float fVec14[2];
	float fRec128[2];
	float fRec127[32768];
	float fRec126[2];
	float fConst212;
	float fRec133[2];
	float fConst213;
	float fConst219;
	float fConst221;
	float fConst222;
	float fConst223;
	float fConst224;
	float fConst225;
	float fRec141[3];
	float fRec140[3];
	float fRec139[3];
	float fRec138[3];
	float fVec15[2];
	float fRec137[2];
	float fRec136[32768];
	float fRec135[2];
	float fConst226;
	float fRec142[2];
	float fConst227;
	float fConst233;
	float fConst235;
	float fConst236;
	float fConst237;
	float fConst238;
	float fConst239;
	float fRec150[3];
	float fRec149[3];
	float fRec148[3];
	float fRec147[3];
	float fVec16[2];
	float fRec146[2];
	float fRec145[32768];
	float fRec144[2];
	float fConst240;
	float fRec151[2];
	float fConst241;
	float fConst247;
	float fConst249;
	float fConst250;
	float fConst251;
	float fConst252;
	float fConst253;
	float fRec159[3];
	float fRec158[3];
	float fRec157[3];
	float fRec156[3];
	float fVec17[2];
	float fRec155[2];
	float fRec154[32768];
	float fRec153[2];
	float fConst254;
	float fRec160[2];
	float fConst255;
	float fConst261;
	float fConst263;
	float fConst264;
	float fConst265;
	float fConst266;
	float fConst267;
	float fRec168[3];
	float fRec167[3];
	float fRec166[3];
	float fRec165[3];
	float fVec18[2];
	float fRec164[2];
	float fRec163[32768];
	float fRec162[2];
	float fConst268;
	float fRec169[2];
	float fConst269;
	float fConst275;
	float fConst277;
	float fConst278;
	float fConst279;
	float fConst280;
	float fConst281;
	float fRec177[3];
	float fRec176[3];
	float fRec175[3];
	float fRec174[3];
	float fVec19[2];
	float fRec173[2];
	float fRec172[32768];
	float fRec171[2];
	float fConst282;
	float fRec178[2];
	float fConst283;
	float fConst289;
	float fConst291;
	float fConst292;
	float fConst293;
	float fConst294;
	float fConst295;
	float fRec186[3];
	float fRec185[3];
	float fRec184[3];
	float fRec183[3];
	float fVec20[2];
	float fRec182[2];
	float fRec181[32768];
	float fRec180[2];
	float fConst296;
	float fRec187[2];
	float fConst297;
	float fConst303;
	float fConst305;
	float fConst306;
	float fConst307;
	float fConst308;
	float fConst309;
	float fRec195[3];
	float fRec194[3];
	float fRec193[3];
	float fRec192[3];
	float fVec21[2];
	float fRec191[2];
	float fRec190[32768];
	float fRec189[2];
	float fConst310;
	float fRec196[2];
	float fConst311;
	float fConst317;
	float fConst319;
	float fConst320;
	float fConst321;
	float fConst322;
	float fConst323;
	float fRec204[3];
	float fRec203[3];
	float fRec202[3];
	float fRec201[3];
	float fVec22[2];
	float fRec200[2];
	float fRec199[32768];
	float fRec198[2];
	float fConst324;
	float fRec205[2];
	float fConst325;
	float fConst331;
	float fConst333;
	float fConst334;
	float fConst335;
	float fConst336;
	float fConst337;
	float fRec213[3];
	float fRec212[3];
	float fRec211[3];
	float fRec210[3];
	float fVec23[2];
	float fRec209[2];
	float fRec208[32768];
	float fRec207[2];
	float fConst338;
	float fRec214[2];
	float fConst339;
	float fConst345;
	float fConst347;
	float fConst348;
	float fConst349;
	float fConst350;
	float fConst351;
	float fRec222[3];
	float fRec221[3];
	float fRec220[3];
	float fRec219[3];
	float fVec24[2];
	float fRec218[2];
	float fRec217[32768];
	float fRec216[2];
	float fConst352;
	float fRec223[2];
	float fConst353;
	float fConst359;
	float fConst361;
	float fConst362;
	float fConst363;
	float fConst364;
	float fConst365;
	float fRec231[3];
	float fRec230[3];
	float fRec229[3];
	float fRec228[3];
	float fVec25[2];
	float fRec227[2];
	float fRec226[32768];
	float fRec225[2];
	float fConst366;
	float fRec232[2];
	float fConst367;
	float fConst373;
	float fConst375;
	float fConst376;
	float fConst377;
	float fConst378;
	float fConst379;
	float fRec240[3];
	float fRec239[3];
	float fRec238[3];
	float fRec237[3];
	float fVec26[2];
	float fRec236[2];
	float fRec235[32768];
	float fRec234[2];
	float fConst380;
	float fRec241[2];
	float fConst381;
	float fConst387;
	float fConst389;
	float fConst390;
	float fConst391;
	float fConst392;
	float fConst393;
	float fRec249[3];
	float fRec248[3];
	float fRec247[3];
	float fRec246[3];
	float fVec27[2];
	float fRec245[2];
	float fRec244[32768];
	float fRec243[2];
	float fConst394;
	float fRec250[2];
	float fConst395;
	float fConst401;
	float fConst403;
	float fConst404;
	float fConst405;
	float fConst406;
	float fConst407;
	float fRec258[3];
	float fRec257[3];
	float fRec256[3];
	float fRec255[3];
	float fVec28[2];
	float fRec254[2];
	float fRec253[32768];
	float fRec252[2];
	float fConst408;
	float fRec259[2];
	float fConst409;
	float fConst415;
	float fConst417;
	float fConst418;
	float fConst419;
	float fConst420;
	float fConst421;
	float fRec267[3];
	float fRec266[3];
	float fRec265[3];
	float fRec264[3];
	float fVec29[2];
	float fRec263[2];
	float fRec262[32768];
	float fRec261[2];
	float fConst422;
	float fRec268[2];
	float fConst423;
	float fConst429;
	float fConst431;
	float fConst432;
	float fConst433;
	float fConst434;
	float fConst435;
	float fRec276[3];
	float fRec275[3];
	float fRec274[3];
	float fRec273[3];
	float fVec30[2];
	float fRec272[2];
	float fRec271[32768];
	float fRec270[2];
	float fConst436;
	float fRec277[2];
	float fConst437;
	float fConst443;
	float fConst445;
	float fConst446;
	float fConst447;
	float fConst448;
	float fConst449;
	float fRec285[3];
	float fRec284[3];
	float fRec283[3];
	float fRec282[3];
	float fVec31[2];
	float fRec281[2];
	float fRec280[32768];
	float fRec279[2];
	float fConst450;
	float fRec286[2];
	float fConst451;
	float fConst457;
	float fConst459;
	float fConst460;
	float fConst461;
	float fConst462;
	float fConst463;
	float fRec294[3];
	float fRec293[3];
	float fRec292[3];
	float fRec291[3];
	float fVec32[2];
	float fRec290[2];
	float fRec289[32768];
	float fRec288[2];
	float fConst464;
	float fRec295[2];
	float fConst465;
	float fConst471;
	float fConst473;
	float fConst474;
	float fConst475;
	float fConst476;
	float fConst477;
	float fRec303[3];
	float fRec302[3];
	float fRec301[3];
	float fRec300[3];
	float fVec33[2];
	float fRec299[2];
	float fRec298[32768];
	float fRec297[2];
	float fConst478;
	float fRec304[2];
	float fConst479;
	float fConst485;
	float fConst487;
	float fConst488;
	float fConst489;
	float fConst490;
	float fConst491;
	float fRec312[3];
	float fRec311[3];
	float fRec310[3];
	float fRec309[3];
	float fVec34[2];
	float fRec308[2];
	float fRec307[32768];
	float fRec306[2];
	float fConst492;
	float fRec313[2];
	float fConst493;
	float fConst499;
	float fConst501;
	float fConst502;
	float fConst503;
	float fConst504;
	float fConst505;
	float fRec321[3];
	float fRec320[3];
	float fRec319[3];
	float fRec318[3];
	float fVec35[2];
	float fRec317[2];
	float fRec316[32768];
	float fRec315[2];
	float fConst506;
	float fRec322[2];
	float fConst507;
	float fConst513;
	float fConst515;
	float fConst516;
	float fConst517;
	float fConst518;
	float fConst519;
	float fRec330[3];
	float fRec329[3];
	float fRec328[3];
	float fRec327[3];
	float fVec36[2];
	float fRec326[2];
	float fRec325[32768];
	float fRec324[2];
	float fConst520;
	float fRec331[2];
	float fConst521;
	float fConst527;
	float fConst529;
	float fConst530;
	float fConst531;
	float fConst532;
	float fConst533;
	float fRec339[3];
	float fRec338[3];
	float fRec337[3];
	float fRec336[3];
	float fVec37[2];
	float fRec335[2];
	float fRec334[32768];
	float fRec333[2];
	float fConst534;
	float fRec340[2];
	float fConst535;
	float fConst541;
	float fConst543;
	float fConst544;
	float fConst545;
	float fConst546;
	float fConst547;
	float fRec348[3];
	float fRec347[3];
	float fRec346[3];
	float fRec345[3];
	float fVec38[2];
	float fRec344[2];
	float fRec343[32768];
	float fRec342[2];
	float fConst548;
	float fRec349[2];
	float fConst549;
	float fConst555;
	float fConst557;
	float fConst558;
	float fConst559;
	float fConst560;
	float fConst561;
	float fRec357[3];
	float fRec356[3];
	float fRec355[3];
	float fRec354[3];
	float fVec39[2];
	float fRec353[2];
	float fRec352[32768];
	float fRec351[2];
	float fConst562;
	float fRec358[2];
	float fConst563;
	float fConst569;
	float fConst571;
	float fConst572;
	float fConst573;
	float fConst574;
	float fConst575;
	float fRec366[3];
	float fRec365[3];
	float fRec364[3];
	float fRec363[3];
	float fVec40[2];
	float fRec362[2];
	float fRec361[32768];
	float fRec360[2];
	float fConst576;
	float fRec367[2];
	float fConst577;
	float fConst583;
	float fConst585;
	float fConst586;
	float fConst587;
	float fConst588;
	float fConst589;
	float fRec375[3];
	float fRec374[3];
	float fRec373[3];
	float fRec372[3];
	float fVec41[2];
	float fRec371[2];
	float fRec370[32768];
	float fRec369[2];
	float fConst590;
	float fRec376[2];
	float fConst591;
	float fConst597;
	float fConst599;
	float fConst600;
	float fConst601;
	float fConst602;
	float fConst603;
	float fRec384[3];
	float fRec383[3];
	float fRec382[3];
	float fRec381[3];
	float fVec42[2];
	float fRec380[2];
	float fRec379[32768];
	float fRec378[2];
	float fConst604;
	float fRec385[2];
	float fConst605;
	float fConst611;
	float fConst613;
	float fConst614;
	float fConst615;
	float fConst616;
	float fConst617;
	float fRec393[3];
	float fRec392[3];
	float fRec391[3];
	float fRec390[3];
	float fVec43[2];
	float fRec389[2];
	float fRec388[32768];
	float fRec387[2];
	float fConst618;
	float fRec394[2];
	float fConst619;
	float fConst625;
	float fConst627;
	float fConst628;
	float fConst629;
	float fConst630;
	float fConst631;
	float fRec402[3];
	float fRec401[3];
	float fRec400[3];
	float fRec399[3];
	float fVec44[2];
	float fRec398[2];
	float fRec397[32768];
	float fRec396[2];
	float fConst632;
	float fRec403[2];
	float fConst633;
	float fConst639;
	float fConst641;
	float fConst642;
	float fConst643;
	float fConst644;
	float fConst645;
	float fRec411[3];
	float fRec410[3];
	float fRec409[3];
	float fRec408[3];
	float fVec45[2];
	float fRec407[2];
	float fRec406[32768];
	float fRec405[2];
	float fConst646;
	float fRec412[2];
	float fConst647;
	float fConst653;
	float fConst655;
	float fConst656;
	float fConst657;
	float fConst658;
	float fConst659;
	float fRec420[3];
	float fRec419[3];
	float fRec418[3];
	float fRec417[3];
	float fVec46[2];
	float fRec416[2];
	float fRec415[32768];
	float fRec414[2];
	float fConst660;
	float fRec421[2];
	float fConst661;
	float fConst667;
	float fConst669;
	float fConst670;
	float fConst671;
	float fConst672;
	float fConst673;
	float fRec429[3];
	float fRec428[3];
	float fRec427[3];
	float fRec426[3];
	float fVec47[2];
	float fRec425[2];
	float fRec424[32768];
	float fRec423[2];
	float fConst674;
	float fRec430[2];
	float fConst675;
	float fConst681;
	float fConst683;
	float fConst684;
	float fConst685;
	float fConst686;
	float fConst687;
	float fRec438[3];
	float fRec437[3];
	float fRec436[3];
	float fRec435[3];
	float fVec48[2];
	float fRec434[2];
	float fRec433[32768];
	float fRec432[2];
	float fConst688;
	float fRec439[2];
	float fConst689;
	float fConst695;
	float fConst697;
	float fConst698;
	float fConst699;
	float fConst700;
	float fConst701;
	float fRec447[3];
	float fRec446[3];
	float fRec445[3];
	float fRec444[3];
	float fVec49[2];
	float fRec443[2];
	float fRec442[32768];
	float fRec441[2];
	float fConst702;
	float fRec448[2];
	float fConst703;
	float fConst709;
	float fConst711;
	float fConst712;
	float fConst713;
	float fConst714;
	float fConst715;
	float fRec456[3];
	float fRec455[3];
	float fRec454[3];
	float fRec453[3];
	float fVec50[2];
	float fRec452[2];
	float fRec451[32768];
	float fRec450[2];
	float fConst716;
	float fRec457[2];
	float fConst717;
	float fConst723;
	float fConst725;
	float fConst726;
	float fConst727;
	float fConst728;
	float fConst729;
	float fRec465[3];
	float fRec464[3];
	float fRec463[3];
	float fRec462[3];
	float fVec51[2];
	float fRec461[2];
	float fRec460[32768];
	float fRec459[2];
	float fConst730;
	float fRec466[2];
	float fConst731;
	float fConst737;
	float fConst739;
	float fConst740;
	float fConst741;
	float fConst742;
	float fConst743;
	float fRec474[3];
	float fRec473[3];
	float fRec472[3];
	float fRec471[3];
	float fVec52[2];
	float fRec470[2];
	float fRec469[32768];
	float fRec468[2];
	float fConst744;
	float fRec475[2];
	float fConst745;
	float fConst751;
	float fConst753;
	float fConst754;
	float fConst755;
	float fConst756;
	float fConst757;
	float fRec483[3];
	float fRec482[3];
	float fRec481[3];
	float fRec480[3];
	float fVec53[2];
	float fRec479[2];
	float fRec478[32768];
	float fRec477[2];
	float fConst758;
	float fRec484[2];
	float fConst759;
	float fConst765;
	float fConst767;
	float fConst768;
	float fConst769;
	float fConst770;
	float fConst771;
	float fRec492[3];
	float fRec491[3];
	float fRec490[3];
	float fRec489[3];
	float fVec54[2];
	float fRec488[2];
	float fRec487[32768];
	float fRec486[2];
	float fConst772;
	float fRec493[2];
	float fConst773;
	float fConst779;
	float fConst781;
	float fConst782;
	float fConst783;
	float fConst784;
	float fConst785;
	float fRec501[3];
	float fRec500[3];
	float fRec499[3];
	float fRec498[3];
	float fVec55[2];
	float fRec497[2];
	float fRec496[32768];
	float fRec495[2];
	float fConst786;
	float fRec502[2];
	float fConst787;
	float fConst793;
	float fConst795;
	float fConst796;
	float fConst797;
	float fConst798;
	float fConst799;
	float fRec510[3];
	float fRec509[3];
	float fRec508[3];
	float fRec507[3];
	float fVec56[2];
	float fRec506[2];
	float fRec505[32768];
	float fRec504[2];
	float fConst800;
	float fRec511[2];
	float fConst801;
	float fConst807;
	float fConst809;
	float fConst810;
	float fConst811;
	float fConst812;
	float fConst813;
	float fRec519[3];
	float fRec518[3];
	float fRec517[3];
	float fRec516[3];
	float fVec57[2];
	float fRec515[2];
	float fRec514[32768];
	float fRec513[2];
	float fConst814;
	float fRec520[2];
	float fConst815;
	float fConst821;
	float fConst823;
	float fConst824;
	float fConst825;
	float fConst826;
	float fConst827;
	float fRec528[3];
	float fRec527[3];
	float fRec526[3];
	float fRec525[3];
	float fVec58[2];
	float fRec524[2];
	float fRec523[32768];
	float fRec522[2];
	float fConst828;
	float fRec529[2];
	float fConst829;
	float fConst835;
	float fConst837;
	float fConst838;
	float fConst839;
	float fConst840;
	float fConst841;
	float fRec537[3];
	float fRec536[3];
	float fRec535[3];
	float fRec534[3];
	float fVec59[2];
	float fRec533[2];
	float fRec532[32768];
	float fRec531[2];
	float fConst842;
	float fRec538[2];
	float fConst843;
	float fConst849;
	float fConst851;
	float fConst852;
	float fConst853;
	float fConst854;
	float fConst855;
	float fRec546[3];
	float fRec545[3];
	float fRec544[3];
	float fRec543[3];
	float fVec60[2];
	float fRec542[2];
	float fRec541[32768];
	float fRec540[2];
	float fConst856;
	float fRec547[2];
	float fConst857;
	float fConst863;
	float fConst865;
	float fConst866;
	float fConst867;
	float fConst868;
	float fConst869;
	float fRec555[3];
	float fRec554[3];
	float fRec553[3];
	float fRec552[3];
	float fVec61[2];
	float fRec551[2];
	float fRec550[32768];
	float fRec549[2];
	float fConst870;
	float fRec556[2];
	float fConst871;
	float fConst877;
	float fConst879;
	float fConst880;
	float fConst881;
	float fConst882;
	float fConst883;
	float fRec564[3];
	float fRec563[3];
	float fRec562[3];
	float fRec561[3];
	float fVec62[2];
	float fRec560[2];
	float fRec559[32768];
	float fRec558[2];
	float fConst884;
	float fRec565[2];
	float fConst885;
	float fConst891;
	float fConst893;
	float fConst894;
	float fConst895;
	float fConst896;
	float fConst897;
	float fRec573[3];
	float fRec572[3];
	float fRec571[3];
	float fRec570[3];
	float fVec63[2];
	float fRec569[2];
	float fRec568[32768];
	float fRec567[2];
	float fConst898;
	float fRec574[2];
	float fConst899;
	float fConst905;
	float fConst907;
	float fConst908;
	float fConst909;
	float fConst910;
	float fConst911;
	float fRec582[3];
	float fRec581[3];
	float fRec580[3];
	float fRec579[3];
	float fVec64[2];
	float fRec578[2];
	float fRec577[32768];
	float fRec576[2];
	float fConst912;
	float fRec583[2];
	float fConst913;
	float fConst919;
	float fConst921;
	float fConst922;
	float fConst923;
	float fConst924;
	float fConst925;
	float fRec591[3];
	float fRec590[3];
	float fRec589[3];
	float fRec588[3];
	float fVec65[2];
	float fRec587[2];
	float fRec586[32768];
	float fRec585[2];
	float fConst926;
	float fRec592[2];
	float fConst927;
	float fConst933;
	float fConst935;
	float fConst936;
	float fConst937;
	float fConst938;
	float fConst939;
	float fRec600[3];
	float fRec599[3];
	float fRec598[3];
	float fRec597[3];
	float fVec66[2];
	float fRec596[2];
	float fRec595[32768];
	float fRec594[2];
	float fConst940;
	float fRec601[2];
	float fConst941;
	float fConst947;
	float fConst949;
	float fConst950;
	float fConst951;
	float fConst952;
	float fConst953;
	float fRec609[3];
	float fRec608[3];
	float fRec607[3];
	float fRec606[3];
	float fVec67[2];
	float fRec605[2];
	float fRec604[32768];
	float fRec603[2];
	float fConst954;
	float fRec610[2];
	float fConst955;
	float fConst961;
	float fConst963;
	float fConst964;
	float fConst965;
	float fConst966;
	float fConst967;
	float fRec618[3];
	float fRec617[3];
	float fRec616[3];
	float fRec615[3];
	float fVec68[2];
	float fRec614[2];
	float fRec613[32768];
	float fRec612[2];
	float fConst968;
	float fRec619[2];
	float fConst969;
	float fConst975;
	float fConst977;
	float fConst978;
	float fConst979;
	float fConst980;
	float fConst981;
	float fRec627[3];
	float fRec626[3];
	float fRec625[3];
	float fRec624[3];
	float fVec69[2];
	float fRec623[2];
	float fRec622[32768];
	float fRec621[2];
	float fConst982;
	float fRec628[2];
	float fConst983;
	float fConst989;
	float fConst991;
	float fConst992;
	float fConst993;
	float fConst994;
	float fConst995;
	float fRec636[3];
	float fRec635[3];
	float fRec634[3];
	float fRec633[3];
	float fVec70[2];
	float fRec632[2];
	float fRec631[32768];
	float fRec630[2];
	float fConst996;
	float fRec637[2];
	float fConst997;
	float fConst1003;
	float fConst1005;
	float fConst1006;
	float fConst1007;
	float fConst1008;
	float fConst1009;
	float fRec645[3];
	float fRec644[3];
	float fRec643[3];
	float fRec642[3];
	float fVec71[2];
	float fRec641[2];
	float fRec640[32768];
	float fRec639[2];
	float fConst1010;
	float fRec646[2];
	float fConst1011;
	float fConst1017;
	float fConst1019;
	float fConst1020;
	float fConst1021;
	float fConst1022;
	float fConst1023;
	float fRec654[3];
	float fRec653[3];
	float fRec652[3];
	float fRec651[3];
	float fVec72[2];
	float fRec650[2];
	float fRec649[32768];
	float fRec648[2];
	float fConst1024;
	float fRec655[2];
	float fConst1025;
	float fConst1031;
	float fConst1033;
	float fConst1034;
	float fConst1035;
	float fConst1036;
	float fConst1037;
	float fRec663[3];
	float fRec662[3];
	float fRec661[3];
	float fRec660[3];
	float fVec73[2];
	float fRec659[2];
	float fRec658[32768];
	float fRec657[2];
	float fConst1038;
	float fRec664[2];
	float fConst1039;
	float fConst1045;
	float fConst1047;
	float fConst1048;
	float fConst1049;
	float fConst1050;
	float fConst1051;
	float fRec672[3];
	float fRec671[3];
	float fRec670[3];
	float fRec669[3];
	float fVec74[2];
	float fRec668[2];
	float fRec667[32768];
	float fRec666[2];
	float fConst1052;
	float fRec673[2];
	float fConst1053;
	float fConst1059;
	float fConst1061;
	float fConst1062;
	float fConst1063;
	float fConst1064;
	float fConst1065;
	float fRec681[3];
	float fRec680[3];
	float fRec679[3];
	float fRec678[3];
	float fVec75[2];
	float fRec677[2];
	float fRec676[32768];
	float fRec675[2];
	float fConst1066;
	float fRec682[2];
	float fConst1067;
	float fConst1073;
	float fConst1075;
	float fConst1076;
	float fConst1077;
	float fConst1078;
	float fConst1079;
	float fRec690[3];
	float fRec689[3];
	float fRec688[3];
	float fRec687[3];
	float fVec76[2];
	float fRec686[2];
	float fRec685[32768];
	float fRec684[2];
	float fConst1080;
	float fRec691[2];
	float fConst1081;
	float fConst1087;
	float fConst1089;
	float fConst1090;
	float fConst1091;
	float fConst1092;
	float fConst1093;
	float fRec699[3];
	float fRec698[3];
	float fRec697[3];
	float fRec696[3];
	float fVec77[2];
	float fRec695[2];
	float fRec694[32768];
	float fRec693[2];
	float fConst1094;
	float fRec700[2];
	float fConst1095;
	float fConst1101;
	float fConst1103;
	float fConst1104;
	float fConst1105;
	float fConst1106;
	float fConst1107;
	float fRec708[3];
	float fRec707[3];
	float fRec706[3];
	float fRec705[3];
	float fVec78[2];
	float fRec704[2];
	float fRec703[32768];
	float fRec702[2];
	float fConst1108;
	float fRec709[2];
	float fConst1109;
	float fConst1115;
	float fConst1117;
	float fConst1118;
	float fConst1119;
	float fConst1120;
	float fConst1121;
	float fRec717[3];
	float fRec716[3];
	float fRec715[3];
	float fRec714[3];
	float fVec79[2];
	float fRec713[2];
	float fRec712[32768];
	float fRec711[2];
	float fConst1122;
	float fRec718[2];
	float fConst1123;
	float fConst1129;
	float fConst1131;
	float fConst1132;
	float fConst1133;
	float fConst1134;
	float fConst1135;
	float fRec726[3];
	float fRec725[3];
	float fRec724[3];
	float fRec723[3];
	float fVec80[2];
	float fRec722[2];
	float fRec721[32768];
	float fRec720[2];
	float fConst1136;
	float fRec727[2];
	float fConst1137;
	float fConst1143;
	float fConst1145;
	float fConst1146;
	float fConst1147;
	float fConst1148;
	float fConst1149;
	float fRec735[3];
	float fRec734[3];
	float fRec733[3];
	float fRec732[3];
	float fVec81[2];
	float fRec731[2];
	float fRec730[32768];
	float fRec729[2];
	float fConst1150;
	float fRec736[2];
	float fConst1151;
	float fConst1157;
	float fConst1159;
	float fConst1160;
	float fConst1161;
	float fConst1162;
	float fConst1163;
	float fRec744[3];
	float fRec743[3];
	float fRec742[3];
	float fRec741[3];
	float fVec82[2];
	float fRec740[2];
	float fRec739[32768];
	float fRec738[2];
	float fConst1164;
	float fRec745[2];
	float fConst1165;
	float fConst1171;
	float fConst1173;
	float fConst1174;
	float fConst1175;
	float fConst1176;
	float fConst1177;
	float fRec753[3];
	float fRec752[3];
	float fRec751[3];
	float fRec750[3];
	float fVec83[2];
	float fRec749[2];
	float fRec748[32768];
	float fRec747[2];
	float fConst1178;
	float fRec754[2];
	float fConst1179;
	float fConst1185;
	float fConst1187;
	float fConst1188;
	float fConst1189;
	float fConst1190;
	float fConst1191;
	float fRec762[3];
	float fRec761[3];
	float fRec760[3];
	float fRec759[3];
	float fVec84[2];
	float fRec758[2];
	float fRec757[32768];
	float fRec756[2];
	float fConst1192;
	float fRec763[2];
	float fConst1193;
	float fConst1199;
	float fConst1201;
	float fConst1202;
	float fConst1203;
	float fConst1204;
	float fConst1205;
	float fRec771[3];
	float fRec770[3];
	float fRec769[3];
	float fRec768[3];
	float fVec85[2];
	float fRec767[2];
	float fRec766[32768];
	float fRec765[2];
	float fConst1206;
	float fRec772[2];
	float fConst1207;
	float fConst1213;
	float fConst1215;
	float fConst1216;
	float fConst1217;
	float fConst1218;
	float fConst1219;
	float fRec780[3];
	float fRec779[3];
	float fRec778[3];
	float fRec777[3];
	float fVec86[2];
	float fRec776[2];
	float fRec775[32768];
	float fRec774[2];
	float fConst1220;
	float fRec781[2];
	float fConst1221;
	float fConst1227;
	float fConst1229;
	float fConst1230;
	float fConst1231;
	float fConst1232;
	float fConst1233;
	float fRec789[3];
	float fRec788[3];
	float fRec787[3];
	float fRec786[3];
	float fVec87[2];
	float fRec785[2];
	float fRec784[32768];
	float fRec783[2];
	float fConst1234;
	float fRec790[2];
	float fConst1235;
	float fConst1241;
	float fConst1243;
	float fConst1244;
	float fConst1245;
	float fConst1246;
	float fConst1247;
	float fRec798[3];
	float fRec797[3];
	float fRec796[3];
	float fRec795[3];
	float fVec88[2];
	float fRec794[2];
	float fRec793[32768];
	float fRec792[2];
	float fConst1248;
	float fRec799[2];
	float fConst1249;
	float fConst1255;
	float fConst1257;
	float fConst1258;
	float fConst1259;
	float fConst1260;
	float fConst1261;
	float fRec807[3];
	float fRec806[3];
	float fRec805[3];
	float fRec804[3];
	float fVec89[2];
	float fRec803[2];
	float fRec802[32768];
	float fRec801[2];
	float fConst1262;
	float fRec808[2];
	float fConst1263;
	float fConst1269;
	float fConst1271;
	float fConst1272;
	float fConst1273;
	float fConst1274;
	float fConst1275;
	float fRec816[3];
	float fRec815[3];
	float fRec814[3];
	float fRec813[3];
	float fVec90[2];
	float fRec812[2];
	float fRec811[32768];
	float fRec810[2];
	float fConst1276;
	float fRec817[2];
	float fConst1277;
	float fConst1283;
	float fConst1285;
	float fConst1286;
	float fConst1287;
	float fConst1288;
	float fConst1289;
	float fRec825[3];
	float fRec824[3];
	float fRec823[3];
	float fRec822[3];
	float fVec91[2];
	float fRec821[2];
	float fRec820[32768];
	float fRec819[2];
	float fConst1290;
	float fRec826[2];
	float fConst1291;
	float fConst1297;
	float fConst1299;
	float fConst1300;
	float fConst1301;
	float fConst1302;
	float fConst1303;
	float fRec834[3];
	float fRec833[3];
	float fRec832[3];
	float fRec831[3];
	float fVec92[2];
	float fRec830[2];
	float fRec829[32768];
	float fRec828[2];
	float fConst1304;
	float fRec835[2];
	float fConst1305;
	float fConst1311;
	float fConst1313;
	float fConst1314;
	float fConst1315;
	float fConst1316;
	float fConst1317;
	float fRec843[3];
	float fRec842[3];
	float fRec841[3];
	float fRec840[3];
	float fVec93[2];
	float fRec839[2];
	float fRec838[32768];
	float fRec837[2];
	float fConst1318;
	float fRec844[2];
	float fConst1319;
	float fConst1325;
	float fConst1327;
	float fConst1328;
	float fConst1329;
	float fConst1330;
	float fConst1331;
	float fRec852[3];
	float fRec851[3];
	float fRec850[3];
	float fRec849[3];
	float fVec94[2];
	float fRec848[2];
	float fRec847[32768];
	float fRec846[2];
	float fConst1332;
	float fRec853[2];
	float fConst1333;
	float fConst1339;
	float fConst1341;
	float fConst1342;
	float fConst1343;
	float fConst1344;
	float fConst1345;
	float fRec861[3];
	float fRec860[3];
	float fRec859[3];
	float fRec858[3];
	float fVec95[2];
	float fRec857[2];
	float fRec856[32768];
	float fRec855[2];
	float fConst1346;
	float fRec862[2];
	float fConst1347;
	float fConst1353;
	float fConst1355;
	float fConst1356;
	float fConst1357;
	float fConst1358;
	float fConst1359;
	float fRec870[3];
	float fRec869[3];
	float fRec868[3];
	float fRec867[3];
	float fVec96[2];
	float fRec866[2];
	float fRec865[32768];
	float fRec864[2];
	float fConst1360;
	float fRec871[2];
	float fConst1361;
	float fConst1367;
	float fConst1369;
	float fConst1370;
	float fConst1371;
	float fConst1372;
	float fConst1373;
	float fRec879[3];
	float fRec878[3];
	float fRec877[3];
	float fRec876[3];
	float fVec97[2];
	float fRec875[2];
	float fRec874[32768];
	float fRec873[2];
	float fConst1374;
	float fRec880[2];
	float fConst1375;
	float fConst1381;
	float fConst1383;
	float fConst1384;
	float fConst1385;
	float fConst1386;
	float fConst1387;
	float fRec888[3];
	float fRec887[3];
	float fRec886[3];
	float fRec885[3];
	float fVec98[2];
	float fRec884[2];
	float fRec883[32768];
	float fRec882[2];
	float fConst1388;
	float fRec889[2];
	float fConst1389;
	float fConst1395;
	float fConst1397;
	float fConst1398;
	float fConst1399;
	float fConst1400;
	float fConst1401;
	float fRec897[3];
	float fRec896[3];
	float fRec895[3];
	float fRec894[3];
	float fVec99[2];
	float fRec893[2];
	float fRec892[32768];
	float fRec891[2];
	float fConst1402;
	float fRec898[2];
	float fConst1403;
	float fConst1409;
	float fConst1411;
	float fConst1412;
	float fConst1413;
	float fConst1414;
	float fConst1415;
	float fRec906[3];
	float fRec905[3];
	float fRec904[3];
	float fRec903[3];
	float fVec100[2];
	float fRec902[2];
	float fRec901[32768];
	float fRec900[2];
	float fConst1416;
	float fRec907[2];
	float fConst1417;
	float fConst1423;
	float fConst1425;
	float fConst1426;
	float fConst1427;
	float fConst1428;
	float fConst1429;
	float fRec915[3];
	float fRec914[3];
	float fRec913[3];
	float fRec912[3];
	float fVec101[2];
	float fRec911[2];
	float fRec910[32768];
	float fRec909[2];
	float fConst1430;
	float fRec916[2];
	float fConst1431;
	float fConst1437;
	float fConst1439;
	float fConst1440;
	float fConst1441;
	float fConst1442;
	float fConst1443;
	float fRec924[3];
	float fRec923[3];
	float fRec922[3];
	float fRec921[3];
	float fVec102[2];
	float fRec920[2];
	float fRec919[32768];
	float fRec918[2];
	float fConst1444;
	float fRec925[2];
	float fConst1445;
	float fConst1451;
	float fConst1453;
	float fConst1454;
	float fConst1455;
	float fConst1456;
	float fConst1457;
	float fRec933[3];
	float fRec932[3];
	float fRec931[3];
	float fRec930[3];
	float fVec103[2];
	float fRec929[2];
	float fRec928[32768];
	float fRec927[2];
	float fConst1458;
	float fRec934[2];
	float fConst1459;
	float fConst1465;
	float fConst1467;
	float fConst1468;
	float fConst1469;
	float fConst1470;
	float fConst1471;
	float fRec942[3];
	float fRec941[3];
	float fRec940[3];
	float fRec939[3];
	float fVec104[2];
	float fRec938[2];
	float fRec937[32768];
	float fRec936[2];
	float fConst1472;
	float fRec943[2];
	float fConst1473;
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("analyzers.lib/ms_envelope_rect:author", "Dario Sanfilippo and Julius O. Smith III");
		m->declare("analyzers.lib/ms_envelope_rect:copyright", "Copyright (C) 2020 Dario Sanfilippo        <sanfilippo.dario@gmail.com> and         2003-2020 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("analyzers.lib/ms_envelope_rect:license", "MIT-style STK-4.3 license");
		m->declare("analyzers.lib/name", "Faust Analyzer Library");
		m->declare("analyzers.lib/rms_envelope_rect:author", "Dario Sanfilippo and Julius O. Smith III");
		m->declare("analyzers.lib/rms_envelope_rect:copyright", "Copyright (C) 2020 Dario Sanfilippo        <sanfilippo.dario@gmail.com> and         2003-2020 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("analyzers.lib/rms_envelope_rect:license", "MIT-style STK-4.3 license");
		m->declare("analyzers.lib/version", "0.1");
		m->declare("author", "Johann Philippe");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.5");
		m->declare("compile_options", "-a /usr/local/share/faust/juce/juce-plugin.cpp -lang cpp -i -scn base_dsp -es 1 -mcd 16 -uim -single -ftz 0");
		m->declare("copyright", "(c) Johann Philippe 2022");
		m->declare("envelopes.lib/author", "GRAME");
		m->declare("envelopes.lib/copyright", "GRAME");
		m->declare("envelopes.lib/license", "LGPL with exception");
		m->declare("envelopes.lib/name", "Faust Envelope Library");
		m->declare("envelopes.lib/version", "0.1");
		m->declare("filename", "polyphonic_detection.dsp");
		m->declare("filters.lib/avg_rect:author", "Dario Sanfilippo and Julius O. Smith III");
		m->declare("filters.lib/avg_rect:copyright", "Copyright (C) 2020 Dario Sanfilippo        <sanfilippo.dario@gmail.com> and         2003-2020 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/avg_rect:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/bandpass0_bandstop1:author", "Julius O. Smith III");
		m->declare("filters.lib/bandpass0_bandstop1:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/bandpass0_bandstop1:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/bandpass:author", "Julius O. Smith III");
		m->declare("filters.lib/bandpass:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/bandpass:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/dcblocker:author", "Julius O. Smith III");
		m->declare("filters.lib/dcblocker:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/dcblocker:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/fir:author", "Julius O. Smith III");
		m->declare("filters.lib/fir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/fir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/iir:author", "Julius O. Smith III");
		m->declare("filters.lib/iir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/integrator:author", "Julius O. Smith III");
		m->declare("filters.lib/integrator:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/integrator:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/pole:author", "Julius O. Smith III");
		m->declare("filters.lib/pole:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/pole:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf1sb:author", "Julius O. Smith III");
		m->declare("filters.lib/tf1sb:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf1sb:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/version", "0.3");
		m->declare("filters.lib/zero:author", "Julius O. Smith III");
		m->declare("filters.lib/zero:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/zero:license", "MIT-style STK-4.3 license");
		m->declare("license", "MIT");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.5");
		m->declare("name", "polyphonic_detection");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.3");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "0.2");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.1");
		m->declare("version", "1.0");
	}

	virtual int getNumInputs() {
		return 1;
	}
	virtual int getNumOutputs() {
		return 105;
	}
	
	static void classInit(int sample_rate) {
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<float>(192000.0f, std::max<float>(1.0f, float(fSampleRate)));
		float fConst1 = std::tan(83.9343338f / fConst0);
		float fConst2 = fConst0 * fConst1;
		float fConst3 = mydsp_faustpower2_f(fConst0);
		float fConst4 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst1 * std::tan(79.223465f / fConst0)));
		float fConst5 = 2.0f * fConst2 - 0.5f * fConst4 / fConst2;
		fConst6 = 1.0f / fConst0;
		float fConst7 = mydsp_faustpower2_f(fConst6);
		float fConst8 = fConst7 * fConst4;
		fConst9 = 2.0f * fConst5 / fConst0;
		float fConst10 = fConst8 + fConst9 + 4.0f;
		fConst11 = 2.0f * fConst5 / (fConst0 * fConst10);
		fConst12 = 0.0f - fConst11;
		fConst13 = 1.0f / fConst10;
		fConst14 = 2.0f * fConst8 + -8.0f;
		fConst15 = fConst8 + 4.0f - fConst9;
		fConst16 = 25.956543f / fConst0;
		fConst17 = 1.0f - 0.0385259315f * fConst0;
		float fConst18 = std::tan(88.9253311f / fConst0);
		float fConst19 = fConst0 * fConst18;
		float fConst20 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst18 * fConst1));
		float fConst21 = 2.0f * fConst19 - 0.5f * fConst20 / fConst19;
		float fConst22 = fConst7 * fConst20;
		fConst23 = 2.0f * fConst21 / fConst0;
		float fConst24 = fConst22 + fConst23 + 4.0f;
		fConst25 = 2.0f * fConst21 / (fConst0 * fConst24);
		fConst26 = 0.0f - fConst25;
		fConst27 = 1.0f / fConst24;
		fConst28 = 2.0f * fConst22 + -8.0f;
		fConst29 = fConst22 + 4.0f - fConst23;
		fConst30 = 27.5f / fConst0;
		fConst31 = 1.0f - 0.0363636352f * fConst0;
		float fConst32 = std::tan(94.2131042f / fConst0);
		float fConst33 = fConst0 * fConst32;
		float fConst34 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst32 * fConst18));
		float fConst35 = 2.0f * fConst33 - 0.5f * fConst34 / fConst33;
		float fConst36 = fConst7 * fConst34;
		fConst37 = 2.0f * fConst35 / fConst0;
		float fConst38 = fConst36 + fConst37 + 4.0f;
		fConst39 = 2.0f * fConst35 / (fConst0 * fConst38);
		fConst40 = 0.0f - fConst39;
		fConst41 = 1.0f / fConst38;
		fConst42 = 2.0f * fConst36 + -8.0f;
		fConst43 = fConst36 + 4.0f - fConst37;
		fConst44 = 29.1352348f / fConst0;
		fConst45 = 1.0f - 0.0343227014f * fConst0;
		float fConst46 = std::tan(99.8153076f / fConst0);
		float fConst47 = fConst0 * fConst46;
		float fConst48 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst46 * fConst32));
		float fConst49 = 2.0f * fConst47 - 0.5f * fConst48 / fConst47;
		float fConst50 = fConst7 * fConst48;
		fConst51 = 2.0f * fConst49 / fConst0;
		float fConst52 = fConst50 + fConst51 + 4.0f;
		fConst53 = 2.0f * fConst49 / (fConst0 * fConst52);
		fConst54 = 0.0f - fConst53;
		fConst55 = 1.0f / fConst52;
		fConst56 = 2.0f * fConst50 + -8.0f;
		fConst57 = fConst50 + 4.0f - fConst51;
		fConst58 = 30.8677063f / fConst0;
		fConst59 = 1.0f - 0.0323963165f * fConst0;
		float fConst60 = std::tan(105.750633f / fConst0);
		float fConst61 = fConst0 * fConst60;
		float fConst62 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst60 * fConst46));
		float fConst63 = 2.0f * fConst61 - 0.5f * fConst62 / fConst61;
		float fConst64 = fConst7 * fConst62;
		fConst65 = 2.0f * fConst63 / fConst0;
		float fConst66 = fConst64 + fConst65 + 4.0f;
		fConst67 = 2.0f * fConst63 / (fConst0 * fConst66);
		fConst68 = 0.0f - fConst67;
		fConst69 = 1.0f / fConst66;
		fConst70 = 2.0f * fConst64 + -8.0f;
		fConst71 = fConst64 + 4.0f - fConst65;
		fConst72 = 32.7031975f / fConst0;
		fConst73 = 1.0f - 0.0305780508f * fConst0;
		float fConst74 = std::tan(112.038895f / fConst0);
		float fConst75 = fConst0 * fConst74;
		float fConst76 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst74 * fConst60));
		float fConst77 = 2.0f * fConst75 - 0.5f * fConst76 / fConst75;
		float fConst78 = fConst7 * fConst76;
		fConst79 = 2.0f * fConst77 / fConst0;
		float fConst80 = fConst78 + fConst79 + 4.0f;
		fConst81 = 2.0f * fConst77 / (fConst0 * fConst80);
		fConst82 = 0.0f - fConst81;
		fConst83 = 1.0f / fConst80;
		fConst84 = 2.0f * fConst78 + -8.0f;
		fConst85 = fConst78 + 4.0f - fConst79;
		fConst86 = 34.6478271f / fConst0;
		fConst87 = 1.0f - 0.0288618375f * fConst0;
		float fConst88 = std::tan(118.701073f / fConst0);
		float fConst89 = fConst0 * fConst88;
		float fConst90 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst88 * fConst74));
		float fConst91 = 2.0f * fConst89 - 0.5f * fConst90 / fConst89;
		float fConst92 = fConst7 * fConst90;
		fConst93 = 2.0f * fConst91 / fConst0;
		float fConst94 = fConst92 + fConst93 + 4.0f;
		fConst95 = 2.0f * fConst91 / (fConst0 * fConst94);
		fConst96 = 0.0f - fConst95;
		fConst97 = 1.0f / fConst94;
		fConst98 = 2.0f * fConst92 + -8.0f;
		fConst99 = fConst92 + 4.0f - fConst93;
		fConst100 = 36.7080956f / fConst0;
		fConst101 = 1.0f - 0.0272419471f * fConst0;
		float fConst102 = std::tan(125.759407f / fConst0);
		float fConst103 = fConst0 * fConst102;
		float fConst104 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst102 * fConst88));
		float fConst105 = 2.0f * fConst103 - 0.5f * fConst104 / fConst103;
		float fConst106 = fConst7 * fConst104;
		fConst107 = 2.0f * fConst105 / fConst0;
		float fConst108 = fConst106 + fConst107 + 4.0f;
		fConst109 = 2.0f * fConst105 / (fConst0 * fConst108);
		fConst110 = 0.0f - fConst109;
		fConst111 = 1.0f / fConst108;
		fConst112 = 2.0f * fConst106 + -8.0f;
		fConst113 = fConst106 + 4.0f - fConst107;
		fConst114 = 38.890873f / fConst0;
		fConst115 = 1.0f - 0.0257129744f * fConst0;
		float fConst116 = std::tan(133.237457f / fConst0);
		float fConst117 = fConst0 * fConst116;
		float fConst118 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst116 * fConst102));
		float fConst119 = 2.0f * fConst117 - 0.5f * fConst118 / fConst117;
		float fConst120 = fConst7 * fConst118;
		fConst121 = 2.0f * fConst119 / fConst0;
		float fConst122 = fConst120 + fConst121 + 4.0f;
		fConst123 = 2.0f * fConst119 / (fConst0 * fConst122);
		fConst124 = 0.0f - fConst123;
		fConst125 = 1.0f / fConst122;
		fConst126 = 2.0f * fConst120 + -8.0f;
		fConst127 = fConst120 + 4.0f - fConst121;
		fConst128 = 41.2034454f / fConst0;
		fConst129 = 1.0f - 0.0242698155f * fConst0;
		float fConst130 = std::tan(141.160156f / fConst0);
		float fConst131 = fConst0 * fConst130;
		float fConst132 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst130 * fConst116));
		float fConst133 = 2.0f * fConst131 - 0.5f * fConst132 / fConst131;
		float fConst134 = fConst7 * fConst132;
		fConst135 = 2.0f * fConst133 / fConst0;
		float fConst136 = fConst134 + fConst135 + 4.0f;
		fConst137 = 2.0f * fConst133 / (fConst0 * fConst136);
		fConst138 = 0.0f - fConst137;
		fConst139 = 1.0f / fConst136;
		fConst140 = 2.0f * fConst134 + -8.0f;
		fConst141 = fConst134 + 4.0f - fConst135;
		fConst142 = 43.6535301f / fConst0;
		fConst143 = 1.0f - 0.0229076557f * fConst0;
		float fConst144 = std::tan(149.553986f / fConst0);
		float fConst145 = fConst0 * fConst144;
		float fConst146 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst144 * fConst130));
		float fConst147 = 2.0f * fConst145 - 0.5f * fConst146 / fConst145;
		float fConst148 = fConst7 * fConst146;
		fConst149 = 2.0f * fConst147 / fConst0;
		float fConst150 = fConst148 + fConst149 + 4.0f;
		fConst151 = 2.0f * fConst147 / (fConst0 * fConst150);
		fConst152 = 0.0f - fConst151;
		fConst153 = 1.0f / fConst150;
		fConst154 = 2.0f * fConst148 + -8.0f;
		fConst155 = fConst148 + 4.0f - fConst149;
		fConst156 = 46.2493019f / fConst0;
		fConst157 = 1.0f - 0.0216219481f * fConst0;
		float fConst158 = std::tan(158.44693f / fConst0);
		float fConst159 = fConst0 * fConst158;
		float fConst160 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst158 * fConst144));
		float fConst161 = 2.0f * fConst159 - 0.5f * fConst160 / fConst159;
		float fConst162 = fConst7 * fConst160;
		fConst163 = 2.0f * fConst161 / fConst0;
		float fConst164 = fConst162 + fConst163 + 4.0f;
		fConst165 = 2.0f * fConst161 / (fConst0 * fConst164);
		fConst166 = 0.0f - fConst165;
		fConst167 = 1.0f / fConst164;
		fConst168 = 2.0f * fConst162 + -8.0f;
		fConst169 = fConst162 + 4.0f - fConst163;
		fConst170 = 48.9994278f / fConst0;
		fConst171 = 1.0f - 0.0204084013f * fConst0;
		float fConst172 = std::tan(167.868668f / fConst0);
		float fConst173 = fConst0 * fConst172;
		float fConst174 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst172 * fConst158));
		float fConst175 = 2.0f * fConst173 - 0.5f * fConst174 / fConst173;
		float fConst176 = fConst7 * fConst174;
		fConst177 = 2.0f * fConst175 / fConst0;
		float fConst178 = fConst176 + fConst177 + 4.0f;
		fConst179 = 2.0f * fConst175 / (fConst0 * fConst178);
		fConst180 = 0.0f - fConst179;
		fConst181 = 1.0f / fConst178;
		fConst182 = 2.0f * fConst176 + -8.0f;
		fConst183 = fConst176 + 4.0f - fConst177;
		fConst184 = 51.9130859f / fConst0;
		fConst185 = 1.0f - 0.0192629658f * fConst0;
		float fConst186 = std::tan(177.850662f / fConst0);
		float fConst187 = fConst0 * fConst186;
		float fConst188 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst186 * fConst172));
		float fConst189 = 2.0f * fConst187 - 0.5f * fConst188 / fConst187;
		float fConst190 = fConst7 * fConst188;
		fConst191 = 2.0f * fConst189 / fConst0;
		float fConst192 = fConst190 + fConst191 + 4.0f;
		fConst193 = 2.0f * fConst189 / (fConst0 * fConst192);
		fConst194 = 0.0f - fConst193;
		fConst195 = 1.0f / fConst192;
		fConst196 = 2.0f * fConst190 + -8.0f;
		fConst197 = fConst190 + 4.0f - fConst191;
		fConst198 = 55.0f / fConst0;
		fConst199 = 1.0f - 0.0181818176f * fConst0;
		float fConst200 = std::tan(188.426208f / fConst0);
		float fConst201 = fConst0 * fConst200;
		float fConst202 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst200 * fConst186));
		float fConst203 = 2.0f * fConst201 - 0.5f * fConst202 / fConst201;
		float fConst204 = fConst7 * fConst202;
		fConst205 = 2.0f * fConst203 / fConst0;
		float fConst206 = fConst204 + fConst205 + 4.0f;
		fConst207 = 2.0f * fConst203 / (fConst0 * fConst206);
		fConst208 = 0.0f - fConst207;
		fConst209 = 1.0f / fConst206;
		fConst210 = 2.0f * fConst204 + -8.0f;
		fConst211 = fConst204 + 4.0f - fConst205;
		fConst212 = 58.2704697f / fConst0;
		fConst213 = 1.0f - 0.0171613507f * fConst0;
		float fConst214 = std::tan(199.630615f / fConst0);
		float fConst215 = fConst0 * fConst214;
		float fConst216 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst214 * fConst200));
		float fConst217 = 2.0f * fConst215 - 0.5f * fConst216 / fConst215;
		float fConst218 = fConst7 * fConst216;
		fConst219 = 2.0f * fConst217 / fConst0;
		float fConst220 = fConst218 + fConst219 + 4.0f;
		fConst221 = 2.0f * fConst217 / (fConst0 * fConst220);
		fConst222 = 0.0f - fConst221;
		fConst223 = 1.0f / fConst220;
		fConst224 = 2.0f * fConst218 + -8.0f;
		fConst225 = fConst218 + 4.0f - fConst219;
		fConst226 = 61.7354126f / fConst0;
		fConst227 = 1.0f - 0.0161981583f * fConst0;
		float fConst228 = std::tan(211.501266f / fConst0);
		float fConst229 = fConst0 * fConst228;
		float fConst230 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst228 * fConst214));
		float fConst231 = 2.0f * fConst229 - 0.5f * fConst230 / fConst229;
		float fConst232 = fConst7 * fConst230;
		fConst233 = 2.0f * fConst231 / fConst0;
		float fConst234 = fConst232 + fConst233 + 4.0f;
		fConst235 = 2.0f * fConst231 / (fConst0 * fConst234);
		fConst236 = 0.0f - fConst235;
		fConst237 = 1.0f / fConst234;
		fConst238 = 2.0f * fConst232 + -8.0f;
		fConst239 = fConst232 + 4.0f - fConst233;
		fConst240 = 65.406395f / fConst0;
		fConst241 = 1.0f - 0.0152890254f * fConst0;
		float fConst242 = std::tan(224.077789f / fConst0);
		float fConst243 = fConst0 * fConst242;
		float fConst244 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst242 * fConst228));
		float fConst245 = 2.0f * fConst243 - 0.5f * fConst244 / fConst243;
		float fConst246 = fConst7 * fConst244;
		fConst247 = 2.0f * fConst245 / fConst0;
		float fConst248 = fConst246 + fConst247 + 4.0f;
		fConst249 = 2.0f * fConst245 / (fConst0 * fConst248);
		fConst250 = 0.0f - fConst249;
		fConst251 = 1.0f / fConst248;
		fConst252 = 2.0f * fConst246 + -8.0f;
		fConst253 = fConst246 + 4.0f - fConst247;
		fConst254 = 69.2956543f / fConst0;
		fConst255 = 1.0f - 0.0144309187f * fConst0;
		float fConst256 = std::tan(237.402145f / fConst0);
		float fConst257 = fConst0 * fConst256;
		float fConst258 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst256 * fConst242));
		float fConst259 = 2.0f * fConst257 - 0.5f * fConst258 / fConst257;
		float fConst260 = fConst7 * fConst258;
		fConst261 = 2.0f * fConst259 / fConst0;
		float fConst262 = fConst260 + fConst261 + 4.0f;
		fConst263 = 2.0f * fConst259 / (fConst0 * fConst262);
		fConst264 = 0.0f - fConst263;
		fConst265 = 1.0f / fConst262;
		fConst266 = 2.0f * fConst260 + -8.0f;
		fConst267 = fConst260 + 4.0f - fConst261;
		fConst268 = 73.4161911f / fConst0;
		fConst269 = 1.0f - 0.0136209736f * fConst0;
		float fConst270 = std::tan(251.518814f / fConst0);
		float fConst271 = fConst0 * fConst270;
		float fConst272 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst270 * fConst256));
		float fConst273 = 2.0f * fConst271 - 0.5f * fConst272 / fConst271;
		float fConst274 = fConst7 * fConst272;
		fConst275 = 2.0f * fConst273 / fConst0;
		float fConst276 = fConst274 + fConst275 + 4.0f;
		fConst277 = 2.0f * fConst273 / (fConst0 * fConst276);
		fConst278 = 0.0f - fConst277;
		fConst279 = 1.0f / fConst276;
		fConst280 = 2.0f * fConst274 + -8.0f;
		fConst281 = fConst274 + 4.0f - fConst275;
		fConst282 = 77.7817459f / fConst0;
		fConst283 = 1.0f - 0.0128564872f * fConst0;
		float fConst284 = std::tan(266.474915f / fConst0);
		float fConst285 = fConst0 * fConst284;
		float fConst286 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst284 * fConst270));
		float fConst287 = 2.0f * fConst285 - 0.5f * fConst286 / fConst285;
		float fConst288 = fConst7 * fConst286;
		fConst289 = 2.0f * fConst287 / fConst0;
		float fConst290 = fConst288 + fConst289 + 4.0f;
		fConst291 = 2.0f * fConst287 / (fConst0 * fConst290);
		fConst292 = 0.0f - fConst291;
		fConst293 = 1.0f / fConst290;
		fConst294 = 2.0f * fConst288 + -8.0f;
		fConst295 = fConst288 + 4.0f - fConst289;
		fConst296 = 82.4068909f / fConst0;
		fConst297 = 1.0f - 0.0121349078f * fConst0;
		float fConst298 = std::tan(282.320312f / fConst0);
		float fConst299 = fConst0 * fConst298;
		float fConst300 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst298 * fConst284));
		float fConst301 = 2.0f * fConst299 - 0.5f * fConst300 / fConst299;
		float fConst302 = fConst7 * fConst300;
		fConst303 = 2.0f * fConst301 / fConst0;
		float fConst304 = fConst302 + fConst303 + 4.0f;
		fConst305 = 2.0f * fConst301 / (fConst0 * fConst304);
		fConst306 = 0.0f - fConst305;
		fConst307 = 1.0f / fConst304;
		fConst308 = 2.0f * fConst302 + -8.0f;
		fConst309 = fConst302 + 4.0f - fConst303;
		fConst310 = 87.3070602f / fConst0;
		fConst311 = 1.0f - 0.0114538278f * fConst0;
		float fConst312 = std::tan(299.107971f / fConst0);
		float fConst313 = fConst0 * fConst312;
		float fConst314 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst312 * fConst298));
		float fConst315 = 2.0f * fConst313 - 0.5f * fConst314 / fConst313;
		float fConst316 = fConst7 * fConst314;
		fConst317 = 2.0f * fConst315 / fConst0;
		float fConst318 = fConst316 + fConst317 + 4.0f;
		fConst319 = 2.0f * fConst315 / (fConst0 * fConst318);
		fConst320 = 0.0f - fConst319;
		fConst321 = 1.0f / fConst318;
		fConst322 = 2.0f * fConst316 + -8.0f;
		fConst323 = fConst316 + 4.0f - fConst317;
		fConst324 = 92.4986038f / fConst0;
		fConst325 = 1.0f - 0.0108109741f * fConst0;
		float fConst326 = std::tan(316.89386f / fConst0);
		float fConst327 = fConst0 * fConst326;
		float fConst328 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst326 * fConst312));
		float fConst329 = 2.0f * fConst327 - 0.5f * fConst328 / fConst327;
		float fConst330 = fConst7 * fConst328;
		fConst331 = 2.0f * fConst329 / fConst0;
		float fConst332 = fConst330 + fConst331 + 4.0f;
		fConst333 = 2.0f * fConst329 / (fConst0 * fConst332);
		fConst334 = 0.0f - fConst333;
		fConst335 = 1.0f / fConst332;
		fConst336 = 2.0f * fConst330 + -8.0f;
		fConst337 = fConst330 + 4.0f - fConst331;
		fConst338 = 97.9988556f / fConst0;
		fConst339 = 1.0f - 0.0102042006f * fConst0;
		float fConst340 = std::tan(335.737335f / fConst0);
		float fConst341 = fConst0 * fConst340;
		float fConst342 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst340 * fConst326));
		float fConst343 = 2.0f * fConst341 - 0.5f * fConst342 / fConst341;
		float fConst344 = fConst7 * fConst342;
		fConst345 = 2.0f * fConst343 / fConst0;
		float fConst346 = fConst344 + fConst345 + 4.0f;
		fConst347 = 2.0f * fConst343 / (fConst0 * fConst346);
		fConst348 = 0.0f - fConst347;
		fConst349 = 1.0f / fConst346;
		fConst350 = 2.0f * fConst344 + -8.0f;
		fConst351 = fConst344 + 4.0f - fConst345;
		fConst352 = 103.826172f / fConst0;
		fConst353 = 1.0f - 0.00963148288f * fConst0;
		float fConst354 = std::tan(355.701324f / fConst0);
		float fConst355 = fConst0 * fConst354;
		float fConst356 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst354 * fConst340));
		float fConst357 = 2.0f * fConst355 - 0.5f * fConst356 / fConst355;
		float fConst358 = fConst7 * fConst356;
		fConst359 = 2.0f * fConst357 / fConst0;
		float fConst360 = fConst358 + fConst359 + 4.0f;
		fConst361 = 2.0f * fConst357 / (fConst0 * fConst360);
		fConst362 = 0.0f - fConst361;
		fConst363 = 1.0f / fConst360;
		fConst364 = 2.0f * fConst358 + -8.0f;
		fConst365 = fConst358 + 4.0f - fConst359;
		fConst366 = 110.0f / fConst0;
		fConst367 = 1.0f - 0.0090909088f * fConst0;
		float fConst368 = std::tan(376.852417f / fConst0);
		float fConst369 = fConst0 * fConst368;
		float fConst370 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst368 * fConst354));
		float fConst371 = 2.0f * fConst369 - 0.5f * fConst370 / fConst369;
		float fConst372 = fConst7 * fConst370;
		fConst373 = 2.0f * fConst371 / fConst0;
		float fConst374 = fConst372 + fConst373 + 4.0f;
		fConst375 = 2.0f * fConst371 / (fConst0 * fConst374);
		fConst376 = 0.0f - fConst375;
		fConst377 = 1.0f / fConst374;
		fConst378 = 2.0f * fConst372 + -8.0f;
		fConst379 = fConst372 + 4.0f - fConst373;
		fConst380 = 116.540939f / fConst0;
		fConst381 = 1.0f - 0.00858067535f * fConst0;
		float fConst382 = std::tan(399.26123f / fConst0);
		float fConst383 = fConst0 * fConst382;
		float fConst384 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst382 * fConst368));
		float fConst385 = 2.0f * fConst383 - 0.5f * fConst384 / fConst383;
		float fConst386 = fConst7 * fConst384;
		fConst387 = 2.0f * fConst385 / fConst0;
		float fConst388 = fConst386 + fConst387 + 4.0f;
		fConst389 = 2.0f * fConst385 / (fConst0 * fConst388);
		fConst390 = 0.0f - fConst389;
		fConst391 = 1.0f / fConst388;
		fConst392 = 2.0f * fConst386 + -8.0f;
		fConst393 = fConst386 + 4.0f - fConst387;
		fConst394 = 123.470825f / fConst0;
		fConst395 = 1.0f - 0.00809907913f * fConst0;
		float fConst396 = std::tan(423.002533f / fConst0);
		float fConst397 = fConst0 * fConst396;
		float fConst398 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst396 * fConst382));
		float fConst399 = 2.0f * fConst397 - 0.5f * fConst398 / fConst397;
		float fConst400 = fConst7 * fConst398;
		fConst401 = 2.0f * fConst399 / fConst0;
		float fConst402 = fConst400 + fConst401 + 4.0f;
		fConst403 = 2.0f * fConst399 / (fConst0 * fConst402);
		fConst404 = 0.0f - fConst403;
		fConst405 = 1.0f / fConst402;
		fConst406 = 2.0f * fConst400 + -8.0f;
		fConst407 = fConst400 + 4.0f - fConst401;
		fConst408 = 130.81279f / fConst0;
		fConst409 = 1.0f - 0.00764451269f * fConst0;
		float fConst410 = std::tan(448.155579f / fConst0);
		float fConst411 = fConst0 * fConst410;
		float fConst412 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst410 * fConst396));
		float fConst413 = 2.0f * fConst411 - 0.5f * fConst412 / fConst411;
		float fConst414 = fConst7 * fConst412;
		fConst415 = 2.0f * fConst413 / fConst0;
		float fConst416 = fConst414 + fConst415 + 4.0f;
		fConst417 = 2.0f * fConst413 / (fConst0 * fConst416);
		fConst418 = 0.0f - fConst417;
		fConst419 = 1.0f / fConst416;
		fConst420 = 2.0f * fConst414 + -8.0f;
		fConst421 = fConst414 + 4.0f - fConst415;
		fConst422 = 138.591309f / fConst0;
		fConst423 = 1.0f - 0.00721545937f * fConst0;
		float fConst424 = std::tan(474.804291f / fConst0);
		float fConst425 = fConst0 * fConst424;
		float fConst426 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst424 * fConst410));
		float fConst427 = 2.0f * fConst425 - 0.5f * fConst426 / fConst425;
		float fConst428 = fConst7 * fConst426;
		fConst429 = 2.0f * fConst427 / fConst0;
		float fConst430 = fConst428 + fConst429 + 4.0f;
		fConst431 = 2.0f * fConst427 / (fConst0 * fConst430);
		fConst432 = 0.0f - fConst431;
		fConst433 = 1.0f / fConst430;
		fConst434 = 2.0f * fConst428 + -8.0f;
		fConst435 = fConst428 + 4.0f - fConst429;
		fConst436 = 146.832382f / fConst0;
		fConst437 = 1.0f - 0.00681048678f * fConst0;
		float fConst438 = std::tan(503.037628f / fConst0);
		float fConst439 = fConst0 * fConst438;
		float fConst440 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst438 * fConst424));
		float fConst441 = 2.0f * fConst439 - 0.5f * fConst440 / fConst439;
		float fConst442 = fConst7 * fConst440;
		fConst443 = 2.0f * fConst441 / fConst0;
		float fConst444 = fConst442 + fConst443 + 4.0f;
		fConst445 = 2.0f * fConst441 / (fConst0 * fConst444);
		fConst446 = 0.0f - fConst445;
		fConst447 = 1.0f / fConst444;
		fConst448 = 2.0f * fConst442 + -8.0f;
		fConst449 = fConst442 + 4.0f - fConst443;
		fConst450 = 155.563492f / fConst0;
		fConst451 = 1.0f - 0.00642824359f * fConst0;
		float fConst452 = std::tan(532.949829f / fConst0);
		float fConst453 = fConst0 * fConst452;
		float fConst454 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst452 * fConst438));
		float fConst455 = 2.0f * fConst453 - 0.5f * fConst454 / fConst453;
		float fConst456 = fConst7 * fConst454;
		fConst457 = 2.0f * fConst455 / fConst0;
		float fConst458 = fConst456 + fConst457 + 4.0f;
		fConst459 = 2.0f * fConst455 / (fConst0 * fConst458);
		fConst460 = 0.0f - fConst459;
		fConst461 = 1.0f / fConst458;
		fConst462 = 2.0f * fConst456 + -8.0f;
		fConst463 = fConst456 + 4.0f - fConst457;
		fConst464 = 164.813782f / fConst0;
		fConst465 = 1.0f - 0.00606745388f * fConst0;
		float fConst466 = std::tan(564.640625f / fConst0);
		float fConst467 = fConst0 * fConst466;
		float fConst468 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst466 * fConst452));
		float fConst469 = 2.0f * fConst467 - 0.5f * fConst468 / fConst467;
		float fConst470 = fConst7 * fConst468;
		fConst471 = 2.0f * fConst469 / fConst0;
		float fConst472 = fConst470 + fConst471 + 4.0f;
		fConst473 = 2.0f * fConst469 / (fConst0 * fConst472);
		fConst474 = 0.0f - fConst473;
		fConst475 = 1.0f / fConst472;
		fConst476 = 2.0f * fConst470 + -8.0f;
		fConst477 = fConst470 + 4.0f - fConst471;
		fConst478 = 174.61412f / fConst0;
		fConst479 = 1.0f - 0.00572691392f * fConst0;
		float fConst480 = std::tan(598.215942f / fConst0);
		float fConst481 = fConst0 * fConst480;
		float fConst482 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst480 * fConst466));
		float fConst483 = 2.0f * fConst481 - 0.5f * fConst482 / fConst481;
		float fConst484 = fConst7 * fConst482;
		fConst485 = 2.0f * fConst483 / fConst0;
		float fConst486 = fConst484 + fConst485 + 4.0f;
		fConst487 = 2.0f * fConst483 / (fConst0 * fConst486);
		fConst488 = 0.0f - fConst487;
		fConst489 = 1.0f / fConst486;
		fConst490 = 2.0f * fConst484 + -8.0f;
		fConst491 = fConst484 + 4.0f - fConst485;
		fConst492 = 184.997208f / fConst0;
		fConst493 = 1.0f - 0.00540548703f * fConst0;
		float fConst494 = std::tan(633.78772f / fConst0);
		float fConst495 = fConst0 * fConst494;
		float fConst496 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst494 * fConst480));
		float fConst497 = 2.0f * fConst495 - 0.5f * fConst496 / fConst495;
		float fConst498 = fConst7 * fConst496;
		fConst499 = 2.0f * fConst497 / fConst0;
		float fConst500 = fConst498 + fConst499 + 4.0f;
		fConst501 = 2.0f * fConst497 / (fConst0 * fConst500);
		fConst502 = 0.0f - fConst501;
		fConst503 = 1.0f / fConst500;
		fConst504 = 2.0f * fConst498 + -8.0f;
		fConst505 = fConst498 + 4.0f - fConst499;
		fConst506 = 195.997711f / fConst0;
		fConst507 = 1.0f - 0.00510210032f * fConst0;
		float fConst508 = std::tan(671.47467f / fConst0);
		float fConst509 = fConst0 * fConst508;
		float fConst510 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst508 * fConst494));
		float fConst511 = 2.0f * fConst509 - 0.5f * fConst510 / fConst509;
		float fConst512 = fConst7 * fConst510;
		fConst513 = 2.0f * fConst511 / fConst0;
		float fConst514 = fConst512 + fConst513 + 4.0f;
		fConst515 = 2.0f * fConst511 / (fConst0 * fConst514);
		fConst516 = 0.0f - fConst515;
		fConst517 = 1.0f / fConst514;
		fConst518 = 2.0f * fConst512 + -8.0f;
		fConst519 = fConst512 + 4.0f - fConst513;
		fConst520 = 207.652344f / fConst0;
		fConst521 = 1.0f - 0.00481574144f * fConst0;
		float fConst522 = std::tan(711.402649f / fConst0);
		float fConst523 = fConst0 * fConst522;
		float fConst524 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst522 * fConst508));
		float fConst525 = 2.0f * fConst523 - 0.5f * fConst524 / fConst523;
		float fConst526 = fConst7 * fConst524;
		fConst527 = 2.0f * fConst525 / fConst0;
		float fConst528 = fConst526 + fConst527 + 4.0f;
		fConst529 = 2.0f * fConst525 / (fConst0 * fConst528);
		fConst530 = 0.0f - fConst529;
		fConst531 = 1.0f / fConst528;
		fConst532 = 2.0f * fConst526 + -8.0f;
		fConst533 = fConst526 + 4.0f - fConst527;
		fConst534 = 220.0f / fConst0;
		fConst535 = 1.0f - 0.0045454544f * fConst0;
		float fConst536 = std::tan(753.704834f / fConst0);
		float fConst537 = fConst0 * fConst536;
		float fConst538 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst536 * fConst522));
		float fConst539 = 2.0f * fConst537 - 0.5f * fConst538 / fConst537;
		float fConst540 = fConst7 * fConst538;
		fConst541 = 2.0f * fConst539 / fConst0;
		float fConst542 = fConst540 + fConst541 + 4.0f;
		fConst543 = 2.0f * fConst539 / (fConst0 * fConst542);
		fConst544 = 0.0f - fConst543;
		fConst545 = 1.0f / fConst542;
		fConst546 = 2.0f * fConst540 + -8.0f;
		fConst547 = fConst540 + 4.0f - fConst541;
		fConst548 = 233.081879f / fConst0;
		fConst549 = 1.0f - 0.00429033767f * fConst0;
		float fConst550 = std::tan(798.522461f / fConst0);
		float fConst551 = fConst0 * fConst550;
		float fConst552 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst550 * fConst536));
		float fConst553 = 2.0f * fConst551 - 0.5f * fConst552 / fConst551;
		float fConst554 = fConst7 * fConst552;
		fConst555 = 2.0f * fConst553 / fConst0;
		float fConst556 = fConst554 + fConst555 + 4.0f;
		fConst557 = 2.0f * fConst553 / (fConst0 * fConst556);
		fConst558 = 0.0f - fConst557;
		fConst559 = 1.0f / fConst556;
		fConst560 = 2.0f * fConst554 + -8.0f;
		fConst561 = fConst554 + 4.0f - fConst555;
		fConst562 = 246.94165f / fConst0;
		fConst563 = 1.0f - 0.00404953957f * fConst0;
		float fConst564 = std::tan(846.005066f / fConst0);
		float fConst565 = fConst0 * fConst564;
		float fConst566 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst564 * fConst550));
		float fConst567 = 2.0f * fConst565 - 0.5f * fConst566 / fConst565;
		float fConst568 = fConst7 * fConst566;
		fConst569 = 2.0f * fConst567 / fConst0;
		float fConst570 = fConst568 + fConst569 + 4.0f;
		fConst571 = 2.0f * fConst567 / (fConst0 * fConst570);
		fConst572 = 0.0f - fConst571;
		fConst573 = 1.0f / fConst570;
		fConst574 = 2.0f * fConst568 + -8.0f;
		fConst575 = fConst568 + 4.0f - fConst569;
		fConst576 = 261.62558f / fConst0;
		fConst577 = 1.0f - 0.00382225635f * fConst0;
		float fConst578 = std::tan(896.311157f / fConst0);
		float fConst579 = fConst0 * fConst578;
		float fConst580 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst578 * fConst564));
		float fConst581 = 2.0f * fConst579 - 0.5f * fConst580 / fConst579;
		float fConst582 = fConst7 * fConst580;
		fConst583 = 2.0f * fConst581 / fConst0;
		float fConst584 = fConst582 + fConst583 + 4.0f;
		fConst585 = 2.0f * fConst581 / (fConst0 * fConst584);
		fConst586 = 0.0f - fConst585;
		fConst587 = 1.0f / fConst584;
		fConst588 = 2.0f * fConst582 + -8.0f;
		fConst589 = fConst582 + 4.0f - fConst583;
		fConst590 = 277.182617f / fConst0;
		fConst591 = 1.0f - 0.00360772968f * fConst0;
		float fConst592 = std::tan(949.608582f / fConst0);
		float fConst593 = fConst0 * fConst592;
		float fConst594 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst592 * fConst578));
		float fConst595 = 2.0f * fConst593 - 0.5f * fConst594 / fConst593;
		float fConst596 = fConst7 * fConst594;
		fConst597 = 2.0f * fConst595 / fConst0;
		float fConst598 = fConst596 + fConst597 + 4.0f;
		fConst599 = 2.0f * fConst595 / (fConst0 * fConst598);
		fConst600 = 0.0f - fConst599;
		fConst601 = 1.0f / fConst598;
		fConst602 = 2.0f * fConst596 + -8.0f;
		fConst603 = fConst596 + 4.0f - fConst597;
		fConst604 = 293.664764f / fConst0;
		fConst605 = 1.0f - 0.00340524339f * fConst0;
		float fConst606 = std::tan(1006.07526f / fConst0);
		float fConst607 = fConst0 * fConst606;
		float fConst608 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst606 * fConst592));
		float fConst609 = 2.0f * fConst607 - 0.5f * fConst608 / fConst607;
		float fConst610 = fConst7 * fConst608;
		fConst611 = 2.0f * fConst609 / fConst0;
		float fConst612 = fConst610 + fConst611 + 4.0f;
		fConst613 = 2.0f * fConst609 / (fConst0 * fConst612);
		fConst614 = 0.0f - fConst613;
		fConst615 = 1.0f / fConst612;
		fConst616 = 2.0f * fConst610 + -8.0f;
		fConst617 = fConst610 + 4.0f - fConst611;
		fConst618 = 311.126984f / fConst0;
		fConst619 = 1.0f - 0.0032141218f * fConst0;
		float fConst620 = std::tan(1065.89966f / fConst0);
		float fConst621 = fConst0 * fConst620;
		float fConst622 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst620 * fConst606));
		float fConst623 = 2.0f * fConst621 - 0.5f * fConst622 / fConst621;
		float fConst624 = fConst7 * fConst622;
		fConst625 = 2.0f * fConst623 / fConst0;
		float fConst626 = fConst624 + fConst625 + 4.0f;
		fConst627 = 2.0f * fConst623 / (fConst0 * fConst626);
		fConst628 = 0.0f - fConst627;
		fConst629 = 1.0f / fConst626;
		fConst630 = 2.0f * fConst624 + -8.0f;
		fConst631 = fConst624 + 4.0f - fConst625;
		fConst632 = 329.627563f / fConst0;
		fConst633 = 1.0f - 0.00303372694f * fConst0;
		float fConst634 = std::tan(1129.28125f / fConst0);
		float fConst635 = fConst0 * fConst634;
		float fConst636 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst634 * fConst620));
		float fConst637 = 2.0f * fConst635 - 0.5f * fConst636 / fConst635;
		float fConst638 = fConst7 * fConst636;
		fConst639 = 2.0f * fConst637 / fConst0;
		float fConst640 = fConst638 + fConst639 + 4.0f;
		fConst641 = 2.0f * fConst637 / (fConst0 * fConst640);
		fConst642 = 0.0f - fConst641;
		fConst643 = 1.0f / fConst640;
		fConst644 = 2.0f * fConst638 + -8.0f;
		fConst645 = fConst638 + 4.0f - fConst639;
		fConst646 = 349.228241f / fConst0;
		fConst647 = 1.0f - 0.00286345696f * fConst0;
		float fConst648 = std::tan(1196.43188f / fConst0);
		float fConst649 = fConst0 * fConst648;
		float fConst650 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst648 * fConst634));
		float fConst651 = 2.0f * fConst649 - 0.5f * fConst650 / fConst649;
		float fConst652 = fConst7 * fConst650;
		fConst653 = 2.0f * fConst651 / fConst0;
		float fConst654 = fConst652 + fConst653 + 4.0f;
		fConst655 = 2.0f * fConst651 / (fConst0 * fConst654);
		fConst656 = 0.0f - fConst655;
		fConst657 = 1.0f / fConst654;
		fConst658 = 2.0f * fConst652 + -8.0f;
		fConst659 = fConst652 + 4.0f - fConst653;
		fConst660 = 369.994415f / fConst0;
		fConst661 = 1.0f - 0.00270274351f * fConst0;
		float fConst662 = std::tan(1267.57544f / fConst0);
		float fConst663 = fConst0 * fConst662;
		float fConst664 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst662 * fConst648));
		float fConst665 = 2.0f * fConst663 - 0.5f * fConst664 / fConst663;
		float fConst666 = fConst7 * fConst664;
		fConst667 = 2.0f * fConst665 / fConst0;
		float fConst668 = fConst666 + fConst667 + 4.0f;
		fConst669 = 2.0f * fConst665 / (fConst0 * fConst668);
		fConst670 = 0.0f - fConst669;
		fConst671 = 1.0f / fConst668;
		fConst672 = 2.0f * fConst666 + -8.0f;
		fConst673 = fConst666 + 4.0f - fConst667;
		fConst674 = 391.995422f / fConst0;
		fConst675 = 1.0f - 0.00255105016f * fConst0;
		float fConst676 = std::tan(1342.94934f / fConst0);
		float fConst677 = fConst0 * fConst676;
		float fConst678 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst676 * fConst662));
		float fConst679 = 2.0f * fConst677 - 0.5f * fConst678 / fConst677;
		float fConst680 = fConst7 * fConst678;
		fConst681 = 2.0f * fConst679 / fConst0;
		float fConst682 = fConst680 + fConst681 + 4.0f;
		fConst683 = 2.0f * fConst679 / (fConst0 * fConst682);
		fConst684 = 0.0f - fConst683;
		fConst685 = 1.0f / fConst682;
		fConst686 = 2.0f * fConst680 + -8.0f;
		fConst687 = fConst680 + 4.0f - fConst681;
		fConst688 = 415.304688f / fConst0;
		fConst689 = 1.0f - 0.00240787072f * fConst0;
		float fConst690 = std::tan(1422.8053f / fConst0);
		float fConst691 = fConst0 * fConst690;
		float fConst692 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst690 * fConst676));
		float fConst693 = 2.0f * fConst691 - 0.5f * fConst692 / fConst691;
		float fConst694 = fConst7 * fConst692;
		fConst695 = 2.0f * fConst693 / fConst0;
		float fConst696 = fConst694 + fConst695 + 4.0f;
		fConst697 = 2.0f * fConst693 / (fConst0 * fConst696);
		fConst698 = 0.0f - fConst697;
		fConst699 = 1.0f / fConst696;
		fConst700 = 2.0f * fConst694 + -8.0f;
		fConst701 = fConst694 + 4.0f - fConst695;
		fConst702 = 440.0f / fConst0;
		fConst703 = 1.0f - 0.0022727272f * fConst0;
		float fConst704 = std::tan(1507.40967f / fConst0);
		float fConst705 = fConst0 * fConst704;
		float fConst706 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst704 * fConst690));
		float fConst707 = 2.0f * fConst705 - 0.5f * fConst706 / fConst705;
		float fConst708 = fConst7 * fConst706;
		fConst709 = 2.0f * fConst707 / fConst0;
		float fConst710 = fConst708 + fConst709 + 4.0f;
		fConst711 = 2.0f * fConst707 / (fConst0 * fConst710);
		fConst712 = 0.0f - fConst711;
		fConst713 = 1.0f / fConst710;
		fConst714 = 2.0f * fConst708 + -8.0f;
		fConst715 = fConst708 + 4.0f - fConst709;
		fConst716 = 466.163757f / fConst0;
		fConst717 = 1.0f - 0.00214516884f * fConst0;
		float fConst718 = std::tan(1597.04492f / fConst0);
		float fConst719 = fConst0 * fConst718;
		float fConst720 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst718 * fConst704));
		float fConst721 = 2.0f * fConst719 - 0.5f * fConst720 / fConst719;
		float fConst722 = fConst7 * fConst720;
		fConst723 = 2.0f * fConst721 / fConst0;
		float fConst724 = fConst722 + fConst723 + 4.0f;
		fConst725 = 2.0f * fConst721 / (fConst0 * fConst724);
		fConst726 = 0.0f - fConst725;
		fConst727 = 1.0f / fConst724;
		fConst728 = 2.0f * fConst722 + -8.0f;
		fConst729 = fConst722 + 4.0f - fConst723;
		fConst730 = 493.883301f / fConst0;
		fConst731 = 1.0f - 0.00202476978f * fConst0;
		float fConst732 = std::tan(1692.01013f / fConst0);
		float fConst733 = fConst0 * fConst732;
		float fConst734 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst732 * fConst718));
		float fConst735 = 2.0f * fConst733 - 0.5f * fConst734 / fConst733;
		float fConst736 = fConst7 * fConst734;
		fConst737 = 2.0f * fConst735 / fConst0;
		float fConst738 = fConst736 + fConst737 + 4.0f;
		fConst739 = 2.0f * fConst735 / (fConst0 * fConst738);
		fConst740 = 0.0f - fConst739;
		fConst741 = 1.0f / fConst738;
		fConst742 = 2.0f * fConst736 + -8.0f;
		fConst743 = fConst736 + 4.0f - fConst737;
		fConst744 = 523.25116f / fConst0;
		fConst745 = 1.0f - 0.00191112817f * fConst0;
		float fConst746 = std::tan(1792.62231f / fConst0);
		float fConst747 = fConst0 * fConst746;
		float fConst748 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst746 * fConst732));
		float fConst749 = 2.0f * fConst747 - 0.5f * fConst748 / fConst747;
		float fConst750 = fConst7 * fConst748;
		fConst751 = 2.0f * fConst749 / fConst0;
		float fConst752 = fConst750 + fConst751 + 4.0f;
		fConst753 = 2.0f * fConst749 / (fConst0 * fConst752);
		fConst754 = 0.0f - fConst753;
		fConst755 = 1.0f / fConst752;
		fConst756 = 2.0f * fConst750 + -8.0f;
		fConst757 = fConst750 + 4.0f - fConst751;
		fConst758 = 554.365234f / fConst0;
		fConst759 = 1.0f - 0.00180386484f * fConst0;
		float fConst760 = std::tan(1899.21716f / fConst0);
		float fConst761 = fConst0 * fConst760;
		float fConst762 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst760 * fConst746));
		float fConst763 = 2.0f * fConst761 - 0.5f * fConst762 / fConst761;
		float fConst764 = fConst7 * fConst762;
		fConst765 = 2.0f * fConst763 / fConst0;
		float fConst766 = fConst764 + fConst765 + 4.0f;
		fConst767 = 2.0f * fConst763 / (fConst0 * fConst766);
		fConst768 = 0.0f - fConst767;
		fConst769 = 1.0f / fConst766;
		fConst770 = 2.0f * fConst764 + -8.0f;
		fConst771 = fConst764 + 4.0f - fConst765;
		fConst772 = 587.329529f / fConst0;
		fConst773 = 1.0f - 0.0017026217f * fConst0;
		float fConst774 = std::tan(2012.15051f / fConst0);
		float fConst775 = fConst0 * fConst774;
		float fConst776 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst774 * fConst760));
		float fConst777 = 2.0f * fConst775 - 0.5f * fConst776 / fConst775;
		float fConst778 = fConst7 * fConst776;
		fConst779 = 2.0f * fConst777 / fConst0;
		float fConst780 = fConst778 + fConst779 + 4.0f;
		fConst781 = 2.0f * fConst777 / (fConst0 * fConst780);
		fConst782 = 0.0f - fConst781;
		fConst783 = 1.0f / fConst780;
		fConst784 = 2.0f * fConst778 + -8.0f;
		fConst785 = fConst778 + 4.0f - fConst779;
		fConst786 = 622.253967f / fConst0;
		fConst787 = 1.0f - 0.0016070609f * fConst0;
		float fConst788 = std::tan(2131.79932f / fConst0);
		float fConst789 = fConst0 * fConst788;
		float fConst790 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst788 * fConst774));
		float fConst791 = 2.0f * fConst789 - 0.5f * fConst790 / fConst789;
		float fConst792 = fConst7 * fConst790;
		fConst793 = 2.0f * fConst791 / fConst0;
		float fConst794 = fConst792 + fConst793 + 4.0f;
		fConst795 = 2.0f * fConst791 / (fConst0 * fConst794);
		fConst796 = 0.0f - fConst795;
		fConst797 = 1.0f / fConst794;
		fConst798 = 2.0f * fConst792 + -8.0f;
		fConst799 = fConst792 + 4.0f - fConst793;
		fConst800 = 659.255127f / fConst0;
		fConst801 = 1.0f - 0.00151686347f * fConst0;
		float fConst802 = std::tan(2258.5625f / fConst0);
		float fConst803 = fConst0 * fConst802;
		float fConst804 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst802 * fConst788));
		float fConst805 = 2.0f * fConst803 - 0.5f * fConst804 / fConst803;
		float fConst806 = fConst7 * fConst804;
		fConst807 = 2.0f * fConst805 / fConst0;
		float fConst808 = fConst806 + fConst807 + 4.0f;
		fConst809 = 2.0f * fConst805 / (fConst0 * fConst808);
		fConst810 = 0.0f - fConst809;
		fConst811 = 1.0f / fConst808;
		fConst812 = 2.0f * fConst806 + -8.0f;
		fConst813 = fConst806 + 4.0f - fConst807;
		fConst814 = 698.456482f / fConst0;
		fConst815 = 1.0f - 0.00143172848f * fConst0;
		float fConst816 = std::tan(2392.86377f / fConst0);
		float fConst817 = fConst0 * fConst816;
		float fConst818 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst816 * fConst802));
		float fConst819 = 2.0f * fConst817 - 0.5f * fConst818 / fConst817;
		float fConst820 = fConst7 * fConst818;
		fConst821 = 2.0f * fConst819 / fConst0;
		float fConst822 = fConst820 + fConst821 + 4.0f;
		fConst823 = 2.0f * fConst819 / (fConst0 * fConst822);
		fConst824 = 0.0f - fConst823;
		fConst825 = 1.0f / fConst822;
		fConst826 = 2.0f * fConst820 + -8.0f;
		fConst827 = fConst820 + 4.0f - fConst821;
		fConst828 = 739.988831f / fConst0;
		fConst829 = 1.0f - 0.00135137176f * fConst0;
		float fConst830 = std::tan(2535.15088f / fConst0);
		float fConst831 = fConst0 * fConst830;
		float fConst832 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst830 * fConst816));
		float fConst833 = 2.0f * fConst831 - 0.5f * fConst832 / fConst831;
		float fConst834 = fConst7 * fConst832;
		fConst835 = 2.0f * fConst833 / fConst0;
		float fConst836 = fConst834 + fConst835 + 4.0f;
		fConst837 = 2.0f * fConst833 / (fConst0 * fConst836);
		fConst838 = 0.0f - fConst837;
		fConst839 = 1.0f / fConst836;
		fConst840 = 2.0f * fConst834 + -8.0f;
		fConst841 = fConst834 + 4.0f - fConst835;
		fConst842 = 783.990845f / fConst0;
		fConst843 = 1.0f - 0.00127552508f * fConst0;
		float fConst844 = std::tan(2685.89868f / fConst0);
		float fConst845 = fConst0 * fConst844;
		float fConst846 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst844 * fConst830));
		float fConst847 = 2.0f * fConst845 - 0.5f * fConst846 / fConst845;
		float fConst848 = fConst7 * fConst846;
		fConst849 = 2.0f * fConst847 / fConst0;
		float fConst850 = fConst848 + fConst849 + 4.0f;
		fConst851 = 2.0f * fConst847 / (fConst0 * fConst850);
		fConst852 = 0.0f - fConst851;
		fConst853 = 1.0f / fConst850;
		fConst854 = 2.0f * fConst848 + -8.0f;
		fConst855 = fConst848 + 4.0f - fConst849;
		fConst856 = 830.609375f / fConst0;
		fConst857 = 1.0f - 0.00120393536f * fConst0;
		float fConst858 = std::tan(2845.6106f / fConst0);
		float fConst859 = fConst0 * fConst858;
		float fConst860 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst858 * fConst844));
		float fConst861 = 2.0f * fConst859 - 0.5f * fConst860 / fConst859;
		float fConst862 = fConst7 * fConst860;
		fConst863 = 2.0f * fConst861 / fConst0;
		float fConst864 = fConst862 + fConst863 + 4.0f;
		fConst865 = 2.0f * fConst861 / (fConst0 * fConst864);
		fConst866 = 0.0f - fConst865;
		fConst867 = 1.0f / fConst864;
		fConst868 = 2.0f * fConst862 + -8.0f;
		fConst869 = fConst862 + 4.0f - fConst863;
		fConst870 = 880.0f / fConst0;
		fConst871 = 1.0f - 0.0011363636f * fConst0;
		float fConst872 = std::tan(3014.81934f / fConst0);
		float fConst873 = fConst0 * fConst872;
		float fConst874 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst872 * fConst858));
		float fConst875 = 2.0f * fConst873 - 0.5f * fConst874 / fConst873;
		float fConst876 = fConst7 * fConst874;
		fConst877 = 2.0f * fConst875 / fConst0;
		float fConst878 = fConst876 + fConst877 + 4.0f;
		fConst879 = 2.0f * fConst875 / (fConst0 * fConst878);
		fConst880 = 0.0f - fConst879;
		fConst881 = 1.0f / fConst878;
		fConst882 = 2.0f * fConst876 + -8.0f;
		fConst883 = fConst876 + 4.0f - fConst877;
		fConst884 = 932.327515f / fConst0;
		fConst885 = 1.0f - 0.00107258442f * fConst0;
		float fConst886 = std::tan(3194.08984f / fConst0);
		float fConst887 = fConst0 * fConst886;
		float fConst888 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst886 * fConst872));
		float fConst889 = 2.0f * fConst887 - 0.5f * fConst888 / fConst887;
		float fConst890 = fConst7 * fConst888;
		fConst891 = 2.0f * fConst889 / fConst0;
		float fConst892 = fConst890 + fConst891 + 4.0f;
		fConst893 = 2.0f * fConst889 / (fConst0 * fConst892);
		fConst894 = 0.0f - fConst893;
		fConst895 = 1.0f / fConst892;
		fConst896 = 2.0f * fConst890 + -8.0f;
		fConst897 = fConst890 + 4.0f - fConst891;
		fConst898 = 987.766602f / fConst0;
		fConst899 = 1.0f - 0.00101238489f * fConst0;
		float fConst900 = std::tan(3384.02026f / fConst0);
		float fConst901 = fConst0 * fConst900;
		float fConst902 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst900 * fConst886));
		float fConst903 = 2.0f * fConst901 - 0.5f * fConst902 / fConst901;
		float fConst904 = fConst7 * fConst902;
		fConst905 = 2.0f * fConst903 / fConst0;
		float fConst906 = fConst904 + fConst905 + 4.0f;
		fConst907 = 2.0f * fConst903 / (fConst0 * fConst906);
		fConst908 = 0.0f - fConst907;
		fConst909 = 1.0f / fConst906;
		fConst910 = 2.0f * fConst904 + -8.0f;
		fConst911 = fConst904 + 4.0f - fConst905;
		fConst912 = 1046.50232f / fConst0;
		fConst913 = 1.0f - 0.000955564086f * fConst0;
		float fConst914 = std::tan(3585.24463f / fConst0);
		float fConst915 = fConst0 * fConst914;
		float fConst916 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst914 * fConst900));
		float fConst917 = 2.0f * fConst915 - 0.5f * fConst916 / fConst915;
		float fConst918 = fConst7 * fConst916;
		fConst919 = 2.0f * fConst917 / fConst0;
		float fConst920 = fConst918 + fConst919 + 4.0f;
		fConst921 = 2.0f * fConst917 / (fConst0 * fConst920);
		fConst922 = 0.0f - fConst921;
		fConst923 = 1.0f / fConst920;
		fConst924 = 2.0f * fConst918 + -8.0f;
		fConst925 = fConst918 + 4.0f - fConst919;
		fConst926 = 1108.73047f / fConst0;
		fConst927 = 1.0f - 0.000901932421f * fConst0;
		float fConst928 = std::tan(3798.43433f / fConst0);
		float fConst929 = fConst0 * fConst928;
		float fConst930 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst928 * fConst914));
		float fConst931 = 2.0f * fConst929 - 0.5f * fConst930 / fConst929;
		float fConst932 = fConst7 * fConst930;
		fConst933 = 2.0f * fConst931 / fConst0;
		float fConst934 = fConst932 + fConst933 + 4.0f;
		fConst935 = 2.0f * fConst931 / (fConst0 * fConst934);
		fConst936 = 0.0f - fConst935;
		fConst937 = 1.0f / fConst934;
		fConst938 = 2.0f * fConst932 + -8.0f;
		fConst939 = fConst932 + 4.0f - fConst933;
		fConst940 = 1174.65906f / fConst0;
		fConst941 = 1.0f - 0.000851310848f * fConst0;
		float fConst942 = std::tan(4024.30103f / fConst0);
		float fConst943 = fConst0 * fConst942;
		float fConst944 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst942 * fConst928));
		float fConst945 = 2.0f * fConst943 - 0.5f * fConst944 / fConst943;
		float fConst946 = fConst7 * fConst944;
		fConst947 = 2.0f * fConst945 / fConst0;
		float fConst948 = fConst946 + fConst947 + 4.0f;
		fConst949 = 2.0f * fConst945 / (fConst0 * fConst948);
		fConst950 = 0.0f - fConst949;
		fConst951 = 1.0f / fConst948;
		fConst952 = 2.0f * fConst946 + -8.0f;
		fConst953 = fConst946 + 4.0f - fConst947;
		fConst954 = 1244.50793f / fConst0;
		fConst955 = 1.0f - 0.000803530449f * fConst0;
		float fConst956 = std::tan(4263.59863f / fConst0);
		float fConst957 = fConst0 * fConst956;
		float fConst958 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst956 * fConst942));
		float fConst959 = 2.0f * fConst957 - 0.5f * fConst958 / fConst957;
		float fConst960 = fConst7 * fConst958;
		fConst961 = 2.0f * fConst959 / fConst0;
		float fConst962 = fConst960 + fConst961 + 4.0f;
		fConst963 = 2.0f * fConst959 / (fConst0 * fConst962);
		fConst964 = 0.0f - fConst963;
		fConst965 = 1.0f / fConst962;
		fConst966 = 2.0f * fConst960 + -8.0f;
		fConst967 = fConst960 + 4.0f - fConst961;
		fConst968 = 1318.51025f / fConst0;
		fConst969 = 1.0f - 0.000758431735f * fConst0;
		float fConst970 = std::tan(4517.125f / fConst0);
		float fConst971 = fConst0 * fConst970;
		float fConst972 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst970 * fConst956));
		float fConst973 = 2.0f * fConst971 - 0.5f * fConst972 / fConst971;
		float fConst974 = fConst7 * fConst972;
		fConst975 = 2.0f * fConst973 / fConst0;
		float fConst976 = fConst974 + fConst975 + 4.0f;
		fConst977 = 2.0f * fConst973 / (fConst0 * fConst976);
		fConst978 = 0.0f - fConst977;
		fConst979 = 1.0f / fConst976;
		fConst980 = 2.0f * fConst974 + -8.0f;
		fConst981 = fConst974 + 4.0f - fConst975;
		fConst982 = 1396.91296f / fConst0;
		fConst983 = 1.0f - 0.00071586424f * fConst0;
		float fConst984 = std::tan(4785.72754f / fConst0);
		float fConst985 = fConst0 * fConst984;
		float fConst986 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst984 * fConst970));
		float fConst987 = 2.0f * fConst985 - 0.5f * fConst986 / fConst985;
		float fConst988 = fConst7 * fConst986;
		fConst989 = 2.0f * fConst987 / fConst0;
		float fConst990 = fConst988 + fConst989 + 4.0f;
		fConst991 = 2.0f * fConst987 / (fConst0 * fConst990);
		fConst992 = 0.0f - fConst991;
		fConst993 = 1.0f / fConst990;
		fConst994 = 2.0f * fConst988 + -8.0f;
		fConst995 = fConst988 + 4.0f - fConst989;
		fConst996 = 1479.97766f / fConst0;
		fConst997 = 1.0f - 0.000675685878f * fConst0;
		float fConst998 = std::tan(5070.30176f / fConst0);
		float fConst999 = fConst0 * fConst998;
		float fConst1000 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst998 * fConst984));
		float fConst1001 = 2.0f * fConst999 - 0.5f * fConst1000 / fConst999;
		float fConst1002 = fConst7 * fConst1000;
		fConst1003 = 2.0f * fConst1001 / fConst0;
		float fConst1004 = fConst1002 + fConst1003 + 4.0f;
		fConst1005 = 2.0f * fConst1001 / (fConst0 * fConst1004);
		fConst1006 = 0.0f - fConst1005;
		fConst1007 = 1.0f / fConst1004;
		fConst1008 = 2.0f * fConst1002 + -8.0f;
		fConst1009 = fConst1002 + 4.0f - fConst1003;
		fConst1010 = 1567.98169f / fConst0;
		fConst1011 = 1.0f - 0.00063776254f * fConst0;
		float fConst1012 = std::tan(5371.79736f / fConst0);
		float fConst1013 = fConst0 * fConst1012;
		float fConst1014 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst1012 * fConst998));
		float fConst1015 = 2.0f * fConst1013 - 0.5f * fConst1014 / fConst1013;
		float fConst1016 = fConst7 * fConst1014;
		fConst1017 = 2.0f * fConst1015 / fConst0;
		float fConst1018 = fConst1016 + fConst1017 + 4.0f;
		fConst1019 = 2.0f * fConst1015 / (fConst0 * fConst1018);
		fConst1020 = 0.0f - fConst1019;
		fConst1021 = 1.0f / fConst1018;
		fConst1022 = 2.0f * fConst1016 + -8.0f;
		fConst1023 = fConst1016 + 4.0f - fConst1017;
		fConst1024 = 1661.21875f / fConst0;
		fConst1025 = 1.0f - 0.00060196768f * fConst0;
		float fConst1026 = std::tan(5691.22119f / fConst0);
		float fConst1027 = fConst0 * fConst1026;
		float fConst1028 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst1026 * fConst1012));
		float fConst1029 = 2.0f * fConst1027 - 0.5f * fConst1028 / fConst1027;
		float fConst1030 = fConst7 * fConst1028;
		fConst1031 = 2.0f * fConst1029 / fConst0;
		float fConst1032 = fConst1030 + fConst1031 + 4.0f;
		fConst1033 = 2.0f * fConst1029 / (fConst0 * fConst1032);
		fConst1034 = 0.0f - fConst1033;
		fConst1035 = 1.0f / fConst1032;
		fConst1036 = 2.0f * fConst1030 + -8.0f;
		fConst1037 = fConst1030 + 4.0f - fConst1031;
		fConst1038 = 1760.0f / fConst0;
		fConst1039 = 1.0f - 0.0005681818f * fConst0;
		float fConst1040 = std::tan(6029.63867f / fConst0);
		float fConst1041 = fConst0 * fConst1040;
		float fConst1042 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst1040 * fConst1026));
		float fConst1043 = 2.0f * fConst1041 - 0.5f * fConst1042 / fConst1041;
		float fConst1044 = fConst7 * fConst1042;
		fConst1045 = 2.0f * fConst1043 / fConst0;
		float fConst1046 = fConst1044 + fConst1045 + 4.0f;
		fConst1047 = 2.0f * fConst1043 / (fConst0 * fConst1046);
		fConst1048 = 0.0f - fConst1047;
		fConst1049 = 1.0f / fConst1046;
		fConst1050 = 2.0f * fConst1044 + -8.0f;
		fConst1051 = fConst1044 + 4.0f - fConst1045;
		fConst1052 = 1864.65503f / fConst0;
		fConst1053 = 1.0f - 0.000536292209f * fConst0;
		float fConst1054 = std::tan(6388.17969f / fConst0);
		float fConst1055 = fConst0 * fConst1054;
		float fConst1056 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst1054 * fConst1040));
		float fConst1057 = 2.0f * fConst1055 - 0.5f * fConst1056 / fConst1055;
		float fConst1058 = fConst7 * fConst1056;
		fConst1059 = 2.0f * fConst1057 / fConst0;
		float fConst1060 = fConst1058 + fConst1059 + 4.0f;
		fConst1061 = 2.0f * fConst1057 / (fConst0 * fConst1060);
		fConst1062 = 0.0f - fConst1061;
		fConst1063 = 1.0f / fConst1060;
		fConst1064 = 2.0f * fConst1058 + -8.0f;
		fConst1065 = fConst1058 + 4.0f - fConst1059;
		fConst1066 = 1975.5332f / fConst0;
		fConst1067 = 1.0f - 0.000506192446f * fConst0;
		float fConst1068 = std::tan(6768.04053f / fConst0);
		float fConst1069 = fConst0 * fConst1068;
		float fConst1070 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst1068 * fConst1054));
		float fConst1071 = 2.0f * fConst1069 - 0.5f * fConst1070 / fConst1069;
		float fConst1072 = fConst7 * fConst1070;
		fConst1073 = 2.0f * fConst1071 / fConst0;
		float fConst1074 = fConst1072 + fConst1073 + 4.0f;
		fConst1075 = 2.0f * fConst1071 / (fConst0 * fConst1074);
		fConst1076 = 0.0f - fConst1075;
		fConst1077 = 1.0f / fConst1074;
		fConst1078 = 2.0f * fConst1072 + -8.0f;
		fConst1079 = fConst1072 + 4.0f - fConst1073;
		fConst1080 = 2093.00464f / fConst0;
		fConst1081 = 1.0f - 0.000477782043f * fConst0;
		float fConst1082 = std::tan(7170.48926f / fConst0);
		float fConst1083 = fConst0 * fConst1082;
		float fConst1084 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst1082 * fConst1068));
		float fConst1085 = 2.0f * fConst1083 - 0.5f * fConst1084 / fConst1083;
		float fConst1086 = fConst7 * fConst1084;
		fConst1087 = 2.0f * fConst1085 / fConst0;
		float fConst1088 = fConst1086 + fConst1087 + 4.0f;
		fConst1089 = 2.0f * fConst1085 / (fConst0 * fConst1088);
		fConst1090 = 0.0f - fConst1089;
		fConst1091 = 1.0f / fConst1088;
		fConst1092 = 2.0f * fConst1086 + -8.0f;
		fConst1093 = fConst1086 + 4.0f - fConst1087;
		fConst1094 = 2217.46094f / fConst0;
		fConst1095 = 1.0f - 0.00045096621f * fConst0;
		float fConst1096 = std::tan(7596.86865f / fConst0);
		float fConst1097 = fConst0 * fConst1096;
		float fConst1098 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst1096 * fConst1082));
		float fConst1099 = 2.0f * fConst1097 - 0.5f * fConst1098 / fConst1097;
		float fConst1100 = fConst7 * fConst1098;
		fConst1101 = 2.0f * fConst1099 / fConst0;
		float fConst1102 = fConst1100 + fConst1101 + 4.0f;
		fConst1103 = 2.0f * fConst1099 / (fConst0 * fConst1102);
		fConst1104 = 0.0f - fConst1103;
		fConst1105 = 1.0f / fConst1102;
		fConst1106 = 2.0f * fConst1100 + -8.0f;
		fConst1107 = fConst1100 + 4.0f - fConst1101;
		fConst1108 = 2349.31812f / fConst0;
		fConst1109 = 1.0f - 0.000425655424f * fConst0;
		float fConst1110 = std::tan(8048.60205f / fConst0);
		float fConst1111 = fConst0 * fConst1110;
		float fConst1112 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst1110 * fConst1096));
		float fConst1113 = 2.0f * fConst1111 - 0.5f * fConst1112 / fConst1111;
		float fConst1114 = fConst7 * fConst1112;
		fConst1115 = 2.0f * fConst1113 / fConst0;
		float fConst1116 = fConst1114 + fConst1115 + 4.0f;
		fConst1117 = 2.0f * fConst1113 / (fConst0 * fConst1116);
		fConst1118 = 0.0f - fConst1117;
		fConst1119 = 1.0f / fConst1116;
		fConst1120 = 2.0f * fConst1114 + -8.0f;
		fConst1121 = fConst1114 + 4.0f - fConst1115;
		fConst1122 = 2489.01587f / fConst0;
		fConst1123 = 1.0f - 0.000401765225f * fConst0;
		float fConst1124 = std::tan(8527.19727f / fConst0);
		float fConst1125 = fConst0 * fConst1124;
		float fConst1126 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst1124 * fConst1110));
		float fConst1127 = 2.0f * fConst1125 - 0.5f * fConst1126 / fConst1125;
		float fConst1128 = fConst7 * fConst1126;
		fConst1129 = 2.0f * fConst1127 / fConst0;
		float fConst1130 = fConst1128 + fConst1129 + 4.0f;
		fConst1131 = 2.0f * fConst1127 / (fConst0 * fConst1130);
		fConst1132 = 0.0f - fConst1131;
		fConst1133 = 1.0f / fConst1130;
		fConst1134 = 2.0f * fConst1128 + -8.0f;
		fConst1135 = fConst1128 + 4.0f - fConst1129;
		fConst1136 = 2637.02051f / fConst0;
		fConst1137 = 1.0f - 0.000379215868f * fConst0;
		float fConst1138 = std::tan(9034.25f / fConst0);
		float fConst1139 = fConst0 * fConst1138;
		float fConst1140 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst1138 * fConst1124));
		float fConst1141 = 2.0f * fConst1139 - 0.5f * fConst1140 / fConst1139;
		float fConst1142 = fConst7 * fConst1140;
		fConst1143 = 2.0f * fConst1141 / fConst0;
		float fConst1144 = fConst1142 + fConst1143 + 4.0f;
		fConst1145 = 2.0f * fConst1141 / (fConst0 * fConst1144);
		fConst1146 = 0.0f - fConst1145;
		fConst1147 = 1.0f / fConst1144;
		fConst1148 = 2.0f * fConst1142 + -8.0f;
		fConst1149 = fConst1142 + 4.0f - fConst1143;
		fConst1150 = 2793.82593f / fConst0;
		fConst1151 = 1.0f - 0.00035793212f * fConst0;
		float fConst1152 = std::tan(9571.45508f / fConst0);
		float fConst1153 = fConst0 * fConst1152;
		float fConst1154 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst1152 * fConst1138));
		float fConst1155 = 2.0f * fConst1153 - 0.5f * fConst1154 / fConst1153;
		float fConst1156 = fConst7 * fConst1154;
		fConst1157 = 2.0f * fConst1155 / fConst0;
		float fConst1158 = fConst1156 + fConst1157 + 4.0f;
		fConst1159 = 2.0f * fConst1155 / (fConst0 * fConst1158);
		fConst1160 = 0.0f - fConst1159;
		fConst1161 = 1.0f / fConst1158;
		fConst1162 = 2.0f * fConst1156 + -8.0f;
		fConst1163 = fConst1156 + 4.0f - fConst1157;
		fConst1164 = 2959.95532f / fConst0;
		fConst1165 = 1.0f - 0.000337842939f * fConst0;
		float fConst1166 = std::tan(10140.6035f / fConst0);
		float fConst1167 = fConst0 * fConst1166;
		float fConst1168 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst1166 * fConst1152));
		float fConst1169 = 2.0f * fConst1167 - 0.5f * fConst1168 / fConst1167;
		float fConst1170 = fConst7 * fConst1168;
		fConst1171 = 2.0f * fConst1169 / fConst0;
		float fConst1172 = fConst1170 + fConst1171 + 4.0f;
		fConst1173 = 2.0f * fConst1169 / (fConst0 * fConst1172);
		fConst1174 = 0.0f - fConst1173;
		fConst1175 = 1.0f / fConst1172;
		fConst1176 = 2.0f * fConst1170 + -8.0f;
		fConst1177 = fConst1170 + 4.0f - fConst1171;
		fConst1178 = 3135.96338f / fConst0;
		fConst1179 = 1.0f - 0.00031888127f * fConst0;
		float fConst1180 = std::tan(10743.5947f / fConst0);
		float fConst1181 = fConst0 * fConst1180;
		float fConst1182 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst1180 * fConst1166));
		float fConst1183 = 2.0f * fConst1181 - 0.5f * fConst1182 / fConst1181;
		float fConst1184 = fConst7 * fConst1182;
		fConst1185 = 2.0f * fConst1183 / fConst0;
		float fConst1186 = fConst1184 + fConst1185 + 4.0f;
		fConst1187 = 2.0f * fConst1183 / (fConst0 * fConst1186);
		fConst1188 = 0.0f - fConst1187;
		fConst1189 = 1.0f / fConst1186;
		fConst1190 = 2.0f * fConst1184 + -8.0f;
		fConst1191 = fConst1184 + 4.0f - fConst1185;
		fConst1192 = 3322.4375f / fConst0;
		fConst1193 = 1.0f - 0.00030098384f * fConst0;
		float fConst1194 = std::tan(11382.4424f / fConst0);
		float fConst1195 = fConst0 * fConst1194;
		float fConst1196 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst1194 * fConst1180));
		float fConst1197 = 2.0f * fConst1195 - 0.5f * fConst1196 / fConst1195;
		float fConst1198 = fConst7 * fConst1196;
		fConst1199 = 2.0f * fConst1197 / fConst0;
		float fConst1200 = fConst1198 + fConst1199 + 4.0f;
		fConst1201 = 2.0f * fConst1197 / (fConst0 * fConst1200);
		fConst1202 = 0.0f - fConst1201;
		fConst1203 = 1.0f / fConst1200;
		fConst1204 = 2.0f * fConst1198 + -8.0f;
		fConst1205 = fConst1198 + 4.0f - fConst1199;
		fConst1206 = 3520.0f / fConst0;
		fConst1207 = 1.0f - 0.0002840909f * fConst0;
		float fConst1208 = std::tan(12059.2773f / fConst0);
		float fConst1209 = fConst0 * fConst1208;
		float fConst1210 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst1208 * fConst1194));
		float fConst1211 = 2.0f * fConst1209 - 0.5f * fConst1210 / fConst1209;
		float fConst1212 = fConst7 * fConst1210;
		fConst1213 = 2.0f * fConst1211 / fConst0;
		float fConst1214 = fConst1212 + fConst1213 + 4.0f;
		fConst1215 = 2.0f * fConst1211 / (fConst0 * fConst1214);
		fConst1216 = 0.0f - fConst1215;
		fConst1217 = 1.0f / fConst1214;
		fConst1218 = 2.0f * fConst1212 + -8.0f;
		fConst1219 = fConst1212 + 4.0f - fConst1213;
		fConst1220 = 3729.31006f / fConst0;
		fConst1221 = 1.0f - 0.000268146105f * fConst0;
		float fConst1222 = std::tan(12776.3594f / fConst0);
		float fConst1223 = fConst0 * fConst1222;
		float fConst1224 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst1222 * fConst1208));
		float fConst1225 = 2.0f * fConst1223 - 0.5f * fConst1224 / fConst1223;
		float fConst1226 = fConst7 * fConst1224;
		fConst1227 = 2.0f * fConst1225 / fConst0;
		float fConst1228 = fConst1226 + fConst1227 + 4.0f;
		fConst1229 = 2.0f * fConst1225 / (fConst0 * fConst1228);
		fConst1230 = 0.0f - fConst1229;
		fConst1231 = 1.0f / fConst1228;
		fConst1232 = 2.0f * fConst1226 + -8.0f;
		fConst1233 = fConst1226 + 4.0f - fConst1227;
		fConst1234 = 3951.06641f / fConst0;
		fConst1235 = 1.0f - 0.000253096223f * fConst0;
		float fConst1236 = std::tan(13536.0811f / fConst0);
		float fConst1237 = fConst0 * fConst1236;
		float fConst1238 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst1236 * fConst1222));
		float fConst1239 = 2.0f * fConst1237 - 0.5f * fConst1238 / fConst1237;
		float fConst1240 = fConst7 * fConst1238;
		fConst1241 = 2.0f * fConst1239 / fConst0;
		float fConst1242 = fConst1240 + fConst1241 + 4.0f;
		fConst1243 = 2.0f * fConst1239 / (fConst0 * fConst1242);
		fConst1244 = 0.0f - fConst1243;
		fConst1245 = 1.0f / fConst1242;
		fConst1246 = 2.0f * fConst1240 + -8.0f;
		fConst1247 = fConst1240 + 4.0f - fConst1241;
		fConst1248 = 4186.00928f / fConst0;
		fConst1249 = 1.0f - 0.000238891022f * fConst0;
		float fConst1250 = std::tan(14340.9785f / fConst0);
		float fConst1251 = fConst0 * fConst1250;
		float fConst1252 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst1250 * fConst1236));
		float fConst1253 = 2.0f * fConst1251 - 0.5f * fConst1252 / fConst1251;
		float fConst1254 = fConst7 * fConst1252;
		fConst1255 = 2.0f * fConst1253 / fConst0;
		float fConst1256 = fConst1254 + fConst1255 + 4.0f;
		fConst1257 = 2.0f * fConst1253 / (fConst0 * fConst1256);
		fConst1258 = 0.0f - fConst1257;
		fConst1259 = 1.0f / fConst1256;
		fConst1260 = 2.0f * fConst1254 + -8.0f;
		fConst1261 = fConst1254 + 4.0f - fConst1255;
		fConst1262 = 4434.92188f / fConst0;
		fConst1263 = 1.0f - 0.000225483105f * fConst0;
		float fConst1264 = std::tan(15193.7373f / fConst0);
		float fConst1265 = fConst0 * fConst1264;
		float fConst1266 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst1264 * fConst1250));
		float fConst1267 = 2.0f * fConst1265 - 0.5f * fConst1266 / fConst1265;
		float fConst1268 = fConst7 * fConst1266;
		fConst1269 = 2.0f * fConst1267 / fConst0;
		float fConst1270 = fConst1268 + fConst1269 + 4.0f;
		fConst1271 = 2.0f * fConst1267 / (fConst0 * fConst1270);
		fConst1272 = 0.0f - fConst1271;
		fConst1273 = 1.0f / fConst1270;
		fConst1274 = 2.0f * fConst1268 + -8.0f;
		fConst1275 = fConst1268 + 4.0f - fConst1269;
		fConst1276 = 4698.63623f / fConst0;
		fConst1277 = 1.0f - 0.000212827712f * fConst0;
		float fConst1278 = std::tan(16097.2041f / fConst0);
		float fConst1279 = fConst0 * fConst1278;
		float fConst1280 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst1278 * fConst1264));
		float fConst1281 = 2.0f * fConst1279 - 0.5f * fConst1280 / fConst1279;
		float fConst1282 = fConst7 * fConst1280;
		fConst1283 = 2.0f * fConst1281 / fConst0;
		float fConst1284 = fConst1282 + fConst1283 + 4.0f;
		fConst1285 = 2.0f * fConst1281 / (fConst0 * fConst1284);
		fConst1286 = 0.0f - fConst1285;
		fConst1287 = 1.0f / fConst1284;
		fConst1288 = 2.0f * fConst1282 + -8.0f;
		fConst1289 = fConst1282 + 4.0f - fConst1283;
		fConst1290 = 4978.03174f / fConst0;
		fConst1291 = 1.0f - 0.000200882612f * fConst0;
		float fConst1292 = std::tan(17054.3945f / fConst0);
		float fConst1293 = fConst0 * fConst1292;
		float fConst1294 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst1292 * fConst1278));
		float fConst1295 = 2.0f * fConst1293 - 0.5f * fConst1294 / fConst1293;
		float fConst1296 = fConst7 * fConst1294;
		fConst1297 = 2.0f * fConst1295 / fConst0;
		float fConst1298 = fConst1296 + fConst1297 + 4.0f;
		fConst1299 = 2.0f * fConst1295 / (fConst0 * fConst1298);
		fConst1300 = 0.0f - fConst1299;
		fConst1301 = 1.0f / fConst1298;
		fConst1302 = 2.0f * fConst1296 + -8.0f;
		fConst1303 = fConst1296 + 4.0f - fConst1297;
		fConst1304 = 5274.04102f / fConst0;
		fConst1305 = 1.0f - 0.000189607934f * fConst0;
		float fConst1306 = std::tan(18068.5f / fConst0);
		float fConst1307 = fConst0 * fConst1306;
		float fConst1308 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst1306 * fConst1292));
		float fConst1309 = 2.0f * fConst1307 - 0.5f * fConst1308 / fConst1307;
		float fConst1310 = fConst7 * fConst1308;
		fConst1311 = 2.0f * fConst1309 / fConst0;
		float fConst1312 = fConst1310 + fConst1311 + 4.0f;
		fConst1313 = 2.0f * fConst1309 / (fConst0 * fConst1312);
		fConst1314 = 0.0f - fConst1313;
		fConst1315 = 1.0f / fConst1312;
		fConst1316 = 2.0f * fConst1310 + -8.0f;
		fConst1317 = fConst1310 + 4.0f - fConst1311;
		fConst1318 = 5587.65186f / fConst0;
		fConst1319 = 1.0f - 0.00017896606f * fConst0;
		float fConst1320 = std::tan(19142.9102f / fConst0);
		float fConst1321 = fConst0 * fConst1320;
		float fConst1322 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst1320 * fConst1306));
		float fConst1323 = 2.0f * fConst1321 - 0.5f * fConst1322 / fConst1321;
		float fConst1324 = fConst7 * fConst1322;
		fConst1325 = 2.0f * fConst1323 / fConst0;
		float fConst1326 = fConst1324 + fConst1325 + 4.0f;
		fConst1327 = 2.0f * fConst1323 / (fConst0 * fConst1326);
		fConst1328 = 0.0f - fConst1327;
		fConst1329 = 1.0f / fConst1326;
		fConst1330 = 2.0f * fConst1324 + -8.0f;
		fConst1331 = fConst1324 + 4.0f - fConst1325;
		fConst1332 = 5919.91064f / fConst0;
		fConst1333 = 1.0f - 0.00016892147f * fConst0;
		float fConst1334 = std::tan(20281.207f / fConst0);
		float fConst1335 = fConst0 * fConst1334;
		float fConst1336 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst1334 * fConst1320));
		float fConst1337 = 2.0f * fConst1335 - 0.5f * fConst1336 / fConst1335;
		float fConst1338 = fConst7 * fConst1336;
		fConst1339 = 2.0f * fConst1337 / fConst0;
		float fConst1340 = fConst1338 + fConst1339 + 4.0f;
		fConst1341 = 2.0f * fConst1337 / (fConst0 * fConst1340);
		fConst1342 = 0.0f - fConst1341;
		fConst1343 = 1.0f / fConst1340;
		fConst1344 = 2.0f * fConst1338 + -8.0f;
		fConst1345 = fConst1338 + 4.0f - fConst1339;
		fConst1346 = 6271.92676f / fConst0;
		fConst1347 = 1.0f - 0.000159440635f * fConst0;
		float fConst1348 = std::tan(21487.1895f / fConst0);
		float fConst1349 = fConst0 * fConst1348;
		float fConst1350 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst1348 * fConst1334));
		float fConst1351 = 2.0f * fConst1349 - 0.5f * fConst1350 / fConst1349;
		float fConst1352 = fConst7 * fConst1350;
		fConst1353 = 2.0f * fConst1351 / fConst0;
		float fConst1354 = fConst1352 + fConst1353 + 4.0f;
		fConst1355 = 2.0f * fConst1351 / (fConst0 * fConst1354);
		fConst1356 = 0.0f - fConst1355;
		fConst1357 = 1.0f / fConst1354;
		fConst1358 = 2.0f * fConst1352 + -8.0f;
		fConst1359 = fConst1352 + 4.0f - fConst1353;
		fConst1360 = 6644.875f / fConst0;
		fConst1361 = 1.0f - 0.00015049192f * fConst0;
		float fConst1362 = std::tan(22764.8848f / fConst0);
		float fConst1363 = fConst0 * fConst1362;
		float fConst1364 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst1362 * fConst1348));
		float fConst1365 = 2.0f * fConst1363 - 0.5f * fConst1364 / fConst1363;
		float fConst1366 = fConst7 * fConst1364;
		fConst1367 = 2.0f * fConst1365 / fConst0;
		float fConst1368 = fConst1366 + fConst1367 + 4.0f;
		fConst1369 = 2.0f * fConst1365 / (fConst0 * fConst1368);
		fConst1370 = 0.0f - fConst1369;
		fConst1371 = 1.0f / fConst1368;
		fConst1372 = 2.0f * fConst1366 + -8.0f;
		fConst1373 = fConst1366 + 4.0f - fConst1367;
		fConst1374 = 7040.0f / fConst0;
		fConst1375 = 1.0f - 0.00014204545f * fConst0;
		float fConst1376 = std::tan(24118.5547f / fConst0);
		float fConst1377 = fConst0 * fConst1376;
		float fConst1378 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst1376 * fConst1362));
		float fConst1379 = 2.0f * fConst1377 - 0.5f * fConst1378 / fConst1377;
		float fConst1380 = fConst7 * fConst1378;
		fConst1381 = 2.0f * fConst1379 / fConst0;
		float fConst1382 = fConst1380 + fConst1381 + 4.0f;
		fConst1383 = 2.0f * fConst1379 / (fConst0 * fConst1382);
		fConst1384 = 0.0f - fConst1383;
		fConst1385 = 1.0f / fConst1382;
		fConst1386 = 2.0f * fConst1380 + -8.0f;
		fConst1387 = fConst1380 + 4.0f - fConst1381;
		fConst1388 = 7458.62012f / fConst0;
		fConst1389 = 1.0f - 0.000134073052f * fConst0;
		float fConst1390 = std::tan(25552.7188f / fConst0);
		float fConst1391 = fConst0 * fConst1390;
		float fConst1392 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst1390 * fConst1376));
		float fConst1393 = 2.0f * fConst1391 - 0.5f * fConst1392 / fConst1391;
		float fConst1394 = fConst7 * fConst1392;
		fConst1395 = 2.0f * fConst1393 / fConst0;
		float fConst1396 = fConst1394 + fConst1395 + 4.0f;
		fConst1397 = 2.0f * fConst1393 / (fConst0 * fConst1396);
		fConst1398 = 0.0f - fConst1397;
		fConst1399 = 1.0f / fConst1396;
		fConst1400 = 2.0f * fConst1394 + -8.0f;
		fConst1401 = fConst1394 + 4.0f - fConst1395;
		fConst1402 = 7902.13281f / fConst0;
		fConst1403 = 1.0f - 0.000126548111f * fConst0;
		float fConst1404 = std::tan(27072.1621f / fConst0);
		float fConst1405 = fConst0 * fConst1404;
		float fConst1406 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst1404 * fConst1390));
		float fConst1407 = 2.0f * fConst1405 - 0.5f * fConst1406 / fConst1405;
		float fConst1408 = fConst7 * fConst1406;
		fConst1409 = 2.0f * fConst1407 / fConst0;
		float fConst1410 = fConst1408 + fConst1409 + 4.0f;
		fConst1411 = 2.0f * fConst1407 / (fConst0 * fConst1410);
		fConst1412 = 0.0f - fConst1411;
		fConst1413 = 1.0f / fConst1410;
		fConst1414 = 2.0f * fConst1408 + -8.0f;
		fConst1415 = fConst1408 + 4.0f - fConst1409;
		fConst1416 = 8372.01855f / fConst0;
		fConst1417 = 1.0f - 0.000119445511f * fConst0;
		float fConst1418 = std::tan(28681.957f / fConst0);
		float fConst1419 = fConst0 * fConst1418;
		float fConst1420 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst1418 * fConst1404));
		float fConst1421 = 2.0f * fConst1419 - 0.5f * fConst1420 / fConst1419;
		float fConst1422 = fConst7 * fConst1420;
		fConst1423 = 2.0f * fConst1421 / fConst0;
		float fConst1424 = fConst1422 + fConst1423 + 4.0f;
		fConst1425 = 2.0f * fConst1421 / (fConst0 * fConst1424);
		fConst1426 = 0.0f - fConst1425;
		fConst1427 = 1.0f / fConst1424;
		fConst1428 = 2.0f * fConst1422 + -8.0f;
		fConst1429 = fConst1422 + 4.0f - fConst1423;
		fConst1430 = 8869.84375f / fConst0;
		fConst1431 = 1.0f - 0.000112741553f * fConst0;
		float fConst1432 = std::tan(30387.4746f / fConst0);
		float fConst1433 = fConst0 * fConst1432;
		float fConst1434 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst1432 * fConst1418));
		float fConst1435 = 2.0f * fConst1433 - 0.5f * fConst1434 / fConst1433;
		float fConst1436 = fConst7 * fConst1434;
		fConst1437 = 2.0f * fConst1435 / fConst0;
		float fConst1438 = fConst1436 + fConst1437 + 4.0f;
		fConst1439 = 2.0f * fConst1435 / (fConst0 * fConst1438);
		fConst1440 = 0.0f - fConst1439;
		fConst1441 = 1.0f / fConst1438;
		fConst1442 = 2.0f * fConst1436 + -8.0f;
		fConst1443 = fConst1436 + 4.0f - fConst1437;
		fConst1444 = 9397.27246f / fConst0;
		fConst1445 = 1.0f - 0.000106413856f * fConst0;
		float fConst1446 = std::tan(32194.4082f / fConst0);
		float fConst1447 = fConst0 * fConst1446;
		float fConst1448 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst1446 * fConst1432));
		float fConst1449 = 2.0f * fConst1447 - 0.5f * fConst1448 / fConst1447;
		float fConst1450 = fConst7 * fConst1448;
		fConst1451 = 2.0f * fConst1449 / fConst0;
		float fConst1452 = fConst1450 + fConst1451 + 4.0f;
		fConst1453 = 2.0f * fConst1449 / (fConst0 * fConst1452);
		fConst1454 = 0.0f - fConst1453;
		fConst1455 = 1.0f / fConst1452;
		fConst1456 = 2.0f * fConst1450 + -8.0f;
		fConst1457 = fConst1450 + 4.0f - fConst1451;
		fConst1458 = 9956.06348f / fConst0;
		fConst1459 = 1.0f - 0.000100441306f * fConst0;
		float fConst1460 = std::tan(34108.7891f / fConst0);
		float fConst1461 = fConst0 * fConst1460;
		float fConst1462 = mydsp_faustpower2_f(std::sqrt(4.0f * fConst3 * fConst1460 * fConst1446));
		float fConst1463 = 2.0f * fConst1461 - 0.5f * fConst1462 / fConst1461;
		float fConst1464 = fConst7 * fConst1462;
		fConst1465 = 2.0f * fConst1463 / fConst0;
		float fConst1466 = fConst1464 + fConst1465 + 4.0f;
		fConst1467 = 2.0f * fConst1463 / (fConst0 * fConst1466);
		fConst1468 = 0.0f - fConst1467;
		fConst1469 = 1.0f / fConst1466;
		fConst1470 = 2.0f * fConst1464 + -8.0f;
		fConst1471 = fConst1464 + 4.0f - fConst1465;
		fConst1472 = 10548.082f / fConst0;
		fConst1473 = 1.0f - 9.48039669e-05f * fConst0;
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(0.01f);
		fHslider1 = FAUSTFLOAT(0.001f);
		fHslider2 = FAUSTFLOAT(0.10000000000000001f);
		fHslider3 = FAUSTFLOAT(0.10000000000000001f);
	}
	
	virtual void instanceClear() {
		IOTA0 = 0;
		for (int l0 = 0; l0 < 3; l0 = l0 + 1) {
			fRec6[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 3; l1 = l1 + 1) {
			fRec5[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 3; l2 = l2 + 1) {
			fRec4[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 3; l3 = l3 + 1) {
			fRec3[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 2; l4 = l4 + 1) {
			fVec0[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec2[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 32768; l6 = l6 + 1) {
			fRec1[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			fRec0[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			fRec7[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 3; l9 = l9 + 1) {
			fRec15[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 3; l10 = l10 + 1) {
			fRec14[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 3; l11 = l11 + 1) {
			fRec13[l11] = 0.0f;
		}
		for (int l12 = 0; l12 < 3; l12 = l12 + 1) {
			fRec12[l12] = 0.0f;
		}
		for (int l13 = 0; l13 < 2; l13 = l13 + 1) {
			fVec1[l13] = 0.0f;
		}
		for (int l14 = 0; l14 < 2; l14 = l14 + 1) {
			fRec11[l14] = 0.0f;
		}
		for (int l15 = 0; l15 < 32768; l15 = l15 + 1) {
			fRec10[l15] = 0.0f;
		}
		for (int l16 = 0; l16 < 2; l16 = l16 + 1) {
			fRec9[l16] = 0.0f;
		}
		for (int l17 = 0; l17 < 2; l17 = l17 + 1) {
			fRec16[l17] = 0.0f;
		}
		for (int l18 = 0; l18 < 3; l18 = l18 + 1) {
			fRec24[l18] = 0.0f;
		}
		for (int l19 = 0; l19 < 3; l19 = l19 + 1) {
			fRec23[l19] = 0.0f;
		}
		for (int l20 = 0; l20 < 3; l20 = l20 + 1) {
			fRec22[l20] = 0.0f;
		}
		for (int l21 = 0; l21 < 3; l21 = l21 + 1) {
			fRec21[l21] = 0.0f;
		}
		for (int l22 = 0; l22 < 2; l22 = l22 + 1) {
			fVec2[l22] = 0.0f;
		}
		for (int l23 = 0; l23 < 2; l23 = l23 + 1) {
			fRec20[l23] = 0.0f;
		}
		for (int l24 = 0; l24 < 32768; l24 = l24 + 1) {
			fRec19[l24] = 0.0f;
		}
		for (int l25 = 0; l25 < 2; l25 = l25 + 1) {
			fRec18[l25] = 0.0f;
		}
		for (int l26 = 0; l26 < 2; l26 = l26 + 1) {
			fRec25[l26] = 0.0f;
		}
		for (int l27 = 0; l27 < 3; l27 = l27 + 1) {
			fRec33[l27] = 0.0f;
		}
		for (int l28 = 0; l28 < 3; l28 = l28 + 1) {
			fRec32[l28] = 0.0f;
		}
		for (int l29 = 0; l29 < 3; l29 = l29 + 1) {
			fRec31[l29] = 0.0f;
		}
		for (int l30 = 0; l30 < 3; l30 = l30 + 1) {
			fRec30[l30] = 0.0f;
		}
		for (int l31 = 0; l31 < 2; l31 = l31 + 1) {
			fVec3[l31] = 0.0f;
		}
		for (int l32 = 0; l32 < 2; l32 = l32 + 1) {
			fRec29[l32] = 0.0f;
		}
		for (int l33 = 0; l33 < 32768; l33 = l33 + 1) {
			fRec28[l33] = 0.0f;
		}
		for (int l34 = 0; l34 < 2; l34 = l34 + 1) {
			fRec27[l34] = 0.0f;
		}
		for (int l35 = 0; l35 < 2; l35 = l35 + 1) {
			fRec34[l35] = 0.0f;
		}
		for (int l36 = 0; l36 < 3; l36 = l36 + 1) {
			fRec42[l36] = 0.0f;
		}
		for (int l37 = 0; l37 < 3; l37 = l37 + 1) {
			fRec41[l37] = 0.0f;
		}
		for (int l38 = 0; l38 < 3; l38 = l38 + 1) {
			fRec40[l38] = 0.0f;
		}
		for (int l39 = 0; l39 < 3; l39 = l39 + 1) {
			fRec39[l39] = 0.0f;
		}
		for (int l40 = 0; l40 < 2; l40 = l40 + 1) {
			fVec4[l40] = 0.0f;
		}
		for (int l41 = 0; l41 < 2; l41 = l41 + 1) {
			fRec38[l41] = 0.0f;
		}
		for (int l42 = 0; l42 < 32768; l42 = l42 + 1) {
			fRec37[l42] = 0.0f;
		}
		for (int l43 = 0; l43 < 2; l43 = l43 + 1) {
			fRec36[l43] = 0.0f;
		}
		for (int l44 = 0; l44 < 2; l44 = l44 + 1) {
			fRec43[l44] = 0.0f;
		}
		for (int l45 = 0; l45 < 3; l45 = l45 + 1) {
			fRec51[l45] = 0.0f;
		}
		for (int l46 = 0; l46 < 3; l46 = l46 + 1) {
			fRec50[l46] = 0.0f;
		}
		for (int l47 = 0; l47 < 3; l47 = l47 + 1) {
			fRec49[l47] = 0.0f;
		}
		for (int l48 = 0; l48 < 3; l48 = l48 + 1) {
			fRec48[l48] = 0.0f;
		}
		for (int l49 = 0; l49 < 2; l49 = l49 + 1) {
			fVec5[l49] = 0.0f;
		}
		for (int l50 = 0; l50 < 2; l50 = l50 + 1) {
			fRec47[l50] = 0.0f;
		}
		for (int l51 = 0; l51 < 32768; l51 = l51 + 1) {
			fRec46[l51] = 0.0f;
		}
		for (int l52 = 0; l52 < 2; l52 = l52 + 1) {
			fRec45[l52] = 0.0f;
		}
		for (int l53 = 0; l53 < 2; l53 = l53 + 1) {
			fRec52[l53] = 0.0f;
		}
		for (int l54 = 0; l54 < 3; l54 = l54 + 1) {
			fRec60[l54] = 0.0f;
		}
		for (int l55 = 0; l55 < 3; l55 = l55 + 1) {
			fRec59[l55] = 0.0f;
		}
		for (int l56 = 0; l56 < 3; l56 = l56 + 1) {
			fRec58[l56] = 0.0f;
		}
		for (int l57 = 0; l57 < 3; l57 = l57 + 1) {
			fRec57[l57] = 0.0f;
		}
		for (int l58 = 0; l58 < 2; l58 = l58 + 1) {
			fVec6[l58] = 0.0f;
		}
		for (int l59 = 0; l59 < 2; l59 = l59 + 1) {
			fRec56[l59] = 0.0f;
		}
		for (int l60 = 0; l60 < 32768; l60 = l60 + 1) {
			fRec55[l60] = 0.0f;
		}
		for (int l61 = 0; l61 < 2; l61 = l61 + 1) {
			fRec54[l61] = 0.0f;
		}
		for (int l62 = 0; l62 < 2; l62 = l62 + 1) {
			fRec61[l62] = 0.0f;
		}
		for (int l63 = 0; l63 < 3; l63 = l63 + 1) {
			fRec69[l63] = 0.0f;
		}
		for (int l64 = 0; l64 < 3; l64 = l64 + 1) {
			fRec68[l64] = 0.0f;
		}
		for (int l65 = 0; l65 < 3; l65 = l65 + 1) {
			fRec67[l65] = 0.0f;
		}
		for (int l66 = 0; l66 < 3; l66 = l66 + 1) {
			fRec66[l66] = 0.0f;
		}
		for (int l67 = 0; l67 < 2; l67 = l67 + 1) {
			fVec7[l67] = 0.0f;
		}
		for (int l68 = 0; l68 < 2; l68 = l68 + 1) {
			fRec65[l68] = 0.0f;
		}
		for (int l69 = 0; l69 < 32768; l69 = l69 + 1) {
			fRec64[l69] = 0.0f;
		}
		for (int l70 = 0; l70 < 2; l70 = l70 + 1) {
			fRec63[l70] = 0.0f;
		}
		for (int l71 = 0; l71 < 2; l71 = l71 + 1) {
			fRec70[l71] = 0.0f;
		}
		for (int l72 = 0; l72 < 3; l72 = l72 + 1) {
			fRec78[l72] = 0.0f;
		}
		for (int l73 = 0; l73 < 3; l73 = l73 + 1) {
			fRec77[l73] = 0.0f;
		}
		for (int l74 = 0; l74 < 3; l74 = l74 + 1) {
			fRec76[l74] = 0.0f;
		}
		for (int l75 = 0; l75 < 3; l75 = l75 + 1) {
			fRec75[l75] = 0.0f;
		}
		for (int l76 = 0; l76 < 2; l76 = l76 + 1) {
			fVec8[l76] = 0.0f;
		}
		for (int l77 = 0; l77 < 2; l77 = l77 + 1) {
			fRec74[l77] = 0.0f;
		}
		for (int l78 = 0; l78 < 32768; l78 = l78 + 1) {
			fRec73[l78] = 0.0f;
		}
		for (int l79 = 0; l79 < 2; l79 = l79 + 1) {
			fRec72[l79] = 0.0f;
		}
		for (int l80 = 0; l80 < 2; l80 = l80 + 1) {
			fRec79[l80] = 0.0f;
		}
		for (int l81 = 0; l81 < 3; l81 = l81 + 1) {
			fRec87[l81] = 0.0f;
		}
		for (int l82 = 0; l82 < 3; l82 = l82 + 1) {
			fRec86[l82] = 0.0f;
		}
		for (int l83 = 0; l83 < 3; l83 = l83 + 1) {
			fRec85[l83] = 0.0f;
		}
		for (int l84 = 0; l84 < 3; l84 = l84 + 1) {
			fRec84[l84] = 0.0f;
		}
		for (int l85 = 0; l85 < 2; l85 = l85 + 1) {
			fVec9[l85] = 0.0f;
		}
		for (int l86 = 0; l86 < 2; l86 = l86 + 1) {
			fRec83[l86] = 0.0f;
		}
		for (int l87 = 0; l87 < 32768; l87 = l87 + 1) {
			fRec82[l87] = 0.0f;
		}
		for (int l88 = 0; l88 < 2; l88 = l88 + 1) {
			fRec81[l88] = 0.0f;
		}
		for (int l89 = 0; l89 < 2; l89 = l89 + 1) {
			fRec88[l89] = 0.0f;
		}
		for (int l90 = 0; l90 < 3; l90 = l90 + 1) {
			fRec96[l90] = 0.0f;
		}
		for (int l91 = 0; l91 < 3; l91 = l91 + 1) {
			fRec95[l91] = 0.0f;
		}
		for (int l92 = 0; l92 < 3; l92 = l92 + 1) {
			fRec94[l92] = 0.0f;
		}
		for (int l93 = 0; l93 < 3; l93 = l93 + 1) {
			fRec93[l93] = 0.0f;
		}
		for (int l94 = 0; l94 < 2; l94 = l94 + 1) {
			fVec10[l94] = 0.0f;
		}
		for (int l95 = 0; l95 < 2; l95 = l95 + 1) {
			fRec92[l95] = 0.0f;
		}
		for (int l96 = 0; l96 < 32768; l96 = l96 + 1) {
			fRec91[l96] = 0.0f;
		}
		for (int l97 = 0; l97 < 2; l97 = l97 + 1) {
			fRec90[l97] = 0.0f;
		}
		for (int l98 = 0; l98 < 2; l98 = l98 + 1) {
			fRec97[l98] = 0.0f;
		}
		for (int l99 = 0; l99 < 3; l99 = l99 + 1) {
			fRec105[l99] = 0.0f;
		}
		for (int l100 = 0; l100 < 3; l100 = l100 + 1) {
			fRec104[l100] = 0.0f;
		}
		for (int l101 = 0; l101 < 3; l101 = l101 + 1) {
			fRec103[l101] = 0.0f;
		}
		for (int l102 = 0; l102 < 3; l102 = l102 + 1) {
			fRec102[l102] = 0.0f;
		}
		for (int l103 = 0; l103 < 2; l103 = l103 + 1) {
			fVec11[l103] = 0.0f;
		}
		for (int l104 = 0; l104 < 2; l104 = l104 + 1) {
			fRec101[l104] = 0.0f;
		}
		for (int l105 = 0; l105 < 32768; l105 = l105 + 1) {
			fRec100[l105] = 0.0f;
		}
		for (int l106 = 0; l106 < 2; l106 = l106 + 1) {
			fRec99[l106] = 0.0f;
		}
		for (int l107 = 0; l107 < 2; l107 = l107 + 1) {
			fRec106[l107] = 0.0f;
		}
		for (int l108 = 0; l108 < 3; l108 = l108 + 1) {
			fRec114[l108] = 0.0f;
		}
		for (int l109 = 0; l109 < 3; l109 = l109 + 1) {
			fRec113[l109] = 0.0f;
		}
		for (int l110 = 0; l110 < 3; l110 = l110 + 1) {
			fRec112[l110] = 0.0f;
		}
		for (int l111 = 0; l111 < 3; l111 = l111 + 1) {
			fRec111[l111] = 0.0f;
		}
		for (int l112 = 0; l112 < 2; l112 = l112 + 1) {
			fVec12[l112] = 0.0f;
		}
		for (int l113 = 0; l113 < 2; l113 = l113 + 1) {
			fRec110[l113] = 0.0f;
		}
		for (int l114 = 0; l114 < 32768; l114 = l114 + 1) {
			fRec109[l114] = 0.0f;
		}
		for (int l115 = 0; l115 < 2; l115 = l115 + 1) {
			fRec108[l115] = 0.0f;
		}
		for (int l116 = 0; l116 < 2; l116 = l116 + 1) {
			fRec115[l116] = 0.0f;
		}
		for (int l117 = 0; l117 < 3; l117 = l117 + 1) {
			fRec123[l117] = 0.0f;
		}
		for (int l118 = 0; l118 < 3; l118 = l118 + 1) {
			fRec122[l118] = 0.0f;
		}
		for (int l119 = 0; l119 < 3; l119 = l119 + 1) {
			fRec121[l119] = 0.0f;
		}
		for (int l120 = 0; l120 < 3; l120 = l120 + 1) {
			fRec120[l120] = 0.0f;
		}
		for (int l121 = 0; l121 < 2; l121 = l121 + 1) {
			fVec13[l121] = 0.0f;
		}
		for (int l122 = 0; l122 < 2; l122 = l122 + 1) {
			fRec119[l122] = 0.0f;
		}
		for (int l123 = 0; l123 < 32768; l123 = l123 + 1) {
			fRec118[l123] = 0.0f;
		}
		for (int l124 = 0; l124 < 2; l124 = l124 + 1) {
			fRec117[l124] = 0.0f;
		}
		for (int l125 = 0; l125 < 2; l125 = l125 + 1) {
			fRec124[l125] = 0.0f;
		}
		for (int l126 = 0; l126 < 3; l126 = l126 + 1) {
			fRec132[l126] = 0.0f;
		}
		for (int l127 = 0; l127 < 3; l127 = l127 + 1) {
			fRec131[l127] = 0.0f;
		}
		for (int l128 = 0; l128 < 3; l128 = l128 + 1) {
			fRec130[l128] = 0.0f;
		}
		for (int l129 = 0; l129 < 3; l129 = l129 + 1) {
			fRec129[l129] = 0.0f;
		}
		for (int l130 = 0; l130 < 2; l130 = l130 + 1) {
			fVec14[l130] = 0.0f;
		}
		for (int l131 = 0; l131 < 2; l131 = l131 + 1) {
			fRec128[l131] = 0.0f;
		}
		for (int l132 = 0; l132 < 32768; l132 = l132 + 1) {
			fRec127[l132] = 0.0f;
		}
		for (int l133 = 0; l133 < 2; l133 = l133 + 1) {
			fRec126[l133] = 0.0f;
		}
		for (int l134 = 0; l134 < 2; l134 = l134 + 1) {
			fRec133[l134] = 0.0f;
		}
		for (int l135 = 0; l135 < 3; l135 = l135 + 1) {
			fRec141[l135] = 0.0f;
		}
		for (int l136 = 0; l136 < 3; l136 = l136 + 1) {
			fRec140[l136] = 0.0f;
		}
		for (int l137 = 0; l137 < 3; l137 = l137 + 1) {
			fRec139[l137] = 0.0f;
		}
		for (int l138 = 0; l138 < 3; l138 = l138 + 1) {
			fRec138[l138] = 0.0f;
		}
		for (int l139 = 0; l139 < 2; l139 = l139 + 1) {
			fVec15[l139] = 0.0f;
		}
		for (int l140 = 0; l140 < 2; l140 = l140 + 1) {
			fRec137[l140] = 0.0f;
		}
		for (int l141 = 0; l141 < 32768; l141 = l141 + 1) {
			fRec136[l141] = 0.0f;
		}
		for (int l142 = 0; l142 < 2; l142 = l142 + 1) {
			fRec135[l142] = 0.0f;
		}
		for (int l143 = 0; l143 < 2; l143 = l143 + 1) {
			fRec142[l143] = 0.0f;
		}
		for (int l144 = 0; l144 < 3; l144 = l144 + 1) {
			fRec150[l144] = 0.0f;
		}
		for (int l145 = 0; l145 < 3; l145 = l145 + 1) {
			fRec149[l145] = 0.0f;
		}
		for (int l146 = 0; l146 < 3; l146 = l146 + 1) {
			fRec148[l146] = 0.0f;
		}
		for (int l147 = 0; l147 < 3; l147 = l147 + 1) {
			fRec147[l147] = 0.0f;
		}
		for (int l148 = 0; l148 < 2; l148 = l148 + 1) {
			fVec16[l148] = 0.0f;
		}
		for (int l149 = 0; l149 < 2; l149 = l149 + 1) {
			fRec146[l149] = 0.0f;
		}
		for (int l150 = 0; l150 < 32768; l150 = l150 + 1) {
			fRec145[l150] = 0.0f;
		}
		for (int l151 = 0; l151 < 2; l151 = l151 + 1) {
			fRec144[l151] = 0.0f;
		}
		for (int l152 = 0; l152 < 2; l152 = l152 + 1) {
			fRec151[l152] = 0.0f;
		}
		for (int l153 = 0; l153 < 3; l153 = l153 + 1) {
			fRec159[l153] = 0.0f;
		}
		for (int l154 = 0; l154 < 3; l154 = l154 + 1) {
			fRec158[l154] = 0.0f;
		}
		for (int l155 = 0; l155 < 3; l155 = l155 + 1) {
			fRec157[l155] = 0.0f;
		}
		for (int l156 = 0; l156 < 3; l156 = l156 + 1) {
			fRec156[l156] = 0.0f;
		}
		for (int l157 = 0; l157 < 2; l157 = l157 + 1) {
			fVec17[l157] = 0.0f;
		}
		for (int l158 = 0; l158 < 2; l158 = l158 + 1) {
			fRec155[l158] = 0.0f;
		}
		for (int l159 = 0; l159 < 32768; l159 = l159 + 1) {
			fRec154[l159] = 0.0f;
		}
		for (int l160 = 0; l160 < 2; l160 = l160 + 1) {
			fRec153[l160] = 0.0f;
		}
		for (int l161 = 0; l161 < 2; l161 = l161 + 1) {
			fRec160[l161] = 0.0f;
		}
		for (int l162 = 0; l162 < 3; l162 = l162 + 1) {
			fRec168[l162] = 0.0f;
		}
		for (int l163 = 0; l163 < 3; l163 = l163 + 1) {
			fRec167[l163] = 0.0f;
		}
		for (int l164 = 0; l164 < 3; l164 = l164 + 1) {
			fRec166[l164] = 0.0f;
		}
		for (int l165 = 0; l165 < 3; l165 = l165 + 1) {
			fRec165[l165] = 0.0f;
		}
		for (int l166 = 0; l166 < 2; l166 = l166 + 1) {
			fVec18[l166] = 0.0f;
		}
		for (int l167 = 0; l167 < 2; l167 = l167 + 1) {
			fRec164[l167] = 0.0f;
		}
		for (int l168 = 0; l168 < 32768; l168 = l168 + 1) {
			fRec163[l168] = 0.0f;
		}
		for (int l169 = 0; l169 < 2; l169 = l169 + 1) {
			fRec162[l169] = 0.0f;
		}
		for (int l170 = 0; l170 < 2; l170 = l170 + 1) {
			fRec169[l170] = 0.0f;
		}
		for (int l171 = 0; l171 < 3; l171 = l171 + 1) {
			fRec177[l171] = 0.0f;
		}
		for (int l172 = 0; l172 < 3; l172 = l172 + 1) {
			fRec176[l172] = 0.0f;
		}
		for (int l173 = 0; l173 < 3; l173 = l173 + 1) {
			fRec175[l173] = 0.0f;
		}
		for (int l174 = 0; l174 < 3; l174 = l174 + 1) {
			fRec174[l174] = 0.0f;
		}
		for (int l175 = 0; l175 < 2; l175 = l175 + 1) {
			fVec19[l175] = 0.0f;
		}
		for (int l176 = 0; l176 < 2; l176 = l176 + 1) {
			fRec173[l176] = 0.0f;
		}
		for (int l177 = 0; l177 < 32768; l177 = l177 + 1) {
			fRec172[l177] = 0.0f;
		}
		for (int l178 = 0; l178 < 2; l178 = l178 + 1) {
			fRec171[l178] = 0.0f;
		}
		for (int l179 = 0; l179 < 2; l179 = l179 + 1) {
			fRec178[l179] = 0.0f;
		}
		for (int l180 = 0; l180 < 3; l180 = l180 + 1) {
			fRec186[l180] = 0.0f;
		}
		for (int l181 = 0; l181 < 3; l181 = l181 + 1) {
			fRec185[l181] = 0.0f;
		}
		for (int l182 = 0; l182 < 3; l182 = l182 + 1) {
			fRec184[l182] = 0.0f;
		}
		for (int l183 = 0; l183 < 3; l183 = l183 + 1) {
			fRec183[l183] = 0.0f;
		}
		for (int l184 = 0; l184 < 2; l184 = l184 + 1) {
			fVec20[l184] = 0.0f;
		}
		for (int l185 = 0; l185 < 2; l185 = l185 + 1) {
			fRec182[l185] = 0.0f;
		}
		for (int l186 = 0; l186 < 32768; l186 = l186 + 1) {
			fRec181[l186] = 0.0f;
		}
		for (int l187 = 0; l187 < 2; l187 = l187 + 1) {
			fRec180[l187] = 0.0f;
		}
		for (int l188 = 0; l188 < 2; l188 = l188 + 1) {
			fRec187[l188] = 0.0f;
		}
		for (int l189 = 0; l189 < 3; l189 = l189 + 1) {
			fRec195[l189] = 0.0f;
		}
		for (int l190 = 0; l190 < 3; l190 = l190 + 1) {
			fRec194[l190] = 0.0f;
		}
		for (int l191 = 0; l191 < 3; l191 = l191 + 1) {
			fRec193[l191] = 0.0f;
		}
		for (int l192 = 0; l192 < 3; l192 = l192 + 1) {
			fRec192[l192] = 0.0f;
		}
		for (int l193 = 0; l193 < 2; l193 = l193 + 1) {
			fVec21[l193] = 0.0f;
		}
		for (int l194 = 0; l194 < 2; l194 = l194 + 1) {
			fRec191[l194] = 0.0f;
		}
		for (int l195 = 0; l195 < 32768; l195 = l195 + 1) {
			fRec190[l195] = 0.0f;
		}
		for (int l196 = 0; l196 < 2; l196 = l196 + 1) {
			fRec189[l196] = 0.0f;
		}
		for (int l197 = 0; l197 < 2; l197 = l197 + 1) {
			fRec196[l197] = 0.0f;
		}
		for (int l198 = 0; l198 < 3; l198 = l198 + 1) {
			fRec204[l198] = 0.0f;
		}
		for (int l199 = 0; l199 < 3; l199 = l199 + 1) {
			fRec203[l199] = 0.0f;
		}
		for (int l200 = 0; l200 < 3; l200 = l200 + 1) {
			fRec202[l200] = 0.0f;
		}
		for (int l201 = 0; l201 < 3; l201 = l201 + 1) {
			fRec201[l201] = 0.0f;
		}
		for (int l202 = 0; l202 < 2; l202 = l202 + 1) {
			fVec22[l202] = 0.0f;
		}
		for (int l203 = 0; l203 < 2; l203 = l203 + 1) {
			fRec200[l203] = 0.0f;
		}
		for (int l204 = 0; l204 < 32768; l204 = l204 + 1) {
			fRec199[l204] = 0.0f;
		}
		for (int l205 = 0; l205 < 2; l205 = l205 + 1) {
			fRec198[l205] = 0.0f;
		}
		for (int l206 = 0; l206 < 2; l206 = l206 + 1) {
			fRec205[l206] = 0.0f;
		}
		for (int l207 = 0; l207 < 3; l207 = l207 + 1) {
			fRec213[l207] = 0.0f;
		}
		for (int l208 = 0; l208 < 3; l208 = l208 + 1) {
			fRec212[l208] = 0.0f;
		}
		for (int l209 = 0; l209 < 3; l209 = l209 + 1) {
			fRec211[l209] = 0.0f;
		}
		for (int l210 = 0; l210 < 3; l210 = l210 + 1) {
			fRec210[l210] = 0.0f;
		}
		for (int l211 = 0; l211 < 2; l211 = l211 + 1) {
			fVec23[l211] = 0.0f;
		}
		for (int l212 = 0; l212 < 2; l212 = l212 + 1) {
			fRec209[l212] = 0.0f;
		}
		for (int l213 = 0; l213 < 32768; l213 = l213 + 1) {
			fRec208[l213] = 0.0f;
		}
		for (int l214 = 0; l214 < 2; l214 = l214 + 1) {
			fRec207[l214] = 0.0f;
		}
		for (int l215 = 0; l215 < 2; l215 = l215 + 1) {
			fRec214[l215] = 0.0f;
		}
		for (int l216 = 0; l216 < 3; l216 = l216 + 1) {
			fRec222[l216] = 0.0f;
		}
		for (int l217 = 0; l217 < 3; l217 = l217 + 1) {
			fRec221[l217] = 0.0f;
		}
		for (int l218 = 0; l218 < 3; l218 = l218 + 1) {
			fRec220[l218] = 0.0f;
		}
		for (int l219 = 0; l219 < 3; l219 = l219 + 1) {
			fRec219[l219] = 0.0f;
		}
		for (int l220 = 0; l220 < 2; l220 = l220 + 1) {
			fVec24[l220] = 0.0f;
		}
		for (int l221 = 0; l221 < 2; l221 = l221 + 1) {
			fRec218[l221] = 0.0f;
		}
		for (int l222 = 0; l222 < 32768; l222 = l222 + 1) {
			fRec217[l222] = 0.0f;
		}
		for (int l223 = 0; l223 < 2; l223 = l223 + 1) {
			fRec216[l223] = 0.0f;
		}
		for (int l224 = 0; l224 < 2; l224 = l224 + 1) {
			fRec223[l224] = 0.0f;
		}
		for (int l225 = 0; l225 < 3; l225 = l225 + 1) {
			fRec231[l225] = 0.0f;
		}
		for (int l226 = 0; l226 < 3; l226 = l226 + 1) {
			fRec230[l226] = 0.0f;
		}
		for (int l227 = 0; l227 < 3; l227 = l227 + 1) {
			fRec229[l227] = 0.0f;
		}
		for (int l228 = 0; l228 < 3; l228 = l228 + 1) {
			fRec228[l228] = 0.0f;
		}
		for (int l229 = 0; l229 < 2; l229 = l229 + 1) {
			fVec25[l229] = 0.0f;
		}
		for (int l230 = 0; l230 < 2; l230 = l230 + 1) {
			fRec227[l230] = 0.0f;
		}
		for (int l231 = 0; l231 < 32768; l231 = l231 + 1) {
			fRec226[l231] = 0.0f;
		}
		for (int l232 = 0; l232 < 2; l232 = l232 + 1) {
			fRec225[l232] = 0.0f;
		}
		for (int l233 = 0; l233 < 2; l233 = l233 + 1) {
			fRec232[l233] = 0.0f;
		}
		for (int l234 = 0; l234 < 3; l234 = l234 + 1) {
			fRec240[l234] = 0.0f;
		}
		for (int l235 = 0; l235 < 3; l235 = l235 + 1) {
			fRec239[l235] = 0.0f;
		}
		for (int l236 = 0; l236 < 3; l236 = l236 + 1) {
			fRec238[l236] = 0.0f;
		}
		for (int l237 = 0; l237 < 3; l237 = l237 + 1) {
			fRec237[l237] = 0.0f;
		}
		for (int l238 = 0; l238 < 2; l238 = l238 + 1) {
			fVec26[l238] = 0.0f;
		}
		for (int l239 = 0; l239 < 2; l239 = l239 + 1) {
			fRec236[l239] = 0.0f;
		}
		for (int l240 = 0; l240 < 32768; l240 = l240 + 1) {
			fRec235[l240] = 0.0f;
		}
		for (int l241 = 0; l241 < 2; l241 = l241 + 1) {
			fRec234[l241] = 0.0f;
		}
		for (int l242 = 0; l242 < 2; l242 = l242 + 1) {
			fRec241[l242] = 0.0f;
		}
		for (int l243 = 0; l243 < 3; l243 = l243 + 1) {
			fRec249[l243] = 0.0f;
		}
		for (int l244 = 0; l244 < 3; l244 = l244 + 1) {
			fRec248[l244] = 0.0f;
		}
		for (int l245 = 0; l245 < 3; l245 = l245 + 1) {
			fRec247[l245] = 0.0f;
		}
		for (int l246 = 0; l246 < 3; l246 = l246 + 1) {
			fRec246[l246] = 0.0f;
		}
		for (int l247 = 0; l247 < 2; l247 = l247 + 1) {
			fVec27[l247] = 0.0f;
		}
		for (int l248 = 0; l248 < 2; l248 = l248 + 1) {
			fRec245[l248] = 0.0f;
		}
		for (int l249 = 0; l249 < 32768; l249 = l249 + 1) {
			fRec244[l249] = 0.0f;
		}
		for (int l250 = 0; l250 < 2; l250 = l250 + 1) {
			fRec243[l250] = 0.0f;
		}
		for (int l251 = 0; l251 < 2; l251 = l251 + 1) {
			fRec250[l251] = 0.0f;
		}
		for (int l252 = 0; l252 < 3; l252 = l252 + 1) {
			fRec258[l252] = 0.0f;
		}
		for (int l253 = 0; l253 < 3; l253 = l253 + 1) {
			fRec257[l253] = 0.0f;
		}
		for (int l254 = 0; l254 < 3; l254 = l254 + 1) {
			fRec256[l254] = 0.0f;
		}
		for (int l255 = 0; l255 < 3; l255 = l255 + 1) {
			fRec255[l255] = 0.0f;
		}
		for (int l256 = 0; l256 < 2; l256 = l256 + 1) {
			fVec28[l256] = 0.0f;
		}
		for (int l257 = 0; l257 < 2; l257 = l257 + 1) {
			fRec254[l257] = 0.0f;
		}
		for (int l258 = 0; l258 < 32768; l258 = l258 + 1) {
			fRec253[l258] = 0.0f;
		}
		for (int l259 = 0; l259 < 2; l259 = l259 + 1) {
			fRec252[l259] = 0.0f;
		}
		for (int l260 = 0; l260 < 2; l260 = l260 + 1) {
			fRec259[l260] = 0.0f;
		}
		for (int l261 = 0; l261 < 3; l261 = l261 + 1) {
			fRec267[l261] = 0.0f;
		}
		for (int l262 = 0; l262 < 3; l262 = l262 + 1) {
			fRec266[l262] = 0.0f;
		}
		for (int l263 = 0; l263 < 3; l263 = l263 + 1) {
			fRec265[l263] = 0.0f;
		}
		for (int l264 = 0; l264 < 3; l264 = l264 + 1) {
			fRec264[l264] = 0.0f;
		}
		for (int l265 = 0; l265 < 2; l265 = l265 + 1) {
			fVec29[l265] = 0.0f;
		}
		for (int l266 = 0; l266 < 2; l266 = l266 + 1) {
			fRec263[l266] = 0.0f;
		}
		for (int l267 = 0; l267 < 32768; l267 = l267 + 1) {
			fRec262[l267] = 0.0f;
		}
		for (int l268 = 0; l268 < 2; l268 = l268 + 1) {
			fRec261[l268] = 0.0f;
		}
		for (int l269 = 0; l269 < 2; l269 = l269 + 1) {
			fRec268[l269] = 0.0f;
		}
		for (int l270 = 0; l270 < 3; l270 = l270 + 1) {
			fRec276[l270] = 0.0f;
		}
		for (int l271 = 0; l271 < 3; l271 = l271 + 1) {
			fRec275[l271] = 0.0f;
		}
		for (int l272 = 0; l272 < 3; l272 = l272 + 1) {
			fRec274[l272] = 0.0f;
		}
		for (int l273 = 0; l273 < 3; l273 = l273 + 1) {
			fRec273[l273] = 0.0f;
		}
		for (int l274 = 0; l274 < 2; l274 = l274 + 1) {
			fVec30[l274] = 0.0f;
		}
		for (int l275 = 0; l275 < 2; l275 = l275 + 1) {
			fRec272[l275] = 0.0f;
		}
		for (int l276 = 0; l276 < 32768; l276 = l276 + 1) {
			fRec271[l276] = 0.0f;
		}
		for (int l277 = 0; l277 < 2; l277 = l277 + 1) {
			fRec270[l277] = 0.0f;
		}
		for (int l278 = 0; l278 < 2; l278 = l278 + 1) {
			fRec277[l278] = 0.0f;
		}
		for (int l279 = 0; l279 < 3; l279 = l279 + 1) {
			fRec285[l279] = 0.0f;
		}
		for (int l280 = 0; l280 < 3; l280 = l280 + 1) {
			fRec284[l280] = 0.0f;
		}
		for (int l281 = 0; l281 < 3; l281 = l281 + 1) {
			fRec283[l281] = 0.0f;
		}
		for (int l282 = 0; l282 < 3; l282 = l282 + 1) {
			fRec282[l282] = 0.0f;
		}
		for (int l283 = 0; l283 < 2; l283 = l283 + 1) {
			fVec31[l283] = 0.0f;
		}
		for (int l284 = 0; l284 < 2; l284 = l284 + 1) {
			fRec281[l284] = 0.0f;
		}
		for (int l285 = 0; l285 < 32768; l285 = l285 + 1) {
			fRec280[l285] = 0.0f;
		}
		for (int l286 = 0; l286 < 2; l286 = l286 + 1) {
			fRec279[l286] = 0.0f;
		}
		for (int l287 = 0; l287 < 2; l287 = l287 + 1) {
			fRec286[l287] = 0.0f;
		}
		for (int l288 = 0; l288 < 3; l288 = l288 + 1) {
			fRec294[l288] = 0.0f;
		}
		for (int l289 = 0; l289 < 3; l289 = l289 + 1) {
			fRec293[l289] = 0.0f;
		}
		for (int l290 = 0; l290 < 3; l290 = l290 + 1) {
			fRec292[l290] = 0.0f;
		}
		for (int l291 = 0; l291 < 3; l291 = l291 + 1) {
			fRec291[l291] = 0.0f;
		}
		for (int l292 = 0; l292 < 2; l292 = l292 + 1) {
			fVec32[l292] = 0.0f;
		}
		for (int l293 = 0; l293 < 2; l293 = l293 + 1) {
			fRec290[l293] = 0.0f;
		}
		for (int l294 = 0; l294 < 32768; l294 = l294 + 1) {
			fRec289[l294] = 0.0f;
		}
		for (int l295 = 0; l295 < 2; l295 = l295 + 1) {
			fRec288[l295] = 0.0f;
		}
		for (int l296 = 0; l296 < 2; l296 = l296 + 1) {
			fRec295[l296] = 0.0f;
		}
		for (int l297 = 0; l297 < 3; l297 = l297 + 1) {
			fRec303[l297] = 0.0f;
		}
		for (int l298 = 0; l298 < 3; l298 = l298 + 1) {
			fRec302[l298] = 0.0f;
		}
		for (int l299 = 0; l299 < 3; l299 = l299 + 1) {
			fRec301[l299] = 0.0f;
		}
		for (int l300 = 0; l300 < 3; l300 = l300 + 1) {
			fRec300[l300] = 0.0f;
		}
		for (int l301 = 0; l301 < 2; l301 = l301 + 1) {
			fVec33[l301] = 0.0f;
		}
		for (int l302 = 0; l302 < 2; l302 = l302 + 1) {
			fRec299[l302] = 0.0f;
		}
		for (int l303 = 0; l303 < 32768; l303 = l303 + 1) {
			fRec298[l303] = 0.0f;
		}
		for (int l304 = 0; l304 < 2; l304 = l304 + 1) {
			fRec297[l304] = 0.0f;
		}
		for (int l305 = 0; l305 < 2; l305 = l305 + 1) {
			fRec304[l305] = 0.0f;
		}
		for (int l306 = 0; l306 < 3; l306 = l306 + 1) {
			fRec312[l306] = 0.0f;
		}
		for (int l307 = 0; l307 < 3; l307 = l307 + 1) {
			fRec311[l307] = 0.0f;
		}
		for (int l308 = 0; l308 < 3; l308 = l308 + 1) {
			fRec310[l308] = 0.0f;
		}
		for (int l309 = 0; l309 < 3; l309 = l309 + 1) {
			fRec309[l309] = 0.0f;
		}
		for (int l310 = 0; l310 < 2; l310 = l310 + 1) {
			fVec34[l310] = 0.0f;
		}
		for (int l311 = 0; l311 < 2; l311 = l311 + 1) {
			fRec308[l311] = 0.0f;
		}
		for (int l312 = 0; l312 < 32768; l312 = l312 + 1) {
			fRec307[l312] = 0.0f;
		}
		for (int l313 = 0; l313 < 2; l313 = l313 + 1) {
			fRec306[l313] = 0.0f;
		}
		for (int l314 = 0; l314 < 2; l314 = l314 + 1) {
			fRec313[l314] = 0.0f;
		}
		for (int l315 = 0; l315 < 3; l315 = l315 + 1) {
			fRec321[l315] = 0.0f;
		}
		for (int l316 = 0; l316 < 3; l316 = l316 + 1) {
			fRec320[l316] = 0.0f;
		}
		for (int l317 = 0; l317 < 3; l317 = l317 + 1) {
			fRec319[l317] = 0.0f;
		}
		for (int l318 = 0; l318 < 3; l318 = l318 + 1) {
			fRec318[l318] = 0.0f;
		}
		for (int l319 = 0; l319 < 2; l319 = l319 + 1) {
			fVec35[l319] = 0.0f;
		}
		for (int l320 = 0; l320 < 2; l320 = l320 + 1) {
			fRec317[l320] = 0.0f;
		}
		for (int l321 = 0; l321 < 32768; l321 = l321 + 1) {
			fRec316[l321] = 0.0f;
		}
		for (int l322 = 0; l322 < 2; l322 = l322 + 1) {
			fRec315[l322] = 0.0f;
		}
		for (int l323 = 0; l323 < 2; l323 = l323 + 1) {
			fRec322[l323] = 0.0f;
		}
		for (int l324 = 0; l324 < 3; l324 = l324 + 1) {
			fRec330[l324] = 0.0f;
		}
		for (int l325 = 0; l325 < 3; l325 = l325 + 1) {
			fRec329[l325] = 0.0f;
		}
		for (int l326 = 0; l326 < 3; l326 = l326 + 1) {
			fRec328[l326] = 0.0f;
		}
		for (int l327 = 0; l327 < 3; l327 = l327 + 1) {
			fRec327[l327] = 0.0f;
		}
		for (int l328 = 0; l328 < 2; l328 = l328 + 1) {
			fVec36[l328] = 0.0f;
		}
		for (int l329 = 0; l329 < 2; l329 = l329 + 1) {
			fRec326[l329] = 0.0f;
		}
		for (int l330 = 0; l330 < 32768; l330 = l330 + 1) {
			fRec325[l330] = 0.0f;
		}
		for (int l331 = 0; l331 < 2; l331 = l331 + 1) {
			fRec324[l331] = 0.0f;
		}
		for (int l332 = 0; l332 < 2; l332 = l332 + 1) {
			fRec331[l332] = 0.0f;
		}
		for (int l333 = 0; l333 < 3; l333 = l333 + 1) {
			fRec339[l333] = 0.0f;
		}
		for (int l334 = 0; l334 < 3; l334 = l334 + 1) {
			fRec338[l334] = 0.0f;
		}
		for (int l335 = 0; l335 < 3; l335 = l335 + 1) {
			fRec337[l335] = 0.0f;
		}
		for (int l336 = 0; l336 < 3; l336 = l336 + 1) {
			fRec336[l336] = 0.0f;
		}
		for (int l337 = 0; l337 < 2; l337 = l337 + 1) {
			fVec37[l337] = 0.0f;
		}
		for (int l338 = 0; l338 < 2; l338 = l338 + 1) {
			fRec335[l338] = 0.0f;
		}
		for (int l339 = 0; l339 < 32768; l339 = l339 + 1) {
			fRec334[l339] = 0.0f;
		}
		for (int l340 = 0; l340 < 2; l340 = l340 + 1) {
			fRec333[l340] = 0.0f;
		}
		for (int l341 = 0; l341 < 2; l341 = l341 + 1) {
			fRec340[l341] = 0.0f;
		}
		for (int l342 = 0; l342 < 3; l342 = l342 + 1) {
			fRec348[l342] = 0.0f;
		}
		for (int l343 = 0; l343 < 3; l343 = l343 + 1) {
			fRec347[l343] = 0.0f;
		}
		for (int l344 = 0; l344 < 3; l344 = l344 + 1) {
			fRec346[l344] = 0.0f;
		}
		for (int l345 = 0; l345 < 3; l345 = l345 + 1) {
			fRec345[l345] = 0.0f;
		}
		for (int l346 = 0; l346 < 2; l346 = l346 + 1) {
			fVec38[l346] = 0.0f;
		}
		for (int l347 = 0; l347 < 2; l347 = l347 + 1) {
			fRec344[l347] = 0.0f;
		}
		for (int l348 = 0; l348 < 32768; l348 = l348 + 1) {
			fRec343[l348] = 0.0f;
		}
		for (int l349 = 0; l349 < 2; l349 = l349 + 1) {
			fRec342[l349] = 0.0f;
		}
		for (int l350 = 0; l350 < 2; l350 = l350 + 1) {
			fRec349[l350] = 0.0f;
		}
		for (int l351 = 0; l351 < 3; l351 = l351 + 1) {
			fRec357[l351] = 0.0f;
		}
		for (int l352 = 0; l352 < 3; l352 = l352 + 1) {
			fRec356[l352] = 0.0f;
		}
		for (int l353 = 0; l353 < 3; l353 = l353 + 1) {
			fRec355[l353] = 0.0f;
		}
		for (int l354 = 0; l354 < 3; l354 = l354 + 1) {
			fRec354[l354] = 0.0f;
		}
		for (int l355 = 0; l355 < 2; l355 = l355 + 1) {
			fVec39[l355] = 0.0f;
		}
		for (int l356 = 0; l356 < 2; l356 = l356 + 1) {
			fRec353[l356] = 0.0f;
		}
		for (int l357 = 0; l357 < 32768; l357 = l357 + 1) {
			fRec352[l357] = 0.0f;
		}
		for (int l358 = 0; l358 < 2; l358 = l358 + 1) {
			fRec351[l358] = 0.0f;
		}
		for (int l359 = 0; l359 < 2; l359 = l359 + 1) {
			fRec358[l359] = 0.0f;
		}
		for (int l360 = 0; l360 < 3; l360 = l360 + 1) {
			fRec366[l360] = 0.0f;
		}
		for (int l361 = 0; l361 < 3; l361 = l361 + 1) {
			fRec365[l361] = 0.0f;
		}
		for (int l362 = 0; l362 < 3; l362 = l362 + 1) {
			fRec364[l362] = 0.0f;
		}
		for (int l363 = 0; l363 < 3; l363 = l363 + 1) {
			fRec363[l363] = 0.0f;
		}
		for (int l364 = 0; l364 < 2; l364 = l364 + 1) {
			fVec40[l364] = 0.0f;
		}
		for (int l365 = 0; l365 < 2; l365 = l365 + 1) {
			fRec362[l365] = 0.0f;
		}
		for (int l366 = 0; l366 < 32768; l366 = l366 + 1) {
			fRec361[l366] = 0.0f;
		}
		for (int l367 = 0; l367 < 2; l367 = l367 + 1) {
			fRec360[l367] = 0.0f;
		}
		for (int l368 = 0; l368 < 2; l368 = l368 + 1) {
			fRec367[l368] = 0.0f;
		}
		for (int l369 = 0; l369 < 3; l369 = l369 + 1) {
			fRec375[l369] = 0.0f;
		}
		for (int l370 = 0; l370 < 3; l370 = l370 + 1) {
			fRec374[l370] = 0.0f;
		}
		for (int l371 = 0; l371 < 3; l371 = l371 + 1) {
			fRec373[l371] = 0.0f;
		}
		for (int l372 = 0; l372 < 3; l372 = l372 + 1) {
			fRec372[l372] = 0.0f;
		}
		for (int l373 = 0; l373 < 2; l373 = l373 + 1) {
			fVec41[l373] = 0.0f;
		}
		for (int l374 = 0; l374 < 2; l374 = l374 + 1) {
			fRec371[l374] = 0.0f;
		}
		for (int l375 = 0; l375 < 32768; l375 = l375 + 1) {
			fRec370[l375] = 0.0f;
		}
		for (int l376 = 0; l376 < 2; l376 = l376 + 1) {
			fRec369[l376] = 0.0f;
		}
		for (int l377 = 0; l377 < 2; l377 = l377 + 1) {
			fRec376[l377] = 0.0f;
		}
		for (int l378 = 0; l378 < 3; l378 = l378 + 1) {
			fRec384[l378] = 0.0f;
		}
		for (int l379 = 0; l379 < 3; l379 = l379 + 1) {
			fRec383[l379] = 0.0f;
		}
		for (int l380 = 0; l380 < 3; l380 = l380 + 1) {
			fRec382[l380] = 0.0f;
		}
		for (int l381 = 0; l381 < 3; l381 = l381 + 1) {
			fRec381[l381] = 0.0f;
		}
		for (int l382 = 0; l382 < 2; l382 = l382 + 1) {
			fVec42[l382] = 0.0f;
		}
		for (int l383 = 0; l383 < 2; l383 = l383 + 1) {
			fRec380[l383] = 0.0f;
		}
		for (int l384 = 0; l384 < 32768; l384 = l384 + 1) {
			fRec379[l384] = 0.0f;
		}
		for (int l385 = 0; l385 < 2; l385 = l385 + 1) {
			fRec378[l385] = 0.0f;
		}
		for (int l386 = 0; l386 < 2; l386 = l386 + 1) {
			fRec385[l386] = 0.0f;
		}
		for (int l387 = 0; l387 < 3; l387 = l387 + 1) {
			fRec393[l387] = 0.0f;
		}
		for (int l388 = 0; l388 < 3; l388 = l388 + 1) {
			fRec392[l388] = 0.0f;
		}
		for (int l389 = 0; l389 < 3; l389 = l389 + 1) {
			fRec391[l389] = 0.0f;
		}
		for (int l390 = 0; l390 < 3; l390 = l390 + 1) {
			fRec390[l390] = 0.0f;
		}
		for (int l391 = 0; l391 < 2; l391 = l391 + 1) {
			fVec43[l391] = 0.0f;
		}
		for (int l392 = 0; l392 < 2; l392 = l392 + 1) {
			fRec389[l392] = 0.0f;
		}
		for (int l393 = 0; l393 < 32768; l393 = l393 + 1) {
			fRec388[l393] = 0.0f;
		}
		for (int l394 = 0; l394 < 2; l394 = l394 + 1) {
			fRec387[l394] = 0.0f;
		}
		for (int l395 = 0; l395 < 2; l395 = l395 + 1) {
			fRec394[l395] = 0.0f;
		}
		for (int l396 = 0; l396 < 3; l396 = l396 + 1) {
			fRec402[l396] = 0.0f;
		}
		for (int l397 = 0; l397 < 3; l397 = l397 + 1) {
			fRec401[l397] = 0.0f;
		}
		for (int l398 = 0; l398 < 3; l398 = l398 + 1) {
			fRec400[l398] = 0.0f;
		}
		for (int l399 = 0; l399 < 3; l399 = l399 + 1) {
			fRec399[l399] = 0.0f;
		}
		for (int l400 = 0; l400 < 2; l400 = l400 + 1) {
			fVec44[l400] = 0.0f;
		}
		for (int l401 = 0; l401 < 2; l401 = l401 + 1) {
			fRec398[l401] = 0.0f;
		}
		for (int l402 = 0; l402 < 32768; l402 = l402 + 1) {
			fRec397[l402] = 0.0f;
		}
		for (int l403 = 0; l403 < 2; l403 = l403 + 1) {
			fRec396[l403] = 0.0f;
		}
		for (int l404 = 0; l404 < 2; l404 = l404 + 1) {
			fRec403[l404] = 0.0f;
		}
		for (int l405 = 0; l405 < 3; l405 = l405 + 1) {
			fRec411[l405] = 0.0f;
		}
		for (int l406 = 0; l406 < 3; l406 = l406 + 1) {
			fRec410[l406] = 0.0f;
		}
		for (int l407 = 0; l407 < 3; l407 = l407 + 1) {
			fRec409[l407] = 0.0f;
		}
		for (int l408 = 0; l408 < 3; l408 = l408 + 1) {
			fRec408[l408] = 0.0f;
		}
		for (int l409 = 0; l409 < 2; l409 = l409 + 1) {
			fVec45[l409] = 0.0f;
		}
		for (int l410 = 0; l410 < 2; l410 = l410 + 1) {
			fRec407[l410] = 0.0f;
		}
		for (int l411 = 0; l411 < 32768; l411 = l411 + 1) {
			fRec406[l411] = 0.0f;
		}
		for (int l412 = 0; l412 < 2; l412 = l412 + 1) {
			fRec405[l412] = 0.0f;
		}
		for (int l413 = 0; l413 < 2; l413 = l413 + 1) {
			fRec412[l413] = 0.0f;
		}
		for (int l414 = 0; l414 < 3; l414 = l414 + 1) {
			fRec420[l414] = 0.0f;
		}
		for (int l415 = 0; l415 < 3; l415 = l415 + 1) {
			fRec419[l415] = 0.0f;
		}
		for (int l416 = 0; l416 < 3; l416 = l416 + 1) {
			fRec418[l416] = 0.0f;
		}
		for (int l417 = 0; l417 < 3; l417 = l417 + 1) {
			fRec417[l417] = 0.0f;
		}
		for (int l418 = 0; l418 < 2; l418 = l418 + 1) {
			fVec46[l418] = 0.0f;
		}
		for (int l419 = 0; l419 < 2; l419 = l419 + 1) {
			fRec416[l419] = 0.0f;
		}
		for (int l420 = 0; l420 < 32768; l420 = l420 + 1) {
			fRec415[l420] = 0.0f;
		}
		for (int l421 = 0; l421 < 2; l421 = l421 + 1) {
			fRec414[l421] = 0.0f;
		}
		for (int l422 = 0; l422 < 2; l422 = l422 + 1) {
			fRec421[l422] = 0.0f;
		}
		for (int l423 = 0; l423 < 3; l423 = l423 + 1) {
			fRec429[l423] = 0.0f;
		}
		for (int l424 = 0; l424 < 3; l424 = l424 + 1) {
			fRec428[l424] = 0.0f;
		}
		for (int l425 = 0; l425 < 3; l425 = l425 + 1) {
			fRec427[l425] = 0.0f;
		}
		for (int l426 = 0; l426 < 3; l426 = l426 + 1) {
			fRec426[l426] = 0.0f;
		}
		for (int l427 = 0; l427 < 2; l427 = l427 + 1) {
			fVec47[l427] = 0.0f;
		}
		for (int l428 = 0; l428 < 2; l428 = l428 + 1) {
			fRec425[l428] = 0.0f;
		}
		for (int l429 = 0; l429 < 32768; l429 = l429 + 1) {
			fRec424[l429] = 0.0f;
		}
		for (int l430 = 0; l430 < 2; l430 = l430 + 1) {
			fRec423[l430] = 0.0f;
		}
		for (int l431 = 0; l431 < 2; l431 = l431 + 1) {
			fRec430[l431] = 0.0f;
		}
		for (int l432 = 0; l432 < 3; l432 = l432 + 1) {
			fRec438[l432] = 0.0f;
		}
		for (int l433 = 0; l433 < 3; l433 = l433 + 1) {
			fRec437[l433] = 0.0f;
		}
		for (int l434 = 0; l434 < 3; l434 = l434 + 1) {
			fRec436[l434] = 0.0f;
		}
		for (int l435 = 0; l435 < 3; l435 = l435 + 1) {
			fRec435[l435] = 0.0f;
		}
		for (int l436 = 0; l436 < 2; l436 = l436 + 1) {
			fVec48[l436] = 0.0f;
		}
		for (int l437 = 0; l437 < 2; l437 = l437 + 1) {
			fRec434[l437] = 0.0f;
		}
		for (int l438 = 0; l438 < 32768; l438 = l438 + 1) {
			fRec433[l438] = 0.0f;
		}
		for (int l439 = 0; l439 < 2; l439 = l439 + 1) {
			fRec432[l439] = 0.0f;
		}
		for (int l440 = 0; l440 < 2; l440 = l440 + 1) {
			fRec439[l440] = 0.0f;
		}
		for (int l441 = 0; l441 < 3; l441 = l441 + 1) {
			fRec447[l441] = 0.0f;
		}
		for (int l442 = 0; l442 < 3; l442 = l442 + 1) {
			fRec446[l442] = 0.0f;
		}
		for (int l443 = 0; l443 < 3; l443 = l443 + 1) {
			fRec445[l443] = 0.0f;
		}
		for (int l444 = 0; l444 < 3; l444 = l444 + 1) {
			fRec444[l444] = 0.0f;
		}
		for (int l445 = 0; l445 < 2; l445 = l445 + 1) {
			fVec49[l445] = 0.0f;
		}
		for (int l446 = 0; l446 < 2; l446 = l446 + 1) {
			fRec443[l446] = 0.0f;
		}
		for (int l447 = 0; l447 < 32768; l447 = l447 + 1) {
			fRec442[l447] = 0.0f;
		}
		for (int l448 = 0; l448 < 2; l448 = l448 + 1) {
			fRec441[l448] = 0.0f;
		}
		for (int l449 = 0; l449 < 2; l449 = l449 + 1) {
			fRec448[l449] = 0.0f;
		}
		for (int l450 = 0; l450 < 3; l450 = l450 + 1) {
			fRec456[l450] = 0.0f;
		}
		for (int l451 = 0; l451 < 3; l451 = l451 + 1) {
			fRec455[l451] = 0.0f;
		}
		for (int l452 = 0; l452 < 3; l452 = l452 + 1) {
			fRec454[l452] = 0.0f;
		}
		for (int l453 = 0; l453 < 3; l453 = l453 + 1) {
			fRec453[l453] = 0.0f;
		}
		for (int l454 = 0; l454 < 2; l454 = l454 + 1) {
			fVec50[l454] = 0.0f;
		}
		for (int l455 = 0; l455 < 2; l455 = l455 + 1) {
			fRec452[l455] = 0.0f;
		}
		for (int l456 = 0; l456 < 32768; l456 = l456 + 1) {
			fRec451[l456] = 0.0f;
		}
		for (int l457 = 0; l457 < 2; l457 = l457 + 1) {
			fRec450[l457] = 0.0f;
		}
		for (int l458 = 0; l458 < 2; l458 = l458 + 1) {
			fRec457[l458] = 0.0f;
		}
		for (int l459 = 0; l459 < 3; l459 = l459 + 1) {
			fRec465[l459] = 0.0f;
		}
		for (int l460 = 0; l460 < 3; l460 = l460 + 1) {
			fRec464[l460] = 0.0f;
		}
		for (int l461 = 0; l461 < 3; l461 = l461 + 1) {
			fRec463[l461] = 0.0f;
		}
		for (int l462 = 0; l462 < 3; l462 = l462 + 1) {
			fRec462[l462] = 0.0f;
		}
		for (int l463 = 0; l463 < 2; l463 = l463 + 1) {
			fVec51[l463] = 0.0f;
		}
		for (int l464 = 0; l464 < 2; l464 = l464 + 1) {
			fRec461[l464] = 0.0f;
		}
		for (int l465 = 0; l465 < 32768; l465 = l465 + 1) {
			fRec460[l465] = 0.0f;
		}
		for (int l466 = 0; l466 < 2; l466 = l466 + 1) {
			fRec459[l466] = 0.0f;
		}
		for (int l467 = 0; l467 < 2; l467 = l467 + 1) {
			fRec466[l467] = 0.0f;
		}
		for (int l468 = 0; l468 < 3; l468 = l468 + 1) {
			fRec474[l468] = 0.0f;
		}
		for (int l469 = 0; l469 < 3; l469 = l469 + 1) {
			fRec473[l469] = 0.0f;
		}
		for (int l470 = 0; l470 < 3; l470 = l470 + 1) {
			fRec472[l470] = 0.0f;
		}
		for (int l471 = 0; l471 < 3; l471 = l471 + 1) {
			fRec471[l471] = 0.0f;
		}
		for (int l472 = 0; l472 < 2; l472 = l472 + 1) {
			fVec52[l472] = 0.0f;
		}
		for (int l473 = 0; l473 < 2; l473 = l473 + 1) {
			fRec470[l473] = 0.0f;
		}
		for (int l474 = 0; l474 < 32768; l474 = l474 + 1) {
			fRec469[l474] = 0.0f;
		}
		for (int l475 = 0; l475 < 2; l475 = l475 + 1) {
			fRec468[l475] = 0.0f;
		}
		for (int l476 = 0; l476 < 2; l476 = l476 + 1) {
			fRec475[l476] = 0.0f;
		}
		for (int l477 = 0; l477 < 3; l477 = l477 + 1) {
			fRec483[l477] = 0.0f;
		}
		for (int l478 = 0; l478 < 3; l478 = l478 + 1) {
			fRec482[l478] = 0.0f;
		}
		for (int l479 = 0; l479 < 3; l479 = l479 + 1) {
			fRec481[l479] = 0.0f;
		}
		for (int l480 = 0; l480 < 3; l480 = l480 + 1) {
			fRec480[l480] = 0.0f;
		}
		for (int l481 = 0; l481 < 2; l481 = l481 + 1) {
			fVec53[l481] = 0.0f;
		}
		for (int l482 = 0; l482 < 2; l482 = l482 + 1) {
			fRec479[l482] = 0.0f;
		}
		for (int l483 = 0; l483 < 32768; l483 = l483 + 1) {
			fRec478[l483] = 0.0f;
		}
		for (int l484 = 0; l484 < 2; l484 = l484 + 1) {
			fRec477[l484] = 0.0f;
		}
		for (int l485 = 0; l485 < 2; l485 = l485 + 1) {
			fRec484[l485] = 0.0f;
		}
		for (int l486 = 0; l486 < 3; l486 = l486 + 1) {
			fRec492[l486] = 0.0f;
		}
		for (int l487 = 0; l487 < 3; l487 = l487 + 1) {
			fRec491[l487] = 0.0f;
		}
		for (int l488 = 0; l488 < 3; l488 = l488 + 1) {
			fRec490[l488] = 0.0f;
		}
		for (int l489 = 0; l489 < 3; l489 = l489 + 1) {
			fRec489[l489] = 0.0f;
		}
		for (int l490 = 0; l490 < 2; l490 = l490 + 1) {
			fVec54[l490] = 0.0f;
		}
		for (int l491 = 0; l491 < 2; l491 = l491 + 1) {
			fRec488[l491] = 0.0f;
		}
		for (int l492 = 0; l492 < 32768; l492 = l492 + 1) {
			fRec487[l492] = 0.0f;
		}
		for (int l493 = 0; l493 < 2; l493 = l493 + 1) {
			fRec486[l493] = 0.0f;
		}
		for (int l494 = 0; l494 < 2; l494 = l494 + 1) {
			fRec493[l494] = 0.0f;
		}
		for (int l495 = 0; l495 < 3; l495 = l495 + 1) {
			fRec501[l495] = 0.0f;
		}
		for (int l496 = 0; l496 < 3; l496 = l496 + 1) {
			fRec500[l496] = 0.0f;
		}
		for (int l497 = 0; l497 < 3; l497 = l497 + 1) {
			fRec499[l497] = 0.0f;
		}
		for (int l498 = 0; l498 < 3; l498 = l498 + 1) {
			fRec498[l498] = 0.0f;
		}
		for (int l499 = 0; l499 < 2; l499 = l499 + 1) {
			fVec55[l499] = 0.0f;
		}
		for (int l500 = 0; l500 < 2; l500 = l500 + 1) {
			fRec497[l500] = 0.0f;
		}
		for (int l501 = 0; l501 < 32768; l501 = l501 + 1) {
			fRec496[l501] = 0.0f;
		}
		for (int l502 = 0; l502 < 2; l502 = l502 + 1) {
			fRec495[l502] = 0.0f;
		}
		for (int l503 = 0; l503 < 2; l503 = l503 + 1) {
			fRec502[l503] = 0.0f;
		}
		for (int l504 = 0; l504 < 3; l504 = l504 + 1) {
			fRec510[l504] = 0.0f;
		}
		for (int l505 = 0; l505 < 3; l505 = l505 + 1) {
			fRec509[l505] = 0.0f;
		}
		for (int l506 = 0; l506 < 3; l506 = l506 + 1) {
			fRec508[l506] = 0.0f;
		}
		for (int l507 = 0; l507 < 3; l507 = l507 + 1) {
			fRec507[l507] = 0.0f;
		}
		for (int l508 = 0; l508 < 2; l508 = l508 + 1) {
			fVec56[l508] = 0.0f;
		}
		for (int l509 = 0; l509 < 2; l509 = l509 + 1) {
			fRec506[l509] = 0.0f;
		}
		for (int l510 = 0; l510 < 32768; l510 = l510 + 1) {
			fRec505[l510] = 0.0f;
		}
		for (int l511 = 0; l511 < 2; l511 = l511 + 1) {
			fRec504[l511] = 0.0f;
		}
		for (int l512 = 0; l512 < 2; l512 = l512 + 1) {
			fRec511[l512] = 0.0f;
		}
		for (int l513 = 0; l513 < 3; l513 = l513 + 1) {
			fRec519[l513] = 0.0f;
		}
		for (int l514 = 0; l514 < 3; l514 = l514 + 1) {
			fRec518[l514] = 0.0f;
		}
		for (int l515 = 0; l515 < 3; l515 = l515 + 1) {
			fRec517[l515] = 0.0f;
		}
		for (int l516 = 0; l516 < 3; l516 = l516 + 1) {
			fRec516[l516] = 0.0f;
		}
		for (int l517 = 0; l517 < 2; l517 = l517 + 1) {
			fVec57[l517] = 0.0f;
		}
		for (int l518 = 0; l518 < 2; l518 = l518 + 1) {
			fRec515[l518] = 0.0f;
		}
		for (int l519 = 0; l519 < 32768; l519 = l519 + 1) {
			fRec514[l519] = 0.0f;
		}
		for (int l520 = 0; l520 < 2; l520 = l520 + 1) {
			fRec513[l520] = 0.0f;
		}
		for (int l521 = 0; l521 < 2; l521 = l521 + 1) {
			fRec520[l521] = 0.0f;
		}
		for (int l522 = 0; l522 < 3; l522 = l522 + 1) {
			fRec528[l522] = 0.0f;
		}
		for (int l523 = 0; l523 < 3; l523 = l523 + 1) {
			fRec527[l523] = 0.0f;
		}
		for (int l524 = 0; l524 < 3; l524 = l524 + 1) {
			fRec526[l524] = 0.0f;
		}
		for (int l525 = 0; l525 < 3; l525 = l525 + 1) {
			fRec525[l525] = 0.0f;
		}
		for (int l526 = 0; l526 < 2; l526 = l526 + 1) {
			fVec58[l526] = 0.0f;
		}
		for (int l527 = 0; l527 < 2; l527 = l527 + 1) {
			fRec524[l527] = 0.0f;
		}
		for (int l528 = 0; l528 < 32768; l528 = l528 + 1) {
			fRec523[l528] = 0.0f;
		}
		for (int l529 = 0; l529 < 2; l529 = l529 + 1) {
			fRec522[l529] = 0.0f;
		}
		for (int l530 = 0; l530 < 2; l530 = l530 + 1) {
			fRec529[l530] = 0.0f;
		}
		for (int l531 = 0; l531 < 3; l531 = l531 + 1) {
			fRec537[l531] = 0.0f;
		}
		for (int l532 = 0; l532 < 3; l532 = l532 + 1) {
			fRec536[l532] = 0.0f;
		}
		for (int l533 = 0; l533 < 3; l533 = l533 + 1) {
			fRec535[l533] = 0.0f;
		}
		for (int l534 = 0; l534 < 3; l534 = l534 + 1) {
			fRec534[l534] = 0.0f;
		}
		for (int l535 = 0; l535 < 2; l535 = l535 + 1) {
			fVec59[l535] = 0.0f;
		}
		for (int l536 = 0; l536 < 2; l536 = l536 + 1) {
			fRec533[l536] = 0.0f;
		}
		for (int l537 = 0; l537 < 32768; l537 = l537 + 1) {
			fRec532[l537] = 0.0f;
		}
		for (int l538 = 0; l538 < 2; l538 = l538 + 1) {
			fRec531[l538] = 0.0f;
		}
		for (int l539 = 0; l539 < 2; l539 = l539 + 1) {
			fRec538[l539] = 0.0f;
		}
		for (int l540 = 0; l540 < 3; l540 = l540 + 1) {
			fRec546[l540] = 0.0f;
		}
		for (int l541 = 0; l541 < 3; l541 = l541 + 1) {
			fRec545[l541] = 0.0f;
		}
		for (int l542 = 0; l542 < 3; l542 = l542 + 1) {
			fRec544[l542] = 0.0f;
		}
		for (int l543 = 0; l543 < 3; l543 = l543 + 1) {
			fRec543[l543] = 0.0f;
		}
		for (int l544 = 0; l544 < 2; l544 = l544 + 1) {
			fVec60[l544] = 0.0f;
		}
		for (int l545 = 0; l545 < 2; l545 = l545 + 1) {
			fRec542[l545] = 0.0f;
		}
		for (int l546 = 0; l546 < 32768; l546 = l546 + 1) {
			fRec541[l546] = 0.0f;
		}
		for (int l547 = 0; l547 < 2; l547 = l547 + 1) {
			fRec540[l547] = 0.0f;
		}
		for (int l548 = 0; l548 < 2; l548 = l548 + 1) {
			fRec547[l548] = 0.0f;
		}
		for (int l549 = 0; l549 < 3; l549 = l549 + 1) {
			fRec555[l549] = 0.0f;
		}
		for (int l550 = 0; l550 < 3; l550 = l550 + 1) {
			fRec554[l550] = 0.0f;
		}
		for (int l551 = 0; l551 < 3; l551 = l551 + 1) {
			fRec553[l551] = 0.0f;
		}
		for (int l552 = 0; l552 < 3; l552 = l552 + 1) {
			fRec552[l552] = 0.0f;
		}
		for (int l553 = 0; l553 < 2; l553 = l553 + 1) {
			fVec61[l553] = 0.0f;
		}
		for (int l554 = 0; l554 < 2; l554 = l554 + 1) {
			fRec551[l554] = 0.0f;
		}
		for (int l555 = 0; l555 < 32768; l555 = l555 + 1) {
			fRec550[l555] = 0.0f;
		}
		for (int l556 = 0; l556 < 2; l556 = l556 + 1) {
			fRec549[l556] = 0.0f;
		}
		for (int l557 = 0; l557 < 2; l557 = l557 + 1) {
			fRec556[l557] = 0.0f;
		}
		for (int l558 = 0; l558 < 3; l558 = l558 + 1) {
			fRec564[l558] = 0.0f;
		}
		for (int l559 = 0; l559 < 3; l559 = l559 + 1) {
			fRec563[l559] = 0.0f;
		}
		for (int l560 = 0; l560 < 3; l560 = l560 + 1) {
			fRec562[l560] = 0.0f;
		}
		for (int l561 = 0; l561 < 3; l561 = l561 + 1) {
			fRec561[l561] = 0.0f;
		}
		for (int l562 = 0; l562 < 2; l562 = l562 + 1) {
			fVec62[l562] = 0.0f;
		}
		for (int l563 = 0; l563 < 2; l563 = l563 + 1) {
			fRec560[l563] = 0.0f;
		}
		for (int l564 = 0; l564 < 32768; l564 = l564 + 1) {
			fRec559[l564] = 0.0f;
		}
		for (int l565 = 0; l565 < 2; l565 = l565 + 1) {
			fRec558[l565] = 0.0f;
		}
		for (int l566 = 0; l566 < 2; l566 = l566 + 1) {
			fRec565[l566] = 0.0f;
		}
		for (int l567 = 0; l567 < 3; l567 = l567 + 1) {
			fRec573[l567] = 0.0f;
		}
		for (int l568 = 0; l568 < 3; l568 = l568 + 1) {
			fRec572[l568] = 0.0f;
		}
		for (int l569 = 0; l569 < 3; l569 = l569 + 1) {
			fRec571[l569] = 0.0f;
		}
		for (int l570 = 0; l570 < 3; l570 = l570 + 1) {
			fRec570[l570] = 0.0f;
		}
		for (int l571 = 0; l571 < 2; l571 = l571 + 1) {
			fVec63[l571] = 0.0f;
		}
		for (int l572 = 0; l572 < 2; l572 = l572 + 1) {
			fRec569[l572] = 0.0f;
		}
		for (int l573 = 0; l573 < 32768; l573 = l573 + 1) {
			fRec568[l573] = 0.0f;
		}
		for (int l574 = 0; l574 < 2; l574 = l574 + 1) {
			fRec567[l574] = 0.0f;
		}
		for (int l575 = 0; l575 < 2; l575 = l575 + 1) {
			fRec574[l575] = 0.0f;
		}
		for (int l576 = 0; l576 < 3; l576 = l576 + 1) {
			fRec582[l576] = 0.0f;
		}
		for (int l577 = 0; l577 < 3; l577 = l577 + 1) {
			fRec581[l577] = 0.0f;
		}
		for (int l578 = 0; l578 < 3; l578 = l578 + 1) {
			fRec580[l578] = 0.0f;
		}
		for (int l579 = 0; l579 < 3; l579 = l579 + 1) {
			fRec579[l579] = 0.0f;
		}
		for (int l580 = 0; l580 < 2; l580 = l580 + 1) {
			fVec64[l580] = 0.0f;
		}
		for (int l581 = 0; l581 < 2; l581 = l581 + 1) {
			fRec578[l581] = 0.0f;
		}
		for (int l582 = 0; l582 < 32768; l582 = l582 + 1) {
			fRec577[l582] = 0.0f;
		}
		for (int l583 = 0; l583 < 2; l583 = l583 + 1) {
			fRec576[l583] = 0.0f;
		}
		for (int l584 = 0; l584 < 2; l584 = l584 + 1) {
			fRec583[l584] = 0.0f;
		}
		for (int l585 = 0; l585 < 3; l585 = l585 + 1) {
			fRec591[l585] = 0.0f;
		}
		for (int l586 = 0; l586 < 3; l586 = l586 + 1) {
			fRec590[l586] = 0.0f;
		}
		for (int l587 = 0; l587 < 3; l587 = l587 + 1) {
			fRec589[l587] = 0.0f;
		}
		for (int l588 = 0; l588 < 3; l588 = l588 + 1) {
			fRec588[l588] = 0.0f;
		}
		for (int l589 = 0; l589 < 2; l589 = l589 + 1) {
			fVec65[l589] = 0.0f;
		}
		for (int l590 = 0; l590 < 2; l590 = l590 + 1) {
			fRec587[l590] = 0.0f;
		}
		for (int l591 = 0; l591 < 32768; l591 = l591 + 1) {
			fRec586[l591] = 0.0f;
		}
		for (int l592 = 0; l592 < 2; l592 = l592 + 1) {
			fRec585[l592] = 0.0f;
		}
		for (int l593 = 0; l593 < 2; l593 = l593 + 1) {
			fRec592[l593] = 0.0f;
		}
		for (int l594 = 0; l594 < 3; l594 = l594 + 1) {
			fRec600[l594] = 0.0f;
		}
		for (int l595 = 0; l595 < 3; l595 = l595 + 1) {
			fRec599[l595] = 0.0f;
		}
		for (int l596 = 0; l596 < 3; l596 = l596 + 1) {
			fRec598[l596] = 0.0f;
		}
		for (int l597 = 0; l597 < 3; l597 = l597 + 1) {
			fRec597[l597] = 0.0f;
		}
		for (int l598 = 0; l598 < 2; l598 = l598 + 1) {
			fVec66[l598] = 0.0f;
		}
		for (int l599 = 0; l599 < 2; l599 = l599 + 1) {
			fRec596[l599] = 0.0f;
		}
		for (int l600 = 0; l600 < 32768; l600 = l600 + 1) {
			fRec595[l600] = 0.0f;
		}
		for (int l601 = 0; l601 < 2; l601 = l601 + 1) {
			fRec594[l601] = 0.0f;
		}
		for (int l602 = 0; l602 < 2; l602 = l602 + 1) {
			fRec601[l602] = 0.0f;
		}
		for (int l603 = 0; l603 < 3; l603 = l603 + 1) {
			fRec609[l603] = 0.0f;
		}
		for (int l604 = 0; l604 < 3; l604 = l604 + 1) {
			fRec608[l604] = 0.0f;
		}
		for (int l605 = 0; l605 < 3; l605 = l605 + 1) {
			fRec607[l605] = 0.0f;
		}
		for (int l606 = 0; l606 < 3; l606 = l606 + 1) {
			fRec606[l606] = 0.0f;
		}
		for (int l607 = 0; l607 < 2; l607 = l607 + 1) {
			fVec67[l607] = 0.0f;
		}
		for (int l608 = 0; l608 < 2; l608 = l608 + 1) {
			fRec605[l608] = 0.0f;
		}
		for (int l609 = 0; l609 < 32768; l609 = l609 + 1) {
			fRec604[l609] = 0.0f;
		}
		for (int l610 = 0; l610 < 2; l610 = l610 + 1) {
			fRec603[l610] = 0.0f;
		}
		for (int l611 = 0; l611 < 2; l611 = l611 + 1) {
			fRec610[l611] = 0.0f;
		}
		for (int l612 = 0; l612 < 3; l612 = l612 + 1) {
			fRec618[l612] = 0.0f;
		}
		for (int l613 = 0; l613 < 3; l613 = l613 + 1) {
			fRec617[l613] = 0.0f;
		}
		for (int l614 = 0; l614 < 3; l614 = l614 + 1) {
			fRec616[l614] = 0.0f;
		}
		for (int l615 = 0; l615 < 3; l615 = l615 + 1) {
			fRec615[l615] = 0.0f;
		}
		for (int l616 = 0; l616 < 2; l616 = l616 + 1) {
			fVec68[l616] = 0.0f;
		}
		for (int l617 = 0; l617 < 2; l617 = l617 + 1) {
			fRec614[l617] = 0.0f;
		}
		for (int l618 = 0; l618 < 32768; l618 = l618 + 1) {
			fRec613[l618] = 0.0f;
		}
		for (int l619 = 0; l619 < 2; l619 = l619 + 1) {
			fRec612[l619] = 0.0f;
		}
		for (int l620 = 0; l620 < 2; l620 = l620 + 1) {
			fRec619[l620] = 0.0f;
		}
		for (int l621 = 0; l621 < 3; l621 = l621 + 1) {
			fRec627[l621] = 0.0f;
		}
		for (int l622 = 0; l622 < 3; l622 = l622 + 1) {
			fRec626[l622] = 0.0f;
		}
		for (int l623 = 0; l623 < 3; l623 = l623 + 1) {
			fRec625[l623] = 0.0f;
		}
		for (int l624 = 0; l624 < 3; l624 = l624 + 1) {
			fRec624[l624] = 0.0f;
		}
		for (int l625 = 0; l625 < 2; l625 = l625 + 1) {
			fVec69[l625] = 0.0f;
		}
		for (int l626 = 0; l626 < 2; l626 = l626 + 1) {
			fRec623[l626] = 0.0f;
		}
		for (int l627 = 0; l627 < 32768; l627 = l627 + 1) {
			fRec622[l627] = 0.0f;
		}
		for (int l628 = 0; l628 < 2; l628 = l628 + 1) {
			fRec621[l628] = 0.0f;
		}
		for (int l629 = 0; l629 < 2; l629 = l629 + 1) {
			fRec628[l629] = 0.0f;
		}
		for (int l630 = 0; l630 < 3; l630 = l630 + 1) {
			fRec636[l630] = 0.0f;
		}
		for (int l631 = 0; l631 < 3; l631 = l631 + 1) {
			fRec635[l631] = 0.0f;
		}
		for (int l632 = 0; l632 < 3; l632 = l632 + 1) {
			fRec634[l632] = 0.0f;
		}
		for (int l633 = 0; l633 < 3; l633 = l633 + 1) {
			fRec633[l633] = 0.0f;
		}
		for (int l634 = 0; l634 < 2; l634 = l634 + 1) {
			fVec70[l634] = 0.0f;
		}
		for (int l635 = 0; l635 < 2; l635 = l635 + 1) {
			fRec632[l635] = 0.0f;
		}
		for (int l636 = 0; l636 < 32768; l636 = l636 + 1) {
			fRec631[l636] = 0.0f;
		}
		for (int l637 = 0; l637 < 2; l637 = l637 + 1) {
			fRec630[l637] = 0.0f;
		}
		for (int l638 = 0; l638 < 2; l638 = l638 + 1) {
			fRec637[l638] = 0.0f;
		}
		for (int l639 = 0; l639 < 3; l639 = l639 + 1) {
			fRec645[l639] = 0.0f;
		}
		for (int l640 = 0; l640 < 3; l640 = l640 + 1) {
			fRec644[l640] = 0.0f;
		}
		for (int l641 = 0; l641 < 3; l641 = l641 + 1) {
			fRec643[l641] = 0.0f;
		}
		for (int l642 = 0; l642 < 3; l642 = l642 + 1) {
			fRec642[l642] = 0.0f;
		}
		for (int l643 = 0; l643 < 2; l643 = l643 + 1) {
			fVec71[l643] = 0.0f;
		}
		for (int l644 = 0; l644 < 2; l644 = l644 + 1) {
			fRec641[l644] = 0.0f;
		}
		for (int l645 = 0; l645 < 32768; l645 = l645 + 1) {
			fRec640[l645] = 0.0f;
		}
		for (int l646 = 0; l646 < 2; l646 = l646 + 1) {
			fRec639[l646] = 0.0f;
		}
		for (int l647 = 0; l647 < 2; l647 = l647 + 1) {
			fRec646[l647] = 0.0f;
		}
		for (int l648 = 0; l648 < 3; l648 = l648 + 1) {
			fRec654[l648] = 0.0f;
		}
		for (int l649 = 0; l649 < 3; l649 = l649 + 1) {
			fRec653[l649] = 0.0f;
		}
		for (int l650 = 0; l650 < 3; l650 = l650 + 1) {
			fRec652[l650] = 0.0f;
		}
		for (int l651 = 0; l651 < 3; l651 = l651 + 1) {
			fRec651[l651] = 0.0f;
		}
		for (int l652 = 0; l652 < 2; l652 = l652 + 1) {
			fVec72[l652] = 0.0f;
		}
		for (int l653 = 0; l653 < 2; l653 = l653 + 1) {
			fRec650[l653] = 0.0f;
		}
		for (int l654 = 0; l654 < 32768; l654 = l654 + 1) {
			fRec649[l654] = 0.0f;
		}
		for (int l655 = 0; l655 < 2; l655 = l655 + 1) {
			fRec648[l655] = 0.0f;
		}
		for (int l656 = 0; l656 < 2; l656 = l656 + 1) {
			fRec655[l656] = 0.0f;
		}
		for (int l657 = 0; l657 < 3; l657 = l657 + 1) {
			fRec663[l657] = 0.0f;
		}
		for (int l658 = 0; l658 < 3; l658 = l658 + 1) {
			fRec662[l658] = 0.0f;
		}
		for (int l659 = 0; l659 < 3; l659 = l659 + 1) {
			fRec661[l659] = 0.0f;
		}
		for (int l660 = 0; l660 < 3; l660 = l660 + 1) {
			fRec660[l660] = 0.0f;
		}
		for (int l661 = 0; l661 < 2; l661 = l661 + 1) {
			fVec73[l661] = 0.0f;
		}
		for (int l662 = 0; l662 < 2; l662 = l662 + 1) {
			fRec659[l662] = 0.0f;
		}
		for (int l663 = 0; l663 < 32768; l663 = l663 + 1) {
			fRec658[l663] = 0.0f;
		}
		for (int l664 = 0; l664 < 2; l664 = l664 + 1) {
			fRec657[l664] = 0.0f;
		}
		for (int l665 = 0; l665 < 2; l665 = l665 + 1) {
			fRec664[l665] = 0.0f;
		}
		for (int l666 = 0; l666 < 3; l666 = l666 + 1) {
			fRec672[l666] = 0.0f;
		}
		for (int l667 = 0; l667 < 3; l667 = l667 + 1) {
			fRec671[l667] = 0.0f;
		}
		for (int l668 = 0; l668 < 3; l668 = l668 + 1) {
			fRec670[l668] = 0.0f;
		}
		for (int l669 = 0; l669 < 3; l669 = l669 + 1) {
			fRec669[l669] = 0.0f;
		}
		for (int l670 = 0; l670 < 2; l670 = l670 + 1) {
			fVec74[l670] = 0.0f;
		}
		for (int l671 = 0; l671 < 2; l671 = l671 + 1) {
			fRec668[l671] = 0.0f;
		}
		for (int l672 = 0; l672 < 32768; l672 = l672 + 1) {
			fRec667[l672] = 0.0f;
		}
		for (int l673 = 0; l673 < 2; l673 = l673 + 1) {
			fRec666[l673] = 0.0f;
		}
		for (int l674 = 0; l674 < 2; l674 = l674 + 1) {
			fRec673[l674] = 0.0f;
		}
		for (int l675 = 0; l675 < 3; l675 = l675 + 1) {
			fRec681[l675] = 0.0f;
		}
		for (int l676 = 0; l676 < 3; l676 = l676 + 1) {
			fRec680[l676] = 0.0f;
		}
		for (int l677 = 0; l677 < 3; l677 = l677 + 1) {
			fRec679[l677] = 0.0f;
		}
		for (int l678 = 0; l678 < 3; l678 = l678 + 1) {
			fRec678[l678] = 0.0f;
		}
		for (int l679 = 0; l679 < 2; l679 = l679 + 1) {
			fVec75[l679] = 0.0f;
		}
		for (int l680 = 0; l680 < 2; l680 = l680 + 1) {
			fRec677[l680] = 0.0f;
		}
		for (int l681 = 0; l681 < 32768; l681 = l681 + 1) {
			fRec676[l681] = 0.0f;
		}
		for (int l682 = 0; l682 < 2; l682 = l682 + 1) {
			fRec675[l682] = 0.0f;
		}
		for (int l683 = 0; l683 < 2; l683 = l683 + 1) {
			fRec682[l683] = 0.0f;
		}
		for (int l684 = 0; l684 < 3; l684 = l684 + 1) {
			fRec690[l684] = 0.0f;
		}
		for (int l685 = 0; l685 < 3; l685 = l685 + 1) {
			fRec689[l685] = 0.0f;
		}
		for (int l686 = 0; l686 < 3; l686 = l686 + 1) {
			fRec688[l686] = 0.0f;
		}
		for (int l687 = 0; l687 < 3; l687 = l687 + 1) {
			fRec687[l687] = 0.0f;
		}
		for (int l688 = 0; l688 < 2; l688 = l688 + 1) {
			fVec76[l688] = 0.0f;
		}
		for (int l689 = 0; l689 < 2; l689 = l689 + 1) {
			fRec686[l689] = 0.0f;
		}
		for (int l690 = 0; l690 < 32768; l690 = l690 + 1) {
			fRec685[l690] = 0.0f;
		}
		for (int l691 = 0; l691 < 2; l691 = l691 + 1) {
			fRec684[l691] = 0.0f;
		}
		for (int l692 = 0; l692 < 2; l692 = l692 + 1) {
			fRec691[l692] = 0.0f;
		}
		for (int l693 = 0; l693 < 3; l693 = l693 + 1) {
			fRec699[l693] = 0.0f;
		}
		for (int l694 = 0; l694 < 3; l694 = l694 + 1) {
			fRec698[l694] = 0.0f;
		}
		for (int l695 = 0; l695 < 3; l695 = l695 + 1) {
			fRec697[l695] = 0.0f;
		}
		for (int l696 = 0; l696 < 3; l696 = l696 + 1) {
			fRec696[l696] = 0.0f;
		}
		for (int l697 = 0; l697 < 2; l697 = l697 + 1) {
			fVec77[l697] = 0.0f;
		}
		for (int l698 = 0; l698 < 2; l698 = l698 + 1) {
			fRec695[l698] = 0.0f;
		}
		for (int l699 = 0; l699 < 32768; l699 = l699 + 1) {
			fRec694[l699] = 0.0f;
		}
		for (int l700 = 0; l700 < 2; l700 = l700 + 1) {
			fRec693[l700] = 0.0f;
		}
		for (int l701 = 0; l701 < 2; l701 = l701 + 1) {
			fRec700[l701] = 0.0f;
		}
		for (int l702 = 0; l702 < 3; l702 = l702 + 1) {
			fRec708[l702] = 0.0f;
		}
		for (int l703 = 0; l703 < 3; l703 = l703 + 1) {
			fRec707[l703] = 0.0f;
		}
		for (int l704 = 0; l704 < 3; l704 = l704 + 1) {
			fRec706[l704] = 0.0f;
		}
		for (int l705 = 0; l705 < 3; l705 = l705 + 1) {
			fRec705[l705] = 0.0f;
		}
		for (int l706 = 0; l706 < 2; l706 = l706 + 1) {
			fVec78[l706] = 0.0f;
		}
		for (int l707 = 0; l707 < 2; l707 = l707 + 1) {
			fRec704[l707] = 0.0f;
		}
		for (int l708 = 0; l708 < 32768; l708 = l708 + 1) {
			fRec703[l708] = 0.0f;
		}
		for (int l709 = 0; l709 < 2; l709 = l709 + 1) {
			fRec702[l709] = 0.0f;
		}
		for (int l710 = 0; l710 < 2; l710 = l710 + 1) {
			fRec709[l710] = 0.0f;
		}
		for (int l711 = 0; l711 < 3; l711 = l711 + 1) {
			fRec717[l711] = 0.0f;
		}
		for (int l712 = 0; l712 < 3; l712 = l712 + 1) {
			fRec716[l712] = 0.0f;
		}
		for (int l713 = 0; l713 < 3; l713 = l713 + 1) {
			fRec715[l713] = 0.0f;
		}
		for (int l714 = 0; l714 < 3; l714 = l714 + 1) {
			fRec714[l714] = 0.0f;
		}
		for (int l715 = 0; l715 < 2; l715 = l715 + 1) {
			fVec79[l715] = 0.0f;
		}
		for (int l716 = 0; l716 < 2; l716 = l716 + 1) {
			fRec713[l716] = 0.0f;
		}
		for (int l717 = 0; l717 < 32768; l717 = l717 + 1) {
			fRec712[l717] = 0.0f;
		}
		for (int l718 = 0; l718 < 2; l718 = l718 + 1) {
			fRec711[l718] = 0.0f;
		}
		for (int l719 = 0; l719 < 2; l719 = l719 + 1) {
			fRec718[l719] = 0.0f;
		}
		for (int l720 = 0; l720 < 3; l720 = l720 + 1) {
			fRec726[l720] = 0.0f;
		}
		for (int l721 = 0; l721 < 3; l721 = l721 + 1) {
			fRec725[l721] = 0.0f;
		}
		for (int l722 = 0; l722 < 3; l722 = l722 + 1) {
			fRec724[l722] = 0.0f;
		}
		for (int l723 = 0; l723 < 3; l723 = l723 + 1) {
			fRec723[l723] = 0.0f;
		}
		for (int l724 = 0; l724 < 2; l724 = l724 + 1) {
			fVec80[l724] = 0.0f;
		}
		for (int l725 = 0; l725 < 2; l725 = l725 + 1) {
			fRec722[l725] = 0.0f;
		}
		for (int l726 = 0; l726 < 32768; l726 = l726 + 1) {
			fRec721[l726] = 0.0f;
		}
		for (int l727 = 0; l727 < 2; l727 = l727 + 1) {
			fRec720[l727] = 0.0f;
		}
		for (int l728 = 0; l728 < 2; l728 = l728 + 1) {
			fRec727[l728] = 0.0f;
		}
		for (int l729 = 0; l729 < 3; l729 = l729 + 1) {
			fRec735[l729] = 0.0f;
		}
		for (int l730 = 0; l730 < 3; l730 = l730 + 1) {
			fRec734[l730] = 0.0f;
		}
		for (int l731 = 0; l731 < 3; l731 = l731 + 1) {
			fRec733[l731] = 0.0f;
		}
		for (int l732 = 0; l732 < 3; l732 = l732 + 1) {
			fRec732[l732] = 0.0f;
		}
		for (int l733 = 0; l733 < 2; l733 = l733 + 1) {
			fVec81[l733] = 0.0f;
		}
		for (int l734 = 0; l734 < 2; l734 = l734 + 1) {
			fRec731[l734] = 0.0f;
		}
		for (int l735 = 0; l735 < 32768; l735 = l735 + 1) {
			fRec730[l735] = 0.0f;
		}
		for (int l736 = 0; l736 < 2; l736 = l736 + 1) {
			fRec729[l736] = 0.0f;
		}
		for (int l737 = 0; l737 < 2; l737 = l737 + 1) {
			fRec736[l737] = 0.0f;
		}
		for (int l738 = 0; l738 < 3; l738 = l738 + 1) {
			fRec744[l738] = 0.0f;
		}
		for (int l739 = 0; l739 < 3; l739 = l739 + 1) {
			fRec743[l739] = 0.0f;
		}
		for (int l740 = 0; l740 < 3; l740 = l740 + 1) {
			fRec742[l740] = 0.0f;
		}
		for (int l741 = 0; l741 < 3; l741 = l741 + 1) {
			fRec741[l741] = 0.0f;
		}
		for (int l742 = 0; l742 < 2; l742 = l742 + 1) {
			fVec82[l742] = 0.0f;
		}
		for (int l743 = 0; l743 < 2; l743 = l743 + 1) {
			fRec740[l743] = 0.0f;
		}
		for (int l744 = 0; l744 < 32768; l744 = l744 + 1) {
			fRec739[l744] = 0.0f;
		}
		for (int l745 = 0; l745 < 2; l745 = l745 + 1) {
			fRec738[l745] = 0.0f;
		}
		for (int l746 = 0; l746 < 2; l746 = l746 + 1) {
			fRec745[l746] = 0.0f;
		}
		for (int l747 = 0; l747 < 3; l747 = l747 + 1) {
			fRec753[l747] = 0.0f;
		}
		for (int l748 = 0; l748 < 3; l748 = l748 + 1) {
			fRec752[l748] = 0.0f;
		}
		for (int l749 = 0; l749 < 3; l749 = l749 + 1) {
			fRec751[l749] = 0.0f;
		}
		for (int l750 = 0; l750 < 3; l750 = l750 + 1) {
			fRec750[l750] = 0.0f;
		}
		for (int l751 = 0; l751 < 2; l751 = l751 + 1) {
			fVec83[l751] = 0.0f;
		}
		for (int l752 = 0; l752 < 2; l752 = l752 + 1) {
			fRec749[l752] = 0.0f;
		}
		for (int l753 = 0; l753 < 32768; l753 = l753 + 1) {
			fRec748[l753] = 0.0f;
		}
		for (int l754 = 0; l754 < 2; l754 = l754 + 1) {
			fRec747[l754] = 0.0f;
		}
		for (int l755 = 0; l755 < 2; l755 = l755 + 1) {
			fRec754[l755] = 0.0f;
		}
		for (int l756 = 0; l756 < 3; l756 = l756 + 1) {
			fRec762[l756] = 0.0f;
		}
		for (int l757 = 0; l757 < 3; l757 = l757 + 1) {
			fRec761[l757] = 0.0f;
		}
		for (int l758 = 0; l758 < 3; l758 = l758 + 1) {
			fRec760[l758] = 0.0f;
		}
		for (int l759 = 0; l759 < 3; l759 = l759 + 1) {
			fRec759[l759] = 0.0f;
		}
		for (int l760 = 0; l760 < 2; l760 = l760 + 1) {
			fVec84[l760] = 0.0f;
		}
		for (int l761 = 0; l761 < 2; l761 = l761 + 1) {
			fRec758[l761] = 0.0f;
		}
		for (int l762 = 0; l762 < 32768; l762 = l762 + 1) {
			fRec757[l762] = 0.0f;
		}
		for (int l763 = 0; l763 < 2; l763 = l763 + 1) {
			fRec756[l763] = 0.0f;
		}
		for (int l764 = 0; l764 < 2; l764 = l764 + 1) {
			fRec763[l764] = 0.0f;
		}
		for (int l765 = 0; l765 < 3; l765 = l765 + 1) {
			fRec771[l765] = 0.0f;
		}
		for (int l766 = 0; l766 < 3; l766 = l766 + 1) {
			fRec770[l766] = 0.0f;
		}
		for (int l767 = 0; l767 < 3; l767 = l767 + 1) {
			fRec769[l767] = 0.0f;
		}
		for (int l768 = 0; l768 < 3; l768 = l768 + 1) {
			fRec768[l768] = 0.0f;
		}
		for (int l769 = 0; l769 < 2; l769 = l769 + 1) {
			fVec85[l769] = 0.0f;
		}
		for (int l770 = 0; l770 < 2; l770 = l770 + 1) {
			fRec767[l770] = 0.0f;
		}
		for (int l771 = 0; l771 < 32768; l771 = l771 + 1) {
			fRec766[l771] = 0.0f;
		}
		for (int l772 = 0; l772 < 2; l772 = l772 + 1) {
			fRec765[l772] = 0.0f;
		}
		for (int l773 = 0; l773 < 2; l773 = l773 + 1) {
			fRec772[l773] = 0.0f;
		}
		for (int l774 = 0; l774 < 3; l774 = l774 + 1) {
			fRec780[l774] = 0.0f;
		}
		for (int l775 = 0; l775 < 3; l775 = l775 + 1) {
			fRec779[l775] = 0.0f;
		}
		for (int l776 = 0; l776 < 3; l776 = l776 + 1) {
			fRec778[l776] = 0.0f;
		}
		for (int l777 = 0; l777 < 3; l777 = l777 + 1) {
			fRec777[l777] = 0.0f;
		}
		for (int l778 = 0; l778 < 2; l778 = l778 + 1) {
			fVec86[l778] = 0.0f;
		}
		for (int l779 = 0; l779 < 2; l779 = l779 + 1) {
			fRec776[l779] = 0.0f;
		}
		for (int l780 = 0; l780 < 32768; l780 = l780 + 1) {
			fRec775[l780] = 0.0f;
		}
		for (int l781 = 0; l781 < 2; l781 = l781 + 1) {
			fRec774[l781] = 0.0f;
		}
		for (int l782 = 0; l782 < 2; l782 = l782 + 1) {
			fRec781[l782] = 0.0f;
		}
		for (int l783 = 0; l783 < 3; l783 = l783 + 1) {
			fRec789[l783] = 0.0f;
		}
		for (int l784 = 0; l784 < 3; l784 = l784 + 1) {
			fRec788[l784] = 0.0f;
		}
		for (int l785 = 0; l785 < 3; l785 = l785 + 1) {
			fRec787[l785] = 0.0f;
		}
		for (int l786 = 0; l786 < 3; l786 = l786 + 1) {
			fRec786[l786] = 0.0f;
		}
		for (int l787 = 0; l787 < 2; l787 = l787 + 1) {
			fVec87[l787] = 0.0f;
		}
		for (int l788 = 0; l788 < 2; l788 = l788 + 1) {
			fRec785[l788] = 0.0f;
		}
		for (int l789 = 0; l789 < 32768; l789 = l789 + 1) {
			fRec784[l789] = 0.0f;
		}
		for (int l790 = 0; l790 < 2; l790 = l790 + 1) {
			fRec783[l790] = 0.0f;
		}
		for (int l791 = 0; l791 < 2; l791 = l791 + 1) {
			fRec790[l791] = 0.0f;
		}
		for (int l792 = 0; l792 < 3; l792 = l792 + 1) {
			fRec798[l792] = 0.0f;
		}
		for (int l793 = 0; l793 < 3; l793 = l793 + 1) {
			fRec797[l793] = 0.0f;
		}
		for (int l794 = 0; l794 < 3; l794 = l794 + 1) {
			fRec796[l794] = 0.0f;
		}
		for (int l795 = 0; l795 < 3; l795 = l795 + 1) {
			fRec795[l795] = 0.0f;
		}
		for (int l796 = 0; l796 < 2; l796 = l796 + 1) {
			fVec88[l796] = 0.0f;
		}
		for (int l797 = 0; l797 < 2; l797 = l797 + 1) {
			fRec794[l797] = 0.0f;
		}
		for (int l798 = 0; l798 < 32768; l798 = l798 + 1) {
			fRec793[l798] = 0.0f;
		}
		for (int l799 = 0; l799 < 2; l799 = l799 + 1) {
			fRec792[l799] = 0.0f;
		}
		for (int l800 = 0; l800 < 2; l800 = l800 + 1) {
			fRec799[l800] = 0.0f;
		}
		for (int l801 = 0; l801 < 3; l801 = l801 + 1) {
			fRec807[l801] = 0.0f;
		}
		for (int l802 = 0; l802 < 3; l802 = l802 + 1) {
			fRec806[l802] = 0.0f;
		}
		for (int l803 = 0; l803 < 3; l803 = l803 + 1) {
			fRec805[l803] = 0.0f;
		}
		for (int l804 = 0; l804 < 3; l804 = l804 + 1) {
			fRec804[l804] = 0.0f;
		}
		for (int l805 = 0; l805 < 2; l805 = l805 + 1) {
			fVec89[l805] = 0.0f;
		}
		for (int l806 = 0; l806 < 2; l806 = l806 + 1) {
			fRec803[l806] = 0.0f;
		}
		for (int l807 = 0; l807 < 32768; l807 = l807 + 1) {
			fRec802[l807] = 0.0f;
		}
		for (int l808 = 0; l808 < 2; l808 = l808 + 1) {
			fRec801[l808] = 0.0f;
		}
		for (int l809 = 0; l809 < 2; l809 = l809 + 1) {
			fRec808[l809] = 0.0f;
		}
		for (int l810 = 0; l810 < 3; l810 = l810 + 1) {
			fRec816[l810] = 0.0f;
		}
		for (int l811 = 0; l811 < 3; l811 = l811 + 1) {
			fRec815[l811] = 0.0f;
		}
		for (int l812 = 0; l812 < 3; l812 = l812 + 1) {
			fRec814[l812] = 0.0f;
		}
		for (int l813 = 0; l813 < 3; l813 = l813 + 1) {
			fRec813[l813] = 0.0f;
		}
		for (int l814 = 0; l814 < 2; l814 = l814 + 1) {
			fVec90[l814] = 0.0f;
		}
		for (int l815 = 0; l815 < 2; l815 = l815 + 1) {
			fRec812[l815] = 0.0f;
		}
		for (int l816 = 0; l816 < 32768; l816 = l816 + 1) {
			fRec811[l816] = 0.0f;
		}
		for (int l817 = 0; l817 < 2; l817 = l817 + 1) {
			fRec810[l817] = 0.0f;
		}
		for (int l818 = 0; l818 < 2; l818 = l818 + 1) {
			fRec817[l818] = 0.0f;
		}
		for (int l819 = 0; l819 < 3; l819 = l819 + 1) {
			fRec825[l819] = 0.0f;
		}
		for (int l820 = 0; l820 < 3; l820 = l820 + 1) {
			fRec824[l820] = 0.0f;
		}
		for (int l821 = 0; l821 < 3; l821 = l821 + 1) {
			fRec823[l821] = 0.0f;
		}
		for (int l822 = 0; l822 < 3; l822 = l822 + 1) {
			fRec822[l822] = 0.0f;
		}
		for (int l823 = 0; l823 < 2; l823 = l823 + 1) {
			fVec91[l823] = 0.0f;
		}
		for (int l824 = 0; l824 < 2; l824 = l824 + 1) {
			fRec821[l824] = 0.0f;
		}
		for (int l825 = 0; l825 < 32768; l825 = l825 + 1) {
			fRec820[l825] = 0.0f;
		}
		for (int l826 = 0; l826 < 2; l826 = l826 + 1) {
			fRec819[l826] = 0.0f;
		}
		for (int l827 = 0; l827 < 2; l827 = l827 + 1) {
			fRec826[l827] = 0.0f;
		}
		for (int l828 = 0; l828 < 3; l828 = l828 + 1) {
			fRec834[l828] = 0.0f;
		}
		for (int l829 = 0; l829 < 3; l829 = l829 + 1) {
			fRec833[l829] = 0.0f;
		}
		for (int l830 = 0; l830 < 3; l830 = l830 + 1) {
			fRec832[l830] = 0.0f;
		}
		for (int l831 = 0; l831 < 3; l831 = l831 + 1) {
			fRec831[l831] = 0.0f;
		}
		for (int l832 = 0; l832 < 2; l832 = l832 + 1) {
			fVec92[l832] = 0.0f;
		}
		for (int l833 = 0; l833 < 2; l833 = l833 + 1) {
			fRec830[l833] = 0.0f;
		}
		for (int l834 = 0; l834 < 32768; l834 = l834 + 1) {
			fRec829[l834] = 0.0f;
		}
		for (int l835 = 0; l835 < 2; l835 = l835 + 1) {
			fRec828[l835] = 0.0f;
		}
		for (int l836 = 0; l836 < 2; l836 = l836 + 1) {
			fRec835[l836] = 0.0f;
		}
		for (int l837 = 0; l837 < 3; l837 = l837 + 1) {
			fRec843[l837] = 0.0f;
		}
		for (int l838 = 0; l838 < 3; l838 = l838 + 1) {
			fRec842[l838] = 0.0f;
		}
		for (int l839 = 0; l839 < 3; l839 = l839 + 1) {
			fRec841[l839] = 0.0f;
		}
		for (int l840 = 0; l840 < 3; l840 = l840 + 1) {
			fRec840[l840] = 0.0f;
		}
		for (int l841 = 0; l841 < 2; l841 = l841 + 1) {
			fVec93[l841] = 0.0f;
		}
		for (int l842 = 0; l842 < 2; l842 = l842 + 1) {
			fRec839[l842] = 0.0f;
		}
		for (int l843 = 0; l843 < 32768; l843 = l843 + 1) {
			fRec838[l843] = 0.0f;
		}
		for (int l844 = 0; l844 < 2; l844 = l844 + 1) {
			fRec837[l844] = 0.0f;
		}
		for (int l845 = 0; l845 < 2; l845 = l845 + 1) {
			fRec844[l845] = 0.0f;
		}
		for (int l846 = 0; l846 < 3; l846 = l846 + 1) {
			fRec852[l846] = 0.0f;
		}
		for (int l847 = 0; l847 < 3; l847 = l847 + 1) {
			fRec851[l847] = 0.0f;
		}
		for (int l848 = 0; l848 < 3; l848 = l848 + 1) {
			fRec850[l848] = 0.0f;
		}
		for (int l849 = 0; l849 < 3; l849 = l849 + 1) {
			fRec849[l849] = 0.0f;
		}
		for (int l850 = 0; l850 < 2; l850 = l850 + 1) {
			fVec94[l850] = 0.0f;
		}
		for (int l851 = 0; l851 < 2; l851 = l851 + 1) {
			fRec848[l851] = 0.0f;
		}
		for (int l852 = 0; l852 < 32768; l852 = l852 + 1) {
			fRec847[l852] = 0.0f;
		}
		for (int l853 = 0; l853 < 2; l853 = l853 + 1) {
			fRec846[l853] = 0.0f;
		}
		for (int l854 = 0; l854 < 2; l854 = l854 + 1) {
			fRec853[l854] = 0.0f;
		}
		for (int l855 = 0; l855 < 3; l855 = l855 + 1) {
			fRec861[l855] = 0.0f;
		}
		for (int l856 = 0; l856 < 3; l856 = l856 + 1) {
			fRec860[l856] = 0.0f;
		}
		for (int l857 = 0; l857 < 3; l857 = l857 + 1) {
			fRec859[l857] = 0.0f;
		}
		for (int l858 = 0; l858 < 3; l858 = l858 + 1) {
			fRec858[l858] = 0.0f;
		}
		for (int l859 = 0; l859 < 2; l859 = l859 + 1) {
			fVec95[l859] = 0.0f;
		}
		for (int l860 = 0; l860 < 2; l860 = l860 + 1) {
			fRec857[l860] = 0.0f;
		}
		for (int l861 = 0; l861 < 32768; l861 = l861 + 1) {
			fRec856[l861] = 0.0f;
		}
		for (int l862 = 0; l862 < 2; l862 = l862 + 1) {
			fRec855[l862] = 0.0f;
		}
		for (int l863 = 0; l863 < 2; l863 = l863 + 1) {
			fRec862[l863] = 0.0f;
		}
		for (int l864 = 0; l864 < 3; l864 = l864 + 1) {
			fRec870[l864] = 0.0f;
		}
		for (int l865 = 0; l865 < 3; l865 = l865 + 1) {
			fRec869[l865] = 0.0f;
		}
		for (int l866 = 0; l866 < 3; l866 = l866 + 1) {
			fRec868[l866] = 0.0f;
		}
		for (int l867 = 0; l867 < 3; l867 = l867 + 1) {
			fRec867[l867] = 0.0f;
		}
		for (int l868 = 0; l868 < 2; l868 = l868 + 1) {
			fVec96[l868] = 0.0f;
		}
		for (int l869 = 0; l869 < 2; l869 = l869 + 1) {
			fRec866[l869] = 0.0f;
		}
		for (int l870 = 0; l870 < 32768; l870 = l870 + 1) {
			fRec865[l870] = 0.0f;
		}
		for (int l871 = 0; l871 < 2; l871 = l871 + 1) {
			fRec864[l871] = 0.0f;
		}
		for (int l872 = 0; l872 < 2; l872 = l872 + 1) {
			fRec871[l872] = 0.0f;
		}
		for (int l873 = 0; l873 < 3; l873 = l873 + 1) {
			fRec879[l873] = 0.0f;
		}
		for (int l874 = 0; l874 < 3; l874 = l874 + 1) {
			fRec878[l874] = 0.0f;
		}
		for (int l875 = 0; l875 < 3; l875 = l875 + 1) {
			fRec877[l875] = 0.0f;
		}
		for (int l876 = 0; l876 < 3; l876 = l876 + 1) {
			fRec876[l876] = 0.0f;
		}
		for (int l877 = 0; l877 < 2; l877 = l877 + 1) {
			fVec97[l877] = 0.0f;
		}
		for (int l878 = 0; l878 < 2; l878 = l878 + 1) {
			fRec875[l878] = 0.0f;
		}
		for (int l879 = 0; l879 < 32768; l879 = l879 + 1) {
			fRec874[l879] = 0.0f;
		}
		for (int l880 = 0; l880 < 2; l880 = l880 + 1) {
			fRec873[l880] = 0.0f;
		}
		for (int l881 = 0; l881 < 2; l881 = l881 + 1) {
			fRec880[l881] = 0.0f;
		}
		for (int l882 = 0; l882 < 3; l882 = l882 + 1) {
			fRec888[l882] = 0.0f;
		}
		for (int l883 = 0; l883 < 3; l883 = l883 + 1) {
			fRec887[l883] = 0.0f;
		}
		for (int l884 = 0; l884 < 3; l884 = l884 + 1) {
			fRec886[l884] = 0.0f;
		}
		for (int l885 = 0; l885 < 3; l885 = l885 + 1) {
			fRec885[l885] = 0.0f;
		}
		for (int l886 = 0; l886 < 2; l886 = l886 + 1) {
			fVec98[l886] = 0.0f;
		}
		for (int l887 = 0; l887 < 2; l887 = l887 + 1) {
			fRec884[l887] = 0.0f;
		}
		for (int l888 = 0; l888 < 32768; l888 = l888 + 1) {
			fRec883[l888] = 0.0f;
		}
		for (int l889 = 0; l889 < 2; l889 = l889 + 1) {
			fRec882[l889] = 0.0f;
		}
		for (int l890 = 0; l890 < 2; l890 = l890 + 1) {
			fRec889[l890] = 0.0f;
		}
		for (int l891 = 0; l891 < 3; l891 = l891 + 1) {
			fRec897[l891] = 0.0f;
		}
		for (int l892 = 0; l892 < 3; l892 = l892 + 1) {
			fRec896[l892] = 0.0f;
		}
		for (int l893 = 0; l893 < 3; l893 = l893 + 1) {
			fRec895[l893] = 0.0f;
		}
		for (int l894 = 0; l894 < 3; l894 = l894 + 1) {
			fRec894[l894] = 0.0f;
		}
		for (int l895 = 0; l895 < 2; l895 = l895 + 1) {
			fVec99[l895] = 0.0f;
		}
		for (int l896 = 0; l896 < 2; l896 = l896 + 1) {
			fRec893[l896] = 0.0f;
		}
		for (int l897 = 0; l897 < 32768; l897 = l897 + 1) {
			fRec892[l897] = 0.0f;
		}
		for (int l898 = 0; l898 < 2; l898 = l898 + 1) {
			fRec891[l898] = 0.0f;
		}
		for (int l899 = 0; l899 < 2; l899 = l899 + 1) {
			fRec898[l899] = 0.0f;
		}
		for (int l900 = 0; l900 < 3; l900 = l900 + 1) {
			fRec906[l900] = 0.0f;
		}
		for (int l901 = 0; l901 < 3; l901 = l901 + 1) {
			fRec905[l901] = 0.0f;
		}
		for (int l902 = 0; l902 < 3; l902 = l902 + 1) {
			fRec904[l902] = 0.0f;
		}
		for (int l903 = 0; l903 < 3; l903 = l903 + 1) {
			fRec903[l903] = 0.0f;
		}
		for (int l904 = 0; l904 < 2; l904 = l904 + 1) {
			fVec100[l904] = 0.0f;
		}
		for (int l905 = 0; l905 < 2; l905 = l905 + 1) {
			fRec902[l905] = 0.0f;
		}
		for (int l906 = 0; l906 < 32768; l906 = l906 + 1) {
			fRec901[l906] = 0.0f;
		}
		for (int l907 = 0; l907 < 2; l907 = l907 + 1) {
			fRec900[l907] = 0.0f;
		}
		for (int l908 = 0; l908 < 2; l908 = l908 + 1) {
			fRec907[l908] = 0.0f;
		}
		for (int l909 = 0; l909 < 3; l909 = l909 + 1) {
			fRec915[l909] = 0.0f;
		}
		for (int l910 = 0; l910 < 3; l910 = l910 + 1) {
			fRec914[l910] = 0.0f;
		}
		for (int l911 = 0; l911 < 3; l911 = l911 + 1) {
			fRec913[l911] = 0.0f;
		}
		for (int l912 = 0; l912 < 3; l912 = l912 + 1) {
			fRec912[l912] = 0.0f;
		}
		for (int l913 = 0; l913 < 2; l913 = l913 + 1) {
			fVec101[l913] = 0.0f;
		}
		for (int l914 = 0; l914 < 2; l914 = l914 + 1) {
			fRec911[l914] = 0.0f;
		}
		for (int l915 = 0; l915 < 32768; l915 = l915 + 1) {
			fRec910[l915] = 0.0f;
		}
		for (int l916 = 0; l916 < 2; l916 = l916 + 1) {
			fRec909[l916] = 0.0f;
		}
		for (int l917 = 0; l917 < 2; l917 = l917 + 1) {
			fRec916[l917] = 0.0f;
		}
		for (int l918 = 0; l918 < 3; l918 = l918 + 1) {
			fRec924[l918] = 0.0f;
		}
		for (int l919 = 0; l919 < 3; l919 = l919 + 1) {
			fRec923[l919] = 0.0f;
		}
		for (int l920 = 0; l920 < 3; l920 = l920 + 1) {
			fRec922[l920] = 0.0f;
		}
		for (int l921 = 0; l921 < 3; l921 = l921 + 1) {
			fRec921[l921] = 0.0f;
		}
		for (int l922 = 0; l922 < 2; l922 = l922 + 1) {
			fVec102[l922] = 0.0f;
		}
		for (int l923 = 0; l923 < 2; l923 = l923 + 1) {
			fRec920[l923] = 0.0f;
		}
		for (int l924 = 0; l924 < 32768; l924 = l924 + 1) {
			fRec919[l924] = 0.0f;
		}
		for (int l925 = 0; l925 < 2; l925 = l925 + 1) {
			fRec918[l925] = 0.0f;
		}
		for (int l926 = 0; l926 < 2; l926 = l926 + 1) {
			fRec925[l926] = 0.0f;
		}
		for (int l927 = 0; l927 < 3; l927 = l927 + 1) {
			fRec933[l927] = 0.0f;
		}
		for (int l928 = 0; l928 < 3; l928 = l928 + 1) {
			fRec932[l928] = 0.0f;
		}
		for (int l929 = 0; l929 < 3; l929 = l929 + 1) {
			fRec931[l929] = 0.0f;
		}
		for (int l930 = 0; l930 < 3; l930 = l930 + 1) {
			fRec930[l930] = 0.0f;
		}
		for (int l931 = 0; l931 < 2; l931 = l931 + 1) {
			fVec103[l931] = 0.0f;
		}
		for (int l932 = 0; l932 < 2; l932 = l932 + 1) {
			fRec929[l932] = 0.0f;
		}
		for (int l933 = 0; l933 < 32768; l933 = l933 + 1) {
			fRec928[l933] = 0.0f;
		}
		for (int l934 = 0; l934 < 2; l934 = l934 + 1) {
			fRec927[l934] = 0.0f;
		}
		for (int l935 = 0; l935 < 2; l935 = l935 + 1) {
			fRec934[l935] = 0.0f;
		}
		for (int l936 = 0; l936 < 3; l936 = l936 + 1) {
			fRec942[l936] = 0.0f;
		}
		for (int l937 = 0; l937 < 3; l937 = l937 + 1) {
			fRec941[l937] = 0.0f;
		}
		for (int l938 = 0; l938 < 3; l938 = l938 + 1) {
			fRec940[l938] = 0.0f;
		}
		for (int l939 = 0; l939 < 3; l939 = l939 + 1) {
			fRec939[l939] = 0.0f;
		}
		for (int l940 = 0; l940 < 2; l940 = l940 + 1) {
			fVec104[l940] = 0.0f;
		}
		for (int l941 = 0; l941 < 2; l941 = l941 + 1) {
			fRec938[l941] = 0.0f;
		}
		for (int l942 = 0; l942 < 32768; l942 = l942 + 1) {
			fRec937[l942] = 0.0f;
		}
		for (int l943 = 0; l943 < 2; l943 = l943 + 1) {
			fRec936[l943] = 0.0f;
		}
		for (int l944 = 0; l944 < 2; l944 = l944 + 1) {
			fRec943[l944] = 0.0f;
		}
	}
	
	virtual void init(int sample_rate) {
		classInit(sample_rate);
		instanceInit(sample_rate);
	}
	virtual void instanceInit(int sample_rate) {
		instanceConstants(sample_rate);
		instanceResetUserInterface();
		instanceClear();
	}
	
	virtual mydsp* clone() {
		return new mydsp();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("polyphonic_detection");
		ui_interface->addHorizontalSlider("attack", &fHslider3, FAUSTFLOAT(0.100000001f), FAUSTFLOAT(0.0500000007f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00999999978f));
		ui_interface->addHorizontalSlider("release", &fHslider2, FAUSTFLOAT(0.100000001f), FAUSTFLOAT(0.00999999978f), FAUSTFLOAT(3.0f), FAUSTFLOAT(0.00999999978f));
		ui_interface->addHorizontalSlider("rms", &fHslider0, FAUSTFLOAT(0.00999999978f), FAUSTFLOAT(9.99999975e-05f), FAUSTFLOAT(0.100000001f), FAUSTFLOAT(9.99999975e-06f));
		ui_interface->addHorizontalSlider("thresh", &fHslider1, FAUSTFLOAT(0.00100000005f), FAUSTFLOAT(9.99999975e-05f), FAUSTFLOAT(1.0f), FAUSTFLOAT(9.99999975e-05f));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		FAUSTFLOAT* output2 = outputs[2];
		FAUSTFLOAT* output3 = outputs[3];
		FAUSTFLOAT* output4 = outputs[4];
		FAUSTFLOAT* output5 = outputs[5];
		FAUSTFLOAT* output6 = outputs[6];
		FAUSTFLOAT* output7 = outputs[7];
		FAUSTFLOAT* output8 = outputs[8];
		FAUSTFLOAT* output9 = outputs[9];
		FAUSTFLOAT* output10 = outputs[10];
		FAUSTFLOAT* output11 = outputs[11];
		FAUSTFLOAT* output12 = outputs[12];
		FAUSTFLOAT* output13 = outputs[13];
		FAUSTFLOAT* output14 = outputs[14];
		FAUSTFLOAT* output15 = outputs[15];
		FAUSTFLOAT* output16 = outputs[16];
		FAUSTFLOAT* output17 = outputs[17];
		FAUSTFLOAT* output18 = outputs[18];
		FAUSTFLOAT* output19 = outputs[19];
		FAUSTFLOAT* output20 = outputs[20];
		FAUSTFLOAT* output21 = outputs[21];
		FAUSTFLOAT* output22 = outputs[22];
		FAUSTFLOAT* output23 = outputs[23];
		FAUSTFLOAT* output24 = outputs[24];
		FAUSTFLOAT* output25 = outputs[25];
		FAUSTFLOAT* output26 = outputs[26];
		FAUSTFLOAT* output27 = outputs[27];
		FAUSTFLOAT* output28 = outputs[28];
		FAUSTFLOAT* output29 = outputs[29];
		FAUSTFLOAT* output30 = outputs[30];
		FAUSTFLOAT* output31 = outputs[31];
		FAUSTFLOAT* output32 = outputs[32];
		FAUSTFLOAT* output33 = outputs[33];
		FAUSTFLOAT* output34 = outputs[34];
		FAUSTFLOAT* output35 = outputs[35];
		FAUSTFLOAT* output36 = outputs[36];
		FAUSTFLOAT* output37 = outputs[37];
		FAUSTFLOAT* output38 = outputs[38];
		FAUSTFLOAT* output39 = outputs[39];
		FAUSTFLOAT* output40 = outputs[40];
		FAUSTFLOAT* output41 = outputs[41];
		FAUSTFLOAT* output42 = outputs[42];
		FAUSTFLOAT* output43 = outputs[43];
		FAUSTFLOAT* output44 = outputs[44];
		FAUSTFLOAT* output45 = outputs[45];
		FAUSTFLOAT* output46 = outputs[46];
		FAUSTFLOAT* output47 = outputs[47];
		FAUSTFLOAT* output48 = outputs[48];
		FAUSTFLOAT* output49 = outputs[49];
		FAUSTFLOAT* output50 = outputs[50];
		FAUSTFLOAT* output51 = outputs[51];
		FAUSTFLOAT* output52 = outputs[52];
		FAUSTFLOAT* output53 = outputs[53];
		FAUSTFLOAT* output54 = outputs[54];
		FAUSTFLOAT* output55 = outputs[55];
		FAUSTFLOAT* output56 = outputs[56];
		FAUSTFLOAT* output57 = outputs[57];
		FAUSTFLOAT* output58 = outputs[58];
		FAUSTFLOAT* output59 = outputs[59];
		FAUSTFLOAT* output60 = outputs[60];
		FAUSTFLOAT* output61 = outputs[61];
		FAUSTFLOAT* output62 = outputs[62];
		FAUSTFLOAT* output63 = outputs[63];
		FAUSTFLOAT* output64 = outputs[64];
		FAUSTFLOAT* output65 = outputs[65];
		FAUSTFLOAT* output66 = outputs[66];
		FAUSTFLOAT* output67 = outputs[67];
		FAUSTFLOAT* output68 = outputs[68];
		FAUSTFLOAT* output69 = outputs[69];
		FAUSTFLOAT* output70 = outputs[70];
		FAUSTFLOAT* output71 = outputs[71];
		FAUSTFLOAT* output72 = outputs[72];
		FAUSTFLOAT* output73 = outputs[73];
		FAUSTFLOAT* output74 = outputs[74];
		FAUSTFLOAT* output75 = outputs[75];
		FAUSTFLOAT* output76 = outputs[76];
		FAUSTFLOAT* output77 = outputs[77];
		FAUSTFLOAT* output78 = outputs[78];
		FAUSTFLOAT* output79 = outputs[79];
		FAUSTFLOAT* output80 = outputs[80];
		FAUSTFLOAT* output81 = outputs[81];
		FAUSTFLOAT* output82 = outputs[82];
		FAUSTFLOAT* output83 = outputs[83];
		FAUSTFLOAT* output84 = outputs[84];
		FAUSTFLOAT* output85 = outputs[85];
		FAUSTFLOAT* output86 = outputs[86];
		FAUSTFLOAT* output87 = outputs[87];
		FAUSTFLOAT* output88 = outputs[88];
		FAUSTFLOAT* output89 = outputs[89];
		FAUSTFLOAT* output90 = outputs[90];
		FAUSTFLOAT* output91 = outputs[91];
		FAUSTFLOAT* output92 = outputs[92];
		FAUSTFLOAT* output93 = outputs[93];
		FAUSTFLOAT* output94 = outputs[94];
		FAUSTFLOAT* output95 = outputs[95];
		FAUSTFLOAT* output96 = outputs[96];
		FAUSTFLOAT* output97 = outputs[97];
		FAUSTFLOAT* output98 = outputs[98];
		FAUSTFLOAT* output99 = outputs[99];
		FAUSTFLOAT* output100 = outputs[100];
		FAUSTFLOAT* output101 = outputs[101];
		FAUSTFLOAT* output102 = outputs[102];
		FAUSTFLOAT* output103 = outputs[103];
		FAUSTFLOAT* output104 = outputs[104];
		float fSlow0 = std::rint(fConst0 * float(fHslider0));
		float fSlow1 = 1.0f / fSlow0;
		int iSlow2 = int(std::max<float>(0.0f, fSlow0));
		float fSlow3 = float(fHslider1);
		float fSlow4 = float(fHslider2);
		float fSlow5 = float(fHslider3);
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			float fTemp0 = float(input0[i0]);
			fRec6[0] = fTemp0 - fConst13 * (fConst14 * fRec6[1] + fConst15 * fRec6[2]);
			fRec5[0] = fConst12 * fRec6[2] + fConst13 * (fConst9 * fRec6[0] - (fConst14 * fRec5[1] + fConst15 * fRec5[2]));
			fRec4[0] = fConst12 * fRec5[2] + fConst13 * (fConst9 * fRec5[0] - (fConst14 * fRec4[1] + fConst15 * fRec4[2]));
			fRec3[0] = fConst12 * fRec4[2] + fConst13 * (fConst9 * fRec4[0] - (fConst14 * fRec3[1] + fConst15 * fRec3[2]));
			float fTemp1 = fConst12 * fRec3[2];
			float fTemp2 = fConst11 * fRec3[0];
			fVec0[0] = fTemp2 + fTemp1;
			fRec2[0] = (fTemp1 + 0.995000005f * fRec2[1] + fTemp2) - fVec0[1];
			fRec1[IOTA0 & 32767] = fRec1[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec2[0]);
			float fTemp3 = std::sqrt(fSlow1 * (fRec1[IOTA0 & 32767] - fRec1[(IOTA0 - iSlow2) & 32767]));
			int iTemp4 = ((fTemp3 > fSlow3) ? fTemp3 : 0.0f) > 0.0f > 0;
			int iTemp5 = iTemp4;
			float fTemp6 = 0.144717798f * ((iTemp5) ? fSlow5 : fSlow4);
			int iTemp7 = std::fabs(fTemp6) < 1.1920929e-07f;
			float fThen3 = std::exp(0.0f - fConst6 / ((iTemp7) ? 1.0f : fTemp6));
			float fTemp8 = ((iTemp7) ? 0.0f : fThen3);
			float fElse4 = float(iTemp4);
			fRec0[0] = (1.0f - fTemp8) * ((iTemp5) ? fElse4 : 0.0f) + fTemp8 * fRec0[1];
			float fTemp9 = fConst16 + fRec7[1] + -1.0f;
			int iTemp10 = fTemp9 < 0.0f;
			float fTemp11 = fConst16 + fRec7[1];
			fRec7[0] = ((iTemp10) ? fTemp11 : fTemp9);
			float fThen6 = fConst16 + fRec7[1] + fConst17 * fTemp9;
			float fRec8 = ((iTemp10) ? fTemp11 : fThen6);
			output0[i0] = FAUSTFLOAT(fRec0[0] * (2.0f * fRec8 + -1.0f));
			fRec15[0] = fTemp0 - fConst27 * (fConst28 * fRec15[1] + fConst29 * fRec15[2]);
			fRec14[0] = fConst26 * fRec15[2] + fConst27 * (fConst23 * fRec15[0] - (fConst28 * fRec14[1] + fConst29 * fRec14[2]));
			fRec13[0] = fConst26 * fRec14[2] + fConst27 * (fConst23 * fRec14[0] - (fConst28 * fRec13[1] + fConst29 * fRec13[2]));
			fRec12[0] = fConst26 * fRec13[2] + fConst27 * (fConst23 * fRec13[0] - (fConst28 * fRec12[1] + fConst29 * fRec12[2]));
			float fTemp12 = fConst26 * fRec12[2];
			float fTemp13 = fConst25 * fRec12[0];
			fVec1[0] = fTemp13 + fTemp12;
			fRec11[0] = (fTemp12 + 0.995000005f * fRec11[1] + fTemp13) - fVec1[1];
			fRec10[IOTA0 & 32767] = fRec10[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec11[0]);
			float fTemp14 = std::sqrt(fSlow1 * (fRec10[IOTA0 & 32767] - fRec10[(IOTA0 - iSlow2) & 32767]));
			int iTemp15 = ((fTemp14 > fSlow3) ? fTemp14 : 0.0f) > 0.0f > 0;
			int iTemp16 = iTemp15;
			float fTemp17 = 0.144717798f * ((iTemp16) ? fSlow5 : fSlow4);
			int iTemp18 = std::fabs(fTemp17) < 1.1920929e-07f;
			float fThen10 = std::exp(0.0f - fConst6 / ((iTemp18) ? 1.0f : fTemp17));
			float fTemp19 = ((iTemp18) ? 0.0f : fThen10);
			float fElse11 = float(iTemp15);
			fRec9[0] = (1.0f - fTemp19) * ((iTemp16) ? fElse11 : 0.0f) + fTemp19 * fRec9[1];
			float fTemp20 = fConst30 + fRec16[1] + -1.0f;
			int iTemp21 = fTemp20 < 0.0f;
			float fTemp22 = fConst30 + fRec16[1];
			fRec16[0] = ((iTemp21) ? fTemp22 : fTemp20);
			float fThen13 = fConst30 + fRec16[1] + fConst31 * fTemp20;
			float fRec17 = ((iTemp21) ? fTemp22 : fThen13);
			output1[i0] = FAUSTFLOAT(fRec9[0] * (2.0f * fRec17 + -1.0f));
			fRec24[0] = fTemp0 - fConst41 * (fConst42 * fRec24[1] + fConst43 * fRec24[2]);
			fRec23[0] = fConst40 * fRec24[2] + fConst41 * (fConst37 * fRec24[0] - (fConst42 * fRec23[1] + fConst43 * fRec23[2]));
			fRec22[0] = fConst40 * fRec23[2] + fConst41 * (fConst37 * fRec23[0] - (fConst42 * fRec22[1] + fConst43 * fRec22[2]));
			fRec21[0] = fConst40 * fRec22[2] + fConst41 * (fConst37 * fRec22[0] - (fConst42 * fRec21[1] + fConst43 * fRec21[2]));
			float fTemp23 = fConst40 * fRec21[2];
			float fTemp24 = fConst39 * fRec21[0];
			fVec2[0] = fTemp24 + fTemp23;
			fRec20[0] = (fTemp23 + 0.995000005f * fRec20[1] + fTemp24) - fVec2[1];
			fRec19[IOTA0 & 32767] = fRec19[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec20[0]);
			float fTemp25 = std::sqrt(fSlow1 * (fRec19[IOTA0 & 32767] - fRec19[(IOTA0 - iSlow2) & 32767]));
			int iTemp26 = ((fTemp25 > fSlow3) ? fTemp25 : 0.0f) > 0.0f > 0;
			int iTemp27 = iTemp26;
			float fTemp28 = 0.144717798f * ((iTemp27) ? fSlow5 : fSlow4);
			int iTemp29 = std::fabs(fTemp28) < 1.1920929e-07f;
			float fThen17 = std::exp(0.0f - fConst6 / ((iTemp29) ? 1.0f : fTemp28));
			float fTemp30 = ((iTemp29) ? 0.0f : fThen17);
			float fElse18 = float(iTemp26);
			fRec18[0] = (1.0f - fTemp30) * ((iTemp27) ? fElse18 : 0.0f) + fTemp30 * fRec18[1];
			float fTemp31 = fConst44 + fRec25[1] + -1.0f;
			int iTemp32 = fTemp31 < 0.0f;
			float fTemp33 = fConst44 + fRec25[1];
			fRec25[0] = ((iTemp32) ? fTemp33 : fTemp31);
			float fThen20 = fConst44 + fRec25[1] + fConst45 * fTemp31;
			float fRec26 = ((iTemp32) ? fTemp33 : fThen20);
			output2[i0] = FAUSTFLOAT(fRec18[0] * (2.0f * fRec26 + -1.0f));
			fRec33[0] = fTemp0 - fConst55 * (fConst56 * fRec33[1] + fConst57 * fRec33[2]);
			fRec32[0] = fConst54 * fRec33[2] + fConst55 * (fConst51 * fRec33[0] - (fConst56 * fRec32[1] + fConst57 * fRec32[2]));
			fRec31[0] = fConst54 * fRec32[2] + fConst55 * (fConst51 * fRec32[0] - (fConst56 * fRec31[1] + fConst57 * fRec31[2]));
			fRec30[0] = fConst54 * fRec31[2] + fConst55 * (fConst51 * fRec31[0] - (fConst56 * fRec30[1] + fConst57 * fRec30[2]));
			float fTemp34 = fConst54 * fRec30[2];
			float fTemp35 = fConst53 * fRec30[0];
			fVec3[0] = fTemp35 + fTemp34;
			fRec29[0] = (fTemp34 + 0.995000005f * fRec29[1] + fTemp35) - fVec3[1];
			fRec28[IOTA0 & 32767] = fRec28[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec29[0]);
			float fTemp36 = std::sqrt(fSlow1 * (fRec28[IOTA0 & 32767] - fRec28[(IOTA0 - iSlow2) & 32767]));
			int iTemp37 = ((fTemp36 > fSlow3) ? fTemp36 : 0.0f) > 0.0f > 0;
			int iTemp38 = iTemp37;
			float fTemp39 = 0.144717798f * ((iTemp38) ? fSlow5 : fSlow4);
			int iTemp40 = std::fabs(fTemp39) < 1.1920929e-07f;
			float fThen24 = std::exp(0.0f - fConst6 / ((iTemp40) ? 1.0f : fTemp39));
			float fTemp41 = ((iTemp40) ? 0.0f : fThen24);
			float fElse25 = float(iTemp37);
			fRec27[0] = (1.0f - fTemp41) * ((iTemp38) ? fElse25 : 0.0f) + fTemp41 * fRec27[1];
			float fTemp42 = fConst58 + fRec34[1] + -1.0f;
			int iTemp43 = fTemp42 < 0.0f;
			float fTemp44 = fConst58 + fRec34[1];
			fRec34[0] = ((iTemp43) ? fTemp44 : fTemp42);
			float fThen27 = fConst58 + fRec34[1] + fConst59 * fTemp42;
			float fRec35 = ((iTemp43) ? fTemp44 : fThen27);
			output3[i0] = FAUSTFLOAT(fRec27[0] * (2.0f * fRec35 + -1.0f));
			fRec42[0] = fTemp0 - fConst69 * (fConst70 * fRec42[1] + fConst71 * fRec42[2]);
			fRec41[0] = fConst68 * fRec42[2] + fConst69 * (fConst65 * fRec42[0] - (fConst70 * fRec41[1] + fConst71 * fRec41[2]));
			fRec40[0] = fConst68 * fRec41[2] + fConst69 * (fConst65 * fRec41[0] - (fConst70 * fRec40[1] + fConst71 * fRec40[2]));
			fRec39[0] = fConst68 * fRec40[2] + fConst69 * (fConst65 * fRec40[0] - (fConst70 * fRec39[1] + fConst71 * fRec39[2]));
			float fTemp45 = fConst68 * fRec39[2];
			float fTemp46 = fConst67 * fRec39[0];
			fVec4[0] = fTemp46 + fTemp45;
			fRec38[0] = (fTemp45 + 0.995000005f * fRec38[1] + fTemp46) - fVec4[1];
			fRec37[IOTA0 & 32767] = fRec37[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec38[0]);
			float fTemp47 = std::sqrt(fSlow1 * (fRec37[IOTA0 & 32767] - fRec37[(IOTA0 - iSlow2) & 32767]));
			int iTemp48 = ((fTemp47 > fSlow3) ? fTemp47 : 0.0f) > 0.0f > 0;
			int iTemp49 = iTemp48;
			float fTemp50 = 0.144717798f * ((iTemp49) ? fSlow5 : fSlow4);
			int iTemp51 = std::fabs(fTemp50) < 1.1920929e-07f;
			float fThen31 = std::exp(0.0f - fConst6 / ((iTemp51) ? 1.0f : fTemp50));
			float fTemp52 = ((iTemp51) ? 0.0f : fThen31);
			float fElse32 = float(iTemp48);
			fRec36[0] = (1.0f - fTemp52) * ((iTemp49) ? fElse32 : 0.0f) + fTemp52 * fRec36[1];
			float fTemp53 = fConst72 + fRec43[1] + -1.0f;
			int iTemp54 = fTemp53 < 0.0f;
			float fTemp55 = fConst72 + fRec43[1];
			fRec43[0] = ((iTemp54) ? fTemp55 : fTemp53);
			float fThen34 = fConst72 + fRec43[1] + fConst73 * fTemp53;
			float fRec44 = ((iTemp54) ? fTemp55 : fThen34);
			output4[i0] = FAUSTFLOAT(fRec36[0] * (2.0f * fRec44 + -1.0f));
			fRec51[0] = fTemp0 - fConst83 * (fConst84 * fRec51[1] + fConst85 * fRec51[2]);
			fRec50[0] = fConst82 * fRec51[2] + fConst83 * (fConst79 * fRec51[0] - (fConst84 * fRec50[1] + fConst85 * fRec50[2]));
			fRec49[0] = fConst82 * fRec50[2] + fConst83 * (fConst79 * fRec50[0] - (fConst84 * fRec49[1] + fConst85 * fRec49[2]));
			fRec48[0] = fConst82 * fRec49[2] + fConst83 * (fConst79 * fRec49[0] - (fConst84 * fRec48[1] + fConst85 * fRec48[2]));
			float fTemp56 = fConst82 * fRec48[2];
			float fTemp57 = fConst81 * fRec48[0];
			fVec5[0] = fTemp57 + fTemp56;
			fRec47[0] = (fTemp56 + 0.995000005f * fRec47[1] + fTemp57) - fVec5[1];
			fRec46[IOTA0 & 32767] = fRec46[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec47[0]);
			float fTemp58 = std::sqrt(fSlow1 * (fRec46[IOTA0 & 32767] - fRec46[(IOTA0 - iSlow2) & 32767]));
			int iTemp59 = ((fTemp58 > fSlow3) ? fTemp58 : 0.0f) > 0.0f > 0;
			int iTemp60 = iTemp59;
			float fTemp61 = 0.144717798f * ((iTemp60) ? fSlow5 : fSlow4);
			int iTemp62 = std::fabs(fTemp61) < 1.1920929e-07f;
			float fThen38 = std::exp(0.0f - fConst6 / ((iTemp62) ? 1.0f : fTemp61));
			float fTemp63 = ((iTemp62) ? 0.0f : fThen38);
			float fElse39 = float(iTemp59);
			fRec45[0] = (1.0f - fTemp63) * ((iTemp60) ? fElse39 : 0.0f) + fTemp63 * fRec45[1];
			float fTemp64 = fConst86 + fRec52[1] + -1.0f;
			int iTemp65 = fTemp64 < 0.0f;
			float fTemp66 = fConst86 + fRec52[1];
			fRec52[0] = ((iTemp65) ? fTemp66 : fTemp64);
			float fThen41 = fConst86 + fRec52[1] + fConst87 * fTemp64;
			float fRec53 = ((iTemp65) ? fTemp66 : fThen41);
			output5[i0] = FAUSTFLOAT(fRec45[0] * (2.0f * fRec53 + -1.0f));
			fRec60[0] = fTemp0 - fConst97 * (fConst98 * fRec60[1] + fConst99 * fRec60[2]);
			fRec59[0] = fConst96 * fRec60[2] + fConst97 * (fConst93 * fRec60[0] - (fConst98 * fRec59[1] + fConst99 * fRec59[2]));
			fRec58[0] = fConst96 * fRec59[2] + fConst97 * (fConst93 * fRec59[0] - (fConst98 * fRec58[1] + fConst99 * fRec58[2]));
			fRec57[0] = fConst96 * fRec58[2] + fConst97 * (fConst93 * fRec58[0] - (fConst98 * fRec57[1] + fConst99 * fRec57[2]));
			float fTemp67 = fConst96 * fRec57[2];
			float fTemp68 = fConst95 * fRec57[0];
			fVec6[0] = fTemp68 + fTemp67;
			fRec56[0] = (fTemp67 + 0.995000005f * fRec56[1] + fTemp68) - fVec6[1];
			fRec55[IOTA0 & 32767] = fRec55[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec56[0]);
			float fTemp69 = std::sqrt(fSlow1 * (fRec55[IOTA0 & 32767] - fRec55[(IOTA0 - iSlow2) & 32767]));
			int iTemp70 = ((fTemp69 > fSlow3) ? fTemp69 : 0.0f) > 0.0f > 0;
			int iTemp71 = iTemp70;
			float fTemp72 = 0.144717798f * ((iTemp71) ? fSlow5 : fSlow4);
			int iTemp73 = std::fabs(fTemp72) < 1.1920929e-07f;
			float fThen45 = std::exp(0.0f - fConst6 / ((iTemp73) ? 1.0f : fTemp72));
			float fTemp74 = ((iTemp73) ? 0.0f : fThen45);
			float fElse46 = float(iTemp70);
			fRec54[0] = (1.0f - fTemp74) * ((iTemp71) ? fElse46 : 0.0f) + fTemp74 * fRec54[1];
			float fTemp75 = fConst100 + fRec61[1] + -1.0f;
			int iTemp76 = fTemp75 < 0.0f;
			float fTemp77 = fConst100 + fRec61[1];
			fRec61[0] = ((iTemp76) ? fTemp77 : fTemp75);
			float fThen48 = fConst100 + fRec61[1] + fConst101 * fTemp75;
			float fRec62 = ((iTemp76) ? fTemp77 : fThen48);
			output6[i0] = FAUSTFLOAT(fRec54[0] * (2.0f * fRec62 + -1.0f));
			fRec69[0] = fTemp0 - fConst111 * (fConst112 * fRec69[1] + fConst113 * fRec69[2]);
			fRec68[0] = fConst110 * fRec69[2] + fConst111 * (fConst107 * fRec69[0] - (fConst112 * fRec68[1] + fConst113 * fRec68[2]));
			fRec67[0] = fConst110 * fRec68[2] + fConst111 * (fConst107 * fRec68[0] - (fConst112 * fRec67[1] + fConst113 * fRec67[2]));
			fRec66[0] = fConst110 * fRec67[2] + fConst111 * (fConst107 * fRec67[0] - (fConst112 * fRec66[1] + fConst113 * fRec66[2]));
			float fTemp78 = fConst110 * fRec66[2];
			float fTemp79 = fConst109 * fRec66[0];
			fVec7[0] = fTemp79 + fTemp78;
			fRec65[0] = (fTemp78 + 0.995000005f * fRec65[1] + fTemp79) - fVec7[1];
			fRec64[IOTA0 & 32767] = fRec64[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec65[0]);
			float fTemp80 = std::sqrt(fSlow1 * (fRec64[IOTA0 & 32767] - fRec64[(IOTA0 - iSlow2) & 32767]));
			int iTemp81 = ((fTemp80 > fSlow3) ? fTemp80 : 0.0f) > 0.0f > 0;
			int iTemp82 = iTemp81;
			float fTemp83 = 0.144717798f * ((iTemp82) ? fSlow5 : fSlow4);
			int iTemp84 = std::fabs(fTemp83) < 1.1920929e-07f;
			float fThen52 = std::exp(0.0f - fConst6 / ((iTemp84) ? 1.0f : fTemp83));
			float fTemp85 = ((iTemp84) ? 0.0f : fThen52);
			float fElse53 = float(iTemp81);
			fRec63[0] = (1.0f - fTemp85) * ((iTemp82) ? fElse53 : 0.0f) + fTemp85 * fRec63[1];
			float fTemp86 = fConst114 + fRec70[1] + -1.0f;
			int iTemp87 = fTemp86 < 0.0f;
			float fTemp88 = fConst114 + fRec70[1];
			fRec70[0] = ((iTemp87) ? fTemp88 : fTemp86);
			float fThen55 = fConst114 + fRec70[1] + fConst115 * fTemp86;
			float fRec71 = ((iTemp87) ? fTemp88 : fThen55);
			output7[i0] = FAUSTFLOAT(fRec63[0] * (2.0f * fRec71 + -1.0f));
			fRec78[0] = fTemp0 - fConst125 * (fConst126 * fRec78[1] + fConst127 * fRec78[2]);
			fRec77[0] = fConst124 * fRec78[2] + fConst125 * (fConst121 * fRec78[0] - (fConst126 * fRec77[1] + fConst127 * fRec77[2]));
			fRec76[0] = fConst124 * fRec77[2] + fConst125 * (fConst121 * fRec77[0] - (fConst126 * fRec76[1] + fConst127 * fRec76[2]));
			fRec75[0] = fConst124 * fRec76[2] + fConst125 * (fConst121 * fRec76[0] - (fConst126 * fRec75[1] + fConst127 * fRec75[2]));
			float fTemp89 = fConst124 * fRec75[2];
			float fTemp90 = fConst123 * fRec75[0];
			fVec8[0] = fTemp90 + fTemp89;
			fRec74[0] = (fTemp89 + 0.995000005f * fRec74[1] + fTemp90) - fVec8[1];
			fRec73[IOTA0 & 32767] = fRec73[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec74[0]);
			float fTemp91 = std::sqrt(fSlow1 * (fRec73[IOTA0 & 32767] - fRec73[(IOTA0 - iSlow2) & 32767]));
			int iTemp92 = ((fTemp91 > fSlow3) ? fTemp91 : 0.0f) > 0.0f > 0;
			int iTemp93 = iTemp92;
			float fTemp94 = 0.144717798f * ((iTemp93) ? fSlow5 : fSlow4);
			int iTemp95 = std::fabs(fTemp94) < 1.1920929e-07f;
			float fThen59 = std::exp(0.0f - fConst6 / ((iTemp95) ? 1.0f : fTemp94));
			float fTemp96 = ((iTemp95) ? 0.0f : fThen59);
			float fElse60 = float(iTemp92);
			fRec72[0] = (1.0f - fTemp96) * ((iTemp93) ? fElse60 : 0.0f) + fTemp96 * fRec72[1];
			float fTemp97 = fConst128 + fRec79[1] + -1.0f;
			int iTemp98 = fTemp97 < 0.0f;
			float fTemp99 = fConst128 + fRec79[1];
			fRec79[0] = ((iTemp98) ? fTemp99 : fTemp97);
			float fThen62 = fConst128 + fRec79[1] + fConst129 * fTemp97;
			float fRec80 = ((iTemp98) ? fTemp99 : fThen62);
			output8[i0] = FAUSTFLOAT(fRec72[0] * (2.0f * fRec80 + -1.0f));
			fRec87[0] = fTemp0 - fConst139 * (fConst140 * fRec87[1] + fConst141 * fRec87[2]);
			fRec86[0] = fConst138 * fRec87[2] + fConst139 * (fConst135 * fRec87[0] - (fConst140 * fRec86[1] + fConst141 * fRec86[2]));
			fRec85[0] = fConst138 * fRec86[2] + fConst139 * (fConst135 * fRec86[0] - (fConst140 * fRec85[1] + fConst141 * fRec85[2]));
			fRec84[0] = fConst138 * fRec85[2] + fConst139 * (fConst135 * fRec85[0] - (fConst140 * fRec84[1] + fConst141 * fRec84[2]));
			float fTemp100 = fConst138 * fRec84[2];
			float fTemp101 = fConst137 * fRec84[0];
			fVec9[0] = fTemp101 + fTemp100;
			fRec83[0] = (fTemp100 + 0.995000005f * fRec83[1] + fTemp101) - fVec9[1];
			fRec82[IOTA0 & 32767] = fRec82[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec83[0]);
			float fTemp102 = std::sqrt(fSlow1 * (fRec82[IOTA0 & 32767] - fRec82[(IOTA0 - iSlow2) & 32767]));
			int iTemp103 = ((fTemp102 > fSlow3) ? fTemp102 : 0.0f) > 0.0f > 0;
			int iTemp104 = iTemp103;
			float fTemp105 = 0.144717798f * ((iTemp104) ? fSlow5 : fSlow4);
			int iTemp106 = std::fabs(fTemp105) < 1.1920929e-07f;
			float fThen66 = std::exp(0.0f - fConst6 / ((iTemp106) ? 1.0f : fTemp105));
			float fTemp107 = ((iTemp106) ? 0.0f : fThen66);
			float fElse67 = float(iTemp103);
			fRec81[0] = (1.0f - fTemp107) * ((iTemp104) ? fElse67 : 0.0f) + fTemp107 * fRec81[1];
			float fTemp108 = fConst142 + fRec88[1] + -1.0f;
			int iTemp109 = fTemp108 < 0.0f;
			float fTemp110 = fConst142 + fRec88[1];
			fRec88[0] = ((iTemp109) ? fTemp110 : fTemp108);
			float fThen69 = fConst142 + fRec88[1] + fConst143 * fTemp108;
			float fRec89 = ((iTemp109) ? fTemp110 : fThen69);
			output9[i0] = FAUSTFLOAT(fRec81[0] * (2.0f * fRec89 + -1.0f));
			fRec96[0] = fTemp0 - fConst153 * (fConst154 * fRec96[1] + fConst155 * fRec96[2]);
			fRec95[0] = fConst152 * fRec96[2] + fConst153 * (fConst149 * fRec96[0] - (fConst154 * fRec95[1] + fConst155 * fRec95[2]));
			fRec94[0] = fConst152 * fRec95[2] + fConst153 * (fConst149 * fRec95[0] - (fConst154 * fRec94[1] + fConst155 * fRec94[2]));
			fRec93[0] = fConst152 * fRec94[2] + fConst153 * (fConst149 * fRec94[0] - (fConst154 * fRec93[1] + fConst155 * fRec93[2]));
			float fTemp111 = fConst152 * fRec93[2];
			float fTemp112 = fConst151 * fRec93[0];
			fVec10[0] = fTemp112 + fTemp111;
			fRec92[0] = (fTemp111 + 0.995000005f * fRec92[1] + fTemp112) - fVec10[1];
			fRec91[IOTA0 & 32767] = fRec91[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec92[0]);
			float fTemp113 = std::sqrt(fSlow1 * (fRec91[IOTA0 & 32767] - fRec91[(IOTA0 - iSlow2) & 32767]));
			int iTemp114 = ((fTemp113 > fSlow3) ? fTemp113 : 0.0f) > 0.0f > 0;
			int iTemp115 = iTemp114;
			float fTemp116 = 0.144717798f * ((iTemp115) ? fSlow5 : fSlow4);
			int iTemp117 = std::fabs(fTemp116) < 1.1920929e-07f;
			float fThen73 = std::exp(0.0f - fConst6 / ((iTemp117) ? 1.0f : fTemp116));
			float fTemp118 = ((iTemp117) ? 0.0f : fThen73);
			float fElse74 = float(iTemp114);
			fRec90[0] = (1.0f - fTemp118) * ((iTemp115) ? fElse74 : 0.0f) + fTemp118 * fRec90[1];
			float fTemp119 = fConst156 + fRec97[1] + -1.0f;
			int iTemp120 = fTemp119 < 0.0f;
			float fTemp121 = fConst156 + fRec97[1];
			fRec97[0] = ((iTemp120) ? fTemp121 : fTemp119);
			float fThen76 = fConst156 + fRec97[1] + fConst157 * fTemp119;
			float fRec98 = ((iTemp120) ? fTemp121 : fThen76);
			output10[i0] = FAUSTFLOAT(fRec90[0] * (2.0f * fRec98 + -1.0f));
			fRec105[0] = fTemp0 - fConst167 * (fConst168 * fRec105[1] + fConst169 * fRec105[2]);
			fRec104[0] = fConst166 * fRec105[2] + fConst167 * (fConst163 * fRec105[0] - (fConst168 * fRec104[1] + fConst169 * fRec104[2]));
			fRec103[0] = fConst166 * fRec104[2] + fConst167 * (fConst163 * fRec104[0] - (fConst168 * fRec103[1] + fConst169 * fRec103[2]));
			fRec102[0] = fConst166 * fRec103[2] + fConst167 * (fConst163 * fRec103[0] - (fConst168 * fRec102[1] + fConst169 * fRec102[2]));
			float fTemp122 = fConst166 * fRec102[2];
			float fTemp123 = fConst165 * fRec102[0];
			fVec11[0] = fTemp123 + fTemp122;
			fRec101[0] = (fTemp122 + 0.995000005f * fRec101[1] + fTemp123) - fVec11[1];
			fRec100[IOTA0 & 32767] = fRec100[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec101[0]);
			float fTemp124 = std::sqrt(fSlow1 * (fRec100[IOTA0 & 32767] - fRec100[(IOTA0 - iSlow2) & 32767]));
			int iTemp125 = ((fTemp124 > fSlow3) ? fTemp124 : 0.0f) > 0.0f > 0;
			int iTemp126 = iTemp125;
			float fTemp127 = 0.144717798f * ((iTemp126) ? fSlow5 : fSlow4);
			int iTemp128 = std::fabs(fTemp127) < 1.1920929e-07f;
			float fThen80 = std::exp(0.0f - fConst6 / ((iTemp128) ? 1.0f : fTemp127));
			float fTemp129 = ((iTemp128) ? 0.0f : fThen80);
			float fElse81 = float(iTemp125);
			fRec99[0] = (1.0f - fTemp129) * ((iTemp126) ? fElse81 : 0.0f) + fTemp129 * fRec99[1];
			float fTemp130 = fConst170 + fRec106[1] + -1.0f;
			int iTemp131 = fTemp130 < 0.0f;
			float fTemp132 = fConst170 + fRec106[1];
			fRec106[0] = ((iTemp131) ? fTemp132 : fTemp130);
			float fThen83 = fConst170 + fRec106[1] + fConst171 * fTemp130;
			float fRec107 = ((iTemp131) ? fTemp132 : fThen83);
			output11[i0] = FAUSTFLOAT(fRec99[0] * (2.0f * fRec107 + -1.0f));
			fRec114[0] = fTemp0 - fConst181 * (fConst182 * fRec114[1] + fConst183 * fRec114[2]);
			fRec113[0] = fConst180 * fRec114[2] + fConst181 * (fConst177 * fRec114[0] - (fConst182 * fRec113[1] + fConst183 * fRec113[2]));
			fRec112[0] = fConst180 * fRec113[2] + fConst181 * (fConst177 * fRec113[0] - (fConst182 * fRec112[1] + fConst183 * fRec112[2]));
			fRec111[0] = fConst180 * fRec112[2] + fConst181 * (fConst177 * fRec112[0] - (fConst182 * fRec111[1] + fConst183 * fRec111[2]));
			float fTemp133 = fConst180 * fRec111[2];
			float fTemp134 = fConst179 * fRec111[0];
			fVec12[0] = fTemp134 + fTemp133;
			fRec110[0] = (fTemp133 + 0.995000005f * fRec110[1] + fTemp134) - fVec12[1];
			fRec109[IOTA0 & 32767] = fRec109[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec110[0]);
			float fTemp135 = std::sqrt(fSlow1 * (fRec109[IOTA0 & 32767] - fRec109[(IOTA0 - iSlow2) & 32767]));
			int iTemp136 = ((fTemp135 > fSlow3) ? fTemp135 : 0.0f) > 0.0f > 0;
			int iTemp137 = iTemp136;
			float fTemp138 = 0.144717798f * ((iTemp137) ? fSlow5 : fSlow4);
			int iTemp139 = std::fabs(fTemp138) < 1.1920929e-07f;
			float fThen87 = std::exp(0.0f - fConst6 / ((iTemp139) ? 1.0f : fTemp138));
			float fTemp140 = ((iTemp139) ? 0.0f : fThen87);
			float fElse88 = float(iTemp136);
			fRec108[0] = (1.0f - fTemp140) * ((iTemp137) ? fElse88 : 0.0f) + fTemp140 * fRec108[1];
			float fTemp141 = fConst184 + fRec115[1] + -1.0f;
			int iTemp142 = fTemp141 < 0.0f;
			float fTemp143 = fConst184 + fRec115[1];
			fRec115[0] = ((iTemp142) ? fTemp143 : fTemp141);
			float fThen90 = fConst184 + fRec115[1] + fConst185 * fTemp141;
			float fRec116 = ((iTemp142) ? fTemp143 : fThen90);
			output12[i0] = FAUSTFLOAT(fRec108[0] * (2.0f * fRec116 + -1.0f));
			fRec123[0] = fTemp0 - fConst195 * (fConst196 * fRec123[1] + fConst197 * fRec123[2]);
			fRec122[0] = fConst194 * fRec123[2] + fConst195 * (fConst191 * fRec123[0] - (fConst196 * fRec122[1] + fConst197 * fRec122[2]));
			fRec121[0] = fConst194 * fRec122[2] + fConst195 * (fConst191 * fRec122[0] - (fConst196 * fRec121[1] + fConst197 * fRec121[2]));
			fRec120[0] = fConst194 * fRec121[2] + fConst195 * (fConst191 * fRec121[0] - (fConst196 * fRec120[1] + fConst197 * fRec120[2]));
			float fTemp144 = fConst194 * fRec120[2];
			float fTemp145 = fConst193 * fRec120[0];
			fVec13[0] = fTemp145 + fTemp144;
			fRec119[0] = (fTemp144 + 0.995000005f * fRec119[1] + fTemp145) - fVec13[1];
			fRec118[IOTA0 & 32767] = fRec118[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec119[0]);
			float fTemp146 = std::sqrt(fSlow1 * (fRec118[IOTA0 & 32767] - fRec118[(IOTA0 - iSlow2) & 32767]));
			int iTemp147 = ((fTemp146 > fSlow3) ? fTemp146 : 0.0f) > 0.0f > 0;
			int iTemp148 = iTemp147;
			float fTemp149 = 0.144717798f * ((iTemp148) ? fSlow5 : fSlow4);
			int iTemp150 = std::fabs(fTemp149) < 1.1920929e-07f;
			float fThen94 = std::exp(0.0f - fConst6 / ((iTemp150) ? 1.0f : fTemp149));
			float fTemp151 = ((iTemp150) ? 0.0f : fThen94);
			float fElse95 = float(iTemp147);
			fRec117[0] = (1.0f - fTemp151) * ((iTemp148) ? fElse95 : 0.0f) + fTemp151 * fRec117[1];
			float fTemp152 = fConst198 + fRec124[1] + -1.0f;
			int iTemp153 = fTemp152 < 0.0f;
			float fTemp154 = fConst198 + fRec124[1];
			fRec124[0] = ((iTemp153) ? fTemp154 : fTemp152);
			float fThen97 = fConst198 + fRec124[1] + fConst199 * fTemp152;
			float fRec125 = ((iTemp153) ? fTemp154 : fThen97);
			output13[i0] = FAUSTFLOAT(fRec117[0] * (2.0f * fRec125 + -1.0f));
			fRec132[0] = fTemp0 - fConst209 * (fConst210 * fRec132[1] + fConst211 * fRec132[2]);
			fRec131[0] = fConst208 * fRec132[2] + fConst209 * (fConst205 * fRec132[0] - (fConst210 * fRec131[1] + fConst211 * fRec131[2]));
			fRec130[0] = fConst208 * fRec131[2] + fConst209 * (fConst205 * fRec131[0] - (fConst210 * fRec130[1] + fConst211 * fRec130[2]));
			fRec129[0] = fConst208 * fRec130[2] + fConst209 * (fConst205 * fRec130[0] - (fConst210 * fRec129[1] + fConst211 * fRec129[2]));
			float fTemp155 = fConst208 * fRec129[2];
			float fTemp156 = fConst207 * fRec129[0];
			fVec14[0] = fTemp156 + fTemp155;
			fRec128[0] = (fTemp155 + 0.995000005f * fRec128[1] + fTemp156) - fVec14[1];
			fRec127[IOTA0 & 32767] = fRec127[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec128[0]);
			float fTemp157 = std::sqrt(fSlow1 * (fRec127[IOTA0 & 32767] - fRec127[(IOTA0 - iSlow2) & 32767]));
			int iTemp158 = ((fTemp157 > fSlow3) ? fTemp157 : 0.0f) > 0.0f > 0;
			int iTemp159 = iTemp158;
			float fTemp160 = 0.144717798f * ((iTemp159) ? fSlow5 : fSlow4);
			int iTemp161 = std::fabs(fTemp160) < 1.1920929e-07f;
			float fThen101 = std::exp(0.0f - fConst6 / ((iTemp161) ? 1.0f : fTemp160));
			float fTemp162 = ((iTemp161) ? 0.0f : fThen101);
			float fElse102 = float(iTemp158);
			fRec126[0] = (1.0f - fTemp162) * ((iTemp159) ? fElse102 : 0.0f) + fTemp162 * fRec126[1];
			float fTemp163 = fConst212 + fRec133[1] + -1.0f;
			int iTemp164 = fTemp163 < 0.0f;
			float fTemp165 = fConst212 + fRec133[1];
			fRec133[0] = ((iTemp164) ? fTemp165 : fTemp163);
			float fThen104 = fConst212 + fRec133[1] + fConst213 * fTemp163;
			float fRec134 = ((iTemp164) ? fTemp165 : fThen104);
			output14[i0] = FAUSTFLOAT(fRec126[0] * (2.0f * fRec134 + -1.0f));
			fRec141[0] = fTemp0 - fConst223 * (fConst224 * fRec141[1] + fConst225 * fRec141[2]);
			fRec140[0] = fConst222 * fRec141[2] + fConst223 * (fConst219 * fRec141[0] - (fConst224 * fRec140[1] + fConst225 * fRec140[2]));
			fRec139[0] = fConst222 * fRec140[2] + fConst223 * (fConst219 * fRec140[0] - (fConst224 * fRec139[1] + fConst225 * fRec139[2]));
			fRec138[0] = fConst222 * fRec139[2] + fConst223 * (fConst219 * fRec139[0] - (fConst224 * fRec138[1] + fConst225 * fRec138[2]));
			float fTemp166 = fConst222 * fRec138[2];
			float fTemp167 = fConst221 * fRec138[0];
			fVec15[0] = fTemp167 + fTemp166;
			fRec137[0] = (fTemp166 + 0.995000005f * fRec137[1] + fTemp167) - fVec15[1];
			fRec136[IOTA0 & 32767] = fRec136[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec137[0]);
			float fTemp168 = std::sqrt(fSlow1 * (fRec136[IOTA0 & 32767] - fRec136[(IOTA0 - iSlow2) & 32767]));
			int iTemp169 = ((fTemp168 > fSlow3) ? fTemp168 : 0.0f) > 0.0f > 0;
			int iTemp170 = iTemp169;
			float fTemp171 = 0.144717798f * ((iTemp170) ? fSlow5 : fSlow4);
			int iTemp172 = std::fabs(fTemp171) < 1.1920929e-07f;
			float fThen108 = std::exp(0.0f - fConst6 / ((iTemp172) ? 1.0f : fTemp171));
			float fTemp173 = ((iTemp172) ? 0.0f : fThen108);
			float fElse109 = float(iTemp169);
			fRec135[0] = (1.0f - fTemp173) * ((iTemp170) ? fElse109 : 0.0f) + fTemp173 * fRec135[1];
			float fTemp174 = fConst226 + fRec142[1] + -1.0f;
			int iTemp175 = fTemp174 < 0.0f;
			float fTemp176 = fConst226 + fRec142[1];
			fRec142[0] = ((iTemp175) ? fTemp176 : fTemp174);
			float fThen111 = fConst226 + fRec142[1] + fConst227 * fTemp174;
			float fRec143 = ((iTemp175) ? fTemp176 : fThen111);
			output15[i0] = FAUSTFLOAT(fRec135[0] * (2.0f * fRec143 + -1.0f));
			fRec150[0] = fTemp0 - fConst237 * (fConst238 * fRec150[1] + fConst239 * fRec150[2]);
			fRec149[0] = fConst236 * fRec150[2] + fConst237 * (fConst233 * fRec150[0] - (fConst238 * fRec149[1] + fConst239 * fRec149[2]));
			fRec148[0] = fConst236 * fRec149[2] + fConst237 * (fConst233 * fRec149[0] - (fConst238 * fRec148[1] + fConst239 * fRec148[2]));
			fRec147[0] = fConst236 * fRec148[2] + fConst237 * (fConst233 * fRec148[0] - (fConst238 * fRec147[1] + fConst239 * fRec147[2]));
			float fTemp177 = fConst236 * fRec147[2];
			float fTemp178 = fConst235 * fRec147[0];
			fVec16[0] = fTemp178 + fTemp177;
			fRec146[0] = (fTemp177 + 0.995000005f * fRec146[1] + fTemp178) - fVec16[1];
			fRec145[IOTA0 & 32767] = fRec145[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec146[0]);
			float fTemp179 = std::sqrt(fSlow1 * (fRec145[IOTA0 & 32767] - fRec145[(IOTA0 - iSlow2) & 32767]));
			int iTemp180 = ((fTemp179 > fSlow3) ? fTemp179 : 0.0f) > 0.0f > 0;
			int iTemp181 = iTemp180;
			float fTemp182 = 0.144717798f * ((iTemp181) ? fSlow5 : fSlow4);
			int iTemp183 = std::fabs(fTemp182) < 1.1920929e-07f;
			float fThen115 = std::exp(0.0f - fConst6 / ((iTemp183) ? 1.0f : fTemp182));
			float fTemp184 = ((iTemp183) ? 0.0f : fThen115);
			float fElse116 = float(iTemp180);
			fRec144[0] = (1.0f - fTemp184) * ((iTemp181) ? fElse116 : 0.0f) + fTemp184 * fRec144[1];
			float fTemp185 = fConst240 + fRec151[1] + -1.0f;
			int iTemp186 = fTemp185 < 0.0f;
			float fTemp187 = fConst240 + fRec151[1];
			fRec151[0] = ((iTemp186) ? fTemp187 : fTemp185);
			float fThen118 = fConst240 + fRec151[1] + fConst241 * fTemp185;
			float fRec152 = ((iTemp186) ? fTemp187 : fThen118);
			output16[i0] = FAUSTFLOAT(fRec144[0] * (2.0f * fRec152 + -1.0f));
			fRec159[0] = fTemp0 - fConst251 * (fConst252 * fRec159[1] + fConst253 * fRec159[2]);
			fRec158[0] = fConst250 * fRec159[2] + fConst251 * (fConst247 * fRec159[0] - (fConst252 * fRec158[1] + fConst253 * fRec158[2]));
			fRec157[0] = fConst250 * fRec158[2] + fConst251 * (fConst247 * fRec158[0] - (fConst252 * fRec157[1] + fConst253 * fRec157[2]));
			fRec156[0] = fConst250 * fRec157[2] + fConst251 * (fConst247 * fRec157[0] - (fConst252 * fRec156[1] + fConst253 * fRec156[2]));
			float fTemp188 = fConst250 * fRec156[2];
			float fTemp189 = fConst249 * fRec156[0];
			fVec17[0] = fTemp189 + fTemp188;
			fRec155[0] = (fTemp188 + 0.995000005f * fRec155[1] + fTemp189) - fVec17[1];
			fRec154[IOTA0 & 32767] = fRec154[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec155[0]);
			float fTemp190 = std::sqrt(fSlow1 * (fRec154[IOTA0 & 32767] - fRec154[(IOTA0 - iSlow2) & 32767]));
			int iTemp191 = ((fTemp190 > fSlow3) ? fTemp190 : 0.0f) > 0.0f > 0;
			int iTemp192 = iTemp191;
			float fTemp193 = 0.144717798f * ((iTemp192) ? fSlow5 : fSlow4);
			int iTemp194 = std::fabs(fTemp193) < 1.1920929e-07f;
			float fThen122 = std::exp(0.0f - fConst6 / ((iTemp194) ? 1.0f : fTemp193));
			float fTemp195 = ((iTemp194) ? 0.0f : fThen122);
			float fElse123 = float(iTemp191);
			fRec153[0] = (1.0f - fTemp195) * ((iTemp192) ? fElse123 : 0.0f) + fTemp195 * fRec153[1];
			float fTemp196 = fConst254 + fRec160[1] + -1.0f;
			int iTemp197 = fTemp196 < 0.0f;
			float fTemp198 = fConst254 + fRec160[1];
			fRec160[0] = ((iTemp197) ? fTemp198 : fTemp196);
			float fThen125 = fConst254 + fRec160[1] + fConst255 * fTemp196;
			float fRec161 = ((iTemp197) ? fTemp198 : fThen125);
			output17[i0] = FAUSTFLOAT(fRec153[0] * (2.0f * fRec161 + -1.0f));
			fRec168[0] = fTemp0 - fConst265 * (fConst266 * fRec168[1] + fConst267 * fRec168[2]);
			fRec167[0] = fConst264 * fRec168[2] + fConst265 * (fConst261 * fRec168[0] - (fConst266 * fRec167[1] + fConst267 * fRec167[2]));
			fRec166[0] = fConst264 * fRec167[2] + fConst265 * (fConst261 * fRec167[0] - (fConst266 * fRec166[1] + fConst267 * fRec166[2]));
			fRec165[0] = fConst264 * fRec166[2] + fConst265 * (fConst261 * fRec166[0] - (fConst266 * fRec165[1] + fConst267 * fRec165[2]));
			float fTemp199 = fConst264 * fRec165[2];
			float fTemp200 = fConst263 * fRec165[0];
			fVec18[0] = fTemp200 + fTemp199;
			fRec164[0] = (fTemp199 + 0.995000005f * fRec164[1] + fTemp200) - fVec18[1];
			fRec163[IOTA0 & 32767] = fRec163[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec164[0]);
			float fTemp201 = std::sqrt(fSlow1 * (fRec163[IOTA0 & 32767] - fRec163[(IOTA0 - iSlow2) & 32767]));
			int iTemp202 = ((fTemp201 > fSlow3) ? fTemp201 : 0.0f) > 0.0f > 0;
			int iTemp203 = iTemp202;
			float fTemp204 = 0.144717798f * ((iTemp203) ? fSlow5 : fSlow4);
			int iTemp205 = std::fabs(fTemp204) < 1.1920929e-07f;
			float fThen129 = std::exp(0.0f - fConst6 / ((iTemp205) ? 1.0f : fTemp204));
			float fTemp206 = ((iTemp205) ? 0.0f : fThen129);
			float fElse130 = float(iTemp202);
			fRec162[0] = (1.0f - fTemp206) * ((iTemp203) ? fElse130 : 0.0f) + fTemp206 * fRec162[1];
			float fTemp207 = fConst268 + fRec169[1] + -1.0f;
			int iTemp208 = fTemp207 < 0.0f;
			float fTemp209 = fConst268 + fRec169[1];
			fRec169[0] = ((iTemp208) ? fTemp209 : fTemp207);
			float fThen132 = fConst268 + fRec169[1] + fConst269 * fTemp207;
			float fRec170 = ((iTemp208) ? fTemp209 : fThen132);
			output18[i0] = FAUSTFLOAT(fRec162[0] * (2.0f * fRec170 + -1.0f));
			fRec177[0] = fTemp0 - fConst279 * (fConst280 * fRec177[1] + fConst281 * fRec177[2]);
			fRec176[0] = fConst278 * fRec177[2] + fConst279 * (fConst275 * fRec177[0] - (fConst280 * fRec176[1] + fConst281 * fRec176[2]));
			fRec175[0] = fConst278 * fRec176[2] + fConst279 * (fConst275 * fRec176[0] - (fConst280 * fRec175[1] + fConst281 * fRec175[2]));
			fRec174[0] = fConst278 * fRec175[2] + fConst279 * (fConst275 * fRec175[0] - (fConst280 * fRec174[1] + fConst281 * fRec174[2]));
			float fTemp210 = fConst278 * fRec174[2];
			float fTemp211 = fConst277 * fRec174[0];
			fVec19[0] = fTemp211 + fTemp210;
			fRec173[0] = (fTemp210 + 0.995000005f * fRec173[1] + fTemp211) - fVec19[1];
			fRec172[IOTA0 & 32767] = fRec172[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec173[0]);
			float fTemp212 = std::sqrt(fSlow1 * (fRec172[IOTA0 & 32767] - fRec172[(IOTA0 - iSlow2) & 32767]));
			int iTemp213 = ((fTemp212 > fSlow3) ? fTemp212 : 0.0f) > 0.0f > 0;
			int iTemp214 = iTemp213;
			float fTemp215 = 0.144717798f * ((iTemp214) ? fSlow5 : fSlow4);
			int iTemp216 = std::fabs(fTemp215) < 1.1920929e-07f;
			float fThen136 = std::exp(0.0f - fConst6 / ((iTemp216) ? 1.0f : fTemp215));
			float fTemp217 = ((iTemp216) ? 0.0f : fThen136);
			float fElse137 = float(iTemp213);
			fRec171[0] = (1.0f - fTemp217) * ((iTemp214) ? fElse137 : 0.0f) + fTemp217 * fRec171[1];
			float fTemp218 = fConst282 + fRec178[1] + -1.0f;
			int iTemp219 = fTemp218 < 0.0f;
			float fTemp220 = fConst282 + fRec178[1];
			fRec178[0] = ((iTemp219) ? fTemp220 : fTemp218);
			float fThen139 = fConst282 + fRec178[1] + fConst283 * fTemp218;
			float fRec179 = ((iTemp219) ? fTemp220 : fThen139);
			output19[i0] = FAUSTFLOAT(fRec171[0] * (2.0f * fRec179 + -1.0f));
			fRec186[0] = fTemp0 - fConst293 * (fConst294 * fRec186[1] + fConst295 * fRec186[2]);
			fRec185[0] = fConst292 * fRec186[2] + fConst293 * (fConst289 * fRec186[0] - (fConst294 * fRec185[1] + fConst295 * fRec185[2]));
			fRec184[0] = fConst292 * fRec185[2] + fConst293 * (fConst289 * fRec185[0] - (fConst294 * fRec184[1] + fConst295 * fRec184[2]));
			fRec183[0] = fConst292 * fRec184[2] + fConst293 * (fConst289 * fRec184[0] - (fConst294 * fRec183[1] + fConst295 * fRec183[2]));
			float fTemp221 = fConst292 * fRec183[2];
			float fTemp222 = fConst291 * fRec183[0];
			fVec20[0] = fTemp222 + fTemp221;
			fRec182[0] = (fTemp221 + 0.995000005f * fRec182[1] + fTemp222) - fVec20[1];
			fRec181[IOTA0 & 32767] = fRec181[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec182[0]);
			float fTemp223 = std::sqrt(fSlow1 * (fRec181[IOTA0 & 32767] - fRec181[(IOTA0 - iSlow2) & 32767]));
			int iTemp224 = ((fTemp223 > fSlow3) ? fTemp223 : 0.0f) > 0.0f > 0;
			int iTemp225 = iTemp224;
			float fTemp226 = 0.144717798f * ((iTemp225) ? fSlow5 : fSlow4);
			int iTemp227 = std::fabs(fTemp226) < 1.1920929e-07f;
			float fThen143 = std::exp(0.0f - fConst6 / ((iTemp227) ? 1.0f : fTemp226));
			float fTemp228 = ((iTemp227) ? 0.0f : fThen143);
			float fElse144 = float(iTemp224);
			fRec180[0] = (1.0f - fTemp228) * ((iTemp225) ? fElse144 : 0.0f) + fTemp228 * fRec180[1];
			float fTemp229 = fConst296 + fRec187[1] + -1.0f;
			int iTemp230 = fTemp229 < 0.0f;
			float fTemp231 = fConst296 + fRec187[1];
			fRec187[0] = ((iTemp230) ? fTemp231 : fTemp229);
			float fThen146 = fConst296 + fRec187[1] + fConst297 * fTemp229;
			float fRec188 = ((iTemp230) ? fTemp231 : fThen146);
			output20[i0] = FAUSTFLOAT(fRec180[0] * (2.0f * fRec188 + -1.0f));
			fRec195[0] = fTemp0 - fConst307 * (fConst308 * fRec195[1] + fConst309 * fRec195[2]);
			fRec194[0] = fConst306 * fRec195[2] + fConst307 * (fConst303 * fRec195[0] - (fConst308 * fRec194[1] + fConst309 * fRec194[2]));
			fRec193[0] = fConst306 * fRec194[2] + fConst307 * (fConst303 * fRec194[0] - (fConst308 * fRec193[1] + fConst309 * fRec193[2]));
			fRec192[0] = fConst306 * fRec193[2] + fConst307 * (fConst303 * fRec193[0] - (fConst308 * fRec192[1] + fConst309 * fRec192[2]));
			float fTemp232 = fConst306 * fRec192[2];
			float fTemp233 = fConst305 * fRec192[0];
			fVec21[0] = fTemp233 + fTemp232;
			fRec191[0] = (fTemp232 + 0.995000005f * fRec191[1] + fTemp233) - fVec21[1];
			fRec190[IOTA0 & 32767] = fRec190[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec191[0]);
			float fTemp234 = std::sqrt(fSlow1 * (fRec190[IOTA0 & 32767] - fRec190[(IOTA0 - iSlow2) & 32767]));
			int iTemp235 = ((fTemp234 > fSlow3) ? fTemp234 : 0.0f) > 0.0f > 0;
			int iTemp236 = iTemp235;
			float fTemp237 = 0.144717798f * ((iTemp236) ? fSlow5 : fSlow4);
			int iTemp238 = std::fabs(fTemp237) < 1.1920929e-07f;
			float fThen150 = std::exp(0.0f - fConst6 / ((iTemp238) ? 1.0f : fTemp237));
			float fTemp239 = ((iTemp238) ? 0.0f : fThen150);
			float fElse151 = float(iTemp235);
			fRec189[0] = (1.0f - fTemp239) * ((iTemp236) ? fElse151 : 0.0f) + fTemp239 * fRec189[1];
			float fTemp240 = fConst310 + fRec196[1] + -1.0f;
			int iTemp241 = fTemp240 < 0.0f;
			float fTemp242 = fConst310 + fRec196[1];
			fRec196[0] = ((iTemp241) ? fTemp242 : fTemp240);
			float fThen153 = fConst310 + fRec196[1] + fConst311 * fTemp240;
			float fRec197 = ((iTemp241) ? fTemp242 : fThen153);
			output21[i0] = FAUSTFLOAT(fRec189[0] * (2.0f * fRec197 + -1.0f));
			fRec204[0] = fTemp0 - fConst321 * (fConst322 * fRec204[1] + fConst323 * fRec204[2]);
			fRec203[0] = fConst320 * fRec204[2] + fConst321 * (fConst317 * fRec204[0] - (fConst322 * fRec203[1] + fConst323 * fRec203[2]));
			fRec202[0] = fConst320 * fRec203[2] + fConst321 * (fConst317 * fRec203[0] - (fConst322 * fRec202[1] + fConst323 * fRec202[2]));
			fRec201[0] = fConst320 * fRec202[2] + fConst321 * (fConst317 * fRec202[0] - (fConst322 * fRec201[1] + fConst323 * fRec201[2]));
			float fTemp243 = fConst320 * fRec201[2];
			float fTemp244 = fConst319 * fRec201[0];
			fVec22[0] = fTemp244 + fTemp243;
			fRec200[0] = (fTemp243 + 0.995000005f * fRec200[1] + fTemp244) - fVec22[1];
			fRec199[IOTA0 & 32767] = fRec199[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec200[0]);
			float fTemp245 = std::sqrt(fSlow1 * (fRec199[IOTA0 & 32767] - fRec199[(IOTA0 - iSlow2) & 32767]));
			int iTemp246 = ((fTemp245 > fSlow3) ? fTemp245 : 0.0f) > 0.0f > 0;
			int iTemp247 = iTemp246;
			float fTemp248 = 0.144717798f * ((iTemp247) ? fSlow5 : fSlow4);
			int iTemp249 = std::fabs(fTemp248) < 1.1920929e-07f;
			float fThen157 = std::exp(0.0f - fConst6 / ((iTemp249) ? 1.0f : fTemp248));
			float fTemp250 = ((iTemp249) ? 0.0f : fThen157);
			float fElse158 = float(iTemp246);
			fRec198[0] = (1.0f - fTemp250) * ((iTemp247) ? fElse158 : 0.0f) + fTemp250 * fRec198[1];
			float fTemp251 = fConst324 + fRec205[1] + -1.0f;
			int iTemp252 = fTemp251 < 0.0f;
			float fTemp253 = fConst324 + fRec205[1];
			fRec205[0] = ((iTemp252) ? fTemp253 : fTemp251);
			float fThen160 = fConst324 + fRec205[1] + fConst325 * fTemp251;
			float fRec206 = ((iTemp252) ? fTemp253 : fThen160);
			output22[i0] = FAUSTFLOAT(fRec198[0] * (2.0f * fRec206 + -1.0f));
			fRec213[0] = fTemp0 - fConst335 * (fConst336 * fRec213[1] + fConst337 * fRec213[2]);
			fRec212[0] = fConst334 * fRec213[2] + fConst335 * (fConst331 * fRec213[0] - (fConst336 * fRec212[1] + fConst337 * fRec212[2]));
			fRec211[0] = fConst334 * fRec212[2] + fConst335 * (fConst331 * fRec212[0] - (fConst336 * fRec211[1] + fConst337 * fRec211[2]));
			fRec210[0] = fConst334 * fRec211[2] + fConst335 * (fConst331 * fRec211[0] - (fConst336 * fRec210[1] + fConst337 * fRec210[2]));
			float fTemp254 = fConst334 * fRec210[2];
			float fTemp255 = fConst333 * fRec210[0];
			fVec23[0] = fTemp255 + fTemp254;
			fRec209[0] = (fTemp254 + 0.995000005f * fRec209[1] + fTemp255) - fVec23[1];
			fRec208[IOTA0 & 32767] = fRec208[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec209[0]);
			float fTemp256 = std::sqrt(fSlow1 * (fRec208[IOTA0 & 32767] - fRec208[(IOTA0 - iSlow2) & 32767]));
			int iTemp257 = ((fTemp256 > fSlow3) ? fTemp256 : 0.0f) > 0.0f > 0;
			int iTemp258 = iTemp257;
			float fTemp259 = 0.144717798f * ((iTemp258) ? fSlow5 : fSlow4);
			int iTemp260 = std::fabs(fTemp259) < 1.1920929e-07f;
			float fThen164 = std::exp(0.0f - fConst6 / ((iTemp260) ? 1.0f : fTemp259));
			float fTemp261 = ((iTemp260) ? 0.0f : fThen164);
			float fElse165 = float(iTemp257);
			fRec207[0] = (1.0f - fTemp261) * ((iTemp258) ? fElse165 : 0.0f) + fTemp261 * fRec207[1];
			float fTemp262 = fConst338 + fRec214[1] + -1.0f;
			int iTemp263 = fTemp262 < 0.0f;
			float fTemp264 = fConst338 + fRec214[1];
			fRec214[0] = ((iTemp263) ? fTemp264 : fTemp262);
			float fThen167 = fConst338 + fRec214[1] + fConst339 * fTemp262;
			float fRec215 = ((iTemp263) ? fTemp264 : fThen167);
			output23[i0] = FAUSTFLOAT(fRec207[0] * (2.0f * fRec215 + -1.0f));
			fRec222[0] = fTemp0 - fConst349 * (fConst350 * fRec222[1] + fConst351 * fRec222[2]);
			fRec221[0] = fConst348 * fRec222[2] + fConst349 * (fConst345 * fRec222[0] - (fConst350 * fRec221[1] + fConst351 * fRec221[2]));
			fRec220[0] = fConst348 * fRec221[2] + fConst349 * (fConst345 * fRec221[0] - (fConst350 * fRec220[1] + fConst351 * fRec220[2]));
			fRec219[0] = fConst348 * fRec220[2] + fConst349 * (fConst345 * fRec220[0] - (fConst350 * fRec219[1] + fConst351 * fRec219[2]));
			float fTemp265 = fConst348 * fRec219[2];
			float fTemp266 = fConst347 * fRec219[0];
			fVec24[0] = fTemp266 + fTemp265;
			fRec218[0] = (fTemp265 + 0.995000005f * fRec218[1] + fTemp266) - fVec24[1];
			fRec217[IOTA0 & 32767] = fRec217[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec218[0]);
			float fTemp267 = std::sqrt(fSlow1 * (fRec217[IOTA0 & 32767] - fRec217[(IOTA0 - iSlow2) & 32767]));
			int iTemp268 = ((fTemp267 > fSlow3) ? fTemp267 : 0.0f) > 0.0f > 0;
			int iTemp269 = iTemp268;
			float fTemp270 = 0.144717798f * ((iTemp269) ? fSlow5 : fSlow4);
			int iTemp271 = std::fabs(fTemp270) < 1.1920929e-07f;
			float fThen171 = std::exp(0.0f - fConst6 / ((iTemp271) ? 1.0f : fTemp270));
			float fTemp272 = ((iTemp271) ? 0.0f : fThen171);
			float fElse172 = float(iTemp268);
			fRec216[0] = (1.0f - fTemp272) * ((iTemp269) ? fElse172 : 0.0f) + fTemp272 * fRec216[1];
			float fTemp273 = fConst352 + fRec223[1] + -1.0f;
			int iTemp274 = fTemp273 < 0.0f;
			float fTemp275 = fConst352 + fRec223[1];
			fRec223[0] = ((iTemp274) ? fTemp275 : fTemp273);
			float fThen174 = fConst352 + fRec223[1] + fConst353 * fTemp273;
			float fRec224 = ((iTemp274) ? fTemp275 : fThen174);
			output24[i0] = FAUSTFLOAT(fRec216[0] * (2.0f * fRec224 + -1.0f));
			fRec231[0] = fTemp0 - fConst363 * (fConst364 * fRec231[1] + fConst365 * fRec231[2]);
			fRec230[0] = fConst362 * fRec231[2] + fConst363 * (fConst359 * fRec231[0] - (fConst364 * fRec230[1] + fConst365 * fRec230[2]));
			fRec229[0] = fConst362 * fRec230[2] + fConst363 * (fConst359 * fRec230[0] - (fConst364 * fRec229[1] + fConst365 * fRec229[2]));
			fRec228[0] = fConst362 * fRec229[2] + fConst363 * (fConst359 * fRec229[0] - (fConst364 * fRec228[1] + fConst365 * fRec228[2]));
			float fTemp276 = fConst362 * fRec228[2];
			float fTemp277 = fConst361 * fRec228[0];
			fVec25[0] = fTemp277 + fTemp276;
			fRec227[0] = (fTemp276 + 0.995000005f * fRec227[1] + fTemp277) - fVec25[1];
			fRec226[IOTA0 & 32767] = fRec226[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec227[0]);
			float fTemp278 = std::sqrt(fSlow1 * (fRec226[IOTA0 & 32767] - fRec226[(IOTA0 - iSlow2) & 32767]));
			int iTemp279 = ((fTemp278 > fSlow3) ? fTemp278 : 0.0f) > 0.0f > 0;
			int iTemp280 = iTemp279;
			float fTemp281 = 0.144717798f * ((iTemp280) ? fSlow5 : fSlow4);
			int iTemp282 = std::fabs(fTemp281) < 1.1920929e-07f;
			float fThen178 = std::exp(0.0f - fConst6 / ((iTemp282) ? 1.0f : fTemp281));
			float fTemp283 = ((iTemp282) ? 0.0f : fThen178);
			float fElse179 = float(iTemp279);
			fRec225[0] = (1.0f - fTemp283) * ((iTemp280) ? fElse179 : 0.0f) + fTemp283 * fRec225[1];
			float fTemp284 = fConst366 + fRec232[1] + -1.0f;
			int iTemp285 = fTemp284 < 0.0f;
			float fTemp286 = fConst366 + fRec232[1];
			fRec232[0] = ((iTemp285) ? fTemp286 : fTemp284);
			float fThen181 = fConst366 + fRec232[1] + fConst367 * fTemp284;
			float fRec233 = ((iTemp285) ? fTemp286 : fThen181);
			output25[i0] = FAUSTFLOAT(fRec225[0] * (2.0f * fRec233 + -1.0f));
			fRec240[0] = fTemp0 - fConst377 * (fConst378 * fRec240[1] + fConst379 * fRec240[2]);
			fRec239[0] = fConst376 * fRec240[2] + fConst377 * (fConst373 * fRec240[0] - (fConst378 * fRec239[1] + fConst379 * fRec239[2]));
			fRec238[0] = fConst376 * fRec239[2] + fConst377 * (fConst373 * fRec239[0] - (fConst378 * fRec238[1] + fConst379 * fRec238[2]));
			fRec237[0] = fConst376 * fRec238[2] + fConst377 * (fConst373 * fRec238[0] - (fConst378 * fRec237[1] + fConst379 * fRec237[2]));
			float fTemp287 = fConst376 * fRec237[2];
			float fTemp288 = fConst375 * fRec237[0];
			fVec26[0] = fTemp288 + fTemp287;
			fRec236[0] = (fTemp287 + 0.995000005f * fRec236[1] + fTemp288) - fVec26[1];
			fRec235[IOTA0 & 32767] = fRec235[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec236[0]);
			float fTemp289 = std::sqrt(fSlow1 * (fRec235[IOTA0 & 32767] - fRec235[(IOTA0 - iSlow2) & 32767]));
			int iTemp290 = ((fTemp289 > fSlow3) ? fTemp289 : 0.0f) > 0.0f > 0;
			int iTemp291 = iTemp290;
			float fTemp292 = 0.144717798f * ((iTemp291) ? fSlow5 : fSlow4);
			int iTemp293 = std::fabs(fTemp292) < 1.1920929e-07f;
			float fThen185 = std::exp(0.0f - fConst6 / ((iTemp293) ? 1.0f : fTemp292));
			float fTemp294 = ((iTemp293) ? 0.0f : fThen185);
			float fElse186 = float(iTemp290);
			fRec234[0] = (1.0f - fTemp294) * ((iTemp291) ? fElse186 : 0.0f) + fTemp294 * fRec234[1];
			float fTemp295 = fConst380 + fRec241[1] + -1.0f;
			int iTemp296 = fTemp295 < 0.0f;
			float fTemp297 = fConst380 + fRec241[1];
			fRec241[0] = ((iTemp296) ? fTemp297 : fTemp295);
			float fThen188 = fConst380 + fRec241[1] + fConst381 * fTemp295;
			float fRec242 = ((iTemp296) ? fTemp297 : fThen188);
			output26[i0] = FAUSTFLOAT(fRec234[0] * (2.0f * fRec242 + -1.0f));
			fRec249[0] = fTemp0 - fConst391 * (fConst392 * fRec249[1] + fConst393 * fRec249[2]);
			fRec248[0] = fConst390 * fRec249[2] + fConst391 * (fConst387 * fRec249[0] - (fConst392 * fRec248[1] + fConst393 * fRec248[2]));
			fRec247[0] = fConst390 * fRec248[2] + fConst391 * (fConst387 * fRec248[0] - (fConst392 * fRec247[1] + fConst393 * fRec247[2]));
			fRec246[0] = fConst390 * fRec247[2] + fConst391 * (fConst387 * fRec247[0] - (fConst392 * fRec246[1] + fConst393 * fRec246[2]));
			float fTemp298 = fConst390 * fRec246[2];
			float fTemp299 = fConst389 * fRec246[0];
			fVec27[0] = fTemp299 + fTemp298;
			fRec245[0] = (fTemp298 + 0.995000005f * fRec245[1] + fTemp299) - fVec27[1];
			fRec244[IOTA0 & 32767] = fRec244[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec245[0]);
			float fTemp300 = std::sqrt(fSlow1 * (fRec244[IOTA0 & 32767] - fRec244[(IOTA0 - iSlow2) & 32767]));
			int iTemp301 = ((fTemp300 > fSlow3) ? fTemp300 : 0.0f) > 0.0f > 0;
			int iTemp302 = iTemp301;
			float fTemp303 = 0.144717798f * ((iTemp302) ? fSlow5 : fSlow4);
			int iTemp304 = std::fabs(fTemp303) < 1.1920929e-07f;
			float fThen192 = std::exp(0.0f - fConst6 / ((iTemp304) ? 1.0f : fTemp303));
			float fTemp305 = ((iTemp304) ? 0.0f : fThen192);
			float fElse193 = float(iTemp301);
			fRec243[0] = (1.0f - fTemp305) * ((iTemp302) ? fElse193 : 0.0f) + fTemp305 * fRec243[1];
			float fTemp306 = fConst394 + fRec250[1] + -1.0f;
			int iTemp307 = fTemp306 < 0.0f;
			float fTemp308 = fConst394 + fRec250[1];
			fRec250[0] = ((iTemp307) ? fTemp308 : fTemp306);
			float fThen195 = fConst394 + fRec250[1] + fConst395 * fTemp306;
			float fRec251 = ((iTemp307) ? fTemp308 : fThen195);
			output27[i0] = FAUSTFLOAT(fRec243[0] * (2.0f * fRec251 + -1.0f));
			fRec258[0] = fTemp0 - fConst405 * (fConst406 * fRec258[1] + fConst407 * fRec258[2]);
			fRec257[0] = fConst404 * fRec258[2] + fConst405 * (fConst401 * fRec258[0] - (fConst406 * fRec257[1] + fConst407 * fRec257[2]));
			fRec256[0] = fConst404 * fRec257[2] + fConst405 * (fConst401 * fRec257[0] - (fConst406 * fRec256[1] + fConst407 * fRec256[2]));
			fRec255[0] = fConst404 * fRec256[2] + fConst405 * (fConst401 * fRec256[0] - (fConst406 * fRec255[1] + fConst407 * fRec255[2]));
			float fTemp309 = fConst404 * fRec255[2];
			float fTemp310 = fConst403 * fRec255[0];
			fVec28[0] = fTemp310 + fTemp309;
			fRec254[0] = (fTemp309 + 0.995000005f * fRec254[1] + fTemp310) - fVec28[1];
			fRec253[IOTA0 & 32767] = fRec253[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec254[0]);
			float fTemp311 = std::sqrt(fSlow1 * (fRec253[IOTA0 & 32767] - fRec253[(IOTA0 - iSlow2) & 32767]));
			int iTemp312 = ((fTemp311 > fSlow3) ? fTemp311 : 0.0f) > 0.0f > 0;
			int iTemp313 = iTemp312;
			float fTemp314 = 0.144717798f * ((iTemp313) ? fSlow5 : fSlow4);
			int iTemp315 = std::fabs(fTemp314) < 1.1920929e-07f;
			float fThen199 = std::exp(0.0f - fConst6 / ((iTemp315) ? 1.0f : fTemp314));
			float fTemp316 = ((iTemp315) ? 0.0f : fThen199);
			float fElse200 = float(iTemp312);
			fRec252[0] = (1.0f - fTemp316) * ((iTemp313) ? fElse200 : 0.0f) + fTemp316 * fRec252[1];
			float fTemp317 = fConst408 + fRec259[1] + -1.0f;
			int iTemp318 = fTemp317 < 0.0f;
			float fTemp319 = fConst408 + fRec259[1];
			fRec259[0] = ((iTemp318) ? fTemp319 : fTemp317);
			float fThen202 = fConst408 + fRec259[1] + fConst409 * fTemp317;
			float fRec260 = ((iTemp318) ? fTemp319 : fThen202);
			output28[i0] = FAUSTFLOAT(fRec252[0] * (2.0f * fRec260 + -1.0f));
			fRec267[0] = fTemp0 - fConst419 * (fConst420 * fRec267[1] + fConst421 * fRec267[2]);
			fRec266[0] = fConst418 * fRec267[2] + fConst419 * (fConst415 * fRec267[0] - (fConst420 * fRec266[1] + fConst421 * fRec266[2]));
			fRec265[0] = fConst418 * fRec266[2] + fConst419 * (fConst415 * fRec266[0] - (fConst420 * fRec265[1] + fConst421 * fRec265[2]));
			fRec264[0] = fConst418 * fRec265[2] + fConst419 * (fConst415 * fRec265[0] - (fConst420 * fRec264[1] + fConst421 * fRec264[2]));
			float fTemp320 = fConst418 * fRec264[2];
			float fTemp321 = fConst417 * fRec264[0];
			fVec29[0] = fTemp321 + fTemp320;
			fRec263[0] = (fTemp320 + 0.995000005f * fRec263[1] + fTemp321) - fVec29[1];
			fRec262[IOTA0 & 32767] = fRec262[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec263[0]);
			float fTemp322 = std::sqrt(fSlow1 * (fRec262[IOTA0 & 32767] - fRec262[(IOTA0 - iSlow2) & 32767]));
			int iTemp323 = ((fTemp322 > fSlow3) ? fTemp322 : 0.0f) > 0.0f > 0;
			int iTemp324 = iTemp323;
			float fTemp325 = 0.144717798f * ((iTemp324) ? fSlow5 : fSlow4);
			int iTemp326 = std::fabs(fTemp325) < 1.1920929e-07f;
			float fThen206 = std::exp(0.0f - fConst6 / ((iTemp326) ? 1.0f : fTemp325));
			float fTemp327 = ((iTemp326) ? 0.0f : fThen206);
			float fElse207 = float(iTemp323);
			fRec261[0] = (1.0f - fTemp327) * ((iTemp324) ? fElse207 : 0.0f) + fTemp327 * fRec261[1];
			float fTemp328 = fConst422 + fRec268[1] + -1.0f;
			int iTemp329 = fTemp328 < 0.0f;
			float fTemp330 = fConst422 + fRec268[1];
			fRec268[0] = ((iTemp329) ? fTemp330 : fTemp328);
			float fThen209 = fConst422 + fRec268[1] + fConst423 * fTemp328;
			float fRec269 = ((iTemp329) ? fTemp330 : fThen209);
			output29[i0] = FAUSTFLOAT(fRec261[0] * (2.0f * fRec269 + -1.0f));
			fRec276[0] = fTemp0 - fConst433 * (fConst434 * fRec276[1] + fConst435 * fRec276[2]);
			fRec275[0] = fConst432 * fRec276[2] + fConst433 * (fConst429 * fRec276[0] - (fConst434 * fRec275[1] + fConst435 * fRec275[2]));
			fRec274[0] = fConst432 * fRec275[2] + fConst433 * (fConst429 * fRec275[0] - (fConst434 * fRec274[1] + fConst435 * fRec274[2]));
			fRec273[0] = fConst432 * fRec274[2] + fConst433 * (fConst429 * fRec274[0] - (fConst434 * fRec273[1] + fConst435 * fRec273[2]));
			float fTemp331 = fConst432 * fRec273[2];
			float fTemp332 = fConst431 * fRec273[0];
			fVec30[0] = fTemp332 + fTemp331;
			fRec272[0] = (fTemp331 + 0.995000005f * fRec272[1] + fTemp332) - fVec30[1];
			fRec271[IOTA0 & 32767] = fRec271[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec272[0]);
			float fTemp333 = std::sqrt(fSlow1 * (fRec271[IOTA0 & 32767] - fRec271[(IOTA0 - iSlow2) & 32767]));
			int iTemp334 = ((fTemp333 > fSlow3) ? fTemp333 : 0.0f) > 0.0f > 0;
			int iTemp335 = iTemp334;
			float fTemp336 = 0.144717798f * ((iTemp335) ? fSlow5 : fSlow4);
			int iTemp337 = std::fabs(fTemp336) < 1.1920929e-07f;
			float fThen213 = std::exp(0.0f - fConst6 / ((iTemp337) ? 1.0f : fTemp336));
			float fTemp338 = ((iTemp337) ? 0.0f : fThen213);
			float fElse214 = float(iTemp334);
			fRec270[0] = (1.0f - fTemp338) * ((iTemp335) ? fElse214 : 0.0f) + fTemp338 * fRec270[1];
			float fTemp339 = fConst436 + fRec277[1] + -1.0f;
			int iTemp340 = fTemp339 < 0.0f;
			float fTemp341 = fConst436 + fRec277[1];
			fRec277[0] = ((iTemp340) ? fTemp341 : fTemp339);
			float fThen216 = fConst436 + fRec277[1] + fConst437 * fTemp339;
			float fRec278 = ((iTemp340) ? fTemp341 : fThen216);
			output30[i0] = FAUSTFLOAT(fRec270[0] * (2.0f * fRec278 + -1.0f));
			fRec285[0] = fTemp0 - fConst447 * (fConst448 * fRec285[1] + fConst449 * fRec285[2]);
			fRec284[0] = fConst446 * fRec285[2] + fConst447 * (fConst443 * fRec285[0] - (fConst448 * fRec284[1] + fConst449 * fRec284[2]));
			fRec283[0] = fConst446 * fRec284[2] + fConst447 * (fConst443 * fRec284[0] - (fConst448 * fRec283[1] + fConst449 * fRec283[2]));
			fRec282[0] = fConst446 * fRec283[2] + fConst447 * (fConst443 * fRec283[0] - (fConst448 * fRec282[1] + fConst449 * fRec282[2]));
			float fTemp342 = fConst446 * fRec282[2];
			float fTemp343 = fConst445 * fRec282[0];
			fVec31[0] = fTemp343 + fTemp342;
			fRec281[0] = (fTemp342 + 0.995000005f * fRec281[1] + fTemp343) - fVec31[1];
			fRec280[IOTA0 & 32767] = fRec280[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec281[0]);
			float fTemp344 = std::sqrt(fSlow1 * (fRec280[IOTA0 & 32767] - fRec280[(IOTA0 - iSlow2) & 32767]));
			int iTemp345 = ((fTemp344 > fSlow3) ? fTemp344 : 0.0f) > 0.0f > 0;
			int iTemp346 = iTemp345;
			float fTemp347 = 0.144717798f * ((iTemp346) ? fSlow5 : fSlow4);
			int iTemp348 = std::fabs(fTemp347) < 1.1920929e-07f;
			float fThen220 = std::exp(0.0f - fConst6 / ((iTemp348) ? 1.0f : fTemp347));
			float fTemp349 = ((iTemp348) ? 0.0f : fThen220);
			float fElse221 = float(iTemp345);
			fRec279[0] = (1.0f - fTemp349) * ((iTemp346) ? fElse221 : 0.0f) + fTemp349 * fRec279[1];
			float fTemp350 = fConst450 + fRec286[1] + -1.0f;
			int iTemp351 = fTemp350 < 0.0f;
			float fTemp352 = fConst450 + fRec286[1];
			fRec286[0] = ((iTemp351) ? fTemp352 : fTemp350);
			float fThen223 = fConst450 + fRec286[1] + fConst451 * fTemp350;
			float fRec287 = ((iTemp351) ? fTemp352 : fThen223);
			output31[i0] = FAUSTFLOAT(fRec279[0] * (2.0f * fRec287 + -1.0f));
			fRec294[0] = fTemp0 - fConst461 * (fConst462 * fRec294[1] + fConst463 * fRec294[2]);
			fRec293[0] = fConst460 * fRec294[2] + fConst461 * (fConst457 * fRec294[0] - (fConst462 * fRec293[1] + fConst463 * fRec293[2]));
			fRec292[0] = fConst460 * fRec293[2] + fConst461 * (fConst457 * fRec293[0] - (fConst462 * fRec292[1] + fConst463 * fRec292[2]));
			fRec291[0] = fConst460 * fRec292[2] + fConst461 * (fConst457 * fRec292[0] - (fConst462 * fRec291[1] + fConst463 * fRec291[2]));
			float fTemp353 = fConst460 * fRec291[2];
			float fTemp354 = fConst459 * fRec291[0];
			fVec32[0] = fTemp354 + fTemp353;
			fRec290[0] = (fTemp353 + 0.995000005f * fRec290[1] + fTemp354) - fVec32[1];
			fRec289[IOTA0 & 32767] = fRec289[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec290[0]);
			float fTemp355 = std::sqrt(fSlow1 * (fRec289[IOTA0 & 32767] - fRec289[(IOTA0 - iSlow2) & 32767]));
			int iTemp356 = ((fTemp355 > fSlow3) ? fTemp355 : 0.0f) > 0.0f > 0;
			int iTemp357 = iTemp356;
			float fTemp358 = 0.144717798f * ((iTemp357) ? fSlow5 : fSlow4);
			int iTemp359 = std::fabs(fTemp358) < 1.1920929e-07f;
			float fThen227 = std::exp(0.0f - fConst6 / ((iTemp359) ? 1.0f : fTemp358));
			float fTemp360 = ((iTemp359) ? 0.0f : fThen227);
			float fElse228 = float(iTemp356);
			fRec288[0] = (1.0f - fTemp360) * ((iTemp357) ? fElse228 : 0.0f) + fTemp360 * fRec288[1];
			float fTemp361 = fConst464 + fRec295[1] + -1.0f;
			int iTemp362 = fTemp361 < 0.0f;
			float fTemp363 = fConst464 + fRec295[1];
			fRec295[0] = ((iTemp362) ? fTemp363 : fTemp361);
			float fThen230 = fConst464 + fRec295[1] + fConst465 * fTemp361;
			float fRec296 = ((iTemp362) ? fTemp363 : fThen230);
			output32[i0] = FAUSTFLOAT(fRec288[0] * (2.0f * fRec296 + -1.0f));
			fRec303[0] = fTemp0 - fConst475 * (fConst476 * fRec303[1] + fConst477 * fRec303[2]);
			fRec302[0] = fConst474 * fRec303[2] + fConst475 * (fConst471 * fRec303[0] - (fConst476 * fRec302[1] + fConst477 * fRec302[2]));
			fRec301[0] = fConst474 * fRec302[2] + fConst475 * (fConst471 * fRec302[0] - (fConst476 * fRec301[1] + fConst477 * fRec301[2]));
			fRec300[0] = fConst474 * fRec301[2] + fConst475 * (fConst471 * fRec301[0] - (fConst476 * fRec300[1] + fConst477 * fRec300[2]));
			float fTemp364 = fConst474 * fRec300[2];
			float fTemp365 = fConst473 * fRec300[0];
			fVec33[0] = fTemp365 + fTemp364;
			fRec299[0] = (fTemp364 + 0.995000005f * fRec299[1] + fTemp365) - fVec33[1];
			fRec298[IOTA0 & 32767] = fRec298[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec299[0]);
			float fTemp366 = std::sqrt(fSlow1 * (fRec298[IOTA0 & 32767] - fRec298[(IOTA0 - iSlow2) & 32767]));
			int iTemp367 = ((fTemp366 > fSlow3) ? fTemp366 : 0.0f) > 0.0f > 0;
			int iTemp368 = iTemp367;
			float fTemp369 = 0.144717798f * ((iTemp368) ? fSlow5 : fSlow4);
			int iTemp370 = std::fabs(fTemp369) < 1.1920929e-07f;
			float fThen234 = std::exp(0.0f - fConst6 / ((iTemp370) ? 1.0f : fTemp369));
			float fTemp371 = ((iTemp370) ? 0.0f : fThen234);
			float fElse235 = float(iTemp367);
			fRec297[0] = (1.0f - fTemp371) * ((iTemp368) ? fElse235 : 0.0f) + fTemp371 * fRec297[1];
			float fTemp372 = fConst478 + fRec304[1] + -1.0f;
			int iTemp373 = fTemp372 < 0.0f;
			float fTemp374 = fConst478 + fRec304[1];
			fRec304[0] = ((iTemp373) ? fTemp374 : fTemp372);
			float fThen237 = fConst478 + fRec304[1] + fConst479 * fTemp372;
			float fRec305 = ((iTemp373) ? fTemp374 : fThen237);
			output33[i0] = FAUSTFLOAT(fRec297[0] * (2.0f * fRec305 + -1.0f));
			fRec312[0] = fTemp0 - fConst489 * (fConst490 * fRec312[1] + fConst491 * fRec312[2]);
			fRec311[0] = fConst488 * fRec312[2] + fConst489 * (fConst485 * fRec312[0] - (fConst490 * fRec311[1] + fConst491 * fRec311[2]));
			fRec310[0] = fConst488 * fRec311[2] + fConst489 * (fConst485 * fRec311[0] - (fConst490 * fRec310[1] + fConst491 * fRec310[2]));
			fRec309[0] = fConst488 * fRec310[2] + fConst489 * (fConst485 * fRec310[0] - (fConst490 * fRec309[1] + fConst491 * fRec309[2]));
			float fTemp375 = fConst488 * fRec309[2];
			float fTemp376 = fConst487 * fRec309[0];
			fVec34[0] = fTemp376 + fTemp375;
			fRec308[0] = (fTemp375 + 0.995000005f * fRec308[1] + fTemp376) - fVec34[1];
			fRec307[IOTA0 & 32767] = fRec307[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec308[0]);
			float fTemp377 = std::sqrt(fSlow1 * (fRec307[IOTA0 & 32767] - fRec307[(IOTA0 - iSlow2) & 32767]));
			int iTemp378 = ((fTemp377 > fSlow3) ? fTemp377 : 0.0f) > 0.0f > 0;
			int iTemp379 = iTemp378;
			float fTemp380 = 0.144717798f * ((iTemp379) ? fSlow5 : fSlow4);
			int iTemp381 = std::fabs(fTemp380) < 1.1920929e-07f;
			float fThen241 = std::exp(0.0f - fConst6 / ((iTemp381) ? 1.0f : fTemp380));
			float fTemp382 = ((iTemp381) ? 0.0f : fThen241);
			float fElse242 = float(iTemp378);
			fRec306[0] = (1.0f - fTemp382) * ((iTemp379) ? fElse242 : 0.0f) + fTemp382 * fRec306[1];
			float fTemp383 = fConst492 + fRec313[1] + -1.0f;
			int iTemp384 = fTemp383 < 0.0f;
			float fTemp385 = fConst492 + fRec313[1];
			fRec313[0] = ((iTemp384) ? fTemp385 : fTemp383);
			float fThen244 = fConst492 + fRec313[1] + fConst493 * fTemp383;
			float fRec314 = ((iTemp384) ? fTemp385 : fThen244);
			output34[i0] = FAUSTFLOAT(fRec306[0] * (2.0f * fRec314 + -1.0f));
			fRec321[0] = fTemp0 - fConst503 * (fConst504 * fRec321[1] + fConst505 * fRec321[2]);
			fRec320[0] = fConst502 * fRec321[2] + fConst503 * (fConst499 * fRec321[0] - (fConst504 * fRec320[1] + fConst505 * fRec320[2]));
			fRec319[0] = fConst502 * fRec320[2] + fConst503 * (fConst499 * fRec320[0] - (fConst504 * fRec319[1] + fConst505 * fRec319[2]));
			fRec318[0] = fConst502 * fRec319[2] + fConst503 * (fConst499 * fRec319[0] - (fConst504 * fRec318[1] + fConst505 * fRec318[2]));
			float fTemp386 = fConst502 * fRec318[2];
			float fTemp387 = fConst501 * fRec318[0];
			fVec35[0] = fTemp387 + fTemp386;
			fRec317[0] = (fTemp386 + 0.995000005f * fRec317[1] + fTemp387) - fVec35[1];
			fRec316[IOTA0 & 32767] = fRec316[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec317[0]);
			float fTemp388 = std::sqrt(fSlow1 * (fRec316[IOTA0 & 32767] - fRec316[(IOTA0 - iSlow2) & 32767]));
			int iTemp389 = ((fTemp388 > fSlow3) ? fTemp388 : 0.0f) > 0.0f > 0;
			int iTemp390 = iTemp389;
			float fTemp391 = 0.144717798f * ((iTemp390) ? fSlow5 : fSlow4);
			int iTemp392 = std::fabs(fTemp391) < 1.1920929e-07f;
			float fThen248 = std::exp(0.0f - fConst6 / ((iTemp392) ? 1.0f : fTemp391));
			float fTemp393 = ((iTemp392) ? 0.0f : fThen248);
			float fElse249 = float(iTemp389);
			fRec315[0] = (1.0f - fTemp393) * ((iTemp390) ? fElse249 : 0.0f) + fTemp393 * fRec315[1];
			float fTemp394 = fConst506 + fRec322[1] + -1.0f;
			int iTemp395 = fTemp394 < 0.0f;
			float fTemp396 = fConst506 + fRec322[1];
			fRec322[0] = ((iTemp395) ? fTemp396 : fTemp394);
			float fThen251 = fConst506 + fRec322[1] + fConst507 * fTemp394;
			float fRec323 = ((iTemp395) ? fTemp396 : fThen251);
			output35[i0] = FAUSTFLOAT(fRec315[0] * (2.0f * fRec323 + -1.0f));
			fRec330[0] = fTemp0 - fConst517 * (fConst518 * fRec330[1] + fConst519 * fRec330[2]);
			fRec329[0] = fConst516 * fRec330[2] + fConst517 * (fConst513 * fRec330[0] - (fConst518 * fRec329[1] + fConst519 * fRec329[2]));
			fRec328[0] = fConst516 * fRec329[2] + fConst517 * (fConst513 * fRec329[0] - (fConst518 * fRec328[1] + fConst519 * fRec328[2]));
			fRec327[0] = fConst516 * fRec328[2] + fConst517 * (fConst513 * fRec328[0] - (fConst518 * fRec327[1] + fConst519 * fRec327[2]));
			float fTemp397 = fConst516 * fRec327[2];
			float fTemp398 = fConst515 * fRec327[0];
			fVec36[0] = fTemp398 + fTemp397;
			fRec326[0] = (fTemp397 + 0.995000005f * fRec326[1] + fTemp398) - fVec36[1];
			fRec325[IOTA0 & 32767] = fRec325[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec326[0]);
			float fTemp399 = std::sqrt(fSlow1 * (fRec325[IOTA0 & 32767] - fRec325[(IOTA0 - iSlow2) & 32767]));
			int iTemp400 = ((fTemp399 > fSlow3) ? fTemp399 : 0.0f) > 0.0f > 0;
			int iTemp401 = iTemp400;
			float fTemp402 = 0.144717798f * ((iTemp401) ? fSlow5 : fSlow4);
			int iTemp403 = std::fabs(fTemp402) < 1.1920929e-07f;
			float fThen255 = std::exp(0.0f - fConst6 / ((iTemp403) ? 1.0f : fTemp402));
			float fTemp404 = ((iTemp403) ? 0.0f : fThen255);
			float fElse256 = float(iTemp400);
			fRec324[0] = (1.0f - fTemp404) * ((iTemp401) ? fElse256 : 0.0f) + fTemp404 * fRec324[1];
			float fTemp405 = fConst520 + fRec331[1] + -1.0f;
			int iTemp406 = fTemp405 < 0.0f;
			float fTemp407 = fConst520 + fRec331[1];
			fRec331[0] = ((iTemp406) ? fTemp407 : fTemp405);
			float fThen258 = fConst520 + fRec331[1] + fConst521 * fTemp405;
			float fRec332 = ((iTemp406) ? fTemp407 : fThen258);
			output36[i0] = FAUSTFLOAT(fRec324[0] * (2.0f * fRec332 + -1.0f));
			fRec339[0] = fTemp0 - fConst531 * (fConst532 * fRec339[1] + fConst533 * fRec339[2]);
			fRec338[0] = fConst530 * fRec339[2] + fConst531 * (fConst527 * fRec339[0] - (fConst532 * fRec338[1] + fConst533 * fRec338[2]));
			fRec337[0] = fConst530 * fRec338[2] + fConst531 * (fConst527 * fRec338[0] - (fConst532 * fRec337[1] + fConst533 * fRec337[2]));
			fRec336[0] = fConst530 * fRec337[2] + fConst531 * (fConst527 * fRec337[0] - (fConst532 * fRec336[1] + fConst533 * fRec336[2]));
			float fTemp408 = fConst530 * fRec336[2];
			float fTemp409 = fConst529 * fRec336[0];
			fVec37[0] = fTemp409 + fTemp408;
			fRec335[0] = (fTemp408 + 0.995000005f * fRec335[1] + fTemp409) - fVec37[1];
			fRec334[IOTA0 & 32767] = fRec334[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec335[0]);
			float fTemp410 = std::sqrt(fSlow1 * (fRec334[IOTA0 & 32767] - fRec334[(IOTA0 - iSlow2) & 32767]));
			int iTemp411 = ((fTemp410 > fSlow3) ? fTemp410 : 0.0f) > 0.0f > 0;
			int iTemp412 = iTemp411;
			float fTemp413 = 0.144717798f * ((iTemp412) ? fSlow5 : fSlow4);
			int iTemp414 = std::fabs(fTemp413) < 1.1920929e-07f;
			float fThen262 = std::exp(0.0f - fConst6 / ((iTemp414) ? 1.0f : fTemp413));
			float fTemp415 = ((iTemp414) ? 0.0f : fThen262);
			float fElse263 = float(iTemp411);
			fRec333[0] = (1.0f - fTemp415) * ((iTemp412) ? fElse263 : 0.0f) + fTemp415 * fRec333[1];
			float fTemp416 = fConst534 + fRec340[1] + -1.0f;
			int iTemp417 = fTemp416 < 0.0f;
			float fTemp418 = fConst534 + fRec340[1];
			fRec340[0] = ((iTemp417) ? fTemp418 : fTemp416);
			float fThen265 = fConst534 + fRec340[1] + fConst535 * fTemp416;
			float fRec341 = ((iTemp417) ? fTemp418 : fThen265);
			output37[i0] = FAUSTFLOAT(fRec333[0] * (2.0f * fRec341 + -1.0f));
			fRec348[0] = fTemp0 - fConst545 * (fConst546 * fRec348[1] + fConst547 * fRec348[2]);
			fRec347[0] = fConst544 * fRec348[2] + fConst545 * (fConst541 * fRec348[0] - (fConst546 * fRec347[1] + fConst547 * fRec347[2]));
			fRec346[0] = fConst544 * fRec347[2] + fConst545 * (fConst541 * fRec347[0] - (fConst546 * fRec346[1] + fConst547 * fRec346[2]));
			fRec345[0] = fConst544 * fRec346[2] + fConst545 * (fConst541 * fRec346[0] - (fConst546 * fRec345[1] + fConst547 * fRec345[2]));
			float fTemp419 = fConst544 * fRec345[2];
			float fTemp420 = fConst543 * fRec345[0];
			fVec38[0] = fTemp420 + fTemp419;
			fRec344[0] = (fTemp419 + 0.995000005f * fRec344[1] + fTemp420) - fVec38[1];
			fRec343[IOTA0 & 32767] = fRec343[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec344[0]);
			float fTemp421 = std::sqrt(fSlow1 * (fRec343[IOTA0 & 32767] - fRec343[(IOTA0 - iSlow2) & 32767]));
			int iTemp422 = ((fTemp421 > fSlow3) ? fTemp421 : 0.0f) > 0.0f > 0;
			int iTemp423 = iTemp422;
			float fTemp424 = 0.144717798f * ((iTemp423) ? fSlow5 : fSlow4);
			int iTemp425 = std::fabs(fTemp424) < 1.1920929e-07f;
			float fThen269 = std::exp(0.0f - fConst6 / ((iTemp425) ? 1.0f : fTemp424));
			float fTemp426 = ((iTemp425) ? 0.0f : fThen269);
			float fElse270 = float(iTemp422);
			fRec342[0] = (1.0f - fTemp426) * ((iTemp423) ? fElse270 : 0.0f) + fTemp426 * fRec342[1];
			float fTemp427 = fConst548 + fRec349[1] + -1.0f;
			int iTemp428 = fTemp427 < 0.0f;
			float fTemp429 = fConst548 + fRec349[1];
			fRec349[0] = ((iTemp428) ? fTemp429 : fTemp427);
			float fThen272 = fConst548 + fRec349[1] + fConst549 * fTemp427;
			float fRec350 = ((iTemp428) ? fTemp429 : fThen272);
			output38[i0] = FAUSTFLOAT(fRec342[0] * (2.0f * fRec350 + -1.0f));
			fRec357[0] = fTemp0 - fConst559 * (fConst560 * fRec357[1] + fConst561 * fRec357[2]);
			fRec356[0] = fConst558 * fRec357[2] + fConst559 * (fConst555 * fRec357[0] - (fConst560 * fRec356[1] + fConst561 * fRec356[2]));
			fRec355[0] = fConst558 * fRec356[2] + fConst559 * (fConst555 * fRec356[0] - (fConst560 * fRec355[1] + fConst561 * fRec355[2]));
			fRec354[0] = fConst558 * fRec355[2] + fConst559 * (fConst555 * fRec355[0] - (fConst560 * fRec354[1] + fConst561 * fRec354[2]));
			float fTemp430 = fConst558 * fRec354[2];
			float fTemp431 = fConst557 * fRec354[0];
			fVec39[0] = fTemp431 + fTemp430;
			fRec353[0] = (fTemp430 + 0.995000005f * fRec353[1] + fTemp431) - fVec39[1];
			fRec352[IOTA0 & 32767] = fRec352[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec353[0]);
			float fTemp432 = std::sqrt(fSlow1 * (fRec352[IOTA0 & 32767] - fRec352[(IOTA0 - iSlow2) & 32767]));
			int iTemp433 = ((fTemp432 > fSlow3) ? fTemp432 : 0.0f) > 0.0f > 0;
			int iTemp434 = iTemp433;
			float fTemp435 = 0.144717798f * ((iTemp434) ? fSlow5 : fSlow4);
			int iTemp436 = std::fabs(fTemp435) < 1.1920929e-07f;
			float fThen276 = std::exp(0.0f - fConst6 / ((iTemp436) ? 1.0f : fTemp435));
			float fTemp437 = ((iTemp436) ? 0.0f : fThen276);
			float fElse277 = float(iTemp433);
			fRec351[0] = (1.0f - fTemp437) * ((iTemp434) ? fElse277 : 0.0f) + fTemp437 * fRec351[1];
			float fTemp438 = fConst562 + fRec358[1] + -1.0f;
			int iTemp439 = fTemp438 < 0.0f;
			float fTemp440 = fConst562 + fRec358[1];
			fRec358[0] = ((iTemp439) ? fTemp440 : fTemp438);
			float fThen279 = fConst562 + fRec358[1] + fConst563 * fTemp438;
			float fRec359 = ((iTemp439) ? fTemp440 : fThen279);
			output39[i0] = FAUSTFLOAT(fRec351[0] * (2.0f * fRec359 + -1.0f));
			fRec366[0] = fTemp0 - fConst573 * (fConst574 * fRec366[1] + fConst575 * fRec366[2]);
			fRec365[0] = fConst572 * fRec366[2] + fConst573 * (fConst569 * fRec366[0] - (fConst574 * fRec365[1] + fConst575 * fRec365[2]));
			fRec364[0] = fConst572 * fRec365[2] + fConst573 * (fConst569 * fRec365[0] - (fConst574 * fRec364[1] + fConst575 * fRec364[2]));
			fRec363[0] = fConst572 * fRec364[2] + fConst573 * (fConst569 * fRec364[0] - (fConst574 * fRec363[1] + fConst575 * fRec363[2]));
			float fTemp441 = fConst572 * fRec363[2];
			float fTemp442 = fConst571 * fRec363[0];
			fVec40[0] = fTemp442 + fTemp441;
			fRec362[0] = (fTemp441 + 0.995000005f * fRec362[1] + fTemp442) - fVec40[1];
			fRec361[IOTA0 & 32767] = fRec361[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec362[0]);
			float fTemp443 = std::sqrt(fSlow1 * (fRec361[IOTA0 & 32767] - fRec361[(IOTA0 - iSlow2) & 32767]));
			int iTemp444 = ((fTemp443 > fSlow3) ? fTemp443 : 0.0f) > 0.0f > 0;
			int iTemp445 = iTemp444;
			float fTemp446 = 0.144717798f * ((iTemp445) ? fSlow5 : fSlow4);
			int iTemp447 = std::fabs(fTemp446) < 1.1920929e-07f;
			float fThen283 = std::exp(0.0f - fConst6 / ((iTemp447) ? 1.0f : fTemp446));
			float fTemp448 = ((iTemp447) ? 0.0f : fThen283);
			float fElse284 = float(iTemp444);
			fRec360[0] = (1.0f - fTemp448) * ((iTemp445) ? fElse284 : 0.0f) + fTemp448 * fRec360[1];
			float fTemp449 = fConst576 + fRec367[1] + -1.0f;
			int iTemp450 = fTemp449 < 0.0f;
			float fTemp451 = fConst576 + fRec367[1];
			fRec367[0] = ((iTemp450) ? fTemp451 : fTemp449);
			float fThen286 = fConst576 + fRec367[1] + fConst577 * fTemp449;
			float fRec368 = ((iTemp450) ? fTemp451 : fThen286);
			output40[i0] = FAUSTFLOAT(fRec360[0] * (2.0f * fRec368 + -1.0f));
			fRec375[0] = fTemp0 - fConst587 * (fConst588 * fRec375[1] + fConst589 * fRec375[2]);
			fRec374[0] = fConst586 * fRec375[2] + fConst587 * (fConst583 * fRec375[0] - (fConst588 * fRec374[1] + fConst589 * fRec374[2]));
			fRec373[0] = fConst586 * fRec374[2] + fConst587 * (fConst583 * fRec374[0] - (fConst588 * fRec373[1] + fConst589 * fRec373[2]));
			fRec372[0] = fConst586 * fRec373[2] + fConst587 * (fConst583 * fRec373[0] - (fConst588 * fRec372[1] + fConst589 * fRec372[2]));
			float fTemp452 = fConst586 * fRec372[2];
			float fTemp453 = fConst585 * fRec372[0];
			fVec41[0] = fTemp453 + fTemp452;
			fRec371[0] = (fTemp452 + 0.995000005f * fRec371[1] + fTemp453) - fVec41[1];
			fRec370[IOTA0 & 32767] = fRec370[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec371[0]);
			float fTemp454 = std::sqrt(fSlow1 * (fRec370[IOTA0 & 32767] - fRec370[(IOTA0 - iSlow2) & 32767]));
			int iTemp455 = ((fTemp454 > fSlow3) ? fTemp454 : 0.0f) > 0.0f > 0;
			int iTemp456 = iTemp455;
			float fTemp457 = 0.144717798f * ((iTemp456) ? fSlow5 : fSlow4);
			int iTemp458 = std::fabs(fTemp457) < 1.1920929e-07f;
			float fThen290 = std::exp(0.0f - fConst6 / ((iTemp458) ? 1.0f : fTemp457));
			float fTemp459 = ((iTemp458) ? 0.0f : fThen290);
			float fElse291 = float(iTemp455);
			fRec369[0] = (1.0f - fTemp459) * ((iTemp456) ? fElse291 : 0.0f) + fTemp459 * fRec369[1];
			float fTemp460 = fConst590 + fRec376[1] + -1.0f;
			int iTemp461 = fTemp460 < 0.0f;
			float fTemp462 = fConst590 + fRec376[1];
			fRec376[0] = ((iTemp461) ? fTemp462 : fTemp460);
			float fThen293 = fConst590 + fRec376[1] + fConst591 * fTemp460;
			float fRec377 = ((iTemp461) ? fTemp462 : fThen293);
			output41[i0] = FAUSTFLOAT(fRec369[0] * (2.0f * fRec377 + -1.0f));
			fRec384[0] = fTemp0 - fConst601 * (fConst602 * fRec384[1] + fConst603 * fRec384[2]);
			fRec383[0] = fConst600 * fRec384[2] + fConst601 * (fConst597 * fRec384[0] - (fConst602 * fRec383[1] + fConst603 * fRec383[2]));
			fRec382[0] = fConst600 * fRec383[2] + fConst601 * (fConst597 * fRec383[0] - (fConst602 * fRec382[1] + fConst603 * fRec382[2]));
			fRec381[0] = fConst600 * fRec382[2] + fConst601 * (fConst597 * fRec382[0] - (fConst602 * fRec381[1] + fConst603 * fRec381[2]));
			float fTemp463 = fConst600 * fRec381[2];
			float fTemp464 = fConst599 * fRec381[0];
			fVec42[0] = fTemp464 + fTemp463;
			fRec380[0] = (fTemp463 + 0.995000005f * fRec380[1] + fTemp464) - fVec42[1];
			fRec379[IOTA0 & 32767] = fRec379[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec380[0]);
			float fTemp465 = std::sqrt(fSlow1 * (fRec379[IOTA0 & 32767] - fRec379[(IOTA0 - iSlow2) & 32767]));
			int iTemp466 = ((fTemp465 > fSlow3) ? fTemp465 : 0.0f) > 0.0f > 0;
			int iTemp467 = iTemp466;
			float fTemp468 = 0.144717798f * ((iTemp467) ? fSlow5 : fSlow4);
			int iTemp469 = std::fabs(fTemp468) < 1.1920929e-07f;
			float fThen297 = std::exp(0.0f - fConst6 / ((iTemp469) ? 1.0f : fTemp468));
			float fTemp470 = ((iTemp469) ? 0.0f : fThen297);
			float fElse298 = float(iTemp466);
			fRec378[0] = (1.0f - fTemp470) * ((iTemp467) ? fElse298 : 0.0f) + fTemp470 * fRec378[1];
			float fTemp471 = fConst604 + fRec385[1] + -1.0f;
			int iTemp472 = fTemp471 < 0.0f;
			float fTemp473 = fConst604 + fRec385[1];
			fRec385[0] = ((iTemp472) ? fTemp473 : fTemp471);
			float fThen300 = fConst604 + fRec385[1] + fConst605 * fTemp471;
			float fRec386 = ((iTemp472) ? fTemp473 : fThen300);
			output42[i0] = FAUSTFLOAT(fRec378[0] * (2.0f * fRec386 + -1.0f));
			fRec393[0] = fTemp0 - fConst615 * (fConst616 * fRec393[1] + fConst617 * fRec393[2]);
			fRec392[0] = fConst614 * fRec393[2] + fConst615 * (fConst611 * fRec393[0] - (fConst616 * fRec392[1] + fConst617 * fRec392[2]));
			fRec391[0] = fConst614 * fRec392[2] + fConst615 * (fConst611 * fRec392[0] - (fConst616 * fRec391[1] + fConst617 * fRec391[2]));
			fRec390[0] = fConst614 * fRec391[2] + fConst615 * (fConst611 * fRec391[0] - (fConst616 * fRec390[1] + fConst617 * fRec390[2]));
			float fTemp474 = fConst614 * fRec390[2];
			float fTemp475 = fConst613 * fRec390[0];
			fVec43[0] = fTemp475 + fTemp474;
			fRec389[0] = (fTemp474 + 0.995000005f * fRec389[1] + fTemp475) - fVec43[1];
			fRec388[IOTA0 & 32767] = fRec388[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec389[0]);
			float fTemp476 = std::sqrt(fSlow1 * (fRec388[IOTA0 & 32767] - fRec388[(IOTA0 - iSlow2) & 32767]));
			int iTemp477 = ((fTemp476 > fSlow3) ? fTemp476 : 0.0f) > 0.0f > 0;
			int iTemp478 = iTemp477;
			float fTemp479 = 0.144717798f * ((iTemp478) ? fSlow5 : fSlow4);
			int iTemp480 = std::fabs(fTemp479) < 1.1920929e-07f;
			float fThen304 = std::exp(0.0f - fConst6 / ((iTemp480) ? 1.0f : fTemp479));
			float fTemp481 = ((iTemp480) ? 0.0f : fThen304);
			float fElse305 = float(iTemp477);
			fRec387[0] = (1.0f - fTemp481) * ((iTemp478) ? fElse305 : 0.0f) + fTemp481 * fRec387[1];
			float fTemp482 = fConst618 + fRec394[1] + -1.0f;
			int iTemp483 = fTemp482 < 0.0f;
			float fTemp484 = fConst618 + fRec394[1];
			fRec394[0] = ((iTemp483) ? fTemp484 : fTemp482);
			float fThen307 = fConst618 + fRec394[1] + fConst619 * fTemp482;
			float fRec395 = ((iTemp483) ? fTemp484 : fThen307);
			output43[i0] = FAUSTFLOAT(fRec387[0] * (2.0f * fRec395 + -1.0f));
			fRec402[0] = fTemp0 - fConst629 * (fConst630 * fRec402[1] + fConst631 * fRec402[2]);
			fRec401[0] = fConst628 * fRec402[2] + fConst629 * (fConst625 * fRec402[0] - (fConst630 * fRec401[1] + fConst631 * fRec401[2]));
			fRec400[0] = fConst628 * fRec401[2] + fConst629 * (fConst625 * fRec401[0] - (fConst630 * fRec400[1] + fConst631 * fRec400[2]));
			fRec399[0] = fConst628 * fRec400[2] + fConst629 * (fConst625 * fRec400[0] - (fConst630 * fRec399[1] + fConst631 * fRec399[2]));
			float fTemp485 = fConst628 * fRec399[2];
			float fTemp486 = fConst627 * fRec399[0];
			fVec44[0] = fTemp486 + fTemp485;
			fRec398[0] = (fTemp485 + 0.995000005f * fRec398[1] + fTemp486) - fVec44[1];
			fRec397[IOTA0 & 32767] = fRec397[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec398[0]);
			float fTemp487 = std::sqrt(fSlow1 * (fRec397[IOTA0 & 32767] - fRec397[(IOTA0 - iSlow2) & 32767]));
			int iTemp488 = ((fTemp487 > fSlow3) ? fTemp487 : 0.0f) > 0.0f > 0;
			int iTemp489 = iTemp488;
			float fTemp490 = 0.144717798f * ((iTemp489) ? fSlow5 : fSlow4);
			int iTemp491 = std::fabs(fTemp490) < 1.1920929e-07f;
			float fThen311 = std::exp(0.0f - fConst6 / ((iTemp491) ? 1.0f : fTemp490));
			float fTemp492 = ((iTemp491) ? 0.0f : fThen311);
			float fElse312 = float(iTemp488);
			fRec396[0] = (1.0f - fTemp492) * ((iTemp489) ? fElse312 : 0.0f) + fTemp492 * fRec396[1];
			float fTemp493 = fConst632 + fRec403[1] + -1.0f;
			int iTemp494 = fTemp493 < 0.0f;
			float fTemp495 = fConst632 + fRec403[1];
			fRec403[0] = ((iTemp494) ? fTemp495 : fTemp493);
			float fThen314 = fConst632 + fRec403[1] + fConst633 * fTemp493;
			float fRec404 = ((iTemp494) ? fTemp495 : fThen314);
			output44[i0] = FAUSTFLOAT(fRec396[0] * (2.0f * fRec404 + -1.0f));
			fRec411[0] = fTemp0 - fConst643 * (fConst644 * fRec411[1] + fConst645 * fRec411[2]);
			fRec410[0] = fConst642 * fRec411[2] + fConst643 * (fConst639 * fRec411[0] - (fConst644 * fRec410[1] + fConst645 * fRec410[2]));
			fRec409[0] = fConst642 * fRec410[2] + fConst643 * (fConst639 * fRec410[0] - (fConst644 * fRec409[1] + fConst645 * fRec409[2]));
			fRec408[0] = fConst642 * fRec409[2] + fConst643 * (fConst639 * fRec409[0] - (fConst644 * fRec408[1] + fConst645 * fRec408[2]));
			float fTemp496 = fConst642 * fRec408[2];
			float fTemp497 = fConst641 * fRec408[0];
			fVec45[0] = fTemp497 + fTemp496;
			fRec407[0] = (fTemp496 + 0.995000005f * fRec407[1] + fTemp497) - fVec45[1];
			fRec406[IOTA0 & 32767] = fRec406[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec407[0]);
			float fTemp498 = std::sqrt(fSlow1 * (fRec406[IOTA0 & 32767] - fRec406[(IOTA0 - iSlow2) & 32767]));
			int iTemp499 = ((fTemp498 > fSlow3) ? fTemp498 : 0.0f) > 0.0f > 0;
			int iTemp500 = iTemp499;
			float fTemp501 = 0.144717798f * ((iTemp500) ? fSlow5 : fSlow4);
			int iTemp502 = std::fabs(fTemp501) < 1.1920929e-07f;
			float fThen318 = std::exp(0.0f - fConst6 / ((iTemp502) ? 1.0f : fTemp501));
			float fTemp503 = ((iTemp502) ? 0.0f : fThen318);
			float fElse319 = float(iTemp499);
			fRec405[0] = (1.0f - fTemp503) * ((iTemp500) ? fElse319 : 0.0f) + fTemp503 * fRec405[1];
			float fTemp504 = fConst646 + fRec412[1] + -1.0f;
			int iTemp505 = fTemp504 < 0.0f;
			float fTemp506 = fConst646 + fRec412[1];
			fRec412[0] = ((iTemp505) ? fTemp506 : fTemp504);
			float fThen321 = fConst646 + fRec412[1] + fConst647 * fTemp504;
			float fRec413 = ((iTemp505) ? fTemp506 : fThen321);
			output45[i0] = FAUSTFLOAT(fRec405[0] * (2.0f * fRec413 + -1.0f));
			fRec420[0] = fTemp0 - fConst657 * (fConst658 * fRec420[1] + fConst659 * fRec420[2]);
			fRec419[0] = fConst656 * fRec420[2] + fConst657 * (fConst653 * fRec420[0] - (fConst658 * fRec419[1] + fConst659 * fRec419[2]));
			fRec418[0] = fConst656 * fRec419[2] + fConst657 * (fConst653 * fRec419[0] - (fConst658 * fRec418[1] + fConst659 * fRec418[2]));
			fRec417[0] = fConst656 * fRec418[2] + fConst657 * (fConst653 * fRec418[0] - (fConst658 * fRec417[1] + fConst659 * fRec417[2]));
			float fTemp507 = fConst656 * fRec417[2];
			float fTemp508 = fConst655 * fRec417[0];
			fVec46[0] = fTemp508 + fTemp507;
			fRec416[0] = (fTemp507 + 0.995000005f * fRec416[1] + fTemp508) - fVec46[1];
			fRec415[IOTA0 & 32767] = fRec415[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec416[0]);
			float fTemp509 = std::sqrt(fSlow1 * (fRec415[IOTA0 & 32767] - fRec415[(IOTA0 - iSlow2) & 32767]));
			int iTemp510 = ((fTemp509 > fSlow3) ? fTemp509 : 0.0f) > 0.0f > 0;
			int iTemp511 = iTemp510;
			float fTemp512 = 0.144717798f * ((iTemp511) ? fSlow5 : fSlow4);
			int iTemp513 = std::fabs(fTemp512) < 1.1920929e-07f;
			float fThen325 = std::exp(0.0f - fConst6 / ((iTemp513) ? 1.0f : fTemp512));
			float fTemp514 = ((iTemp513) ? 0.0f : fThen325);
			float fElse326 = float(iTemp510);
			fRec414[0] = (1.0f - fTemp514) * ((iTemp511) ? fElse326 : 0.0f) + fTemp514 * fRec414[1];
			float fTemp515 = fConst660 + fRec421[1] + -1.0f;
			int iTemp516 = fTemp515 < 0.0f;
			float fTemp517 = fConst660 + fRec421[1];
			fRec421[0] = ((iTemp516) ? fTemp517 : fTemp515);
			float fThen328 = fConst660 + fRec421[1] + fConst661 * fTemp515;
			float fRec422 = ((iTemp516) ? fTemp517 : fThen328);
			output46[i0] = FAUSTFLOAT(fRec414[0] * (2.0f * fRec422 + -1.0f));
			fRec429[0] = fTemp0 - fConst671 * (fConst672 * fRec429[1] + fConst673 * fRec429[2]);
			fRec428[0] = fConst670 * fRec429[2] + fConst671 * (fConst667 * fRec429[0] - (fConst672 * fRec428[1] + fConst673 * fRec428[2]));
			fRec427[0] = fConst670 * fRec428[2] + fConst671 * (fConst667 * fRec428[0] - (fConst672 * fRec427[1] + fConst673 * fRec427[2]));
			fRec426[0] = fConst670 * fRec427[2] + fConst671 * (fConst667 * fRec427[0] - (fConst672 * fRec426[1] + fConst673 * fRec426[2]));
			float fTemp518 = fConst670 * fRec426[2];
			float fTemp519 = fConst669 * fRec426[0];
			fVec47[0] = fTemp519 + fTemp518;
			fRec425[0] = (fTemp518 + 0.995000005f * fRec425[1] + fTemp519) - fVec47[1];
			fRec424[IOTA0 & 32767] = fRec424[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec425[0]);
			float fTemp520 = std::sqrt(fSlow1 * (fRec424[IOTA0 & 32767] - fRec424[(IOTA0 - iSlow2) & 32767]));
			int iTemp521 = ((fTemp520 > fSlow3) ? fTemp520 : 0.0f) > 0.0f > 0;
			int iTemp522 = iTemp521;
			float fTemp523 = 0.144717798f * ((iTemp522) ? fSlow5 : fSlow4);
			int iTemp524 = std::fabs(fTemp523) < 1.1920929e-07f;
			float fThen332 = std::exp(0.0f - fConst6 / ((iTemp524) ? 1.0f : fTemp523));
			float fTemp525 = ((iTemp524) ? 0.0f : fThen332);
			float fElse333 = float(iTemp521);
			fRec423[0] = (1.0f - fTemp525) * ((iTemp522) ? fElse333 : 0.0f) + fTemp525 * fRec423[1];
			float fTemp526 = fConst674 + fRec430[1] + -1.0f;
			int iTemp527 = fTemp526 < 0.0f;
			float fTemp528 = fConst674 + fRec430[1];
			fRec430[0] = ((iTemp527) ? fTemp528 : fTemp526);
			float fThen335 = fConst674 + fRec430[1] + fConst675 * fTemp526;
			float fRec431 = ((iTemp527) ? fTemp528 : fThen335);
			output47[i0] = FAUSTFLOAT(fRec423[0] * (2.0f * fRec431 + -1.0f));
			fRec438[0] = fTemp0 - fConst685 * (fConst686 * fRec438[1] + fConst687 * fRec438[2]);
			fRec437[0] = fConst684 * fRec438[2] + fConst685 * (fConst681 * fRec438[0] - (fConst686 * fRec437[1] + fConst687 * fRec437[2]));
			fRec436[0] = fConst684 * fRec437[2] + fConst685 * (fConst681 * fRec437[0] - (fConst686 * fRec436[1] + fConst687 * fRec436[2]));
			fRec435[0] = fConst684 * fRec436[2] + fConst685 * (fConst681 * fRec436[0] - (fConst686 * fRec435[1] + fConst687 * fRec435[2]));
			float fTemp529 = fConst684 * fRec435[2];
			float fTemp530 = fConst683 * fRec435[0];
			fVec48[0] = fTemp530 + fTemp529;
			fRec434[0] = (fTemp529 + 0.995000005f * fRec434[1] + fTemp530) - fVec48[1];
			fRec433[IOTA0 & 32767] = fRec433[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec434[0]);
			float fTemp531 = std::sqrt(fSlow1 * (fRec433[IOTA0 & 32767] - fRec433[(IOTA0 - iSlow2) & 32767]));
			int iTemp532 = ((fTemp531 > fSlow3) ? fTemp531 : 0.0f) > 0.0f > 0;
			int iTemp533 = iTemp532;
			float fTemp534 = 0.144717798f * ((iTemp533) ? fSlow5 : fSlow4);
			int iTemp535 = std::fabs(fTemp534) < 1.1920929e-07f;
			float fThen339 = std::exp(0.0f - fConst6 / ((iTemp535) ? 1.0f : fTemp534));
			float fTemp536 = ((iTemp535) ? 0.0f : fThen339);
			float fElse340 = float(iTemp532);
			fRec432[0] = (1.0f - fTemp536) * ((iTemp533) ? fElse340 : 0.0f) + fTemp536 * fRec432[1];
			float fTemp537 = fConst688 + fRec439[1] + -1.0f;
			int iTemp538 = fTemp537 < 0.0f;
			float fTemp539 = fConst688 + fRec439[1];
			fRec439[0] = ((iTemp538) ? fTemp539 : fTemp537);
			float fThen342 = fConst688 + fRec439[1] + fConst689 * fTemp537;
			float fRec440 = ((iTemp538) ? fTemp539 : fThen342);
			output48[i0] = FAUSTFLOAT(fRec432[0] * (2.0f * fRec440 + -1.0f));
			fRec447[0] = fTemp0 - fConst699 * (fConst700 * fRec447[1] + fConst701 * fRec447[2]);
			fRec446[0] = fConst698 * fRec447[2] + fConst699 * (fConst695 * fRec447[0] - (fConst700 * fRec446[1] + fConst701 * fRec446[2]));
			fRec445[0] = fConst698 * fRec446[2] + fConst699 * (fConst695 * fRec446[0] - (fConst700 * fRec445[1] + fConst701 * fRec445[2]));
			fRec444[0] = fConst698 * fRec445[2] + fConst699 * (fConst695 * fRec445[0] - (fConst700 * fRec444[1] + fConst701 * fRec444[2]));
			float fTemp540 = fConst698 * fRec444[2];
			float fTemp541 = fConst697 * fRec444[0];
			fVec49[0] = fTemp541 + fTemp540;
			fRec443[0] = (fTemp540 + 0.995000005f * fRec443[1] + fTemp541) - fVec49[1];
			fRec442[IOTA0 & 32767] = fRec442[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec443[0]);
			float fTemp542 = std::sqrt(fSlow1 * (fRec442[IOTA0 & 32767] - fRec442[(IOTA0 - iSlow2) & 32767]));
			int iTemp543 = ((fTemp542 > fSlow3) ? fTemp542 : 0.0f) > 0.0f > 0;
			int iTemp544 = iTemp543;
			float fTemp545 = 0.144717798f * ((iTemp544) ? fSlow5 : fSlow4);
			int iTemp546 = std::fabs(fTemp545) < 1.1920929e-07f;
			float fThen346 = std::exp(0.0f - fConst6 / ((iTemp546) ? 1.0f : fTemp545));
			float fTemp547 = ((iTemp546) ? 0.0f : fThen346);
			float fElse347 = float(iTemp543);
			fRec441[0] = (1.0f - fTemp547) * ((iTemp544) ? fElse347 : 0.0f) + fTemp547 * fRec441[1];
			float fTemp548 = fConst702 + fRec448[1] + -1.0f;
			int iTemp549 = fTemp548 < 0.0f;
			float fTemp550 = fConst702 + fRec448[1];
			fRec448[0] = ((iTemp549) ? fTemp550 : fTemp548);
			float fThen349 = fConst702 + fRec448[1] + fConst703 * fTemp548;
			float fRec449 = ((iTemp549) ? fTemp550 : fThen349);
			output49[i0] = FAUSTFLOAT(fRec441[0] * (2.0f * fRec449 + -1.0f));
			fRec456[0] = fTemp0 - fConst713 * (fConst714 * fRec456[1] + fConst715 * fRec456[2]);
			fRec455[0] = fConst712 * fRec456[2] + fConst713 * (fConst709 * fRec456[0] - (fConst714 * fRec455[1] + fConst715 * fRec455[2]));
			fRec454[0] = fConst712 * fRec455[2] + fConst713 * (fConst709 * fRec455[0] - (fConst714 * fRec454[1] + fConst715 * fRec454[2]));
			fRec453[0] = fConst712 * fRec454[2] + fConst713 * (fConst709 * fRec454[0] - (fConst714 * fRec453[1] + fConst715 * fRec453[2]));
			float fTemp551 = fConst712 * fRec453[2];
			float fTemp552 = fConst711 * fRec453[0];
			fVec50[0] = fTemp552 + fTemp551;
			fRec452[0] = (fTemp551 + 0.995000005f * fRec452[1] + fTemp552) - fVec50[1];
			fRec451[IOTA0 & 32767] = fRec451[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec452[0]);
			float fTemp553 = std::sqrt(fSlow1 * (fRec451[IOTA0 & 32767] - fRec451[(IOTA0 - iSlow2) & 32767]));
			int iTemp554 = ((fTemp553 > fSlow3) ? fTemp553 : 0.0f) > 0.0f > 0;
			int iTemp555 = iTemp554;
			float fTemp556 = 0.144717798f * ((iTemp555) ? fSlow5 : fSlow4);
			int iTemp557 = std::fabs(fTemp556) < 1.1920929e-07f;
			float fThen353 = std::exp(0.0f - fConst6 / ((iTemp557) ? 1.0f : fTemp556));
			float fTemp558 = ((iTemp557) ? 0.0f : fThen353);
			float fElse354 = float(iTemp554);
			fRec450[0] = (1.0f - fTemp558) * ((iTemp555) ? fElse354 : 0.0f) + fTemp558 * fRec450[1];
			float fTemp559 = fConst716 + fRec457[1] + -1.0f;
			int iTemp560 = fTemp559 < 0.0f;
			float fTemp561 = fConst716 + fRec457[1];
			fRec457[0] = ((iTemp560) ? fTemp561 : fTemp559);
			float fThen356 = fConst716 + fRec457[1] + fConst717 * fTemp559;
			float fRec458 = ((iTemp560) ? fTemp561 : fThen356);
			output50[i0] = FAUSTFLOAT(fRec450[0] * (2.0f * fRec458 + -1.0f));
			fRec465[0] = fTemp0 - fConst727 * (fConst728 * fRec465[1] + fConst729 * fRec465[2]);
			fRec464[0] = fConst726 * fRec465[2] + fConst727 * (fConst723 * fRec465[0] - (fConst728 * fRec464[1] + fConst729 * fRec464[2]));
			fRec463[0] = fConst726 * fRec464[2] + fConst727 * (fConst723 * fRec464[0] - (fConst728 * fRec463[1] + fConst729 * fRec463[2]));
			fRec462[0] = fConst726 * fRec463[2] + fConst727 * (fConst723 * fRec463[0] - (fConst728 * fRec462[1] + fConst729 * fRec462[2]));
			float fTemp562 = fConst726 * fRec462[2];
			float fTemp563 = fConst725 * fRec462[0];
			fVec51[0] = fTemp563 + fTemp562;
			fRec461[0] = (fTemp562 + 0.995000005f * fRec461[1] + fTemp563) - fVec51[1];
			fRec460[IOTA0 & 32767] = fRec460[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec461[0]);
			float fTemp564 = std::sqrt(fSlow1 * (fRec460[IOTA0 & 32767] - fRec460[(IOTA0 - iSlow2) & 32767]));
			int iTemp565 = ((fTemp564 > fSlow3) ? fTemp564 : 0.0f) > 0.0f > 0;
			int iTemp566 = iTemp565;
			float fTemp567 = 0.144717798f * ((iTemp566) ? fSlow5 : fSlow4);
			int iTemp568 = std::fabs(fTemp567) < 1.1920929e-07f;
			float fThen360 = std::exp(0.0f - fConst6 / ((iTemp568) ? 1.0f : fTemp567));
			float fTemp569 = ((iTemp568) ? 0.0f : fThen360);
			float fElse361 = float(iTemp565);
			fRec459[0] = (1.0f - fTemp569) * ((iTemp566) ? fElse361 : 0.0f) + fTemp569 * fRec459[1];
			float fTemp570 = fConst730 + fRec466[1] + -1.0f;
			int iTemp571 = fTemp570 < 0.0f;
			float fTemp572 = fConst730 + fRec466[1];
			fRec466[0] = ((iTemp571) ? fTemp572 : fTemp570);
			float fThen363 = fConst730 + fRec466[1] + fConst731 * fTemp570;
			float fRec467 = ((iTemp571) ? fTemp572 : fThen363);
			output51[i0] = FAUSTFLOAT(fRec459[0] * (2.0f * fRec467 + -1.0f));
			fRec474[0] = fTemp0 - fConst741 * (fConst742 * fRec474[1] + fConst743 * fRec474[2]);
			fRec473[0] = fConst740 * fRec474[2] + fConst741 * (fConst737 * fRec474[0] - (fConst742 * fRec473[1] + fConst743 * fRec473[2]));
			fRec472[0] = fConst740 * fRec473[2] + fConst741 * (fConst737 * fRec473[0] - (fConst742 * fRec472[1] + fConst743 * fRec472[2]));
			fRec471[0] = fConst740 * fRec472[2] + fConst741 * (fConst737 * fRec472[0] - (fConst742 * fRec471[1] + fConst743 * fRec471[2]));
			float fTemp573 = fConst740 * fRec471[2];
			float fTemp574 = fConst739 * fRec471[0];
			fVec52[0] = fTemp574 + fTemp573;
			fRec470[0] = (fTemp573 + 0.995000005f * fRec470[1] + fTemp574) - fVec52[1];
			fRec469[IOTA0 & 32767] = fRec469[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec470[0]);
			float fTemp575 = std::sqrt(fSlow1 * (fRec469[IOTA0 & 32767] - fRec469[(IOTA0 - iSlow2) & 32767]));
			int iTemp576 = ((fTemp575 > fSlow3) ? fTemp575 : 0.0f) > 0.0f > 0;
			int iTemp577 = iTemp576;
			float fTemp578 = 0.144717798f * ((iTemp577) ? fSlow5 : fSlow4);
			int iTemp579 = std::fabs(fTemp578) < 1.1920929e-07f;
			float fThen367 = std::exp(0.0f - fConst6 / ((iTemp579) ? 1.0f : fTemp578));
			float fTemp580 = ((iTemp579) ? 0.0f : fThen367);
			float fElse368 = float(iTemp576);
			fRec468[0] = (1.0f - fTemp580) * ((iTemp577) ? fElse368 : 0.0f) + fTemp580 * fRec468[1];
			float fTemp581 = fConst744 + fRec475[1] + -1.0f;
			int iTemp582 = fTemp581 < 0.0f;
			float fTemp583 = fConst744 + fRec475[1];
			fRec475[0] = ((iTemp582) ? fTemp583 : fTemp581);
			float fThen370 = fConst744 + fRec475[1] + fConst745 * fTemp581;
			float fRec476 = ((iTemp582) ? fTemp583 : fThen370);
			output52[i0] = FAUSTFLOAT(fRec468[0] * (2.0f * fRec476 + -1.0f));
			fRec483[0] = fTemp0 - fConst755 * (fConst756 * fRec483[1] + fConst757 * fRec483[2]);
			fRec482[0] = fConst754 * fRec483[2] + fConst755 * (fConst751 * fRec483[0] - (fConst756 * fRec482[1] + fConst757 * fRec482[2]));
			fRec481[0] = fConst754 * fRec482[2] + fConst755 * (fConst751 * fRec482[0] - (fConst756 * fRec481[1] + fConst757 * fRec481[2]));
			fRec480[0] = fConst754 * fRec481[2] + fConst755 * (fConst751 * fRec481[0] - (fConst756 * fRec480[1] + fConst757 * fRec480[2]));
			float fTemp584 = fConst754 * fRec480[2];
			float fTemp585 = fConst753 * fRec480[0];
			fVec53[0] = fTemp585 + fTemp584;
			fRec479[0] = (fTemp584 + 0.995000005f * fRec479[1] + fTemp585) - fVec53[1];
			fRec478[IOTA0 & 32767] = fRec478[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec479[0]);
			float fTemp586 = std::sqrt(fSlow1 * (fRec478[IOTA0 & 32767] - fRec478[(IOTA0 - iSlow2) & 32767]));
			int iTemp587 = ((fTemp586 > fSlow3) ? fTemp586 : 0.0f) > 0.0f > 0;
			int iTemp588 = iTemp587;
			float fTemp589 = 0.144717798f * ((iTemp588) ? fSlow5 : fSlow4);
			int iTemp590 = std::fabs(fTemp589) < 1.1920929e-07f;
			float fThen374 = std::exp(0.0f - fConst6 / ((iTemp590) ? 1.0f : fTemp589));
			float fTemp591 = ((iTemp590) ? 0.0f : fThen374);
			float fElse375 = float(iTemp587);
			fRec477[0] = (1.0f - fTemp591) * ((iTemp588) ? fElse375 : 0.0f) + fTemp591 * fRec477[1];
			float fTemp592 = fConst758 + fRec484[1] + -1.0f;
			int iTemp593 = fTemp592 < 0.0f;
			float fTemp594 = fConst758 + fRec484[1];
			fRec484[0] = ((iTemp593) ? fTemp594 : fTemp592);
			float fThen377 = fConst758 + fRec484[1] + fConst759 * fTemp592;
			float fRec485 = ((iTemp593) ? fTemp594 : fThen377);
			output53[i0] = FAUSTFLOAT(fRec477[0] * (2.0f * fRec485 + -1.0f));
			fRec492[0] = fTemp0 - fConst769 * (fConst770 * fRec492[1] + fConst771 * fRec492[2]);
			fRec491[0] = fConst768 * fRec492[2] + fConst769 * (fConst765 * fRec492[0] - (fConst770 * fRec491[1] + fConst771 * fRec491[2]));
			fRec490[0] = fConst768 * fRec491[2] + fConst769 * (fConst765 * fRec491[0] - (fConst770 * fRec490[1] + fConst771 * fRec490[2]));
			fRec489[0] = fConst768 * fRec490[2] + fConst769 * (fConst765 * fRec490[0] - (fConst770 * fRec489[1] + fConst771 * fRec489[2]));
			float fTemp595 = fConst768 * fRec489[2];
			float fTemp596 = fConst767 * fRec489[0];
			fVec54[0] = fTemp596 + fTemp595;
			fRec488[0] = (fTemp595 + 0.995000005f * fRec488[1] + fTemp596) - fVec54[1];
			fRec487[IOTA0 & 32767] = fRec487[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec488[0]);
			float fTemp597 = std::sqrt(fSlow1 * (fRec487[IOTA0 & 32767] - fRec487[(IOTA0 - iSlow2) & 32767]));
			int iTemp598 = ((fTemp597 > fSlow3) ? fTemp597 : 0.0f) > 0.0f > 0;
			int iTemp599 = iTemp598;
			float fTemp600 = 0.144717798f * ((iTemp599) ? fSlow5 : fSlow4);
			int iTemp601 = std::fabs(fTemp600) < 1.1920929e-07f;
			float fThen381 = std::exp(0.0f - fConst6 / ((iTemp601) ? 1.0f : fTemp600));
			float fTemp602 = ((iTemp601) ? 0.0f : fThen381);
			float fElse382 = float(iTemp598);
			fRec486[0] = (1.0f - fTemp602) * ((iTemp599) ? fElse382 : 0.0f) + fTemp602 * fRec486[1];
			float fTemp603 = fConst772 + fRec493[1] + -1.0f;
			int iTemp604 = fTemp603 < 0.0f;
			float fTemp605 = fConst772 + fRec493[1];
			fRec493[0] = ((iTemp604) ? fTemp605 : fTemp603);
			float fThen384 = fConst772 + fRec493[1] + fConst773 * fTemp603;
			float fRec494 = ((iTemp604) ? fTemp605 : fThen384);
			output54[i0] = FAUSTFLOAT(fRec486[0] * (2.0f * fRec494 + -1.0f));
			fRec501[0] = fTemp0 - fConst783 * (fConst784 * fRec501[1] + fConst785 * fRec501[2]);
			fRec500[0] = fConst782 * fRec501[2] + fConst783 * (fConst779 * fRec501[0] - (fConst784 * fRec500[1] + fConst785 * fRec500[2]));
			fRec499[0] = fConst782 * fRec500[2] + fConst783 * (fConst779 * fRec500[0] - (fConst784 * fRec499[1] + fConst785 * fRec499[2]));
			fRec498[0] = fConst782 * fRec499[2] + fConst783 * (fConst779 * fRec499[0] - (fConst784 * fRec498[1] + fConst785 * fRec498[2]));
			float fTemp606 = fConst782 * fRec498[2];
			float fTemp607 = fConst781 * fRec498[0];
			fVec55[0] = fTemp607 + fTemp606;
			fRec497[0] = (fTemp606 + 0.995000005f * fRec497[1] + fTemp607) - fVec55[1];
			fRec496[IOTA0 & 32767] = fRec496[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec497[0]);
			float fTemp608 = std::sqrt(fSlow1 * (fRec496[IOTA0 & 32767] - fRec496[(IOTA0 - iSlow2) & 32767]));
			int iTemp609 = ((fTemp608 > fSlow3) ? fTemp608 : 0.0f) > 0.0f > 0;
			int iTemp610 = iTemp609;
			float fTemp611 = 0.144717798f * ((iTemp610) ? fSlow5 : fSlow4);
			int iTemp612 = std::fabs(fTemp611) < 1.1920929e-07f;
			float fThen388 = std::exp(0.0f - fConst6 / ((iTemp612) ? 1.0f : fTemp611));
			float fTemp613 = ((iTemp612) ? 0.0f : fThen388);
			float fElse389 = float(iTemp609);
			fRec495[0] = (1.0f - fTemp613) * ((iTemp610) ? fElse389 : 0.0f) + fTemp613 * fRec495[1];
			float fTemp614 = fConst786 + fRec502[1] + -1.0f;
			int iTemp615 = fTemp614 < 0.0f;
			float fTemp616 = fConst786 + fRec502[1];
			fRec502[0] = ((iTemp615) ? fTemp616 : fTemp614);
			float fThen391 = fConst786 + fRec502[1] + fConst787 * fTemp614;
			float fRec503 = ((iTemp615) ? fTemp616 : fThen391);
			output55[i0] = FAUSTFLOAT(fRec495[0] * (2.0f * fRec503 + -1.0f));
			fRec510[0] = fTemp0 - fConst797 * (fConst798 * fRec510[1] + fConst799 * fRec510[2]);
			fRec509[0] = fConst796 * fRec510[2] + fConst797 * (fConst793 * fRec510[0] - (fConst798 * fRec509[1] + fConst799 * fRec509[2]));
			fRec508[0] = fConst796 * fRec509[2] + fConst797 * (fConst793 * fRec509[0] - (fConst798 * fRec508[1] + fConst799 * fRec508[2]));
			fRec507[0] = fConst796 * fRec508[2] + fConst797 * (fConst793 * fRec508[0] - (fConst798 * fRec507[1] + fConst799 * fRec507[2]));
			float fTemp617 = fConst796 * fRec507[2];
			float fTemp618 = fConst795 * fRec507[0];
			fVec56[0] = fTemp618 + fTemp617;
			fRec506[0] = (fTemp617 + 0.995000005f * fRec506[1] + fTemp618) - fVec56[1];
			fRec505[IOTA0 & 32767] = fRec505[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec506[0]);
			float fTemp619 = std::sqrt(fSlow1 * (fRec505[IOTA0 & 32767] - fRec505[(IOTA0 - iSlow2) & 32767]));
			int iTemp620 = ((fTemp619 > fSlow3) ? fTemp619 : 0.0f) > 0.0f > 0;
			int iTemp621 = iTemp620;
			float fTemp622 = 0.144717798f * ((iTemp621) ? fSlow5 : fSlow4);
			int iTemp623 = std::fabs(fTemp622) < 1.1920929e-07f;
			float fThen395 = std::exp(0.0f - fConst6 / ((iTemp623) ? 1.0f : fTemp622));
			float fTemp624 = ((iTemp623) ? 0.0f : fThen395);
			float fElse396 = float(iTemp620);
			fRec504[0] = (1.0f - fTemp624) * ((iTemp621) ? fElse396 : 0.0f) + fTemp624 * fRec504[1];
			float fTemp625 = fConst800 + fRec511[1] + -1.0f;
			int iTemp626 = fTemp625 < 0.0f;
			float fTemp627 = fConst800 + fRec511[1];
			fRec511[0] = ((iTemp626) ? fTemp627 : fTemp625);
			float fThen398 = fConst800 + fRec511[1] + fConst801 * fTemp625;
			float fRec512 = ((iTemp626) ? fTemp627 : fThen398);
			output56[i0] = FAUSTFLOAT(fRec504[0] * (2.0f * fRec512 + -1.0f));
			fRec519[0] = fTemp0 - fConst811 * (fConst812 * fRec519[1] + fConst813 * fRec519[2]);
			fRec518[0] = fConst810 * fRec519[2] + fConst811 * (fConst807 * fRec519[0] - (fConst812 * fRec518[1] + fConst813 * fRec518[2]));
			fRec517[0] = fConst810 * fRec518[2] + fConst811 * (fConst807 * fRec518[0] - (fConst812 * fRec517[1] + fConst813 * fRec517[2]));
			fRec516[0] = fConst810 * fRec517[2] + fConst811 * (fConst807 * fRec517[0] - (fConst812 * fRec516[1] + fConst813 * fRec516[2]));
			float fTemp628 = fConst810 * fRec516[2];
			float fTemp629 = fConst809 * fRec516[0];
			fVec57[0] = fTemp629 + fTemp628;
			fRec515[0] = (fTemp628 + 0.995000005f * fRec515[1] + fTemp629) - fVec57[1];
			fRec514[IOTA0 & 32767] = fRec514[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec515[0]);
			float fTemp630 = std::sqrt(fSlow1 * (fRec514[IOTA0 & 32767] - fRec514[(IOTA0 - iSlow2) & 32767]));
			int iTemp631 = ((fTemp630 > fSlow3) ? fTemp630 : 0.0f) > 0.0f > 0;
			int iTemp632 = iTemp631;
			float fTemp633 = 0.144717798f * ((iTemp632) ? fSlow5 : fSlow4);
			int iTemp634 = std::fabs(fTemp633) < 1.1920929e-07f;
			float fThen402 = std::exp(0.0f - fConst6 / ((iTemp634) ? 1.0f : fTemp633));
			float fTemp635 = ((iTemp634) ? 0.0f : fThen402);
			float fElse403 = float(iTemp631);
			fRec513[0] = (1.0f - fTemp635) * ((iTemp632) ? fElse403 : 0.0f) + fTemp635 * fRec513[1];
			float fTemp636 = fConst814 + fRec520[1] + -1.0f;
			int iTemp637 = fTemp636 < 0.0f;
			float fTemp638 = fConst814 + fRec520[1];
			fRec520[0] = ((iTemp637) ? fTemp638 : fTemp636);
			float fThen405 = fConst814 + fRec520[1] + fConst815 * fTemp636;
			float fRec521 = ((iTemp637) ? fTemp638 : fThen405);
			output57[i0] = FAUSTFLOAT(fRec513[0] * (2.0f * fRec521 + -1.0f));
			fRec528[0] = fTemp0 - fConst825 * (fConst826 * fRec528[1] + fConst827 * fRec528[2]);
			fRec527[0] = fConst824 * fRec528[2] + fConst825 * (fConst821 * fRec528[0] - (fConst826 * fRec527[1] + fConst827 * fRec527[2]));
			fRec526[0] = fConst824 * fRec527[2] + fConst825 * (fConst821 * fRec527[0] - (fConst826 * fRec526[1] + fConst827 * fRec526[2]));
			fRec525[0] = fConst824 * fRec526[2] + fConst825 * (fConst821 * fRec526[0] - (fConst826 * fRec525[1] + fConst827 * fRec525[2]));
			float fTemp639 = fConst824 * fRec525[2];
			float fTemp640 = fConst823 * fRec525[0];
			fVec58[0] = fTemp640 + fTemp639;
			fRec524[0] = (fTemp639 + 0.995000005f * fRec524[1] + fTemp640) - fVec58[1];
			fRec523[IOTA0 & 32767] = fRec523[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec524[0]);
			float fTemp641 = std::sqrt(fSlow1 * (fRec523[IOTA0 & 32767] - fRec523[(IOTA0 - iSlow2) & 32767]));
			int iTemp642 = ((fTemp641 > fSlow3) ? fTemp641 : 0.0f) > 0.0f > 0;
			int iTemp643 = iTemp642;
			float fTemp644 = 0.144717798f * ((iTemp643) ? fSlow5 : fSlow4);
			int iTemp645 = std::fabs(fTemp644) < 1.1920929e-07f;
			float fThen409 = std::exp(0.0f - fConst6 / ((iTemp645) ? 1.0f : fTemp644));
			float fTemp646 = ((iTemp645) ? 0.0f : fThen409);
			float fElse410 = float(iTemp642);
			fRec522[0] = (1.0f - fTemp646) * ((iTemp643) ? fElse410 : 0.0f) + fTemp646 * fRec522[1];
			float fTemp647 = fConst828 + fRec529[1] + -1.0f;
			int iTemp648 = fTemp647 < 0.0f;
			float fTemp649 = fConst828 + fRec529[1];
			fRec529[0] = ((iTemp648) ? fTemp649 : fTemp647);
			float fThen412 = fConst828 + fRec529[1] + fConst829 * fTemp647;
			float fRec530 = ((iTemp648) ? fTemp649 : fThen412);
			output58[i0] = FAUSTFLOAT(fRec522[0] * (2.0f * fRec530 + -1.0f));
			fRec537[0] = fTemp0 - fConst839 * (fConst840 * fRec537[1] + fConst841 * fRec537[2]);
			fRec536[0] = fConst838 * fRec537[2] + fConst839 * (fConst835 * fRec537[0] - (fConst840 * fRec536[1] + fConst841 * fRec536[2]));
			fRec535[0] = fConst838 * fRec536[2] + fConst839 * (fConst835 * fRec536[0] - (fConst840 * fRec535[1] + fConst841 * fRec535[2]));
			fRec534[0] = fConst838 * fRec535[2] + fConst839 * (fConst835 * fRec535[0] - (fConst840 * fRec534[1] + fConst841 * fRec534[2]));
			float fTemp650 = fConst838 * fRec534[2];
			float fTemp651 = fConst837 * fRec534[0];
			fVec59[0] = fTemp651 + fTemp650;
			fRec533[0] = (fTemp650 + 0.995000005f * fRec533[1] + fTemp651) - fVec59[1];
			fRec532[IOTA0 & 32767] = fRec532[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec533[0]);
			float fTemp652 = std::sqrt(fSlow1 * (fRec532[IOTA0 & 32767] - fRec532[(IOTA0 - iSlow2) & 32767]));
			int iTemp653 = ((fTemp652 > fSlow3) ? fTemp652 : 0.0f) > 0.0f > 0;
			int iTemp654 = iTemp653;
			float fTemp655 = 0.144717798f * ((iTemp654) ? fSlow5 : fSlow4);
			int iTemp656 = std::fabs(fTemp655) < 1.1920929e-07f;
			float fThen416 = std::exp(0.0f - fConst6 / ((iTemp656) ? 1.0f : fTemp655));
			float fTemp657 = ((iTemp656) ? 0.0f : fThen416);
			float fElse417 = float(iTemp653);
			fRec531[0] = (1.0f - fTemp657) * ((iTemp654) ? fElse417 : 0.0f) + fTemp657 * fRec531[1];
			float fTemp658 = fConst842 + fRec538[1] + -1.0f;
			int iTemp659 = fTemp658 < 0.0f;
			float fTemp660 = fConst842 + fRec538[1];
			fRec538[0] = ((iTemp659) ? fTemp660 : fTemp658);
			float fThen419 = fConst842 + fRec538[1] + fConst843 * fTemp658;
			float fRec539 = ((iTemp659) ? fTemp660 : fThen419);
			output59[i0] = FAUSTFLOAT(fRec531[0] * (2.0f * fRec539 + -1.0f));
			fRec546[0] = fTemp0 - fConst853 * (fConst854 * fRec546[1] + fConst855 * fRec546[2]);
			fRec545[0] = fConst852 * fRec546[2] + fConst853 * (fConst849 * fRec546[0] - (fConst854 * fRec545[1] + fConst855 * fRec545[2]));
			fRec544[0] = fConst852 * fRec545[2] + fConst853 * (fConst849 * fRec545[0] - (fConst854 * fRec544[1] + fConst855 * fRec544[2]));
			fRec543[0] = fConst852 * fRec544[2] + fConst853 * (fConst849 * fRec544[0] - (fConst854 * fRec543[1] + fConst855 * fRec543[2]));
			float fTemp661 = fConst852 * fRec543[2];
			float fTemp662 = fConst851 * fRec543[0];
			fVec60[0] = fTemp662 + fTemp661;
			fRec542[0] = (fTemp661 + 0.995000005f * fRec542[1] + fTemp662) - fVec60[1];
			fRec541[IOTA0 & 32767] = fRec541[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec542[0]);
			float fTemp663 = std::sqrt(fSlow1 * (fRec541[IOTA0 & 32767] - fRec541[(IOTA0 - iSlow2) & 32767]));
			int iTemp664 = ((fTemp663 > fSlow3) ? fTemp663 : 0.0f) > 0.0f > 0;
			int iTemp665 = iTemp664;
			float fTemp666 = 0.144717798f * ((iTemp665) ? fSlow5 : fSlow4);
			int iTemp667 = std::fabs(fTemp666) < 1.1920929e-07f;
			float fThen423 = std::exp(0.0f - fConst6 / ((iTemp667) ? 1.0f : fTemp666));
			float fTemp668 = ((iTemp667) ? 0.0f : fThen423);
			float fElse424 = float(iTemp664);
			fRec540[0] = (1.0f - fTemp668) * ((iTemp665) ? fElse424 : 0.0f) + fTemp668 * fRec540[1];
			float fTemp669 = fConst856 + fRec547[1] + -1.0f;
			int iTemp670 = fTemp669 < 0.0f;
			float fTemp671 = fConst856 + fRec547[1];
			fRec547[0] = ((iTemp670) ? fTemp671 : fTemp669);
			float fThen426 = fConst856 + fRec547[1] + fConst857 * fTemp669;
			float fRec548 = ((iTemp670) ? fTemp671 : fThen426);
			output60[i0] = FAUSTFLOAT(fRec540[0] * (2.0f * fRec548 + -1.0f));
			fRec555[0] = fTemp0 - fConst867 * (fConst868 * fRec555[1] + fConst869 * fRec555[2]);
			fRec554[0] = fConst866 * fRec555[2] + fConst867 * (fConst863 * fRec555[0] - (fConst868 * fRec554[1] + fConst869 * fRec554[2]));
			fRec553[0] = fConst866 * fRec554[2] + fConst867 * (fConst863 * fRec554[0] - (fConst868 * fRec553[1] + fConst869 * fRec553[2]));
			fRec552[0] = fConst866 * fRec553[2] + fConst867 * (fConst863 * fRec553[0] - (fConst868 * fRec552[1] + fConst869 * fRec552[2]));
			float fTemp672 = fConst866 * fRec552[2];
			float fTemp673 = fConst865 * fRec552[0];
			fVec61[0] = fTemp673 + fTemp672;
			fRec551[0] = (fTemp672 + 0.995000005f * fRec551[1] + fTemp673) - fVec61[1];
			fRec550[IOTA0 & 32767] = fRec550[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec551[0]);
			float fTemp674 = std::sqrt(fSlow1 * (fRec550[IOTA0 & 32767] - fRec550[(IOTA0 - iSlow2) & 32767]));
			int iTemp675 = ((fTemp674 > fSlow3) ? fTemp674 : 0.0f) > 0.0f > 0;
			int iTemp676 = iTemp675;
			float fTemp677 = 0.144717798f * ((iTemp676) ? fSlow5 : fSlow4);
			int iTemp678 = std::fabs(fTemp677) < 1.1920929e-07f;
			float fThen430 = std::exp(0.0f - fConst6 / ((iTemp678) ? 1.0f : fTemp677));
			float fTemp679 = ((iTemp678) ? 0.0f : fThen430);
			float fElse431 = float(iTemp675);
			fRec549[0] = (1.0f - fTemp679) * ((iTemp676) ? fElse431 : 0.0f) + fTemp679 * fRec549[1];
			float fTemp680 = fConst870 + fRec556[1] + -1.0f;
			int iTemp681 = fTemp680 < 0.0f;
			float fTemp682 = fConst870 + fRec556[1];
			fRec556[0] = ((iTemp681) ? fTemp682 : fTemp680);
			float fThen433 = fConst870 + fRec556[1] + fConst871 * fTemp680;
			float fRec557 = ((iTemp681) ? fTemp682 : fThen433);
			output61[i0] = FAUSTFLOAT(fRec549[0] * (2.0f * fRec557 + -1.0f));
			fRec564[0] = fTemp0 - fConst881 * (fConst882 * fRec564[1] + fConst883 * fRec564[2]);
			fRec563[0] = fConst880 * fRec564[2] + fConst881 * (fConst877 * fRec564[0] - (fConst882 * fRec563[1] + fConst883 * fRec563[2]));
			fRec562[0] = fConst880 * fRec563[2] + fConst881 * (fConst877 * fRec563[0] - (fConst882 * fRec562[1] + fConst883 * fRec562[2]));
			fRec561[0] = fConst880 * fRec562[2] + fConst881 * (fConst877 * fRec562[0] - (fConst882 * fRec561[1] + fConst883 * fRec561[2]));
			float fTemp683 = fConst880 * fRec561[2];
			float fTemp684 = fConst879 * fRec561[0];
			fVec62[0] = fTemp684 + fTemp683;
			fRec560[0] = (fTemp683 + 0.995000005f * fRec560[1] + fTemp684) - fVec62[1];
			fRec559[IOTA0 & 32767] = fRec559[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec560[0]);
			float fTemp685 = std::sqrt(fSlow1 * (fRec559[IOTA0 & 32767] - fRec559[(IOTA0 - iSlow2) & 32767]));
			int iTemp686 = ((fTemp685 > fSlow3) ? fTemp685 : 0.0f) > 0.0f > 0;
			int iTemp687 = iTemp686;
			float fTemp688 = 0.144717798f * ((iTemp687) ? fSlow5 : fSlow4);
			int iTemp689 = std::fabs(fTemp688) < 1.1920929e-07f;
			float fThen437 = std::exp(0.0f - fConst6 / ((iTemp689) ? 1.0f : fTemp688));
			float fTemp690 = ((iTemp689) ? 0.0f : fThen437);
			float fElse438 = float(iTemp686);
			fRec558[0] = (1.0f - fTemp690) * ((iTemp687) ? fElse438 : 0.0f) + fTemp690 * fRec558[1];
			float fTemp691 = fConst884 + fRec565[1] + -1.0f;
			int iTemp692 = fTemp691 < 0.0f;
			float fTemp693 = fConst884 + fRec565[1];
			fRec565[0] = ((iTemp692) ? fTemp693 : fTemp691);
			float fThen440 = fConst884 + fRec565[1] + fConst885 * fTemp691;
			float fRec566 = ((iTemp692) ? fTemp693 : fThen440);
			output62[i0] = FAUSTFLOAT(fRec558[0] * (2.0f * fRec566 + -1.0f));
			fRec573[0] = fTemp0 - fConst895 * (fConst896 * fRec573[1] + fConst897 * fRec573[2]);
			fRec572[0] = fConst894 * fRec573[2] + fConst895 * (fConst891 * fRec573[0] - (fConst896 * fRec572[1] + fConst897 * fRec572[2]));
			fRec571[0] = fConst894 * fRec572[2] + fConst895 * (fConst891 * fRec572[0] - (fConst896 * fRec571[1] + fConst897 * fRec571[2]));
			fRec570[0] = fConst894 * fRec571[2] + fConst895 * (fConst891 * fRec571[0] - (fConst896 * fRec570[1] + fConst897 * fRec570[2]));
			float fTemp694 = fConst894 * fRec570[2];
			float fTemp695 = fConst893 * fRec570[0];
			fVec63[0] = fTemp695 + fTemp694;
			fRec569[0] = (fTemp694 + 0.995000005f * fRec569[1] + fTemp695) - fVec63[1];
			fRec568[IOTA0 & 32767] = fRec568[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec569[0]);
			float fTemp696 = std::sqrt(fSlow1 * (fRec568[IOTA0 & 32767] - fRec568[(IOTA0 - iSlow2) & 32767]));
			int iTemp697 = ((fTemp696 > fSlow3) ? fTemp696 : 0.0f) > 0.0f > 0;
			int iTemp698 = iTemp697;
			float fTemp699 = 0.144717798f * ((iTemp698) ? fSlow5 : fSlow4);
			int iTemp700 = std::fabs(fTemp699) < 1.1920929e-07f;
			float fThen444 = std::exp(0.0f - fConst6 / ((iTemp700) ? 1.0f : fTemp699));
			float fTemp701 = ((iTemp700) ? 0.0f : fThen444);
			float fElse445 = float(iTemp697);
			fRec567[0] = (1.0f - fTemp701) * ((iTemp698) ? fElse445 : 0.0f) + fTemp701 * fRec567[1];
			float fTemp702 = fConst898 + fRec574[1] + -1.0f;
			int iTemp703 = fTemp702 < 0.0f;
			float fTemp704 = fConst898 + fRec574[1];
			fRec574[0] = ((iTemp703) ? fTemp704 : fTemp702);
			float fThen447 = fConst898 + fRec574[1] + fConst899 * fTemp702;
			float fRec575 = ((iTemp703) ? fTemp704 : fThen447);
			output63[i0] = FAUSTFLOAT(fRec567[0] * (2.0f * fRec575 + -1.0f));
			fRec582[0] = fTemp0 - fConst909 * (fConst910 * fRec582[1] + fConst911 * fRec582[2]);
			fRec581[0] = fConst908 * fRec582[2] + fConst909 * (fConst905 * fRec582[0] - (fConst910 * fRec581[1] + fConst911 * fRec581[2]));
			fRec580[0] = fConst908 * fRec581[2] + fConst909 * (fConst905 * fRec581[0] - (fConst910 * fRec580[1] + fConst911 * fRec580[2]));
			fRec579[0] = fConst908 * fRec580[2] + fConst909 * (fConst905 * fRec580[0] - (fConst910 * fRec579[1] + fConst911 * fRec579[2]));
			float fTemp705 = fConst908 * fRec579[2];
			float fTemp706 = fConst907 * fRec579[0];
			fVec64[0] = fTemp706 + fTemp705;
			fRec578[0] = (fTemp705 + 0.995000005f * fRec578[1] + fTemp706) - fVec64[1];
			fRec577[IOTA0 & 32767] = fRec577[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec578[0]);
			float fTemp707 = std::sqrt(fSlow1 * (fRec577[IOTA0 & 32767] - fRec577[(IOTA0 - iSlow2) & 32767]));
			int iTemp708 = ((fTemp707 > fSlow3) ? fTemp707 : 0.0f) > 0.0f > 0;
			int iTemp709 = iTemp708;
			float fTemp710 = 0.144717798f * ((iTemp709) ? fSlow5 : fSlow4);
			int iTemp711 = std::fabs(fTemp710) < 1.1920929e-07f;
			float fThen451 = std::exp(0.0f - fConst6 / ((iTemp711) ? 1.0f : fTemp710));
			float fTemp712 = ((iTemp711) ? 0.0f : fThen451);
			float fElse452 = float(iTemp708);
			fRec576[0] = (1.0f - fTemp712) * ((iTemp709) ? fElse452 : 0.0f) + fTemp712 * fRec576[1];
			float fTemp713 = fConst912 + fRec583[1] + -1.0f;
			int iTemp714 = fTemp713 < 0.0f;
			float fTemp715 = fConst912 + fRec583[1];
			fRec583[0] = ((iTemp714) ? fTemp715 : fTemp713);
			float fThen454 = fConst912 + fRec583[1] + fConst913 * fTemp713;
			float fRec584 = ((iTemp714) ? fTemp715 : fThen454);
			output64[i0] = FAUSTFLOAT(fRec576[0] * (2.0f * fRec584 + -1.0f));
			fRec591[0] = fTemp0 - fConst923 * (fConst924 * fRec591[1] + fConst925 * fRec591[2]);
			fRec590[0] = fConst922 * fRec591[2] + fConst923 * (fConst919 * fRec591[0] - (fConst924 * fRec590[1] + fConst925 * fRec590[2]));
			fRec589[0] = fConst922 * fRec590[2] + fConst923 * (fConst919 * fRec590[0] - (fConst924 * fRec589[1] + fConst925 * fRec589[2]));
			fRec588[0] = fConst922 * fRec589[2] + fConst923 * (fConst919 * fRec589[0] - (fConst924 * fRec588[1] + fConst925 * fRec588[2]));
			float fTemp716 = fConst922 * fRec588[2];
			float fTemp717 = fConst921 * fRec588[0];
			fVec65[0] = fTemp717 + fTemp716;
			fRec587[0] = (fTemp716 + 0.995000005f * fRec587[1] + fTemp717) - fVec65[1];
			fRec586[IOTA0 & 32767] = fRec586[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec587[0]);
			float fTemp718 = std::sqrt(fSlow1 * (fRec586[IOTA0 & 32767] - fRec586[(IOTA0 - iSlow2) & 32767]));
			int iTemp719 = ((fTemp718 > fSlow3) ? fTemp718 : 0.0f) > 0.0f > 0;
			int iTemp720 = iTemp719;
			float fTemp721 = 0.144717798f * ((iTemp720) ? fSlow5 : fSlow4);
			int iTemp722 = std::fabs(fTemp721) < 1.1920929e-07f;
			float fThen458 = std::exp(0.0f - fConst6 / ((iTemp722) ? 1.0f : fTemp721));
			float fTemp723 = ((iTemp722) ? 0.0f : fThen458);
			float fElse459 = float(iTemp719);
			fRec585[0] = (1.0f - fTemp723) * ((iTemp720) ? fElse459 : 0.0f) + fTemp723 * fRec585[1];
			float fTemp724 = fConst926 + fRec592[1] + -1.0f;
			int iTemp725 = fTemp724 < 0.0f;
			float fTemp726 = fConst926 + fRec592[1];
			fRec592[0] = ((iTemp725) ? fTemp726 : fTemp724);
			float fThen461 = fConst926 + fRec592[1] + fConst927 * fTemp724;
			float fRec593 = ((iTemp725) ? fTemp726 : fThen461);
			output65[i0] = FAUSTFLOAT(fRec585[0] * (2.0f * fRec593 + -1.0f));
			fRec600[0] = fTemp0 - fConst937 * (fConst938 * fRec600[1] + fConst939 * fRec600[2]);
			fRec599[0] = fConst936 * fRec600[2] + fConst937 * (fConst933 * fRec600[0] - (fConst938 * fRec599[1] + fConst939 * fRec599[2]));
			fRec598[0] = fConst936 * fRec599[2] + fConst937 * (fConst933 * fRec599[0] - (fConst938 * fRec598[1] + fConst939 * fRec598[2]));
			fRec597[0] = fConst936 * fRec598[2] + fConst937 * (fConst933 * fRec598[0] - (fConst938 * fRec597[1] + fConst939 * fRec597[2]));
			float fTemp727 = fConst936 * fRec597[2];
			float fTemp728 = fConst935 * fRec597[0];
			fVec66[0] = fTemp728 + fTemp727;
			fRec596[0] = (fTemp727 + 0.995000005f * fRec596[1] + fTemp728) - fVec66[1];
			fRec595[IOTA0 & 32767] = fRec595[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec596[0]);
			float fTemp729 = std::sqrt(fSlow1 * (fRec595[IOTA0 & 32767] - fRec595[(IOTA0 - iSlow2) & 32767]));
			int iTemp730 = ((fTemp729 > fSlow3) ? fTemp729 : 0.0f) > 0.0f > 0;
			int iTemp731 = iTemp730;
			float fTemp732 = 0.144717798f * ((iTemp731) ? fSlow5 : fSlow4);
			int iTemp733 = std::fabs(fTemp732) < 1.1920929e-07f;
			float fThen465 = std::exp(0.0f - fConst6 / ((iTemp733) ? 1.0f : fTemp732));
			float fTemp734 = ((iTemp733) ? 0.0f : fThen465);
			float fElse466 = float(iTemp730);
			fRec594[0] = (1.0f - fTemp734) * ((iTemp731) ? fElse466 : 0.0f) + fTemp734 * fRec594[1];
			float fTemp735 = fConst940 + fRec601[1] + -1.0f;
			int iTemp736 = fTemp735 < 0.0f;
			float fTemp737 = fConst940 + fRec601[1];
			fRec601[0] = ((iTemp736) ? fTemp737 : fTemp735);
			float fThen468 = fConst940 + fRec601[1] + fConst941 * fTemp735;
			float fRec602 = ((iTemp736) ? fTemp737 : fThen468);
			output66[i0] = FAUSTFLOAT(fRec594[0] * (2.0f * fRec602 + -1.0f));
			fRec609[0] = fTemp0 - fConst951 * (fConst952 * fRec609[1] + fConst953 * fRec609[2]);
			fRec608[0] = fConst950 * fRec609[2] + fConst951 * (fConst947 * fRec609[0] - (fConst952 * fRec608[1] + fConst953 * fRec608[2]));
			fRec607[0] = fConst950 * fRec608[2] + fConst951 * (fConst947 * fRec608[0] - (fConst952 * fRec607[1] + fConst953 * fRec607[2]));
			fRec606[0] = fConst950 * fRec607[2] + fConst951 * (fConst947 * fRec607[0] - (fConst952 * fRec606[1] + fConst953 * fRec606[2]));
			float fTemp738 = fConst950 * fRec606[2];
			float fTemp739 = fConst949 * fRec606[0];
			fVec67[0] = fTemp739 + fTemp738;
			fRec605[0] = (fTemp738 + 0.995000005f * fRec605[1] + fTemp739) - fVec67[1];
			fRec604[IOTA0 & 32767] = fRec604[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec605[0]);
			float fTemp740 = std::sqrt(fSlow1 * (fRec604[IOTA0 & 32767] - fRec604[(IOTA0 - iSlow2) & 32767]));
			int iTemp741 = ((fTemp740 > fSlow3) ? fTemp740 : 0.0f) > 0.0f > 0;
			int iTemp742 = iTemp741;
			float fTemp743 = 0.144717798f * ((iTemp742) ? fSlow5 : fSlow4);
			int iTemp744 = std::fabs(fTemp743) < 1.1920929e-07f;
			float fThen472 = std::exp(0.0f - fConst6 / ((iTemp744) ? 1.0f : fTemp743));
			float fTemp745 = ((iTemp744) ? 0.0f : fThen472);
			float fElse473 = float(iTemp741);
			fRec603[0] = (1.0f - fTemp745) * ((iTemp742) ? fElse473 : 0.0f) + fTemp745 * fRec603[1];
			float fTemp746 = fConst954 + fRec610[1] + -1.0f;
			int iTemp747 = fTemp746 < 0.0f;
			float fTemp748 = fConst954 + fRec610[1];
			fRec610[0] = ((iTemp747) ? fTemp748 : fTemp746);
			float fThen475 = fConst954 + fRec610[1] + fConst955 * fTemp746;
			float fRec611 = ((iTemp747) ? fTemp748 : fThen475);
			output67[i0] = FAUSTFLOAT(fRec603[0] * (2.0f * fRec611 + -1.0f));
			fRec618[0] = fTemp0 - fConst965 * (fConst966 * fRec618[1] + fConst967 * fRec618[2]);
			fRec617[0] = fConst964 * fRec618[2] + fConst965 * (fConst961 * fRec618[0] - (fConst966 * fRec617[1] + fConst967 * fRec617[2]));
			fRec616[0] = fConst964 * fRec617[2] + fConst965 * (fConst961 * fRec617[0] - (fConst966 * fRec616[1] + fConst967 * fRec616[2]));
			fRec615[0] = fConst964 * fRec616[2] + fConst965 * (fConst961 * fRec616[0] - (fConst966 * fRec615[1] + fConst967 * fRec615[2]));
			float fTemp749 = fConst964 * fRec615[2];
			float fTemp750 = fConst963 * fRec615[0];
			fVec68[0] = fTemp750 + fTemp749;
			fRec614[0] = (fTemp749 + 0.995000005f * fRec614[1] + fTemp750) - fVec68[1];
			fRec613[IOTA0 & 32767] = fRec613[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec614[0]);
			float fTemp751 = std::sqrt(fSlow1 * (fRec613[IOTA0 & 32767] - fRec613[(IOTA0 - iSlow2) & 32767]));
			int iTemp752 = ((fTemp751 > fSlow3) ? fTemp751 : 0.0f) > 0.0f > 0;
			int iTemp753 = iTemp752;
			float fTemp754 = 0.144717798f * ((iTemp753) ? fSlow5 : fSlow4);
			int iTemp755 = std::fabs(fTemp754) < 1.1920929e-07f;
			float fThen479 = std::exp(0.0f - fConst6 / ((iTemp755) ? 1.0f : fTemp754));
			float fTemp756 = ((iTemp755) ? 0.0f : fThen479);
			float fElse480 = float(iTemp752);
			fRec612[0] = (1.0f - fTemp756) * ((iTemp753) ? fElse480 : 0.0f) + fTemp756 * fRec612[1];
			float fTemp757 = fConst968 + fRec619[1] + -1.0f;
			int iTemp758 = fTemp757 < 0.0f;
			float fTemp759 = fConst968 + fRec619[1];
			fRec619[0] = ((iTemp758) ? fTemp759 : fTemp757);
			float fThen482 = fConst968 + fRec619[1] + fConst969 * fTemp757;
			float fRec620 = ((iTemp758) ? fTemp759 : fThen482);
			output68[i0] = FAUSTFLOAT(fRec612[0] * (2.0f * fRec620 + -1.0f));
			fRec627[0] = fTemp0 - fConst979 * (fConst980 * fRec627[1] + fConst981 * fRec627[2]);
			fRec626[0] = fConst978 * fRec627[2] + fConst979 * (fConst975 * fRec627[0] - (fConst980 * fRec626[1] + fConst981 * fRec626[2]));
			fRec625[0] = fConst978 * fRec626[2] + fConst979 * (fConst975 * fRec626[0] - (fConst980 * fRec625[1] + fConst981 * fRec625[2]));
			fRec624[0] = fConst978 * fRec625[2] + fConst979 * (fConst975 * fRec625[0] - (fConst980 * fRec624[1] + fConst981 * fRec624[2]));
			float fTemp760 = fConst978 * fRec624[2];
			float fTemp761 = fConst977 * fRec624[0];
			fVec69[0] = fTemp761 + fTemp760;
			fRec623[0] = (fTemp760 + 0.995000005f * fRec623[1] + fTemp761) - fVec69[1];
			fRec622[IOTA0 & 32767] = fRec622[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec623[0]);
			float fTemp762 = std::sqrt(fSlow1 * (fRec622[IOTA0 & 32767] - fRec622[(IOTA0 - iSlow2) & 32767]));
			int iTemp763 = ((fTemp762 > fSlow3) ? fTemp762 : 0.0f) > 0.0f > 0;
			int iTemp764 = iTemp763;
			float fTemp765 = 0.144717798f * ((iTemp764) ? fSlow5 : fSlow4);
			int iTemp766 = std::fabs(fTemp765) < 1.1920929e-07f;
			float fThen486 = std::exp(0.0f - fConst6 / ((iTemp766) ? 1.0f : fTemp765));
			float fTemp767 = ((iTemp766) ? 0.0f : fThen486);
			float fElse487 = float(iTemp763);
			fRec621[0] = (1.0f - fTemp767) * ((iTemp764) ? fElse487 : 0.0f) + fTemp767 * fRec621[1];
			float fTemp768 = fConst982 + fRec628[1] + -1.0f;
			int iTemp769 = fTemp768 < 0.0f;
			float fTemp770 = fConst982 + fRec628[1];
			fRec628[0] = ((iTemp769) ? fTemp770 : fTemp768);
			float fThen489 = fConst982 + fRec628[1] + fConst983 * fTemp768;
			float fRec629 = ((iTemp769) ? fTemp770 : fThen489);
			output69[i0] = FAUSTFLOAT(fRec621[0] * (2.0f * fRec629 + -1.0f));
			fRec636[0] = fTemp0 - fConst993 * (fConst994 * fRec636[1] + fConst995 * fRec636[2]);
			fRec635[0] = fConst992 * fRec636[2] + fConst993 * (fConst989 * fRec636[0] - (fConst994 * fRec635[1] + fConst995 * fRec635[2]));
			fRec634[0] = fConst992 * fRec635[2] + fConst993 * (fConst989 * fRec635[0] - (fConst994 * fRec634[1] + fConst995 * fRec634[2]));
			fRec633[0] = fConst992 * fRec634[2] + fConst993 * (fConst989 * fRec634[0] - (fConst994 * fRec633[1] + fConst995 * fRec633[2]));
			float fTemp771 = fConst992 * fRec633[2];
			float fTemp772 = fConst991 * fRec633[0];
			fVec70[0] = fTemp772 + fTemp771;
			fRec632[0] = (fTemp771 + 0.995000005f * fRec632[1] + fTemp772) - fVec70[1];
			fRec631[IOTA0 & 32767] = fRec631[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec632[0]);
			float fTemp773 = std::sqrt(fSlow1 * (fRec631[IOTA0 & 32767] - fRec631[(IOTA0 - iSlow2) & 32767]));
			int iTemp774 = ((fTemp773 > fSlow3) ? fTemp773 : 0.0f) > 0.0f > 0;
			int iTemp775 = iTemp774;
			float fTemp776 = 0.144717798f * ((iTemp775) ? fSlow5 : fSlow4);
			int iTemp777 = std::fabs(fTemp776) < 1.1920929e-07f;
			float fThen493 = std::exp(0.0f - fConst6 / ((iTemp777) ? 1.0f : fTemp776));
			float fTemp778 = ((iTemp777) ? 0.0f : fThen493);
			float fElse494 = float(iTemp774);
			fRec630[0] = (1.0f - fTemp778) * ((iTemp775) ? fElse494 : 0.0f) + fTemp778 * fRec630[1];
			float fTemp779 = fConst996 + fRec637[1] + -1.0f;
			int iTemp780 = fTemp779 < 0.0f;
			float fTemp781 = fConst996 + fRec637[1];
			fRec637[0] = ((iTemp780) ? fTemp781 : fTemp779);
			float fThen496 = fConst996 + fRec637[1] + fConst997 * fTemp779;
			float fRec638 = ((iTemp780) ? fTemp781 : fThen496);
			output70[i0] = FAUSTFLOAT(fRec630[0] * (2.0f * fRec638 + -1.0f));
			fRec645[0] = fTemp0 - fConst1007 * (fConst1008 * fRec645[1] + fConst1009 * fRec645[2]);
			fRec644[0] = fConst1006 * fRec645[2] + fConst1007 * (fConst1003 * fRec645[0] - (fConst1008 * fRec644[1] + fConst1009 * fRec644[2]));
			fRec643[0] = fConst1006 * fRec644[2] + fConst1007 * (fConst1003 * fRec644[0] - (fConst1008 * fRec643[1] + fConst1009 * fRec643[2]));
			fRec642[0] = fConst1006 * fRec643[2] + fConst1007 * (fConst1003 * fRec643[0] - (fConst1008 * fRec642[1] + fConst1009 * fRec642[2]));
			float fTemp782 = fConst1006 * fRec642[2];
			float fTemp783 = fConst1005 * fRec642[0];
			fVec71[0] = fTemp783 + fTemp782;
			fRec641[0] = (fTemp782 + 0.995000005f * fRec641[1] + fTemp783) - fVec71[1];
			fRec640[IOTA0 & 32767] = fRec640[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec641[0]);
			float fTemp784 = std::sqrt(fSlow1 * (fRec640[IOTA0 & 32767] - fRec640[(IOTA0 - iSlow2) & 32767]));
			int iTemp785 = ((fTemp784 > fSlow3) ? fTemp784 : 0.0f) > 0.0f > 0;
			int iTemp786 = iTemp785;
			float fTemp787 = 0.144717798f * ((iTemp786) ? fSlow5 : fSlow4);
			int iTemp788 = std::fabs(fTemp787) < 1.1920929e-07f;
			float fThen500 = std::exp(0.0f - fConst6 / ((iTemp788) ? 1.0f : fTemp787));
			float fTemp789 = ((iTemp788) ? 0.0f : fThen500);
			float fElse501 = float(iTemp785);
			fRec639[0] = (1.0f - fTemp789) * ((iTemp786) ? fElse501 : 0.0f) + fTemp789 * fRec639[1];
			float fTemp790 = fConst1010 + fRec646[1] + -1.0f;
			int iTemp791 = fTemp790 < 0.0f;
			float fTemp792 = fConst1010 + fRec646[1];
			fRec646[0] = ((iTemp791) ? fTemp792 : fTemp790);
			float fThen503 = fConst1010 + fRec646[1] + fConst1011 * fTemp790;
			float fRec647 = ((iTemp791) ? fTemp792 : fThen503);
			output71[i0] = FAUSTFLOAT(fRec639[0] * (2.0f * fRec647 + -1.0f));
			fRec654[0] = fTemp0 - fConst1021 * (fConst1022 * fRec654[1] + fConst1023 * fRec654[2]);
			fRec653[0] = fConst1020 * fRec654[2] + fConst1021 * (fConst1017 * fRec654[0] - (fConst1022 * fRec653[1] + fConst1023 * fRec653[2]));
			fRec652[0] = fConst1020 * fRec653[2] + fConst1021 * (fConst1017 * fRec653[0] - (fConst1022 * fRec652[1] + fConst1023 * fRec652[2]));
			fRec651[0] = fConst1020 * fRec652[2] + fConst1021 * (fConst1017 * fRec652[0] - (fConst1022 * fRec651[1] + fConst1023 * fRec651[2]));
			float fTemp793 = fConst1020 * fRec651[2];
			float fTemp794 = fConst1019 * fRec651[0];
			fVec72[0] = fTemp794 + fTemp793;
			fRec650[0] = (fTemp793 + 0.995000005f * fRec650[1] + fTemp794) - fVec72[1];
			fRec649[IOTA0 & 32767] = fRec649[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec650[0]);
			float fTemp795 = std::sqrt(fSlow1 * (fRec649[IOTA0 & 32767] - fRec649[(IOTA0 - iSlow2) & 32767]));
			int iTemp796 = ((fTemp795 > fSlow3) ? fTemp795 : 0.0f) > 0.0f > 0;
			int iTemp797 = iTemp796;
			float fTemp798 = 0.144717798f * ((iTemp797) ? fSlow5 : fSlow4);
			int iTemp799 = std::fabs(fTemp798) < 1.1920929e-07f;
			float fThen507 = std::exp(0.0f - fConst6 / ((iTemp799) ? 1.0f : fTemp798));
			float fTemp800 = ((iTemp799) ? 0.0f : fThen507);
			float fElse508 = float(iTemp796);
			fRec648[0] = (1.0f - fTemp800) * ((iTemp797) ? fElse508 : 0.0f) + fTemp800 * fRec648[1];
			float fTemp801 = fConst1024 + fRec655[1] + -1.0f;
			int iTemp802 = fTemp801 < 0.0f;
			float fTemp803 = fConst1024 + fRec655[1];
			fRec655[0] = ((iTemp802) ? fTemp803 : fTemp801);
			float fThen510 = fConst1024 + fRec655[1] + fConst1025 * fTemp801;
			float fRec656 = ((iTemp802) ? fTemp803 : fThen510);
			output72[i0] = FAUSTFLOAT(fRec648[0] * (2.0f * fRec656 + -1.0f));
			fRec663[0] = fTemp0 - fConst1035 * (fConst1036 * fRec663[1] + fConst1037 * fRec663[2]);
			fRec662[0] = fConst1034 * fRec663[2] + fConst1035 * (fConst1031 * fRec663[0] - (fConst1036 * fRec662[1] + fConst1037 * fRec662[2]));
			fRec661[0] = fConst1034 * fRec662[2] + fConst1035 * (fConst1031 * fRec662[0] - (fConst1036 * fRec661[1] + fConst1037 * fRec661[2]));
			fRec660[0] = fConst1034 * fRec661[2] + fConst1035 * (fConst1031 * fRec661[0] - (fConst1036 * fRec660[1] + fConst1037 * fRec660[2]));
			float fTemp804 = fConst1034 * fRec660[2];
			float fTemp805 = fConst1033 * fRec660[0];
			fVec73[0] = fTemp805 + fTemp804;
			fRec659[0] = (fTemp804 + 0.995000005f * fRec659[1] + fTemp805) - fVec73[1];
			fRec658[IOTA0 & 32767] = fRec658[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec659[0]);
			float fTemp806 = std::sqrt(fSlow1 * (fRec658[IOTA0 & 32767] - fRec658[(IOTA0 - iSlow2) & 32767]));
			int iTemp807 = ((fTemp806 > fSlow3) ? fTemp806 : 0.0f) > 0.0f > 0;
			int iTemp808 = iTemp807;
			float fTemp809 = 0.144717798f * ((iTemp808) ? fSlow5 : fSlow4);
			int iTemp810 = std::fabs(fTemp809) < 1.1920929e-07f;
			float fThen514 = std::exp(0.0f - fConst6 / ((iTemp810) ? 1.0f : fTemp809));
			float fTemp811 = ((iTemp810) ? 0.0f : fThen514);
			float fElse515 = float(iTemp807);
			fRec657[0] = (1.0f - fTemp811) * ((iTemp808) ? fElse515 : 0.0f) + fTemp811 * fRec657[1];
			float fTemp812 = fConst1038 + fRec664[1] + -1.0f;
			int iTemp813 = fTemp812 < 0.0f;
			float fTemp814 = fConst1038 + fRec664[1];
			fRec664[0] = ((iTemp813) ? fTemp814 : fTemp812);
			float fThen517 = fConst1038 + fRec664[1] + fConst1039 * fTemp812;
			float fRec665 = ((iTemp813) ? fTemp814 : fThen517);
			output73[i0] = FAUSTFLOAT(fRec657[0] * (2.0f * fRec665 + -1.0f));
			fRec672[0] = fTemp0 - fConst1049 * (fConst1050 * fRec672[1] + fConst1051 * fRec672[2]);
			fRec671[0] = fConst1048 * fRec672[2] + fConst1049 * (fConst1045 * fRec672[0] - (fConst1050 * fRec671[1] + fConst1051 * fRec671[2]));
			fRec670[0] = fConst1048 * fRec671[2] + fConst1049 * (fConst1045 * fRec671[0] - (fConst1050 * fRec670[1] + fConst1051 * fRec670[2]));
			fRec669[0] = fConst1048 * fRec670[2] + fConst1049 * (fConst1045 * fRec670[0] - (fConst1050 * fRec669[1] + fConst1051 * fRec669[2]));
			float fTemp815 = fConst1048 * fRec669[2];
			float fTemp816 = fConst1047 * fRec669[0];
			fVec74[0] = fTemp816 + fTemp815;
			fRec668[0] = (fTemp815 + 0.995000005f * fRec668[1] + fTemp816) - fVec74[1];
			fRec667[IOTA0 & 32767] = fRec667[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec668[0]);
			float fTemp817 = std::sqrt(fSlow1 * (fRec667[IOTA0 & 32767] - fRec667[(IOTA0 - iSlow2) & 32767]));
			int iTemp818 = ((fTemp817 > fSlow3) ? fTemp817 : 0.0f) > 0.0f > 0;
			int iTemp819 = iTemp818;
			float fTemp820 = 0.144717798f * ((iTemp819) ? fSlow5 : fSlow4);
			int iTemp821 = std::fabs(fTemp820) < 1.1920929e-07f;
			float fThen521 = std::exp(0.0f - fConst6 / ((iTemp821) ? 1.0f : fTemp820));
			float fTemp822 = ((iTemp821) ? 0.0f : fThen521);
			float fElse522 = float(iTemp818);
			fRec666[0] = (1.0f - fTemp822) * ((iTemp819) ? fElse522 : 0.0f) + fTemp822 * fRec666[1];
			float fTemp823 = fConst1052 + fRec673[1] + -1.0f;
			int iTemp824 = fTemp823 < 0.0f;
			float fTemp825 = fConst1052 + fRec673[1];
			fRec673[0] = ((iTemp824) ? fTemp825 : fTemp823);
			float fThen524 = fConst1052 + fRec673[1] + fConst1053 * fTemp823;
			float fRec674 = ((iTemp824) ? fTemp825 : fThen524);
			output74[i0] = FAUSTFLOAT(fRec666[0] * (2.0f * fRec674 + -1.0f));
			fRec681[0] = fTemp0 - fConst1063 * (fConst1064 * fRec681[1] + fConst1065 * fRec681[2]);
			fRec680[0] = fConst1062 * fRec681[2] + fConst1063 * (fConst1059 * fRec681[0] - (fConst1064 * fRec680[1] + fConst1065 * fRec680[2]));
			fRec679[0] = fConst1062 * fRec680[2] + fConst1063 * (fConst1059 * fRec680[0] - (fConst1064 * fRec679[1] + fConst1065 * fRec679[2]));
			fRec678[0] = fConst1062 * fRec679[2] + fConst1063 * (fConst1059 * fRec679[0] - (fConst1064 * fRec678[1] + fConst1065 * fRec678[2]));
			float fTemp826 = fConst1062 * fRec678[2];
			float fTemp827 = fConst1061 * fRec678[0];
			fVec75[0] = fTemp827 + fTemp826;
			fRec677[0] = (fTemp826 + 0.995000005f * fRec677[1] + fTemp827) - fVec75[1];
			fRec676[IOTA0 & 32767] = fRec676[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec677[0]);
			float fTemp828 = std::sqrt(fSlow1 * (fRec676[IOTA0 & 32767] - fRec676[(IOTA0 - iSlow2) & 32767]));
			int iTemp829 = ((fTemp828 > fSlow3) ? fTemp828 : 0.0f) > 0.0f > 0;
			int iTemp830 = iTemp829;
			float fTemp831 = 0.144717798f * ((iTemp830) ? fSlow5 : fSlow4);
			int iTemp832 = std::fabs(fTemp831) < 1.1920929e-07f;
			float fThen528 = std::exp(0.0f - fConst6 / ((iTemp832) ? 1.0f : fTemp831));
			float fTemp833 = ((iTemp832) ? 0.0f : fThen528);
			float fElse529 = float(iTemp829);
			fRec675[0] = (1.0f - fTemp833) * ((iTemp830) ? fElse529 : 0.0f) + fTemp833 * fRec675[1];
			float fTemp834 = fConst1066 + fRec682[1] + -1.0f;
			int iTemp835 = fTemp834 < 0.0f;
			float fTemp836 = fConst1066 + fRec682[1];
			fRec682[0] = ((iTemp835) ? fTemp836 : fTemp834);
			float fThen531 = fConst1066 + fRec682[1] + fConst1067 * fTemp834;
			float fRec683 = ((iTemp835) ? fTemp836 : fThen531);
			output75[i0] = FAUSTFLOAT(fRec675[0] * (2.0f * fRec683 + -1.0f));
			fRec690[0] = fTemp0 - fConst1077 * (fConst1078 * fRec690[1] + fConst1079 * fRec690[2]);
			fRec689[0] = fConst1076 * fRec690[2] + fConst1077 * (fConst1073 * fRec690[0] - (fConst1078 * fRec689[1] + fConst1079 * fRec689[2]));
			fRec688[0] = fConst1076 * fRec689[2] + fConst1077 * (fConst1073 * fRec689[0] - (fConst1078 * fRec688[1] + fConst1079 * fRec688[2]));
			fRec687[0] = fConst1076 * fRec688[2] + fConst1077 * (fConst1073 * fRec688[0] - (fConst1078 * fRec687[1] + fConst1079 * fRec687[2]));
			float fTemp837 = fConst1076 * fRec687[2];
			float fTemp838 = fConst1075 * fRec687[0];
			fVec76[0] = fTemp838 + fTemp837;
			fRec686[0] = (fTemp837 + 0.995000005f * fRec686[1] + fTemp838) - fVec76[1];
			fRec685[IOTA0 & 32767] = fRec685[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec686[0]);
			float fTemp839 = std::sqrt(fSlow1 * (fRec685[IOTA0 & 32767] - fRec685[(IOTA0 - iSlow2) & 32767]));
			int iTemp840 = ((fTemp839 > fSlow3) ? fTemp839 : 0.0f) > 0.0f > 0;
			int iTemp841 = iTemp840;
			float fTemp842 = 0.144717798f * ((iTemp841) ? fSlow5 : fSlow4);
			int iTemp843 = std::fabs(fTemp842) < 1.1920929e-07f;
			float fThen535 = std::exp(0.0f - fConst6 / ((iTemp843) ? 1.0f : fTemp842));
			float fTemp844 = ((iTemp843) ? 0.0f : fThen535);
			float fElse536 = float(iTemp840);
			fRec684[0] = (1.0f - fTemp844) * ((iTemp841) ? fElse536 : 0.0f) + fTemp844 * fRec684[1];
			float fTemp845 = fConst1080 + fRec691[1] + -1.0f;
			int iTemp846 = fTemp845 < 0.0f;
			float fTemp847 = fConst1080 + fRec691[1];
			fRec691[0] = ((iTemp846) ? fTemp847 : fTemp845);
			float fThen538 = fConst1080 + fRec691[1] + fConst1081 * fTemp845;
			float fRec692 = ((iTemp846) ? fTemp847 : fThen538);
			output76[i0] = FAUSTFLOAT(fRec684[0] * (2.0f * fRec692 + -1.0f));
			fRec699[0] = fTemp0 - fConst1091 * (fConst1092 * fRec699[1] + fConst1093 * fRec699[2]);
			fRec698[0] = fConst1090 * fRec699[2] + fConst1091 * (fConst1087 * fRec699[0] - (fConst1092 * fRec698[1] + fConst1093 * fRec698[2]));
			fRec697[0] = fConst1090 * fRec698[2] + fConst1091 * (fConst1087 * fRec698[0] - (fConst1092 * fRec697[1] + fConst1093 * fRec697[2]));
			fRec696[0] = fConst1090 * fRec697[2] + fConst1091 * (fConst1087 * fRec697[0] - (fConst1092 * fRec696[1] + fConst1093 * fRec696[2]));
			float fTemp848 = fConst1090 * fRec696[2];
			float fTemp849 = fConst1089 * fRec696[0];
			fVec77[0] = fTemp849 + fTemp848;
			fRec695[0] = (fTemp848 + 0.995000005f * fRec695[1] + fTemp849) - fVec77[1];
			fRec694[IOTA0 & 32767] = fRec694[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec695[0]);
			float fTemp850 = std::sqrt(fSlow1 * (fRec694[IOTA0 & 32767] - fRec694[(IOTA0 - iSlow2) & 32767]));
			int iTemp851 = ((fTemp850 > fSlow3) ? fTemp850 : 0.0f) > 0.0f > 0;
			int iTemp852 = iTemp851;
			float fTemp853 = 0.144717798f * ((iTemp852) ? fSlow5 : fSlow4);
			int iTemp854 = std::fabs(fTemp853) < 1.1920929e-07f;
			float fThen542 = std::exp(0.0f - fConst6 / ((iTemp854) ? 1.0f : fTemp853));
			float fTemp855 = ((iTemp854) ? 0.0f : fThen542);
			float fElse543 = float(iTemp851);
			fRec693[0] = (1.0f - fTemp855) * ((iTemp852) ? fElse543 : 0.0f) + fTemp855 * fRec693[1];
			float fTemp856 = fConst1094 + fRec700[1] + -1.0f;
			int iTemp857 = fTemp856 < 0.0f;
			float fTemp858 = fConst1094 + fRec700[1];
			fRec700[0] = ((iTemp857) ? fTemp858 : fTemp856);
			float fThen545 = fConst1094 + fRec700[1] + fConst1095 * fTemp856;
			float fRec701 = ((iTemp857) ? fTemp858 : fThen545);
			output77[i0] = FAUSTFLOAT(fRec693[0] * (2.0f * fRec701 + -1.0f));
			fRec708[0] = fTemp0 - fConst1105 * (fConst1106 * fRec708[1] + fConst1107 * fRec708[2]);
			fRec707[0] = fConst1104 * fRec708[2] + fConst1105 * (fConst1101 * fRec708[0] - (fConst1106 * fRec707[1] + fConst1107 * fRec707[2]));
			fRec706[0] = fConst1104 * fRec707[2] + fConst1105 * (fConst1101 * fRec707[0] - (fConst1106 * fRec706[1] + fConst1107 * fRec706[2]));
			fRec705[0] = fConst1104 * fRec706[2] + fConst1105 * (fConst1101 * fRec706[0] - (fConst1106 * fRec705[1] + fConst1107 * fRec705[2]));
			float fTemp859 = fConst1104 * fRec705[2];
			float fTemp860 = fConst1103 * fRec705[0];
			fVec78[0] = fTemp860 + fTemp859;
			fRec704[0] = (fTemp859 + 0.995000005f * fRec704[1] + fTemp860) - fVec78[1];
			fRec703[IOTA0 & 32767] = fRec703[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec704[0]);
			float fTemp861 = std::sqrt(fSlow1 * (fRec703[IOTA0 & 32767] - fRec703[(IOTA0 - iSlow2) & 32767]));
			int iTemp862 = ((fTemp861 > fSlow3) ? fTemp861 : 0.0f) > 0.0f > 0;
			int iTemp863 = iTemp862;
			float fTemp864 = 0.144717798f * ((iTemp863) ? fSlow5 : fSlow4);
			int iTemp865 = std::fabs(fTemp864) < 1.1920929e-07f;
			float fThen549 = std::exp(0.0f - fConst6 / ((iTemp865) ? 1.0f : fTemp864));
			float fTemp866 = ((iTemp865) ? 0.0f : fThen549);
			float fElse550 = float(iTemp862);
			fRec702[0] = (1.0f - fTemp866) * ((iTemp863) ? fElse550 : 0.0f) + fTemp866 * fRec702[1];
			float fTemp867 = fConst1108 + fRec709[1] + -1.0f;
			int iTemp868 = fTemp867 < 0.0f;
			float fTemp869 = fConst1108 + fRec709[1];
			fRec709[0] = ((iTemp868) ? fTemp869 : fTemp867);
			float fThen552 = fConst1108 + fRec709[1] + fConst1109 * fTemp867;
			float fRec710 = ((iTemp868) ? fTemp869 : fThen552);
			output78[i0] = FAUSTFLOAT(fRec702[0] * (2.0f * fRec710 + -1.0f));
			fRec717[0] = fTemp0 - fConst1119 * (fConst1120 * fRec717[1] + fConst1121 * fRec717[2]);
			fRec716[0] = fConst1118 * fRec717[2] + fConst1119 * (fConst1115 * fRec717[0] - (fConst1120 * fRec716[1] + fConst1121 * fRec716[2]));
			fRec715[0] = fConst1118 * fRec716[2] + fConst1119 * (fConst1115 * fRec716[0] - (fConst1120 * fRec715[1] + fConst1121 * fRec715[2]));
			fRec714[0] = fConst1118 * fRec715[2] + fConst1119 * (fConst1115 * fRec715[0] - (fConst1120 * fRec714[1] + fConst1121 * fRec714[2]));
			float fTemp870 = fConst1118 * fRec714[2];
			float fTemp871 = fConst1117 * fRec714[0];
			fVec79[0] = fTemp871 + fTemp870;
			fRec713[0] = (fTemp870 + 0.995000005f * fRec713[1] + fTemp871) - fVec79[1];
			fRec712[IOTA0 & 32767] = fRec712[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec713[0]);
			float fTemp872 = std::sqrt(fSlow1 * (fRec712[IOTA0 & 32767] - fRec712[(IOTA0 - iSlow2) & 32767]));
			int iTemp873 = ((fTemp872 > fSlow3) ? fTemp872 : 0.0f) > 0.0f > 0;
			int iTemp874 = iTemp873;
			float fTemp875 = 0.144717798f * ((iTemp874) ? fSlow5 : fSlow4);
			int iTemp876 = std::fabs(fTemp875) < 1.1920929e-07f;
			float fThen556 = std::exp(0.0f - fConst6 / ((iTemp876) ? 1.0f : fTemp875));
			float fTemp877 = ((iTemp876) ? 0.0f : fThen556);
			float fElse557 = float(iTemp873);
			fRec711[0] = (1.0f - fTemp877) * ((iTemp874) ? fElse557 : 0.0f) + fTemp877 * fRec711[1];
			float fTemp878 = fConst1122 + fRec718[1] + -1.0f;
			int iTemp879 = fTemp878 < 0.0f;
			float fTemp880 = fConst1122 + fRec718[1];
			fRec718[0] = ((iTemp879) ? fTemp880 : fTemp878);
			float fThen559 = fConst1122 + fRec718[1] + fConst1123 * fTemp878;
			float fRec719 = ((iTemp879) ? fTemp880 : fThen559);
			output79[i0] = FAUSTFLOAT(fRec711[0] * (2.0f * fRec719 + -1.0f));
			fRec726[0] = fTemp0 - fConst1133 * (fConst1134 * fRec726[1] + fConst1135 * fRec726[2]);
			fRec725[0] = fConst1132 * fRec726[2] + fConst1133 * (fConst1129 * fRec726[0] - (fConst1134 * fRec725[1] + fConst1135 * fRec725[2]));
			fRec724[0] = fConst1132 * fRec725[2] + fConst1133 * (fConst1129 * fRec725[0] - (fConst1134 * fRec724[1] + fConst1135 * fRec724[2]));
			fRec723[0] = fConst1132 * fRec724[2] + fConst1133 * (fConst1129 * fRec724[0] - (fConst1134 * fRec723[1] + fConst1135 * fRec723[2]));
			float fTemp881 = fConst1132 * fRec723[2];
			float fTemp882 = fConst1131 * fRec723[0];
			fVec80[0] = fTemp882 + fTemp881;
			fRec722[0] = (fTemp881 + 0.995000005f * fRec722[1] + fTemp882) - fVec80[1];
			fRec721[IOTA0 & 32767] = fRec721[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec722[0]);
			float fTemp883 = std::sqrt(fSlow1 * (fRec721[IOTA0 & 32767] - fRec721[(IOTA0 - iSlow2) & 32767]));
			int iTemp884 = ((fTemp883 > fSlow3) ? fTemp883 : 0.0f) > 0.0f > 0;
			int iTemp885 = iTemp884;
			float fTemp886 = 0.144717798f * ((iTemp885) ? fSlow5 : fSlow4);
			int iTemp887 = std::fabs(fTemp886) < 1.1920929e-07f;
			float fThen563 = std::exp(0.0f - fConst6 / ((iTemp887) ? 1.0f : fTemp886));
			float fTemp888 = ((iTemp887) ? 0.0f : fThen563);
			float fElse564 = float(iTemp884);
			fRec720[0] = (1.0f - fTemp888) * ((iTemp885) ? fElse564 : 0.0f) + fTemp888 * fRec720[1];
			float fTemp889 = fConst1136 + fRec727[1] + -1.0f;
			int iTemp890 = fTemp889 < 0.0f;
			float fTemp891 = fConst1136 + fRec727[1];
			fRec727[0] = ((iTemp890) ? fTemp891 : fTemp889);
			float fThen566 = fConst1136 + fRec727[1] + fConst1137 * fTemp889;
			float fRec728 = ((iTemp890) ? fTemp891 : fThen566);
			output80[i0] = FAUSTFLOAT(fRec720[0] * (2.0f * fRec728 + -1.0f));
			fRec735[0] = fTemp0 - fConst1147 * (fConst1148 * fRec735[1] + fConst1149 * fRec735[2]);
			fRec734[0] = fConst1146 * fRec735[2] + fConst1147 * (fConst1143 * fRec735[0] - (fConst1148 * fRec734[1] + fConst1149 * fRec734[2]));
			fRec733[0] = fConst1146 * fRec734[2] + fConst1147 * (fConst1143 * fRec734[0] - (fConst1148 * fRec733[1] + fConst1149 * fRec733[2]));
			fRec732[0] = fConst1146 * fRec733[2] + fConst1147 * (fConst1143 * fRec733[0] - (fConst1148 * fRec732[1] + fConst1149 * fRec732[2]));
			float fTemp892 = fConst1146 * fRec732[2];
			float fTemp893 = fConst1145 * fRec732[0];
			fVec81[0] = fTemp893 + fTemp892;
			fRec731[0] = (fTemp892 + 0.995000005f * fRec731[1] + fTemp893) - fVec81[1];
			fRec730[IOTA0 & 32767] = fRec730[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec731[0]);
			float fTemp894 = std::sqrt(fSlow1 * (fRec730[IOTA0 & 32767] - fRec730[(IOTA0 - iSlow2) & 32767]));
			int iTemp895 = ((fTemp894 > fSlow3) ? fTemp894 : 0.0f) > 0.0f > 0;
			int iTemp896 = iTemp895;
			float fTemp897 = 0.144717798f * ((iTemp896) ? fSlow5 : fSlow4);
			int iTemp898 = std::fabs(fTemp897) < 1.1920929e-07f;
			float fThen570 = std::exp(0.0f - fConst6 / ((iTemp898) ? 1.0f : fTemp897));
			float fTemp899 = ((iTemp898) ? 0.0f : fThen570);
			float fElse571 = float(iTemp895);
			fRec729[0] = (1.0f - fTemp899) * ((iTemp896) ? fElse571 : 0.0f) + fTemp899 * fRec729[1];
			float fTemp900 = fConst1150 + fRec736[1] + -1.0f;
			int iTemp901 = fTemp900 < 0.0f;
			float fTemp902 = fConst1150 + fRec736[1];
			fRec736[0] = ((iTemp901) ? fTemp902 : fTemp900);
			float fThen573 = fConst1150 + fRec736[1] + fConst1151 * fTemp900;
			float fRec737 = ((iTemp901) ? fTemp902 : fThen573);
			output81[i0] = FAUSTFLOAT(fRec729[0] * (2.0f * fRec737 + -1.0f));
			fRec744[0] = fTemp0 - fConst1161 * (fConst1162 * fRec744[1] + fConst1163 * fRec744[2]);
			fRec743[0] = fConst1160 * fRec744[2] + fConst1161 * (fConst1157 * fRec744[0] - (fConst1162 * fRec743[1] + fConst1163 * fRec743[2]));
			fRec742[0] = fConst1160 * fRec743[2] + fConst1161 * (fConst1157 * fRec743[0] - (fConst1162 * fRec742[1] + fConst1163 * fRec742[2]));
			fRec741[0] = fConst1160 * fRec742[2] + fConst1161 * (fConst1157 * fRec742[0] - (fConst1162 * fRec741[1] + fConst1163 * fRec741[2]));
			float fTemp903 = fConst1160 * fRec741[2];
			float fTemp904 = fConst1159 * fRec741[0];
			fVec82[0] = fTemp904 + fTemp903;
			fRec740[0] = (fTemp903 + 0.995000005f * fRec740[1] + fTemp904) - fVec82[1];
			fRec739[IOTA0 & 32767] = fRec739[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec740[0]);
			float fTemp905 = std::sqrt(fSlow1 * (fRec739[IOTA0 & 32767] - fRec739[(IOTA0 - iSlow2) & 32767]));
			int iTemp906 = ((fTemp905 > fSlow3) ? fTemp905 : 0.0f) > 0.0f > 0;
			int iTemp907 = iTemp906;
			float fTemp908 = 0.144717798f * ((iTemp907) ? fSlow5 : fSlow4);
			int iTemp909 = std::fabs(fTemp908) < 1.1920929e-07f;
			float fThen577 = std::exp(0.0f - fConst6 / ((iTemp909) ? 1.0f : fTemp908));
			float fTemp910 = ((iTemp909) ? 0.0f : fThen577);
			float fElse578 = float(iTemp906);
			fRec738[0] = (1.0f - fTemp910) * ((iTemp907) ? fElse578 : 0.0f) + fTemp910 * fRec738[1];
			float fTemp911 = fConst1164 + fRec745[1] + -1.0f;
			int iTemp912 = fTemp911 < 0.0f;
			float fTemp913 = fConst1164 + fRec745[1];
			fRec745[0] = ((iTemp912) ? fTemp913 : fTemp911);
			float fThen580 = fConst1164 + fRec745[1] + fConst1165 * fTemp911;
			float fRec746 = ((iTemp912) ? fTemp913 : fThen580);
			output82[i0] = FAUSTFLOAT(fRec738[0] * (2.0f * fRec746 + -1.0f));
			fRec753[0] = fTemp0 - fConst1175 * (fConst1176 * fRec753[1] + fConst1177 * fRec753[2]);
			fRec752[0] = fConst1174 * fRec753[2] + fConst1175 * (fConst1171 * fRec753[0] - (fConst1176 * fRec752[1] + fConst1177 * fRec752[2]));
			fRec751[0] = fConst1174 * fRec752[2] + fConst1175 * (fConst1171 * fRec752[0] - (fConst1176 * fRec751[1] + fConst1177 * fRec751[2]));
			fRec750[0] = fConst1174 * fRec751[2] + fConst1175 * (fConst1171 * fRec751[0] - (fConst1176 * fRec750[1] + fConst1177 * fRec750[2]));
			float fTemp914 = fConst1174 * fRec750[2];
			float fTemp915 = fConst1173 * fRec750[0];
			fVec83[0] = fTemp915 + fTemp914;
			fRec749[0] = (fTemp914 + 0.995000005f * fRec749[1] + fTemp915) - fVec83[1];
			fRec748[IOTA0 & 32767] = fRec748[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec749[0]);
			float fTemp916 = std::sqrt(fSlow1 * (fRec748[IOTA0 & 32767] - fRec748[(IOTA0 - iSlow2) & 32767]));
			int iTemp917 = ((fTemp916 > fSlow3) ? fTemp916 : 0.0f) > 0.0f > 0;
			int iTemp918 = iTemp917;
			float fTemp919 = 0.144717798f * ((iTemp918) ? fSlow5 : fSlow4);
			int iTemp920 = std::fabs(fTemp919) < 1.1920929e-07f;
			float fThen584 = std::exp(0.0f - fConst6 / ((iTemp920) ? 1.0f : fTemp919));
			float fTemp921 = ((iTemp920) ? 0.0f : fThen584);
			float fElse585 = float(iTemp917);
			fRec747[0] = (1.0f - fTemp921) * ((iTemp918) ? fElse585 : 0.0f) + fTemp921 * fRec747[1];
			float fTemp922 = fConst1178 + fRec754[1] + -1.0f;
			int iTemp923 = fTemp922 < 0.0f;
			float fTemp924 = fConst1178 + fRec754[1];
			fRec754[0] = ((iTemp923) ? fTemp924 : fTemp922);
			float fThen587 = fConst1178 + fRec754[1] + fConst1179 * fTemp922;
			float fRec755 = ((iTemp923) ? fTemp924 : fThen587);
			output83[i0] = FAUSTFLOAT(fRec747[0] * (2.0f * fRec755 + -1.0f));
			fRec762[0] = fTemp0 - fConst1189 * (fConst1190 * fRec762[1] + fConst1191 * fRec762[2]);
			fRec761[0] = fConst1188 * fRec762[2] + fConst1189 * (fConst1185 * fRec762[0] - (fConst1190 * fRec761[1] + fConst1191 * fRec761[2]));
			fRec760[0] = fConst1188 * fRec761[2] + fConst1189 * (fConst1185 * fRec761[0] - (fConst1190 * fRec760[1] + fConst1191 * fRec760[2]));
			fRec759[0] = fConst1188 * fRec760[2] + fConst1189 * (fConst1185 * fRec760[0] - (fConst1190 * fRec759[1] + fConst1191 * fRec759[2]));
			float fTemp925 = fConst1188 * fRec759[2];
			float fTemp926 = fConst1187 * fRec759[0];
			fVec84[0] = fTemp926 + fTemp925;
			fRec758[0] = (fTemp925 + 0.995000005f * fRec758[1] + fTemp926) - fVec84[1];
			fRec757[IOTA0 & 32767] = fRec757[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec758[0]);
			float fTemp927 = std::sqrt(fSlow1 * (fRec757[IOTA0 & 32767] - fRec757[(IOTA0 - iSlow2) & 32767]));
			int iTemp928 = ((fTemp927 > fSlow3) ? fTemp927 : 0.0f) > 0.0f > 0;
			int iTemp929 = iTemp928;
			float fTemp930 = 0.144717798f * ((iTemp929) ? fSlow5 : fSlow4);
			int iTemp931 = std::fabs(fTemp930) < 1.1920929e-07f;
			float fThen591 = std::exp(0.0f - fConst6 / ((iTemp931) ? 1.0f : fTemp930));
			float fTemp932 = ((iTemp931) ? 0.0f : fThen591);
			float fElse592 = float(iTemp928);
			fRec756[0] = (1.0f - fTemp932) * ((iTemp929) ? fElse592 : 0.0f) + fTemp932 * fRec756[1];
			float fTemp933 = fConst1192 + fRec763[1] + -1.0f;
			int iTemp934 = fTemp933 < 0.0f;
			float fTemp935 = fConst1192 + fRec763[1];
			fRec763[0] = ((iTemp934) ? fTemp935 : fTemp933);
			float fThen594 = fConst1192 + fRec763[1] + fConst1193 * fTemp933;
			float fRec764 = ((iTemp934) ? fTemp935 : fThen594);
			output84[i0] = FAUSTFLOAT(fRec756[0] * (2.0f * fRec764 + -1.0f));
			fRec771[0] = fTemp0 - fConst1203 * (fConst1204 * fRec771[1] + fConst1205 * fRec771[2]);
			fRec770[0] = fConst1202 * fRec771[2] + fConst1203 * (fConst1199 * fRec771[0] - (fConst1204 * fRec770[1] + fConst1205 * fRec770[2]));
			fRec769[0] = fConst1202 * fRec770[2] + fConst1203 * (fConst1199 * fRec770[0] - (fConst1204 * fRec769[1] + fConst1205 * fRec769[2]));
			fRec768[0] = fConst1202 * fRec769[2] + fConst1203 * (fConst1199 * fRec769[0] - (fConst1204 * fRec768[1] + fConst1205 * fRec768[2]));
			float fTemp936 = fConst1202 * fRec768[2];
			float fTemp937 = fConst1201 * fRec768[0];
			fVec85[0] = fTemp937 + fTemp936;
			fRec767[0] = (fTemp936 + 0.995000005f * fRec767[1] + fTemp937) - fVec85[1];
			fRec766[IOTA0 & 32767] = fRec766[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec767[0]);
			float fTemp938 = std::sqrt(fSlow1 * (fRec766[IOTA0 & 32767] - fRec766[(IOTA0 - iSlow2) & 32767]));
			int iTemp939 = ((fTemp938 > fSlow3) ? fTemp938 : 0.0f) > 0.0f > 0;
			int iTemp940 = iTemp939;
			float fTemp941 = 0.144717798f * ((iTemp940) ? fSlow5 : fSlow4);
			int iTemp942 = std::fabs(fTemp941) < 1.1920929e-07f;
			float fThen598 = std::exp(0.0f - fConst6 / ((iTemp942) ? 1.0f : fTemp941));
			float fTemp943 = ((iTemp942) ? 0.0f : fThen598);
			float fElse599 = float(iTemp939);
			fRec765[0] = (1.0f - fTemp943) * ((iTemp940) ? fElse599 : 0.0f) + fTemp943 * fRec765[1];
			float fTemp944 = fConst1206 + fRec772[1] + -1.0f;
			int iTemp945 = fTemp944 < 0.0f;
			float fTemp946 = fConst1206 + fRec772[1];
			fRec772[0] = ((iTemp945) ? fTemp946 : fTemp944);
			float fThen601 = fConst1206 + fRec772[1] + fConst1207 * fTemp944;
			float fRec773 = ((iTemp945) ? fTemp946 : fThen601);
			output85[i0] = FAUSTFLOAT(fRec765[0] * (2.0f * fRec773 + -1.0f));
			fRec780[0] = fTemp0 - fConst1217 * (fConst1218 * fRec780[1] + fConst1219 * fRec780[2]);
			fRec779[0] = fConst1216 * fRec780[2] + fConst1217 * (fConst1213 * fRec780[0] - (fConst1218 * fRec779[1] + fConst1219 * fRec779[2]));
			fRec778[0] = fConst1216 * fRec779[2] + fConst1217 * (fConst1213 * fRec779[0] - (fConst1218 * fRec778[1] + fConst1219 * fRec778[2]));
			fRec777[0] = fConst1216 * fRec778[2] + fConst1217 * (fConst1213 * fRec778[0] - (fConst1218 * fRec777[1] + fConst1219 * fRec777[2]));
			float fTemp947 = fConst1216 * fRec777[2];
			float fTemp948 = fConst1215 * fRec777[0];
			fVec86[0] = fTemp948 + fTemp947;
			fRec776[0] = (fTemp947 + 0.995000005f * fRec776[1] + fTemp948) - fVec86[1];
			fRec775[IOTA0 & 32767] = fRec775[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec776[0]);
			float fTemp949 = std::sqrt(fSlow1 * (fRec775[IOTA0 & 32767] - fRec775[(IOTA0 - iSlow2) & 32767]));
			int iTemp950 = ((fTemp949 > fSlow3) ? fTemp949 : 0.0f) > 0.0f > 0;
			int iTemp951 = iTemp950;
			float fTemp952 = 0.144717798f * ((iTemp951) ? fSlow5 : fSlow4);
			int iTemp953 = std::fabs(fTemp952) < 1.1920929e-07f;
			float fThen605 = std::exp(0.0f - fConst6 / ((iTemp953) ? 1.0f : fTemp952));
			float fTemp954 = ((iTemp953) ? 0.0f : fThen605);
			float fElse606 = float(iTemp950);
			fRec774[0] = (1.0f - fTemp954) * ((iTemp951) ? fElse606 : 0.0f) + fTemp954 * fRec774[1];
			float fTemp955 = fConst1220 + fRec781[1] + -1.0f;
			int iTemp956 = fTemp955 < 0.0f;
			float fTemp957 = fConst1220 + fRec781[1];
			fRec781[0] = ((iTemp956) ? fTemp957 : fTemp955);
			float fThen608 = fConst1220 + fRec781[1] + fConst1221 * fTemp955;
			float fRec782 = ((iTemp956) ? fTemp957 : fThen608);
			output86[i0] = FAUSTFLOAT(fRec774[0] * (2.0f * fRec782 + -1.0f));
			fRec789[0] = fTemp0 - fConst1231 * (fConst1232 * fRec789[1] + fConst1233 * fRec789[2]);
			fRec788[0] = fConst1230 * fRec789[2] + fConst1231 * (fConst1227 * fRec789[0] - (fConst1232 * fRec788[1] + fConst1233 * fRec788[2]));
			fRec787[0] = fConst1230 * fRec788[2] + fConst1231 * (fConst1227 * fRec788[0] - (fConst1232 * fRec787[1] + fConst1233 * fRec787[2]));
			fRec786[0] = fConst1230 * fRec787[2] + fConst1231 * (fConst1227 * fRec787[0] - (fConst1232 * fRec786[1] + fConst1233 * fRec786[2]));
			float fTemp958 = fConst1230 * fRec786[2];
			float fTemp959 = fConst1229 * fRec786[0];
			fVec87[0] = fTemp959 + fTemp958;
			fRec785[0] = (fTemp958 + 0.995000005f * fRec785[1] + fTemp959) - fVec87[1];
			fRec784[IOTA0 & 32767] = fRec784[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec785[0]);
			float fTemp960 = std::sqrt(fSlow1 * (fRec784[IOTA0 & 32767] - fRec784[(IOTA0 - iSlow2) & 32767]));
			int iTemp961 = ((fTemp960 > fSlow3) ? fTemp960 : 0.0f) > 0.0f > 0;
			int iTemp962 = iTemp961;
			float fTemp963 = 0.144717798f * ((iTemp962) ? fSlow5 : fSlow4);
			int iTemp964 = std::fabs(fTemp963) < 1.1920929e-07f;
			float fThen612 = std::exp(0.0f - fConst6 / ((iTemp964) ? 1.0f : fTemp963));
			float fTemp965 = ((iTemp964) ? 0.0f : fThen612);
			float fElse613 = float(iTemp961);
			fRec783[0] = (1.0f - fTemp965) * ((iTemp962) ? fElse613 : 0.0f) + fTemp965 * fRec783[1];
			float fTemp966 = fConst1234 + fRec790[1] + -1.0f;
			int iTemp967 = fTemp966 < 0.0f;
			float fTemp968 = fConst1234 + fRec790[1];
			fRec790[0] = ((iTemp967) ? fTemp968 : fTemp966);
			float fThen615 = fConst1234 + fRec790[1] + fConst1235 * fTemp966;
			float fRec791 = ((iTemp967) ? fTemp968 : fThen615);
			output87[i0] = FAUSTFLOAT(fRec783[0] * (2.0f * fRec791 + -1.0f));
			fRec798[0] = fTemp0 - fConst1245 * (fConst1246 * fRec798[1] + fConst1247 * fRec798[2]);
			fRec797[0] = fConst1244 * fRec798[2] + fConst1245 * (fConst1241 * fRec798[0] - (fConst1246 * fRec797[1] + fConst1247 * fRec797[2]));
			fRec796[0] = fConst1244 * fRec797[2] + fConst1245 * (fConst1241 * fRec797[0] - (fConst1246 * fRec796[1] + fConst1247 * fRec796[2]));
			fRec795[0] = fConst1244 * fRec796[2] + fConst1245 * (fConst1241 * fRec796[0] - (fConst1246 * fRec795[1] + fConst1247 * fRec795[2]));
			float fTemp969 = fConst1244 * fRec795[2];
			float fTemp970 = fConst1243 * fRec795[0];
			fVec88[0] = fTemp970 + fTemp969;
			fRec794[0] = (fTemp969 + 0.995000005f * fRec794[1] + fTemp970) - fVec88[1];
			fRec793[IOTA0 & 32767] = fRec793[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec794[0]);
			float fTemp971 = std::sqrt(fSlow1 * (fRec793[IOTA0 & 32767] - fRec793[(IOTA0 - iSlow2) & 32767]));
			int iTemp972 = ((fTemp971 > fSlow3) ? fTemp971 : 0.0f) > 0.0f > 0;
			int iTemp973 = iTemp972;
			float fTemp974 = 0.144717798f * ((iTemp973) ? fSlow5 : fSlow4);
			int iTemp975 = std::fabs(fTemp974) < 1.1920929e-07f;
			float fThen619 = std::exp(0.0f - fConst6 / ((iTemp975) ? 1.0f : fTemp974));
			float fTemp976 = ((iTemp975) ? 0.0f : fThen619);
			float fElse620 = float(iTemp972);
			fRec792[0] = (1.0f - fTemp976) * ((iTemp973) ? fElse620 : 0.0f) + fTemp976 * fRec792[1];
			float fTemp977 = fConst1248 + fRec799[1] + -1.0f;
			int iTemp978 = fTemp977 < 0.0f;
			float fTemp979 = fConst1248 + fRec799[1];
			fRec799[0] = ((iTemp978) ? fTemp979 : fTemp977);
			float fThen622 = fConst1248 + fRec799[1] + fConst1249 * fTemp977;
			float fRec800 = ((iTemp978) ? fTemp979 : fThen622);
			output88[i0] = FAUSTFLOAT(fRec792[0] * (2.0f * fRec800 + -1.0f));
			fRec807[0] = fTemp0 - fConst1259 * (fConst1260 * fRec807[1] + fConst1261 * fRec807[2]);
			fRec806[0] = fConst1258 * fRec807[2] + fConst1259 * (fConst1255 * fRec807[0] - (fConst1260 * fRec806[1] + fConst1261 * fRec806[2]));
			fRec805[0] = fConst1258 * fRec806[2] + fConst1259 * (fConst1255 * fRec806[0] - (fConst1260 * fRec805[1] + fConst1261 * fRec805[2]));
			fRec804[0] = fConst1258 * fRec805[2] + fConst1259 * (fConst1255 * fRec805[0] - (fConst1260 * fRec804[1] + fConst1261 * fRec804[2]));
			float fTemp980 = fConst1258 * fRec804[2];
			float fTemp981 = fConst1257 * fRec804[0];
			fVec89[0] = fTemp981 + fTemp980;
			fRec803[0] = (fTemp980 + 0.995000005f * fRec803[1] + fTemp981) - fVec89[1];
			fRec802[IOTA0 & 32767] = fRec802[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec803[0]);
			float fTemp982 = std::sqrt(fSlow1 * (fRec802[IOTA0 & 32767] - fRec802[(IOTA0 - iSlow2) & 32767]));
			int iTemp983 = ((fTemp982 > fSlow3) ? fTemp982 : 0.0f) > 0.0f > 0;
			int iTemp984 = iTemp983;
			float fTemp985 = 0.144717798f * ((iTemp984) ? fSlow5 : fSlow4);
			int iTemp986 = std::fabs(fTemp985) < 1.1920929e-07f;
			float fThen626 = std::exp(0.0f - fConst6 / ((iTemp986) ? 1.0f : fTemp985));
			float fTemp987 = ((iTemp986) ? 0.0f : fThen626);
			float fElse627 = float(iTemp983);
			fRec801[0] = (1.0f - fTemp987) * ((iTemp984) ? fElse627 : 0.0f) + fTemp987 * fRec801[1];
			float fTemp988 = fConst1262 + fRec808[1] + -1.0f;
			int iTemp989 = fTemp988 < 0.0f;
			float fTemp990 = fConst1262 + fRec808[1];
			fRec808[0] = ((iTemp989) ? fTemp990 : fTemp988);
			float fThen629 = fConst1262 + fRec808[1] + fConst1263 * fTemp988;
			float fRec809 = ((iTemp989) ? fTemp990 : fThen629);
			output89[i0] = FAUSTFLOAT(fRec801[0] * (2.0f * fRec809 + -1.0f));
			fRec816[0] = fTemp0 - fConst1273 * (fConst1274 * fRec816[1] + fConst1275 * fRec816[2]);
			fRec815[0] = fConst1272 * fRec816[2] + fConst1273 * (fConst1269 * fRec816[0] - (fConst1274 * fRec815[1] + fConst1275 * fRec815[2]));
			fRec814[0] = fConst1272 * fRec815[2] + fConst1273 * (fConst1269 * fRec815[0] - (fConst1274 * fRec814[1] + fConst1275 * fRec814[2]));
			fRec813[0] = fConst1272 * fRec814[2] + fConst1273 * (fConst1269 * fRec814[0] - (fConst1274 * fRec813[1] + fConst1275 * fRec813[2]));
			float fTemp991 = fConst1272 * fRec813[2];
			float fTemp992 = fConst1271 * fRec813[0];
			fVec90[0] = fTemp992 + fTemp991;
			fRec812[0] = (fTemp991 + 0.995000005f * fRec812[1] + fTemp992) - fVec90[1];
			fRec811[IOTA0 & 32767] = fRec811[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec812[0]);
			float fTemp993 = std::sqrt(fSlow1 * (fRec811[IOTA0 & 32767] - fRec811[(IOTA0 - iSlow2) & 32767]));
			int iTemp994 = ((fTemp993 > fSlow3) ? fTemp993 : 0.0f) > 0.0f > 0;
			int iTemp995 = iTemp994;
			float fTemp996 = 0.144717798f * ((iTemp995) ? fSlow5 : fSlow4);
			int iTemp997 = std::fabs(fTemp996) < 1.1920929e-07f;
			float fThen633 = std::exp(0.0f - fConst6 / ((iTemp997) ? 1.0f : fTemp996));
			float fTemp998 = ((iTemp997) ? 0.0f : fThen633);
			float fElse634 = float(iTemp994);
			fRec810[0] = (1.0f - fTemp998) * ((iTemp995) ? fElse634 : 0.0f) + fTemp998 * fRec810[1];
			float fTemp999 = fConst1276 + fRec817[1] + -1.0f;
			int iTemp1000 = fTemp999 < 0.0f;
			float fTemp1001 = fConst1276 + fRec817[1];
			fRec817[0] = ((iTemp1000) ? fTemp1001 : fTemp999);
			float fThen636 = fConst1276 + fRec817[1] + fConst1277 * fTemp999;
			float fRec818 = ((iTemp1000) ? fTemp1001 : fThen636);
			output90[i0] = FAUSTFLOAT(fRec810[0] * (2.0f * fRec818 + -1.0f));
			fRec825[0] = fTemp0 - fConst1287 * (fConst1288 * fRec825[1] + fConst1289 * fRec825[2]);
			fRec824[0] = fConst1286 * fRec825[2] + fConst1287 * (fConst1283 * fRec825[0] - (fConst1288 * fRec824[1] + fConst1289 * fRec824[2]));
			fRec823[0] = fConst1286 * fRec824[2] + fConst1287 * (fConst1283 * fRec824[0] - (fConst1288 * fRec823[1] + fConst1289 * fRec823[2]));
			fRec822[0] = fConst1286 * fRec823[2] + fConst1287 * (fConst1283 * fRec823[0] - (fConst1288 * fRec822[1] + fConst1289 * fRec822[2]));
			float fTemp1002 = fConst1286 * fRec822[2];
			float fTemp1003 = fConst1285 * fRec822[0];
			fVec91[0] = fTemp1003 + fTemp1002;
			fRec821[0] = (fTemp1002 + 0.995000005f * fRec821[1] + fTemp1003) - fVec91[1];
			fRec820[IOTA0 & 32767] = fRec820[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec821[0]);
			float fTemp1004 = std::sqrt(fSlow1 * (fRec820[IOTA0 & 32767] - fRec820[(IOTA0 - iSlow2) & 32767]));
			int iTemp1005 = ((fTemp1004 > fSlow3) ? fTemp1004 : 0.0f) > 0.0f > 0;
			int iTemp1006 = iTemp1005;
			float fTemp1007 = 0.144717798f * ((iTemp1006) ? fSlow5 : fSlow4);
			int iTemp1008 = std::fabs(fTemp1007) < 1.1920929e-07f;
			float fThen640 = std::exp(0.0f - fConst6 / ((iTemp1008) ? 1.0f : fTemp1007));
			float fTemp1009 = ((iTemp1008) ? 0.0f : fThen640);
			float fElse641 = float(iTemp1005);
			fRec819[0] = (1.0f - fTemp1009) * ((iTemp1006) ? fElse641 : 0.0f) + fTemp1009 * fRec819[1];
			float fTemp1010 = fConst1290 + fRec826[1] + -1.0f;
			int iTemp1011 = fTemp1010 < 0.0f;
			float fTemp1012 = fConst1290 + fRec826[1];
			fRec826[0] = ((iTemp1011) ? fTemp1012 : fTemp1010);
			float fThen643 = fConst1290 + fRec826[1] + fConst1291 * fTemp1010;
			float fRec827 = ((iTemp1011) ? fTemp1012 : fThen643);
			output91[i0] = FAUSTFLOAT(fRec819[0] * (2.0f * fRec827 + -1.0f));
			fRec834[0] = fTemp0 - fConst1301 * (fConst1302 * fRec834[1] + fConst1303 * fRec834[2]);
			fRec833[0] = fConst1300 * fRec834[2] + fConst1301 * (fConst1297 * fRec834[0] - (fConst1302 * fRec833[1] + fConst1303 * fRec833[2]));
			fRec832[0] = fConst1300 * fRec833[2] + fConst1301 * (fConst1297 * fRec833[0] - (fConst1302 * fRec832[1] + fConst1303 * fRec832[2]));
			fRec831[0] = fConst1300 * fRec832[2] + fConst1301 * (fConst1297 * fRec832[0] - (fConst1302 * fRec831[1] + fConst1303 * fRec831[2]));
			float fTemp1013 = fConst1300 * fRec831[2];
			float fTemp1014 = fConst1299 * fRec831[0];
			fVec92[0] = fTemp1014 + fTemp1013;
			fRec830[0] = (fTemp1013 + 0.995000005f * fRec830[1] + fTemp1014) - fVec92[1];
			fRec829[IOTA0 & 32767] = fRec829[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec830[0]);
			float fTemp1015 = std::sqrt(fSlow1 * (fRec829[IOTA0 & 32767] - fRec829[(IOTA0 - iSlow2) & 32767]));
			int iTemp1016 = ((fTemp1015 > fSlow3) ? fTemp1015 : 0.0f) > 0.0f > 0;
			int iTemp1017 = iTemp1016;
			float fTemp1018 = 0.144717798f * ((iTemp1017) ? fSlow5 : fSlow4);
			int iTemp1019 = std::fabs(fTemp1018) < 1.1920929e-07f;
			float fThen647 = std::exp(0.0f - fConst6 / ((iTemp1019) ? 1.0f : fTemp1018));
			float fTemp1020 = ((iTemp1019) ? 0.0f : fThen647);
			float fElse648 = float(iTemp1016);
			fRec828[0] = (1.0f - fTemp1020) * ((iTemp1017) ? fElse648 : 0.0f) + fTemp1020 * fRec828[1];
			float fTemp1021 = fConst1304 + fRec835[1] + -1.0f;
			int iTemp1022 = fTemp1021 < 0.0f;
			float fTemp1023 = fConst1304 + fRec835[1];
			fRec835[0] = ((iTemp1022) ? fTemp1023 : fTemp1021);
			float fThen650 = fConst1304 + fRec835[1] + fConst1305 * fTemp1021;
			float fRec836 = ((iTemp1022) ? fTemp1023 : fThen650);
			output92[i0] = FAUSTFLOAT(fRec828[0] * (2.0f * fRec836 + -1.0f));
			fRec843[0] = fTemp0 - fConst1315 * (fConst1316 * fRec843[1] + fConst1317 * fRec843[2]);
			fRec842[0] = fConst1314 * fRec843[2] + fConst1315 * (fConst1311 * fRec843[0] - (fConst1316 * fRec842[1] + fConst1317 * fRec842[2]));
			fRec841[0] = fConst1314 * fRec842[2] + fConst1315 * (fConst1311 * fRec842[0] - (fConst1316 * fRec841[1] + fConst1317 * fRec841[2]));
			fRec840[0] = fConst1314 * fRec841[2] + fConst1315 * (fConst1311 * fRec841[0] - (fConst1316 * fRec840[1] + fConst1317 * fRec840[2]));
			float fTemp1024 = fConst1314 * fRec840[2];
			float fTemp1025 = fConst1313 * fRec840[0];
			fVec93[0] = fTemp1025 + fTemp1024;
			fRec839[0] = (fTemp1024 + 0.995000005f * fRec839[1] + fTemp1025) - fVec93[1];
			fRec838[IOTA0 & 32767] = fRec838[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec839[0]);
			float fTemp1026 = std::sqrt(fSlow1 * (fRec838[IOTA0 & 32767] - fRec838[(IOTA0 - iSlow2) & 32767]));
			int iTemp1027 = ((fTemp1026 > fSlow3) ? fTemp1026 : 0.0f) > 0.0f > 0;
			int iTemp1028 = iTemp1027;
			float fTemp1029 = 0.144717798f * ((iTemp1028) ? fSlow5 : fSlow4);
			int iTemp1030 = std::fabs(fTemp1029) < 1.1920929e-07f;
			float fThen654 = std::exp(0.0f - fConst6 / ((iTemp1030) ? 1.0f : fTemp1029));
			float fTemp1031 = ((iTemp1030) ? 0.0f : fThen654);
			float fElse655 = float(iTemp1027);
			fRec837[0] = (1.0f - fTemp1031) * ((iTemp1028) ? fElse655 : 0.0f) + fTemp1031 * fRec837[1];
			float fTemp1032 = fConst1318 + fRec844[1] + -1.0f;
			int iTemp1033 = fTemp1032 < 0.0f;
			float fTemp1034 = fConst1318 + fRec844[1];
			fRec844[0] = ((iTemp1033) ? fTemp1034 : fTemp1032);
			float fThen657 = fConst1318 + fRec844[1] + fConst1319 * fTemp1032;
			float fRec845 = ((iTemp1033) ? fTemp1034 : fThen657);
			output93[i0] = FAUSTFLOAT(fRec837[0] * (2.0f * fRec845 + -1.0f));
			fRec852[0] = fTemp0 - fConst1329 * (fConst1330 * fRec852[1] + fConst1331 * fRec852[2]);
			fRec851[0] = fConst1328 * fRec852[2] + fConst1329 * (fConst1325 * fRec852[0] - (fConst1330 * fRec851[1] + fConst1331 * fRec851[2]));
			fRec850[0] = fConst1328 * fRec851[2] + fConst1329 * (fConst1325 * fRec851[0] - (fConst1330 * fRec850[1] + fConst1331 * fRec850[2]));
			fRec849[0] = fConst1328 * fRec850[2] + fConst1329 * (fConst1325 * fRec850[0] - (fConst1330 * fRec849[1] + fConst1331 * fRec849[2]));
			float fTemp1035 = fConst1328 * fRec849[2];
			float fTemp1036 = fConst1327 * fRec849[0];
			fVec94[0] = fTemp1036 + fTemp1035;
			fRec848[0] = (fTemp1035 + 0.995000005f * fRec848[1] + fTemp1036) - fVec94[1];
			fRec847[IOTA0 & 32767] = fRec847[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec848[0]);
			float fTemp1037 = std::sqrt(fSlow1 * (fRec847[IOTA0 & 32767] - fRec847[(IOTA0 - iSlow2) & 32767]));
			int iTemp1038 = ((fTemp1037 > fSlow3) ? fTemp1037 : 0.0f) > 0.0f > 0;
			int iTemp1039 = iTemp1038;
			float fTemp1040 = 0.144717798f * ((iTemp1039) ? fSlow5 : fSlow4);
			int iTemp1041 = std::fabs(fTemp1040) < 1.1920929e-07f;
			float fThen661 = std::exp(0.0f - fConst6 / ((iTemp1041) ? 1.0f : fTemp1040));
			float fTemp1042 = ((iTemp1041) ? 0.0f : fThen661);
			float fElse662 = float(iTemp1038);
			fRec846[0] = (1.0f - fTemp1042) * ((iTemp1039) ? fElse662 : 0.0f) + fTemp1042 * fRec846[1];
			float fTemp1043 = fConst1332 + fRec853[1] + -1.0f;
			int iTemp1044 = fTemp1043 < 0.0f;
			float fTemp1045 = fConst1332 + fRec853[1];
			fRec853[0] = ((iTemp1044) ? fTemp1045 : fTemp1043);
			float fThen664 = fConst1332 + fRec853[1] + fConst1333 * fTemp1043;
			float fRec854 = ((iTemp1044) ? fTemp1045 : fThen664);
			output94[i0] = FAUSTFLOAT(fRec846[0] * (2.0f * fRec854 + -1.0f));
			fRec861[0] = fTemp0 - fConst1343 * (fConst1344 * fRec861[1] + fConst1345 * fRec861[2]);
			fRec860[0] = fConst1342 * fRec861[2] + fConst1343 * (fConst1339 * fRec861[0] - (fConst1344 * fRec860[1] + fConst1345 * fRec860[2]));
			fRec859[0] = fConst1342 * fRec860[2] + fConst1343 * (fConst1339 * fRec860[0] - (fConst1344 * fRec859[1] + fConst1345 * fRec859[2]));
			fRec858[0] = fConst1342 * fRec859[2] + fConst1343 * (fConst1339 * fRec859[0] - (fConst1344 * fRec858[1] + fConst1345 * fRec858[2]));
			float fTemp1046 = fConst1342 * fRec858[2];
			float fTemp1047 = fConst1341 * fRec858[0];
			fVec95[0] = fTemp1047 + fTemp1046;
			fRec857[0] = (fTemp1046 + 0.995000005f * fRec857[1] + fTemp1047) - fVec95[1];
			fRec856[IOTA0 & 32767] = fRec856[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec857[0]);
			float fTemp1048 = std::sqrt(fSlow1 * (fRec856[IOTA0 & 32767] - fRec856[(IOTA0 - iSlow2) & 32767]));
			int iTemp1049 = ((fTemp1048 > fSlow3) ? fTemp1048 : 0.0f) > 0.0f > 0;
			int iTemp1050 = iTemp1049;
			float fTemp1051 = 0.144717798f * ((iTemp1050) ? fSlow5 : fSlow4);
			int iTemp1052 = std::fabs(fTemp1051) < 1.1920929e-07f;
			float fThen668 = std::exp(0.0f - fConst6 / ((iTemp1052) ? 1.0f : fTemp1051));
			float fTemp1053 = ((iTemp1052) ? 0.0f : fThen668);
			float fElse669 = float(iTemp1049);
			fRec855[0] = (1.0f - fTemp1053) * ((iTemp1050) ? fElse669 : 0.0f) + fTemp1053 * fRec855[1];
			float fTemp1054 = fConst1346 + fRec862[1] + -1.0f;
			int iTemp1055 = fTemp1054 < 0.0f;
			float fTemp1056 = fConst1346 + fRec862[1];
			fRec862[0] = ((iTemp1055) ? fTemp1056 : fTemp1054);
			float fThen671 = fConst1346 + fRec862[1] + fConst1347 * fTemp1054;
			float fRec863 = ((iTemp1055) ? fTemp1056 : fThen671);
			output95[i0] = FAUSTFLOAT(fRec855[0] * (2.0f * fRec863 + -1.0f));
			fRec870[0] = fTemp0 - fConst1357 * (fConst1358 * fRec870[1] + fConst1359 * fRec870[2]);
			fRec869[0] = fConst1356 * fRec870[2] + fConst1357 * (fConst1353 * fRec870[0] - (fConst1358 * fRec869[1] + fConst1359 * fRec869[2]));
			fRec868[0] = fConst1356 * fRec869[2] + fConst1357 * (fConst1353 * fRec869[0] - (fConst1358 * fRec868[1] + fConst1359 * fRec868[2]));
			fRec867[0] = fConst1356 * fRec868[2] + fConst1357 * (fConst1353 * fRec868[0] - (fConst1358 * fRec867[1] + fConst1359 * fRec867[2]));
			float fTemp1057 = fConst1356 * fRec867[2];
			float fTemp1058 = fConst1355 * fRec867[0];
			fVec96[0] = fTemp1058 + fTemp1057;
			fRec866[0] = (fTemp1057 + 0.995000005f * fRec866[1] + fTemp1058) - fVec96[1];
			fRec865[IOTA0 & 32767] = fRec865[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec866[0]);
			float fTemp1059 = std::sqrt(fSlow1 * (fRec865[IOTA0 & 32767] - fRec865[(IOTA0 - iSlow2) & 32767]));
			int iTemp1060 = ((fTemp1059 > fSlow3) ? fTemp1059 : 0.0f) > 0.0f > 0;
			int iTemp1061 = iTemp1060;
			float fTemp1062 = 0.144717798f * ((iTemp1061) ? fSlow5 : fSlow4);
			int iTemp1063 = std::fabs(fTemp1062) < 1.1920929e-07f;
			float fThen675 = std::exp(0.0f - fConst6 / ((iTemp1063) ? 1.0f : fTemp1062));
			float fTemp1064 = ((iTemp1063) ? 0.0f : fThen675);
			float fElse676 = float(iTemp1060);
			fRec864[0] = (1.0f - fTemp1064) * ((iTemp1061) ? fElse676 : 0.0f) + fTemp1064 * fRec864[1];
			float fTemp1065 = fConst1360 + fRec871[1] + -1.0f;
			int iTemp1066 = fTemp1065 < 0.0f;
			float fTemp1067 = fConst1360 + fRec871[1];
			fRec871[0] = ((iTemp1066) ? fTemp1067 : fTemp1065);
			float fThen678 = fConst1360 + fRec871[1] + fConst1361 * fTemp1065;
			float fRec872 = ((iTemp1066) ? fTemp1067 : fThen678);
			output96[i0] = FAUSTFLOAT(fRec864[0] * (2.0f * fRec872 + -1.0f));
			fRec879[0] = fTemp0 - fConst1371 * (fConst1372 * fRec879[1] + fConst1373 * fRec879[2]);
			fRec878[0] = fConst1370 * fRec879[2] + fConst1371 * (fConst1367 * fRec879[0] - (fConst1372 * fRec878[1] + fConst1373 * fRec878[2]));
			fRec877[0] = fConst1370 * fRec878[2] + fConst1371 * (fConst1367 * fRec878[0] - (fConst1372 * fRec877[1] + fConst1373 * fRec877[2]));
			fRec876[0] = fConst1370 * fRec877[2] + fConst1371 * (fConst1367 * fRec877[0] - (fConst1372 * fRec876[1] + fConst1373 * fRec876[2]));
			float fTemp1068 = fConst1370 * fRec876[2];
			float fTemp1069 = fConst1369 * fRec876[0];
			fVec97[0] = fTemp1069 + fTemp1068;
			fRec875[0] = (fTemp1068 + 0.995000005f * fRec875[1] + fTemp1069) - fVec97[1];
			fRec874[IOTA0 & 32767] = fRec874[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec875[0]);
			float fTemp1070 = std::sqrt(fSlow1 * (fRec874[IOTA0 & 32767] - fRec874[(IOTA0 - iSlow2) & 32767]));
			int iTemp1071 = ((fTemp1070 > fSlow3) ? fTemp1070 : 0.0f) > 0.0f > 0;
			int iTemp1072 = iTemp1071;
			float fTemp1073 = 0.144717798f * ((iTemp1072) ? fSlow5 : fSlow4);
			int iTemp1074 = std::fabs(fTemp1073) < 1.1920929e-07f;
			float fThen682 = std::exp(0.0f - fConst6 / ((iTemp1074) ? 1.0f : fTemp1073));
			float fTemp1075 = ((iTemp1074) ? 0.0f : fThen682);
			float fElse683 = float(iTemp1071);
			fRec873[0] = (1.0f - fTemp1075) * ((iTemp1072) ? fElse683 : 0.0f) + fTemp1075 * fRec873[1];
			float fTemp1076 = fConst1374 + fRec880[1] + -1.0f;
			int iTemp1077 = fTemp1076 < 0.0f;
			float fTemp1078 = fConst1374 + fRec880[1];
			fRec880[0] = ((iTemp1077) ? fTemp1078 : fTemp1076);
			float fThen685 = fConst1374 + fRec880[1] + fConst1375 * fTemp1076;
			float fRec881 = ((iTemp1077) ? fTemp1078 : fThen685);
			output97[i0] = FAUSTFLOAT(fRec873[0] * (2.0f * fRec881 + -1.0f));
			fRec888[0] = fTemp0 - fConst1385 * (fConst1386 * fRec888[1] + fConst1387 * fRec888[2]);
			fRec887[0] = fConst1384 * fRec888[2] + fConst1385 * (fConst1381 * fRec888[0] - (fConst1386 * fRec887[1] + fConst1387 * fRec887[2]));
			fRec886[0] = fConst1384 * fRec887[2] + fConst1385 * (fConst1381 * fRec887[0] - (fConst1386 * fRec886[1] + fConst1387 * fRec886[2]));
			fRec885[0] = fConst1384 * fRec886[2] + fConst1385 * (fConst1381 * fRec886[0] - (fConst1386 * fRec885[1] + fConst1387 * fRec885[2]));
			float fTemp1079 = fConst1384 * fRec885[2];
			float fTemp1080 = fConst1383 * fRec885[0];
			fVec98[0] = fTemp1080 + fTemp1079;
			fRec884[0] = (fTemp1079 + 0.995000005f * fRec884[1] + fTemp1080) - fVec98[1];
			fRec883[IOTA0 & 32767] = fRec883[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec884[0]);
			float fTemp1081 = std::sqrt(fSlow1 * (fRec883[IOTA0 & 32767] - fRec883[(IOTA0 - iSlow2) & 32767]));
			int iTemp1082 = ((fTemp1081 > fSlow3) ? fTemp1081 : 0.0f) > 0.0f > 0;
			int iTemp1083 = iTemp1082;
			float fTemp1084 = 0.144717798f * ((iTemp1083) ? fSlow5 : fSlow4);
			int iTemp1085 = std::fabs(fTemp1084) < 1.1920929e-07f;
			float fThen689 = std::exp(0.0f - fConst6 / ((iTemp1085) ? 1.0f : fTemp1084));
			float fTemp1086 = ((iTemp1085) ? 0.0f : fThen689);
			float fElse690 = float(iTemp1082);
			fRec882[0] = (1.0f - fTemp1086) * ((iTemp1083) ? fElse690 : 0.0f) + fTemp1086 * fRec882[1];
			float fTemp1087 = fConst1388 + fRec889[1] + -1.0f;
			int iTemp1088 = fTemp1087 < 0.0f;
			float fTemp1089 = fConst1388 + fRec889[1];
			fRec889[0] = ((iTemp1088) ? fTemp1089 : fTemp1087);
			float fThen692 = fConst1388 + fRec889[1] + fConst1389 * fTemp1087;
			float fRec890 = ((iTemp1088) ? fTemp1089 : fThen692);
			output98[i0] = FAUSTFLOAT(fRec882[0] * (2.0f * fRec890 + -1.0f));
			fRec897[0] = fTemp0 - fConst1399 * (fConst1400 * fRec897[1] + fConst1401 * fRec897[2]);
			fRec896[0] = fConst1398 * fRec897[2] + fConst1399 * (fConst1395 * fRec897[0] - (fConst1400 * fRec896[1] + fConst1401 * fRec896[2]));
			fRec895[0] = fConst1398 * fRec896[2] + fConst1399 * (fConst1395 * fRec896[0] - (fConst1400 * fRec895[1] + fConst1401 * fRec895[2]));
			fRec894[0] = fConst1398 * fRec895[2] + fConst1399 * (fConst1395 * fRec895[0] - (fConst1400 * fRec894[1] + fConst1401 * fRec894[2]));
			float fTemp1090 = fConst1398 * fRec894[2];
			float fTemp1091 = fConst1397 * fRec894[0];
			fVec99[0] = fTemp1091 + fTemp1090;
			fRec893[0] = (fTemp1090 + 0.995000005f * fRec893[1] + fTemp1091) - fVec99[1];
			fRec892[IOTA0 & 32767] = fRec892[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec893[0]);
			float fTemp1092 = std::sqrt(fSlow1 * (fRec892[IOTA0 & 32767] - fRec892[(IOTA0 - iSlow2) & 32767]));
			int iTemp1093 = ((fTemp1092 > fSlow3) ? fTemp1092 : 0.0f) > 0.0f > 0;
			int iTemp1094 = iTemp1093;
			float fTemp1095 = 0.144717798f * ((iTemp1094) ? fSlow5 : fSlow4);
			int iTemp1096 = std::fabs(fTemp1095) < 1.1920929e-07f;
			float fThen696 = std::exp(0.0f - fConst6 / ((iTemp1096) ? 1.0f : fTemp1095));
			float fTemp1097 = ((iTemp1096) ? 0.0f : fThen696);
			float fElse697 = float(iTemp1093);
			fRec891[0] = (1.0f - fTemp1097) * ((iTemp1094) ? fElse697 : 0.0f) + fTemp1097 * fRec891[1];
			float fTemp1098 = fConst1402 + fRec898[1] + -1.0f;
			int iTemp1099 = fTemp1098 < 0.0f;
			float fTemp1100 = fConst1402 + fRec898[1];
			fRec898[0] = ((iTemp1099) ? fTemp1100 : fTemp1098);
			float fThen699 = fConst1402 + fRec898[1] + fConst1403 * fTemp1098;
			float fRec899 = ((iTemp1099) ? fTemp1100 : fThen699);
			output99[i0] = FAUSTFLOAT(fRec891[0] * (2.0f * fRec899 + -1.0f));
			fRec906[0] = fTemp0 - fConst1413 * (fConst1414 * fRec906[1] + fConst1415 * fRec906[2]);
			fRec905[0] = fConst1412 * fRec906[2] + fConst1413 * (fConst1409 * fRec906[0] - (fConst1414 * fRec905[1] + fConst1415 * fRec905[2]));
			fRec904[0] = fConst1412 * fRec905[2] + fConst1413 * (fConst1409 * fRec905[0] - (fConst1414 * fRec904[1] + fConst1415 * fRec904[2]));
			fRec903[0] = fConst1412 * fRec904[2] + fConst1413 * (fConst1409 * fRec904[0] - (fConst1414 * fRec903[1] + fConst1415 * fRec903[2]));
			float fTemp1101 = fConst1412 * fRec903[2];
			float fTemp1102 = fConst1411 * fRec903[0];
			fVec100[0] = fTemp1102 + fTemp1101;
			fRec902[0] = (fTemp1101 + 0.995000005f * fRec902[1] + fTemp1102) - fVec100[1];
			fRec901[IOTA0 & 32767] = fRec901[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec902[0]);
			float fTemp1103 = std::sqrt(fSlow1 * (fRec901[IOTA0 & 32767] - fRec901[(IOTA0 - iSlow2) & 32767]));
			int iTemp1104 = ((fTemp1103 > fSlow3) ? fTemp1103 : 0.0f) > 0.0f > 0;
			int iTemp1105 = iTemp1104;
			float fTemp1106 = 0.144717798f * ((iTemp1105) ? fSlow5 : fSlow4);
			int iTemp1107 = std::fabs(fTemp1106) < 1.1920929e-07f;
			float fThen703 = std::exp(0.0f - fConst6 / ((iTemp1107) ? 1.0f : fTemp1106));
			float fTemp1108 = ((iTemp1107) ? 0.0f : fThen703);
			float fElse704 = float(iTemp1104);
			fRec900[0] = (1.0f - fTemp1108) * ((iTemp1105) ? fElse704 : 0.0f) + fTemp1108 * fRec900[1];
			float fTemp1109 = fConst1416 + fRec907[1] + -1.0f;
			int iTemp1110 = fTemp1109 < 0.0f;
			float fTemp1111 = fConst1416 + fRec907[1];
			fRec907[0] = ((iTemp1110) ? fTemp1111 : fTemp1109);
			float fThen706 = fConst1416 + fRec907[1] + fConst1417 * fTemp1109;
			float fRec908 = ((iTemp1110) ? fTemp1111 : fThen706);
			output100[i0] = FAUSTFLOAT(fRec900[0] * (2.0f * fRec908 + -1.0f));
			fRec915[0] = fTemp0 - fConst1427 * (fConst1428 * fRec915[1] + fConst1429 * fRec915[2]);
			fRec914[0] = fConst1426 * fRec915[2] + fConst1427 * (fConst1423 * fRec915[0] - (fConst1428 * fRec914[1] + fConst1429 * fRec914[2]));
			fRec913[0] = fConst1426 * fRec914[2] + fConst1427 * (fConst1423 * fRec914[0] - (fConst1428 * fRec913[1] + fConst1429 * fRec913[2]));
			fRec912[0] = fConst1426 * fRec913[2] + fConst1427 * (fConst1423 * fRec913[0] - (fConst1428 * fRec912[1] + fConst1429 * fRec912[2]));
			float fTemp1112 = fConst1426 * fRec912[2];
			float fTemp1113 = fConst1425 * fRec912[0];
			fVec101[0] = fTemp1113 + fTemp1112;
			fRec911[0] = (fTemp1112 + 0.995000005f * fRec911[1] + fTemp1113) - fVec101[1];
			fRec910[IOTA0 & 32767] = fRec910[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec911[0]);
			float fTemp1114 = std::sqrt(fSlow1 * (fRec910[IOTA0 & 32767] - fRec910[(IOTA0 - iSlow2) & 32767]));
			int iTemp1115 = ((fTemp1114 > fSlow3) ? fTemp1114 : 0.0f) > 0.0f > 0;
			int iTemp1116 = iTemp1115;
			float fTemp1117 = 0.144717798f * ((iTemp1116) ? fSlow5 : fSlow4);
			int iTemp1118 = std::fabs(fTemp1117) < 1.1920929e-07f;
			float fThen710 = std::exp(0.0f - fConst6 / ((iTemp1118) ? 1.0f : fTemp1117));
			float fTemp1119 = ((iTemp1118) ? 0.0f : fThen710);
			float fElse711 = float(iTemp1115);
			fRec909[0] = (1.0f - fTemp1119) * ((iTemp1116) ? fElse711 : 0.0f) + fTemp1119 * fRec909[1];
			float fTemp1120 = fConst1430 + fRec916[1] + -1.0f;
			int iTemp1121 = fTemp1120 < 0.0f;
			float fTemp1122 = fConst1430 + fRec916[1];
			fRec916[0] = ((iTemp1121) ? fTemp1122 : fTemp1120);
			float fThen713 = fConst1430 + fRec916[1] + fConst1431 * fTemp1120;
			float fRec917 = ((iTemp1121) ? fTemp1122 : fThen713);
			output101[i0] = FAUSTFLOAT(fRec909[0] * (2.0f * fRec917 + -1.0f));
			fRec924[0] = fTemp0 - fConst1441 * (fConst1442 * fRec924[1] + fConst1443 * fRec924[2]);
			fRec923[0] = fConst1440 * fRec924[2] + fConst1441 * (fConst1437 * fRec924[0] - (fConst1442 * fRec923[1] + fConst1443 * fRec923[2]));
			fRec922[0] = fConst1440 * fRec923[2] + fConst1441 * (fConst1437 * fRec923[0] - (fConst1442 * fRec922[1] + fConst1443 * fRec922[2]));
			fRec921[0] = fConst1440 * fRec922[2] + fConst1441 * (fConst1437 * fRec922[0] - (fConst1442 * fRec921[1] + fConst1443 * fRec921[2]));
			float fTemp1123 = fConst1440 * fRec921[2];
			float fTemp1124 = fConst1439 * fRec921[0];
			fVec102[0] = fTemp1124 + fTemp1123;
			fRec920[0] = (fTemp1123 + 0.995000005f * fRec920[1] + fTemp1124) - fVec102[1];
			fRec919[IOTA0 & 32767] = fRec919[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec920[0]);
			float fTemp1125 = std::sqrt(fSlow1 * (fRec919[IOTA0 & 32767] - fRec919[(IOTA0 - iSlow2) & 32767]));
			int iTemp1126 = ((fTemp1125 > fSlow3) ? fTemp1125 : 0.0f) > 0.0f > 0;
			int iTemp1127 = iTemp1126;
			float fTemp1128 = 0.144717798f * ((iTemp1127) ? fSlow5 : fSlow4);
			int iTemp1129 = std::fabs(fTemp1128) < 1.1920929e-07f;
			float fThen717 = std::exp(0.0f - fConst6 / ((iTemp1129) ? 1.0f : fTemp1128));
			float fTemp1130 = ((iTemp1129) ? 0.0f : fThen717);
			float fElse718 = float(iTemp1126);
			fRec918[0] = (1.0f - fTemp1130) * ((iTemp1127) ? fElse718 : 0.0f) + fTemp1130 * fRec918[1];
			float fTemp1131 = fConst1444 + fRec925[1] + -1.0f;
			int iTemp1132 = fTemp1131 < 0.0f;
			float fTemp1133 = fConst1444 + fRec925[1];
			fRec925[0] = ((iTemp1132) ? fTemp1133 : fTemp1131);
			float fThen720 = fConst1444 + fRec925[1] + fConst1445 * fTemp1131;
			float fRec926 = ((iTemp1132) ? fTemp1133 : fThen720);
			output102[i0] = FAUSTFLOAT(fRec918[0] * (2.0f * fRec926 + -1.0f));
			fRec933[0] = fTemp0 - fConst1455 * (fConst1456 * fRec933[1] + fConst1457 * fRec933[2]);
			fRec932[0] = fConst1454 * fRec933[2] + fConst1455 * (fConst1451 * fRec933[0] - (fConst1456 * fRec932[1] + fConst1457 * fRec932[2]));
			fRec931[0] = fConst1454 * fRec932[2] + fConst1455 * (fConst1451 * fRec932[0] - (fConst1456 * fRec931[1] + fConst1457 * fRec931[2]));
			fRec930[0] = fConst1454 * fRec931[2] + fConst1455 * (fConst1451 * fRec931[0] - (fConst1456 * fRec930[1] + fConst1457 * fRec930[2]));
			float fTemp1134 = fConst1454 * fRec930[2];
			float fTemp1135 = fConst1453 * fRec930[0];
			fVec103[0] = fTemp1135 + fTemp1134;
			fRec929[0] = (fTemp1134 + 0.995000005f * fRec929[1] + fTemp1135) - fVec103[1];
			fRec928[IOTA0 & 32767] = fRec928[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec929[0]);
			float fTemp1136 = std::sqrt(fSlow1 * (fRec928[IOTA0 & 32767] - fRec928[(IOTA0 - iSlow2) & 32767]));
			int iTemp1137 = ((fTemp1136 > fSlow3) ? fTemp1136 : 0.0f) > 0.0f > 0;
			int iTemp1138 = iTemp1137;
			float fTemp1139 = 0.144717798f * ((iTemp1138) ? fSlow5 : fSlow4);
			int iTemp1140 = std::fabs(fTemp1139) < 1.1920929e-07f;
			float fThen724 = std::exp(0.0f - fConst6 / ((iTemp1140) ? 1.0f : fTemp1139));
			float fTemp1141 = ((iTemp1140) ? 0.0f : fThen724);
			float fElse725 = float(iTemp1137);
			fRec927[0] = (1.0f - fTemp1141) * ((iTemp1138) ? fElse725 : 0.0f) + fTemp1141 * fRec927[1];
			float fTemp1142 = fConst1458 + fRec934[1] + -1.0f;
			int iTemp1143 = fTemp1142 < 0.0f;
			float fTemp1144 = fConst1458 + fRec934[1];
			fRec934[0] = ((iTemp1143) ? fTemp1144 : fTemp1142);
			float fThen727 = fConst1458 + fRec934[1] + fConst1459 * fTemp1142;
			float fRec935 = ((iTemp1143) ? fTemp1144 : fThen727);
			output103[i0] = FAUSTFLOAT(fRec927[0] * (2.0f * fRec935 + -1.0f));
			fRec942[0] = fTemp0 - fConst1469 * (fConst1470 * fRec942[1] + fConst1471 * fRec942[2]);
			fRec941[0] = fConst1468 * fRec942[2] + fConst1469 * (fConst1465 * fRec942[0] - (fConst1470 * fRec941[1] + fConst1471 * fRec941[2]));
			fRec940[0] = fConst1468 * fRec941[2] + fConst1469 * (fConst1465 * fRec941[0] - (fConst1470 * fRec940[1] + fConst1471 * fRec940[2]));
			fRec939[0] = fConst1468 * fRec940[2] + fConst1469 * (fConst1465 * fRec940[0] - (fConst1470 * fRec939[1] + fConst1471 * fRec939[2]));
			float fTemp1145 = fConst1468 * fRec939[2];
			float fTemp1146 = fConst1467 * fRec939[0];
			fVec104[0] = fTemp1146 + fTemp1145;
			fRec938[0] = (fTemp1145 + 0.995000005f * fRec938[1] + fTemp1146) - fVec104[1];
			fRec937[IOTA0 & 32767] = fRec937[(IOTA0 - 1) & 32767] + mydsp_faustpower2_f(fRec938[0]);
			float fTemp1147 = std::sqrt(fSlow1 * (fRec937[IOTA0 & 32767] - fRec937[(IOTA0 - iSlow2) & 32767]));
			int iTemp1148 = ((fTemp1147 > fSlow3) ? fTemp1147 : 0.0f) > 0.0f > 0;
			int iTemp1149 = iTemp1148;
			float fTemp1150 = 0.144717798f * ((iTemp1149) ? fSlow5 : fSlow4);
			int iTemp1151 = std::fabs(fTemp1150) < 1.1920929e-07f;
			float fThen731 = std::exp(0.0f - fConst6 / ((iTemp1151) ? 1.0f : fTemp1150));
			float fTemp1152 = ((iTemp1151) ? 0.0f : fThen731);
			float fElse732 = float(iTemp1148);
			fRec936[0] = (1.0f - fTemp1152) * ((iTemp1149) ? fElse732 : 0.0f) + fTemp1152 * fRec936[1];
			float fTemp1153 = fConst1472 + fRec943[1] + -1.0f;
			int iTemp1154 = fTemp1153 < 0.0f;
			float fTemp1155 = fConst1472 + fRec943[1];
			fRec943[0] = ((iTemp1154) ? fTemp1155 : fTemp1153);
			float fThen734 = fConst1472 + fRec943[1] + fConst1473 * fTemp1153;
			float fRec944 = ((iTemp1154) ? fTemp1155 : fThen734);
			output104[i0] = FAUSTFLOAT(fRec936[0] * (2.0f * fRec944 + -1.0f));
			IOTA0 = IOTA0 + 1;
			fRec6[2] = fRec6[1];
			fRec6[1] = fRec6[0];
			fRec5[2] = fRec5[1];
			fRec5[1] = fRec5[0];
			fRec4[2] = fRec4[1];
			fRec4[1] = fRec4[0];
			fRec3[2] = fRec3[1];
			fRec3[1] = fRec3[0];
			fVec0[1] = fVec0[0];
			fRec2[1] = fRec2[0];
			fRec0[1] = fRec0[0];
			fRec7[1] = fRec7[0];
			fRec15[2] = fRec15[1];
			fRec15[1] = fRec15[0];
			fRec14[2] = fRec14[1];
			fRec14[1] = fRec14[0];
			fRec13[2] = fRec13[1];
			fRec13[1] = fRec13[0];
			fRec12[2] = fRec12[1];
			fRec12[1] = fRec12[0];
			fVec1[1] = fVec1[0];
			fRec11[1] = fRec11[0];
			fRec9[1] = fRec9[0];
			fRec16[1] = fRec16[0];
			fRec24[2] = fRec24[1];
			fRec24[1] = fRec24[0];
			fRec23[2] = fRec23[1];
			fRec23[1] = fRec23[0];
			fRec22[2] = fRec22[1];
			fRec22[1] = fRec22[0];
			fRec21[2] = fRec21[1];
			fRec21[1] = fRec21[0];
			fVec2[1] = fVec2[0];
			fRec20[1] = fRec20[0];
			fRec18[1] = fRec18[0];
			fRec25[1] = fRec25[0];
			fRec33[2] = fRec33[1];
			fRec33[1] = fRec33[0];
			fRec32[2] = fRec32[1];
			fRec32[1] = fRec32[0];
			fRec31[2] = fRec31[1];
			fRec31[1] = fRec31[0];
			fRec30[2] = fRec30[1];
			fRec30[1] = fRec30[0];
			fVec3[1] = fVec3[0];
			fRec29[1] = fRec29[0];
			fRec27[1] = fRec27[0];
			fRec34[1] = fRec34[0];
			fRec42[2] = fRec42[1];
			fRec42[1] = fRec42[0];
			fRec41[2] = fRec41[1];
			fRec41[1] = fRec41[0];
			fRec40[2] = fRec40[1];
			fRec40[1] = fRec40[0];
			fRec39[2] = fRec39[1];
			fRec39[1] = fRec39[0];
			fVec4[1] = fVec4[0];
			fRec38[1] = fRec38[0];
			fRec36[1] = fRec36[0];
			fRec43[1] = fRec43[0];
			fRec51[2] = fRec51[1];
			fRec51[1] = fRec51[0];
			fRec50[2] = fRec50[1];
			fRec50[1] = fRec50[0];
			fRec49[2] = fRec49[1];
			fRec49[1] = fRec49[0];
			fRec48[2] = fRec48[1];
			fRec48[1] = fRec48[0];
			fVec5[1] = fVec5[0];
			fRec47[1] = fRec47[0];
			fRec45[1] = fRec45[0];
			fRec52[1] = fRec52[0];
			fRec60[2] = fRec60[1];
			fRec60[1] = fRec60[0];
			fRec59[2] = fRec59[1];
			fRec59[1] = fRec59[0];
			fRec58[2] = fRec58[1];
			fRec58[1] = fRec58[0];
			fRec57[2] = fRec57[1];
			fRec57[1] = fRec57[0];
			fVec6[1] = fVec6[0];
			fRec56[1] = fRec56[0];
			fRec54[1] = fRec54[0];
			fRec61[1] = fRec61[0];
			fRec69[2] = fRec69[1];
			fRec69[1] = fRec69[0];
			fRec68[2] = fRec68[1];
			fRec68[1] = fRec68[0];
			fRec67[2] = fRec67[1];
			fRec67[1] = fRec67[0];
			fRec66[2] = fRec66[1];
			fRec66[1] = fRec66[0];
			fVec7[1] = fVec7[0];
			fRec65[1] = fRec65[0];
			fRec63[1] = fRec63[0];
			fRec70[1] = fRec70[0];
			fRec78[2] = fRec78[1];
			fRec78[1] = fRec78[0];
			fRec77[2] = fRec77[1];
			fRec77[1] = fRec77[0];
			fRec76[2] = fRec76[1];
			fRec76[1] = fRec76[0];
			fRec75[2] = fRec75[1];
			fRec75[1] = fRec75[0];
			fVec8[1] = fVec8[0];
			fRec74[1] = fRec74[0];
			fRec72[1] = fRec72[0];
			fRec79[1] = fRec79[0];
			fRec87[2] = fRec87[1];
			fRec87[1] = fRec87[0];
			fRec86[2] = fRec86[1];
			fRec86[1] = fRec86[0];
			fRec85[2] = fRec85[1];
			fRec85[1] = fRec85[0];
			fRec84[2] = fRec84[1];
			fRec84[1] = fRec84[0];
			fVec9[1] = fVec9[0];
			fRec83[1] = fRec83[0];
			fRec81[1] = fRec81[0];
			fRec88[1] = fRec88[0];
			fRec96[2] = fRec96[1];
			fRec96[1] = fRec96[0];
			fRec95[2] = fRec95[1];
			fRec95[1] = fRec95[0];
			fRec94[2] = fRec94[1];
			fRec94[1] = fRec94[0];
			fRec93[2] = fRec93[1];
			fRec93[1] = fRec93[0];
			fVec10[1] = fVec10[0];
			fRec92[1] = fRec92[0];
			fRec90[1] = fRec90[0];
			fRec97[1] = fRec97[0];
			fRec105[2] = fRec105[1];
			fRec105[1] = fRec105[0];
			fRec104[2] = fRec104[1];
			fRec104[1] = fRec104[0];
			fRec103[2] = fRec103[1];
			fRec103[1] = fRec103[0];
			fRec102[2] = fRec102[1];
			fRec102[1] = fRec102[0];
			fVec11[1] = fVec11[0];
			fRec101[1] = fRec101[0];
			fRec99[1] = fRec99[0];
			fRec106[1] = fRec106[0];
			fRec114[2] = fRec114[1];
			fRec114[1] = fRec114[0];
			fRec113[2] = fRec113[1];
			fRec113[1] = fRec113[0];
			fRec112[2] = fRec112[1];
			fRec112[1] = fRec112[0];
			fRec111[2] = fRec111[1];
			fRec111[1] = fRec111[0];
			fVec12[1] = fVec12[0];
			fRec110[1] = fRec110[0];
			fRec108[1] = fRec108[0];
			fRec115[1] = fRec115[0];
			fRec123[2] = fRec123[1];
			fRec123[1] = fRec123[0];
			fRec122[2] = fRec122[1];
			fRec122[1] = fRec122[0];
			fRec121[2] = fRec121[1];
			fRec121[1] = fRec121[0];
			fRec120[2] = fRec120[1];
			fRec120[1] = fRec120[0];
			fVec13[1] = fVec13[0];
			fRec119[1] = fRec119[0];
			fRec117[1] = fRec117[0];
			fRec124[1] = fRec124[0];
			fRec132[2] = fRec132[1];
			fRec132[1] = fRec132[0];
			fRec131[2] = fRec131[1];
			fRec131[1] = fRec131[0];
			fRec130[2] = fRec130[1];
			fRec130[1] = fRec130[0];
			fRec129[2] = fRec129[1];
			fRec129[1] = fRec129[0];
			fVec14[1] = fVec14[0];
			fRec128[1] = fRec128[0];
			fRec126[1] = fRec126[0];
			fRec133[1] = fRec133[0];
			fRec141[2] = fRec141[1];
			fRec141[1] = fRec141[0];
			fRec140[2] = fRec140[1];
			fRec140[1] = fRec140[0];
			fRec139[2] = fRec139[1];
			fRec139[1] = fRec139[0];
			fRec138[2] = fRec138[1];
			fRec138[1] = fRec138[0];
			fVec15[1] = fVec15[0];
			fRec137[1] = fRec137[0];
			fRec135[1] = fRec135[0];
			fRec142[1] = fRec142[0];
			fRec150[2] = fRec150[1];
			fRec150[1] = fRec150[0];
			fRec149[2] = fRec149[1];
			fRec149[1] = fRec149[0];
			fRec148[2] = fRec148[1];
			fRec148[1] = fRec148[0];
			fRec147[2] = fRec147[1];
			fRec147[1] = fRec147[0];
			fVec16[1] = fVec16[0];
			fRec146[1] = fRec146[0];
			fRec144[1] = fRec144[0];
			fRec151[1] = fRec151[0];
			fRec159[2] = fRec159[1];
			fRec159[1] = fRec159[0];
			fRec158[2] = fRec158[1];
			fRec158[1] = fRec158[0];
			fRec157[2] = fRec157[1];
			fRec157[1] = fRec157[0];
			fRec156[2] = fRec156[1];
			fRec156[1] = fRec156[0];
			fVec17[1] = fVec17[0];
			fRec155[1] = fRec155[0];
			fRec153[1] = fRec153[0];
			fRec160[1] = fRec160[0];
			fRec168[2] = fRec168[1];
			fRec168[1] = fRec168[0];
			fRec167[2] = fRec167[1];
			fRec167[1] = fRec167[0];
			fRec166[2] = fRec166[1];
			fRec166[1] = fRec166[0];
			fRec165[2] = fRec165[1];
			fRec165[1] = fRec165[0];
			fVec18[1] = fVec18[0];
			fRec164[1] = fRec164[0];
			fRec162[1] = fRec162[0];
			fRec169[1] = fRec169[0];
			fRec177[2] = fRec177[1];
			fRec177[1] = fRec177[0];
			fRec176[2] = fRec176[1];
			fRec176[1] = fRec176[0];
			fRec175[2] = fRec175[1];
			fRec175[1] = fRec175[0];
			fRec174[2] = fRec174[1];
			fRec174[1] = fRec174[0];
			fVec19[1] = fVec19[0];
			fRec173[1] = fRec173[0];
			fRec171[1] = fRec171[0];
			fRec178[1] = fRec178[0];
			fRec186[2] = fRec186[1];
			fRec186[1] = fRec186[0];
			fRec185[2] = fRec185[1];
			fRec185[1] = fRec185[0];
			fRec184[2] = fRec184[1];
			fRec184[1] = fRec184[0];
			fRec183[2] = fRec183[1];
			fRec183[1] = fRec183[0];
			fVec20[1] = fVec20[0];
			fRec182[1] = fRec182[0];
			fRec180[1] = fRec180[0];
			fRec187[1] = fRec187[0];
			fRec195[2] = fRec195[1];
			fRec195[1] = fRec195[0];
			fRec194[2] = fRec194[1];
			fRec194[1] = fRec194[0];
			fRec193[2] = fRec193[1];
			fRec193[1] = fRec193[0];
			fRec192[2] = fRec192[1];
			fRec192[1] = fRec192[0];
			fVec21[1] = fVec21[0];
			fRec191[1] = fRec191[0];
			fRec189[1] = fRec189[0];
			fRec196[1] = fRec196[0];
			fRec204[2] = fRec204[1];
			fRec204[1] = fRec204[0];
			fRec203[2] = fRec203[1];
			fRec203[1] = fRec203[0];
			fRec202[2] = fRec202[1];
			fRec202[1] = fRec202[0];
			fRec201[2] = fRec201[1];
			fRec201[1] = fRec201[0];
			fVec22[1] = fVec22[0];
			fRec200[1] = fRec200[0];
			fRec198[1] = fRec198[0];
			fRec205[1] = fRec205[0];
			fRec213[2] = fRec213[1];
			fRec213[1] = fRec213[0];
			fRec212[2] = fRec212[1];
			fRec212[1] = fRec212[0];
			fRec211[2] = fRec211[1];
			fRec211[1] = fRec211[0];
			fRec210[2] = fRec210[1];
			fRec210[1] = fRec210[0];
			fVec23[1] = fVec23[0];
			fRec209[1] = fRec209[0];
			fRec207[1] = fRec207[0];
			fRec214[1] = fRec214[0];
			fRec222[2] = fRec222[1];
			fRec222[1] = fRec222[0];
			fRec221[2] = fRec221[1];
			fRec221[1] = fRec221[0];
			fRec220[2] = fRec220[1];
			fRec220[1] = fRec220[0];
			fRec219[2] = fRec219[1];
			fRec219[1] = fRec219[0];
			fVec24[1] = fVec24[0];
			fRec218[1] = fRec218[0];
			fRec216[1] = fRec216[0];
			fRec223[1] = fRec223[0];
			fRec231[2] = fRec231[1];
			fRec231[1] = fRec231[0];
			fRec230[2] = fRec230[1];
			fRec230[1] = fRec230[0];
			fRec229[2] = fRec229[1];
			fRec229[1] = fRec229[0];
			fRec228[2] = fRec228[1];
			fRec228[1] = fRec228[0];
			fVec25[1] = fVec25[0];
			fRec227[1] = fRec227[0];
			fRec225[1] = fRec225[0];
			fRec232[1] = fRec232[0];
			fRec240[2] = fRec240[1];
			fRec240[1] = fRec240[0];
			fRec239[2] = fRec239[1];
			fRec239[1] = fRec239[0];
			fRec238[2] = fRec238[1];
			fRec238[1] = fRec238[0];
			fRec237[2] = fRec237[1];
			fRec237[1] = fRec237[0];
			fVec26[1] = fVec26[0];
			fRec236[1] = fRec236[0];
			fRec234[1] = fRec234[0];
			fRec241[1] = fRec241[0];
			fRec249[2] = fRec249[1];
			fRec249[1] = fRec249[0];
			fRec248[2] = fRec248[1];
			fRec248[1] = fRec248[0];
			fRec247[2] = fRec247[1];
			fRec247[1] = fRec247[0];
			fRec246[2] = fRec246[1];
			fRec246[1] = fRec246[0];
			fVec27[1] = fVec27[0];
			fRec245[1] = fRec245[0];
			fRec243[1] = fRec243[0];
			fRec250[1] = fRec250[0];
			fRec258[2] = fRec258[1];
			fRec258[1] = fRec258[0];
			fRec257[2] = fRec257[1];
			fRec257[1] = fRec257[0];
			fRec256[2] = fRec256[1];
			fRec256[1] = fRec256[0];
			fRec255[2] = fRec255[1];
			fRec255[1] = fRec255[0];
			fVec28[1] = fVec28[0];
			fRec254[1] = fRec254[0];
			fRec252[1] = fRec252[0];
			fRec259[1] = fRec259[0];
			fRec267[2] = fRec267[1];
			fRec267[1] = fRec267[0];
			fRec266[2] = fRec266[1];
			fRec266[1] = fRec266[0];
			fRec265[2] = fRec265[1];
			fRec265[1] = fRec265[0];
			fRec264[2] = fRec264[1];
			fRec264[1] = fRec264[0];
			fVec29[1] = fVec29[0];
			fRec263[1] = fRec263[0];
			fRec261[1] = fRec261[0];
			fRec268[1] = fRec268[0];
			fRec276[2] = fRec276[1];
			fRec276[1] = fRec276[0];
			fRec275[2] = fRec275[1];
			fRec275[1] = fRec275[0];
			fRec274[2] = fRec274[1];
			fRec274[1] = fRec274[0];
			fRec273[2] = fRec273[1];
			fRec273[1] = fRec273[0];
			fVec30[1] = fVec30[0];
			fRec272[1] = fRec272[0];
			fRec270[1] = fRec270[0];
			fRec277[1] = fRec277[0];
			fRec285[2] = fRec285[1];
			fRec285[1] = fRec285[0];
			fRec284[2] = fRec284[1];
			fRec284[1] = fRec284[0];
			fRec283[2] = fRec283[1];
			fRec283[1] = fRec283[0];
			fRec282[2] = fRec282[1];
			fRec282[1] = fRec282[0];
			fVec31[1] = fVec31[0];
			fRec281[1] = fRec281[0];
			fRec279[1] = fRec279[0];
			fRec286[1] = fRec286[0];
			fRec294[2] = fRec294[1];
			fRec294[1] = fRec294[0];
			fRec293[2] = fRec293[1];
			fRec293[1] = fRec293[0];
			fRec292[2] = fRec292[1];
			fRec292[1] = fRec292[0];
			fRec291[2] = fRec291[1];
			fRec291[1] = fRec291[0];
			fVec32[1] = fVec32[0];
			fRec290[1] = fRec290[0];
			fRec288[1] = fRec288[0];
			fRec295[1] = fRec295[0];
			fRec303[2] = fRec303[1];
			fRec303[1] = fRec303[0];
			fRec302[2] = fRec302[1];
			fRec302[1] = fRec302[0];
			fRec301[2] = fRec301[1];
			fRec301[1] = fRec301[0];
			fRec300[2] = fRec300[1];
			fRec300[1] = fRec300[0];
			fVec33[1] = fVec33[0];
			fRec299[1] = fRec299[0];
			fRec297[1] = fRec297[0];
			fRec304[1] = fRec304[0];
			fRec312[2] = fRec312[1];
			fRec312[1] = fRec312[0];
			fRec311[2] = fRec311[1];
			fRec311[1] = fRec311[0];
			fRec310[2] = fRec310[1];
			fRec310[1] = fRec310[0];
			fRec309[2] = fRec309[1];
			fRec309[1] = fRec309[0];
			fVec34[1] = fVec34[0];
			fRec308[1] = fRec308[0];
			fRec306[1] = fRec306[0];
			fRec313[1] = fRec313[0];
			fRec321[2] = fRec321[1];
			fRec321[1] = fRec321[0];
			fRec320[2] = fRec320[1];
			fRec320[1] = fRec320[0];
			fRec319[2] = fRec319[1];
			fRec319[1] = fRec319[0];
			fRec318[2] = fRec318[1];
			fRec318[1] = fRec318[0];
			fVec35[1] = fVec35[0];
			fRec317[1] = fRec317[0];
			fRec315[1] = fRec315[0];
			fRec322[1] = fRec322[0];
			fRec330[2] = fRec330[1];
			fRec330[1] = fRec330[0];
			fRec329[2] = fRec329[1];
			fRec329[1] = fRec329[0];
			fRec328[2] = fRec328[1];
			fRec328[1] = fRec328[0];
			fRec327[2] = fRec327[1];
			fRec327[1] = fRec327[0];
			fVec36[1] = fVec36[0];
			fRec326[1] = fRec326[0];
			fRec324[1] = fRec324[0];
			fRec331[1] = fRec331[0];
			fRec339[2] = fRec339[1];
			fRec339[1] = fRec339[0];
			fRec338[2] = fRec338[1];
			fRec338[1] = fRec338[0];
			fRec337[2] = fRec337[1];
			fRec337[1] = fRec337[0];
			fRec336[2] = fRec336[1];
			fRec336[1] = fRec336[0];
			fVec37[1] = fVec37[0];
			fRec335[1] = fRec335[0];
			fRec333[1] = fRec333[0];
			fRec340[1] = fRec340[0];
			fRec348[2] = fRec348[1];
			fRec348[1] = fRec348[0];
			fRec347[2] = fRec347[1];
			fRec347[1] = fRec347[0];
			fRec346[2] = fRec346[1];
			fRec346[1] = fRec346[0];
			fRec345[2] = fRec345[1];
			fRec345[1] = fRec345[0];
			fVec38[1] = fVec38[0];
			fRec344[1] = fRec344[0];
			fRec342[1] = fRec342[0];
			fRec349[1] = fRec349[0];
			fRec357[2] = fRec357[1];
			fRec357[1] = fRec357[0];
			fRec356[2] = fRec356[1];
			fRec356[1] = fRec356[0];
			fRec355[2] = fRec355[1];
			fRec355[1] = fRec355[0];
			fRec354[2] = fRec354[1];
			fRec354[1] = fRec354[0];
			fVec39[1] = fVec39[0];
			fRec353[1] = fRec353[0];
			fRec351[1] = fRec351[0];
			fRec358[1] = fRec358[0];
			fRec366[2] = fRec366[1];
			fRec366[1] = fRec366[0];
			fRec365[2] = fRec365[1];
			fRec365[1] = fRec365[0];
			fRec364[2] = fRec364[1];
			fRec364[1] = fRec364[0];
			fRec363[2] = fRec363[1];
			fRec363[1] = fRec363[0];
			fVec40[1] = fVec40[0];
			fRec362[1] = fRec362[0];
			fRec360[1] = fRec360[0];
			fRec367[1] = fRec367[0];
			fRec375[2] = fRec375[1];
			fRec375[1] = fRec375[0];
			fRec374[2] = fRec374[1];
			fRec374[1] = fRec374[0];
			fRec373[2] = fRec373[1];
			fRec373[1] = fRec373[0];
			fRec372[2] = fRec372[1];
			fRec372[1] = fRec372[0];
			fVec41[1] = fVec41[0];
			fRec371[1] = fRec371[0];
			fRec369[1] = fRec369[0];
			fRec376[1] = fRec376[0];
			fRec384[2] = fRec384[1];
			fRec384[1] = fRec384[0];
			fRec383[2] = fRec383[1];
			fRec383[1] = fRec383[0];
			fRec382[2] = fRec382[1];
			fRec382[1] = fRec382[0];
			fRec381[2] = fRec381[1];
			fRec381[1] = fRec381[0];
			fVec42[1] = fVec42[0];
			fRec380[1] = fRec380[0];
			fRec378[1] = fRec378[0];
			fRec385[1] = fRec385[0];
			fRec393[2] = fRec393[1];
			fRec393[1] = fRec393[0];
			fRec392[2] = fRec392[1];
			fRec392[1] = fRec392[0];
			fRec391[2] = fRec391[1];
			fRec391[1] = fRec391[0];
			fRec390[2] = fRec390[1];
			fRec390[1] = fRec390[0];
			fVec43[1] = fVec43[0];
			fRec389[1] = fRec389[0];
			fRec387[1] = fRec387[0];
			fRec394[1] = fRec394[0];
			fRec402[2] = fRec402[1];
			fRec402[1] = fRec402[0];
			fRec401[2] = fRec401[1];
			fRec401[1] = fRec401[0];
			fRec400[2] = fRec400[1];
			fRec400[1] = fRec400[0];
			fRec399[2] = fRec399[1];
			fRec399[1] = fRec399[0];
			fVec44[1] = fVec44[0];
			fRec398[1] = fRec398[0];
			fRec396[1] = fRec396[0];
			fRec403[1] = fRec403[0];
			fRec411[2] = fRec411[1];
			fRec411[1] = fRec411[0];
			fRec410[2] = fRec410[1];
			fRec410[1] = fRec410[0];
			fRec409[2] = fRec409[1];
			fRec409[1] = fRec409[0];
			fRec408[2] = fRec408[1];
			fRec408[1] = fRec408[0];
			fVec45[1] = fVec45[0];
			fRec407[1] = fRec407[0];
			fRec405[1] = fRec405[0];
			fRec412[1] = fRec412[0];
			fRec420[2] = fRec420[1];
			fRec420[1] = fRec420[0];
			fRec419[2] = fRec419[1];
			fRec419[1] = fRec419[0];
			fRec418[2] = fRec418[1];
			fRec418[1] = fRec418[0];
			fRec417[2] = fRec417[1];
			fRec417[1] = fRec417[0];
			fVec46[1] = fVec46[0];
			fRec416[1] = fRec416[0];
			fRec414[1] = fRec414[0];
			fRec421[1] = fRec421[0];
			fRec429[2] = fRec429[1];
			fRec429[1] = fRec429[0];
			fRec428[2] = fRec428[1];
			fRec428[1] = fRec428[0];
			fRec427[2] = fRec427[1];
			fRec427[1] = fRec427[0];
			fRec426[2] = fRec426[1];
			fRec426[1] = fRec426[0];
			fVec47[1] = fVec47[0];
			fRec425[1] = fRec425[0];
			fRec423[1] = fRec423[0];
			fRec430[1] = fRec430[0];
			fRec438[2] = fRec438[1];
			fRec438[1] = fRec438[0];
			fRec437[2] = fRec437[1];
			fRec437[1] = fRec437[0];
			fRec436[2] = fRec436[1];
			fRec436[1] = fRec436[0];
			fRec435[2] = fRec435[1];
			fRec435[1] = fRec435[0];
			fVec48[1] = fVec48[0];
			fRec434[1] = fRec434[0];
			fRec432[1] = fRec432[0];
			fRec439[1] = fRec439[0];
			fRec447[2] = fRec447[1];
			fRec447[1] = fRec447[0];
			fRec446[2] = fRec446[1];
			fRec446[1] = fRec446[0];
			fRec445[2] = fRec445[1];
			fRec445[1] = fRec445[0];
			fRec444[2] = fRec444[1];
			fRec444[1] = fRec444[0];
			fVec49[1] = fVec49[0];
			fRec443[1] = fRec443[0];
			fRec441[1] = fRec441[0];
			fRec448[1] = fRec448[0];
			fRec456[2] = fRec456[1];
			fRec456[1] = fRec456[0];
			fRec455[2] = fRec455[1];
			fRec455[1] = fRec455[0];
			fRec454[2] = fRec454[1];
			fRec454[1] = fRec454[0];
			fRec453[2] = fRec453[1];
			fRec453[1] = fRec453[0];
			fVec50[1] = fVec50[0];
			fRec452[1] = fRec452[0];
			fRec450[1] = fRec450[0];
			fRec457[1] = fRec457[0];
			fRec465[2] = fRec465[1];
			fRec465[1] = fRec465[0];
			fRec464[2] = fRec464[1];
			fRec464[1] = fRec464[0];
			fRec463[2] = fRec463[1];
			fRec463[1] = fRec463[0];
			fRec462[2] = fRec462[1];
			fRec462[1] = fRec462[0];
			fVec51[1] = fVec51[0];
			fRec461[1] = fRec461[0];
			fRec459[1] = fRec459[0];
			fRec466[1] = fRec466[0];
			fRec474[2] = fRec474[1];
			fRec474[1] = fRec474[0];
			fRec473[2] = fRec473[1];
			fRec473[1] = fRec473[0];
			fRec472[2] = fRec472[1];
			fRec472[1] = fRec472[0];
			fRec471[2] = fRec471[1];
			fRec471[1] = fRec471[0];
			fVec52[1] = fVec52[0];
			fRec470[1] = fRec470[0];
			fRec468[1] = fRec468[0];
			fRec475[1] = fRec475[0];
			fRec483[2] = fRec483[1];
			fRec483[1] = fRec483[0];
			fRec482[2] = fRec482[1];
			fRec482[1] = fRec482[0];
			fRec481[2] = fRec481[1];
			fRec481[1] = fRec481[0];
			fRec480[2] = fRec480[1];
			fRec480[1] = fRec480[0];
			fVec53[1] = fVec53[0];
			fRec479[1] = fRec479[0];
			fRec477[1] = fRec477[0];
			fRec484[1] = fRec484[0];
			fRec492[2] = fRec492[1];
			fRec492[1] = fRec492[0];
			fRec491[2] = fRec491[1];
			fRec491[1] = fRec491[0];
			fRec490[2] = fRec490[1];
			fRec490[1] = fRec490[0];
			fRec489[2] = fRec489[1];
			fRec489[1] = fRec489[0];
			fVec54[1] = fVec54[0];
			fRec488[1] = fRec488[0];
			fRec486[1] = fRec486[0];
			fRec493[1] = fRec493[0];
			fRec501[2] = fRec501[1];
			fRec501[1] = fRec501[0];
			fRec500[2] = fRec500[1];
			fRec500[1] = fRec500[0];
			fRec499[2] = fRec499[1];
			fRec499[1] = fRec499[0];
			fRec498[2] = fRec498[1];
			fRec498[1] = fRec498[0];
			fVec55[1] = fVec55[0];
			fRec497[1] = fRec497[0];
			fRec495[1] = fRec495[0];
			fRec502[1] = fRec502[0];
			fRec510[2] = fRec510[1];
			fRec510[1] = fRec510[0];
			fRec509[2] = fRec509[1];
			fRec509[1] = fRec509[0];
			fRec508[2] = fRec508[1];
			fRec508[1] = fRec508[0];
			fRec507[2] = fRec507[1];
			fRec507[1] = fRec507[0];
			fVec56[1] = fVec56[0];
			fRec506[1] = fRec506[0];
			fRec504[1] = fRec504[0];
			fRec511[1] = fRec511[0];
			fRec519[2] = fRec519[1];
			fRec519[1] = fRec519[0];
			fRec518[2] = fRec518[1];
			fRec518[1] = fRec518[0];
			fRec517[2] = fRec517[1];
			fRec517[1] = fRec517[0];
			fRec516[2] = fRec516[1];
			fRec516[1] = fRec516[0];
			fVec57[1] = fVec57[0];
			fRec515[1] = fRec515[0];
			fRec513[1] = fRec513[0];
			fRec520[1] = fRec520[0];
			fRec528[2] = fRec528[1];
			fRec528[1] = fRec528[0];
			fRec527[2] = fRec527[1];
			fRec527[1] = fRec527[0];
			fRec526[2] = fRec526[1];
			fRec526[1] = fRec526[0];
			fRec525[2] = fRec525[1];
			fRec525[1] = fRec525[0];
			fVec58[1] = fVec58[0];
			fRec524[1] = fRec524[0];
			fRec522[1] = fRec522[0];
			fRec529[1] = fRec529[0];
			fRec537[2] = fRec537[1];
			fRec537[1] = fRec537[0];
			fRec536[2] = fRec536[1];
			fRec536[1] = fRec536[0];
			fRec535[2] = fRec535[1];
			fRec535[1] = fRec535[0];
			fRec534[2] = fRec534[1];
			fRec534[1] = fRec534[0];
			fVec59[1] = fVec59[0];
			fRec533[1] = fRec533[0];
			fRec531[1] = fRec531[0];
			fRec538[1] = fRec538[0];
			fRec546[2] = fRec546[1];
			fRec546[1] = fRec546[0];
			fRec545[2] = fRec545[1];
			fRec545[1] = fRec545[0];
			fRec544[2] = fRec544[1];
			fRec544[1] = fRec544[0];
			fRec543[2] = fRec543[1];
			fRec543[1] = fRec543[0];
			fVec60[1] = fVec60[0];
			fRec542[1] = fRec542[0];
			fRec540[1] = fRec540[0];
			fRec547[1] = fRec547[0];
			fRec555[2] = fRec555[1];
			fRec555[1] = fRec555[0];
			fRec554[2] = fRec554[1];
			fRec554[1] = fRec554[0];
			fRec553[2] = fRec553[1];
			fRec553[1] = fRec553[0];
			fRec552[2] = fRec552[1];
			fRec552[1] = fRec552[0];
			fVec61[1] = fVec61[0];
			fRec551[1] = fRec551[0];
			fRec549[1] = fRec549[0];
			fRec556[1] = fRec556[0];
			fRec564[2] = fRec564[1];
			fRec564[1] = fRec564[0];
			fRec563[2] = fRec563[1];
			fRec563[1] = fRec563[0];
			fRec562[2] = fRec562[1];
			fRec562[1] = fRec562[0];
			fRec561[2] = fRec561[1];
			fRec561[1] = fRec561[0];
			fVec62[1] = fVec62[0];
			fRec560[1] = fRec560[0];
			fRec558[1] = fRec558[0];
			fRec565[1] = fRec565[0];
			fRec573[2] = fRec573[1];
			fRec573[1] = fRec573[0];
			fRec572[2] = fRec572[1];
			fRec572[1] = fRec572[0];
			fRec571[2] = fRec571[1];
			fRec571[1] = fRec571[0];
			fRec570[2] = fRec570[1];
			fRec570[1] = fRec570[0];
			fVec63[1] = fVec63[0];
			fRec569[1] = fRec569[0];
			fRec567[1] = fRec567[0];
			fRec574[1] = fRec574[0];
			fRec582[2] = fRec582[1];
			fRec582[1] = fRec582[0];
			fRec581[2] = fRec581[1];
			fRec581[1] = fRec581[0];
			fRec580[2] = fRec580[1];
			fRec580[1] = fRec580[0];
			fRec579[2] = fRec579[1];
			fRec579[1] = fRec579[0];
			fVec64[1] = fVec64[0];
			fRec578[1] = fRec578[0];
			fRec576[1] = fRec576[0];
			fRec583[1] = fRec583[0];
			fRec591[2] = fRec591[1];
			fRec591[1] = fRec591[0];
			fRec590[2] = fRec590[1];
			fRec590[1] = fRec590[0];
			fRec589[2] = fRec589[1];
			fRec589[1] = fRec589[0];
			fRec588[2] = fRec588[1];
			fRec588[1] = fRec588[0];
			fVec65[1] = fVec65[0];
			fRec587[1] = fRec587[0];
			fRec585[1] = fRec585[0];
			fRec592[1] = fRec592[0];
			fRec600[2] = fRec600[1];
			fRec600[1] = fRec600[0];
			fRec599[2] = fRec599[1];
			fRec599[1] = fRec599[0];
			fRec598[2] = fRec598[1];
			fRec598[1] = fRec598[0];
			fRec597[2] = fRec597[1];
			fRec597[1] = fRec597[0];
			fVec66[1] = fVec66[0];
			fRec596[1] = fRec596[0];
			fRec594[1] = fRec594[0];
			fRec601[1] = fRec601[0];
			fRec609[2] = fRec609[1];
			fRec609[1] = fRec609[0];
			fRec608[2] = fRec608[1];
			fRec608[1] = fRec608[0];
			fRec607[2] = fRec607[1];
			fRec607[1] = fRec607[0];
			fRec606[2] = fRec606[1];
			fRec606[1] = fRec606[0];
			fVec67[1] = fVec67[0];
			fRec605[1] = fRec605[0];
			fRec603[1] = fRec603[0];
			fRec610[1] = fRec610[0];
			fRec618[2] = fRec618[1];
			fRec618[1] = fRec618[0];
			fRec617[2] = fRec617[1];
			fRec617[1] = fRec617[0];
			fRec616[2] = fRec616[1];
			fRec616[1] = fRec616[0];
			fRec615[2] = fRec615[1];
			fRec615[1] = fRec615[0];
			fVec68[1] = fVec68[0];
			fRec614[1] = fRec614[0];
			fRec612[1] = fRec612[0];
			fRec619[1] = fRec619[0];
			fRec627[2] = fRec627[1];
			fRec627[1] = fRec627[0];
			fRec626[2] = fRec626[1];
			fRec626[1] = fRec626[0];
			fRec625[2] = fRec625[1];
			fRec625[1] = fRec625[0];
			fRec624[2] = fRec624[1];
			fRec624[1] = fRec624[0];
			fVec69[1] = fVec69[0];
			fRec623[1] = fRec623[0];
			fRec621[1] = fRec621[0];
			fRec628[1] = fRec628[0];
			fRec636[2] = fRec636[1];
			fRec636[1] = fRec636[0];
			fRec635[2] = fRec635[1];
			fRec635[1] = fRec635[0];
			fRec634[2] = fRec634[1];
			fRec634[1] = fRec634[0];
			fRec633[2] = fRec633[1];
			fRec633[1] = fRec633[0];
			fVec70[1] = fVec70[0];
			fRec632[1] = fRec632[0];
			fRec630[1] = fRec630[0];
			fRec637[1] = fRec637[0];
			fRec645[2] = fRec645[1];
			fRec645[1] = fRec645[0];
			fRec644[2] = fRec644[1];
			fRec644[1] = fRec644[0];
			fRec643[2] = fRec643[1];
			fRec643[1] = fRec643[0];
			fRec642[2] = fRec642[1];
			fRec642[1] = fRec642[0];
			fVec71[1] = fVec71[0];
			fRec641[1] = fRec641[0];
			fRec639[1] = fRec639[0];
			fRec646[1] = fRec646[0];
			fRec654[2] = fRec654[1];
			fRec654[1] = fRec654[0];
			fRec653[2] = fRec653[1];
			fRec653[1] = fRec653[0];
			fRec652[2] = fRec652[1];
			fRec652[1] = fRec652[0];
			fRec651[2] = fRec651[1];
			fRec651[1] = fRec651[0];
			fVec72[1] = fVec72[0];
			fRec650[1] = fRec650[0];
			fRec648[1] = fRec648[0];
			fRec655[1] = fRec655[0];
			fRec663[2] = fRec663[1];
			fRec663[1] = fRec663[0];
			fRec662[2] = fRec662[1];
			fRec662[1] = fRec662[0];
			fRec661[2] = fRec661[1];
			fRec661[1] = fRec661[0];
			fRec660[2] = fRec660[1];
			fRec660[1] = fRec660[0];
			fVec73[1] = fVec73[0];
			fRec659[1] = fRec659[0];
			fRec657[1] = fRec657[0];
			fRec664[1] = fRec664[0];
			fRec672[2] = fRec672[1];
			fRec672[1] = fRec672[0];
			fRec671[2] = fRec671[1];
			fRec671[1] = fRec671[0];
			fRec670[2] = fRec670[1];
			fRec670[1] = fRec670[0];
			fRec669[2] = fRec669[1];
			fRec669[1] = fRec669[0];
			fVec74[1] = fVec74[0];
			fRec668[1] = fRec668[0];
			fRec666[1] = fRec666[0];
			fRec673[1] = fRec673[0];
			fRec681[2] = fRec681[1];
			fRec681[1] = fRec681[0];
			fRec680[2] = fRec680[1];
			fRec680[1] = fRec680[0];
			fRec679[2] = fRec679[1];
			fRec679[1] = fRec679[0];
			fRec678[2] = fRec678[1];
			fRec678[1] = fRec678[0];
			fVec75[1] = fVec75[0];
			fRec677[1] = fRec677[0];
			fRec675[1] = fRec675[0];
			fRec682[1] = fRec682[0];
			fRec690[2] = fRec690[1];
			fRec690[1] = fRec690[0];
			fRec689[2] = fRec689[1];
			fRec689[1] = fRec689[0];
			fRec688[2] = fRec688[1];
			fRec688[1] = fRec688[0];
			fRec687[2] = fRec687[1];
			fRec687[1] = fRec687[0];
			fVec76[1] = fVec76[0];
			fRec686[1] = fRec686[0];
			fRec684[1] = fRec684[0];
			fRec691[1] = fRec691[0];
			fRec699[2] = fRec699[1];
			fRec699[1] = fRec699[0];
			fRec698[2] = fRec698[1];
			fRec698[1] = fRec698[0];
			fRec697[2] = fRec697[1];
			fRec697[1] = fRec697[0];
			fRec696[2] = fRec696[1];
			fRec696[1] = fRec696[0];
			fVec77[1] = fVec77[0];
			fRec695[1] = fRec695[0];
			fRec693[1] = fRec693[0];
			fRec700[1] = fRec700[0];
			fRec708[2] = fRec708[1];
			fRec708[1] = fRec708[0];
			fRec707[2] = fRec707[1];
			fRec707[1] = fRec707[0];
			fRec706[2] = fRec706[1];
			fRec706[1] = fRec706[0];
			fRec705[2] = fRec705[1];
			fRec705[1] = fRec705[0];
			fVec78[1] = fVec78[0];
			fRec704[1] = fRec704[0];
			fRec702[1] = fRec702[0];
			fRec709[1] = fRec709[0];
			fRec717[2] = fRec717[1];
			fRec717[1] = fRec717[0];
			fRec716[2] = fRec716[1];
			fRec716[1] = fRec716[0];
			fRec715[2] = fRec715[1];
			fRec715[1] = fRec715[0];
			fRec714[2] = fRec714[1];
			fRec714[1] = fRec714[0];
			fVec79[1] = fVec79[0];
			fRec713[1] = fRec713[0];
			fRec711[1] = fRec711[0];
			fRec718[1] = fRec718[0];
			fRec726[2] = fRec726[1];
			fRec726[1] = fRec726[0];
			fRec725[2] = fRec725[1];
			fRec725[1] = fRec725[0];
			fRec724[2] = fRec724[1];
			fRec724[1] = fRec724[0];
			fRec723[2] = fRec723[1];
			fRec723[1] = fRec723[0];
			fVec80[1] = fVec80[0];
			fRec722[1] = fRec722[0];
			fRec720[1] = fRec720[0];
			fRec727[1] = fRec727[0];
			fRec735[2] = fRec735[1];
			fRec735[1] = fRec735[0];
			fRec734[2] = fRec734[1];
			fRec734[1] = fRec734[0];
			fRec733[2] = fRec733[1];
			fRec733[1] = fRec733[0];
			fRec732[2] = fRec732[1];
			fRec732[1] = fRec732[0];
			fVec81[1] = fVec81[0];
			fRec731[1] = fRec731[0];
			fRec729[1] = fRec729[0];
			fRec736[1] = fRec736[0];
			fRec744[2] = fRec744[1];
			fRec744[1] = fRec744[0];
			fRec743[2] = fRec743[1];
			fRec743[1] = fRec743[0];
			fRec742[2] = fRec742[1];
			fRec742[1] = fRec742[0];
			fRec741[2] = fRec741[1];
			fRec741[1] = fRec741[0];
			fVec82[1] = fVec82[0];
			fRec740[1] = fRec740[0];
			fRec738[1] = fRec738[0];
			fRec745[1] = fRec745[0];
			fRec753[2] = fRec753[1];
			fRec753[1] = fRec753[0];
			fRec752[2] = fRec752[1];
			fRec752[1] = fRec752[0];
			fRec751[2] = fRec751[1];
			fRec751[1] = fRec751[0];
			fRec750[2] = fRec750[1];
			fRec750[1] = fRec750[0];
			fVec83[1] = fVec83[0];
			fRec749[1] = fRec749[0];
			fRec747[1] = fRec747[0];
			fRec754[1] = fRec754[0];
			fRec762[2] = fRec762[1];
			fRec762[1] = fRec762[0];
			fRec761[2] = fRec761[1];
			fRec761[1] = fRec761[0];
			fRec760[2] = fRec760[1];
			fRec760[1] = fRec760[0];
			fRec759[2] = fRec759[1];
			fRec759[1] = fRec759[0];
			fVec84[1] = fVec84[0];
			fRec758[1] = fRec758[0];
			fRec756[1] = fRec756[0];
			fRec763[1] = fRec763[0];
			fRec771[2] = fRec771[1];
			fRec771[1] = fRec771[0];
			fRec770[2] = fRec770[1];
			fRec770[1] = fRec770[0];
			fRec769[2] = fRec769[1];
			fRec769[1] = fRec769[0];
			fRec768[2] = fRec768[1];
			fRec768[1] = fRec768[0];
			fVec85[1] = fVec85[0];
			fRec767[1] = fRec767[0];
			fRec765[1] = fRec765[0];
			fRec772[1] = fRec772[0];
			fRec780[2] = fRec780[1];
			fRec780[1] = fRec780[0];
			fRec779[2] = fRec779[1];
			fRec779[1] = fRec779[0];
			fRec778[2] = fRec778[1];
			fRec778[1] = fRec778[0];
			fRec777[2] = fRec777[1];
			fRec777[1] = fRec777[0];
			fVec86[1] = fVec86[0];
			fRec776[1] = fRec776[0];
			fRec774[1] = fRec774[0];
			fRec781[1] = fRec781[0];
			fRec789[2] = fRec789[1];
			fRec789[1] = fRec789[0];
			fRec788[2] = fRec788[1];
			fRec788[1] = fRec788[0];
			fRec787[2] = fRec787[1];
			fRec787[1] = fRec787[0];
			fRec786[2] = fRec786[1];
			fRec786[1] = fRec786[0];
			fVec87[1] = fVec87[0];
			fRec785[1] = fRec785[0];
			fRec783[1] = fRec783[0];
			fRec790[1] = fRec790[0];
			fRec798[2] = fRec798[1];
			fRec798[1] = fRec798[0];
			fRec797[2] = fRec797[1];
			fRec797[1] = fRec797[0];
			fRec796[2] = fRec796[1];
			fRec796[1] = fRec796[0];
			fRec795[2] = fRec795[1];
			fRec795[1] = fRec795[0];
			fVec88[1] = fVec88[0];
			fRec794[1] = fRec794[0];
			fRec792[1] = fRec792[0];
			fRec799[1] = fRec799[0];
			fRec807[2] = fRec807[1];
			fRec807[1] = fRec807[0];
			fRec806[2] = fRec806[1];
			fRec806[1] = fRec806[0];
			fRec805[2] = fRec805[1];
			fRec805[1] = fRec805[0];
			fRec804[2] = fRec804[1];
			fRec804[1] = fRec804[0];
			fVec89[1] = fVec89[0];
			fRec803[1] = fRec803[0];
			fRec801[1] = fRec801[0];
			fRec808[1] = fRec808[0];
			fRec816[2] = fRec816[1];
			fRec816[1] = fRec816[0];
			fRec815[2] = fRec815[1];
			fRec815[1] = fRec815[0];
			fRec814[2] = fRec814[1];
			fRec814[1] = fRec814[0];
			fRec813[2] = fRec813[1];
			fRec813[1] = fRec813[0];
			fVec90[1] = fVec90[0];
			fRec812[1] = fRec812[0];
			fRec810[1] = fRec810[0];
			fRec817[1] = fRec817[0];
			fRec825[2] = fRec825[1];
			fRec825[1] = fRec825[0];
			fRec824[2] = fRec824[1];
			fRec824[1] = fRec824[0];
			fRec823[2] = fRec823[1];
			fRec823[1] = fRec823[0];
			fRec822[2] = fRec822[1];
			fRec822[1] = fRec822[0];
			fVec91[1] = fVec91[0];
			fRec821[1] = fRec821[0];
			fRec819[1] = fRec819[0];
			fRec826[1] = fRec826[0];
			fRec834[2] = fRec834[1];
			fRec834[1] = fRec834[0];
			fRec833[2] = fRec833[1];
			fRec833[1] = fRec833[0];
			fRec832[2] = fRec832[1];
			fRec832[1] = fRec832[0];
			fRec831[2] = fRec831[1];
			fRec831[1] = fRec831[0];
			fVec92[1] = fVec92[0];
			fRec830[1] = fRec830[0];
			fRec828[1] = fRec828[0];
			fRec835[1] = fRec835[0];
			fRec843[2] = fRec843[1];
			fRec843[1] = fRec843[0];
			fRec842[2] = fRec842[1];
			fRec842[1] = fRec842[0];
			fRec841[2] = fRec841[1];
			fRec841[1] = fRec841[0];
			fRec840[2] = fRec840[1];
			fRec840[1] = fRec840[0];
			fVec93[1] = fVec93[0];
			fRec839[1] = fRec839[0];
			fRec837[1] = fRec837[0];
			fRec844[1] = fRec844[0];
			fRec852[2] = fRec852[1];
			fRec852[1] = fRec852[0];
			fRec851[2] = fRec851[1];
			fRec851[1] = fRec851[0];
			fRec850[2] = fRec850[1];
			fRec850[1] = fRec850[0];
			fRec849[2] = fRec849[1];
			fRec849[1] = fRec849[0];
			fVec94[1] = fVec94[0];
			fRec848[1] = fRec848[0];
			fRec846[1] = fRec846[0];
			fRec853[1] = fRec853[0];
			fRec861[2] = fRec861[1];
			fRec861[1] = fRec861[0];
			fRec860[2] = fRec860[1];
			fRec860[1] = fRec860[0];
			fRec859[2] = fRec859[1];
			fRec859[1] = fRec859[0];
			fRec858[2] = fRec858[1];
			fRec858[1] = fRec858[0];
			fVec95[1] = fVec95[0];
			fRec857[1] = fRec857[0];
			fRec855[1] = fRec855[0];
			fRec862[1] = fRec862[0];
			fRec870[2] = fRec870[1];
			fRec870[1] = fRec870[0];
			fRec869[2] = fRec869[1];
			fRec869[1] = fRec869[0];
			fRec868[2] = fRec868[1];
			fRec868[1] = fRec868[0];
			fRec867[2] = fRec867[1];
			fRec867[1] = fRec867[0];
			fVec96[1] = fVec96[0];
			fRec866[1] = fRec866[0];
			fRec864[1] = fRec864[0];
			fRec871[1] = fRec871[0];
			fRec879[2] = fRec879[1];
			fRec879[1] = fRec879[0];
			fRec878[2] = fRec878[1];
			fRec878[1] = fRec878[0];
			fRec877[2] = fRec877[1];
			fRec877[1] = fRec877[0];
			fRec876[2] = fRec876[1];
			fRec876[1] = fRec876[0];
			fVec97[1] = fVec97[0];
			fRec875[1] = fRec875[0];
			fRec873[1] = fRec873[0];
			fRec880[1] = fRec880[0];
			fRec888[2] = fRec888[1];
			fRec888[1] = fRec888[0];
			fRec887[2] = fRec887[1];
			fRec887[1] = fRec887[0];
			fRec886[2] = fRec886[1];
			fRec886[1] = fRec886[0];
			fRec885[2] = fRec885[1];
			fRec885[1] = fRec885[0];
			fVec98[1] = fVec98[0];
			fRec884[1] = fRec884[0];
			fRec882[1] = fRec882[0];
			fRec889[1] = fRec889[0];
			fRec897[2] = fRec897[1];
			fRec897[1] = fRec897[0];
			fRec896[2] = fRec896[1];
			fRec896[1] = fRec896[0];
			fRec895[2] = fRec895[1];
			fRec895[1] = fRec895[0];
			fRec894[2] = fRec894[1];
			fRec894[1] = fRec894[0];
			fVec99[1] = fVec99[0];
			fRec893[1] = fRec893[0];
			fRec891[1] = fRec891[0];
			fRec898[1] = fRec898[0];
			fRec906[2] = fRec906[1];
			fRec906[1] = fRec906[0];
			fRec905[2] = fRec905[1];
			fRec905[1] = fRec905[0];
			fRec904[2] = fRec904[1];
			fRec904[1] = fRec904[0];
			fRec903[2] = fRec903[1];
			fRec903[1] = fRec903[0];
			fVec100[1] = fVec100[0];
			fRec902[1] = fRec902[0];
			fRec900[1] = fRec900[0];
			fRec907[1] = fRec907[0];
			fRec915[2] = fRec915[1];
			fRec915[1] = fRec915[0];
			fRec914[2] = fRec914[1];
			fRec914[1] = fRec914[0];
			fRec913[2] = fRec913[1];
			fRec913[1] = fRec913[0];
			fRec912[2] = fRec912[1];
			fRec912[1] = fRec912[0];
			fVec101[1] = fVec101[0];
			fRec911[1] = fRec911[0];
			fRec909[1] = fRec909[0];
			fRec916[1] = fRec916[0];
			fRec924[2] = fRec924[1];
			fRec924[1] = fRec924[0];
			fRec923[2] = fRec923[1];
			fRec923[1] = fRec923[0];
			fRec922[2] = fRec922[1];
			fRec922[1] = fRec922[0];
			fRec921[2] = fRec921[1];
			fRec921[1] = fRec921[0];
			fVec102[1] = fVec102[0];
			fRec920[1] = fRec920[0];
			fRec918[1] = fRec918[0];
			fRec925[1] = fRec925[0];
			fRec933[2] = fRec933[1];
			fRec933[1] = fRec933[0];
			fRec932[2] = fRec932[1];
			fRec932[1] = fRec932[0];
			fRec931[2] = fRec931[1];
			fRec931[1] = fRec931[0];
			fRec930[2] = fRec930[1];
			fRec930[1] = fRec930[0];
			fVec103[1] = fVec103[0];
			fRec929[1] = fRec929[0];
			fRec927[1] = fRec927[0];
			fRec934[1] = fRec934[0];
			fRec942[2] = fRec942[1];
			fRec942[1] = fRec942[0];
			fRec941[2] = fRec941[1];
			fRec941[1] = fRec941[0];
			fRec940[2] = fRec940[1];
			fRec940[1] = fRec940[0];
			fRec939[2] = fRec939[1];
			fRec939[1] = fRec939[0];
			fVec104[1] = fVec104[0];
			fRec938[1] = fRec938[0];
			fRec936[1] = fRec936[0];
			fRec943[1] = fRec943[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "polyphonic_detection.dsp"
	#define FAUST_CLASS_NAME "mydsp"
	#define FAUST_COMPILATION_OPIONS "-a /usr/local/share/faust/juce/juce-plugin.cpp -lang cpp -i -scn base_dsp -es 1 -mcd 16 -uim -single -ftz 0"
	#define FAUST_INPUTS 1
	#define FAUST_OUTPUTS 105
	#define FAUST_ACTIVES 4
	#define FAUST_PASSIVES 0

	FAUST_ADDHORIZONTALSLIDER("attack", fHslider3, 0.10000000000000001f, 0.050000000000000003f, 1.0f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("release", fHslider2, 0.10000000000000001f, 0.01f, 3.0f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("rms", fHslider0, 0.01f, 0.0001f, 0.10000000000000001f, 1.0000000000000001e-05f);
	FAUST_ADDHORIZONTALSLIDER("thresh", fHslider1, 0.001f, 0.0001f, 1.0f, 0.0001f);

	#define FAUST_LIST_ACTIVES(p) \
		p(HORIZONTALSLIDER, attack, "attack", fHslider3, 0.10000000000000001f, 0.050000000000000003f, 1.0f, 0.01f) \
		p(HORIZONTALSLIDER, release, "release", fHslider2, 0.10000000000000001f, 0.01f, 3.0f, 0.01f) \
		p(HORIZONTALSLIDER, rms, "rms", fHslider0, 0.01f, 0.0001f, 0.10000000000000001f, 1.0000000000000001e-05f) \
		p(HORIZONTALSLIDER, thresh, "thresh", fHslider1, 0.001f, 0.0001f, 1.0f, 0.0001f) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

#if defined(JUCE_POLY)

struct FaustSound : public juce::SynthesiserSound {
    
    bool appliesToNote (int /*midiNoteNumber*/) override        { return true; }
    bool appliesToChannel (int /*midiChannel*/) override        { return true; }
};

// An hybrid JUCE and Faust voice

class FaustVoice : public juce::SynthesiserVoice, public dsp_voice {
    
    private:
        
        std::unique_ptr<juce::AudioBuffer<FAUSTFLOAT>> fBuffer;
        
    public:
        
        FaustVoice(base_dsp* base_dsp):dsp_voice(base_dsp)
        {
            // Allocate buffer for mixing
            fBuffer = std::make_unique<juce::AudioBuffer<FAUSTFLOAT>>(base_dsp->getNumOutputs(), 8192);
            fDSP->init(juce::SynthesiserVoice::getSampleRate());
        }
        
        bool canPlaySound (juce::SynthesiserSound* sound) override
        {
            return dynamic_cast<FaustSound*> (sound) != nullptr;
        }
        
        void startNote (int midiNoteNumber,
                        float velocity,
                        juce::SynthesiserSound* s,
                        int currentPitchWheelPosition) override
        {
            // Note is triggered
            keyOn(midiNoteNumber, velocity);
        }
        
        void stopNote (float velocity, bool allowTailOff) override
        {
            keyOff(!allowTailOff);
        }
        
        void pitchWheelMoved (int newPitchWheelValue) override
        {
            // not implemented for now
        }
        
        void controllerMoved (int controllerNumber, int newControllerValue) override
        {
            // not implemented for now
        }
        
        void renderNextBlock (juce::AudioBuffer<FAUSTFLOAT>& outputBuffer,
                              int startSample,
                              int numSamples) override
        {
            // Only plays when the voice is active
            if (isVoiceActive()) {
                
                // Play the voice
                compute(numSamples, nullptr, (FAUSTFLOAT**)fBuffer->getArrayOfWritePointers());
                
                // Mix it in outputs
                for (int i = 0; i < fDSP->getNumOutputs(); i++) {
                    outputBuffer.addFrom(i, startSample, *fBuffer, i, 0, numSamples);
                }
            }
        }
    
};

// Decorates the JUCE Synthesiser and adds Faust polyphonic code for GUI handling

class FaustSynthesiser : public juce::Synthesiser, public dsp_voice_group {
    
    private:
        
        juce::Synthesiser fSynth;
    
        static void panic(float val, void* arg)
        {
            static_cast<FaustSynthesiser*>(arg)->allNotesOff(0, false); // 0 stops all voices
        }
  
    public:
        
        FaustSynthesiser():dsp_voice_group(panic, this, true, true)
        {
            setNoteStealingEnabled(true);
        }
        
        virtual ~FaustSynthesiser()
        {
            // Voices will be deallocated by fSynth
            dsp_voice_group::clearVoices();
        }
        
        void addVoice(FaustVoice* voice)
        {
            fSynth.addVoice(voice);
            dsp_voice_group::addVoice(voice);
        }
        
        void addSound(juce::SynthesiserSound* sound)
        {
            fSynth.addSound(sound);
        }
        
        void allNotesOff(int midiChannel, bool allowTailOff)
        {
            fSynth.allNotesOff(midiChannel, allowTailOff);
        }
        
        void setCurrentPlaybackSampleRate (double newRate)
        {
            fSynth.setCurrentPlaybackSampleRate(newRate);
        }
        
        void renderNextBlock (juce::AudioBuffer<float>& outputAudio,
                              const juce::MidiBuffer& inputMidi,
                              int startSample,
                              int numSamples)
        {
            fSynth.renderNextBlock(outputAudio, inputMidi, startSample, numSamples);
        }
        
        void renderNextBlock (juce::AudioBuffer<double>& outputAudio,
                              const juce::MidiBuffer& inputMidi,
                              int startSample,
                              int numSamples)
        {
            fSynth.renderNextBlock(outputAudio, inputMidi, startSample, numSamples);
        }
    
};

#endif

// Using the PluginGuiMagic project (https://foleysfinest.com/developer/pluginguimagic/)

#if defined(PLUGIN_MAGIC)

class FaustPlugInAudioProcessor : public foleys::MagicProcessor, private juce::Timer
{
    
    public:
        FaustPlugInAudioProcessor();
        virtual ~FaustPlugInAudioProcessor() {}
        
        void prepareToPlay (double sampleRate, int samplesPerBlock) override;
        
        bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
        
        void processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages) override
        {
            jassert (! isUsingDoublePrecision());
            process (buffer, midiMessages);
    #ifdef MAGIC_LEVEL_SOURCE
            fOutputMeter->pushSamples(buffer);
    #endif
        }
        
        void processBlock (juce::AudioBuffer<double>& buffer, juce::MidiBuffer& midiMessages) override
        {
            jassert (isUsingDoublePrecision());
            process (buffer, midiMessages);
        }
        
        const juce::String getName() const override;
        
        bool acceptsMidi() const override;
        bool producesMidi() const override;
        double getTailLengthSeconds() const override;
        
        int getNumPrograms() override;
        int getCurrentProgram() override;
        void setCurrentProgram (int index) override;
        const juce::String getProgramName (int index) override;
        void changeProgramName (int index, const juce::String& newName) override;
        
        void releaseResources() override
        {}
        
        void timerCallback() override;
        
        juce::AudioProcessor::BusesProperties getBusesProperties();
        bool supportsDoublePrecisionProcessing() const override;
      
    #ifdef MAGIC_LEVEL_SOURCE
        foleys::MagicLevelSource* fOutputMeter = nullptr;
    #endif
        juce::AudioProcessorValueTreeState treeState{ *this, nullptr };
    
    #ifdef JUCE_POLY
        std::unique_ptr<FaustSynthesiser> fSynth;
    #else
    #if defined(MIDICTRL)
        std::unique_ptr<juce_midi_handler> fMIDIHandler;
        std::unique_ptr<MidiUI> fMIDIUI;
    #endif
        std::unique_ptr<base_dsp> fDSP;
    #endif
        
    #if defined(OSCCTRL)
        std::unique_ptr<JuceOSCUI> fOSCUI;
    #endif
        
    #if defined(SOUNDFILE)
        std::unique_ptr<SoundUI> fSoundUI;
    #endif
        
        JuceStateUI fStateUI;
        JuceParameterUI fParameterUI;
        
        bool fIsPrepared = false;
        
    private:
        
        template <typename FloatType>
        void process (juce::AudioBuffer<FloatType>& buffer, juce::MidiBuffer& midiMessages);
        
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FaustPlugInAudioProcessor)
    
};

#else

class FaustPlugInAudioProcessor : public juce::AudioProcessor, private juce::Timer
{

    public:
        
        FaustPlugInAudioProcessor();
        virtual ~FaustPlugInAudioProcessor() {}
        
        void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    
        bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
        
        void processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages) override
        {
            jassert (! isUsingDoublePrecision());
            process (buffer, midiMessages);
        }
        
        void processBlock (juce::AudioBuffer<double>& buffer, juce::MidiBuffer& midiMessages) override
        {
            jassert (isUsingDoublePrecision());
            process (buffer, midiMessages);
        }
    
        juce::AudioProcessorEditor* createEditor() override;
        bool hasEditor() const override;
        
        const juce::String getName() const override;
        
        bool acceptsMidi() const override;
        bool producesMidi() const override;
        double getTailLengthSeconds() const override;
        
        int getNumPrograms() override;
        int getCurrentProgram() override;
        void setCurrentProgram (int index) override;
        const juce::String getProgramName (int index) override;
        void changeProgramName (int index, const juce::String& newName) override;
        
        void getStateInformation (juce::MemoryBlock& destData) override;
        void setStateInformation (const void* data, int sizeInBytes) override;
    
        void releaseResources() override
        {}
        
        void timerCallback() override;
    
        juce::AudioProcessor::BusesProperties getBusesProperties();
        bool supportsDoublePrecisionProcessing() const override;
    
    #ifdef JUCE_POLY
        std::unique_ptr<FaustSynthesiser> fSynth;
    #else
    #if defined(MIDICTRL)
        std::unique_ptr<juce_midi_handler> fMIDIHandler;
        std::unique_ptr<MidiUI> fMIDIUI;
    #endif
        std::unique_ptr<base_dsp> fDSP;
    #endif
        
    #if defined(OSCCTRL)
        std::unique_ptr<JuceOSCUI> fOSCUI;
    #endif
    
    #if defined(SOUNDFILE)
        std::unique_ptr<SoundUI> fSoundUI;
    #endif
    
        JuceStateUI fStateUI;
        JuceParameterUI fParameterUI;
    
        bool fIsPrepared = false;
    
    private:
    
        template <typename FloatType>
        void process (juce::AudioBuffer<FloatType>& buffer, juce::MidiBuffer& midiMessages);
    
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FaustPlugInAudioProcessor)
    
};

#endif

class FaustPlugInAudioProcessorEditor : public juce::AudioProcessorEditor
{
    
    public:
        
        FaustPlugInAudioProcessorEditor (FaustPlugInAudioProcessor&);
        virtual ~FaustPlugInAudioProcessorEditor() {}
        
        void paint (juce::Graphics&) override;
        void resized() override;
        
    private:
        
        // This reference is provided as a quick way for your editor to
        // access the processor object that created it.
        FaustPlugInAudioProcessor& processor;
        
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FaustPlugInAudioProcessorEditor)
#ifndef PLUGIN_MAGIC        
        JuceGUI fJuceGUI;
#endif    
};

#ifndef PLUGIN_MAGIC
FaustPlugInAudioProcessor::FaustPlugInAudioProcessor()
: juce::AudioProcessor (getBusesProperties()), fParameterUI(this)
#else
FaustPlugInAudioProcessor::FaustPlugInAudioProcessor()
: foleys::MagicProcessor (getBusesProperties()), fParameterUI(this)	
#endif
{
    bool midi_sync = false;
    int nvoices = 0;
    
    mydsp* tmp_dsp = new mydsp();
    MidiMeta::analyse(tmp_dsp, midi_sync, nvoices);
    delete tmp_dsp;
	
#ifdef PLUGIN_MAGIC
#ifdef MAGIC_LOAD_BINARY
    // change magic_xml and magic_xmlSize to match the name of your included
    // XML file from Plugin GUI Magic
    magicState.setGuiValueTree(BinaryData::magic_xml, BinaryData::magic_xmlSize);
#endif
// put other GUI Magic sources here, similar to expression below.
#ifdef MAGIC_LEVEL_SOURCE
    fOutputMeter = magicState.createAndAddObject<foleys::MagicLevelSource>("output");
#endif
#endif
   
#ifdef JUCE_POLY
    assert(nvoices > 0);
    fSynth = std::make_unique<FaustSynthesiser>();
    for (int i = 0; i < nvoices; i++) {
        fSynth->addVoice(new FaustVoice(new mydsp()));
    }
    fSynth->init();
    fSynth->addSound(new FaustSound());
#else
    
    bool group = true;
    
#ifdef POLY2
    assert(nvoices > 0);
    std::cout << "Started with " << nvoices << " voices\n";
    base_dsp* base_dsp = new mydsp_poly(new mydsp(), nvoices, true, group);
    
#if MIDICTRL
    if (midi_sync) {
        fDSP = std::make_unique<timed_dsp>(new dsp_sequencer(base_dsp, new effect()));
    } else {
        fDSP = std::make_unique<dsp_sequencer>(base_dsp, new effect());
    }
#else
    fDSP = std::make_unique<dsp_sequencer>(base_dsp, new effects());
#endif
    
#else
    if (nvoices > 0) {
        std::cout << "Started with " << nvoices << " voices\n";
        base_dsp* base_dsp = new mydsp_poly(new mydsp(), nvoices, true, group);
        
#if MIDICTRL
        if (midi_sync) {
            fDSP = std::make_unique<timed_dsp>(base_dsp);
        } else {
            fDSP = std::make_unique<decorator_dsp>(base_dsp);
        }
#else
        fDSP = std::make_unique<decorator_dsp>(base_dsp);
#endif
    } else {
#if MIDICTRL
        if (midi_sync) {
            fDSP = std::make_unique<timed_dsp>(new mydsp());
        } else {
            fDSP = std::make_unique<mydsp>();
        }
#else
        fDSP = std::make_unique<mydsp>();
#endif
    }
    
#endif
    
#if defined(MIDICTRL)
    fMIDIHandler = std::make_unique<juce_midi_handler>();
    fMIDIUI = std::make_unique<MidiUI>(fMIDIHandler.get());
    fDSP->buildUserInterface(fMIDIUI.get());
    if (!fMIDIUI->run()) {
        std::cerr << "JUCE MIDI handler cannot be started..." << std::endl;
    }
#endif
    
#endif
    
#if defined(OSCCTRL)
    fOSCUI = std::make_unique<JuceOSCUI>("127.0.0.1", 5510, 5511);
#ifdef JUCE_POLY
    fSynth->buildUserInterface(fOSCUI.get());
#else
    fDSP->buildUserInterface(fOSCUI.get());
#endif
    if (!fOSCUI->run()) {
        std::cerr << "JUCE OSC handler cannot be started..." << std::endl;
    }
#endif
    
#if defined(SOUNDFILE)
    // Use bundle path
    auto file = juce::File::getSpecialLocation(juce::File::currentExecutableFile)
        .getParentDirectory().getParentDirectory().getChildFile("Resources");
    fSoundUI = std::make_unique<SoundUI>(file.getFullPathName().toStdString());
    fDSP->buildUserInterface(fSoundUI.get());
#endif
    
#ifdef JUCE_POLY
    fSynth->buildUserInterface(&fStateUI);
    fSynth->buildUserInterface(&fParameterUI);
    // When no previous state was restored, init DSP controllers with their default values
    if (!fStateUI.fRestored) {
        fSynth->instanceResetUserInterface();
    }
#else
    fDSP->buildUserInterface(&fStateUI);
    fDSP->buildUserInterface(&fParameterUI);
    // When no previous state was restored, init DSP controllers with their default values
    if (!fStateUI.fRestored) {
        fDSP->instanceResetUserInterface();
    }
#endif
    
    startTimerHz(25);
}

juce::AudioProcessor::BusesProperties FaustPlugInAudioProcessor::getBusesProperties()
{
    if (juce::PluginHostType::getPluginLoadedAs() == wrapperType_Standalone) {
        if (FAUST_INPUTS == 0) {
            return BusesProperties().withOutput("Output", juce::AudioChannelSet::discreteChannels(std::min<int>(2, FAUST_OUTPUTS)), true);
        } else {
            return BusesProperties()
            .withInput("Input", juce::AudioChannelSet::discreteChannels(std::min<int>(2, FAUST_INPUTS)), true)
            .withOutput("Output", juce::AudioChannelSet::discreteChannels(std::min<int>(2, FAUST_OUTPUTS)), true);
        }
    } else {
        if (FAUST_INPUTS == 0) {
            return BusesProperties().withOutput("Output", juce::AudioChannelSet::discreteChannels(FAUST_OUTPUTS), true);
        } else {
            return BusesProperties()
            .withInput("Input", juce::AudioChannelSet::discreteChannels(FAUST_INPUTS), true)
            .withOutput("Output", juce::AudioChannelSet::discreteChannels(FAUST_OUTPUTS), true);
        }
    }
}

void FaustPlugInAudioProcessor::timerCallback()
{
    GUI::updateAllGuis();
}

//==============================================================================
const juce::String FaustPlugInAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FaustPlugInAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool FaustPlugInAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

double FaustPlugInAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FaustPlugInAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int FaustPlugInAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FaustPlugInAudioProcessor::setCurrentProgram (int index)
{}

const juce::String FaustPlugInAudioProcessor::getProgramName (int index)
{
    return juce::String();
}

void FaustPlugInAudioProcessor::changeProgramName (int index, const juce::String& newName)
{}

bool FaustPlugInAudioProcessor::supportsDoublePrecisionProcessing() const
{
    return sizeof(FAUSTFLOAT) == 8;
}

//==============================================================================
void FaustPlugInAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // prepareToPlay may be called several times (like in VST3 context)
    if (fIsPrepared) return;
    
    // Use this method as the place to do any pre-playback
    // initialisation that you need...
    
    fIsPrepared = true;
    
#ifdef JUCE_POLY
    fSynth->setCurrentPlaybackSampleRate (sampleRate);
#else
    
    // Possible sample size adaptation
    if (sizeof(FAUSTFLOAT) == 8) {
        fDSP = std::make_unique<dsp_sample_adapter<FAUSTFLOAT, float>>(fDSP.release());
    }
    
    // Possibly adapt DSP inputs/outputs number
    if (fDSP->getNumInputs() > getTotalNumInputChannels() || fDSP->getNumOutputs() > getTotalNumOutputChannels()) {
        fDSP = std::make_unique<dsp_adapter>(fDSP.release(), getTotalNumInputChannels(), getTotalNumOutputChannels(), 4096);
    }
   
    // Setting the DSP control values has already been done
    // by 'buildUserInterface(&fStateUI)', using the saved values or the default ones.
    // What has to be done to finish the DSP initialization is done now.
    mydsp::classInit(int(sampleRate));
    fDSP->instanceConstants(int(sampleRate));
    fDSP->instanceClear();
    
#endif
#ifdef MAGIC_LEVEL_SOURCE
    magicState.prepareToPlay(sampleRate, samplesPerBlock);
    fOutputMeter->setupSource(getMainBusNumOutputChannels(), sampleRate, 500, 200);
#endif
}

bool FaustPlugInAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
#ifdef JUCE_POLY
    return true;
#else
    
#if JucePlugin_IsSynth
    // Stereo is supported
    return (layouts.getMainOutputChannelSet().size() == 2) || (layouts.getMainOutputChannelSet().size() == fDSP->getNumOutputs());
#else
    // Stereo is supported
    return
    ((layouts.getMainInputChannelSet().size() == 2) && (layouts.getMainOutputChannelSet().size() == 2))
    ||
    ((layouts.getMainInputChannelSet().size() == fDSP->getNumInputs()) && (layouts.getMainOutputChannelSet().size() == fDSP->getNumOutputs()));
#endif
    
#endif
}

template <typename FloatType>
void FaustPlugInAudioProcessor::process (juce::AudioBuffer<FloatType>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    
#ifdef JUCE_POLY
    fSynth->renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
#else
#if defined(MIDICTRL)
    // Read MIDI input events from midiMessages
    fMIDIHandler->decodeBuffer(midiMessages);
    // Then write MIDI output events to midiMessages
    fMIDIHandler->encodeBuffer(midiMessages);
#endif
    // MIDI timestamp is expressed in frames
    fDSP->compute(-1, buffer.getNumSamples(),
                  (FAUSTFLOAT**)buffer.getArrayOfReadPointers(),
                  (FAUSTFLOAT**)buffer.getArrayOfWritePointers());
#endif
}

//==============================================================================
#ifndef PLUGIN_MAGIC
bool FaustPlugInAudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* FaustPlugInAudioProcessor::createEditor()
{
    return new FaustPlugInAudioProcessorEditor (*this);
}

//==============================================================================
void FaustPlugInAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    
    fStateUI.getStateInformation(destData);
}

void FaustPlugInAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    
    fStateUI.setStateInformation(data, sizeInBytes);
 }
#endif
//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FaustPlugInAudioProcessor();
}

//==============================================================================
#ifndef PLUGIN_MAGIC
FaustPlugInAudioProcessorEditor::FaustPlugInAudioProcessorEditor (FaustPlugInAudioProcessor& p)
: juce::AudioProcessorEditor (&p), processor (p)
{
#ifdef JUCE_POLY
    p.fSynth->buildUserInterface(&fJuceGUI);
#else
    p.fDSP->buildUserInterface(&fJuceGUI);
#endif
    
    addAndMakeVisible(fJuceGUI);
    
    juce::Rectangle<int> recommendedSize = fJuceGUI.getSize();
    setSize (recommendedSize.getWidth(), recommendedSize.getHeight());
}

//==============================================================================
void FaustPlugInAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::white);
}

void FaustPlugInAudioProcessorEditor::resized()
{
    fJuceGUI.setBounds(getLocalBounds());
}

#endif
// Globals
std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

#endif
