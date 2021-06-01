#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "utility.h"
#include "planet.h"
#include "text.h"

int main()
{
    const float G = 6.67f * 1000;

    float currentMass = 10.0f;
    int currentInteractionMode = 0;
    sf::Vector2f currentVelocity = sf::Vector2f(0, 0);

    int windowWidth = 800, windowHeight = 500;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Gravity Sim");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);


    //storage
    std::vector<Planet> planets;


    //UI ELEMENTS

    //planet count text
    Text planetCountText = Text(13, "Planet Count : 0", sf::Vector2f(0, 0));

    //interaction text
    Text interactionModeText = Text(13, "Interaction Mode: ALL", sf::Vector2f(0,15));

    //mass text
    Text massText = Text(13, "Mass: 1", sf::Vector2f(float(windowWidth), 0));
    massText.setOrigin(2);

    //velocity text
	Text velocityText = Text(13, "Velocity: 10,20", sf::Vector2f(float(windowWidth), 15));
	velocityText.setOrigin(2);

    //Velocity line
    sf::RectangleShape velocityLine = sf::RectangleShape(sf::Vector2f(100,1));
    velocityLine.setFillColor(sf::Color(150, 150, 150));

    sf::Clock deltaClock;
    float deltaTime = 0.0f, debouceClock = 0.0f, lastSpawn = 0.0f, lastButton = 0.0f;
    sf::Time dt;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

			if (event.type == sf::Event::MouseWheelMoved)
			{
                int mouseWheelDelta = event.mouseWheel.delta;
                if (mouseWheelDelta > 0) {
                    currentMass += 5;
                }
                else if (mouseWheelDelta < 0) {
                    currentMass -= 5;
                    if (currentMass < 1) {
                        currentMass = 1;
                    }
                }
			}
        }

		
        //INPUT
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (debouceClock - lastSpawn > 150) {
                //Spawn new planet
				sf::Vector2i mousePixelPos = sf::Mouse::getPosition(window);
				sf::Vector2f worldPos = window.mapPixelToCoords(mousePixelPos);
				Planet newPlanet(currentMass * 1.25f, sf::Color(255, 255, 255), currentMass, false, worldPos , currentVelocity);
				planets.push_back(newPlanet);
				lastSpawn = debouceClock;

                
            }
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			if (debouceClock - lastSpawn > 150) {
				//Spawn new planet
				sf::Vector2i mousePixelPos = sf::Mouse::getPosition(window);
				sf::Vector2f worldPos = window.mapPixelToCoords(mousePixelPos);
				Planet newPlanet( currentMass*1.25f, sf::Color(255, 120, 120), currentMass,true, worldPos);
				planets.push_back(newPlanet);
				lastSpawn = debouceClock;


			}
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)) {
			if (debouceClock - lastSpawn> 150) {
                planets.clear();
				lastButton = debouceClock;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
			if (debouceClock - lastButton > 150) {
                currentInteractionMode += 1;
                if (currentInteractionMode >= 4) {
                    currentInteractionMode = 0;
                }
				lastButton = debouceClock;
			}
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			if (debouceClock - lastButton > 150) {
				currentVelocity.y -= 10.0f;
				lastButton = debouceClock;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			if (debouceClock - lastButton > 150) {
				currentVelocity.y += 10.0f;
				lastButton = debouceClock;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			if (debouceClock - lastButton > 150) {
				currentVelocity.x += 10.0f;
				lastButton = debouceClock;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			if (debouceClock - lastButton > 150) {
				currentVelocity.x -= 10.0f;
				lastButton = debouceClock;
			}
		}

        
        


        window.clear();
        
        //std::cout << "Number of planets: " << planets.size() << std::endl;

        //apply gravity
        for (unsigned int i = 0 ; i < planets.size();i++) 
        {
            for (unsigned int j = 0 ;j < planets.size(); j++)
            {
                if (currentInteractionMode == 0) {
                    //continue normally
                }
                else if(currentInteractionMode==1)
                {
                    //only attract to passive bodies
                    if (!(planets[i].m_isPassive&&!planets[j].m_isPassive)) {
                        continue;
                    }
                }
				else if (currentInteractionMode == 2)
				{
					//only attract to active bodies
                    if (!((planets[i].m_isPassive && !planets[j].m_isPassive) || (!planets[i].m_isPassive && !planets[j].m_isPassive)))
			        {
                        continue;
					}
				}
                else if (currentInteractionMode == 3) {
                    //skip
                    continue;
                }


                if (planets[i].m_position == planets[j].m_position) {
                    continue;
                }
                float distance = getDistance(planets[i].m_position, planets[j].m_position);
                float force;
                sf::Vector2f forceDirection = sf::Vector2f(0,0), forceVector = sf::Vector2f(0, 0);
                if (distance < planets[i].m_radius || distance < planets[j].m_radius) {
                    force = 0.0f;
                }
                else {
                    force = ((G * planets[i].m_mass * planets[j].m_mass) / (distance * distance));
                    forceDirection = getNormlizedVector(planets[i].m_position, planets[j].m_position);
                    forceVector = forceDirection * force;
                }
                planets[j].applyForce(forceVector,100.0f,deltaTime);
            }
        }

        //update planets' position

        for (unsigned int i = 0; i < planets.size(); i++) {
            planets[i].updatePosition(deltaTime);
        }

        //update UI
        {
            {
				int planetCount = planets.size();
				std::string planetCountTextString = "Planet count: " + std::to_string(planetCount);
				planetCountText.setText(planetCountTextString);
            }
            {
                std::string massTextString = "Mass: " + std::to_string(ceil(currentMass));
                massText.setText(massTextString);
                massText.recalculateOrigin();
            }
            {
                std::string currentInteractionModeString;
                switch (currentInteractionMode)
                {
				case 0:
				{
					currentInteractionModeString = "ALL";
				}break;
				case 1:
				{
					currentInteractionModeString = "ONLY WITH PASSIVE";
				}break;
				case 2:
				{
					currentInteractionModeString = "ONLY WITH ACTIVE (does not work yet)";
				}break;
				case 3:
				{
					currentInteractionModeString = "NONE";
				}break;
                default:
                    currentInteractionModeString = "INVALID";
                    break;
                }

                std::string interactionModeTextString = "Interaction Mode: " + currentInteractionModeString;
                interactionModeText.setText(interactionModeTextString);
                interactionModeText.recalculateOrigin();
            }
            {
                std::string currentVelocityString = "Velocity: " + std::to_string(currentVelocity.x) + "," + std::to_string((currentVelocity.y*-1.0f));
                velocityText.setText(currentVelocityString);
                velocityText.recalculateOrigin();
            }
            {
				sf::Vector2i mousePixelPos = sf::Mouse::getPosition(window);
				sf::Vector2f worldPos = window.mapPixelToCoords(mousePixelPos);
                velocityLine.setPosition(worldPos);
                float rotation = getVectorAngle(currentVelocity);
				velocityLine.setRotation(rotation);
				float magnitude = getVectorMagnitude(currentVelocity);
				velocityLine.setScale(magnitude/100.0f, 1);


            }
        }


        //draw UI
        window.draw(planetCountText.m_text);
        window.draw(interactionModeText.m_text);
        window.draw(massText.m_text);
        window.draw(velocityText.m_text);
        window.draw(velocityLine);

        //draw planets
        for (Planet planet : planets) {
            window.draw(planet.m_shape);
        }

        window.display();
        dt = deltaClock.restart();
        deltaTime = dt.asSeconds();
        debouceClock += dt.asMilliseconds();
    }

    return 0;
}