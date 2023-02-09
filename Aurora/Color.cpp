#include "Color.h"

#include <math.h>

#define PI (A_FL32)(3.1415926f)

constexpr A_FL32 sq(A_FL32 x) { return x * x; }
constexpr A_FL32 half(A_FL32 x) { return x / 2.0f; }
constexpr A_FL32 radtodeg(A_FL32 x) { return x * 180.0f / PI; }

namespace Aurora {
	namespace Colors {
		const RGB AliceBlue = RGB(240, 248, 255);
		const RGB AntiqueWhite = RGB(250, 235, 215);
		const RGB Aqua = RGB(0, 255, 255);
		const RGB Aquamarine = RGB(127, 255, 212);
		const RGB Azure = RGB(240, 255, 255);
		const RGB Beige = RGB(245, 245, 220);
		const RGB Bisque = RGB(255, 228, 196);
		const RGB Black = RGB(0, 0, 0);
		const RGB BlancedAlmond = RGB(255, 235, 205);
		const RGB Blue = RGB(0, 0, 255);
		const RGB BlueViolet = RGB(138, 43, 226);
		const RGB Brown = RGB(165, 42, 42);
		const RGB BurlyWood = RGB(222, 184, 135);
		const RGB CadetBlue = RGB(95, 158, 160);
		const RGB Chartreuse = RGB(127, 255, 0);
		const RGB Chocolate = RGB(210, 105, 30);
		const RGB Coral = RGB(255, 127, 80);
		const RGB CornflowerBlue = RGB(100, 149, 237);
		const RGB Cornsilk = RGB(255, 248, 220);
		const RGB Crimson = RGB(220, 20, 60);
		const RGB Cyan = RGB(0, 255, 255);
		const RGB DarkBlue = RGB(0, 0, 139);
		const RGB DarkCyan = RGB(0, 139, 139);
		const RGB DarkGoldenrod = RGB(184, 134, 11);
		const RGB DarkGray = RGB(169, 169, 169);
		const RGB DarkGreen = RGB(0, 100, 0);
		const RGB DarkKhaki = RGB(189, 183, 107);
		const RGB DarkMagenta = RGB(139, 0, 139);
		const RGB DarkOliveGreen = RGB(85, 107, 47);
		const RGB DarkOrange = RGB(255, 140, 0);
		const RGB DarkRed = RGB(139, 0, 0);
		const RGB DarkSalmon = RGB(233, 150, 122);
		const RGB DarkSeaGreen = RGB(143, 188, 143);
		const RGB DarkSlateBlue = RGB(72, 61, 139);
		const RGB DarkSlateGray = RGB(47, 79, 79);
		const RGB DarkTurquoise = RGB(0, 206, 209);
		const RGB DarkViolet = RGB(148, 0, 211);
		const RGB DeepPink = RGB(255, 20, 147);
		const RGB DeepSkyBlue = RGB(0, 191, 255);
		const RGB DimGray = RGB(105, 105, 105);
		const RGB DodgerBlue = RGB(30, 144, 255);
		const RGB Firebrick = RGB(178, 34, 34);
		const RGB FloralWhite = RGB(255, 250, 240);
		const RGB FloralGreen = RGB(181, 230, 190);
		const RGB Fuchsia = RGB(255, 0, 255);
		const RGB Gainsboro = RGB(220, 220, 220);
		const RGB GhostWhite = RGB(248, 248, 255);
		const RGB Gold = RGB(255, 215, 0);
		const RGB Goldenrod = RGB(218, 165, 32);
		const RGB Gray = RGB(128, 128, 128);
		const RGB Green = RGB(0, 255, 0);
		const RGB GreenYellow = RGB(173, 255, 47);
		const RGB Honeydew = RGB(240, 255, 240);
		const RGB HotPink = RGB(255, 105, 180);
		const RGB IndianRed = RGB(205, 92, 92);
		const RGB Indigo = RGB(75, 0, 130);
		const RGB Ivory = RGB(255, 255, 240);
		const RGB Lavender = RGB(230, 230, 250);
		const RGB LavenderBlush = RGB(255, 240, 245);
		const RGB LawnGreen = RGB(124, 252, 0);
		const RGB LemonChiffon = RGB(255, 250, 205);
		const RGB LightBlue = RGB(173, 216, 230);
		const RGB LightCoral = RGB(240, 128, 128);
		const RGB LightCyan = RGB(224, 255, 255);
		const RGB LightGoldenrodYellow = RGB(250, 250, 210);
		const RGB LightGray = RGB(211, 211, 211);
		const RGB LightPink = RGB(255, 182, 193);
		const RGB LightSalmon = RGB(255, 160, 122);
		const RGB LightSeaGreen = RGB(32, 178, 170);
		const RGB LightSkyBlue = RGB(135, 206, 250);
		const RGB LightSlateGray = RGB(119, 136, 153);
		const RGB LightSteelBlue = RGB(176, 196, 222);
		const RGB LightYellow = RGB(255, 255, 224);
		const RGB Lime = RGB(191, 255, 0);
		const RGB LimeGreen = RGB(50, 205, 50);
		const RGB Linen = RGB(250, 240, 230);
		const RGB Magenta = RGB(255, 0, 255);
		const RGB Maroon = RGB(128, 0, 0);
		const RGB MediumAquamarine = RGB(102, 205, 170);
		const RGB MediumBlue = RGB(0, 0, 205);
		const RGB MediumOrchid = RGB(186, 85, 211);
		const RGB MediumPurple = RGB(147, 112, 219);
		const RGB MediumSeaGreen = RGB(60, 179, 113);
		const RGB MediumSlateBlue = RGB(123, 104, 238);
		const RGB MediumSpringGreen = RGB(0, 250, 154);
		const RGB MediumTurquoise = RGB(72, 209, 204);
		const RGB MediumVioletRed = RGB(199, 21, 133);
		const RGB MidnightBlue = RGB(25, 25, 112);
		const RGB MintCream = RGB(245, 255, 250);
		const RGB MistyRose = RGB(255, 228, 225);
		const RGB Moccasin = RGB(255, 228, 181);
		const RGB NajavoWhite = RGB(255, 222, 173);
		const RGB Navy = RGB(0, 0, 128);
		const RGB OldLace = RGB(253, 245, 230);
		const RGB Olive = RGB(128, 128, 0);
		const RGB OliveDrab = RGB(107, 142, 35);
		const RGB Orange = RGB(255, 165, 0);
		const RGB OrangeRed = RGB(255, 69, 0);
		const RGB Orchid = RGB(218, 112, 214);
		const RGB PaleGoldenrod = RGB(238, 232, 170);
		const RGB PaleGreen = RGB(152, 251, 152);
		const RGB PaleTurquoise = RGB(175, 238, 238);
		const RGB PaleVioletRed = RGB(219, 112, 147);
		const RGB PapayaWhip = RGB(255, 239, 213);
		const RGB PeachPuff = RGB(255, 218, 185);
		const RGB Peru = RGB(205, 133, 63);
		const RGB Pink = RGB(255, 192, 203);
		const RGB Plum = RGB(221, 160, 221);
		const RGB PowderBlue = RGB(176, 224, 230);
		const RGB Purple = RGB(128, 0, 128);
		const RGB Red = RGB(255, 0, 0);
		const RGB RosyBrown = RGB(188, 143, 143);
		const RGB RoyalBlue = RGB(65, 105, 225);
		const RGB SaddleBrown = RGB(139, 69, 19);
		const RGB Salmon = RGB(255, 140, 105);
		const RGB SandyBrown = RGB(244, 164, 96);
		const RGB SeaGreen = RGB(46, 139, 87);
		const RGB SeaShell = RGB(255, 245, 238);
		const RGB Sienna = RGB(136, 45, 23);
		const RGB Silver = RGB(192, 192, 192);
		const RGB SkyBlue = RGB(135, 206, 235);
	}

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

