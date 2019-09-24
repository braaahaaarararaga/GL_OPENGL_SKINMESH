#include "main.h"
#include "renderer.h"
#include "GeometryGenerator.h"
#include "gameObject.h"
#include "field.h"
#include "texture.h"

void CField::Init()
{
	cellSize = 1.0f;
	xCellCount = 32;
	zCellCount = 32;

	GeometryGenerator::MeshData meshData;
	GeometryGenerator::CreateStripField(cellSize, xCellCount, zCellCount, meshData);

	vertices.resize(meshData.vertices.size());
	
	for (int i = 0; i < vertices.size(); i++)
	{
		vertices[i].pos = meshData.vertices[i].Position;
	}

	gridIndexCount = meshData.indices.size();
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(VERTEX_3D) * meshData.vertices.size();
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = &meshData.vertices[0];

		CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
	}


	// �C���f�b�N�X�o�b�t�@����
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(unsigned short) * meshData.indices.size();
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = &meshData.indices[0];

		CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_IndexBuffer);
	}
	m_Texture = new CTexture();
	m_Texture->Load("asset/field004.tga");

}

void CField::Uninit()
{
	m_VertexBuffer->Release();
	m_IndexBuffer->Release();
	m_Texture->Unload();
	delete m_Texture;
}

void CField::Update()
{
}

void CField::Draw()
{

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	
	// �C���f�b�N�X�o�b�t�@�ݒ�
	CRenderer::SetIndexBuffer(m_IndexBuffer);

	// �e�N�X�`���ݒ�
	CRenderer::SetTexture(m_Texture);

	// �}�g���N�X�ݒ�
	XMMATRIX world;
	world = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	CRenderer::SetWorldMatrix(&world);

	// �v���~�e�B�u�g�|���W�ݒ�
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �|���S���`��
	CRenderer::GetDeviceContext()->DrawIndexed(gridIndexCount, 0, 0);
}

float CField::GetHeight(XMFLOAT3 position)
{
	int x, z;
	XMFLOAT3 p0, p1, p2, v, va, vb, hp;
	XMVECTOR v01, v02, n;
	float dp0n, dvn, dpn, t;
	v = XMFLOAT3(0.0f, -10.0f, 0.0f);
	// �Ȃ�u���b�N�ɂ���̂�
	x = position.x / 0.1f; // 0.1�̓u���b�N�̃T�C�Y
	z = -position.z / 0.1f;

	va.x = vertices[(z + 1) * 5/*�����_��*/ + (x + 1)].pos.x - vertices[z * 5 + x].pos.x;
	va.y = vertices[(z + 1) * 5 + (x + 1)].pos.y - vertices[z * 5 + x].pos.y;
	va.z = vertices[(z + 1) * 5 + (x + 1)].pos.z - vertices[z * 5 + x].pos.z;

	vb.x = position.x - vertices[z * 5 + x].pos.x;
	vb.y = position.y - vertices[z * 5 + x].pos.y;
	vb.z = position.z - vertices[z * 5 + x].pos.z;

	if (va.z * vb.x - va.x * vb.z/*y�����������v�Z*/ > 0.0f)
	{
		p0 = vertices[(z + 1) * 5 + x].pos;
		p1 = vertices[(z * 5 + x)].pos;
		p2 = vertices[(z + 1) * 5 + (x + 1)].pos;
	}
	else
	{
		p0 = vertices[z * 5 + (x + 1)].pos;
		p1 = vertices[(z + 1) * 5 + (x + 1)].pos;
		p2 = vertices[(z * 5 + x)].pos;
	}
	XMVECTOR vp0, vp1, vp2;
	vp0 = XMLoadFloat3(&p0);
	vp1 = XMLoadFloat3(&p1);
	vp2 = XMLoadFloat3(&p2);
	v01 = vp1 - vp0;
	v02 = vp2 - vp0;
	n = XMVector3Cross(v01, v02);//v01 �O�� v02;
	XMFLOAT3 fn;
	XMStoreFloat3(&fn, n);
	dvn = v.x * fn.x + v.y * fn.y + v.z * fn.z; //v ���� n;
	dp0n = p0.x * fn.x + p0.y * fn.y + p0.z * fn.z; //p0 ���� n;
	dpn = position.x * fn.x + position.y * fn.y + position.z * fn.z; //position ���� n;
	t = (dp0n - dpn) / dvn;
	hp.x = position.x + v.x * t;
	hp.y = position.y + v.y * t;
	hp.z = position.z + v.z * t;
	return hp.y;

}
