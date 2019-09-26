
#include "modelAnimation.h"

aiMatrix4x4 matXfloat(aiMatrix4x4 mat, float f)
{
	mat.a1 *= f;
	mat.a2 *= f;
	mat.a3 *= f;
	mat.a4 *= f;
	mat.b1 *= f;
	mat.b2 *= f;
	mat.b3 *= f;
	mat.b4 *= f;
	mat.c1 *= f;
	mat.c2 *= f;
	mat.c3 *= f;
	mat.c4 *= f;
	mat.d1 *= f;
	mat.d2 *= f;
	mat.d3 *= f;
	mat.d4 *= f;
	return mat;
}



void ModelAnimation::UpdateBoneMatrix(aiNode * Node, aiMatrix4x4 Matrix)
{
	BONE* bone = &g_Bone[Node->mName.C_Str()];
	aiMatrix4x4 world;
	world = Matrix * bone->AnimationMatrix;
	bone->Matrix = world * bone->OffsetMatrix;
	for (int i = 0; i < Node->mNumChildren; i++)
	{
		UpdateBoneMatrix(Node->mChildren[i], world);
	}
}

void ModelAnimation::DrawMesh(const aiNode * Node)
{
	aiMatrix4x4 matrix = Node->mTransformation;
	aiTransposeMatrix4(&matrix);
	glPushMatrix();
	glScalef(.2f, .2f, .2f);
	glMultMatrixf((float*)&matrix);

	for (int n = 0; n < Node->mNumMeshes; n++)
	{
		unsigned int m = Node->mMeshes[n];
		aiMesh* mesh = g_Scene->mMeshes[m];
		std::vector<DEFORM_VERTEX>* vertices = &g_DeformVertex[m];

		glBegin(GL_TRIANGLES);
		for (int f = 0; f < mesh->mNumFaces; f++)
		{
			aiFace* face = &mesh->mFaces[f];
			for (int i = 0; i < face->mNumIndices; i++)
			{
				int index = face->mIndices[i];
				DEFORM_VERTEX* vertex = &(*vertices)[index];
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				glNormal3f(vertex->DeformNormal.x, vertex->DeformNormal.y, vertex->DeformNormal.z);
				glVertex3f(vertex->DeformPosition.x, vertex->DeformPosition.y, vertex->DeformPosition.z);

			}
		}
		glEnd();
	}
	for (int n = 0; n < Node->mNumChildren; n++)
	{
		DrawMesh(Node->mChildren[n])
			;
	}
	glPopMatrix();
}

void ModelAnimation::CreateBone(aiNode * Node)
{
	BONE bone;
	g_Bone[Node->mName.C_Str()] = bone;
	for (int i = 0; i < Node->mNumChildren; i++)
	{
		CreateBone(Node->mChildren[i]);
	}
}

ModelAnimation::ModelAnimation(const char * filepath)
{
	g_Scene = aiImportFile(filepath, aiProcessPreset_TargetRealtime_MaxQuality);
	CreateBone(g_Scene->mRootNode);
	g_DeformVertex = new std::vector<DEFORM_VERTEX>[g_Scene->mNumMeshes];


	for (int m = 0; m < g_Scene->mNumMeshes; m++)
	{
		aiMesh* mesh = g_Scene->mMeshes[m];
		for (int v = 0; v < mesh->mNumVertices; v++)
		{
			DEFORM_VERTEX vertex;
			vertex.Position = mesh->mVertices[v];
			vertex.DeformPosition = mesh->mVertices[v];
			vertex.Normal = mesh->mNormals[v];
			vertex.DeformNormal = mesh->mNormals[v];
			for (unsigned int b = 0; b < 4; b++)
			{
				vertex.BoneName[b] = "";
				vertex.BoneWeight[b] = 0.0f;
			}
			vertex.BoneNum = 0;
			g_DeformVertex[m].push_back(vertex);
		}
		for (unsigned int b = 0; b < mesh->mNumBones; b++)
		{
			aiBone* bone = mesh->mBones[b];
			g_Bone[bone->mName.C_Str()].OffsetMatrix = bone->mOffsetMatrix;
			for (unsigned int w = 0; w < bone->mNumWeights; w++)
			{
				aiVertexWeight weight = bone->mWeights[w];
				g_DeformVertex[m][weight.mVertexId].BoneName[g_DeformVertex[m][weight.mVertexId].BoneNum] = bone->mName.C_Str();
				g_DeformVertex[m][weight.mVertexId].BoneWeight[g_DeformVertex[m][weight.mVertexId].BoneNum] = weight.mWeight;
				g_DeformVertex[m][weight.mVertexId].BoneNum++;
			}
		}

		/*if (g_Scene->mMaterials[m]->GetTexture(--)--)
		{
			if (path.data[0] == '*')
			{
				int id = atoi(&path.data[1]);
				g_Texture[--] = LoadTextureFromMemory((const unsigned char*)g_Scene->mTextures[id]->pcData,
					g_Scene->mTextures[id]->mWidth);
			}
		}*/
	}
}

