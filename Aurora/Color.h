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

	namespace Colors {
		AURORA_API extern const RGB AliceBlue;
		AURORA_API extern const RGB AntiqueWhite;
		AURORA_API extern const RGB Aqua;
		AURORA_API extern const RGB Aquamarine;
		AURORA_API extern const RGB Azure;
		AURORA_API extern const RGB Beige;
		AURORA_API extern const RGB Bisque;
		AURORA_API extern const RGB Black;
		AURORA_API extern const RGB BlancedAlmond;
		AURORA_API extern const RGB Blue;
		AURORA_API extern const RGB BlueViolet;
		AURORA_API extern const RGB Brown;
		AURORA_API extern const RGB BurlyWood;
		AURORA_API extern const RGB CadetBlue;
		AURORA_API extern const RGB Chartreuse;
		AURORA_API extern const RGB Chocolate;
		AURORA_API extern const RGB Coral;
		AURORA_API extern const RGB CornflowerBlue;
		AURORA_API extern const RGB Cornsilk;
		AURORA_API extern const RGB Crimson;
		AURORA_API extern const RGB Cyan;
		AURORA_API extern const RGB DarkBlue;
		AURORA_API extern const RGB DarkCyan;
		AURORA_API extern const RGB DarkGoldenrod;
		AURORA_API extern const RGB DarkGray;
		AURORA_API extern const RGB DarkGreen;
		AURORA_API extern const RGB DarkKhaki;
		AURORA_API extern const RGB DarkMagenta;
		AURORA_API extern const RGB DarkOliveGreen;
		AURORA_API extern const RGB DarkOrange;
		AURORA_API extern const RGB DarkRed;
		AURORA_API extern const RGB DarkSalmon;
		AURORA_API extern const RGB DarkSeaGreen;
		AURORA_API extern const RGB DarkSlateBlue;
		AURORA_API extern const RGB DarkSlateGray;
		AURORA_API extern const RGB DarkTurquoise;
		AURORA_API extern const RGB DarkViolet;
		AURORA_API extern const RGB DeepPink;
		AURORA_API extern const RGB DeepSkyBlue;
		AURORA_API extern const RGB DimGray;
		AURORA_API extern const RGB DodgerBlue;
		AURORA_API extern const RGB Firebrick;
		AURORA_API extern const RGB FloralWhite;
		AURORA_API extern const RGB FloralGreen;
		AURORA_API extern const RGB Fuchsia;
		AURORA_API extern const RGB Gainsboro;
		AURORA_API extern const RGB GhostWhite;
		AURORA_API extern const RGB Gold;
		AURORA_API extern const RGB Goldenrod;
		AURORA_API extern const RGB Gray;
		AURORA_API extern const RGB Green;
		AURORA_API extern const RGB GreenYellow;
		AURORA_API extern const RGB Honeydew;
		AURORA_API extern const RGB HotPink;
		AURORA_API extern const RGB IndianRed;
		AURORA_API extern const RGB Indigo;
		AURORA_API extern const RGB Ivory;
		AURORA_API extern const RGB Lavender;
		AURORA_API extern const RGB LavenderBlush;
		AURORA_API extern const RGB LawnGreen;
		AURORA_API extern const RGB LemonChiffon;
		AURORA_API extern const RGB LightBlue;
		AURORA_API extern const RGB LightCoral;
		AURORA_API extern const RGB LightCyan;
		AURORA_API extern const RGB LightGoldenrodYellow;
		AURORA_API extern const RGB LightGray;
		AURORA_API extern const RGB LightPink;
		AURORA_API extern const RGB LightSalmon;
		AURORA_API extern const RGB LightSeaGreen;
		AURORA_API extern const RGB LightSkyBlue;
		AURORA_API extern const RGB LightSlateGray;
		AURORA_API extern const RGB LightSteelBlue;
		AURORA_API extern const RGB LightYellow;
		AURORA_API extern const RGB Lime;
		AURORA_API extern const RGB LimeGreen;
		AURORA_API extern const RGB Linen;
		AURORA_API extern const RGB Magenta;
		AURORA_API extern const RGB Maroon;
		AURORA_API extern const RGB MediumAquamarine;
		AURORA_API extern const RGB MediumBlue;
		AURORA_API extern const RGB MediumOrchid;
		AURORA_API extern const RGB MediumPurple;
		AURORA_API extern const RGB MediumSeaGreen;
		AURORA_API extern const RGB MediumSlateBlue;
		AURORA_API extern const RGB MediumSpringGreen;
		AURORA_API extern const RGB MediumTurquoise;
		AURORA_API extern const RGB MediumVioletRed;
		AURORA_API extern const RGB MidnightBlue;
		AURORA_API extern const RGB MintCream;
		AURORA_API extern const RGB MistyRose;
		AURORA_API extern const RGB Moccasin;
		AURORA_API extern const RGB NajavoWhite;
		AURORA_API extern const RGB Navy;
		AURORA_API extern const RGB OldLace;
		AURORA_API extern const RGB Olive;
		AURORA_API extern const RGB OliveDrab;
		AURORA_API extern const RGB Orange;
		AURORA_API extern const RGB OrangeRed;
		AURORA_API extern const RGB Orchid;
		AURORA_API extern const RGB PaleGoldenrod;
		AURORA_API extern const RGB PaleGreen;
		AURORA_API extern const RGB PaleTurquoise;
		AURORA_API extern const RGB PaleVioletRed;
		AURORA_API extern const RGB PapayaWhip;
		AURORA_API extern const RGB PeachPuff;
		AURORA_API extern const RGB Peru;
		AURORA_API extern const RGB Pink;
		AURORA_API extern const RGB Plum;
		AURORA_API extern const RGB PowderBlue;
		AURORA_API extern const RGB Purple;
		AURORA_API extern const RGB Red;
		AURORA_API extern const RGB RosyBrown;
		AURORA_API extern const RGB RoyalBlue;
		AURORA_API extern const RGB SaddleBrown;
		AURORA_API extern const RGB Salmon;
		AURORA_API extern const RGB SandyBrown;
		AURORA_API extern const RGB SeaGreen;
		AURORA_API extern const RGB SeaShell;
		AURORA_API extern const RGB Sienna;
		AURORA_API extern const RGB Silver;
		AURORA_API extern const RGB SkyBlue;
		AURORA_API extern const RGB SlateBlue;
		AURORA_API extern const RGB SlateGray;
		AURORA_API extern const RGB Snow;
		AURORA_API extern const RGB SpringGreen;
		AURORA_API extern const RGB SteelBlue;
		AURORA_API extern const RGB Tan;
		AURORA_API extern const RGB Teal;
		AURORA_API extern const RGB Thistle;
		AURORA_API extern const RGB Tomato;
		AURORA_API extern const RGBA Transparent;
		AURORA_API extern const RGB Turquoise;
		AURORA_API extern const RGB Violet;
		AURORA_API extern const RGB Wheat;
		AURORA_API extern const RGB White;
		AURORA_API extern const RGB WhiteSmoke;
		AURORA_API extern const RGB Yellow;
		AURORA_API extern const RGB YellowGreen;
	}
}

#endif // !__AURORA_COLOR_H__