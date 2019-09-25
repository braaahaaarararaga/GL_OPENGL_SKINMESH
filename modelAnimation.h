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
		aiMatrix4x4 Matrix;				// �ŏI�I�ȃ}�g���b�N�X
		aiMatrix4x4 AnimationMatrix;	// ���̉�]�ʂ�matrix
		aiMatrix4x4 OffsetMatrix;		// ���_���炸��̗ʂ�matrix
	};
	struct DEFORM_VERTEX
	{
		aiVector3D Position;
		aiVector3D DeformPosition;
		aiVector3D Normal;
		aiVector3D DeformNormal;
		std::string BoneName[4]; // �{���͖��O�ł͂Ȃ��C���f�b�N�X�ŊǗ�����
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