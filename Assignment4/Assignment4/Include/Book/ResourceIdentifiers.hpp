#ifndef BOOK_RESOURCEIDENTIFIERS_HPP
#define BOOK_RESOURCEIDENTIFIERS_HPP


// Forward declaration of SFML classes
namespace sf
{
	class Texture;
	class Font;
	class Shader;
}

namespace Textures
{
	enum ID
	{
		Actors,
		Entities,
		Jungle,
		TitleScreen,
		Buttons,
		Explosion,
		Particle,
		FinishLine,
		Run_BG,
		Run_BG_Building1,
		Run_BG_Building2,
		Run_BG_Building3,
		Run_Character_Jump,
		Run_Character_Slide,
		Run_Character_1,
		Run_Character_2,
		Run_Character_3,
		Run_Character_4,
		Run_Character_5,
		Run_Character_6,
		Run_Character_7,
		Run_Character_8,
		Run_Character_9,
		Run_Character_10,
		Run_Character_11,
		Run_Character_12,
		Run_FG_win1,
		Run_FG_win2,
		Run_FG_nowin1,
		Run_FG_nowin2,
		Run_FG_instr,
		Run_Props_BlackBird,
		Run_Props_WhiteBird,
		Run_Props_Lamp,
		Run_Props_HouseNoWin,
		Run_Props_HouseWin,
		Run_Props_Flowers,
		Run_ParticleTexture_Rain,
	};

}

namespace Shaders
{
	enum ID
	{
		BrightnessPass,
		DownSamplePass,
		GaussianBlurPass,
		AddPass,
	};
}

namespace Fonts
{
	enum ID
	{
		Main,
	};
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID>	TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>			FontHolder;
typedef ResourceHolder<sf::Shader, Shaders::ID>			ShaderHolder;

#endif // BOOK_RESOURCEIDENTIFIERS_HPP
