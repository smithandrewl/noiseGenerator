#include <TGUI/TGUI.hpp>
#include "noise_generator.h"

void loadWidgets(tgui::Gui& gui) {
    auto theme = std::make_shared<tgui::Theme>("TGUI/widgets/Black.txt");

    tgui::Button::Ptr button = theme->load("Button");

    button->setText("Generate");
    button->setSize({400, 45});
    button->setPosition(25, 825);

    gui.add(button);

    tgui::Label::Ptr distanceFuncLabel = theme->load("Label");
    distanceFuncLabel->setText("Distance Function:");
    distanceFuncLabel->setSize({200, 25});
    distanceFuncLabel->setPosition(25, 700);

    gui.add(distanceFuncLabel);

    tgui::ComboBox::Ptr distanceFuncComboBox = theme->load("ComboBox");
    distanceFuncComboBox->setSize({200, 30});
    distanceFuncComboBox->setPosition(220, 700);
    distanceFuncComboBox->addItem("Euclidean");
    distanceFuncComboBox->addItem("Manhattan");
    distanceFuncComboBox->addItem("Chebyshev");
    distanceFuncComboBox->addItem("Other");
    distanceFuncComboBox->addItem("OrthEuclidean");
    distanceFuncComboBox->addItem("OrthManhattan");
    distanceFuncComboBox->addItem("OrthChebyshev");
    distanceFuncComboBox->addItem("OrthOther");

    distanceFuncComboBox->setSelectedItem("Euclidean");
    gui.add(distanceFuncComboBox);

    tgui::Label::Ptr colorFuncLabel = theme->load("Label");
    colorFuncLabel->setText("Color Function:");
    colorFuncLabel->setSize({200, 25});
    colorFuncLabel->setPosition(25, 740);

    gui.add(colorFuncLabel);

    tgui::ComboBox::Ptr colorFuncComboBox = theme->load("ComboBox");
    colorFuncComboBox->setSize({200, 30});
    colorFuncComboBox->setPosition(220, 740);
    colorFuncComboBox->addItem("Linear");
    colorFuncComboBox->addItem("Xor");
    colorFuncComboBox->addItem("Mod");
    colorFuncComboBox->addItem("And");
    colorFuncComboBox->addItem("Sin");
    colorFuncComboBox->addItem("Tan");

    colorFuncComboBox->setSelectedItem("Linear");
    gui.add(colorFuncComboBox);

    tgui::Label::Ptr pointsLabel = theme->load("Label");
    pointsLabel->setText("Number of Points:");
    pointsLabel->setSize({200, 25});
    pointsLabel->setPosition(25, 780);
    gui.add(pointsLabel);

    tgui::Slider::Ptr slider = theme->load("Slider");
    slider->setSize({200, 20});
    slider->setPosition(220, 780);

    gui.add(slider);

}

int main()
{
    sf::Vector2i topLeft(10,10);

    NoiseGenerator noiseGenerator(topLeft);

    sf::RenderWindow window{{1440, 900}, "Noise Maker"};
    tgui::Gui gui{window}; // Create the gui and attach it to the window
    loadWidgets(gui);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            gui.handleEvent(event); // Pass the event to the widgets
        }

        window.clear(sf::Color(19, 17, 17));

        gui.draw(); // Draw all widgets
        noiseGenerator.draw(window);
        window.display();
    }
}
