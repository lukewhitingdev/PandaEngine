#pragma once
#include "UI.h"
#include "Vector3D.h"
#include <string>
#include <vector>

class InspectorUI : public PandaEngine::UI
{
private:


public:
	//enum UITypes {
	//	TEXT,
	//	SLIDER,
	//	COLORSLIDER,
	//	BUTTON
	//};

	void addSection(std::string sectionName);
	void removeSection(std::string sectionName);

	void addComponentToSection(std::string section, std::string componentName, std::string componentValue);
	void addComponentToSection(std::string section, std::string componentName, int componentValue);
	void addComponentToSection(std::string section, std::string componentName, float componentValue);
	void addComponentToSection(std::string section, std::string componentName, Vector3D componentValue);
	void addComponentToSection(std::string section, std::string componentName, bool componentValue);
	InspectorUI();
	void render();
};

