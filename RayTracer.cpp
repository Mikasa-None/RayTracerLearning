#include "RayTracer.h"
void RayTracer::Draw(const Scene& scn,Canvas& cvs) const
{
	int nsample = 16;
	for (int i = 0; i < Canvas::ScreenWidth; ++i)
	{
		for (int j = 0; j < Canvas::ScreenHeight; ++j)
		{
			vec3 color;
			for (int k = 0; k < nsample; ++k)
			{
				float u = float(i+getRandom()) / float(Canvas::ScreenWidth);
				float v = float(j + getRandom()) / float(Canvas::ScreenHeight);
				Ray r = camera.GetRay(u, v);
				//color += scn.castRay(r, 0);
				color += scn.PathTracing(r);

			}
			color /= float(nsample);
			color = vec3(sqrt(color[0]), sqrt(color[1]), sqrt(color[2]));
			int ir = int(255.99*color[0]);
			int ig = int(255.99*color[1]);
			int ib = int(255.99*color[2]);
			cvs.PutPixel(i, j, ir, ig, ib);

		}
	}
}
