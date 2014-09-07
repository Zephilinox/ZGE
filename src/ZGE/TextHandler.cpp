#include "ZGE/TextHandler.hpp"

using namespace zge;

TextHandler::TextHandler(std::string textString, std::string fontLocation, unsigned characterSize, sf::Vector2f position, Origin origin):
m_font(fontLocation),
m_position(position),
m_origin(origin),
m_borderEnabled(false),
m_borderColor(sf::Color::Black)
{
    m_text.setFont(m_font);
    m_text.setString(textString);
    m_text.setCharacterSize(characterSize);

    updatePosition();
}

void TextHandler::handleEvent(const sf::Event& event)
{

}

void TextHandler::update(float dt)
{
    updatePosition();
}

void TextHandler::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (m_borderEnabled)
    {
        sf::Vector2f pos = m_text.getPosition();
        sf::Text text = m_text;

        //We need to use the alpha of the original text so that the border can fade along with it.
        text.setColor(sf::Color(m_borderColor.r, m_borderColor.g, m_borderColor.b, m_text.getColor().a));

        text.setPosition(pos.x - 1, pos.y);
        target.draw(text, states);

        text.setPosition(pos.x + 1, pos.y);
        target.draw(text, states);

        text.setPosition(pos.x, pos.y - 1);
        target.draw(text, states);

        text.setPosition(pos.x, pos.y + 1);
        target.draw(text, states);

        target.draw(m_text, states);
    }
    else
    {
        target.draw(m_text, states);
    }
}

void TextHandler::setText(std::string str)
{
    m_text.setString(str);
}

void TextHandler::setColor(sf::Color col)
{
    m_text.setColor(col);
}

void TextHandler::enableBorder(bool enable)
{
    m_borderEnabled = enable;
}

void TextHandler::setBorderColor(sf::Color col)
{
    m_borderColor = col;
}

sf::Color TextHandler::getColor()
{
    return m_text.getColor();
}

void TextHandler::updatePosition()
{
    switch(m_origin)
    {
        case Origin::TopLeft:
        {
            m_text.setPosition(m_position.x,
                               m_position.y);
            break;
        }

        case Origin::TopRight:
        {
            m_text.setPosition(m_position.x - (m_text.getLocalBounds().width + m_text.getLocalBounds().left),
                               m_position.y);
            break;
        }

        case Origin::TopCentre:
        {
            m_text.setPosition(m_position.x - ((m_text.getLocalBounds().width + m_text.getLocalBounds().left)/2),
                               m_position.y);
            break;
        }

        case Origin::BottomLeft:
        {
            m_text.setPosition(m_position.x,
                               m_position.y - (m_text.getLocalBounds().height + m_text.getLocalBounds().top));
            break;
        }

        case Origin::BottomRight:
        {
            m_text.setPosition(m_position.x - (m_text.getLocalBounds().width + m_text.getLocalBounds().left),
                               m_position.y - (m_text.getLocalBounds().height + m_text.getLocalBounds().top));
            break;
        }

        case Origin::MiddleCentre:
        default:
        {
            m_text.setPosition(m_position.x - ((m_text.getLocalBounds().width + m_text.getLocalBounds().left)/2),
                               m_position.y - ((m_text.getLocalBounds().height + m_text.getLocalBounds().top))/2);
            break;
        }
    }
}
