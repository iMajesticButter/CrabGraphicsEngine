#include "CrabGraphicsUtils.h"
#include <math.h>

namespace CrabEngine {
    namespace Graphics {
        using namespace CrabEngine::Math;

        Vec3 HSVToRGB(const Vec3& in) {
            double      hh, p, q, t, ff;
            long        i;
            Vec3         out;

            if(in.y <= 0.0) {       // < is bogus, just shuts up warnings
                out.x = in.z;
                out.y = in.z;
                out.z = in.z;
                return out;
            }
            hh = in.x;
            if(hh >= 360.0) hh = 0.0;
            hh /= 60.0;
            i = (long)hh;
            ff = hh - i;
            p = in.z * (1.0 - in.y);
            q = in.z * (1.0 - (in.y * ff));
            t = in.z * (1.0 - (in.y * (1.0 - ff)));

            switch(i) {
            case 0:
                out.x = in.z;
                out.y = t;
                out.z = p;
                break;
            case 1:
                out.x = q;
                out.y = in.z;
                out.z = p;
                break;
            case 2:
                out.x = p;
                out.y = in.z;
                out.z = t;
                break;

            case 3:
                out.x = p;
                out.y = q;
                out.z = in.z;
                break;
            case 4:
                out.x = t;
                out.y = p;
                out.z = in.z;
                break;
            case 5:
            default:
                out.x = in.z;
                out.y = p;
                out.z = q;
                break;
            }
            return out * 255;
        }
        Vec3 RGBtoHSV(const Vec3& rgb) {
            Vec3 hcol;

            float r = rgb.x/255;
            float g = rgb.y/255;
            float b = rgb.z/255;

            float cmax = std::max(r,std::max(g,b));
            float cmin = std::min(r,std::min(g,b));

            if(cmax == cmin) {
                hcol.x = 0;
                hcol.y = 0;
                hcol.z = cmin;
                return hcol;
            }

            float d = (r==cmin) ? g-b : ((b==cmin) ? r-g : b-r);
            float h = (r==cmin) ? 3 : ((b == cmin) ? 1 : 5);

            hcol.x = 60*(h-d/(cmax-cmin));
            hcol.y = (cmax - cmin)/cmax;
            hcol.z = cmax;

            return hcol;
        }

    }
}
