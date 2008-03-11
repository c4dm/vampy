/*
    Vamp

    An API for audio analysis and feature extraction plugins.

    Centre for Digital Music, Queen Mary, University of London.
    Copyright 2006 Chris Cannam.
  
    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use, copy,
    modify, merge, publish, distribute, sublicense, and/or sell copies
    of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR
    ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
    CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

    Except as contained in this notice, the names of the Centre for
    Digital Music; Queen Mary, University of London; and Chris Cannam
    shall not be used in advertising or otherwise to promote the sale,
    use or other dealings in this Software without prior written
    authorization.
*/

	/**
	 * This plugin abstracts appropriate Python Scripts as a VAMP plugin.
	*/

#ifndef _PYTHON_WRAPPER_PLUGIN_H_
#define _PYTHON_WRAPPER_PLUGIN_H_

#include "vamp-sdk/Plugin.h"
#include "/usr/include/python/Python.h"

//fields in OutputDescriptor
enum eOutDescriptors {
	not_found,
	identifier,
	name,
	description,
	unit, 
	hasFixedBinCount,
	binCount,
	binNames,
	hasKnownExtents,
	minValue,
	maxValue,
	isQuantized,
	quantizeStep,
	sampleType,	
	sampleRate,
	endNode
	}; 

namespace p {
enum eParmDescriptors {
	not_found,
	identifier,
	name,
	description,
	unit, 
	minValue,
	maxValue,
	defaultValue,
	isQuantized
	};
}

enum eSampleTypes {
	OneSamplePerStep,
	FixedSampleRate,
	VariableSampleRate
	};

enum eFeatureFields {
	unknown,
	hasTimestamp,
	timeStamp,
	values,
	label
	};


class PyPlugin : public Vamp::Plugin
{
public:
    PyPlugin(std::string plugin,float inputSampleRate, PyObject *pyInstance);
    virtual ~PyPlugin();

    bool initialise(size_t channels, size_t stepSize, size_t blockSize);
    void reset();
	//virtuals:
	InputDomain getInputDomain() const;
	size_t getPreferredBlockSize() const;
	size_t getPreferredStepSize() const; 
	size_t getMinChannelCount() const; 
	size_t getMaxChannelCount() const;

    std::string getIdentifier() const;
    std::string getName() const;
    std::string getDescription() const;
    std::string getMaker() const;
    int getPluginVersion() const;
    std::string getCopyright() const;
 
    OutputList getOutputDescriptors() const;
    ParameterList getParameterDescriptors() const;
	float getParameter(std::string paramid) const;
	void setParameter(std::string paramid, float newval);
    
FeatureSet process(const float *const *inputBuffers,
                       Vamp::RealTime timestamp);

    FeatureSet getRemainingFeatures();

protected:
	PyObject *m_pyInstance;
    size_t m_stepSize;
    float m_previousSample;
	std::string m_plugin;
	std::string m_class;
	std::string m_path;
};


#endif
