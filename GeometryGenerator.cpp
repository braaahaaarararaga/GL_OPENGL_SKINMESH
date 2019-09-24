#include "main.h"
#include "renderer.h"
#include "GeometryGenerator.h"



GeometryGenerator::GeometryGenerator()
{
}


GeometryGenerator::~GeometryGenerator()
{
}

void GeometryGenerator::CreateGrid(float width, float depth, UINT m, UINT n, MeshData & meshData)
{
	UINT vertexCount = m * n;
	UINT faceCount = (m - 1)*(n - 1) * 2;
	float halfWidth = 0.5f*width;
	float halfDepth = 0.5f*depth;
	float dx = width / (n - 1);
	float dz = depth / (m - 1);

	meshData.vertices.resize(vertexCount);
	for (UINT i = 0; i < m; i++)
	{
		float z = halfDepth - i * dz;
		for (UINT j = 0; j < n; j++)
		{
			float x = -halfWidth + j * dx;
			meshData.vertices[i * n + j].Position = XMFLOAT3(x, 0.0f, z);
			meshData.vertices[i * n + j].Normal = XMFLOAT3(0, 1.0f, 0);
			meshData.vertices[i * n + j].Diffuse = XMFLOAT4(1, 1.0f, 1,1);
			meshData.vertices[i * n + j].TexCoord = XMFLOAT2((float)j  , -(float) i );
		}
	}

	meshData.indices.resize(faceCount * 3);

	UINT k = 0;
	for (UINT i = 0; i < m - 1; i++)
	{
		for (UINT j = 0; j < n - 1; j++)
		{
			meshData.indices[k]		= i * n + j;
			meshData.indices[k + 1] = i * n + j + 1;
			meshData.indices[k + 2] = (i + 1) * n + j;

			meshData.indices[k + 3] = (i + 1)*n + j;
			meshData.indices[k + 4] = i * n + j + 1;
			meshData.indices[k + 5] = (i + 1)*n + j + 1;
			
			k += 6;
		}
	}
}

void GeometryGenerator::CreateStripField(float cellWidth, int nRows, int nCols, MeshData& meshData)
{

	int RowCells = nRows;
	int ColCells = nCols;
	nRows++;
	nCols++;

	float offsetX = RowCells * cellWidth / 2 * -1;
	float offsetY = ColCells * cellWidth / 2 * -1;

	meshData.vertices.resize(nRows * nCols);
	meshData.indices.resize(ColCells * nRows * 2 + (ColCells - 1) * 2);

	std::vector<float> heightData;
	std::string filePath = "asset/heightMap02.raw";
	ReadRawFile(filePath, heightData);

	float scale = 0.05f;
	for (auto& item : heightData)
	{
		item *= scale;
	}
	float heightSize = sqrt(heightData.size());

	for (int i = 0; i < nCols; i++)
	{
		for (int j = 0; j < nRows; j++)
		{
			meshData.vertices[i * nRows + j].Position = XMFLOAT3(j * cellWidth + offsetX,
				/*heightData[int((float)j / nRows * (heightSize - 1) + (float)i / nCols * (heightSize - 1) * heightSize)]*/
				sinf(j * 0.5f) * sinf(i * 0.3f) * 2.0f,
				i * cellWidth + offsetY);
			int l = (float)i / nCols * (heightSize - 1) * heightSize + (float)j / nRows * (heightSize - 1);
			meshData.vertices[i * nRows + j].TexCoord = XMFLOAT2((float)j, -(float)i);
			meshData.vertices[i * nRows + j].Normal = XMFLOAT3(0, 1.0f, 0);
			meshData.vertices[i * nRows + j].Diffuse = XMFLOAT4(1, 1.0f, 1, 1);
		}
	}

	for (int i = 0; i < nCols - 1; i++)
	{
		for (int j = 0; j < 2 * nRows; j += 2)
		{
			meshData.indices[i * (2 * nRows + 2) + j] = i * nRows + j / 2;
			meshData.indices[i * (2 * nRows + 2) + j + 1] = (i + 1) * nRows + j / 2;
			if (j == 0 && i != 0)
			{
				meshData.indices[i * (2 * nRows + 2) - 2] = i * nRows + nRows - 1;
				meshData.indices[i * (2 * nRows + 2) - 1] = i * nRows;
			}
		}
	}
}

bool GeometryGenerator::ReadRawFile(std::string filePath, std::vector<float> &heightData)
{
	std::ifstream inFile;
	inFile.open(filePath.c_str(), std::ios::binary);
	inFile.seekg(0, std::ios::end);
	std::vector<BYTE> inData(inFile.tellg());
	inFile.seekg(std::ios::beg);
	inFile.read((char*)&inData[0], inData.size());
	inFile.close();
	
	heightData.resize(inData.size());
	for (int i = 0; i < inData.size(); ++i)
	{
		heightData[i] = inData[i];
	}
	
	return true;
	
}
