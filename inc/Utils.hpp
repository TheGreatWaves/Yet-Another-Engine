#pragma once

#include "Common.hpp"

namespace Utils
{
    namespace Text
    {
        float GetSFMLTextMaxHeight(const sf::Text& InText)
        {
            // Extract font and character size from the text object.
            auto CharSize = InText.getCharacterSize();
            auto Font = InText.getFont();
            bool bBold = (InText.getStyle() & sf::Text::Bold);

            // Initialize the maximum height to 0.
            float Max = 0.f;

            // Iterate over the characters in the text string.
            for (size_t i = 0, End = InText.getString().getSize(); i < End; ++i)
            {
                // Get the character and its glyph from the font.
                sf::Uint32 Character = InText.getString()[i];
                auto Glyph = Font->getGlyph(Character, CharSize, bBold);

                // Update the maximum height if necessary.
                auto Height = Glyph.bounds.height;
                if (Height > Max) { Max = Height; }
            }

            // Return the maximum height of the text.
            return Max;
        }
    }
}