void ModelAnimation::Draw()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	// matrix setting
	DrawMesh(g_Scene->mRootNode);
	glPopMatrix();
}

void ModelAnimation::Update()
{
	g_Frame += 1;
	aiAnimation* animation = g_Scene->mAnimations[0];
	for (unsigned int c = 0; c < animation->mNumChannels; c++)
	{
		aiNodeAnim* nodeAnim = animation->mChannels[c];
		BONE* bone = &g_Bone[nodeAnim->mNodeName.C_Str()];
		int f = g_Frame % nodeAnim->mNumRotationKeys;
		aiQuaternion rot = nodeAnim->mRotationKeys[f].mValue;
		f = g_Frame % nodeAnim->mNumPositionKeys;
		aiVector3D pos = nodeAnim->mPositionKeys[f].mValue;
		bone->AnimationMatrix = aiMatrix4x4(aiVector3D(1.0f, 1.0f, 1.0f), rot, pos);
	}
	UpdateBoneMatrix(g_Scene->mRootNode, aiMatrix4x4());
	for (unsigned int m = 0; m < g_Scene->mNumMeshes; m++)
	{
		for (auto& vertex : g_DeformVertex[m])
		{
			aiMatrix4x4 matrix[4];
			aiMatrix4x4 outMatrix;
			matrix[0] = g_Bone[vertex.BoneName[0]].Matrix;
			matrix[1] = g_Bone[vertex.BoneName[1]].Matrix;
			matrix[2] = g_Bone[vertex.BoneName[2]].Matrix;
			matrix[3] = g_Bone[vertex.BoneName[3]].Matrix;
			outMatrix.a1 = matXfloat(matrix[0], vertex.BoneWeight[0]).a1
						 + matXfloat(matrix[1], vertex.BoneWeight[1]).a1
						 + matXfloat(matrix[2], vertex.BoneWeight[2]).a1
						 + matXfloat(matrix[3], vertex.BoneWeight[3]).a1;

			outMatrix.a2 = matXfloat(matrix[0], vertex.BoneWeight[0]).a2
						 + matXfloat(matrix[1], vertex.BoneWeight[1]).a2
						 + matXfloat(matrix[2], vertex.BoneWeight[2]).a2
						 + matXfloat(matrix[3], vertex.BoneWeight[3]).a2;

			outMatrix.a3 = matXfloat(matrix[0], vertex.BoneWeight[0]).a3
						 + matXfloat(matrix[1], vertex.BoneWeight[1]).a3
						 + matXfloat(matrix[2], vertex.BoneWeight[2]).a3
						 + matXfloat(matrix[3], vertex.BoneWeight[3]).a3;

			outMatrix.a4 = matXfloat(matrix[0], vertex.BoneWeight[0]).a4
						 + matXfloat(matrix[1], vertex.BoneWeight[1]).a4
						 + matXfloat(matrix[2], vertex.BoneWeight[2]).a4
						 + matXfloat(matrix[3], vertex.BoneWeight[3]).a4;

			outMatrix.b1 = matXfloat(matrix[0], vertex.BoneWeight[0]).b1
						 + matXfloat(matrix[1], vertex.BoneWeight[1]).b1
						 + matXfloat(matrix[2], vertex.BoneWeight[2]).b1
						 + matXfloat(matrix[3], vertex.BoneWeight[3]).b1;

			outMatrix.b2 = matXfloat(matrix[0], vertex.BoneWeight[0]).b2
						 + matXfloat(matrix[1], vertex.BoneWeight[1]).b2
						 + matXfloat(matrix[2], vertex.BoneWeight[2]).b2
						 + matXfloat(matrix[3], vertex.BoneWeight[3]).b2;

			outMatrix.b3 = matXfloat(matrix[0], vertex.BoneWeight[0]).b3
						 + matXfloat(matrix[1], vertex.BoneWeight[1]).b3
						 + matXfloat(matrix[2], vertex.BoneWeight[2]).b3
						 + matXfloat(matrix[3], vertex.BoneWeight[3]).b3;

			outMatrix.b4 = matXfloat(matrix[0], vertex.BoneWeight[0]).b4
						 + matXfloat(matrix[1], vertex.BoneWeight[1]).b4
						 + matXfloat(matrix[2], vertex.BoneWeight[2]).b4
						 + matXfloat(matrix[3], vertex.BoneWeight[3]).b4;

			outMatrix.c1 = matXfloat(matrix[0], vertex.BoneWeight[0]).c1
						 + matXfloat(matrix[1], vertex.BoneWeight[1]).c1
						 + matXfloat(matrix[2], vertex.BoneWeight[2]).c1
						 + matXfloat(matrix[3], vertex.BoneWeight[3]).c1;

			outMatrix.c2 = matXfloat(matrix[0], vertex.BoneWeight[0]).c2
						 + matXfloat(matrix[1], vertex.BoneWeight[1]).c2
						 + matXfloat(matrix[2], vertex.BoneWeight[2]).c2
						 + matXfloat(matrix[3], vertex.BoneWeight[3]).c2;

			outMatrix.c3 = matXfloat(matrix[0], vertex.BoneWeight[0]).c3
						 + matXfloat(matrix[1], vertex.BoneWeight[1]).c3
						 + matXfloat(matrix[2], vertex.BoneWeight[2]).c3
						 + matXfloat(matrix[3], vertex.BoneWeight[3]).c3;

			outMatrix.c4 = matXfloat(matrix[0], vertex.BoneWeight[0]).c4
						 + matXfloat(matrix[1], vertex.BoneWeight[1]).c4
						 + matXfloat(matrix[2], vertex.BoneWeight[2]).c4
						 + matXfloat(matrix[3], vertex.BoneWeight[3]).c4;

			outMatrix.d1 = matXfloat(matrix[0], vertex.BoneWeight[0]).d1
						 + matXfloat(matrix[1], vertex.BoneWeight[1]).d1
						 + matXfloat(matrix[2], vertex.BoneWeight[2]).d1
						 + matXfloat(matrix[3], vertex.BoneWeight[3]).d1;

			outMatrix.d2 = matXfloat(matrix[0], vertex.BoneWeight[0]).d2
						 + matXfloat(matrix[1], vertex.BoneWeight[1]).d2
						 + matXfloat(matrix[2], vertex.BoneWeight[2]).d2
						 + matXfloat(matrix[3], vertex.BoneWeight[3]).d2;

			outMatrix.d3 = matXfloat(matrix[0], vertex.BoneWeight[0]).d3
						 + matXfloat(matrix[1], vertex.BoneWeight[1]).d3
						 + matXfloat(matrix[2], vertex.BoneWeight[2]).d3
						 + matXfloat(matrix[3], vertex.BoneWeight[3]).d3;

			outMatrix.d4 = matXfloat(matrix[0], vertex.BoneWeight[0]).d4
						 + matXfloat(matrix[1], vertex.BoneWeight[1]).d4
						 + matXfloat(matrix[2], vertex.BoneWeight[2]).d4
						 + matXfloat(matrix[3], vertex.BoneWeight[3]).d4;


			vertex.DeformPosition = vertex.Position;
			aiTransformVecByMatrix4(&vertex.DeformPosition, &outMatrix);
			outMatrix.a4 = outMatrix.b4 = outMatrix.c4 = 0.0f;
			vertex.DeformNormal = vertex.Normal;
			aiTransformVecByMatrix4(&vertex.DeformNormal, &outMatrix);
		}
	}
}

ModelAnimation::~ModelAnimation()
{
	delete[] g_DeformVertex;
	aiReleaseImport(g_Scene);
}
