#pragma once
#include <vector>
#include <fstream>
class GeometryGenerator
{
public:
	GeometryGenerator();
	~GeometryGenerator();

public:
	struct MeshData
	{
		std::vector<VERTEX_3D> vertices;
		std::vector<unsigned short> indices;
	};

	static void CreateGrid(float width, float depth, UINT m, UINT n, MeshData& meshData);
	static void CreateStripField(float cellWidth, int nRows, int nCols, MeshData& meshData); 
	static bool ReadRawFile(std::string filePath, std::vector<float> &heightData);
};

