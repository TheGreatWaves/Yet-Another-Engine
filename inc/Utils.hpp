#pragma once

#include "Common.hpp"

namespace Utils
{
	namespace Text
	{
		float GetSfmlTextMaxHeight(const sf::Text& in_text)
		{
			// Extract font and character size from the text object.
			auto char_size = in_text.getCharacterSize();
			auto font = in_text.getFont();
			bool bold = (in_text.getStyle() & sf::Text::Bold);

			// Initialize the maximum height to 0.
			float max = 0.f;

			// Iterate over the characters in the text string.
			for (size_t i = 0, end = in_text.getString().getSize(); i < end; ++i)
			{
				// Get the character and its glyph from the font.
				sf::Uint32 character = in_text.getString()[i];
				auto glyph = font->getGlyph(character, char_size, bold);
				// Update the maximum height if necessary.
				auto height = glyph.bounds.height;
				if (height > max)
				{
					max = height;
				}
			}

			// Return the maximum height of the text.
			return max;
		}
	} // namespace Text
} // namespace Utils