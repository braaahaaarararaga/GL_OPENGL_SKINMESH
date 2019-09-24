#include "main.h"
#include "model.h"
#include "input.h"
#include <map>
#include <vector>
#include "texture.h"

const aiScene* gg_Scene = nullptr;
std::map<std::string, unsigned int> g_TextureIdMap;
std::map<std::string, float> g_RotationZ;
std::map<std::string, float> g_RotationX;



void InitModel()
{

	const std::string modelPath = "asset/model/murase_tank.fbx";
	gg_Scene = aiImportFile(modelPath.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);
	size_t pos = modelPath.find_last_of("\\/");
	std::string basePath = modelPath.substr(0, pos + 1);
	for (unsigned int m = 0; m < gg_Scene->mNumMaterials; m++)
	{
		aiString path;
		if (gg_Scene->mMaterials[m]->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
		{
			std::string fileloc = basePath + path.data;
			g_TextureIdMap[path.data] = LoadTexture(fileloc.c_str()); 
		}
		else
		{
			g_TextureIdMap[path.data] = 0;
		}
	}

	//g_RotationZ["Cube"] = 0.0f;
	//g_RotationZ["Cylinder"] = 0.0f;
	//g_RotationZ["Cylinder.001"] = 0.0f;
	//
	//g_RotationX["Cube"] = 0.0f;
	//g_RotationX["Cylinder"] = 0.0f;
	//g_RotationX["Cylinder.001"] = 0.0f;
}

void UninitModel()
{
	aiReleaseImport(gg_Scene);
	for (std::pair<std::string, unsigned int> pair : g_TextureIdMap)
	{
		glDeleteTextures(1, &pair.second);
	}
}

void UpdateModel()
{
	//if (CInput::GetKeyPress(VK_LEFT))
	//{
	//	g_RotationZ["Cylinder"] += 1.0f;
	//}
	//if (CInput::GetKeyPress(VK_RIGHT))
	//{
	//	g_RotationZ["Cylinder"] -= 1.0f;
	//}
	//if (CInput::GetKeyPress(VK_UP))
	//{
	//	g_RotationX["Cylinder.001"] += 1.0f;
	//}
	//if (CInput::GetKeyPress(VK_DOWN))
	//{
	//	g_RotationX["Cylinder.001"] -= 1.0f;
	//}
	//if (CInput::GetKeyPress('A'))
	//{
	//	g_RotationZ["Cube"] += 1.0f;
	//}
	//if (CInput::GetKeyPress('D'))
	//{
	//	g_RotationZ["Cube"] -= 1.0f;
	//}
}

void DrawModel()
{
	// matrix setting
	glEnable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	//

	

	DrawMesh(gg_Scene, gg_Scene->mRootNode);


	//
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void DrawMesh(const aiScene * scene, aiNode * node)
{
	aiMatrix4x4 matrix = node->mTransformation;
	aiTransposeMatrix4(&matrix);
	glPushMatrix();
	glMultMatrixf((float*)&matrix);
	//glRotatef(g_RotationZ[node->mName.data], 0.0f, 0.0f, 1.0f);
	//glRotatef(g_RotationX[node->mName.data], 1.0f, 0.0f, 0.0f);
	for (int n = 0; n < node->mNumMeshes; n++)
	{
		const aiMesh* mesh = gg_Scene->mMeshes[node->mMeshes[n]];
		const aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		aiColor4D diffuse;
		aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, (float*)&diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, (float*)&diffuse);
		aiString path;
		material->GetTexture(aiTextureType_DIFFUSE, 0, &path);
		glBindTexture(GL_TEXTURE_2D, g_TextureIdMap[path.data]);
		glBegin(GL_TRIANGLES);

		for (int t = 0; t < mesh->mNumFaces; t++)
		{
			const aiFace* face = &mesh->mFaces[t];
			for (int i = 0; i < face->mNumIndices; i++)
			{
				int index = face->mIndices[i];
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				if (mesh->mNormals != nullptr)
				{
					glNormal3f(mesh->mNormals[index].x, mesh->mNormals[index].y, mesh->mNormals[index].z);

				}
				if (mesh->HasTextureCoords(0))
				{
					glTexCoord2f(mesh->mTextureCoords[0][index].x, mesh->mTextureCoords[0][index].y);
				}
				glVertex3f(mesh->mVertices[index].x, mesh->mVertices[index].y, mesh->mVertices[index].z);
			}
		}
		glEnd();
		glBegin(GL_LINES);
		for (int t = 0; t < mesh->mNumFaces; t++)
		{
			const aiFace* face = &mesh->mFaces[t];
			for (int i = 0; i < face->mNumIndices; i++)
			{
				int index = face->mIndices[i];
				glVertex3f(mesh->mVertices[index].x, mesh->mVertices[index].y, mesh->mVertices[index].z);

				glVertex3f(mesh->mVertices[index].x + mesh->mNormals[index].x * 2.0f,
					mesh->mVertices[index].y + mesh->mNormals[index].y * 2.0f, 
					mesh->mVertices[index].z + mesh->mNormals[index].z * 2.0f);


			}
		}
		glEnd();
	}

	for (int n = 0; n < node->mNumChildren; n++)
	{
		DrawMesh(scene, node->mChildren[n])
			;
	}
	glPopMatrix();
}





