#include "Color.h"

namespace Bokoblin
{
namespace MaterialDesignComponentsForSFML
{
//------------------------------------------------------------------------------------------------
//      STATIC MEMBER DATA : SPECIAL COLORS
//------------------------------------------------------------------------------------------------
const sf::Color Color::Transparent(0, 0, 0, 0);     //#00000000
const sf::Color Color::Black(0, 0, 0, 255);         //#000000FF
const sf::Color Color::White(255, 255, 255, 255);   //#FFFFFFFF

//------------------------------------------------------------------------------------------------
//      STATIC MEMBER DATA : MAIN COLORS
//------------------------------------------------------------------------------------------------

const sf::Color Color::MaterialRed(244, 67, 54);            //#F44336
const sf::Color Color::MaterialPink(233, 30, 99);           //#E91E63
const sf::Color Color::MaterialPurple(156, 39, 176);        //#9C27B0
const sf::Color Color::MaterialDeepPurple(103, 58, 183);    //#673AB7
const sf::Color Color::MaterialIndigo(63, 81, 181);         //#3F51B5
const sf::Color Color::MaterialBlue(33, 150, 243);          //#2196F3
const sf::Color Color::MaterialLightBlue(3, 169, 244);      //#03A9F4
const sf::Color Color::MaterialCyan(0, 188, 212);           //#00BCD4
const sf::Color Color::MaterialTeal(0, 150, 136);           //#009688
const sf::Color Color::MaterialGreen(76, 175, 80);          //#4CAF50
const sf::Color Color::MaterialLightGreen(139, 195, 74);    //#8BC34A
const sf::Color Color::MaterialLime(205, 220, 57);          //#CDDC39
const sf::Color Color::MaterialYellow(255, 235, 59);        //#FFEB3B
const sf::Color Color::MaterialAmber(255, 193, 7);          //#FFC107
const sf::Color Color::MaterialOrange(255, 152, 0);         //#FF9800
const sf::Color Color::MaterialDeepOrange(255, 87, 34);     //#FF5722
const sf::Color Color::MaterialBrown(121, 85, 72);          //#795548
const sf::Color Color::MaterialGrey(158, 158, 158);         //#9E9E9E
const sf::Color Color::MaterialBlueGrey(96, 125, 139);      //#607D8B

//------------------------------------------------------------------------------------------------
//      STATIC MEMBER DATA : ADDITIONAL RED COLORS
//------------------------------------------------------------------------------------------------
const sf::Color Color::MaterialRed50(255, 235, 238);        //#FFEBEE
const sf::Color Color::MaterialRed100(255, 205, 210);       //#FFCDD2
const sf::Color Color::MaterialRed200(239, 154, 154);       //#EF9A9A
const sf::Color Color::MaterialRed300(229, 115, 115);       //#E57373
const sf::Color Color::MaterialRed400(239, 83, 80);         //#EF5350
const sf::Color Color::MaterialRed500(244, 67, 54);         //#F44336
const sf::Color Color::MaterialRed600(229, 57, 53);         //#E53935
const sf::Color Color::MaterialRed700(211, 47, 47);         //#D32F2F
const sf::Color Color::MaterialRed800(198, 40, 40);         //#C62828
const sf::Color Color::MaterialRed900(183, 28, 28);         //#B71C1C
const sf::Color Color::MaterialRedA100(255, 138, 128);      //#FF8A80
const sf::Color Color::MaterialRedA200(255, 82, 82);        //#FF5252
const sf::Color Color::MaterialRedA400(255, 23, 68);        //#FF1744
const sf::Color Color::MaterialRedA700(213, 0, 0);          //#D50000

//------------------------------------------------------------------------------------------------
//      STATIC MEMBER DATA : ADDITIONAL PINK COLORS
//------------------------------------------------------------------------------------------------
const sf::Color Color::MaterialPink50(252, 228, 236);       //#FCE4EC
const sf::Color Color::MaterialPink100(248, 187, 208);      //#F8BBD0
const sf::Color Color::MaterialPink200(244, 143, 177);      //#F48FB1
const sf::Color Color::MaterialPink300(240, 98, 146);       //#F06292
const sf::Color Color::MaterialPink400(236, 64, 122);       //#EC407A
const sf::Color Color::MaterialPink500(233, 30, 99);        //#E91E63
const sf::Color Color::MaterialPink600(216, 27, 96);        //#D81B60
const sf::Color Color::MaterialPink700(194, 24, 91);        //#C2185B
const sf::Color Color::MaterialPink800(173, 20, 87);        //#AD1457
const sf::Color Color::MaterialPink900(136, 14, 79);        //#880E4F
const sf::Color Color::MaterialPinkA100(255, 128, 171);     //#FF80AB
const sf::Color Color::MaterialPinkA200(255, 64, 129);      //#FF4081
const sf::Color Color::MaterialPinkA400(245, 0, 87);        //#F50057
const sf::Color Color::MaterialPinkA700(197, 17, 98);       //#C51162

//------------------------------------------------------------------------------------------------
//      STATIC MEMBER DATA : ADDITIONAL PURPLE COLORS
//------------------------------------------------------------------------------------------------
const sf::Color Color::MaterialPurple50(243, 229, 245);     //#F3E5F5
const sf::Color Color::MaterialPurple100(225, 190, 231);    //#E1BEE7
const sf::Color Color::MaterialPurple200(206, 147, 216);    //#CE93D8
const sf::Color Color::MaterialPurple300(186, 104, 200);    //#BA68C8
const sf::Color Color::MaterialPurple400(171, 71, 188);     //#AB47BC
const sf::Color Color::MaterialPurple500(156, 39, 176);     //#9C27B0
const sf::Color Color::MaterialPurple600(142, 36, 170);     //#8E24AA
const sf::Color Color::MaterialPurple700(123, 31, 162);     //#7B1FA2
const sf::Color Color::MaterialPurple800(106, 27, 154);     //#6A1B9A
const sf::Color Color::MaterialPurple900(74, 20, 140);      //#4A148C
const sf::Color Color::MaterialPurpleA100(234, 128, 252);   //#EA80FC
const sf::Color Color::MaterialPurpleA200(224, 64, 251);    //#E040FB
const sf::Color Color::MaterialPurpleA400(213, 0, 249);     //#D500F9
const sf::Color Color::MaterialPurpleA700(170, 0, 255);     //#AA00FF

//------------------------------------------------------------------------------------------------
//      STATIC MEMBER DATA : ADDITIONAL INDIGO COLORS
//------------------------------------------------------------------------------------------------
const sf::Color Color::MaterialIndigo50(232, 234, 246);         //#E8EAF6
const sf::Color Color::MaterialIndigo100(197, 202, 233);        //#C5CAE9
const sf::Color Color::MaterialIndigo200(159, 168, 218);        //#9FA8DA
const sf::Color Color::MaterialIndigo300(121, 134, 203);        //#7986CB
const sf::Color Color::MaterialIndigo400(92, 107, 192);         //#5C6BC0
const sf::Color Color::MaterialIndigo500(63, 81, 181);          //#3F51B5
const sf::Color Color::MaterialIndigo600(57, 73, 171);          //#3949AB
const sf::Color Color::MaterialIndigo700(48, 63, 159);          //#303F9F
const sf::Color Color::MaterialIndigo800(40, 53, 147);          //#283593
const sf::Color Color::MaterialIndigo900(26, 35, 126);          //#1A237E
const sf::Color Color::MaterialIndigoA100(140, 158, 255);       //#8C9EFF
const sf::Color Color::MaterialIndigoA200(83, 109, 254);        //#536DFE
const sf::Color Color::MaterialIndigoA400(61, 90, 254);         //#3D5AFE
const sf::Color Color::MaterialIndigoA700(48, 79, 254);         //#304FFE

//------------------------------------------------------------------------------------------------
//      STATIC MEMBER DATA : ADDITIONAL BLUE COLORS
//------------------------------------------------------------------------------------------------
const sf::Color Color::MaterialBlue50(227, 242, 253);           //#E3F2FD
const sf::Color Color::MaterialBlue100(187, 222, 251);          //#BBDEFB
const sf::Color Color::MaterialBlue200(144, 202, 249);          //#90CAF9
const sf::Color Color::MaterialBlue300(100, 181, 246);          //#64B5F6
const sf::Color Color::MaterialBlue400(66, 165, 245);           //#42A5F5
const sf::Color Color::MaterialBlue500(33, 150, 243);           //#2196F3
const sf::Color Color::MaterialBlue600(30, 136, 229);           //#1E88E5
const sf::Color Color::MaterialBlue700(25, 118, 210);           //#1976D2
const sf::Color Color::MaterialBlue800(21, 101, 192);           //#1565C0
const sf::Color Color::MaterialBlue900(13, 71, 161);            //#0D47A1
const sf::Color Color::MaterialBlueA100(130, 177, 255);         //#82B1FF
const sf::Color Color::MaterialBlueA200(68, 138, 255);          //#448AFF
const sf::Color Color::MaterialBlueA400(41, 121, 255);          //#2979FF
const sf::Color Color::MaterialBlueA700(41, 98, 255);           //#2962FF

//------------------------------------------------------------------------------------------------
//      STATIC MEMBER DATA : ADDITIONAL LIGHT BLUE COLORS
//------------------------------------------------------------------------------------------------
const sf::Color Color::MaterialLightBlue50(225, 245, 254);      //#E1F5FE
const sf::Color Color::MaterialLightBlue100(179, 229, 252);     //#B3E5FC
const sf::Color Color::MaterialLightBlue200(129, 212, 250);     //#81D4FA
const sf::Color Color::MaterialLightBlue300(79, 195, 247);      //#4FC3F7
const sf::Color Color::MaterialLightBlue400(41, 182, 246);      //#29B6F6
const sf::Color Color::MaterialLightBlue500(3, 169, 244);       //#03A9F4
const sf::Color Color::MaterialLightBlue600(3, 155, 229);       //#039BE5
const sf::Color Color::MaterialLightBlue700(2, 136, 209);       //#0288D1
const sf::Color Color::MaterialLightBlue800(2, 119, 189);       //#0277BD
const sf::Color Color::MaterialLightBlue900(1, 87, 155);        //#01579B
const sf::Color Color::MaterialLightBlueA100(128, 216, 255);    //#80D8FF
const sf::Color Color::MaterialLightBlueA200(64, 196, 255);     //#40C4FF
const sf::Color Color::MaterialLightBlueA400(0, 176, 255);      //#00B0FF
const sf::Color Color::MaterialLightBlueA700(0, 145, 234);      //#0091EA

//------------------------------------------------------------------------------------------------
//      STATIC MEMBER DATA : ADDITIONAL CYAN COLORS
//------------------------------------------------------------------------------------------------
const sf::Color Color::MaterialCyan50(224, 247, 250);           //#E0F7FA
const sf::Color Color::MaterialCyan100(178, 235, 242);          //#B2EBF2
const sf::Color Color::MaterialCyan200(128, 222, 234);          //#80DEEA
const sf::Color Color::MaterialCyan300(77, 208, 225);           //#4DD0E1
const sf::Color Color::MaterialCyan400(38, 198, 218);           //#26C6DA
const sf::Color Color::MaterialCyan500(0, 188, 212);            //#00BCD4
const sf::Color Color::MaterialCyan600(0, 172, 193);            //#00ACC1
const sf::Color Color::MaterialCyan700(0, 151, 167);            //#0097A7
const sf::Color Color::MaterialCyan800(0, 131, 143);            //#00838F
const sf::Color Color::MaterialCyan900(0, 96, 100);             //#006064
const sf::Color Color::MaterialCyanA100(132, 255, 255);         //#84FFFF
const sf::Color Color::MaterialCyanA200(24, 255, 255);          //#18FFFF
const sf::Color Color::MaterialCyanA400(0, 229, 255);           //#00E5FF
const sf::Color Color::MaterialCyanA700(0, 184, 212);           //#00B8D4

//------------------------------------------------------------------------------------------------
//      STATIC MEMBER DATA : ADDITIONAL TEAL COLORS
//------------------------------------------------------------------------------------------------
const sf::Color Color::MaterialTeal50(224, 242, 241);           //#E0F2F1
const sf::Color Color::MaterialTeal100(178, 223, 219);          //#B2DFDB
const sf::Color Color::MaterialTeal200(128, 203, 196);          //#80CBC4
const sf::Color Color::MaterialTeal300(77, 182, 172);           //#4DB6AC
const sf::Color Color::MaterialTeal400(38, 166, 154);           //#26A69A
const sf::Color Color::MaterialTeal500(0, 150, 136);            //#009688
const sf::Color Color::MaterialTeal600(0, 137, 123);            //#00897B
const sf::Color Color::MaterialTeal700(0, 121, 107);            //#00796B
const sf::Color Color::MaterialTeal800(0, 105, 92);             //#00695C
const sf::Color Color::MaterialTeal900(0, 77, 64);              //#004D40
const sf::Color Color::MaterialTealA100(167, 255, 235);         //#A7FFEB
const sf::Color Color::MaterialTealA200(100, 255, 218);         //#64FFDA
const sf::Color Color::MaterialTealA400(29, 233, 182);          //#1DE9B6
const sf::Color Color::MaterialTealA700(0, 191, 165);           //#00BFA5

//------------------------------------------------------------------------------------------------
//      STATIC MEMBER DATA : ADDITIONAL GREEN COLORS
//------------------------------------------------------------------------------------------------
const sf::Color Color::MaterialGreen50(232, 245, 233);          //#E8F5E9
const sf::Color Color::MaterialGreen100(200, 230, 201);         //#C8E6C9
const sf::Color Color::MaterialGreen200(165, 214, 167);         //#A5D6A7
const sf::Color Color::MaterialGreen300(129, 199, 132);         //#81C784
const sf::Color Color::MaterialGreen400(102, 187, 106);         //#66BB6A
const sf::Color Color::MaterialGreen500(76, 175, 80);           //#4CAF50
const sf::Color Color::MaterialGreen600(67, 160, 71);           //#43A047
const sf::Color Color::MaterialGreen700(56, 142, 60);           //#388E3C
const sf::Color Color::MaterialGreen800(46, 125, 50);           //#2E7D32
const sf::Color Color::MaterialGreen900(27, 94, 32);            //#1B5E20
const sf::Color Color::MaterialGreenA100(185, 246, 202);        //#B9F6CA
const sf::Color Color::MaterialGreenA200(105, 240, 174);        //#69F0AE
const sf::Color Color::MaterialGreenA400(0, 230, 118);          //#00E676
const sf::Color Color::MaterialGreenA700(0, 200, 83);           //#00C853

//------------------------------------------------------------------------------------------------
//      STATIC MEMBER DATA : ADDITIONAL LIGHT GREEN COLORS
//------------------------------------------------------------------------------------------------
const sf::Color Color::MaterialLightGreen50(241, 248, 233);     //#F1F8E9
const sf::Color Color::MaterialLightGreen100(220, 237, 200);    //#DCEDC8
const sf::Color Color::MaterialLightGreen200(197, 225, 165);    //#C5E1A5
const sf::Color Color::MaterialLightGreen300(174, 213, 129);    //#AED581
const sf::Color Color::MaterialLightGreen400(156, 204, 101);    //#9CCC65
const sf::Color Color::MaterialLightGreen500(139, 195, 74);     //#8BC34A
const sf::Color Color::MaterialLightGreen600(124, 179, 66);     //#7CB342
const sf::Color Color::MaterialLightGreen700(104, 159, 56);     //#689F38
const sf::Color Color::MaterialLightGreen800(85, 139, 47);      //#558B2F
const sf::Color Color::MaterialLightGreen900(51, 105, 30);      //#33691E
const sf::Color Color::MaterialLightGreenA100(204, 255, 144);   //#CCFF90
const sf::Color Color::MaterialLightGreenA200(178, 255, 89);    //#B2FF59
const sf::Color Color::MaterialLightGreenA400(118, 255, 3);     //#76FF03
const sf::Color Color::MaterialLightGreenA700(100, 221, 23);    //#64DD17

//------------------------------------------------------------------------------------------------
//      STATIC MEMBER DATA : ADDITIONAL LIME COLORS
//------------------------------------------------------------------------------------------------
const sf::Color Color::MaterialLime50(249, 251, 231);           //#F9FBE7
const sf::Color Color::MaterialLime100(240, 244, 195);          //#F0F4C3
const sf::Color Color::MaterialLime200(230, 238, 156);          //#E6EE9C
const sf::Color Color::MaterialLime300(220, 231, 117);          //#DCE775
const sf::Color Color::MaterialLime400(212, 225, 87);           //#D4E157
const sf::Color Color::MaterialLime500(205, 220, 57);           //#CDDC39
const sf::Color Color::MaterialLime600(192, 202, 51);           //#C0CA33
const sf::Color Color::MaterialLime700(175, 180, 43);           //#AFB42B
const sf::Color Color::MaterialLime800(158, 157, 36);           //#9E9D24
const sf::Color Color::MaterialLime900(130, 119, 23);           //#827717
const sf::Color Color::MaterialLimeA100(244, 255, 129);         //#F4FF81
const sf::Color Color::MaterialLimeA200(238, 255, 65);          //#EEFF41
const sf::Color Color::MaterialLimeA400(198, 255, 0);           //#C6FF00
const sf::Color Color::MaterialLimeA700(174, 234, 0);           //#AEEA00

//------------------------------------------------------------------------------------------------
//      STATIC MEMBER DATA : ADDITIONAL YELLOW COLORS
//------------------------------------------------------------------------------------------------
const sf::Color Color::MaterialYellow50(255, 253, 231);         //#FFFDE7
const sf::Color Color::MaterialYellow100(255, 249, 196);        //#FFF9C4
const sf::Color Color::MaterialYellow200(255, 245, 157);        //#FFF59D
const sf::Color Color::MaterialYellow300(255, 241, 118);        //#FFF176
const sf::Color Color::MaterialYellow400(255, 238, 88);         //#FFEE58
const sf::Color Color::MaterialYellow500(255, 235, 59);         //#FFEB3B
const sf::Color Color::MaterialYellow600(253, 216, 53);         //#FDD835
const sf::Color Color::MaterialYellow700(251, 192, 45);         //#FBC02D
const sf::Color Color::MaterialYellow800(249, 168, 37);         //#F9A825
const sf::Color Color::MaterialYellow900(245, 127, 23);         //#F57F17
const sf::Color Color::MaterialYellowA100(255, 255, 141);       //#FFFF8D
const sf::Color Color::MaterialYellowA200(255, 255, 0);         //#FFFF00
const sf::Color Color::MaterialYellowA400(255, 234, 0);         //#FFEA00
const sf::Color Color::MaterialYellowA700(255, 214, 0);         //#FFD600

//------------------------------------------------------------------------------------------------
//      STATIC MEMBER DATA : ADDITIONAL AMBER COLORS
//------------------------------------------------------------------------------------------------
const sf::Color Color::MaterialAmber50(255, 248, 225);          //#FFF8E1
const sf::Color Color::MaterialAmber100(255, 236, 179);         //#FFECB3
const sf::Color Color::MaterialAmber200(255, 224, 130);         //#FFE082
const sf::Color Color::MaterialAmber300(255, 213, 79);          //#FFD54F
const sf::Color Color::MaterialAmber400(255, 202, 40);          //#FFCA28
const sf::Color Color::MaterialAmber500(255, 193, 7);           //#FFC107
const sf::Color Color::MaterialAmber600(255, 179, 0);           //#FFB300
const sf::Color Color::MaterialAmber700(255, 160, 0);           //#FFA000
const sf::Color Color::MaterialAmber800(255, 143, 0);           //#FF8F00
const sf::Color Color::MaterialAmber900(255, 111, 0);           //#FF6F00
const sf::Color Color::MaterialAmberA100(255, 229, 127);        //#FFE57F
const sf::Color Color::MaterialAmberA200(255, 215, 64);         //#FFD740
const sf::Color Color::MaterialAmberA400(255, 196, 0);          //#FFC400
const sf::Color Color::MaterialAmberA700(255, 171, 0);          //#FFAB00

//------------------------------------------------------------------------------------------------
//      STATIC MEMBER DATA : ADDITIONAL ORANGE COLORS
//------------------------------------------------------------------------------------------------
const sf::Color Color::MaterialOrange50(255, 243, 224);         //#FFF3E0
const sf::Color Color::MaterialOrange100(255, 224, 178);        //#FFE0B2
const sf::Color Color::MaterialOrange200(255, 204, 128);        //#FFCC80
const sf::Color Color::MaterialOrange300(255, 183, 77);         //#FFB74D
const sf::Color Color::MaterialOrange400(255, 167, 38);         //#FFA726
const sf::Color Color::MaterialOrange500(255, 152, 0);          //#FF9800
const sf::Color Color::MaterialOrange600(251, 140, 0);          //#FB8C00
const sf::Color Color::MaterialOrange700(245, 124, 0);          //#F57C00
const sf::Color Color::MaterialOrange800(239, 108, 0);          //#EF6C00
const sf::Color Color::MaterialOrange900(230, 81, 0);           //#E65100
const sf::Color Color::MaterialOrangeA100(255, 209, 128);       //#FFD180
const sf::Color Color::MaterialOrangeA200(255, 171, 64);        //#FFAB40
const sf::Color Color::MaterialOrangeA400(255, 145, 0);         //#FF9100
const sf::Color Color::MaterialOrangeA700(255, 109, 0);         //#FF6D00

//------------------------------------------------------------------------------------------------
//      STATIC MEMBER DATA : ADDITIONAL DEEP ORANGE COLORS
//------------------------------------------------------------------------------------------------
const sf::Color Color::MaterialDeepOrange50(251, 233, 231);     //#FBE9E7
const sf::Color Color::MaterialDeepOrange100(255, 204, 188);    //#FFCCBC
const sf::Color Color::MaterialDeepOrange200(255, 171, 145);    //#FFAB91
const sf::Color Color::MaterialDeepOrange300(255, 138, 101);    //#FF8A65
const sf::Color Color::MaterialDeepOrange400(255, 112, 67);     //#FF7043
const sf::Color Color::MaterialDeepOrange500(255, 87, 34);      //#FF5722
const sf::Color Color::MaterialDeepOrange600(244, 81, 30);      //#F4511E
const sf::Color Color::MaterialDeepOrange700(230, 74, 25);      //#E64A19
const sf::Color Color::MaterialDeepOrange800(216, 67, 21);      //#D84315
const sf::Color Color::MaterialDeepOrange900(191, 54, 12);      //#BF360C
const sf::Color Color::MaterialDeepOrangeA100(255, 158, 128);   //#FF9E80
const sf::Color Color::MaterialDeepOrangeA200(255, 110, 64);    //#FF6E40
const sf::Color Color::MaterialDeepOrangeA400(255, 61, 0);      //#FF3D00
const sf::Color Color::MaterialDeepOrangeA700(221, 44, 0);      //#DD2C00

//------------------------------------------------------------------------------------------------
//      STATIC MEMBER DATA : ADDITIONAL BROWN COLORS
//------------------------------------------------------------------------------------------------
const sf::Color Color::MaterialBrown50(239, 235, 233);          //#EFEBE9
const sf::Color Color::MaterialBrown100(215, 204, 200);         //#D7CCC8
const sf::Color Color::MaterialBrown200(188, 170, 164);         //#BCAAA4
const sf::Color Color::MaterialBrown300(161, 136, 127);         //#A1887F
const sf::Color Color::MaterialBrown400(141, 110, 99);          //#8D6E63
const sf::Color Color::MaterialBrown500(121, 85, 72);           //#795548
const sf::Color Color::MaterialBrown600(109, 76, 65);           //#6D4C41
const sf::Color Color::MaterialBrown700(93, 64, 55);            //#5D4037
const sf::Color Color::MaterialBrown800(78, 52, 46);            //#4E342E
const sf::Color Color::MaterialBrown900(62, 39, 35);            //#3E2723

//------------------------------------------------------------------------------------------------
//      STATIC MEMBER DATA : ADDITIONAL GRAY COLORS
//------------------------------------------------------------------------------------------------
const sf::Color Color::MaterialGray50(250, 250, 250);           //#FAFAFA
const sf::Color Color::MaterialGray100(245, 245, 245);          //#F5F5F5
const sf::Color Color::MaterialGray200(238, 238, 238);          //#EEEEEE
const sf::Color Color::MaterialGray300(224, 224, 224);          //#E0E0E0
const sf::Color Color::MaterialGray400(189, 189, 189);          //#BDBDBD
const sf::Color Color::MaterialGray500(158, 158, 158);          //#9E9E9E
const sf::Color Color::MaterialGray600(117, 117, 117);          //#757575
const sf::Color Color::MaterialGray700(97, 97, 97);             //#616161
const sf::Color Color::MaterialGray800(66, 66, 66);             //#424242
const sf::Color Color::MaterialGray900(33, 33, 33);             //#212121

//------------------------------------------------------------------------------------------------
//      STATIC MEMBER DATA : ADDITIONAL BLUE GRAY COLORS
//------------------------------------------------------------------------------------------------
const sf::Color Color::MaterialBlueGray50(236, 239, 241);       //#ECEFF1
const sf::Color Color::MaterialBlueGray100(207, 216, 220);      //#CFD8DC
const sf::Color Color::MaterialBlueGray200(176, 190, 197);      //#B0BEC5
const sf::Color Color::MaterialBlueGray300(144, 164, 174);      //#90A4AE
const sf::Color Color::MaterialBlueGray400(120, 144, 156);      //#78909C
const sf::Color Color::MaterialBlueGray500(96, 125, 139);       //#607D8B
const sf::Color Color::MaterialBlueGray600(84, 110, 122);       //#546E7A
const sf::Color Color::MaterialBlueGray700(69, 90, 100);        //#455A64
const sf::Color Color::MaterialBlueGray800(55, 71, 79);         //#37474F
const sf::Color Color::MaterialBlueGray900(38, 50, 56);         //#263238

} //namespace MaterialDesignComponentsForSFML
} //namespace Bokoblin