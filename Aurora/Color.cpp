#include "Color.h"

#include <math.h>

#define SQUARED(x) (x * x)
#define HALF_OF(x) (x / static_cast<decltype(x)>(2))
#define PI (A_FL32)(3.1415926f)
#define RADIANS_TO_DEGREES(x) (x * 180 / PI)

namespace Aurora {
	RGB::RGB() : uR(0), uG(0), uB(0) {}

	RGB::RGB(_In_ A_U8 uR, _In_ A_U8 uG, _In_ A_U8 uB) : uR(uR), uG(uG), uB(uB) {}

	RGB::RGB(_In_ const Vector3<>& v3Values, _In_ ColorRepresentation nRepresentation) {
		if (nRepresentation == ColorRepresentation::Integral) {
			uR = static_cast<A_U8>(v3Values.X());
			uG = static_cast<A_U8>(v3Values.Y());
			uB = static_cast<A_U8>(v3Values.Z());
		}
		else if (nRepresentation == ColorRepresentation::Percent) {
			uR = static_cast<A_U8>(v3Values.X() * ('\0' - 1));
			uG = static_cast<A_U8>(v3Values.Y() * ('\0' - 1));
			uB = static_cast<A_U8>(v3Values.Z() * ('\0' - 1));
		}
		else {
			uR = 0;
			uG = 0;
			uB = 0;
		}
	}

	String RGB::ToString() const {
		String ret;
		ret.AddFormat(-1, "rgb(%hhu, %hhu, %hhu)", uR, uG, uB);
		return ret;
	}

	RGBA RGB::ToRGBA() const {
		return RGBA(uR, uG, uB, 255);
	}

	HSL RGB::ToHSL() const {
		A_FL32 fR = static_cast<A_FL32>(uR);
		A_FL32 fG = static_cast<A_FL32>(uG);
		A_FL32 fB = static_cast<A_FL32>(uB);

		A_FL32 fMax = fmaxf(fmaxf(fR, fG), fB);
		A_FL32 fMin = fminf(fminf(fR, fG), fB);
		A_FL32 fDelta = (fMax - fMin) / 255.0f;

		A_FL32 fLightness = (fMax + fMin) / 510.0f;
		A_FL32 fSaturation = (fLightness > 0.0f) ? roundf((fDelta / (1 - fabsf(2 * fLightness - 1))) * 100.0f) / 100.0f : 0.0f;

		A_FL32 fHue = roundf(RADIANS_TO_DEGREES(acosf((fR - HALF_OF(fG) - HALF_OF(fB)) / sqrtf(SQUARED(fR) + SQUARED(fG) + SQUARED(fB) - fR * fG - fR * fB - fG * fB))));

		A_FL32 fHueFinal = fB > fG ? (360.0f - fHue) : fHue;

		return HSL(static_cast<A_U16>(fHueFinal), fSaturation, fLightness);
	}

	HEX RGB::ToHex() const {
		return HEX();
	}

	RGBA::RGBA() { }
	RGBA::RGBA(_In_ A_U8 uR, _In_ A_U8 uG, _In_ A_U8 uB, _In_ A_U8 uA) { }
	RGBA::RGBA(_In_ const Vector4<>& v4Values, _In_ ColorRepresentation nRepresentation) { }

	String RGBA::ToString() const { return String(); }
	RGB RGBA::ToRGB() const { return RGB(); }
	HSL RGBA::ToHSL() const { return HSL(); }
	HEX RGBA::ToHex() const { return HEX(); }

	HSL::HSL() : uHue(0), fSaturation(0.0f), fLightness(0.0f), fAlpha(0.0f) {}
	HSL::HSL(_In_ A_U16 uHue, _In_ A_FL32 fSaturation, _In_ A_FL32 fLightness, _In_ A_FL32 fAlpha) : uHue(uHue), fSaturation(fSaturation), fLightness(fLightness), fAlpha(fAlpha) {}

	String HSL::ToString() const {
		String ret;
		ret.AddFormat(-1, "hsl(%hu, %hhu%%, %hhu%%, %f)", uHue, static_cast<A_U8>(fSaturation * 100.0f), static_cast<A_U8>(fLightness * 100.0f), fAlpha);
		return ret;
	}
	RGB HSL::ToRGB() const { return RGB(); }
	RGBA HSL::ToRGBA() const { return RGBA(); }
	HEX HSL::ToHex() const { return HEX(); }
}