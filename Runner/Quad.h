#ifndef QUAD_H__
#define QUAD_H__

namespace Runner
{

	struct Quad
	{
		int vboID;
		float vert[3*4 + 2*4];
		unsigned int vertCount;
		int stride;
		unsigned int textureID;

		Quad() : vboID(-1), vertCount(4), textureID(-1)
		{
			stride = (3*4 + 2*4) /** sizeof(float)*/;

			vert[0]  = -0.5; vert[1]   = -0.5; vert[2]   = 0.0; vert[3]  = 0.f; vert[4]  = 0.f;
			vert[5]  = +0.5; vert[6]   = -0.5; vert[7]   = 0.0; vert[8]  = 1.f; vert[9]  = 0.f;
			vert[10] = -0.5; vert[11]  = +0.5; vert[12]  = 0.0; vert[13] = 0.f; vert[14] = 1.f;
			vert[15] = +0.5; vert[16]  = +0.5; vert[17]  = 0.0; vert[18] = 1.f; vert[19] = 1.f;
		}
	};

}
#endif