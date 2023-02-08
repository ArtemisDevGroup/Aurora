#ifndef __AURORA_COLOR_H__
#define __AURORA_COLOR_H__

#include "Definitions.h"
#include "String.h"
#include "Vector.h"

namespace Aurora {
	enum class ColorRepresentation {
		Percent,
		Integral
	};

	class AURORA_API RGBA;
	class AURORA_API HSL;
	class AURORA_API HEX;

	class AURORA_API RGB {
	public:
		A_U8 uR, uG, uB;

		RGB();
		RGB(_In_ A_U8 uR, _In_ A_U8 uG, _In_ A_U8 uB);
		RGB(_In_ const Vector3<>& v3Values, _In_ ColorRepresentation nRepresentation);

		String ToString() const;
		RGBA ToRGBA() const;
		HSL ToHSL() const;
		HEX ToHex() const;
	};

	class AURORA_API RGBA {
	public:
		A_U8 uR, uG, uB, uA;

		RGBA();
		RGBA(_In_ A_U8 uR, _In_ A_U8 uG, _In_ A_U8 uB, _In_ A_U8 uA);
		RGBA(_In_ const Vector4<>& v4Values, _In_ ColorRepresentation nRepresentation);

		String ToString() const;
		RGB ToRGB() const;
		HSL ToHSL() const;
		HEX ToHex() const;
	};

	class AURORA_API HSL {
	public:
		A_U16 uHue;
		A_FL32 fSaturation, fLightness, fAlpha;

		HSL();
		HSL(_In_ A_U16 uHue, _In_ A_FL32 fSaturation, _In_ A_FL32 fLightness, _In_ A_FL32 fAlpha = 1.0f);

		String ToString() const;
		RGB ToRGB() const;
		RGBA ToRGBA() const;
		HEX ToHex() const;
	};
	
	class AURORA_API HEX {
		
	};
}

#endif // !__AURORA_COLOR_H__