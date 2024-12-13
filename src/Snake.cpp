#include "Snake.hpp"

#include <stdexcept>

Snake::Snake() : m_body(std::list<sf::Sprite>(4)), m_directions(4, sf::Vector2f{1.f, 0.f})
{
    m_head = --m_body.end();
    m_tail = m_body.begin();
}

Snake::~Snake()
{
}

void Snake::Init(const sf::Texture &texture)
{
    float x = 16.f;
    for (auto &piece : m_body)
    {
        piece.setTexture(texture);
        piece.setPosition({x, 16.f});
        x += 16.f;
    }

    if (!m_collisionSoundBuffer.loadFromFile("assets/sounds/collision.ogg"))
    {
        throw std::runtime_error("No se pudo cargar el archivo de sonido de colisión.");
    }
    m_collisionSound.setBuffer(m_collisionSoundBuffer);

    if (!m_eatSoundBuffer.loadFromFile("assets/sounds/eat.ogg"))
    {
        throw std::runtime_error("No se pudo cargar el archivo de sonido de comer.");
    }
    m_eatSound.setBuffer(m_eatSoundBuffer);
}

void Snake::PlayCollisionSound()
{
    m_collisionSound.play();
}

float Snake::GetRotationAngle(const sf::Vector2f &direction)
{
    if (direction == sf::Vector2f{1.f, 0.f}) // Derecha
        return 0.f;
    if (direction == sf::Vector2f{0.f, 1.f}) // Abajo
        return 90.f;
    if (direction == sf::Vector2f{-1.f, 0.f}) // Izquierda
        return 180.f;
    if (direction == sf::Vector2f{0.f, -1.f}) // Arriba
        return 270.f;

    return 0.f; // Por defecto (puedes manejar otros casos si es necesario)
}


void Snake::Move(const sf::Vector2f &direction)
{
    // Actualizar la dirección de cada segmento
    m_directions.insert(m_directions.begin(), direction);
    m_directions.pop_back();

    // Rotar y mover cada segmento
    auto dirIt = m_directions.begin();
    for (auto &piece : m_body)
    {
        piece.setRotation(GetRotationAngle(*dirIt));
        ++dirIt;
    }

    // Mover la cola al frente (circular)
    m_tail->setPosition(m_head->getPosition() + direction);
    m_head = m_tail;
    ++m_tail;

    if (m_tail == m_body.end())
    {
        m_tail = m_body.begin();
    }
}


bool Snake::IsOn(const sf::Sprite &other) const
{
    return other.getGlobalBounds().intersects(m_head->getGlobalBounds());
}

void Snake::Grow(const sf::Vector2f &direction)
{
    sf::Sprite newPiece;
    newPiece.setTexture(*(m_body.begin()->getTexture()));
    newPiece.setPosition(m_head->getPosition() + direction);
    newPiece.setRotation(GetRotationAngle(direction));

    // Insertar el nuevo segmento en el cuerpo
    m_head = m_body.insert(++m_head, newPiece);

    m_directions.insert(m_directions.begin() + std::distance(m_body.begin(), m_head), direction);

}


void Snake::PlayEatSound()
{
    m_eatSound.play();
}

bool Snake::IsSelfIntersecting() const
{
    bool flag = false;

    for (auto piece = m_body.begin(); piece != m_body.end(); ++piece)
    {
        if (m_head != piece)
        {
            flag = IsOn(*piece);

            if (flag)
            {
                break;
            }
        }
    }

    return flag;
}

void Snake::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (auto &piece : m_body)
    {
        target.draw(piece);
    }
}
