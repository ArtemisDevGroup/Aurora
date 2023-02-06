#include "Color.h"

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
		return HSL();
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

	HSL::HSL() { }
	HSL::HSL(_In_ A_U16 uHue, _In_ A_FL32 fSaturation, _In_ A_FL32 fLightness, _In_ A_FL32 fAlpha) { }

	String HSL::ToString() const { return String(); }
	RGB HSL::ToRGB() const { return RGB(); }
	RGBA HSL::ToRGBA() const { return RGBA(); }
	HEX HSL::ToHex() const { return HEX(); }
}