	RGBA RGB::ToRGBA() const { return RGBA(uR, uG, uB, 255); }

	HSL RGB::ToHSL() const {
		A_FL32 fR = static_cast<A_FL32>(uR);
		A_FL32 fG = static_cast<A_FL32>(uG);
		A_FL32 fB = static_cast<A_FL32>(uB);

		A_FL32 fMax = fmaxf(fmaxf(fR, fG), fB);
		A_FL32 fMin = fminf(fminf(fR, fG), fB);
		A_FL32 fDelta = (fMax - fMin) / 255.0f;

		A_FL32 fLightness = (fMax + fMin) / 510.0f;
		A_FL32 fSaturation = (fLightness > 0.0f) ? roundf((fDelta / (1 - fabsf(2 * fLightness - 1))) * 100.0f) / 100.0f : 0.0f;

		A_FL32 fHue = roundf(radtodeg(acosf((fR - half(fG) - half(fB)) / sqrtf(sq(fR) + sq(fG) + sq(fB) - fR * fG - fR * fB - fG * fB))));

		return HSL(static_cast<A_U16>(fB > fG ? (360.0f - fHue) : fHue), fSaturation, fLightness);
	}

	HEX RGB::ToHex() const { return HEX(); }

	RGBA::RGBA() : uR(0), uG(0), uB(0), uA(0) { }
	RGBA::RGBA(_In_ A_U8 uR, _In_ A_U8 uG, _In_ A_U8 uB, _In_ A_U8 uA) : uR(uR), uG(uG), uB(uB), uA(uA) {}
	RGBA::RGBA(_In_ const Vector4<>& v4Values, _In_ ColorRepresentation nRepresentation) { }

