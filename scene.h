#pragma once

#include <list>
#include <vector>
#include <typeinfo>
#include "main.h"
#include "camera.h"
#include "field.h"
#include "model.h"
#include "player.h"
#include "polygon.h"
#include "enemy.h"

class CScene
{
protected:
	std::list<GameObject*> gameObjects[5];
public:
	CScene() {}
	virtual ~CScene() {}

	template <typename T>
	T* AddGameObject(int layer)
	{
		T* object = new T();
		object->Init();
		gameObjects[layer].push_back(object);
		return object;
	}
	template <typename T>
	T* GetGameObject(int layer)
	{
		for (GameObject* object : gameObjects[layer])
		{
			if (typeid(*object) == typeid(T))
			{
				return (T*)object;
			}
		}
		return nullptr;
	}

	template <typename T>
	std::vector<T*> GetGameObjects(int layer)
	{
		std::vector<T*> objects;
		for (GameObject* object : gameObjects[layer])
		{
			if (typeid(*object) == typeid(T))
			{
				objects.push_back((T*)object);
			}
		}
		return objects;
	}

	void DestroyGameObject(GameObject* gameObject)
	{
		gameObject->SetDestroy();
	}

	virtual void Init()
	{
		AddGameObject<CCamera>(0);
		AddGameObject<CField>(0);
		AddGameObject<Enemy>(0);
		AddGameObject<Enemy>(0);
		AddGameObject<Enemy>(0);
		AddGameObject<Enemy>(0);
		AddGameObject<Enemy>(0);
		AddGameObject<Player>(0);
		AddGameObject<CPolygon>(4);
	}
	virtual void Uninit()
	{
		for (int i = 0; i < 5; i++)
		{
			for (GameObject* object : gameObjects[i])
			{
				object->Uninit();
				delete object;
			}
			gameObjects[i].clear();
		}
	}
	virtual void Update()
	{
		for (int i = 0; i < 5; i++)
		{
			for (GameObject* object : gameObjects[i])
			{
				object->Update();
			}
			gameObjects[i].remove_if([](GameObject* object){return object->Destroy();}); // [] = ���O�̂Ȃ��֐������
		}
	}
	virtual void Draw()
	{
		for (int i = 0; i < 5; i++)
		{
			for (GameObject* object : gameObjects[i])
			{
				object->Draw();
			}
		}
	}
};