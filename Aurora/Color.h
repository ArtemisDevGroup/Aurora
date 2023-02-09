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

	class AURORA_API RGB;
	class AURORA_API RGBA;
	class AURORA_API HSL;
	class AURORA_API HEX;

	namespace Colors {
		extern const RGB AliceBlue;
		extern const RGB AntiqueWhite;
		extern const RGB Aqua;
		extern const RGB Aquamarine;
		extern const RGB Azure;
		extern const RGB Beige;
		extern const RGB Bisque;
		extern const RGB Black;
		extern const RGB BlancedAlmond;
		extern const RGB Blue;
		extern const RGB BlueViolet;
		extern const RGB Brown;
		extern const RGB BurlyWood;
		extern const RGB CadetBlue;
		extern const RGB Chartreuse;
		extern const RGB Chocolate;
		extern const RGB Coral;
		extern const RGB CornflowerBlue;
		extern const RGB Cornsilk;
		extern const RGB Crimson;
		extern const RGB Cyan;
		extern const RGB DarkBlue;
		extern const RGB DarkCyan;
		extern const RGB DarkGoldenrod;
		extern const RGB DarkGray;
		extern const RGB DarkGreen;
		extern const RGB DarkKhaki;
		extern const RGB DarkMagenta;
		extern const RGB DarkOliveGreen;
		extern const RGB DarkOrange;
		extern const RGB DarkRed;
		extern const RGB DarkSalmon;
		extern const RGB DarkSeaGreen;
		extern const RGB DarkSlateBlue;
		extern const RGB DarkSlateGray;
		extern const RGB DarkTurquoise;
		extern const RGB DarkViolet;
		extern const RGB DeepPink;
		extern const RGB DeepSkyBlue;
		extern const RGB DimGray;
		extern const RGB DodgerBlue;
		extern const RGB Firebrick;
		extern const RGB FloralWhite;
		extern const RGB FloralGreen;
		extern const RGB Fuchsia;
		extern const RGB Gainsboro;
		extern const RGB GhostWhite;
		extern const RGB Gold;
		extern const RGB Goldenrod;
		extern const RGB Gray;
		extern const RGB Green;
		extern const RGB GreenYellow;
		extern const RGB Honeydew;
		extern const RGB HotPink;
		extern const RGB IndianRed;
		extern const RGB Indigo;
		extern const RGB Ivory;
		extern const RGB Lavender;
		extern const RGB LavenderBlush;
		extern const RGB LawnGreen;
		extern const RGB LemonChiffon;
		extern const RGB LightBlue;
		extern const RGB LightCoral;
		extern const RGB LightCyan;
		extern const RGB LightGoldenrodYellow;
		extern const RGB LightGray;
		extern const RGB LightPink;
		extern const RGB LightSalmon;
		extern const RGB LightSeaGreen;
		extern const RGB LightSkyBlue;
		extern const RGB LightSlateGray;
		extern const RGB LightSteelBlue;
		extern const RGB LightYellow;
		extern const RGB Lime;
		extern const RGB LimeGreen;
		extern const RGB Linen;
		extern const RGB Magenta;
		extern const RGB Maroon;
		extern const RGB MediumAquamarine;
		extern const RGB MediumBlue;
		extern const RGB MediumOrchid;
		extern const RGB MediumPurple;
		extern const RGB MediumSeaGreen;
		extern const RGB MediumSlateBlue;
		extern const RGB MediumSpringGreen;
		extern const RGB MediumTurquoise;
		extern const RGB MediumVioletRed;
		extern const RGB MidnightBlue;
		extern const RGB MintCream;
		extern const RGB MistyRose;
		extern const RGB Moccasin;
		extern const RGB NajavoWhite;
		extern const RGB Navy;
		extern const RGB OldLace;
		extern const RGB Olive;
		extern const RGB OliveDrab;
		extern const RGB Orange;
		extern const RGB OrangeRed;
		extern const RGB Orchid;
		extern const RGB PaleGoldenrod;
		extern const RGB PaleGreen;
		extern const RGB PaleTurquoise;
		extern const RGB PaleVioletRed;
		extern const RGB PapayaWhip;
		extern const RGB PeachPuff;
		extern const RGB Peru;
		extern const RGB Pink;
		extern const RGB Plum;
		extern const RGB PowderBlue;
		extern const RGB Purple;
		extern const RGB Red;
		extern const RGB RosyBrown;
		extern const RGB RoyalBlue;
		extern const RGB SaddleBrown;
		extern const RGB Salmon;
		extern const RGB SandyBrown;
		extern const RGB SeaGreen;
		extern const RGB SeaShell;
		extern const RGB Sienna;
		extern const RGB Silver;
		extern const RGB SkyBlue;

		extern const RGB SlateBlue;
		extern const RGB SlateGray;
		extern const RGB Snow;
		extern const RGB SpringGreen;
		extern const RGB SteelBlue;
		extern const RGB Tan;
		extern const RGB Teal;
		extern const RGB Thistle;
		extern const RGB Tomato;
		extern const RGBA Transparent;
		extern const RGB Turquoise;
		extern const RGB Violet;
		extern const RGB Wheat;
		extern const RGB White;
		extern const RGB WhiteSmoke;
		extern const RGB Yellow;
		extern const RGB YellowGreen;
	}

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