	String RGBA::ToString() const {
		return String();
	}

	RGB RGBA::ToRGB() const { return RGB(uR, uG, uB); }

	HSL RGBA::ToHSL() const {
		HSL hsl = ToRGB().ToHSL();
		hsl.fAlpha = static_cast<A_FL32>(uA) / 255.f;
		return hsl;
	}

	HEX RGBA::ToHex() const { return HEX(); }

	HSL::HSL() : uHue(0), fSaturation(0.0f), fLightness(0.0f), fAlpha(0.0f) {}
	HSL::HSL(_In_ A_U16 uHue, _In_ A_FL32 fSaturation, _In_ A_FL32 fLightness, _In_ A_FL32 fAlpha) : uHue(uHue), fSaturation(fSaturation), fLightness(fLightness), fAlpha(fAlpha) {}

	String HSL::ToString() const {
		String ret;
		ret.AddFormat(-1, "hsl(%hu, %hhu%%, %hhu%%, %f)", uHue, static_cast<A_U8>(fSaturation * 100.0f), static_cast<A_U8>(fLightness * 100.0f), fAlpha);
		return ret;
	}

	RGB HSL::ToRGB() const {
		A_FL64 fC = (1.f - fabs(2.f * fLightness - 1.f)) * fSaturation;
		A_FL64 fX = fC * (1.f - fabs(fmod(static_cast<A_FL64>(uHue) / 60.f, 2.f) - 1.f));
		A_FL64 fm = fLightness - fC / 2.f;

		A_FL64 fR, fG, fB;

		if (0 <= uHue && uHue < 60) {
			fR = fC;
			fG = fX;
			fB = 0.f;
		}
		else if (60 <= uHue && uHue < 120) {
			fR = fX;
			fG = fC;
			fB = 0.f;
		}
		else if (120 <= uHue && uHue < 180) {
			fR = 0.f;
			fG = fC;
			fB = fX;
		}
		else if (180 <= uHue && uHue < 240) {
			fR = 0.f;
			fG = fX;
			fB = fC;
		}
		else if (240 <= uHue && uHue < 300) {
			fR = fX;
			fG = 0.f;
			fB = fC;
		}
		else if (300 <= uHue && uHue < 360) {
			fR = fC;
			fG = 0.f;
			fB = fX;
		}
		else { fR = 0.f; fG = 0.f; fB = 0.f; }

		return RGB(
			static_cast<A_U16>(round((fR + fm) * 255.f)),
			static_cast<A_U16>(round((fG + fm) * 255.f)),
			static_cast<A_U16>(round((fB + fm) * 255.f))
		);
	}

	RGBA HSL::ToRGBA() const {
		RGB rgb = ToRGB();
		return RGBA(rgb.uR, rgb.uG,	rgb.uR, static_cast<A_U8>(fAlpha * 255.f));
	}

	HEX HSL::ToHex() const { return HEX(); }
}