#pragma once
#include "main.h"
#include "input.h"
#include <map>
#include <vector>
#include "texture.h"



class ModelAnimation
{

	struct BONE
	{
		aiMatrix4x4 Matrix;				// 最終的なマトリックス
		aiMatrix4x4 AnimationMatrix;	// 骨の回転量のmatrix
		aiMatrix4x4 OffsetMatrix;		// 原点からずれの量のmatrix
	};
	struct DEFORM_VERTEX
	{
		aiVector3D Position;
		aiVector3D DeformPosition;
		aiVector3D Normal;
		aiVector3D DeformNormal;
		std::string BoneName[4]; // 本来は名前ではなくインデックスで管理する
		float BoneWeight[4];
		int BoneNum;
	};

	std::vector<DEFORM_VERTEX>* g_DeformVertex;
	std::map<std::string, BONE> g_Bone;
	const aiScene* g_Scene = nullptr;
	unsigned int g_Frame = 0;

	void UpdateBoneMatrix(aiNode* Node, aiMatrix4x4 Matrix);
	void DrawMesh(const aiNode* Node);
	void CreateBone(aiNode* Node);
public:
	ModelAnimation(const char* filepath);
	void Draw();
	void Update();
	~ModelAnimation();
};