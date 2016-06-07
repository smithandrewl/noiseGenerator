#include <TGUI/TGUI.hpp>
#include "noise_generator.h"

#define MIN_POINTS    1
#define MAX_POINTS 1000

void loadWidgets(NoiseGenerator& noiseGenerator, tgui::Gui& gui) {
    auto theme = std::make_shared<tgui::Theme>("TGUI/widgets/Black.txt");

    tgui::Panel::Ptr panel = theme->load("Panel");

    panel->setPosition({300, 750});
    panel->setSize(860, 250);

    gui.add(panel);

//============ Label for Distance Function Combobox =================
    tgui::Label::Ptr distanceFuncLabel = theme->load("Label");

    distanceFuncLabel->setText("Distance Function:");
    distanceFuncLabel->setSize({200, 25});
    distanceFuncLabel->setPosition(25, 25);

    panel->add(distanceFuncLabel);
// =================================================================

// =========== Distance Function Combobox ==========================
    tgui::ComboBox::Ptr distanceFuncComboBox = theme->load("ComboBox");

    distanceFuncComboBox->setSize({200, 30});
    distanceFuncComboBox->setPosition(220, 25);
    distanceFuncComboBox->addItem("Euclidean");
    distanceFuncComboBox->addItem("Manhattan");
    distanceFuncComboBox->addItem("Chebyshev");
    distanceFuncComboBox->addItem("Other");
    distanceFuncComboBox->addItem("Other1");
    distanceFuncComboBox->addItem("Other2");
    distanceFuncComboBox->addItem("Other3");
    distanceFuncComboBox->addItem("OrthEuclidean");
    distanceFuncComboBox->addItem("OrthManhattan");
    distanceFuncComboBox->addItem("OrthChebyshev");
    distanceFuncComboBox->addItem("OrthOther");
    distanceFuncComboBox->addItem("Average");

    distanceFuncComboBox->setSelectedItem("Euclidean");

    panel->add(distanceFuncComboBox);
// ================================================================


// =========== Label for Color Function Combobox ==================
    tgui::Label::Ptr colorFuncLabel = theme->load("Label");

    colorFuncLabel->setText("Color Function:");
    colorFuncLabel->setSize({200, 25});
    colorFuncLabel->setPosition(25, 75);

    panel->add(colorFuncLabel);
// ================================================================

// ========== Color Function Combobox =============================
    tgui::ComboBox::Ptr colorFuncComboBox = theme->load("ComboBox");

    colorFuncComboBox->setSize({200, 30});
    colorFuncComboBox->setPosition(220, 75);
    colorFuncComboBox->addItem("Linear");
    colorFuncComboBox->addItem("Xor");
    colorFuncComboBox->addItem("Mod");
    colorFuncComboBox->addItem("And");
    colorFuncComboBox->addItem("Sin");
    colorFuncComboBox->addItem("Tan");

    colorFuncComboBox->setSelectedItem("Linear");

    panel->add(colorFuncComboBox);
// ===============================================================

// ========= Label for Number of Points Slider ===================
    tgui::Label::Ptr pointsLabel = theme->load("Label");

    pointsLabel->setText("Number of Points:");
    pointsLabel->setSize({200, 25});
    pointsLabel->setPosition(25, 125);

    panel->add(pointsLabel);
// ===============================================================

// ======== Number of Points Slider ==============================
    tgui::Slider::Ptr slider = theme->load("Slider");

    slider->setSize({200, 20});
    slider->setPosition(220, 125);
    slider->setMinimum(MIN_POINTS);
    slider->setMaximum(MAX_POINTS);
    slider->setValue(10);

    panel->add(slider);
// ===============================================================

// ======== Label for Invert Distance Checkbox ===================
    tgui::Label::Ptr invertDistanceLabel = theme->load("Label");

    invertDistanceLabel->setText("Invert Distance:");
    invertDistanceLabel->setSize({200, 25});
    invertDistanceLabel->setPosition({25, 170});

    panel->add(invertDistanceLabel);

// ===============================================================

// ======== Invert Distance Checkbox =============================
    tgui::CheckBox::Ptr invertCheckbox = theme->load("CheckBox");

    invertCheckbox->setSize({25, 20});
    invertCheckbox->setPosition({220, 170});

    panel->add(invertCheckbox);

// ===============================================================

// ======== Label for Invert Colors Checkbox =====================
   tgui::Label::Ptr invertColorsLabel = theme->load("Label");

   invertColorsLabel->setText("Invert Colors:");
   invertColorsLabel->setSize({200, 25});
   invertColorsLabel->setPosition({25, 210});

   panel->add(invertColorsLabel);
// ===============================================================

// ======== Invert Colors Checkbox ===============================
   tgui::CheckBox::Ptr invertColorsCheckbox = theme->load("CheckBox");

   invertColorsCheckbox->setSize({25, 20});
   invertColorsCheckbox->setPosition({220, 210});

   panel->add(invertColorsCheckbox);
// ===============================================================

// ======== Generate Button ======================================
    tgui::Button::Ptr button = theme->load("Button");

    button->setText("Generate");
    button->setSize({400, 45});
    button->setPosition(440, 25);

    button->connect("clicked", [&noiseGenerator, slider, colorFuncComboBox, distanceFuncComboBox, invertCheckbox, invertColorsCheckbox]() {

        noiseGenerator.setInverted(invertCheckbox->isChecked());
        noiseGenerator.setInvertColors(invertColorsCheckbox->isChecked());
        // set color function
        std::string colorFunction    = colorFuncComboBox->getSelectedItem();
        std::string distanceFunction = distanceFuncComboBox->getSelectedItem();

        ColorFunction    colorFunc    = Linear;
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
        } else if (distanceFunction == "Other1") {
            distanceFunc = Other1;
        } else if (distanceFunction == "Other2") {
            distanceFunc = Other2;
        } else if (distanceFunction == "Other3") {
            distanceFunc = Other3;
        }
        else if (distanceFunction == "OrthEuclidean") {
            distanceFunc = OrthEuclidean;
        } else if (distanceFunction == "OrthManhattan") {
            distanceFunc = OrthManhattan;
        } else if (distanceFunction == "OrthChebyshev") {
           distanceFunc = OrthChebyshev;
        } else if (distanceFunction == "OrthOther") {
          distanceFunc = OrthOther;
        }

        noiseGenerator.setDistanceFunction(distanceFunc);

        noiseGenerator.setNumberOfPoints(slider->getValue());
        noiseGenerator.generate();
    });

    panel->add(button);
// ===============================================================
}

int main()
{
    sf::Vector2i topLeft(10,10);

    NoiseGenerator noiseGenerator(topLeft, 10);


    sf::RenderWindow window{{1680, 1050}, "Noise Maker"};
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


        noiseGenerator.draw(window);
        gui.draw(); // Draw all widgets
        window.display();
    }
}
