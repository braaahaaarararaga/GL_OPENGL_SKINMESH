#pragma once

void InitModelAnimation();
void DrawModelAnimation();
void DrawModelAnimationMesh(const aiNode* Node);
void UninitModelAnimation();
void UpdateModelAnimation();
void CreateBone(aiNode* Node);
void UpdateBoneMatrix(aiNode* Node, aiMatrix4x4 Matrix);