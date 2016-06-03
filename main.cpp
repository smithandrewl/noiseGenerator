#include <TGUI/TGUI.hpp>
#include "noise_generator.h"

#define MIN_POINTS 30
#define MAX_POINTS 1000

void loadWidgets(NoiseGenerator& noiseGenerator, tgui::Gui& gui) {
    auto theme = std::make_shared<tgui::Theme>("TGUI/widgets/Black.txt");

    tgui::Label::Ptr distanceFuncLabel = theme->load("Label");
    distanceFuncLabel->setText("Distance Function:");
    distanceFuncLabel->setSize({200, 25});
    distanceFuncLabel->setPosition(25, 670);

    gui.add(distanceFuncLabel);

    tgui::ComboBox::Ptr distanceFuncComboBox = theme->load("ComboBox");
    distanceFuncComboBox->setSize({200, 30});
    distanceFuncComboBox->setPosition(220, 670);
    distanceFuncComboBox->addItem("Euclidean");
    distanceFuncComboBox->addItem("Manhattan");
    distanceFuncComboBox->addItem("Chebyshev");
    distanceFuncComboBox->addItem("Other");
    //distanceFuncComboBox->addItem("OrthEuclidean");
    //distanceFuncComboBox->addItem("OrthManhattan");
    //distanceFuncComboBox->addItem("OrthChebyshev");
    //distanceFuncComboBox->addItem("OrthOther");

    distanceFuncComboBox->setSelectedItem("Euclidean");
    gui.add(distanceFuncComboBox);

    tgui::Label::Ptr colorFuncLabel = theme->load("Label");
    colorFuncLabel->setText("Color Function:");
    colorFuncLabel->setSize({200, 25});
    colorFuncLabel->setPosition(25, 705);

    gui.add(colorFuncLabel);

    tgui::ComboBox::Ptr colorFuncComboBox = theme->load("ComboBox");
    colorFuncComboBox->setSize({200, 30});
    colorFuncComboBox->setPosition(220, 705);
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
    pointsLabel->setPosition(25, 750);
    gui.add(pointsLabel);

    tgui::Slider::Ptr slider = theme->load("Slider");
    slider->setSize({200, 20});
    slider->setPosition(220, 750);
    slider->setMinimum(MIN_POINTS);
    slider->setMaximum(MAX_POINTS);
    slider->setValue(MIN_POINTS);
    gui.add(slider);

    tgui::Button::Ptr button = theme->load("Button");

    button->setText("Generate");
    button->setSize({400, 45});
    button->setPosition(25, 825);

    button->connect("clicked", [&noiseGenerator, slider, colorFuncComboBox, distanceFuncComboBox]() {

        // set color function
        std::string colorFunction = colorFuncComboBox->getSelectedItem();
        std::string distanceFunction = distanceFuncComboBox->getSelectedItem();

        ColorFunction colorFunc = Linear;
        DistanceFunction distanceFunc = Euclidean;

        if(colorFunction == "Linear") {
          colorFunc = Linear;
        } else if(colorFunction == "Xor") {
          colorFunc = Xor;
        } else if(colorFunction == "Mod") {
          colorFunc = Mod;
        } else if(colorFunction == "And") {
          colorFunc = And;
        } else if(colorFunction == "Sin") {
          colorFunc = Sin;
        } else if(colorFunction == "Tan") {
          colorFunc = Tan;
        }
        noiseGenerator.setColorFunction(colorFunc);

        if(distanceFunction == "Euclidean") {
            distanceFunc = Euclidean;
        } else if (distanceFunction == "Manhattan") {
            distanceFunc = Manhattan;
        } else if (distanceFunction == "Chebyshev") {
            distanceFunc = Chebyshev;
        } else if (distanceFunction == "Other") {
            distanceFunc = Other;
        }
        noiseGenerator.setDistanceFunction(distanceFunc);
        // set distance function

        noiseGenerator.setNumberOfPoints(slider->getValue());
        noiseGenerator.generate();
    });

    gui.add(button);

}

int main()
{
    sf::Vector2i topLeft(10,10);

    NoiseGenerator noiseGenerator(topLeft, MIN_POINTS);

    sf::RenderWindow window{{1440, 900}, "Noise Maker"};
    tgui::Gui gui{window}; // Create the gui and attach it to the window
    loadWidgets(noiseGenerator, gui);

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
