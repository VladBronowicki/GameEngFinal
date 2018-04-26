#include <GameObjects/Runner.hpp>
#include <Book/DataTables.hpp>
#include <Book/Utility.hpp>
#include <GameObjects/Ability.hpp>
#include <Book/CommandQueue.hpp>
#include <Book/ResourceHolder.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <cmath>


namespace INFINITYRUNNER
{
	const std::vector<RunnerData> Table = initializeRunnerData();

}

INFINITYRUNNER::Runner::Runner(Character type, const TextureHolder & textures, const FontHolder & fonts)
	: Actor(Table[type].health)
	, mCharacter(type)
	, mSprite(textures.get(Table[type].texture), Table[type].textureRect)
	, mAnimRun(textures.)
{
}


