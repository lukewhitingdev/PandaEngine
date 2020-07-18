#pragma once
#include <vector>
#include "GameObject.h"
#include "objectIncludes.h"
namespace PandaEngine {
	class objectManager
	{
	public:
		objectManager();

		void setDevice(ID3D11Device* device) { _device = device; }

		// Creators
		void createCubeGameObject(Transform* transform, const wchar_t* texfileName) { _objectVector.push_back(new GameObject(transform, new cube(_device, texfileName))); };
		void createCylinderGameObject(Transform* transform, const wchar_t* texfileName){ _objectVector.push_back(new GameObject(transform, new cylinder(_device, texfileName))); };
		void createSphereGameObject(Transform* transform, const wchar_t* texfileName){ _objectVector.push_back(new GameObject(transform, new sphere(_device, texfileName))); };
		void createTorusGameObject(Transform* transform, const wchar_t* texfileName){ _objectVector.push_back(new GameObject(transform, new torus(_device, texfileName))); };
		void createCustomGameObject(Transform* transform, char* objfileName, bool rHand, Mesh::meshType mType){ _objectVector.push_back(new GameObject(transform, new customModel(_device, objfileName, rHand, mType))); };
		void createCustomGameObject(Transform* transform, const wchar_t* texfileName, char* objfileName, Mesh::meshType mType){ _objectVector.push_back(new GameObject(transform, new customModel(_device, texfileName, objfileName, mType))); };
		void createCustomGameObject(Transform* transform, const wchar_t* texfileName, char* objfileName, bool rHand) { _objectVector.push_back(new GameObject(transform, new customModel(_device, texfileName, objfileName, rHand))); };;

		size_t objectCount() { return _objectVector.size(); };
		GameObject* getObjectAtIndex(int index) { return _objectVector[index]; };
		std::vector<GameObject*> getObjectVector() { return _objectVector; };

	private:
		std::vector<GameObject*> _objectVector;
		ID3D11Device* _device;
	};
}

