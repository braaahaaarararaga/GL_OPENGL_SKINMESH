#pragma once
#include <vector>
class CField : public GameObject
{
private:
	struct Vertex
	{
		XMFLOAT3 pos;
	};

	std::vector<Vertex> vertices;
	UINT gridIndexCount;
	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11Buffer* m_IndexBuffer = NULL;
	CTexture*	  m_Texture = NULL;

	float cellSize;
	int xCellCount;
	int zCellCount;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	float GetHeight(XMFLOAT3 position);
};